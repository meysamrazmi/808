<?php if(!isset($_COOKIE['banner'])):?>
    <div id="block-block-45" class="block block-block contextual-links-region first odd">
        <div class="content">
            <span class="close-banner">X</span>
<!--            --><?php //if(rand(0,1) == 0){ ?>
<!--                <a class="bim" href="/node/21193" target="_blank">-->
<!--                    <div class="new-title">-->
<!--                        <p id="festival-desc" style="">دوره حضوری گام های اجرایی BIM؛ مطالعه موردی: پروژه Expolink امارات-->
<!--                            <br>-->
<!--                            <span class="sub-title" style="position: relative; font-weight: bold">-->
<!--                                اردیبهشت ماه 98-->
<!--                            </span>-->
<!---->
<!--                        </p>-->
<!--                    </div>-->
<!--                </a>-->
<!--                <a class="bim" href="http://land.civil808.com/98/fetr" target="_blank">-->
<!--                    <div class="new-title">-->
<!--<!--                        <img class="right sq" src="/sites/all/themes/sara/images/laptop.png">-->-->
<!--                        <div style="margin-top: 5px; color: #cacaca!important;">-->
<!--                            <div style="color: #fff;margin-bottom: -10px">جشنواره فروش ویژه به مناسبت فرارسیدن عید سعید فطر</div>-->
<!--                            <span style="font-size: 12px">تا ۳۵ درصد تخفیف ویژه تا ۱۸ خرداد ماه تمدید شد</span>-->
<!--                        </div>-->
<!--                    </div>-->
<!--                    <div class="left" style="color: #fff !important;">کلیک کنید-->
<!--                        <span>></span>-->
<!--                    </div>-->
<!--                    <img style="display: none;" class="left" src="/sites/default/files/attachfromftp/node-19072/banner-pic.png">-->
<!--                </a>-->
<!--            --><?php //}else{ ?>
                <a class="herfe" href="/node/20190" target="_blank">
                    <div class="new-title">
                        <img class="right" src="/sites/all/themes/sara/images/banners/engineerGuy.png">
                        <div style="margin-top: 5px;">
                            <div>ثبت نام دوره های حضوری-آنلاین آمادگی ورود به حرفه عمران و معماری</div>
                            محاسبات، طراحی، نظارت و اجرا
                        </div>
                    </div>
                    <div class="left">کلیک کنید
                        <span>></span>
                    </div>
                    <img style="display: none;" class="left" src="/sites/default/files/attachfromftp/node-19072/banner-pic.png">
                </a>
<!--            --><?php //}?>
        </div>
    </div>
    <style>


        #tamdid {
            position: absolute;
            left: 151px;
            top: -15px;
        }

        #festival-desc {
            margin-top: 9px;
            font-weight: bold;
            font-family: fanum;
            color: #000000;
            font-size: 16px;
            text-shadow: 3px 3px 5px #fff, -1px -1px 0 #fff, 1px -1px 0 #fff, -1px 1px 0 #fff, 1px 1px 0 #fff;
        }

        @media screen and (max-width: 720px) {
            #kolah {
                display: none;
            }
            #clickkonid {
                display: none!important;

            }
            #tamdid {
                position: absolute;
                left: 15px;
                top: -15px;
                width: 60px;
            }
        }

        .sub-title{
            color: #6f6f6f!important;
            font-size: 11px;
            padding-top: 3px;
        }
        .sub-title > span{
            color: #9f4d4d;
            padding: 0 5px;
        }
        @media screen and (max-width: 500px) {
            .sub-title{
                font-size: 14px;
            }
        }
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
        div#block-block-45 a.bim:before {
            content: "";
            background: url(/sites/all/themes/sara/images/fetr-banner.jpg);

            top: 0;
            left: 0;
            bottom: 0;
            right: 0;
            position: absolute;
            z-index: -1;
            background-position-x: right;
            background-size: cover;
            background-position-y: center;
        }
        div#block-block-45 a.bim .left{
            position: absolute;
            left: 9px;
            top: 23px;
        }

        @media (max-width: 600px) {
            div#block-block-45 a.bim .left{
                display: none;
            }
        }
        div#block-block-45 a.bim .new-title{
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
        div#block-block-45 a.herfe .new-title{
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
        div#block-block-45 a.bim .new-title > div{
            font-size: 20px;
            color: #E65100;
            margin-top: 2px;
        }

        div#block-block-45 a.herfe .new-title > div > div{
            font-size: 20px;
            color: #E65100;
            margin-top: 2px;
        }
        div#block-block-45 a.herfe img.right{
            margin: -20px 0px 0 18px;
        }
        div#block-block-45 a.herfe img.right.sq{
            height: 80px !important;
            width: 80px;
        }

        div#block-block-45 a.herfe  img.left{
            transform: rotateY(180deg);
            position: absolute;
            left: 0;
            top: 0;
        }
        div#block-block-45 a.herfe div.left{
            position: absolute;
            left: 12px;
            top: 22px;
            color: #000;
            font-size: 15px;
        }

        @media (max-width: 1200px){}
        @media (max-width: 979px){
            div#block-block-45 a.herfe div.left{
                display: none;
            }
            div#block-block-45 a.bim .new-title{
                text-align: center;
                margin-right: 15px;
            }
        }
        @media (max-width: 979px) and (min-width: 769px) {}
        @media all and (max-width: 768px) {}
        @media all and (max-width: 600px) {
            div#block-block-45 a.herfe .new-title > div > div{
                font-size: 15px;
            }
            div#block-block-45 a.bim .new-title > div{
                font-size: 18px;
            }
        }
        @media all and (max-width: 500px) {
            div#block-block-45 a.herfe .new-title{
                text-align: center;
                margin-right: auto;
            }
            div#block-block-45 a.herfe img.right{
                display: none;
            }
            div#block-block-45 a.bim .new-title{
                text-align: center;
                margin-right: auto;
            }
            div#block-block-45 a.bim .new-title #festival-desc{
                font-size: 12px;
                margin-top: 17px;
            }
            div#block-block-45 a.bim .new-title #festival-desc .sub-title{
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