<?php if(!isset($_COOKIE['banner'])): ?>
    <div id="block-block-45" class="block block-block contextual-links-region first odd">
        <div class="content">
            <span class="close-banner">X</span>
            <a href="http://land.civil808.com/98/eid" target="_blank">

                <div class="new-title">
                    <p id="festival-desc" style="">تا 50 درصد تخفيف تا پایان اسفند
                        <br>
                        <span class="sub-title" style="position: relative; font-weight: bold">
                             30 تخفیف ویژه +
                            10 درصد؜ تخفيف اعضای VIP + تخفیف گروهی و شارژ هدیه اپلیکیشن
                        </span>

                    </p>
                </div>
<!--                <img id="tamdid" src="/sites/all/themes/sara/images/banners/tamdid.png" width="85px" alt="">-->
                <img id="kolah" src="/sites/all/themes/sara/images/7sin.png" width="100px"
                     style="position: absolute;
                            right: 51px;
                            top: -26px;">

                <span id="clickkonid" style="color:#424242;font-weight:bold;font-size: 16px;position: absolute; left: 50px; top: 15px;background: rgba(255,255,255,0.7);z-index: 2;display: inline-block; padding: 5px;border-radius: 5px">کلیک کنید!</span>

            </a>
        </div>
    </div>
    <style>


        #tamdid {
            position: absolute;
            left: 151px;
            top: -15px;
        }

        #festival-desc {
            margin-top: 5px;
            font-weight: bold;
            font-family: fanum;
            color: #388E3C;
            font-size: 16px;
            text-shadow:
                    3px 3px 5px #fff,
                    -1px -1px 0 #fff,
                    1px -1px 0 #fff,
                    -1px 1px 0 #fff,
                    1px 1px 0 #fff;
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
            color: #F44336!important;
            font-size: 17px;
            font-weight: bold;
            padding-top: 3px;
            /*display: block;*/
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
        div#block-block-45 a:before {
            content: "";
            background:url(/sites/all/themes/sara/images/nowruz.jpg);
            opacity: 0.3;
            top: 0;
            left: 0;
            bottom: 0;
            right: 0;
            position: absolute;
            z-index: -1;
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
                text-align: center;
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