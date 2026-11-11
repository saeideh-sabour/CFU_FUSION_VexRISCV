# ممیزی فنی مدل MNIST و قرارداد پیشنهادی CFU

تاریخ: ۱۳ اکتبر ۲۰۲۶. شواهد عددی در verification/audit.json و cpu_host_result.txt موجودند.

## ۱. پروژه گروه هوش مصنوعی چیست؟
یک CNN کوچک PyTorch برای تشخیص ارقام MNIST است. آموزش در notebook با Adam، نرخ 0.001، CrossEntropy، ده epoch و batch=64 انجام شده. ورودی تقسیم بر 255 می‌شود. کوانتیزه‌سازی پس از آموزش با fbgemm و فقط یک batch از train برای calibration انجام شده. خروجی ذخیره‌شده notebook دقت FP32 را 98.65% و INT8 را 98.74% گزارش می‌کند؛ این ممیزی دقت کل test set را دوباره اندازه نگرفته است. برای حفظ مدل فعلی نباید مجدداً calibration یا training انجام دهیم.

| مرحله | خروجی CHW | وزن | MAC برای هر تصویر، با احتساب padding |
|---|---|---|---:|
| Input | 1×28×28 | — | — |
| Conv1+ReLU+Requant | 8×28×28 | 8×1×3×3 | 56,448 |
| MaxPool1 2×2 stride2 | 8×14×14 | — | — |
| Conv2+ReLU+Requant | 16×14×14 | 16×8×3×3 | 225,792 |
| MaxPool2 2×2 stride2 | 16×7×7 | — | — |
| Flatten | 784 | — | — |
| FC1 سپس ReLU | 64 | 64×784 | 50,176 |
| FC2 | 10 | 10×64 | 640 |

همه لایه‌ها bias=False دارند. مجموع 333,056 MAC است؛ سهم Conv حدود 84.74% و FC حدود 15.26% است. FC1 محاسبات صفر یا ناچیز ندارد، ولی مطابق نیاز پروژه روی CPU می‌ماند. این درصد MAC معادل درصد زمان اجرا نیست. تعداد وزن 52,040 بایت INT8 است؛ 50,816 بایت آن مربوط به FC است. برای بهبود سرعت نهایی، سهم زمانی FC باید واقعاً اندازه‌گیری شود.

## ۲. کدام فایل مرجع است؟

| فایل | تصمیم |
|---|---|
| mnist_cnn_int8.pth | checkpoint مرجع؛ داده‌های عددی مستقیماً از آن استخراج شد |
| model.ipynb | ساختار/آموزش/کوانتیزه‌سازی مرجع، بدون نیاز به اجرای مجدد training |
| layer_outputs.txt | golden ده تصویر نخست test CSV؛ با checkpoint بازسازی و تطبیق شد |
| weights_int8(bias_int8)_matrix_conv_sd.txt | وزن‌های هر چهار لایه دقیقاً مطابق checkpoint |
| requant_params.txt | scaleها و multiplierها؛ به‌تنهایی برای اجرا کافی نیست، zero pointها لازم است |
| weights_int8(bias_int8)_matrix_conv.txt | نسخه متفاوت؛ وارد baseline نشود |
| mnist_cnn_int8.pt و weights_int8.txt | مسیر export قدیمی و مستقل؛ بدون اثبات هم‌ارزی با مرجع استفاده نشود |
| mnist_cnn.pth | checkpoint float؛ برای CPU integer baseline جایگزین مدل INT8 نشود |
| test.py | نیازمند اصلاح ورودی دستی و حلقه نتایج؛ مستقیماً مبنای تحویل نیست |
| layer_outputs_for_specific_input.txt | خروجی ناقص؛ golden کامل inference نیست |
| MNIST Simple CNN.docx | شرح مفهومی؛ ترتیب دقیق و zero pointها از checkpoint تعیین شود |

فایل بدون `_sd` نسبت به مرجع در Conv1 تعداد 71 از 72، Conv2 تعداد 1140 از 1152، FC1 تعداد 49781 از 50176 و FC2 تعداد 635 از 640 وزن متفاوت دارد.

export_weights.py ساختاری با bias پیش‌فرض دارد و از مدل .pt بارگذاری می‌کند؛ این مسیر با checkpoint bias=False فعلی یکسان فرض نشود. اسکریپت‌های export_matrix و export_requant برخلاف notebook، FC1+ReLU را هم fuse می‌کنند. وجود فایل با نام bias_int8 دلیل وجود bias نیست؛ checkpoint فعلی هیچ bias ندارد.

