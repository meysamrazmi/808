<?php if(!isset($_COOKIE['banner'])): ?>
    <div id="block-block-45" class="block block-block contextual-links-region first odd">
        <div class="content">
	        <span class="close-banner">X</span>
            <?php // echo '<div id="smile"><canvas style="display: block;"></canvas></div>' ?>
            <a href="http://civil808.com/conference/4" target="_blank" style="border-top: 3px solid #92278f; ">
            <?php  //echo <p class="textimg"></p> ?>
            <?php  //echo <p class="titr"><img src="/sites/all/themes/sara/images/title-daneshjoo.png"></p> ?>
            <?php  //echo <p class="texts"> ?>
            <?php  //echo '<span class="texttt">20<span >%</span></span><span class="text1"> شارژ هدیه</span><span class="text4">+</span><span class="text2">ارسال رایگان</span>' ;?>
            <?php  //echo '<span class="text5"> تا 28 مهر ماه تمدید شد !!</span></p>' ;?> 
            <?php //echo '<p class="text6"><span>یک ماه عضویت vip</span><span>به ازای تکمیل پروفایل خود در سایت</span></p>'; ?>
            <?php //echo '<p class="text6"><span class="row1"><span style="color: #960a00;">20 %</span><span> شارژ هدیه</span></span><span>ارسال رایگان پستی </span></p>'; ?>
            <?php /*echo <div class="background-nim"><img src="/sites/all/themes/sara/images/yaldatemp.png"></div>
            <div class="text-nim">
            <div> زمستان امسال با <p class="inner-p"><span> 808 </span> <span> + </span></p> در کنار شما هستیم </div>
            <p> کلیک کنید و تخفیف های شب یلدا و قابلیت های سیستم پرسش و پاسخ جدید ما را ببینید !! </p>
            </div>
            */ ?> 
            <div class="back-right">
                <img src="/sites/all/themes/sara/images/tabriz.png" width="150px" height="auto" style="opacity: 0.3;vertical-align: top;">
                <img src="/sites/all/themes/sara/images/mashad.png" width="200px" height="auto" style="vertical-align: top;margin-right: 27px;">
            </div>
            <div class="back-left">
                <img src="/sites/all/themes/sara/images/azadi-tower.png" width="110px" height="auto" style="opacity: 0.1;vertical-align: top;">
                <img src="/sites/all/themes/sara/images/esfehan.png" width="240px" height="auto" style="vertical-align: top;margin-right: 27px;">
            </div>
            <div class="middle-text"> چهارمین همایش ملی طراحی عملکردی سازه ها </div>
            </a>
        </div>
    </div>
<?php endif;?>

