# STEP05 BRAM — نسخه مستقل اصلاح مصرف منابع

## وضعیت و علت تغییر
این بسته نسخه جدیدی است؛ پروژه اصلی و integration قبلی را تغییر نمی‌دهد.
از snapshot واقعی ارسالی routing_diagnostic_20261013_232540_100095.zip استفاده شده است.

در Vivado قدیمی inputs_reg و weights_reg به رجیستر تبدیل شدند (Synth 8-4767).
ظرفیت آن دو آرایه جمعاً 49152 بیت است؛ CFU در گزارش placement دارای 49614 FF بود.
خروجی Conv و Pool به RAM توزیع‌شده نگاشت شدند و CFU هیچ BRAM نداشت.
منابع کل: 120171 LUT، 54036 FF، 23.5 BRAM36-equivalent، 22 DSP.
سهم CFU: 59271 LUT؛ سهم گزارش‌شده VexRiscv: 58935 LUT.
این سهم VexRiscv معادل CPU-only baseline نیست. اثر نگاشت کل طراحی باید با سنتز مجدد بررسی شود؛ سورس CPU تغییر نکرده است.

بدترین مسیر سنتز از kernel_index_reg به lx_reg با WNS=-26.546ns، تأخیر39.693ns و 50 سطح منطق بود.
کلاک این مسیر 75MHz (13.333ns) است. این گزارش پیش از routing است، نه نتیجه نهایی timing.

## اصلاح واقعی RTL
- ورودی و وزن: یک write سی‌ودوبیتی در هر بانک، به جای چهار نوشتن مستقل بایتی؛ read کلاک‌دار.
- خروجی Conv و Pool: read کلاک‌دار و یک سیکل تأخیر پاسخ READ برای سازگاری با RAM.
- حافظه‌ها reset نمی‌شوند؛ reset فقط شمارنده و کنترل و اعتبار داده‌ها را پاک می‌کند.
- مختصات کرنل با شمارنده kx/ky و channel_base تولید می‌شود؛ تقسیم و باقیمانده آدرس از FETCH حذف شده است.
- محاسبه مختصات، آدرس، خواندن RAM و ثبت lane مراحل جدا دارند.
- چهار operand به ترتیب جمع‌آوری می‌شوند و سپس MAC4 واقعی اجرا می‌شود.
- درخواست use_dsp برای ضرب‌های MAC4؛ نتیجه واقعی mapping فقط با سنتز روشن می‌شود.
- Conv START همچنان کل لایه را تا پایان اجرا می‌کند؛ فقط یک MAC نیست.
- requantization Q31 ties-to-even و ReLU و stream داخلی و حالت capture/both حفظ شده‌اند.
- دستورها، driver، شناسه ISA و قالب پارامترها تغییر نکرده‌اند.

این نسخه عمداً operandها را ترتیبی می‌خواند تا مصرف منابع کنترل شود. ممکن است سیکل Conv بیشتر شود؛ هیچ ادعای speedup یا fit یا timing-pass نداریم. بهبود بعدی پس از گرفتن اعداد واقعی می‌تواند بانک‌بندی/پایپ‌لاین باشد.

## محدوده عمومی بودن
پارامترپذیر برای اندازه‌ها و کانال‌های داخل ظرفیت، اما فقط Conv3x3 stride1 padding1 بدون bias و Pool2x2 stride2.
ورودی/خروجی UINT8، وزن INT8 متقارن، multiplier مثبت Q31 per-channel.
FC1/ReLU/FC2 روی CPU باقی می‌مانند. هنوز پشتیبانی از هر شبکه یا هر نوع کانولوشن وجود ندارد.
حد پیش‌فرض: ورودی2048 بایت، وزن4096 بایت، Conv8192 بایت، Pool4096 بایت، عرض/ارتفاع/کانال تا32، با بررسی حاصل‌ضرب ظرفیت‌ها.

## آزمون‌ها
evidence/run.log خروجی اجرای واقعی Verilator در محیط دستیار است.
- ده نمونه MNIST در UNFUSED، FUSED، BOTH با مقایسه tensorهای قابل مشاهده.
- FC روی میزبان؛ این آزمون اجرای RISC-V یا FPGA نیست.
- operandهای فرمان بلافاصله پس از پذیرش تغییر می‌کنند و پاسخ با backpressure بررسی می‌شود.
- آزمون گردکردن، saturation، zero point، دستور نامعتبر و reset.
- هشت شکل اضافه، شامل کانال32، عرض32، ظرفیت کامل ورودی و خروجی، ابعاد فرد و مرز کلمات حافظه.

اجرای محلی روی WSL:
```bash
bash tools/run_tests.sh
python3 tools/synth_only.py --stop-old-build
```

## رفتار synth_only.py
1. یکپارچگی بسته و PASS محلی شبیه‌سازی را بررسی می‌کند.
2. CPU/top/XDC نسخه قدیمی را با snapshot مقایسه می‌کند.
3. فایل‌های اصلی rom/sram/mem.init را از همان bridge قدیمی بازیابی می‌کند؛ نبودن آن‌ها خطاست.
4. گزارش‌های قبلی را در results/synth_<timestamp>/old_evidence نگه می‌دارد.
5. تنها اگر --stop-old-build داده شود، Vivado با command line حاوی مسیر دقیق بیلد قدیمی را متوقف می‌کند.
   هیچ پروژه دیگر را متوقف نمی‌کند. اگر Vivado دیگری فعال باشد، سنتز جدید را شروع نمی‌کند.
6. فولدر جدید Windows برای این اجرا می‌سازد؛ هیچ rm -rf یا نوشتن روی پروژه قدیمی ندارد.
7. همان CPU، top، قیود و directive سنتز را با CFU جدید اجرا می‌کند.
8. گزارش منابع و timing و checkpoint سنتز ذخیره می‌شود. Placement/Route/Bitstream اجرا نمی‌شوند.
9. SYNTH_ONLY_COMPLETE به معنی timing pass یا اجرای برد نیست.

قبل از synthesis جدید باید منابع و timing بررسی شوند. برای CFU انتظار نگاشت چهار بانک بزرگ به BRAM داریم؛ هنوز Vivado جدید در محیط دستیار اجرا نشده است. اگر مصرف VexRiscv همچنان بالا بود، آن را جداگانه بررسی می‌کنیم؛ CPU را بر اساس حدس تعویض نمی‌کنیم.

## مسیرها
- rtl/cfu.v: تنها RTL جدید
- simulation/tb_step05.cpp: تست‌های golden و مرزی
- software و model: مرجع/driver/داده تست
- snapshot: سورس اصلی CPU/SoC/XDC از فایل ارسالی
- evidence/step03: منابع و timing قدیمی
- evidence/run.log و build.log: نتیجه دستیار برای نسخه جدید
- results: خروجی اجرای کاربر، هر سنتز در فولدر زمان‌دار جدا
- PROJECT_STATE.md: نقطه ادامه کار

مبنای الگوی حافظه: AMD UG901، Choosing Between Distributed RAM and Dedicated Block RAM؛ BRAM دارای read همگام است.
https://docs.amd.com/r/2022.1-English/ug901-vivado-synthesis/Choosing-Between-Distributed-RAM-and-Dedicated-Block-RAM
