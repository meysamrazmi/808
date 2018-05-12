<?php if(!isset($_COOKIE['banner'])): ?>
<div id="block-block-45" class="block block-block contextual-links-region first odd">
	
    <div class="content">
	<span class="close-banner">X</span>
	<a href="http://land.civil808.com/97/bookfair" target="_blank">
		<!--<span style="background: #F44336;color: #fff;position: absolute;right: calc(50% - 110px);visibility: visible;padding: 0px 25px;font-size: 17px;width: 220px;top: -3px;border-radius: 0 0 15px 15px;border: 1px solid #fff;">تا 13 فروردین تمدید شد</span>-->
		<!--<div class="tablightext">
			<span>
			تا <span style="color: #F44336;font-family:fanum;font-size: 21px;display: inline-block;line-height: 26px;padding: 0 3px;">50%</span> تخفیف رو از دست ندید
			</span>
		</div>-->
        <div class="with-pic"><span class="pic"></span> تا <span>25</span><span>%</span>
            تخفیف کتاب و ایبوک
        </div>
        <div class="pic2" style="
    position: absolute;
    bottom: 7px;
    right: 89px;
    visibility: visible !important;
    color: black;
">
            <span style="
    font-weight: bold;
    padding: 0 4px 0 2px;
    color: #F44336;
">+</span>
            <span style="
    font-weight: bold;
    padding: 0 4px 0 2px;
    color: #F44336;
">20</span><span style="
    font-weight: bold;
    padding: 0 4px 0 2px;
    color: #F44336;
">%</span>
            شارژ هدیه
        </div>

        <div class="new-title">جشنواره کتاب و کتاب خوانی 808</div>
	</a>
	<?php
	/*دهه فجر
	<span class="close-banner">X</span>
	<a href="http://land.civil808.com/fajr95" target="_blank">
		<p>
			<span style="font-size: 50px;height: 40px;display: inline-block;vertical-align: top;line-height: 45px;z-index: 1;position: relative;">۲۰</span>
			<span style="font-size: 20px;vertical-align: top;line-height: 20px;z-index: 1;position: relative;">%</span>
		</p>
		<p>
			<span class="main-text">جشنواره فروش فصلی پاییز و روز دانشجو <span style="letter-spacing: -1px;font-weight: normal;font-size: 17px;margin: 0 10px 0 0;text-decoration: line-through;color: #FF7043;">تا ۱۶ آذر</span><span style="letter-spacing: -1px;font-weight: normal;font-size: 17px;margin: 0 10px 0 0;color: #49ff00;font-size: 20px;">تا ۲۰ آذر</span><span style="letter-spacing: -1px;font-weight: normal;font-size: 18px;background: #F44336;padding: 2px 10px;border-radius: 4px;position: absolute;width: 85px;transform: rotate(0deg);top: 0px;text-shadow: 0 0 1px #F44336;margin-right: 40px;border: 1px solid #ffffff;">تمدید شد</span></span>
		</p>   
		<span class="" style="display: inline;padding: 3px 15px;border-radius: 15px;background: #f80;background: linear-gradient(to bottom left, #FFC107 ,#F44336);font-size: 14px;letter-spacing: 0px;display: block;width: 100px;margin: -23px auto 0;line-height: 16px;text-shadow: 0 0 10px #000;display: none;">تا ۱۶ آذر</span>
		<span class="link">کلیک کنید</span>
	</a>
	*/?>
</div>
</div>

