<?php
$node_content = node_load(1480);
$url = substr($node_content->field_image['und'][0]['uri'] , 8);
$url = "https://civil808.com/sites/default/files" . $url;
?>
    <img src="<?php print $url;?>" width="100%" height="auto" style="box-shadow: rgba(0, 0, 0, 0.15) 0px 1px 6px, rgba(0, 0, 0, 0.157) 0px 1px 5px;" alt="<?php print $node_content->title;?>" title="دوره های آنلاین <?php print $node_content->title;?>">


<section id="profile-features" class="panel" style="padding-bottom:139px;!important;">
    <h2>مزایای ارتقاء پروفایل به عضویت Vip</h2>
    <p style="text-align: center;	margin-top: 30px;	font-size: 15px;color: #888; margin-bottom: 35px;">
        برای مشاهده توضیحات بیشتر
        <a href="/node/20945" target="_blank">کلیک کنید</a>
    </p>
    <div class="features">
        <div style="position: relative">
            <span class="hexa">
                <span style="letter-spacing: initial;font-size: 50px;height: 40px;display: inline-block;vertical-align: top;line-height: 45px;z-index: 1;position: relative;">10</span>
                <span style="font-size: 20px;vertical-align: top;line-height: 20px;z-index: 1;position: relative;  letter-spacing: 0;">%</span>
            </span>
            <h3 style="margin-top: 118px;">۱۰٪ تخفیف دائمی دوره ها و محصولات فروشگاه</h3>
            <p>
                خرید کلیه محصولات تولیدی ۸۰۸ شامل ایبوک‌ها، دوره و فیلم‌های آموزشی اختصاصی
            </p>
            <a href="https://civil808.com/college" target="_blank" class="btn">آموزشگاه</a>
            <a href="https://civil808.com/store" target="_blank" class="btn">فروشگاه</a>
        </div>
        <div class="vip">
            <img src="/sites/all/themes/sara/images/vip.svg">
            <h3>استفاده رایگان از بسیاری از محتواها</h3>
            <p>
                امکان استفاده رایگان از تعداد زیادی از محتواهای سایت، شامل
                <a href="/article" target="_blank">مقالات تحلیلی</a>
                ،
                <a href="/publication" target="_blank">ایبوک ها </a>
                ،
                <a href="/article/software" target="_blank">نرم افزارها </a>
                ،
                <a href="/education" target="_blank">کارگاه های آموزشی و فیلم ضبط شده آن </a>
                ،
                <a href="/article/store" target="_blank">فیلم های دوبله شده در CSI </a>
            </p>
        </div>
        <div class="moshaver">
            <img src="/sites/all/themes/sara/images/conversation.svg">
            <h3>مشاوره رایگان با مشاوران اختصاصی</h3>
            <p>امکان مشاهده پروفایل تمامی کاربران سایت و مشاوره نامحدود با اساتید سایت</p>
            <a href="https://civil808.com/landing/advisor" target="_blank" class="btn">لیست تمام مشاوران</a>
        </div>
        <div class="connection">
            <img src="/sites/all/themes/sara/images/net.svg">
            <h3>قابلیت های پروفایل کاربران Vip</h3>
            <p>
                امکان درج و انتشار فعالیت های اعضای VIP، لینک وبسایت شخصی یا حرفه ای و نمایش آیکن Vip در پروفایل کاربر
            </p>
            <a href="/user/59/mojtaba808" target="_blank" class="btn">پروفایل نمونه</a>
        </div>
        <div class="linkedin">
            <img src="/sites/all/themes/sara/images/browser.svg">
            <!--<img src="/sites/all/themes/sara/images/moshaver-like.svg">-->
            <h3> نمایش پروفایل در دانشنامه تخصصی</h3>
            <p>
                در دانشنامه تخصصی عمران و معماری ۸۰۸ لیست جامعی از تخصص های این دو رشته جمع آوری شده است. پروفایل کاربران Vip در پایین تخصصشان به نمایش در می آید.
            </p>
            <a href="https://civil808.com/pedia" target="_blank" class="btn">دانشنامه</a>
        </div>
    </div>
</section>

<h2 style="text-align: center;margin: 118px 0 0 20px;"><?php print $node_content->title;?></h2>
<div class="field field-name-body field-type-text-with-summary field-label-hidden">
    <?php
    print($node_content->body['und'][0]['value']);
    ?>
</div>

<section id="profile-features" class="panel">
    <h2 style="margin-bottom: 50px;">با کلیک بر لینک های زیر کاربری خود را به VIP ارتقاء دهید</h2>
    <div class="ozviyat-div">
        <a class="ozviyat" href="/cart/add/p20657_a73o228?destination=cart">
            <div class="top">عضویت</div>
            <div class="middle">یک ماهه</div>
            <div class="gheymat">۵۰,۰۰۰ تومان</div>
        </a>
        <a class="ozviyat" href="/cart/add/p20657_a73o229?destination=cart">
            <div class="top">عضویت</div>
            <div class="middle">سه ماهه</div>
            <div class="gheymat">۱۲۰,۰۰۰ تومان</div>
        </a>
        <a class="ozviyat bold" href="/cart/add/p20657_a73o230?destination=cart">
            <div class="top">تخفیف ویژه عضویت</div>
            <div class="middle">شش ماهه</div>
            <div class="gheymat">۱۷۰,۰۰۰ تومان</div>
            <div class="gheymat-ghadim">۲۲۰,۰۰۰ تومان</div>
        </a>
        <a class="ozviyat bold" href="/cart/add/p20657_a73o231?destination=cart">
            <div class="top">تخفیف ویژه عضویت</div>
            <div class="middle">یک ساله</div>
            <div class="gheymat">۲۱۰,۰۰۰ تومان</div>
            <div class="gheymat-ghadim">۴۲۰,۰۰۰ تومان</div>
        </a>
    </div>