ترتیب وزن در export متنی کانولوشن [Cin][Kh×Kw][Cout] است؛ checkpoint و header جدید [Cout][Cin][Kh][Kw] هستند. FC متنی [input][output] است، header جدید [output][input]. جابه‌جایی این ترتیب بدون تبدیل، نتیجه را خراب می‌کند.

## ۳. خطاهای test.py
ورودی دستی دارای شکل 1×1×1×584 است؛ تصویر 1×1×28×28 نیست. حتی تعداد عناصر 784 نیست که صرفاً با reshape حل شود. باید از CSV معتبر استفاده شود. اولین Pool با ارتفاع 1 خروجی معتبر ایجاد نمی‌کند. لاگ مربوطه پس از Conv1+ReLU متوقف شده است. افزون بر آن، حلقه نهایی ده پیش‌بینی می‌خواند، در حالی که ورودی دستی یک نمونه است. راه‌حل این بسته استفاده از ده سطر نخست CSV و golden سازگار است.

## ۴. قرارداد عددی
Activation از نوع UINT8 و weight از نوع INT8 است؛ اشتباه گرفتن activation با INT8 signed به‌خصوص در FC غلط است. وزن‌ها per-output-channel scale و zero point صفر دارند. INT32 accumulator در ابعاد این مدل کافی است؛ برای مدل بزرگ‌تر باید کران دوباره محاسبه شود.

acc[o] = Σ (qx - zx) × (qw - zw[o])

M[o] = sx × sw[o] / sy

qy = clamp(round(acc[o] × M[o]) + zy, 0, 255)

ReLU در فضای quantized یعنی max(qy, zy)، نه همواره max(qy, 0). Padding ورودی نیز باید zx باشد.

| مرحله | sx | zx | sy | zy |
|---|---:|---:|---:|---:|
| Conv1 | 0.007870171219110489 | 0 | 0.020095039159059525 | 0 |
| Conv2 | 0.020095039159059525 | 0 | 0.05678895115852356 | 0 |
| FC1 | 0.05678895115852356 | 0 | 0.5123212933540344 | 70 |
| FC2 | 0.5123212933540344 | 70 | 0.4178983271121979 | 73 |

MaxPool scale و zero point را تغییر نمی‌دهد. FC1 ReLU باید مقادیر زیر 70 را به 70 ببرد. ورودی FC2 باید پیش از ضرب، 70 از آن کم شود. خروجی FC2 به ReLU نیاز ندارد. برای انتخاب کلاس، argmax خروجی UINT8 FC2 کافی است؛ dequantization با scale مثبت مشترک رتبه را تغییر نمی‌دهد.

Q31 پیشنهادی فعلی: multiplier = round_even(M×2^31)، ضرب INT32×INT32 با حاصل INT64، تقسیم بر 2^31 با round-to-nearest ties-to-even، سپس zero point و clamp. استفاده از فقط `(product + 2^30) >> 31` معادل ties-to-even نیست. کد C نحوه دقیق rounding signed را مشخص می‌کند.

روی ده نمونه، Q31 و golden در همه نقاط برابر شدند؛ این اثبات هم‌ارزی روی تمام ورودی‌ها نیست. خطای تقریب multiplier و تفاوت rounding float backend ممکن است روی داده‌های دیگر یک واحد اختلاف بدهد. گام بعد: کل test set؛ CPU و RTL باید در هر حال یک قرارداد integer واحد داشته باشند و اختلاف نسبت به PyTorch جدا گزارش شود.

## ۵. نتایج واقعاً اجراشده
بازسازی مستقل NumPy از checkpoint، بدون PyTorch، انجام شد. ورودی quantized و هفت نقطه میانی/نهایی در مجموع 126,820 مقدار برای ده نمونه با متن golden دقیقاً برابرند. C integer/Q31 نیز کامپایل و اجرا شده و 118,980 خروجی میانی/نهایی با golden برابرند. کلاس‌ها: 7,2,1,0,4,1,4,9,5,9. این آزمایش CPU میزبان است؛ نه RISC-V، نه FPGA و نه cycle simulation.