<style>
    div.with-pic {
        display: flex;
        /* align-items: center; */
        /* justify-content: right; */
        font-size: 15px;
        margin: 0;
        font-family: fanum;
        color: #000;
        text-shadow: 0 1px 1px #fff;
        position: absolute;
        right: 22px;
        top: 10px;
        visibility: visible !important;
    }
    div.with-pic span.pic {

        background: url(http://civil808.com/land/97/bookfair/images/percentage.svg);
        background-repeat: no-repeat;
        background-color: white;
        border-radius: 50%;
        background-size: 50%;
        background-position: center;
        box-shadow: 0 1px 1px #FF5722;
        width: 40px;
        height: 40px;
        display: block;
        margin-left: 15px;
        margin: 3px -4px 0px 13px;
        visibility: visible !important;
    }
    div.with-pic span:not(.pic) {
        font-weight: bold;
        padding: 0 4px 0 2px;
        color: #F44336;
    }

div#block-block-45 {
    /* background: url(http://civil808.com/sites/all/themes/sara/images/book-banner.jpg); */
    width: 100%;
    position: fixed;
    bottom: 0;
    right: 0;
    border-top: 3px solid #795548;
    height: 70px;
    z-index: 100;
    background-position-x: center;
    background-size: cover;
    display: flex;
    align-items: center;
    background-color: #ecede8;
}
div#block-block-45:after {

    content: "";
    position: absolute;
    background: url(http://civil808.com/sites/all/themes/sara/images/bookandvup.jpg);
    background-repeat: no-repeat;
    width: 200px;
    height: 70px;
    left: 9%;
    top: 0px;
    background-size: 96%;
}
div#block-block-45 .content a > div.new-title{
    visibility: visible;
    background: url(http://civil808.com/sites/all/themes/sara/images/jashnvare-png.png);
    font-size: 0px;
    width: 300px;
    height: 40px;
    background-position: center;
    background-repeat: no-repeat;
    margin: 15px auto 0 auto;
}
div#block-block-45:before {
  content: "";
  position: absolute;
  background: url(../images/20percent.png);
  background-repeat: no-repeat;
  background-size: cover;
  width: 340px;
  height: 30px;
  right: 5%;
  visibility: hidden;
}
div#block-block-45 span.link {
  position: absolute;
  left: 50px;
  top: 8px;
  font-size: 17px;
  border: 2px solid;
  padding: 3px 20px 3px 40px;
  border-radius: 35px;
  background: rgba(255, 255, 255, 0.19);
  text-shadow: 0 0 8px #000;
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
div#block-block-45 .content a > * {
  visibility: hidden;
}
div#block-block-45 .content p:first-child {
  visibility: visible;
  position: absolute;
  right: 5%;
  top: -3px;
  font-weight: bold;
  box-shadow: rgba(0, 0, 0, 0.247059) 0px 10px 45px, rgba(0, 0, 0, 0.219608) 0px 9px 18px;
  font-family: fanum;
  background: #F44336;
  padding: 8px 0px 0 4px;
  letter-spacing: -7px;
  width: 50px;
  height: 50px;
  text-align: center;
  border-radius: 0;
}
div#block-block-45 .content p:first-child:before {
  -webkit-transform: rotate(30deg);
  -moz-transform: rotate(30deg);
  -ms-transform: rotate(30deg);
  -o-transform: rotate(30deg);
}
div#block-block-45 .content p:first-child:before, div#block-block-45 .content p:first-child:after {
  content: "";
  position: absolute;
  top: 0;
  left: 0;
  height: 50px;
  width: 50px;
  background: #F44336;
  z-index: 0;
}
div#block-block-45 .content p:first-child:after {
  -webkit-transform: rotate(60deg);
  -moz-transform: rotate(60deg);
  -ms-transform: rotate(60deg);
  -o-transform: rotate(60deg);
}
div#block-block-45 .main-text {
  font-size: 21px;
  text-shadow: 0 0 10px #000;
  border-bottom: 2px solid;
  border-right: 5px solid;
  padding: 0px 30px;
  position: absolute;
  right: 60px;
  bottom: 4px;
  font-weight: 500;
}
div#block-block-45 span.link:after {
  content: "\f04d";
  font-family: mat;
  position: absolute;
  padding: 3px 0px 4px 0;
  font-size: 22px;
  transition: all 0.3s ease;
}
div#block-block-45:hover span.link:after {
  padding: 3px 7px 4px 0;
}

div#block-block-45 .content {
  display: flex;
  align-items: center;
  height: 100%;
}
div#block-block-45 .content:before {
    /*background: url(/sites/all/themes/sara/images/font96.png);*/
    background-repeat: no-repeat;
    width: 24%;
    height: 53px;
    background-position: center;
    background-size: 80%;
    right: 31%;
    content:"";
    position: absolute;
}

#block-block-45 div.tablightext{
    position: absolute;
    left: 0px;
    height: 60px;
    width: 36%;
    z-index: 36;
    text-align: center;
    padding-top: 18px;
}
#block-block-45 div.tablightext span{
    color: black;
    font-size: 15px;
    font-weight: bold;
    height: 57px;
    text-align: center;
    visibility: visible;
    vertical-align: top;
}
#block-block-45 div.tablightext:after {
    content: "\f104";
    font-size: 38px;
    font-family: aw;
    color: black;
    visibility: visible;
    line-height: 23px;
    margin-right: 29px;
    transition: all ease 0.5s;
    position: absolute;
}
#block-block-45:hover div.tablightext:after {
    margin-right: 50px;
}
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

@media (max-width: 1200px){

}

@media (max-width: 979px){
    .with-pic,.pic2{
        display:none !important;
    }
    .new-title{
    text-align: right !important;
    margin-right: 15px !important;
    }

}

@media (max-width: 979px) and (min-width: 769px){


@media all and (max-width: 768px) {
}

@media all and (max-width: 600px) {
    div#block-block-45 .content a > div.new-title{
        text-align: center !important;
        margin-right: 0px !important;
    }
    div#block-block-45:after{
        display: none !important;
    }
}

@media all and (max-width: 500px) {

}

@media all and (max-width: 400px) {

}

</style>



<?php endif;?>



