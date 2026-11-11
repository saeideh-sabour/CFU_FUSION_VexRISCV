# STEP06 — Configuration pipeline

این نسخه مستقل از STEP05 است. مقصد پیشنهادی:
~/MNIST_CFU_FUSION_20261013_V1/revisions/MNIST_STEP06_TIMING

## شواهد مرحله قبل
STEP05 روی سیستم کاربر سنتز شد: کل SoC=5999 LUT /4154 FF /28 BRAM36-equivalent /17 DSP.
CFU=974 LUT /397 FF /4.5 BRAM36-equivalent /13 DSP.
WNS=-3.918ns در کلاک75MHz؛ هنوز timing پاس نشده بود.
گزارش ارسال‌شده مسیر height_reg -> valid_conv -> منطق کنترل -> DSP CEB2/CEA2 را نشان می‌دهد.
تأخیر بدترین مسیر16.522ns،16 سطح منطق، نیاز13.333ns است. این مسیر به پایه enable می‌رسد؛ شاهدی برای خطای محاسبات عددی نیست.

## اصلاح STEP06
پس از هر دستور CONFIG، سه مرحله CFG1/CFG2/CFG3 اجرا می‌شوند:
1. ثبت plane=width*height و kernel_len=cin*9.
2. ثبت تعداد خروجی، تعداد ورودی و تعداد وزن‌ها.
3. ثبت valid_conv و valid_pool و سپس صدور پاسخ CONFIG.
تا پایان این مراحل، فرمان بعدی پذیرفته نمی‌شود. نتیجه خطای CONFIG نیز حفظ می‌شود.
این تغییر محاسبات ابعاد/اعتبارسنجی را از زنجیره ترکیبی طولانی کنترل جدا می‌کند.
فرمت ISA، driver، MAC4، BRAMها، requantization، ReLU، pooling و مسیر داخلی Fusion حفظ شده‌اند.
هر CONFIG سه سیکل انتظار اضافه دارد؛ حلقه gather/MAC نسبت به STEP05 تغییر نکرده است.
CPU، قیود کلاک و فرکانس تغییر نکرده‌اند. نتیجه زمان‌بندی نهایی فقط با سنتز/پیاده‌سازی مشخص می‌شود.

## صحت و حدود اعتبار
در محیط دستیار Verilator اجرا شد؛ evidence/run.log:
RTL_CORNER_TESTS PASS
RTL_ADDRESS_TESTS PASS shapes=8 including capacity boundaries
RTL_ALL_MODES PASS samples=10 modes=3 mismatches=0
FC روی میزبان اجرا می‌شود. این آزمون اجرای برد یا benchmark سرعت نیست.
سنتز Vivado برای STEP06 هنوز انجام نشده؛ منابع STEP05 را به STEP06 نسبت ندهید.

## اجرا روی WSL
bash tools/run_tests.sh
python3 tools/synth_only.py

اسکریپت سنتز فقط Synthesis و گزارش‌ها و checkpoint را می‌سازد.
Placement/Route/Bitstream خودکار اجرا نمی‌شود.
اصلاح کوتیشن cmd.exe که در STEP05 روی سیستم کاربر جواب داد، داخل این بسته اعمال شده است.
فایل‌های init اصلی از bridge قدیمی خوانده می‌شوند و منابع اصلی CPU/top/XDC با snapshot تطبیق داده می‌شوند.
هیچ پروژه قبلی بازنویسی نمی‌شود؛ هر اجرای Vivado فولدر جدید زمان‌دار دارد.
برای این مرحله نیازی به گزینه --stop-old-build نیست.

در پایان جدول hierarchical و WNS را به چت بفرستید.
اگر همچنان منفی بود، گزارش مسیر بحرانی جدید باید بررسی شود؛ ادعای timing-pass نداریم.

## محدوده معماری
Conv3x3 stride1 pad1 بدون bias؛ Pool2x2 stride2؛ ورودی/خروجیUINT8 و وزنINT8؛ Q31 ties-even.
ظرفیت‌ها و سه حالت UNFUSED/FUSED/BOTH مثل STEP05 هستند.
هدف نهایی همچنان مقایسه صحت و سیکل‌ها و منابع با CPU و اجرای دو برد است.
جزئیات سابقه در README_STEP05_HISTORY.md و PROJECT_STATE.md نگهداری شده‌اند.
