<?php if(!isset($_COOKIE['banner'])): ?>
    <div id="block-block-45" class="block block-block contextual-links-region first odd">
        <div class="content">
            <span class="close-banner">X</span>
            <a href="/seismosoft" target="_blank">
                <div class="new-title">
<!--                    <img style="display: none;" class="right" src="/sites/all/themes/sara/images/banners/engineerGuy.png">-->
                    <div style="margin-top: 5px;">
                        <div><span>25% + 10%</span>تخفیف محصولات Seismosoft به مناسبت سال نو میلادی</div>
                    </div>
                </div>
            </a>
        </div>
    </div>
    <style>
        div#block-block-45 {
            width: 100%;
            position: fixed;
            bottom: 0;
            right: 0;
            border-top: 3px solid #ff0057;
            height: 63px;
            z-index: 100;
            display: flex;
            align-items: self-start;
            background-image: url(/sites/all/themes/sara/images/aa.jpg);
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
        div#block-block-45 .new-title{
            font-size: 12px;
            width: auto;
            background-position: center;
            background-repeat: no-repeat;
            color: black;
            text-align: center;
            font-weight: bold;
            z-index: 2;
            position: relative;
            display: flex;
            justify-content: center;
        }
        div#block-block-45 .new-title > div{
            background: rgb(255, 255, 255);
            padding: 9px 40px 15px;
            border-radius: 50px;
            margin-top: 0px !important;
        }
        div#block-block-45 .new-title > div > div {
            font-size: 16px;
            color: #000000;
            font-weight: normal;
            margin-top: 7px;
            text-shadow: 0 0px 7px #fff, 0 0px 10px #fff, 0 0px 15px #fff, 0 0px 20px #fff, 0 0px 25px #fff, 0 0px 30px #FFF, 0 0px 2px #fff, 0 0px 7px #fff, 0 0px 10px #fff, 0 0px 15px #fff, 0 0px 20px #fff, 0 0px 25px #fff, 0 0px 30px #FFF, 0 0px 2px #fff, 0 0px 7px #fff, 0 0px 10px #fff, 0 0px 15px #fff, 0 0px 20px #fff, 0 0px 25px #fff, 0 0px 30px #FFF, 0 0px 2px #fff;
        }
        div#block-block-45 .new-title > div > div span {
            margin: 9px;
            color: #E91E63;
            font-family: fanum;
            font-weight: bold;
            font-size: 19px;brighttheme-notice
        }
        div#block-block-45 img.right{
            margin: -20px 0px 0 18px;
        }
        div#block-block-45 img.left{
            transform: rotateY(180deg);
            position: absolute;
            left: 0;
            top: 0;
        }
        div#block-block-45 div.left{
            position: absolute;
            left: 12px;
            top: 22px;
            color: #E91E63;
            font-size: 15px;
        }
        @media (max-width: 1200px){}
        @media (max-width: 979px){
            div#block-block-45 div.left{
                display: none;
            }
        }
        @media (max-width: 979px) and (min-width: 769px) {}
        @media all and (max-width: 768px) {}
        @media all and (max-width: 600px) {
            div#block-block-45 .new-title > div > div{
                font-size: 18px;
            }
        }
        @media all and (max-width: 500px) {
            div#block-block-45 .new-title{
                text-align: center;
                margin-right: auto;
            }
            div#block-block-45 img.right{
                display: none;
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