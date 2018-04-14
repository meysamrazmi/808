<?php if(!isset($_COOKIE['banner'])): ?>
<div id="block-block-45" class="block block-block contextual-links-region first odd">
	
    <div class="content">
	<span class="close-banner">X</span>
	<a href="http://land.civil808.com/97/eid" target="_blank">
		<span style="background: #F44336;color: #fff;position: absolute;right: calc(50% - 110px);visibility: visible;padding: 0px 25px;font-size: 17px;width: 220px;top: -3px;border-radius: 0 0 15px 15px;border: 1px solid #fff;">تا 13 فروردین تمدید شد</span>
		<div class="tablightext">
			<span>
			تا <span style="color: #F44336;font-family:fanum;font-size: 21px;display: inline-block;line-height: 26px;padding: 0 3px;">50%</span> تخفیف رو از دست ندید
			</span>
		</div>
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

div#block-block-45 {
	background: url(http://civil808.com/sites/all/themes/sara/images/bg-sabz2.png);
	width: 100%;
	position: fixed;
	bottom: 0;
	right: 0;
	border-top: 3px solid #8bb65d;
	height: 70px;
	z-index: 100;
	background-position-x: center;
	background-size: cover;
	display: flex;
	align-items: center;
	background-color:white;
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
div#block-block-45:after {
	content: "";
    position: absolute;
    background: url(http://civil808.com/sites/all/themes/sara/images/gol.png);
    background-repeat: no-repeat;
    width: 27%;
    height: 159px;
    right: 0;
    background-size: 90%;
    -ms-transform: rotate(17deg);
    -webkit-transform: rotate(17deg);
    transform: rotate(17deg);
    bottom: -54px;
}
div#block-block-45 .content {
  display: flex;
  align-items: center;
  height: 100%;
}
div#block-block-45 .content:before {
    background: url(/sites/all/themes/sara/images/font96.png);
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
div#block-block-45:after {
    width: 27%;
    height: 159px;
}
#block-block-45 div.tablightext:after {
    font-size: 28px;
    line-height: 28px;
    margin-right: 16px;
}
#block-block-45 div.tablightext span {
    font-size: 17px;
}
#block-block-45 div.tablightext {
    width: 33%;
}
#block-block-45:hover div.tablightext:after {
    margin-right: 20px;
}
}

@media (max-width: 979px){
div#block-block-45:before {
  width: 300px;
  height: 27px;
  right: 2%;
}
div#block-block-45 .content p:first-child {
  right: 2%;
}
}

@media (max-width: 979px) and (min-width: 769px){
div#block-block-45:after{
    height: 148px;
    bottom: -67px;
}
div#block-block-45 .content:before {
    width: 33%;
}
div#block-block-45 {
    background-position-x: 41%;	
}
}

@media all and (max-width: 768px) {
div#block-block-45 .content a{
	zoom: 0.8;
    margin-top: 10px;
}
div#block-block-45:after {
    width: 32%;
    margin-bottom: -2%;
}
div#block-block-45 {
    background-position-x: 38%;
}
div#block-block-45 .content:before {
    width: 35%;
}
}

@media all and (max-width: 600px) {
	#block-block-45 div.tablightext span {
    font-size: 15px;
}
div#block-block-45 .content:before {
    width: 42%;
    right: 23%;
}
div#block-block-45:after {
    width: 32%;
    margin-bottom: -4%;
}
}

@media all and (max-width: 500px) {
div#block-block-45 .content p:first-child {
  right: 5px;
}
div#block-block-45 span.link {
  left: calc(50% - 70px);
  left: 10px;
  bottom: 0;
  top: initial;
  display: none;
}
div#block-block-45 .main-text {
  width: 96%;
  right: 2%;
  border: solid #ffffff;
  /* background: rgba(255, 255, 255, 0.4); */
  border-width: 0 5px;
  top: 11px;
  bottom: inherit;
}
div#block-block-45 .content:before {
    width: 47%;
    right: 14%;
}
#block-block-45 div.tablightext {
    width: 37%;
}
div#block-block-45 .content p:first-child {
  right: calc(50% - 190px);
}
div#block-block-45 {
    background-position-x: 34%;
}
div#block-block-45:after {
    bottom: -62px;
    width: 34%;
}
div#block-block-45:before {
  right: calc(50% - 150px);
}
}

@media all and (max-width: 400px) {
div#block-block-45:after {
    display:none;
}
div#block-block-45 .content:before {
    width: 55%;
    right: 10px;
}
div#block-block-45 {
    background-position-x: 33%;
}
}

</style>



<?php endif;?>



