<img src="/sites/default/files/field/image/node_20190.jpg" width="100%" height="auto" style="	box-shadow: rgba(0, 0, 0, 0.15) 0px 1px 6px, rgba(0, 0, 0, 0.157) 0px 1px 5px;">

<section class="kargah-sec">
    <h2>دوره حضوری ورود به حرفه محاسبات، نظارت و اجرا</h2>
    <p style="text-align: center;margin-top: 30px;font-size: 15px;color: #888;">دوره فقط حضوری و بدون ضبط فیلم است.</p>
    <div class="first-row" style="margin-top: 40px;">
        <div>
            <?php
                $body_value = node_load(20190);
                print($body_value->body['und'][0]['value']);
            ?>
        </div>
        <div class="lecturer">
            <img src="/sites/default/files/styles/200x200/public/pictures/picture-1138-1446395095.jpg?itok=5NJ8JRPM" width="150px" height="auto">
            <p style="margin: 10px 0 0 0"><strong> مدرس </strong></p>
            <h3 style="margin:5px"> مهندس مصطفی دوگوهرانی </h3>
            <p> کارشناس ارشد سازه </p>
            <a href="/sites/default/files/field/file/cv/profile_1004.pdf" target="_blank" class="btn btn-primary" download="cv">رزومه</a>
        </div>
    </div>
</section>

<section style="margin: 50px 0 80px 0;">
    <h2> قسمتی از فیلم ورکشاپ آشنایی با آزمون نظام مهندسی عمران </h2>
    <p style="text-align: center;margin-bottom: 40px;margin-top: 30px;	font-size: 15px;color: #888;">برای مشاهده نمونه فیلم های بیشتر
        <a href="/gallery/videos/playlist/2605/15748" target="_blank">کلیک کنید.</a>
    </p>
    <?php
    //sis3_VP8.webm,sis3_x264.mp4
    $video_attrs = array(
        'src' => '/sites/default/files/filed/files/node_15748-herfe-workshop-omran_vp8.webm',
        'width' => '840px',
        'height' => '447px',
        'videoWidth' => '840px',
        'videoHeight' => '447px',
        'controls' => true,
    );
    $video_sett =  array(
        'download_link' => true,
        'download_text' => 'download'
    );
    print theme('mediaelement_video', array('attributes' => $video_attrs, 'settings' => $video_sett));
    //'poster ' => '/sites/default/files/conference-4-film' ,
    ?>
</section>

<section class="second">
    <h2 class="text"> ثبت نام در دوره حضوری ورود به حرفه محاسبات، نظارت و اجرا</h2>
    <p style="text-align: center;margin-top: -18px;font-size: 15px;color: #888;margin-bottom: 29px;">
        با تخفیفات ویژه برای شرکت کنندگان دوره
    </p>
<!--    <div class="takhfifat" style="margin-bottom: 15px;">-->
<!--        <p>-->
<!--            <span>10 %</span>تخفیف برای اعضای VIP، <a href="/landing/vip" target="_blank">عضو ویژه شوید</a>-->
<!--        </p>-->
<!--    </div>-->
<!--    <div class="takhfifat">-->
<!--        <p>و<span>5 %</span> تخفیف به ازای اضافه شدن هر نفر تا سقف 20 درصد</p>-->
<!--    </div>-->
    <div class="tickets">
        <div>
            <a href="/cart/add/p20193?destination=cart" target="_blank">
                <div class="city-name"><span>دوره محاسبات</span></div>
                <div class="inner-text">
                    <p class="text"> مدرس: مصطفی دوگوهرانی </p>
                    <div class="tarikh">شروع دوره 16 آذر 1397</div>
                    <div class="makan"> موسسه آموزشی 808 </div>
                    <div class="zaman"> پنج شنبه ها ساعت 14 تا 20، جمعه ها ساعت 8 تا 18 (جمعا 100 ساعت) </div>
                    <div class="mablagh"> 1,200,000 تومان </div>
                </div>
                <span class="sabtenam"> ثبت نام </span>
            </a>
            <a href="/cart/add/p20194?destination=cart">
                <div class="city-name"><span>دوره نظارت و اجرا</span></div>
                <div class="inner-text">
                    <p class="text"> مدرس: مصطفی دوگوهرانی </p>
                    <div class="tarikh"> شروع دوره 10 آذر ماه 1397 </div>
                    <div class="makan"> موسسه آموزشی 808 </div>
                    <div class="zaman"> شنبه ها، دوشنبه ها و چهارشنبه ها ساعت 16 تا 21 (جمعا 60 ساعت) </div>
                    <div class="mablagh"> 850,000 تومان </div>
                </div>
                <span class="sabtenam"> ثبت نام </span>
            </a>
        </div>
        <div class="bought-tickets">سوال های خود را می توانید از طریق شماره تماس موسسه و سیستم پیغام خصوصی با ما در میان بگذارید.</div>
	</div>

</section>

<section id="ebooks" class="product-node">
    <h2> فیلم های آموزشی مرتبط </h2>
    <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888;">برای سفارش آنلاين پكيج فيلم هاي آموزشي آمادگي آزمون ورود به حرفه محاسبات، نظارت و اجرا
        <a href="/store" target="_blank" class="title"> به این صفحه </a>
        مراجعه کنید</p>
    <div class="owl-carousel">
        <?php
        $nids = array( 5552 , 11160 , 5532 , 5533 , 13647, 8424);
        $view_mode = 'teaser';
        foreach ($nids as $nid){
            $node = node_load($nid);
            print '<div class="row">';
            $myelement = node_view($node , $view_mode);
            print render($myelement); /*this line is causing the problem*/
            print '</div>';
        }
        ?>
    </div>
