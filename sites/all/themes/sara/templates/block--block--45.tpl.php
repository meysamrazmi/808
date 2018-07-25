<?php if(!isset($_COOKIE['banner'])): ?>
<div id="block-block-45" class="block block-block contextual-links-region first odd">
    <div class="content">
        <span class="close-banner">X</span>
        <a href="http://civil808.com/node/19340" target="_blank">
            <img class="right" src="/sites/all/themes/sara/images/ramadan-bg.jpg">
            <div class="new-title">
                تا 10 مرداد تمدید شد
                <div>20 درصد شارژ هدیه برای شرایط بحرانی اقتصاد کشور</div>
            </div>
            <img class="left" src="/sites/all/themes/sara/images/ramadan-bg.jpg">
        </a>
    </div>
</div>
<style>
    div#block-block-45 {
        width: 100%;
        position: fixed;
        bottom: 0;
        right: 0;
        /* border-top: 3px solid #564967; */
        height: 70px;
        z-index: 100;
        background-position-x: center;
        background-size: cover;
        display: flex;
        align-items: center;
        background-color: white;
    }
    div#block-block-45 .content {
        display: flex;
        align-items: center;
        height: 100%;
    }
    div#block-block-45 .content a {
        color: #fff !important;
        position: absolute;
        width: 100%;
        height: 100%;
        right: 0;
        top: 0;
        z-index: 1;
        background-color: #584968;
    }
    .new-title{
        font-size: 12px;
        width: auto;
        background-position: center;
        background-repeat: no-repeat;
        margin: 8px auto 0 auto;
        /*color: #fec57e;*/
        color: #ff9800;
        text-align: center;
        font-weight: bold;
        z-index: 2;
        position: relative;
    }
    .new-title > div{
        font-size: 19px;
        color: #ffffff;
        margin-top: 2px;
        font-weight: normal;
    }
    img.right{
        transform: rotateY(180deg);
        position: absolute;
        right: 0;
        top: 0;
    }
    img.left{
        position: absolute;
        left: 0;
        top: 0;
    }

@media (max-width: 1360px){
    .new-title{
        text-align: right;
        margin-right: 15px;
    }
    img.right{
        display: none;
    }
}
@media (max-width: 979px){}
@media (max-width: 979px) and (min-width: 769px) {}
@media all and (max-width: 768px) {}
@media all and (max-width: 896px) {
    .new-title > div{
        font-size: 18px;
    }
    img.left{
        opacity: 0.2;
        height: 70px;
    }
}
@media all and (max-width: 500px) {
    .new-title{
        text-align: center;
        margin-right: auto;
    }
    .new-title > div{
        font-size: 15px;
        margin-top: 5px;
    }
}
@media all and (max-width: 400px) {}

/*----------------------------------------------------*/
    .close-banner {
        position: absolute;
        top: -25px;
        left: 5px;
        background: rgba(0, 0, 0, 0.5);
        color: #fff;
        width: 20px;
        height: 20px;
        padding: 0;
        border-radius: 50%;
        text-align: center;
        cursor: pointer;
    }
    .close-banner:hover:before {
        opacity: 1;
        left: 30px;
    }
    .close-banner:before {
        content: "بستن تبلیغ";
        position: absolute;
        left: -30px;
        color: #555;
        font-size: 12px;
        line-height: 20px;
        transition: all 0.1s;
        white-space: nowrap;
        opacity: 0;
    }

</style>

<?php endif;?>



