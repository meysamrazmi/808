

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php print render($title_prefix); ?>
    <?php if (!$page): ?>

    <?php endif; ?>
    <?php print render($title_suffix); ?>

    <div class="content"<?php print $content_attributes; ?>>
        <?php
        print render($content);
        ?>
    </div>

    <section class="second">
        <h2 class="text"> ثبت نام در دوره حضوری گام های اجرایی BIM </h2>
        <!--<p style="text-align: center;margin-top: -18px;font-size: 15px;color:red;margin-bottom: 29px;">
            ظرفیت دوره رو به اتمام است.
        </p>
        <div class="takhfifat" style="margin-bottom: 15px;">
            <p>
                <span>10 %</span>تخفیف برای اعضای VIP، <a href="/landing/vip" target="_blank">عضو ویژه شوید</a>        </p>
        </div>
        <div class="takhfifat">
            <p>و<span>5 %</span> تخفیف به ازای اضافه شدن هر نفر تا سقف 20 درصد</p>
        </div>-->
        <div class="tickets">
            <div>
                <a href="/cart/add/p<?php print $node->nid; ?>?destination=cart" style="width: auto;">
                    <div class="city-name"><span>
                            <?php print $node->title; ?>
                        </span>
                    </div>
                    <div class="inner-text">
                        <p class="text"> مدرس: Omare Muhammad Azam </p>
                        <!--<p style="padding: 9px 12px 0px 0px;"> شامل پذیرایی ناهار در 2 روز اول و پکیج همراه دوره </p>
                        <p class="important" style="margin: 2px 12px 5px 0;font-weight: bold;background-color: #f5f5f5;padding: 6px 14px;display: inline-block;">به همراه پکیج مخصوص
                        </p>-->
                        <div class="tarikh"> ۲۵ و ۲۶ آوریل سال ۲۰۱۹ معادل با ۵ و ۶ اردیبهشت سال ۹۸ از ساعت ۹:۰۰ تا ۲۰:۰۰ </div>
                        <div class="makan"> موسسه آموزشی 808 </div>
                        <!--<div class="zaman"> دوره تئوری: 25 مهر ساعت 8 تا 17 و 26 مهر 8 تا 12، دوره نرم افزاری: 6 روز 9 تا 16 - جمعا 48 ساعت </div>-->
                        <div class="mablagh ghabl"> 300,000 تومان </div>
                        <div class="mablagh"> 210,000 تومان </div>
                    </div>
                    <span class="sabtenam"> ثبت نام </span>
                </a>
            </div>
            <!--<div class="bought-tickets">سوال های خود را می توانید از طریق شماره تماس موسسه و سیستم پیغام خصوصی با ما در میان بگذارید.</div>-->
        </div>

    </section>

</div>

<style>
    .field-name-title h2{
        text-align: center;
        margin: 64px auto 35px;
        background: #f9f9f9;
        max-width: 96%;
        z-index: 2;
        position: relative;
    }
    .field-name-title h2:before{
        content: "";
        position: absolute;
        width: 130px;
        height: 3px;
        background: #883ab7;
        bottom: -10px;
        right: calc(50% - 65px);
        box-shadow: rgba(136,58,183,0.15) 0 1px 6px, rgba(136,58,183,0.157) 0 1px 4px;
    }
    .field-name-body{
        margin-top: -66px;
    }
    <?php
        echo readfile("https://civil808.com/sites/all/themes/sara/css/less/kargah-land.min.css");
    ?>
</style>