<?php if(!isset($_COOKIE['banner'])): ?>
<div id="block-block-45" class="block block-block contextual-links-region first odd">
    <div class="content">
        <span class="close-banner">X</span>
        <div id="smile">
            <canvas width="570" height="250" style="display: block;">
            </canvas>
            <a href="http://land.civil808.com/97/eidtaeid/" target="_blank">
                <img class="right" style="display: none;" src="/sites/all/themes/sara/images/ramadan-bg.jpg">
                <div class="new-title">
                    <!--                تا 10 مرداد تمدید شد-->
                    <div>جشنواره فروش ویژه عید تا عید با سورپرایزهای جدید</div>
                </div>
                <img class="left" style="display: none;"  src="/sites/all/themes/sara/images/ramadan-bg.jpg">
            </a>
        </div>
        <span class="darsad"><span>%</span><span>20</span></span>
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
        box-shadow: rgba(0, 0, 0, 0.15) 0px 1px 6px, rgba(0, 0, 0, 0.157) 0px 1px 4px;
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
        z-index: 5;
        border-top: 2px solid #f44336;
    }
    div#smile {
        position: absolute;
        height: 100%;
        border: none;
        background: #81d4fa;
    }
    div#smile + .darsad {
        position: absolute;
        z-index: 1;
        right: 20px;
        top: -3px;
    }
    span.darsad {
        font-family: fanum;
        background: #F44336;
        color: #fff;
        text-shadow: none;
        margin: 0 10px 0 20px;
        padding: 0 10px 0 0;
        font-weight: bold;
        font-size: 4rem;
        display: inline-block;
        letter-spacing: -10px;
        width: 60px;
        height: 60px;
        position: relative;
        text-align: center;
        box-sizing: border-box;
        line-height: 4.8rem;
        font-size: 50px;
    }
    .darsad:before, .darsad:after {
        content: "";
        position: absolute;
        top: 0;
        left: 0;
        height: 60px;
        width: 60px;
        background: #F44336;
        z-index: 0;
    }
    .darsad:before {
        -webkit-transform: rotate(30deg);
        -moz-transform: rotate(30deg);
        -ms-transform: rotate(30deg);
        -o-transform: rotate(30deg);
    }
    .darsad:after {
        -webkit-transform: rotate(60deg);
        -moz-transform: rotate(60deg);
        -ms-transform: rotate(60deg);
        -o-transform: rotate(60deg);
    }
    .darsad span {
        z-index: 1;
        position: relative;
    }
    .darsad span:first-child {
        font-size: 1.5rem;
        letter-spacing: 0;
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
        color: #fff;
        margin-top: 2px;
        font-weight: normal;
        line-height: 50px;
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