</section>

<section id="ebooks">
    <h2> در 808 بیشتر بخوانید </h2>
    <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888;">لیستی از مطالب مرتبط، فیلم های آموزشی، محصولات فروشگاه و ...در رابطه  با این همایش را میتوانید
        <a href="/eng" target="_blank" class="title"> در صفحه اختصاصی ورود به حرفه </a>
        مشاهده کنید</p>
    <div class="owl-carousel">
        <div class="row">
            <a href="/shop/main#/?search=%DA%A9%D8%AA%D8%A7%D8%A8%20%D8%B5%D9%88%D8%AA%DB%8C" target="_blank">
                <img src="/sites/default/files/styles/uc_product_full/public/field/image/node_19236_0.jpg?itok=yVKMdJKz" width="300" height="170" alt="سفارش آنلاین مجموعه كتب صوتي مقررات ملي ساختمان" title=" سفارش آنلاین مجموعه كتب صوتي مقررات ملي ساختمان ">
            </a>
            <a href="/shop/main#/?search=%DA%A9%D8%AA%D8%A7%D8%A8%20%D8%B5%D9%88%D8%AA%DB%8C" target="_blank" class="title">
                سفارش آنلاین مجموعه كتب صوتي مقررات ملي ساختمان
            </a>
        </div>
        <div class="row">
            <a href="/node/16827" target="_blank">
                <img src="/sites/default/files/photo_2018-09-15_12-36-40.jpg" width="300" height="170" alt="دوره آنلاین ورود به حرفه محاسبات (ترم تابستان ۹۷)" title=" دوره آنلاین ورود به حرفه محاسبات (ترم تابستان ۹۷) ">
            </a>
            <a href="/node/16827" target="_blank" class="title">
                دوره آنلاین ورود به حرفه محاسبات (ترم تابستان ۹۷)
            </a>
        </div>
        <div class="row">
            <a href="/node/16828" target="_blank">
                <img src="/sites/default/files/photo_2018-09-15_12-46-05.jpg" width="300" height="170" alt="دوره آنلاین ورود به حرفه نظارت (ترم تابستان ۹۷)" title="دوره آنلاین ورود به حرفه نظارت (ترم تابستان ۹۷)">
            </a>
            <a href="/node/16828" target="_blank" class="title">
                دوره آنلاین ورود به حرفه نظارت (ترم تابستان ۹۷)
            </a>
        </div>
        <div class="row">
            <a href="/node/1107" target="_blank">
                <img src="/sites/default/files/styles/808/public/field/image/node_1107.jpg?itok=df31Wt33" width="300" height="170" alt="برنامه های عمرانی ماشین حساب ویژه آزمون ورود به حرفه محاسبات" title="برنامه های عمرانی ماشین حساب ویژه آزمون ورود به حرفه محاسبات">
            </a>
            <a href="/node/1107" target="_blank" class="title">
                برنامه های عمرانی ماشین حساب ویژه آزمون ورود به حرفه محاسبات همراه با 2 ساعت فیلم آموزشی (به روز رسانی اسفند 96)
            </a>
        </div>
        <div class="row">
            <a href="/gallery/videos/playlist/2605/15748" target="_blank">
                <img src="/sites/default/files/field/image/node_15748-photo5976604562305427827.jpg" width="300" height="170" alt="فیلم آشنایی با خدمات سازمان نظام مهندسی رشته عمران" title="فیلم آشنایی با خدمات سازمان نظام مهندسی رشته عمران">
            </a>
            <a href="/gallery/videos/playlist/2605/15748" target="_blank" class="title">
                فیلم آشنایی با خدمات سازمان نظام مهندسی رشته عمران
            </a>
        </div>
        <div class="row">
            <a href="/gallery/videos/playlist/3685/19009" target="_blank">
                <img src="/sites/default/files/field/image/node_19009-azmoon-nezam-mohandesi-97.jpg" width="300" height="170" alt="حل سوال 60 تحلیل سازه آزمون ورود به حرفه محاسبات ارديبهشت ٩٧ توسط ماشین حساب" title="حل سوال 60 تحلیل سازه آزمون ورود به حرفه محاسبات ارديبهشت ٩٧ توسط ماشین حساب">
            </a>
            <a href="/gallery/videos/playlist/3685/19009" target="_blank" class="title">
                حل سوال 60 تحلیل سازه آزمون ورود به حرفه محاسبات ارديبهشت ٩٧ توسط ماشین حساب
            </a>
        </div>
        <div class="row">
            <a href="/node/9799" target="_blank">
                <img src="/sites/default/files/field/image/node_2704-blog_71.jpg" width="300" height="170" alt="دوره های آنلاین آمادگی آزمون ورود به حرفه عمران و معماری" title="دوره های آنلاین آمادگی آزمون ورود به حرفه عمران و معماری">
            </a>
            <a href="/node/9799" target="_blank" class="title">
                دوره های آنلاین آمادگی آزمون ورود به حرفه عمران و معماری
            </a>
        </div>
        <div class="row">
            <a href="/node/17146" target="_blank">
                <img src="/sites/default/files/photo5877664063587199527_1.jpg" width="300" height="170" alt="فیلم وبينار مشاوره نحوه شركت در آزمون های بين المللی FE/PE" title="فیلم وبينار مشاوره نحوه شركت در آزمون های بين المللی FE/PE">
            </a>
            <a href="/node/17146" target="_blank" class="title">
                فیلم وبينار مشاوره نحوه شركت در آزمون های بين المللی FE/PE
            </a>
        </div>
        <div class="row">
            <a href="/node/17075" target="_blank">
                <img src="/sites/default/files/styles/808/public/field/image/node_17075.jpg?itok=q4SNihYD" width="300" height="170" alt="ایبوک ۱۷۵: جداول افزایش سرعت تست های آزمون محاسبات نظام مهندسی" title="ایبوک ۱۷۵: جداول افزایش سرعت تست های آزمون محاسبات نظام مهندسی">
            </a>
            <a href="/node/17075" target="_blank" class="title">
                ایبوک ۱۷۵: جداول افزایش سرعت تست های آزمون محاسبات نظام مهندسی
            </a>
        </div>
        <div class="row">
            <a href="/node/3845" target="_blank">
                <img src="/sites/default/files/styles/808/public/field/image/node_3845.jpg?itok=U-I2htwX" width="300" height="170" alt="کلید واژه های تخصصی آزمون ورود به حرفه اردیبهشت 97 منتشر شد (همه گرایش ها)" title="کلید واژه های تخصصی آزمون ورود به حرفه اردیبهشت 97 منتشر شد (همه گرایش ها)">
            </a>
            <a href="/node/3845" target="_blank" class="title">
                کلید واژه های تخصصی آزمون ورود به حرفه اردیبهشت 97 منتشر شد (همه گرایش ها)
            </a>
        </div>
        <div class="row">
            <a href="/node/16090" target="_blank">
                <img src="/sites/default/files/styles/808/public/field/image/node_16090.jpg?itok=5QCu3fcI" width="300" height="170" alt="نمونه سوالات مباحث ۲۲ گانه مقررات ملی ساختمان ویژه آزمون نظام مهندسی" title="نمونه سوالات مباحث ۲۲ گانه مقررات ملی ساختمان ویژه آزمون نظام مهندسی">
            </a>
            <a href="/node/16090" target="_blank" class="title">
                نمونه سوالات مباحث ۲۲ گانه مقررات ملی ساختمان ویژه آزمون نظام مهندسی
            </a>
        </div>
        <div class="row">
            <a href="/node/3968" target="_blank">
                <img src="/sites/default/files/styles/808/public/field/image/node_3979-photo375916600721781737.jpg?itok=QwsG8Heh" width="300" height="170" alt="معرفی پکیج استثنایی شابلن کوییک (مختص آزمون ورود به حرفه معماری)" title="معرفی پکیج استثنایی شابلن کوییک (مختص آزمون ورود به حرفه معماری)">
            </a>
            <a href="/node/3968" target="_blank" class="title">
                معرفی پکیج استثنایی شابلن کوییک (مختص آزمون ورود به حرفه معماری)
            </a>
        </div>
        <div class="row">
            <a href="/node/17089" target="_blank">
                <img src="/sites/default/files/styles/200x200/public/fe-exam.jpg?itok=4C4U40Ru" width="300" height="170" alt="آزمون FE یا Fundamentals of Engineering" title="آزمون FE یا Fundamentals of Engineering">
            </a>
            <a href="/node/17089" target="_blank" class="title">
                آزمون FE یا Fundamentals of Engineering
            </a>
        </div>
        <div class="row">
            <a href="/node/17090" target="_blank">
                <img src="/sites/default/files/styles/200x200/public/pe-exam.jpg?itok=rK3SwDau" width="300" height="170" alt="آزمون حرفه ای مهندسی (PE) یا Profasional Engineering Exam" title="آزمون حرفه ای مهندسی (PE) یا Profasional Engineering Exam">
            </a>
            <a href="/node/17090" target="_blank" class="title">
                آزمون حرفه ای مهندسی (PE) یا Profasional Engineering Exam
            </a>
        </div>
        <div class="row">
            <a href="/node/17077" target="_blank">
                <img src="/sites/default/files/styles/200x200/public/engineering-system-test.jpg?itok=CNPf4UzR" width="300" height="170" alt="آزمون نظام مهندسی، Engineering system test" title="آزمون نظام مهندسی، Engineering system test">
            </a>
            <a href="/node/17077" target="_blank" class="title">
                آزمون نظام مهندسی، Engineering system test
            </a>
        </div>
    </div>