## ۶. معماری پیشنهادی سخت‌افزار؛ هنوز پیاده نشده
دو خانواده دستور محاسباتی داریم. cfu_op0 شامل config/load/start/status/read مربوط به Conv است؛ cfu_op1 کنترل مستقل Pool را دارد. funct7 برای زیرعملیات استفاده می‌شود. شماره‌های دقیق funct7 پس از بررسی cfu.h محلی تثبیت می‌شوند. خانواده دستور را با دو ماژول تکراری برای دو لایه اشتباه نگیریم: همان یک موتور با descriptor جدید Conv1 و Conv2 را اجرا می‌کند.

رابط استاندارد CFU داده‌ها را از رجیستر CPU می‌گیرد؛ آدرس دادن در operand به خودی خود دسترسی به RAM ایجاد نمی‌کند. مسیر write-back استاندارد چنین است: CFU → response/read → CPU register → store to RAM. اگر DMA مستقیم لازم شود، تغییر SoC و bus-master کار جداگانه است و شرط fusion داخلی نیست.

پیشنهاد برای تطبیق با فراخوانی لایه‌ای: CPU ابتدا input/weight/config را در بانک داخلی بارگذاری کند. یک START در خانواده op0 اجرای Conv لایه را آغاز کند؛ موتور با MAC4، INT32 accumulation و requant/relu خودش خروجی‌ها را تولید کند. بارگذاری و تخلیه همچنان چند دستور نیاز دارد. wrapper سطح C برای هر لایه یک بار فراخوانی می‌شود. یک custom instruction با دو operand نمی‌تواند تمام تصویر و وزن‌ها را بدون بارگذاری قبلی دریافت کند.

### حالت‌های خروجی
- MEMORY_ONLY: نتیجه Conv در output bank قرار گیرد و CPU آن را بخواند و ذخیره کند؛ Pool ورودی مستقل از CPU بگیرد.
- STREAM_ONLY: خروجی requant/relu فقط وارد مسیر داخلی Pool شود؛ tensor کامل Conv از RAM عبور نکند.
- BOTH: همان خروجی به output bank و FIFO داخلی تحویل داده شود؛ هر خروجی دقیقاً یک بار در هر مقصد ثبت شود.

اگر هدف اجرای Conv کامل با START blocking باشد، Pool در حالت fused باید پیش از START با op1 پیکربندی و ARM شود و هم‌زمان FIFO را مصرف کند. بعد op1 وضعیت و نتیجه pooled را می‌خواند. نباید Conv کامل را روی FIFO کوچک اجرا کرد و تازه بعد از برگشت آن Pool را فعال کرد؛ FIFO پر می‌شود و بن‌بست ایجاد می‌کند. حالت جایگزین، بانک داخلی کامل tensor است که اجازه اجرای ترتیبی می‌دهد ولی BRAM بیشتری می‌خواهد. این دو انتخاب باید صریح باشند؛ طرح پیشنهادی stream از ARM پیشاپیش استفاده می‌کند.

برای ترتیب CHW raster، چهار مقدار پشت سر هم الزاماً پنجره 2×2 نیستند. Pool به مختصات/شمارنده و line buffer نیاز دارد؛ برای یک کانال در هر لحظه یک ردیف 28 بایتی به‌علاوه رجیسترهای لازم کافی است. اگر ترتیب تولید pixel-major یا چندکاناله شود ظرفیت و آدرس‌دهی buffer تغییر می‌کند. ترتیب flatten به FC باید همان CHW باقی بماند.

ورودی Conv2 از Pool1 می‌تواند در RAM ذخیره شود؛ الزام فعلی حذف رفت‌وبرگشت بین هر Conv و Pool همان جفت است. fusion بین دو کانولوشن هدف اضافی نیست.

### نکات RTL که نباید حذف شوند
- MAC4 چهار ضرب unsigned activation / signed weight یا نسخه centered مناسب داشته باشد؛ جمع partialها در INT32.
- Conv1 نه ضرب دارد: سه گروه MAC4 با سه lane نامعتبر در آخر؛ Conv2 هفتادودو ضرب دارد: هجده گروه. lane mask باید درست اعمال شود.
- requant/relu یک بار پس از پایان dot product کامل، نه پس از هر MAC4.
- START accumulator و شمارنده را درست reset کند؛ بارگذاری بعدی state قبلی را مخلوط نکند.
- دسترسی هم‌زمان چهار ورودی/وزن به banking یا prefetch سازگار با BRAM نیاز دارد؛ چهار DSP تنها بخش MAC است و کل مصرف DSP از پیش چهار اعلام نشود.
- valid/ready، نگه‌داشت پاسخ هنگام backpressure، FIFO full/empty، reset و end-of-layer تعریف شوند.
- BOTH دو مقصد را هماهنگ کند؛ overflow نباید موجب حذف بی‌صدای داده شود.
- READ در وضعیت not-ready نباید تنها CPU لازم برای پیشرفت را برای همیشه متوقف کند.
- descriptor شامل ابعاد، کانال‌ها، kernel/stride/padding پشتیبانی‌شده، quantization و routing باشد؛ ظرفیت‌های محدود compile-time و خطای ابعاد unsupported مستند شوند.

