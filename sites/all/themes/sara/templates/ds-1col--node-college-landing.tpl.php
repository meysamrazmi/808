

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php print render($title_prefix); ?><?php if (!$page): ?><?php endif; ?><?php print render($title_suffix); ?>
    <?php if ($node->nid == 21193): ?>
    <div class="content"<?php print $content_attributes; ?>>
        <?php
        print render($content);
        ?>
    </div>
    <section class="iframe">
        <h2 class="text">معرفی گواهینامه‌های جدید 808 مبتنی بر سیستم بلاک‌چین</h2>

        <div style="max-width: 840px; margin: auto;">
            <div style="position: relative; padding-bottom: 56.25%;">
                <iframe style="background-image: url('../../img/iframe.gif'); position: absolute; top: 0px; left: 0px; width: 840px; height: 472px; max-width: 840px; max-height: 472px;" src="https://www.civil808.com/file/iframe/21192" width="320" height="240"></iframe>
            </div>
        </div>
    </section>
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
        <div class="takhfifat" style="margin-bottom: 15px;">
            <p>
                <span>10 %</span>تخفیف برای اعضای VIP، <a href="/landing/vip" target="_blank">عضو ویژه شوید</a>        </p>
        </div>
        <div class="takhfifat">
            <p>و<span>5 %</span> تخفیف به ازای اضافه شدن هر نفر تا سقف 20 درصد</p>
        </div>
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
                        <div class="mablagh"> 300,000 تومان </div>
<!--                        <div class="mablagh"> 210,000 تومان </div>-->
                    </div>
                    <span class="sabtenam"> ثبت نام </span>
                </a>
            </div>
            <!--<div class="bought-tickets">سوال های خود را می توانید از طریق شماره تماس موسسه و سیستم پیغام خصوصی با ما در میان بگذارید.</div>-->
        </div>
    </section>
    <?php endif; ?>

    <?php if($node->nid == 19124): ?>
    <div class="content"<?php print $content_attributes; ?>>
    <?php
        //madump($node);
        //madump(entity_load('field_collection_item', array(2157)));
    /**
     * text | متن ساده
     * iframe | iframe
     * teacherUid | مدرس با uid
     * teacherNid | مدرس از دانشنامه با nid
     * relateTid | مطالب مرتبط با دسته بندی
     * relateNid | مطالب مرتبط با nid
     */
        foreach ($node->field_college_landing_collection['und'] as $key => $section){
            $section_id = $section['value'];
            $collection_load = entity_load('field_collection_item', array($section_id));
            $section_name = $collection_load[$section_id]->field_collection_section['und'][0]['value'];
            $section_title = $collection_load[$section_id]->field_collection_title['und'][0]['value'];
            $section_subtitle = $collection_load[$section_id]->field_collection_subtitle['und'][0]['value']; ?>
            <section class="<?php print $section_name; ?>">
                <h2 class="text"><?php print $section_title; ?></h2>
                <p style="text-align: center;padding: 15px 0 0;color: #888;"><?php print $section_subtitle; ?></p>
            </section>

        <?php
        }
        ?>
    </div>
    <?php endif; ?>

</div>

<style>
    .node-unpublished {
        background-color: transparent;
    }
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

    div.presenter img {
        border-radius: 50%;
        border: 2px solid #fff;
        box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
    }
    div.presenter {
        position: relative;
        text-align: center;
        background: #fff;
        box-shadow: rgba(0, 0, 0, 0.15) 0px 1px 6px, rgba(0, 0, 0, 0.157) 0px 1px 4px;
        margin: auto;
        padding: 15px 15px 15px;
        max-width: 800px;
        width: 100%;
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

    <?php
        echo readfile("https://civil808.com/sites/all/themes/sara/css/less/kargah-land.min.css");
    ?>
</style>