</section>

<style>
    #profile-features h2{
        position: relative;
    }
    #profile-features h2:before{
        content: "";
        position: absolute;
        width: 130px;
        height: 3px;
        background: #883ab7;
        bottom: -10px;
        right: calc(50% - 65px);
        box-shadow: rgba(136,58,183,0.15) 0px 1px 6px, rgba(136,58,183,0.157) 0px 1px 4px;
    }
    .hexa {
        visibility: visible;
        position: absolute;
        right: calc(50% - 37px);
        top: 29px;
        font-weight: bold;
        /* box-shadow: rgba(0, 0, 0, 0.147059) 0px 6px 35px, rgba(0, 0, 0, 0.119608) 0px 2px 12px; */
        font-family: fanum;
        background: #F44336;
        letter-spacing: -7px;
        width: 70px;
        height: 70px;
        text-align: center;
        color: #fff;
        line-height: 70px;
        padding: 16px 0 0 0;
        box-sizing: border-box;
    }
    .hexa h3{
        line-height: 36px;
    }
    .hexa:after {
        -webkit-transform: rotate(60deg);
        -moz-transform: rotate(60deg);
        -ms-transform: rotate(60deg);
        -o-transform: rotate(60deg);
    }
    .hexa:before {
        -webkit-transform: rotate(30deg);
        -moz-transform: rotate(30deg);
        -ms-transform: rotate(30deg);
        -o-transform: rotate(30deg);
    }
    .hexa:before, .hexa:after {
        content: "";
        position: absolute;
        top: 0;
        left: 0;
        height: 70px;
        width: 70px;
        background: #F44336;
        z-index: 0;
    }
    .contain div.right {
        padding-right: 130px;
    }
    .contain div.left {
        padding-left: 130px;
    }
    .left .hexa:before, .left .hexa:after, .left .hexa {
        background: #FF9800;
    }
    .left .hexa {
        left: 15px;
        right: inherit;
    }
    #profile-features {
        background: #f5f5f5;
        padding: 92px 2vw 50px;
        margin: auto;
        position: relative;
        overflow: visible;
    }
    #profile-features:before {
        content: "";
        background: #f5f5f5;
        position: absolute;
        width: calc(100vw - 2px);
        top: 0;
        right: calc(50% - 50vw - 8px);
        z-index: -1;
        height: 100%;
    }
    #profile-features h2 img {
        width: 200px;
        display: block;
        margin: 0 auto 20px;
        /* box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px; */
    }
    #profile-features .features {
        display: block;
        width: 100%;
        text-align: center;
    }
    .features img {
        width: 100px;
    }
    .features > div:hover {
        box-shadow: rgba(0, 0, 0, 0.156863) 0px 3px 10px, rgba(0, 0, 0, 0.227451) 0px 3px 10px;
    }
    .features > div {
        width: 237px;
        margin: 14px 15px;
        border-radius: 5px;
        padding: 15px;
        transition: all 0.2s;
        background: #fff;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        display: inline-block;
        vertical-align: top;
    }
    #profile-features h2 {
        font-weight: normal !important;
        text-align: center;
        display: block;
    }
    .profile-vip {
        margin: 50px auto 0;
        max-width: 800px;
        display: flex;
        justify-content: center;
        align-items: center;
        border-top: 1px solid #f00;
        padding-top: 40px;
    }
    .profile-vip p {
        font-weight: bold;
        font-size: 20px;
        margin: 0 20px 0 60px;
    }
    .ozviyat-div{
        padding: 30px 0 100px;
        text-align: center;
    }
    a.ozviyat {
        background-color: white;
        box-shadow: rgba(0,0,0,0.227451) 0 3px 10px, rgba(0,0,0,0.227451) 0 3px 10px;
        width: 240px;
        height: 181px;
        padding: 1.5% 1% 1% 1%;
        text-align: center;
        display: inline-block;
        margin: 28px 2vw;
        vertical-align: top;
    }
    a.bold.ozviyat {
        border: 1px solid #f44336;
        box-shadow: rgba(253, 0, 0, 0.227451) 0 3px 10px, rgba(255, 0, 0, 0.227451) 0 3px 10px;
        width: 300px;
        height: 200px;
    }
    .gheymat-ghadim {
        text-decoration: line-through;
        color: #555;
    }
    .top {
        color: black;
    }
    .middle {
        font-size: 45px;
        padding: 5px 0 1px 0;
    }
    .gheymat {
        color: #31cc17;
        font-size: 20px;
    }

</style>