«عمومی» یعنی موتور پارامتری با محدوده پشتیبانی روشن؛ نه پشتیبانی خودکار از تمام CNNها. اول Conv 3×3 stride1 pad1 و MaxPool2×2 stride2 را برای این مدل تثبیت می‌کنیم. افزودن dilation/grouped/average pooling توسعه جداست.

## ۷. هزینه حافظه و سنجه‌ها
Conv1 دارای 6272 بایت و Conv2 دارای 3136 بایت خروجی UINT8 است. در baseline با materialization و یک بار خواندن هر عنصر برای Pool، حذف write+read این tensorها برابر 18,816 بایت ترافیک منطقی در هر تصویر است. این عدد به معنای همین مقدار کاهش تراکنش DDR فیزیکی یا همین نسبت speedup نیست؛ cache، packing و driver مؤثرند. در BOTH نوشتن Conv باقی می‌ماند ولی Pool دوباره آن را از RAM نمی‌خواند.

سه mode روی هر برد: CPU_ONLY، CFU_UNFUSED، CFU_FUSED. CPU_ONLY باید واقعاً محاسبات را بدون custom-op انجام دهد. ابتدا روی یک SoC یکسان زمان نرم‌افزار سه mode مقایسه شود. برای هزینه منابع افزوده، یک build SoC بدون CFU و یک build SoC با CFU هم لازم است؛ CPU_ONLY روی FPGA دارای CFU به معنی صفر منابع CFU نیست.

داده مدل، کامپایلر/flags، clock CPU، cache/حافظه و ورودی‌ها ثابت باشند. cycles شامل load، config، compute، drain، stores و FC باشد؛ زمان kernel-only جدا گزارش شود. چاپ UART، مقایسه golden و initialization benchmark بیرون پنجره باشند. warm/cold cache و تکرارها معلوم باشد. CRC به‌تنهایی جای مقایسه کامل tensor را نگیرد.

cycles هر لایه و end-to-end؛ latency = cycles / frequency؛ speedup = CPU total / CFU total تحت شرایط برابر. LUT، FF، DSP، BRAM، timing slack و فرکانس حاصل از implementation برای هر برد مستقل ثبت شود. برآورد MAC4 یا زمان کامپیوتر جای شمارنده cycle CPU نیست. سرعت Renode بدون مدل latency معتبر مدرک سرعت FPGA نیست.

## ۸. سازماندهی و تحویل
source_original.zip آرشیو اصلی را بدون تغییر نگه می‌دارد. docs قرارداد و گزارش را دارد؛ model خروجی canonical تولیدشده؛ software baseline؛ tools ابزار بازتولید/بازرسی؛ verification شواهد تست. rtl فعلاً فقط وضعیت عدم پیاده‌سازی دارد. results برای لاگ runهای واقعی است.

هنگام تکمیل، تحویل شامل RTL و interface، CPU/CFU software، مدل و hashes، golden، testbench و pass logs، دستورات و نسخه ابزار، constraints/config هر برد، utilization/timing reports، cycle CSV و README اجرای دقیق خواهد بود. buildها و checkpoints هر برد در زیرپوشه جدا باشند. برای ادامه چت PROJECT_STATE.md به‌همراه آخرین لاگ کافی است؛ این فایل باید پس از هر مرحله به‌روز شود.

## منابع رابط و برد
- https://cfu-playground.readthedocs.io/en/latest/overview.html
- https://cfu-playground.readthedocs.io/en/latest/interface.html
- https://github.com/google/CFU-Playground/blob/main/docs/source/step-by-step.rst
- https://digilent.com/reference/_media/reference/programmable-logic/nexys-video/nexys-video_rm.pdf
- https://digilent.com/reference/_media/reference/programmable-logic/nexys-a7/nexys-a7_rm.pdf

مرجع قطعی integration، checkout نصب‌شده کاربر است و هنوز از این محیط قابل مشاهده نیست.