</section>

<section class="plus808">
    <div class="inner">
        <h2>  ثبت نام در کلاس ها و مشاوره های خصوصی </h2>
        <h4> اگر دوره مورد نظر خود را پیدا نکردید، با مدرس دلخواه خود آموزش ببینید </h4>
        <a class="ask-question btn btn-primary" href="/college/course-vip" target="_blank"> درخواست کلاس </a>
        <a class="ask-question btn" href="/question/list" target="_blank">پرسش و پاسخ</a>
    </div>
</section>

<section class="third">
    <h2> آموزش های آمادگی ورود به حرفه </h2>
    <div class="inside">
        <a href="/eng" target="_blank">
            <span class="icon"></span>
            <div class="esm">صفحه اختصاصی ورود به حرفه</div>
        </a>
        <a href="/college/herfe" target="_blank">
            <span class="icon"></span>
            <div class="esm">دوره های آنلاین ورود به حرفه</div>
        </a>
        <a href="/landing/exam" target="_blank">
            <span class="icon"></span>
            <div class="esm">آزمون های آزمایشی</div>
        </a>
        <a href="/shop/main#/?exam=2250" target="_blank">
            <span class="icon"></span>
            <div class="esm">فروشگاه محصولات مرتبط</div>
        </a>
        <a target="_blank" href="/taxonomy/term/2212">
            <span class="icon"></span>
            <div class="esm">گالری فیلم های آموزشی</div>
        </a>
    </div>