<!-- old css code for this block -->
<style>
    div#block-block-45 .titr{
      position: absolute;
      top: 19px;
      right: calc(50vw - 195px);
      font-size: 25px;
      color: white;
  }
  div#block-block-45 .titr img{
      width: 420px;
  }
  div#block-block-45 .titr span {
      color: red;
  }
  div#block-block-45 a > img {
      position: absolute;
      left: 12px;
      width: 95px;
      transform: rotate(32deg);
      top: -11px;
  }
  div#block-block-45 div#smile {
      width: 100%;
      position: absolute;
      z-index: 0;
      top: 0;
      height: 100%;
      border: none;
      background: #fff;
  }
  div#block-block-45 .titr:after {
      /*content: "";
      height: 74px;
      width: 80px;
      left: -60px;
      top: 0;
      position: absolute;
      display: flex;
      align-items: center;
      background-image: url(//civil808.com/sites/all/themes/sara/images/moon.png);
      background-repeat: no-repeat;*/
  }
  #block-block-45 .text3{
      position: absolute;
      border-radius: 50%;
      background-color: #FDD835;
      width: 0px;
      transition: all ease 0.2s;
      top: 35px;
      left: 104px;
      height: 4px;
      z-index: 100;
      width: 0px;
      opacity: 0;
  }
  #block-block-45:hover .text3{
      left: -276px;
      top: -45px;
      width: 514px;
      height: 454px;
      opacity: 1;
  }
  #block-block-45:hover span.more{
      color:black;
  }
  #block-block-45 .texts{
      position: absolute;
      font-size: 20px;
      color: #444;
      top: 19px;
      right: 4%;
      text-align: center;
      padding: 2px 15px;
  }
  #block-block-45 .textimg{
      position: absolute;
      top: -51px;
      right: 0;
      padding: 2px 15px;
      background-image: url(http://civil808.com/sites/all/themes/sara/images/pencil.png);
      height: 138px;
      width: 240px;
      background-position: center;
      background-size: cover;
  }
  #block-block-45 a.more{
      position: absolute;
      /* top: 63px; */
      /* right: 103px; */
      font-size: 16px;
      left: 2%;
      top: 26px;
      z-index: 102;
      color: #333;
  }
  #block-block-45 a.more:after {
      content: "\f141";
      font-family: mat;
      vertical-align: sub;
      margin-right: 5px;
  }
  #block-block-45 .text1{
      margin-right: 12px;
  }
  #block-block-45 .text2{
      color: red;
      text-shadow: 0 0 10px #fff, 0 0 10px #fff, 0 0 10px #fff;
      background: #eee;
      padding: 0 10px;
      border-radius: 5px;
      display: inline-block;
  }
  #block-block-45 .text4{
      margin: 0 7px;
  }
  #block-block-45 span.texttt {
      background: #f00;
      width: 45px;
      display: inline-block;
      line-height: 40px;
      position: absolute;
      z-index: 1;
      margin-left: 12px;
      font-family: fanum;
      margin: -40px -40px 0 0;
      font-size: 40px;
      font-weight: bold;
      padding-left: 10px;
      padding-top: 5px;
      letter-spacing: -8px;
      color: #fff;
  }
  #block-block-45 span.texttt:before,
  #block-block-45 span.texttt:after {
      content: "";
      position: absolute;
      width: 45px;
      height: 45px;
      background: #f00;
      right: 0;
      top: 0;
      z-index: -1;
  }
  #block-block-45 span.texttt:before {
      transform: rotate(60deg);
  }
  #block-block-45 span.texttt:after {
      transform: rotate(120deg);
  }
  #block-block-45 span.texttt span{
      position: absolute;
      font-size: 20px;
      top: 0px;
      left: 1px;
      letter-spacing: 0;
  }
  #block-block-45 .text5 {
      /*margin: 0 25px 0 0;*/
      font-family: fanum;
  }
  #block-block-45 p.text6 {
      position: absolute;
      left: 67px;
      height: 52px;
      margin-top: 4px;
      font-size: 13px;
      line-height: 33px;
  }
  #block-block-45 p.text6 > span {
      display: block;
      text-align: center;
      color: #fff;
      font-size: 15px;
  }
  #block-block-45 p.text6 span.row1:after {
      /*content: "\f1a5";
      font-family: mat;
      float: left;
      position: absolute;
      bottom: 21px;
      margin-right: 4px;
      font-size: 25px;
      color: #fcd201;*/
      content: "+";
      font-family: mat;
      float: left;
      position: absolute;
      bottom: 20px;
      margin-right: 9px;
      font-size: 26px;
      color: #960a00;
      font-weight: bold;
  }
  
  #block-block-45 p.text6 span.row1 {
      /*border-bottom: 2px solid #fcd201;
      text-align: right;
      padding: 0 37px 0 59px;
      font-size: 16px;
      color: white;*/
      border-bottom: 2px solid #fcd201;
      text-align: right;
      padding: 0 35px 0 59px;
      font-size: 16px;
      color: white;
  }
  @media all and (max-width:1200px){
      #block-block-45 .texts{
          font-size: 16px;
          top: 21px;
      }
      div#block-block-45 .titr {
          right: calc(50vw - 183px);
      }
      #block-block-45 p.text6 {
          left: 22px;
      }
      #block-block-45 p.text6 span:first-child {
          font-size: 13px;
      }
  }
  @media (max-width: 979px ){
      div#block-block-45 a.titr {
      right: calc(50vw - 106px);
      font-size: 23px;
      }
      #block-block-45 a.more {
          left: 1%;
          font-size: 13px;
          top: 28px;
      }
      #block-block-45:hover .text3 {
          width: 453px;
          height: 390px;
      }
      div#block-block-45 a > img {
          display: none;
      }
      #block-block-45 .texts{
          display: flex;
          flex-direction: column;
          top: 3px;
          right: 6%;
      }
      #block-block-45 .text4{
          display: none;
      }
      #block-block-45 span.text1:after {
          content: " + ";
      }
      div#block-block-45 .titr {
          right: calc(50vw - 119px);
      }
      #block-block-45 p.text6 {
          display : none;
      }
  }
  @media (max-width: 768px ){
      div#block-block-45 .titr {
          right: calc(50vw - 71px);
          width: 341px;
      }
      #block-block-45 p.text6 {
          display: none;
      }
  }
  @media (max-width: 660px ){
      div#block-block-45 a.titr {
      left: 70px;
      right: inherit;
      }
      div#block-block-45 .more,
      div#block-block-45 .text3{
          display:none;
      }
      .close-banner {
          left: 5px;
          right: initial;
      }
      div#block-block-45 .texts{
          display: none;
      }
      div#block-block-45 .titr {
          position: relative;
          text-align: center;
          right: calc(50vw - 113px);
      }
      #block-block-45 p.textimg {
          background-size: 77%;
          background-repeat: no-repeat;
          right: -22px;
          width: 200px;
          top: auto;
          bottom: -34px;
      }
  }
  @media (max-width: 500px ){
      div#block-block-45 a.titr {
          font-size: 18px;
          line-height: 15px;
          padding: 15px 0;
      }
      #block-block-45 .texts {
          display: flex;
          flex-direction: column;
          top: 3px;
          right: 8%;
      }
      div#block-block-45 .titr {
          position: relative;
          text-align: center;
          right: auto;
          margin: auto;
          width: 300px;
          top: 23px;
      }
      #block-block-45 p.textimg {
          display: none;
      }
  }
  @media (max-width: 400px ){
      #block-block-45 .texts {
      flex-direction: row;
      top: 15px;
      }
      div#block-block-45 a.titr {
      color: #fff;
      }
  div#block-block-45 a.titr span {
      color: #fff;
  }
  }
</style>