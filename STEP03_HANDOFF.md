# ادامه پروژه — STEP03 — 2026-10-13

## هدف ثابت
دو خانواده custom instruction: op0=Conv3x3+INT32 Accumulate+Q31 Requant+ReLU، op1=MaxPool2x2؛ FC روی CPU. یک موتور Conv برای هر دو لایه. مسیر CAPTURE/STREAM/BOTH؛ در fusion هیچ tensor میانی Conv از RAM اصلی عبور نکند. مقایسه CPU_ONLY، CFU_UNFUSED، CFU_FUSED روی Nexys Video و Nexys A7-100T.

## مسیرهای ثابت
- منبع اصلی: /home/ksrtakosar/MNIST_CFU_FUSION_20261013_V1
- پروژه مستقل integration که setup می‌سازد: /home/ksrtakosar/CFU-Playground/proj/mnist_cfu_fusion_20261013_v1
- این مسیر integration جایگزین منبع اصلی نیست؛ کپی مخصوص build است.
- هرگز پروژه قدیمی mnist_cnn_cfu_fusion_accel_v1 یا فایل‌های عمومی CFU-Playground را بازنویسی نکن.

## شواهد قطعی
- CPU_Q31_REFERENCE PASS روی WSL کاربر گزارش شد؛ ده تصویر و همه خروجی‌های بررسی‌شده برابرند.
- RTL واقعی نوشته شده: rtl/step03/{mac4,requant_q31,pool2x2_stream,cfu_top}.v و فایل یکپارچه cfu.v.
- Verilator در محیط دستیار build و اجرا شد؛ RTL_CORNER_TESTS PASS و RTL_ALL_MODES PASS samples=10 modes=3 mismatches=0.
- در این شبیه‌سازی Conv/Pool در RTL و FC روی CPU میزبان هستند؛ هنوز CPU RISC-V یا برد اجرا نشده است.
- Predictions برای هر سه mode: 7,2,1,0,4,1,4,9,5,9.
- لاگ دستیار: verification/step03_assistant_run.log.
- قرارداد دقیق: docs/STEP03_INTERFACE.md.

## محیط کاربر تأییدشده
CFU-Playground commit 7f8ec4147b39db98534f8a10f9ddb1c26aca5648 با تغییرات محلی موجود؛ آنها حفظ شوند. gcc، Verilator، Icarus، Yosys، RISC-V GCC موجودند. pyrun فایل environment را source می‌کند. NumPy/Torch در Python فعال موجود نیستند؛ برای مرحله فعلی لازم نیستند.

پل عمومی ~/bin/vivado در هر build پوشه مشترک F:\k\CFU_Vivado_Bridge\digilent_nexys4ddr را حذف می‌کند؛ برای این پروژه استفاده نشود. setup_integration.py یک کپی خصوصی می‌سازد که در هر build مسیر تازه مختص همین پروژه ایجاد می‌کند. خود setup نه Vivado را اجرا می‌کند نه پوشه قبلی را حذف می‌کند.

## مرحله جاری و کار بعد
1. نصب آپدیت STEP03 داخل همان مسیر اصلی؛ فایل‌های قدیمی جابه‌جا نشوند.
2. اجرای bash tools/step03/run_tests.sh روی WSL کاربر؛ خروجی محلی هنوز از کاربر دریافت نشده است.
3. اجرای python3 tools/step03/setup_integration.py پس از PASS؛ سپس build نرم‌افزار پروژه مستقل.
4. رفع خطای build فقط براساس لاگ؛ سپس SoC/برد با پل خصوصی، ابتدا Nexys Video.
5. سپس برد دوم، گزارش cycles، LUT/FF/DSP/BRAM و timing واقعی؛ این نتایج هنوز وجود ندارند.

## محدودیت‌های صریح
RTL در این مرحله functional baseline است؛ mapping حافظه‌های چندپورتی، banking و مسیر محاسبه آدرس هنوز از نظر منابع/زمان بهینه نشده. ادعای fit یا timing closure نداریم. سه حالت روی ده تصویر بررسی شده، نه کل test set. CPU-only در harness integration روی SoC دارای CFU اجرا می‌شود؛ برای مقایسه منابع کل، build مجزای بدون CFU لازم است.

## قالب جواب‌های بعدی
هر پاسخ: کار انجام‌شده / نتیجه واقعی / قدم بعد / خلاصه انتقال به چت بعد. وضعیت واقعی را بعد از هر مرحله به PROJECT_STATE.md اضافه کن. اگر ادامه به چت دیگری منتقل شد، این فایل و آخرین PROJECT_STATE.md و لاگ را بخوان؛ از ابتدا پروژه را نساز.
