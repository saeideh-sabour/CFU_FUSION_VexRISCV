# وضعیت قطعی پروژه — 2026-10-13 — نسخه V1

این فایل نقطه شروع ادامه کار است. ابتدا این فایل، سپس docs/AUDIT_FA.md و verification/audit.json خوانده شود.

## هدف تغییرناپذیر
- مدل اصلی MNIST گروه هوش مصنوعی؛ بدون آموزش مجدد یا تعویض وزن.
- یک موتور قابل استفاده مجدد Conv+Requantization+ReLU در خانواده cfu_op0.
- یک موتور MaxPool در خانواده cfu_op1.
- FC1، ReLU مربوط به FC1 و FC2 روی CPU باقی بمانند.
- سه حالت مسیر خروجی Conv: CPU/Memory، داخلی به Pool، هر دو.
- در fusion، tensor میانی Conv به RAM اصلی نوشته و از RAM خوانده نشود.
- CPU-only، CFU-unfused و CFU-fused با یک مدل و ورودی مقایسه شوند.
- بردها: Nexys Video و Nexys A7-100T؛ منابع و timing برای هر برد جدا.

## مسیر ثابت جدید پیشنهادی در WSL
`~/MNIST_CFU_FUSION_20261013_V1`

هیچ پروژه قبلی بازنویسی، حذف یا clean نشود. CFU-Playground فعلی محل ابزار است؛ پروژه جدید آن پس از بررسی Makefile با نام مستقل ساخته می‌شود. مسیر build و پل ویندوز نیز باید مختص همین نسخه و برد باشد. هنوز آن اتصال انجام نشده است.

## انجام‌شده و مستند
- تمام ۱۸ عضو ZIP شناسایی؛ اسکریپت‌ها، notebook، متن DOCX، خروجی‌ها و metadata مدل بررسی شد.
- checkpoint کوانتیزه با decoder محدود و بدون اجرای pickle دلخواه استخراج شد.
- SHA256 همه فایل‌ها در verification/audit.json ثبت شد.
- ۱۲۶۸۲۰ مقدار ورودی/میانی/نهاییِ ۱۰ تصویر با بازسازی NumPy مقایسه شد: صفر اختلاف.
- فایل وزن `_sd.txt` برای هر چهار لایه با checkpoint برابر است؛ فایل بدون `_sd` متفاوت است.
- Requantization صحیح Q31 با round-to-nearest ties-to-even روی این ۱۰ تصویر برابر است.
- software/cpu_reference.c با gcc -O2 -Wall -Wextra -Werror -std=c11 کامپایل و اجرا شد؛ تمام ۱۱۸۹۸۰ مقدار خروجی میانی/نهایی برابر است.
- خروجی ده تصویر: 7,2,1,0,4,1,4,9,5,9.

## هنوز انجام نشده؛ نباید PASS اعلام شود
- صحت Q31 نسبت به PyTorch روی کل ۱۰۰۰۰ تصویر.
- RTL، شبیه‌سازی HDL، اتصال به CFU-Playground و اجرای RISC-V.
- اجرای Renode یا اجرای واقعی برد.
- synthesis/place-and-route، منابع، Fmax، cycles یا speedup واقعی.
- اندازه‌گیری زمان load/config/drain و اثبات عدم مراجعه به RAM برای tensor میانی در fusion.

## قدم بعدی دقیق
1. بسته در مسیر جدید نصب شود؛ tools/inspect_wsl.sh فقط محیط فعلی را بخواند.
2. خروجی inspect برای تطبیق cfu.h، proj.mk، کامپایلر و پل Vivado بررسی شود.
3. قرارداد numeric Q31، opcode، ظرفیت بانک‌ها و ارزیابی کل test set تثبیت شود.
4. CPU-only روی RISC-V؛ سپس RTL دو موتور و تست مستقل، سپس integration.
5. CFU-unfused سپس fused؛ برابری layer-by-layer شرط ورود به benchmark.
6. ابتدا یک برد end-to-end؛ بعد همان سورس با target و build مستقل روی برد دوم.

