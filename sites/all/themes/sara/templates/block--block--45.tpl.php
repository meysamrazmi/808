<?php if(!isset($_COOKIE['banner'])): ?>
<div id="block-block-45" class="block block-block contextual-links-region first odd">
    <div class="content">
        <span class="close-banner">X</span>
        <a href="/node/19072" target="_blank">
            <img class="right" src="/sites/default/files/attachfromftp/node-19072/banner-pic.png">
            <div class="new-title">
                دوره جامع آموزش اصول محاسبات
                <div>بهسازی لرزه ای و طراحی عملکردی سازه ها</div>
            </div>
            <img class="left" src="/sites/default/files/attachfromftp/node-19072/banner-pic.png">
        </a>
    </div>
</div>
<style>
    div#block-block-45 {
        width: 100%;
        position: fixed;
        bottom: 0;
        right: 0;
        border-top: 3px solid #1a68a9;
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
    }
    .new-title{
        font-size: 12px;
        width: auto;
        background-position: center;
        background-repeat: no-repeat;
        margin: 7px auto 0 auto;
        color: black;
        text-align: center;
        font-weight: bold;
        z-index: 2;
        position: relative;
    }
    .new-title > div{
        font-size: 20px;
        color: #E65100;
        margin-top: 2px;
    }
    img.right{
        position: absolute;
        right: 0;
        top: 0;
    }
    img.left{
        transform: rotateY(180deg);
        position: absolute;
        left: 0;
        top: 0;
    }

@media (max-width: 1200px){}
@media (max-width: 979px){
    .new-title{
        text-align: right;
        margin-right: 15px;
    }
    img.right{
        display: none;
    }
}
@media (max-width: 979px) and (min-width: 769px) {}
@media all and (max-width: 768px) {}
@media all and (max-width: 600px) {
    .new-title > div{
        font-size: 18px;
    }
    img.left{
        opacity: 0.3;
        height: 70px;
    }
}
@media all and (max-width: 500px) {
    .new-title{
        text-align: center;
        margin-right: auto;
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