</section>

<!--<section class="fifth">
    <div class="mojri">
        <h2> برگزارکننده </h2>
        <img src="/sites/all/themes/sara/images/808-logo.png" width="200px" height="auto">
        <h3> موسسه آموزشی مهندسی 808 </h3><a href="http://seismosoft.com/contacts" target="_blank"> نماینده رسمی شرکت SeismoSoft در ایران </a>
    </div>
</section>-->


<style>
    .product-node .owl-stage-outer {
        margin-bottom: 45px;
    }
    .node-teaser .vip-price .title {
        display: none !important;
    }
    .product-node .owl-item .row {
        box-shadow: none;
    }
    .owl-item .row {
        margin: 15px;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        background: #fff;
    }
    .node-product.node-teaser, .node-product-kit.node-teaser {
        width: 100%;
    }
    #more-data{
        margin: 86px 20px;
    }
    #more-data li{
        line-height:29px;
    }
    .mediaelement-download-link a{
        font-size:0px;
    }
    .mediaelement-download-link a:after{
        font-size: 13px;
    }
    .seis-box{
        position: relative;
        display: flex;
        justify-content: center;
        align-items: center;
    }
    .seis-text > div > div {
        font-size: 15px;
        font-weight: bold;
        color: #9C27B0;
        float: right;
        clear: right;
        margin: 0 0 0 14px;
    }
    .seis-text > div > span {
        font-weight: bold;
        font-size: 17px;
        font-family: Tahoma;
        display: block;
        padding: 1px 0;
    }
    .seis-text{
        max-width: 615px;
        padding: 2% 2%;
        background: #fff;
        border-radius: 5px;
        box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
        color: #555 !important;
        min-height: 150px;
        margin: 33px 10px;
        position: relative;
        text-align: justify;
        z-index: 2;
    }
    .seis-text p{
        font-size: 14px;
        line-height: 32px;
    }
    section:not('.plus808') h2{
        position: relative;
    }
    section:not('.plus808') h2:before{
        content: "";
        position: absolute;
        width: 130px;
        height: 3px;
        background: #883ab7;
        bottom: -10px;
        right: calc(50% - 65px);
        box-shadow: rgba(136,58,183,0.15) 0px 1px 6px, rgba(136,58,183,0.157) 0px 1px 4px;
    }
    #pbd-panel{
        width: 90%;
        margin: 50px auto 130px auto;
    }
    h2{
        text-align: center;
    }
    #pbd-panel > div{
        margin-top: 65px !important;
    }
    .page-node-19072 #pbd-panel .node-product.node-teaser{
        margin:1% 10px !important;
    }
    .views_slideshow_main .views-slideshow-cycle-main-frame,
    .views_slideshow_main .views_slideshow_slide {
        width: 100% !important;
    }
    a.v-en {
        position: fixed;
        bottom: -195px;
        left: -131px;
        z-index: 100;
        background-color: #673ab77a;
        width: 300px;
        height: 300px;
        border-radius: 50%;
        transition: width 0.8s,height 0.8s;
        font-size: 16px;
        padding: 40px 61px 0 0;
        color: #000 !important;
    }
    a.v-en:hover {
        width: 303px;
        height: 303px;
    }
    a.v-en b {
        display: block;
        padding-right: 25px;
        /*color: #E65100;*/
    }
    section.timing{
        position: relative;
    }
    section.timing .timing-wh{
        display: flex !important;
        align-items: start;
        justify-content: space-evenly;
        padding: 30px 0 110px 0;
        margin: 50px 0 0 0;
    }
    section.timing h2{
        text-align:center;
    }
    section.timing .description{
        text-align: center;
        background: #fff;
        box-shadow: rgba(0, 0, 0, 0.15) 0px 1px 6px, rgba(0, 0, 0, 0.157) 0px 1px 4px;
        max-width: 300px;
        margin: 0 5px;
    }
    .des-top {
        display: flex;
        align-items: center;
        justify-content: flex-start;
        padding: 15px;
        border-bottom: 1px solid #eee;
    }
    .des-top img {
        width: 70px;
        height: 70px;
        border-radius: 50%;
        border: 2px solid #fff;
        box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
        /* overflow: hidden; */
    }
    .des-left {
        text-align: right;
        margin: 0 15px 0 0;
    }
    .des-left div {
        margin-top: 5px;
        font-size: 12px;
    }
    .des-down {
        padding: 15px;
    }
    .time1 .des-down a{
        display: block;
        margin: 6px 0 -1px 0;
        color: #0076bd !important;
    }
    .time1 .des-down a:before {
        content: '\f225';
        font-family: mat;
        font-size: 18px;
        vertical-align: middle;
    }
    .timebox {
        text-align: center;
        z-index: 2;
    }
    .moddat {
        font-family: fanum;
        margin-bottom: 7px;
        font-size: 15px;
        font-weight: bold;
    }
    .circle {
        width: 40px;
        height: 40px;
        background-color: #eee;
        border-radius: 50%;
        margin: auto;
        border: 2px solid #873ab6;
        padding: 3px;
    }
    .circle:before {
        width: 100%;
        height: 100%;
        content: ' ';
        background-color: #ffffff;
        display: block;
        border-radius: 50%;
    }
    .line {
        width: 2px;
        height: 40px;
        background-color: #883ab75c;
        margin: auto;
    }
    .timing-wh:before {
        content: " ";
        position: absolute;
        top: 171px;
        width: 72%;
        height: 2px;
        background-color: #d1b5e2;
    }
    @media (max-width: 992px) and (min-width: 769px){
        .des-left {
            text-align: center;
        }
        .des-top{
            display:block;
        }
    }
    @media (max-width:768px){
        .seis-box img{
            display: none;
        }
        section.timing .timing-wh {
            align-items: center;
            justify-content: center;
            padding: 30px 0 110px 0;
            margin: 50px 0 0 0;
            flex-direction: column;
        }
        .timebox {
            text-align: center;
            z-index: 2;
            display: flex;
            align-items: center;
            position: relative;
        }
        .circle{
            position:relative;
            width: 30px;
            height: 30px;
        }
        .circle:after {
            content: " ";
            position: absolute;
            width: 2px;
            height: 127px;
            background-color: #d1b5e2;
            top: 28px;
        }
        .timebox.time3 .circle:after {
            height: 112px;
        }
        .timebox.time2 .circle:after {
            height: 102px;
        }
        .timebox.time4 .circle:after {
            display:none;
        }
        .moddat {
            font-size: 14px;
            width: 71px;
            position: absolute;
            margin-top: -34px;
            right: -21px;
        }
        .line {
            height: 2px;
            width: 40px;
            margin: auto;
        }
        section.timing .description {
            margin: 5px 0;
        }
        .timing-wh:before {
            display: none;
        }
    }
    @media (max-width:440px){
        section.timing .description{
            max-width: 240px;
        }
        .bought-tickets a:before{
            display:none !important;
        }
        .circle {
            width: 30px;
            height: 30px;
        }
        .timebox.time1 .circle:after {
            height: 212px;
        }
        .timebox.time2 .circle:after {
            height: 188px;
        }
        .timebox.time3 .circle:after {
            height: 177px;
        }
        .des-left {
            text-align: center;
        }
        .des-top{
            display:block;
        }
        .line {
            height: 2px;
            width: 30px;
        }
        .moddat {
            font-size: 12px;
        }
        .bought-tickets {
            margin: 66px 2px 80px !important;
        }
        .bought-tickets a {
            padding: 20px 5px !important;
            font-size: 13px !important;
        }
    }

    .aks3{
        margin: 57px auto;
        text-align: center;
    }
    .aks3 a{
        display: inline-block;
        margin: 10px 17px;
    }
    #block-system-main section:not(.plus808) h2{
        position: relative;
    }
    #block-system-main section:not(.plus808) h2:before{
        content: "";
        position: absolute;
        width: 130px;
        height: 3px;
        background: #883ab7;
        bottom: -10px;
        right: calc(50% - 65px);
        box-shadow: rgba(136,58,183,0.15) 0px 1px 6px, rgba(136,58,183,0.157) 0px 1px 4px;
    }
    .fifth h2 {
        margin: 10px auto 80px;
        font-size: 25px;
        display: block;
    }
    section.second h2 {
        text-align: center;
        margin: 30px auto 50px;
        background: #f9f9f9;
        width: 670px;
        max-width: 96%;
        z-index: 2;
    }
    .hamin h2 {
        margin-top: 95px;
        margin-bottom: 35px;
    }
    section.third h2 {
        text-align: center;
        margin-bottom: 60px;
    }
    #ebooks h2 {
        text-align: center;
    }

    section.kargah-sec {
        padding: 80px 5% 30px 5%;
    }
    #block-system-main .content {
        background-color: #f9f9f9;
    }
    section.first {
        box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
        position: relative;
        background: #fff;
        overflow: hidden;
    }
    section.first div#seismosoft {
        max-width: 1200px;
        margin: 0 auto !important;
        padding: 50px 15px;
        box-shadow: none;
        position: initial;
    }
    .namayandegi img {
        width: 100%;
    }
    .namayandegi .pane-content > p {
        float: left;
        text-align: center;
        width: calc(40% - 50px);
        min-width: 170px;
        margin-right: 30px;
    }
    .kargah-sec .first-row {
        display: flex;
        justify-content: space-around;
        align-items: flex-start;
    }
    .lecturer {
        text-align: center;
        background: #fff;
        box-shadow: rgba(0, 0, 0, 0.15) 0px 1px 6px, rgba(0, 0, 0, 0.157) 0px 1px 4px;
        width: 300px;
        padding: 24px 15px 15px;
    }
    .lecturer > img{
        border-radius: 50%;
        border: 2px solid #fff;
        box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
    }
    .kargah-sec .first-row > div:first-child p {
        font-size: 14px;
        line-height: 28px;
    }
    .kargah-sec .first-row > div:first-child li {
        line-height: 25px;
    }
    .kargah-sec .first-row > div:first-child {
        width: 640px;
        margin-left: 50px;
    }
    .important{
        padding: 0px 13px;
        border: 1px solid #FF5722;
        /* margin: 20px 30px 30px 30px; */
        border-width: 0 2px 0 0px;
        /* background-color: #ffffff; */
        font-size: 13px !important;
        /* line-height: 27px; */
        max-width: 700px;
    }
    .ghabl.mablagh {
        color: #F44336;
        font-size: 15px;
        margin: 15px 15px -10px;
        text-decoration: line-through;
        text-shadow: none;
    }
    section.fifth {
        text-align: center;
        padding: 55px 0;

    }
    .mojri h3 {
        font-size: 21px;
    }
    .mojri img{
        display: block;
        margin: auto;
    }
    .mojri a {
        color: #717171 !important;
        font-size: 13px;
    }
    #node-17760 > .content {
        padding: 0 !important;
    }
    section.second {
        background: #f9f9f9;
        max-width: 1300px;
        margin: 50px auto;
    }
    .tickets > div {
        display: flex;
        justify-content: space-evenly;
    }
    .tickets a{
        display: inline-flex;
        width: 500px;
        padding: 15px;
        background: #fff;
        border-radius: 5px;
        box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
        color: #555 !important;
        min-height: 150px;
        align-items: stretch;
        margin: 10px 15px;
        position: relative;
        z-index: 10;
        text-shadow: 0 0 10px #fff, 0 0 10px #fff, 0 0 10px #fff, 0 0 10px #fff, 0 0 10px #fff, 0 0 10px #fff, 0 0 10px #fff;
        flex-direction: column;
    }
    .tickets a div.city-name {
        display: flex;
        justify-content: center;
        align-items: center;
        border-radius: 50%;
        /* border: 2px solid #2196F3; */
        color: #9C27B0;
        font-weight: 500;
        font-size: 18px;
        padding: 6px 15px 0px 15px;
        position: relative;
        box-sizing: content-box;
        line-height: 38px;
    }
    .tickets a div.city-name:after {
        content: "";
        position: absolute;
        left: 4%;
        bottom: -16px;
        height: 1px;
        border-bottom: 4px dotted #aaa;
        width: 83%;
        right: 4%;
    }
    .tickets a .inner-text{
        margin: 30px 20px 0 40px;
    }
    p.text {
        font-size: 15px;
        padding: 3px 13px;
        margin-bottom: 0;
        font-weight: 500;
    }
    .tarikh,
    .mablagh,
    .makan,
    .zaman {
        font-family: fanum;
        margin: 10px 7px;
    }
    .tarikh:before,
    .mablagh:before,
    .zaman:before,
    .makan:before {
        content: "\f0ed";
        font-family: mat;
        float: right;
        margin-left: 6px;
        font-size: 20px;
        color: #9C27B0;
    }
    .mablagh:before{
        content:"\f116";
        display:none;
    }
    .mablagh {
        font-size: 25px;
        color: #4CAF50;
        margin-right: 10px;
    }
    .zaman:before{
        content:"\f51b";
    }
    .makan:before{
        content:"\f34e";
    }
    span.sabtenam {
        position: absolute;
        top: calc( 50% - 15px );
        transform: rotate(-90deg);
        left: 12px;
        font-size: 18px;
        color: #9E9E9E;
    }
    span.sabtenam:after {
        content: "\f141";
        transform: rotate(90deg);
        display: inline-block;
        position: absolute;
        right: 7px;
        top: -31px;
        font-family: mat;
        font-size: 41px;
    }
    .tickets a > div img{
        position: absolute;
        bottom: 0;
        left: 51px;
        z-index: -1;
    }
    section.third {
        padding: 70px 50px 50px;
        z-index: 3;
        text-align: center;
    }
    section.third .inside{
        max-width: 1200px;
        margin: auto;
    }
    section.third a {
        display: inline-block;
        width: 200px;
        background-color: #fff;
        border-radius: 50%;
        height: 200px;
        margin: 20px 1%;
        box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
        vertical-align: top;
    }
    section.third a .esm {
        margin: 14px 10px 17px 10px;
        font-size: 13px;
        text-align: center;
        color: black;
        line-height: 26px;
    }
    section.third a .icon {
        width: 50px;
        height: 50px;
        background-color: #f2f2f2;
        text-align: center;
        margin: auto;
        border-radius: 50%;
        line-height: 50px;
        margin-bottom: 12px;
    }
    section.third a .icon:before {
        margin: 44px 0 20px 0;
        display: block;
        color: #9c27b0;
        content: "\f428";
        font-family: mat;
        font-size: 62px;
    }
    section.third a:nth-child(2) .icon:before {
        content: "\f517";
    }
    section.third a:nth-child(3) .icon:before {
        content: "\f3ed";
    }
    section.third a:nth-child(4) .icon:before {
        content: "\f111";
    }
    section.third a:nth-child(5) .icon:before {
        content: "\f22f";
    }
    .logos{
        text-align: center;
    }
    .logos > div {
        width: 200px;
        display: inline-block;
        vertical-align: middle;
        margin: 30px 3%;
    }
    @media (min-width:1100px){
        .logos > div {
            margin: 22px 7%;
        }
    }

    .owl-theme .owl-dots,.owl-theme .owl-nav{text-align:center;-webkit-tap-highlight-color:transparent}.owl-theme .owl-nav{margin-top:10px}.owl-theme .owl-nav [class*=owl-]    {color:#FFF;font-size:14px;margin:5px;padding:4px 7px;background:#D6D6D6;display:inline-block;cursor:pointer;border-radius:3px}.owl-theme .owl-nav [class*=owl-]:hover  {background:#869791;color:#FFF;text-decoration:none}.owl-theme .owl-nav .disabled{opacity:.5;cursor:default}.owl-theme .owl-nav.disabled+.owl-dots{margin-top:10px}   .owl-theme .owl-dots .owl-dot{display:inline-block;zoom:1}.owl-theme .owl-dots .owl-dot span{width:10px;height:10px;margin:5px 7px;background:#D6D6D6;display:block;   -webkit-backface-visibility:visible;transition:opacity .2s ease;border-radius:30px}.owl-theme .owl-dots .owl-dot.active span,.owl-theme .owl-dots .owl-dot:hover span  {background:#869791}

    .owl-item .item {
        background: #2196F3;
        padding: 15px;
    }
    .owl-item .item {
        background: #abc;
        padding: 15px;
    }
    .owl-item .row {
        margin: 15px;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        background: #fff;
    }
    .owl-item .row .title {
        font-size: 13px;
        padding: 10px;
        display: inline-block;
        color: #333 !important;
        font-weight: 500;
        line-height: 30px;
    }
    .owl-carousel {
        padding: 50px 5%;
        width: 90% !important;
        margin: auto;
    }
    .owl-carousel .owl-item img {
        height: auto;
        margin: auto;
    }
    .owl-dot span:before {
        content: "";
        background: #aaa;
        display: inline-block;
        width: 15px;
        height: 15px;
        border-radius: 50%;
    }
    .owl-dot.active span:before {
        background: #333;
    }
    .owl-dots {
        display: flex;
        justify-content: center;
    }
    .owl-dot {
        padding: 0 10px;
        margin: 0 5px;
    }
    .owl-nav {
        display: flex;
        justify-content: center;
        display: none !important;
    }
    .owl-nav div {
        background: #eee;
        margin: 10px 20px 20px;
        padding: 5px 25px;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        font-size: 15px;
        color: #555;
    }
    .product-node {
        border-top: none;
        position: relative;
        padding: 80px 50px 70px;
        background: #fff;
        box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
    }
    #ebooks:not(.product-node) {
        position: relative;
        padding: 80px 50px 70px;
    }
    .mediaelement-download-link{
        display: block !important;
    }
    .mediaelement-download-link a:after {
        content: 'دانلود';
        vertical-align: middle;
        padding-bottom: 5px;
        display: inline-block;
    }
    .takhfifat {
        display: flex;
        flex-direction: column;
        text-align: center;
        align-items: center;
        justify-content: center;
        margin: -10px 0 30px 0;
    }

    .takhfifat p {
        background: #fff;
        border-radius: 50px;
        margin: 5px 15px;
        padding: 15px;
        box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
        font-family: fanum;
    }

    .takhfifat p:before {
        content: "\f415";
        font-family: mat;
        font-size: 30px;
        vertical-align: middle;
        margin: -10px -10px -10px 15px;
        border: 1px solid #aaa;
        border-radius: 50%;
        width: 40px;
        display: inline-flex;
        height: 40px;
        color: #F44336;
        align-items: center;
        justify-content: center;
    }

    .takhfifat p span {
        font-size: 15px;
        margin: 0 5px;
        color: #F44336;
        border: 1px solid;
        padding: 0 10px;
        border-radius: 30px;
        background: #ffffff;
    }
    .bought-tickets {
        margin: 82px 20px 80px;
        text-align: center;
        font-size: 15px;
        color: #888;
    }

    .bought-tickets a {
        padding: 20px 40px;
        border-radius: 30px;
        background: #fff;
        color: #555 !important;
        box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
        font-size: 15px;
    }

    .bought-tickets a:before {
        content: "\f518";
        font-family: mat;
        font-size: 30px;
        vertical-align: middle;
        margin: -10px -35px -10px 15px;
        border: 1px solid #aaa;
        border-radius: 50%;
        width: 56px;
        display: inline-flex;
        height: 56px;
        color: #F44336;
        align-items: center;
        justify-content: center;
    }
    .bought-tickets div {
        margin: 0 0 40px 0;
        font-size: 15px;
        color: #888;
    }
    .bought-tickets a.muted {
        opacity: 0.7;
    }
    @media (max-width: 768px) {
        .owl-carousel .owl-dots {
            overflow: hidden;
        }
    }
    @media (max-width: 850px){
        .tickets > div {
            flex-direction: column;
        }
        .tickets a {
            display: flex;
            width: auto !important;
        }
    }
    @media (max-width: 600px){
        .namayandegi .pane-content div {
            width: calc(100% - 40px);
        }
        .kargah-sec .first-row {
            flex-direction: column-reverse;
            align-items: center;
        }
        section.kargah-sec {
            padding: 50px 15px 30px;
        }
        .kargah-sec .first-row > div:first-child {
            width: 100%;
            margin: 30px 0 0;
        }
    }
    @media (max-width: 400px){
        .tickets a div.city-name {
            font-size: 17px;
            padding: 3px 8px;
        }
        .tickets a .inner-text {
            margin: 27px 0px 0 40px;
        }
        .takhfifat p {
            margin: 5px 9px;
            padding: 8px;
            font-size: 11px;
        }
        .takhfifat p:before {
            margin: -8px -4px -8px 0px;
            width: 32px;
            height: 32px;
        }
    }

    .link-hamayesh{
        width: 70%;
        background-color: #ffffff;
        padding: 20px;
        margin: 0px auto 50px auto;
        border: solid #b39dd9;
        border-width: 0px 3px;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
    }

    .link-hamayesh a{
        color: #909090 !important;
        font-size: 16px;
    }
    .link-hamayesh a:hover{
        color: #c0c0c0 !important;
    }

    @media (max-width: 768px) {
        .link-hamayesh{
            width: 90%;
        }
    }
    @media (max-width: 480px) {
        .link-hamayesh a{
            font-size: 13px;
        }
    }

    /*--------------------aplication-section--------------------*/
    #pbd .wh{
        width: calc(100% - 30px);
        max-width: 1100px;
        margin: auto;
        text-align: center;
        padding: 80px 15px;
        z-index: 1;
        position: relative;
    }
    #pbd h2{
        font-size: 24px;
        text-align: center;
        position: relative;
        font-weight:500px;
        line-height: 40px;
    }
    #pbd h2:before {
        content: "";
        position: absolute;
        width: 130px;
        height: 3px;
        background: #883ab7;
        bottom: -10px;
        right: calc(50% - 65px);
        box-shadow: rgba(136,58,183,0.15) 0px 1px 6px, rgba(136,58,183,0.157) 0px 1px 4px;
    }
    #pbd{
        background-color: #f5f5f5;
    }
    #pbd img{
        position: absolute;
        left: -60px;
        bottom: 82px;
        width: 446px;
    }
    #pbd .sec-li > div{
        background-color: rgba(255, 255, 255, 0.85);
        box-shadow: rgba(0, 0, 0, 0.156863) 0px 1px 6px, rgba(0, 0, 0, 0.227451) 0px 1px 6px;
        max-width: 1067px;
        width: 100%;
        margin: auto;
        box-sizing: border-box;
        padding: 23px 3.5% 36px 37%;
        text-align: right;
    }
    #pbd .sec-li > div li,
    #pbd .sec-li > div div{
        text-align:justify;
    }
    #pbd .sec-li > div div{
        margin-right: 16px;
        margin-bottom: -9px;
    }
    #pbd .sec-li > div{
        padding: 23px 0.5% 36px 37%;
        font-family: fanum;
        text-align: center;
        font-size: 14.3px;
        line-height: 30px;
    }
    #pbd .sec-li > div p,
    #pbd .sec-li > div li,
    #pbd .sec-li > div ol{
        font-size: 14.3px;
        line-height: 30px;
    }
    #pbd .sec-li > div ol{
        -webkit-margin-after: 14.3px;
        -webkit-margin-before: 14.3px;
        -webkit-margin-end: 0px;
        -webkit-margin-start: 0px;
        -webkit-padding-start: 40px;
        list-style-type: decimal;
        text-align: center;
    }
    #pbd .sec-li > div > p{
        text-align: justify;
    }
    #pbd .sec-li > div li{
        text-align:right;
    }
    #pbd .aboutus {
        text-align: right;
        font-size: 1.1rem;
        line-height: 30px;
        display: inline-block;
        width: 100%;
        margin-top: 45px;
        margin-bottom: 30px;
        position:relative;
    }
    a.poster {
        border-radius: 2px;
        line-height: 36px;
        text-align: center;
        padding: 0 10px 0 16px;
        display: inline-block;
        font-size: 14px;
        transition: all 0.2s;
        box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
        outline: none;
        color: #2196f3 !important;
        border: 1px solid #2196f3;
        margin: 11px 8px -10px 8px;
        box-sizing: border-box;
        vertical-align: top;
        width: auto;
    }
    a.poster:before {
        content: '\f1da';
        font-family: mat;
        padding: 0 0 0 5px;
        font-size: 18px;
        display: inline-block;
        vertical-align: bottom;
    }
    a.poster.view:before {
        content: '\f349';
    }

    @media (max-width: 1200px){
        #pbd .sec-li > div{
            padding: 24px 0.5% 36px 46%;
        }
        #pbd img{
            position: absolute;
            left: 3%;
            width: 42%;
            top: 2vw;
        }
    }

    @media (max-width: 992px){
        #pbd img {
            position: absolute;
            width: 285px;
            top: -13px;
            right: calc(50% - 141px);
        }
        #pbd .sec-li > div {
            padding: 37px 2% 37px 5%;
            margin-top: 243px;
        }
    }
    @media (max-width: 500px) {

        #pbd .sec-li > div {
            margin-top: 230px;
            padding: 50px 0% 37px 5%;
        }
        #pbd ol{
            padding-right: 31px;
        }
        #pbd img{
            width: 300px;
            top: -23px;
            right: calc(50% - 150px);
        }
        #pbd .wh {
            padding: 8vh 0 10vh 0;
        }

    }
    #block-system-main > .content:before {
        /*content: "";*/
        position: absolute;
        background-color: #f3e5f585;
        width: 186%;
        top: 509px;
        z-index: 0;
        right: 0;
        height: 1321px;
        transform: skew(-68deg);
    }
</style>