## قواعد ادامه
- خروجی واقعی را از تحلیل یا تخمین جدا بنویس.
- هر بار نسخه سورس، ورودی، فرمان، نتیجه و NEXT_ACTION ثبت شود.
- خطا موجب تغییر مسیر، تغییر وزن یا جایگزینی پروژه با مثال‌های قدیمی نشود.
- یک wrapper نرم‌افزاری برای هر لایه با یک دستور CPU برابر نیست؛ load/config/read می‌توانند چند دستور باشند.
- زمان یا منابع را از شمارش MAC یا خروجی Python جعل نکن.
- این بسته مرحله ممیزی و baseline است؛ RTL کامل تحویلی نیست.

## UPDATE STEP02 — این بخش از وضعیت اولیه جدیدتر است
- نصب بسته و بررسی محیط WSL موفق بود.
- مسیر ثابت: /home/ksrtakosar/MNIST_CFU_FUSION_20261013_V1
- CFU-Playground commit: 7f8ec4147b39db98534f8a10f9ddb1c26aca5648
- ابزارهای gcc، Verilator، Icarus، Yosys و RISC-V GCC موجودند.
- مرجع C روی WSL کامپایل و اجرا شد و با کد خروج صفر پایان یافت.
- لاگ واقعی: results/host/cpu_reference_wsl.txt
- این آزمایش روی CPU میزبان است؛ اجرای RISC-V یا FPGA نیست.
- RTL و اندازه‌گیری cycles/resources هنوز انجام نشده‌اند.
- NEXT: بررسی پل Vivado و قواعد build؛ سپس پیاده‌سازی و تست RTL
  دو موتور Conv+Requant+ReLU و Pool با مسیر داخلی fusion.
- پروژه‌های قبلی و فایل‌های عمومی CFU-Playground تغییر نکنند.

## STEP03 LOCAL RTL TEST PASS — supersedes earlier pending RTL status
- CPU Q31 reference passed on user WSL (reported 2026-10-13).
- Local Verilator test now passed: 10 samples, 3 modes, zero mismatches.
- UNFUSED, FUSED, BOTH; Conv/Pool computed in RTL, FC on host CPU.
- Source: rtl/step03; driver: software/step03/cfu_driver.h.
- Evidence: results/rtl_step03/run.log and build.log.
- Not yet RISC-V/FPGA execution; no hardware cycles/resources measured.
- NEXT: tools/step03/setup_integration.py; then isolated project software build.
- Never invoke the old shared Vivado bridge for this project: it deletes its shared directory.

## STEP03 Integration files prepared (build/run not yet verified)
- CFU Playground project: /home/ksrtakosar/CFU-Playground/proj/mnist_cfu_fusion_20261013_v1
- Source workspace remains: /home/ksrtakosar/MNIST_CFU_FUSION_20261013_V1
- Private Vivado wrapper: tools/step03/bin/vivado; new Windows directory per build.
- NEXT: build software in independent project; inspect errors before board synthesis.

## STEP03 C LINKAGE FIX — SOFTWARE BUILD PASSED
- Previous link failed: undefined reference to do_proj_menu.
- Fixed definition to extern "C" in canonical and integration sources.
- Rebuilt software successfully after correction.
- Evidence: results/step03_software_linkfix.log
- FPGA synthesis, programming and resource/cycle measurements remain pending.
- NEXT: build gateware using the project-private Vivado bridge.

## STEP04 GATEWARE BUILD STARTED
- RISC-V software build passed; software.elf and software.bin generated.
- Target: digilent_nexys_video
- Private Vivado bridge selected.
- Synthesis/implementation started; success not yet established.
- Log: results/step04_gateware_build.log
- FPGA programming has not been requested in this step.

## STEP03 LOCAL RTL TEST PASS — supersedes earlier pending RTL status
- CPU Q31 reference passed on user WSL (reported 2026-10-13).
- Local Verilator test now passed: 10 samples, 3 modes, zero mismatches.
- UNFUSED, FUSED, BOTH; Conv/Pool computed in RTL, FC on host CPU.
- Source: rtl/step03; driver: software/step03/cfu_driver.h.
- Evidence: results/rtl_step03/run.log and build.log.
- Not yet RISC-V/FPGA execution; no hardware cycles/resources measured.
- NEXT: tools/step03/setup_integration.py; then isolated project software build.
- Never invoke the old shared Vivado bridge for this project: it deletes its shared directory.
