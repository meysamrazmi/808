<?php

/**
 * @file
 * This file is the default customer invoice template for Ubercart.
 *
 * Available variables:
 * - $products: An array of product objects in the order, with the following
 *   members:
 *   - title: The product title.
 *   - model: The product SKU.
 *   - qty: The quantity ordered.
 *   - total_price: The formatted total price for the quantity ordered.
 *   - individual_price: If quantity is more than 1, the formatted product
 *     price of a single item.
 *   - details: Any extra details about the product, such as attributes.
 * - $line_items: An array of line item arrays attached to the order, each with
 *   the following keys:
 *   - line_item_id: The type of line item (subtotal, shipping, etc.).
 *   - title: The line item display title.
 *   - formatted_amount: The formatted amount of the line item.
 * - $shippable: TRUE if the order is shippable.
 *
 * Tokens: All site, store and order tokens are also available as
 * variables, such as $site_logo, $store_name and $order_first_name.
 *
 * Display options:
 * - $op: 'view', 'print', 'checkout-mail' or 'admin-mail', depending on
 *   which variant of the invoice is being rendered.
 * - $business_header: TRUE if the invoice header should be displayed.
 * - $shipping_method: TRUE if shipping information should be displayed.
 * - $help_text: TRUE if the store help message should be displayed.
 * - $email_text: TRUE if the "do not reply to this email" message should
 *   be displayed.
 * - $store_footer: TRUE if the store URL should be displayed.
 * - $thank_you_message: TRUE if the 'thank you for your order' message
 *   should be displayed.
 *
 * @see template_preprocess_uc_order()
 */
?>
<style type="text/css">
  @font-face {
  	font-family: iransans;
  	font-style: normal;
  	font-weight: bold;
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Bold.eot');
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Bold.eot?#iefix') format('embedded-opentype'),  /* IE6-8 */
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/woff2/IRANSansWeb_Bold.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/woff/IRANSansWeb_Bold.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/ttf/IRANSansWeb_Bold.ttf') format('truetype');
  }
  @font-face {
  	font-family: iransans;
  	font-style: normal;
  	font-weight: 500;
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Medium.eot');
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Medium.eot?#iefix') format('embedded-opentype'),  /* IE6-8 */
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/woff2/IRANSansWeb_Medium.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/woff/IRANSansWeb_Medium.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/ttf/IRANSansWeb_Medium.ttf') format('truetype');
  }
  @font-face {
  	font-family: iransans;
  	font-style: normal;
  	font-weight: normal;
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb.eot');
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb.eot?#iefix') format('embedded-opentype'),  /* IE6-8 */
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/woff2/IRANSansWeb.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/woff/IRANSansWeb.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/ttf/IRANSansWeb.ttf') format('truetype');
  }
  @font-face {
  	font-family: iransans;
  	font-style: normal;
  	font-weight: 200;
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Light.eot');
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Light.eot?#iefix') format('embedded-opentype'),  /* IE6-8 */
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/woff2/IRANSansWeb_Light.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/woff/IRANSansWeb_Light.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/ttf/IRANSansWeb_Light.ttf') format('truetype');
  }
  @font-face {
  	font-family: iransans;
  	font-style: normal;
  	font-weight: 100;
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_UltraLight.eot');
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_UltraLight.eot?#iefix') format('embedded-opentype'),  /* IE6-8*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/woff2/IRANSansWeb_UltraLight.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/woff/IRANSansWeb_UltraLight.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/ttf/IRANSansWeb_UltraLight.ttf') format('truetype');
  }
  @font-face {
  	font-family: fanum;
  	font-style: normal;
  	font-weight: 100;
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/fanum/irsfanum.eot');
  	src: url('https://civil808.com/sites/all/themes/sara/fonts/sans/fanum/irsfanum.eot?#iefix') format('embedded-opentype'),  /* IE6-8*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/fanum/irsfanum.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/fanum/irsfanum.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
  		 url('https://civil808.com/sites/all/themes/sara/fonts/sans/fanum/irsfanum.ttf') format('truetype');
  }
  @font-face {
    font-family:'mat';
    src:	url('https://civil808.com/sites/all/themes/sara/fonts/material/material.eot');
    src:	url('https://civil808.com/sites/all/themes/sara/fonts/material/material.eot?#iefix') format('embedded-opentype'),
      url('https://civil808.com/sites/all/themes/sara/fonts/material/material.woff') format('woff'),
      url('https://civil808.com/sites/all/themes/sara/fonts/material/material.ttf') format('truetype'),
      url('https://civil808.com/sites/all/themes/sara/fonts/material/material.svg#materialdesigniconsregular') format('svg');
    font-weight:normal;
    font-style:normal;
  }
</style>

<style type="text/css">
    .sissors {
      background-image: url(/sites/all/themes/sara/images/sissor.png);
      position: absolute;
      left: 0px;
      width: 20px;
      height: 21px;
      background-size: cover;
      bottom: -10.7px;
    }
    .city-name > p{
      color: #bdbdbd;
      direction: ltr;
      margin: 86px 0 0 0;
    }
    .tickets{
      text-align: center;
      font-size: 13px !important;
      direction: rtl !important;
      padding-bottom: 30px;
      border-bottom: 2px dotted #aaa;
      position: relative;
      margin: 0;
      page-break-after: always;
    }
    .tickets .blit{
      display: block;
      width: 700px;
      padding: 15px 15px 0 15px;
      background: #fff;
      border-radius: 5px;
      color: #555 !important;
      height: 275px;
      align-items: stretch;
      margin: 10px auto 20px auto;
      position: relative;
      z-index: 10;
      border: 1px solid #b9b9b9;
    }
    .gerdali {
      position: absolute;
      top: calc( 50% - 25px);
      right: -28px;
      width: 50px;
      height: 50px;
      background-color: #ffffff;
      border-radius: 50%;
      transform: rotate(0deg);
      border: 1px solid #b9b9b9;
    }
    .gerdali:before {
      content: "";
      position: absolute;
      width: 30px;
      height: 107%;
      top: -2px;
      right: -4.999999px;
      background: #ffffff;
      border-radius: 0 50% 50% 0;
    }
    .tickets .blit div.city-name span {
      width: 80px;
      display: block;
      margin: 109px auto 0 auto;
    }
    .tickets .blit div.city-name {    
      width: 73px;
      display: inline-block;
      color: #9C27B0;
      font-weight: 500;
      font-size: 20px;
      padding: 0 15px 0 20px;
      position: relative;
      box-sizing: content-box;
      margin-left: 20px;
      border-left: 4px dotted #aaa;
      height: 260px;
      vertical-align: top;
      text-align: center;
    }
    p.text {    
      font-size: 19px;
      text-align: right;
      line-height: 32px;
      color:black;
    }
    .tarikh,
    .mablagh,
    .makan,
    .zaman,
    .nam {
        font-family: fanum ,iransans,tahoma !important;
        margin: 10px 7px;
        text-align: right;
        line-height: 23px;
        color:black;
    }
    .nam{    
      margin-bottom: 15px;
      margin-right: 5px;
      margin-left: 0px;
      white-space: nowrap;
      margin-top: 2px;
    }
    .tarikh > span ,
    .mablagh > span,
    .zaman > span,
    .makan > span {
        float: right;
        margin-left: 6px;
        content: " ";
        background-image: url(/sites/all/themes/sara/images/invoice-ico.JPG);
        width: 20px;
        height: 22px;
        background-position: center -7px;
        background-size: 39px;
        display:none;
    }
    .mablagh {
      font-size: 25px;
      color: #4CAF50;
      margin-right: 10px;
      margin-top: 20px;
    }
    .zaman > span{
        background-position: center 29px;
    }
    .makan > span{
        background-position: center -44px;
    }
    span.sabtenam {
        position: absolute;
        top: calc( 50% - 15px );
        transform: rotate(-90deg);
        left: 12px;
        font-size: 18px;
        color: #9E9E9E;
    }
    span.sabtenam:after {
        content: "\f141";
        transform: rotate(90deg);
        display: inline-block;
        position: absolute;
        right: 7px;
        top: -31px;
        font-family: mat;
        font-size: 41px;
    }
    .tickets .blit > div img{
      display: inline-block;
      vertical-align: bottom;
    }
    .left-side{
      display: inline-block;
      vertical-align: top;
      width: 563px;
      height: 275px;
      overflow: hidden;
    }
    .in_inside {
      display: inline-block;
      margin-bottom: 24px;
    }
    .maps img{
      display:block;
      margin:auto;
    }
    .maps p{
      margin: 13px auto;
    }
    .get-ticket{
      text-align: center;
      margin: 55px 0 40px 0;
      display: inline-block;
      width: 100%;
    }
    .get-ticket a{
      padding: 20px 40px;
      border-radius: 30px;
      background: #fff;
      color: #555 !important;
      box-shadow: rgba(0,0,0,0.117647) 0px 1px 6px, rgba(0,0,0,0.117647) 0px 1px 4px;
      font-size: 15px;
      text-decoration: none;
      border:1px solid #eee;
    }
    .get-ticket a:before {
      content: "\f518";
      font-family: mat;
      font-size: 30px;
      vertical-align: middle;
      margin: -10px -35px -10px 15px;
      border: 1px solid #aaa;
      border-radius: 50%;
      width: 56px;
      display: inline-flex;
      height: 56px;
      color: #F44336;
      align-items: center;
      justify-content: center;
    }
</style>

<style type="text/css">
  * {
    font-family: iransans,tahoma !important;
  }
  #center .center{
    margin: -2px auto 0 auto;
    padding: 0;
    border: 0;
    font-size: 14px;
    font: inherit;
    direction: rtl;
    vertical-align: baseline;
    line-height: 1;
    background: #f7f7f7;
    color: #444;
    width: 100%;
    border-radius: 2px;
  }
  #header-mail{
	  margin: 2px auto;
    padding: 15px 0;
    border: 0;
    font-size: 100%;
    font: inherit;
    direction: rtl;
    vertical-align: baseline;
    text-align: center;
    display: block;
    overflow: hidden;
    width: 85%;
  }
  #header-mail img{
	  max-width: 100%;
    width: 127.2px;
    min-height: auto!important;
  }
  #main{
	  margin: 0 auto 0px;
    padding: 30px 30px;
    border: 1px solid #e2e2e2;
    font-size: 100%;
    font: inherit;
    direction: rtl;
    vertical-align: baseline;
    background: #fff;
    overflow: hidden;
    border-radius: 2px;
    line-height: 30px;
    box-sizing: border-box;
    text-align: justify;
	  width: 77%;
  }
  #footer-mail{
	  direction: rtl;
    font-size: 100%;
	  margin: -5px auto 0 auto;
    font: inherit;
    vertical-align: baseline;
    text-align: center;
    display: block;
    overflow: hidden;
    width: 100%;
    padding-bottom: 20px;
    padding: 0;
    border: 0;
    background-color: #f7f7f7;
    padding: 20px 0;
  }
  .first-row a{
	  font-size: 20px;
    color: black;
    text-decoration: blink;
    padding-bottom: 20px;
    display: block;
  }
  .socialss a{
	  margin:0px 10px;
  }
  .sender {
    word-spacing: 4px;
  }
  .sender br{
  display: none;
  }
  .sender br:nth-child(4) {
    display: block;
  }
  .logo img {
    width: 150px;
    padding: 10px 40px;
  }
  #center #main{
    direction: rtl;
    font-size: small;
  }
</style>

<div id="center">

<?php
  function print_it_nice($variable){
    echo '<pre>';
    print_r($variable);
    echo '</pre>';
  }

  $print_blit = false;
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  $c = webform_get_submissions(array('nid' => '17894', 'uid' => $order->uid));
  if( sizeof($c) != 0 ){
    $a = array();
    foreach($c as $row=>$val){
      $bb = unserialize($val->data[1][0]);
      foreach($bb as $b){
        $a[$b[6]][$b[5]][] = $b;
      }
    }
    if(isset($a[$order->order_id])){
      $print_blit = true;
    }
  }
  
  $tehran_i = 0;
  $mashhad_i = 0;
  $esfehan_i = 0;
  $tabriz_i = 0;

  /*$city_name = array();
  foreach( $a as $a_key => $a_value ){
    if( $a_key == 7637 ){
      foreach( $a_value as $a_key_city => $a_city_value ){
        foreach( $a_city_value as $a_city_data ){
          //$city_name[$a_key_city] = $a_city_data["1"];
          print "{$a_key_city} : {$a_city_data["1"]} </br>";
        }
      }
    }
  }*/
  
  
  $cities = array();
  $is_email = true;
  $url_last = substr( $_SERVER['REQUEST_URI'] , strlen($_SERVER['REQUEST_URI']) - 5, strlen($_SERVER['REQUEST_URI']) - 2 );
  if( $url_last === "print"){
    $is_email = false;
  }
  $print_once = false;
  foreach( $products as $product ){
    if($product->nid == 17782){
      if($print_blit == true && $is_email == false){
        if(!$print_once){
          print '<div class="tickets">';
          $print_once = true;
        }
        for( $i = 0 ; $i < $product->qty ; $i++){
?>
  <div class="blit">
    <?php if(!$is_email): ?>
      <div class="gerdali"></div>
    <?php endif; ?>
    <div class="city-name">
      <span> 
        <?php 
        $city = reset($product->data['attributes']['شهر']);
        print_r($city);
        ?>
      </span>
      <p>#
        <?php
          print $order->order_id;
        ?>
      </p>
    </div>
    <div class="left-side">
      <p class="text"> بلیط شرکت در چهارمین همایش ملی طراحی عملکردی سازه ها </p>
      <?php 
        switch ($city) {
          case "تهران":{
            print "<div class='in_inside' style='width: 353px;'>
            <div class='nam'><b> نام و نام خانوادگی :  </b> {$a[$order->order_id]['تهران'][$tehran_i][1]} </div>
            <div class='tarikh'><span></span> شنبه 28 بهمن 1396 </div>
            <div class='makan'><span></span> هتل المپیک </div>
            <div class='zaman'><span></span> ساعت 4 تا 8 عصر </div>
            <div class='mablagh'> 200 هزار تومان </div>
            </div>
            <img src='/sites/all/themes/sara/images/azadi-tower.png' width='180px' height='auto' style='opacity: 0.3;margin-left: 20px;'>";
            $tehran_i++;
            break;
          }
          case "مشهد":{
            print "<div class='in_inside' style='width: 228px;'>
            <div class='nam'><b> نام و نام خانوادگی :  </b> {$a[$order->order_id]['مشهد'][$mashhad_i][1]} </div>
            <div class='tarikh'><span></span> سه شنبه 24 بهمن 1396 </div>
            <div class='makan'><span></span> هتل پردیسان مشهد </div>
            <div class='zaman'><span></span> ساعت 4 تا 8 عصر </div>
            <div class='mablagh'> 100 هزار تومان </div>
            </div>
            <img src='/sites/all/themes/sara/images/mashad2.png' width='330px' height='auto' style='opacity:0.6;margin-top: -115px;'>'";
            $mashhad_i++;
            break;
          }
          case "تبریز":{
            print "<div class='in_inside' style='width: 323px;'>
            <div class='nam'><b> نام و نام خانوادگی :  </b> {$a[$order->order_id]['تبریز'][$tabriz_i][1]} </div>
            <div class='tarikh'><span></span> پنج شنبه 26 بهمن 1396 </div>
            <div class='makan'><span></span> هتل پارس تبریز </div>
            <div class='zaman'><span></span> ساعت 3 تا 7 عصر </div>
            <div class='mablagh'> 100 هزار تومان </div>
            </div>
            <img src='/sites/all/themes/sara/images/tabriz.png' width='200px' height='auto' style='opacity: 0.7;margin-left: 30px;'>";
            $tabriz_i++;
            break;
          }
          case "اصفهان":{
            print "<div class='in_inside' style='width: 222px;'>
            <div class='nam'><b> نام و نام خانوادگی :  </b> {$a[$order->order_id]['اصفهان'][$esfehan_i][1]} </div>
            <div class='tarikh'><span></span> یک شنبه 29 بهمن 1396 </div>
            <div class='makan'><span></span> هتل پارسیان کوثر </div>
            <div class='zaman'><span></span> ساعت 3 تا 7 عصر </div>
            <div class='mablagh'> 100 هزار تومان </div>
            </div>
            <img src='/sites/all/themes/sara/images/esfehan2.png' width='330px' height='auto' style='opacity:0.6;'>";
            $esfehan_i++;
            break;
          }
        }
      ?>
    </div>
  </div>
<?php 
      }
      array_push($cities , $city);
      }
      else{
        print '<div class="get-ticket"><a href="https://civil808.com/form/complete-information" target="_blank">برای تکمیل اطلاعات و پرینت بلیط <span>همایش طراحی عملکردی</span> کلیک کنید </a></div>';
        break;
      }
    }
  }
  if ($print_once):
    print '<div class="maps">';
    $cities = array_unique($cities);
    foreach ($cities as $eachcity){
      switch($eachcity){
        case "تهران":{
          print '<p> تهران | هتل المپیک </p>';
          print '<div><iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d21789.112427786557!2d51.25387721890719!3d35.72693318052376!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x3f8dfc83a8f40b7d%3A0x671b8897d271da91!2sOlympic+Hotel!5e0!3m2!1sen!2s!4v1516109408607" width="700" height="400" frameborder="0" style="border:0" allowfullscreen></iframe></div>';
          break;
        }
        case "مشهد":{
          print '<p> مشهد | هتل پردیسان </p>';
          print '<div><iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d4547.325595825614!2d59.53424814817398!3d36.30151992776468!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x3f6c9248d3f8d5f5%3A0xe660cb8c30824e9d!2sPardisan+Hotel!5e0!3m2!1sen!2s!4v1516110055455" width="700" height="400" frameborder="0" style="border:0" allowfullscreen></iframe></div>';
          break;
        }
        case "تبریز":{
          print '<p>  تبریز | هتل پارس </p>';
          print '<div><iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d14951.126116948431!2d46.35774531364191!3d38.02174912955888!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x401a19f0d4b10319%3A0x32282d4434a3aa8d!2sPars+Hotel!5e0!3m2!1sen!2s!4v1516110002895" width="700" height="400" frameborder="0" style="border:0" allowfullscreen></iframe></div>';
          break;
        }
        case "اصفهان":{
          print '<p> اصفهان | هتل پارسیان کوثر </p>';
          print '<div><iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d3359.6509807836837!2d51.663194726176705!3d32.64211678673048!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x3fbc360a5b7dc6b5%3A0x7993a86d010415aa!2sParsian+Kowsar+Hotel!5e0!3m2!1sen!2s!4v1516109797294" width="700" height="400" frameborder="0" style="border:0" allowfullscreen></iframe></div>';
          break;
        }
      }
    }
    print '</div><div class="sissors"></div></div>';
  endif;
?>
<div class="center">
  <div id="header-mail">
		<a href="https://civil808.com"  target="_blank">
		  <img src="https://civil808.com/sites/all/themes/sara/logo.png" alt="">
		</a>
	</div>
	<div id="main">
    <table width="95%" border="0" cellspacing="0" align="center">
    <tr>
      <td>
        <table width="100%" border="0" cellspacing="0"  align="center">
          <tr valign="top">
            <td>
              <?php if ($thank_you_message): ?>
              <p><b><?php print t('Thanks for your order, !order_first_name!', array('!order_first_name' => $order_first_name)); ?></b></p>
              <?php if (isset($order->data['new_user'])): ?>
              <p><b><?php print t('An account has been created for you with the following details:'); ?></b></p>
              <p><b><?php print t('Username:'); ?></b> <?php print $order_new_username; ?><br />
              <b><?php print t('Password:'); ?></b> <?php print $order_new_password; ?></p>
              <?php endif; ?>
              <p><b><?php print t('Want to manage your order online?'); ?></b><br />
              <?php print 'اگر نیاز به بررسی وضعیت سفارش خود را دارید، لطفا در صفحه ی اصلی civil808.com بر روی منو کاربری خود (بالای صفحه سمت چپ) کلیک کرده و پس از باز شدن منو ، با انتخاب گزینه ی "پیگیری سفارش ها" وارد صفحه ی مورد نظر شوید یا با استفاده از لینک زیر وارد شوید : ' ; ?>
              <br /><?php print $site_login_link; ?></p>
              <?php endif; ?>
              <table cellpadding="4" cellspacing="0" border="0" width="100%">
                <tr>
                  <td nowrap="nowrap" style="border-bottom: 3px solid #a5a;"></td>
                  <td nowrap="nowrap" style="border-bottom: 3px solid #a5a;"></td>
                </tr>
                <tr>
                  <td colspan="2">
                    <table border="0" cellpadding="1" cellspacing="0" width="100%" style="font-size: small;">
                    <tr>
						            <td>
							            <table width="100%" cellspacing="0" cellpadding="0" style="background-color: #fdfdfd;border: 1px solid #eee;border-radius: 5px;margin-left: 1%;box-sizing: border-box;width: 99%;margin-bottom: 5px;padding: 5px 15px;">
								            <tr>
								              <?php if ($shippable): ?>
								              <td valign="top" width="50%">
									              <?php print $order_shipping_address; ?><br />
								              </td>
								              <?php endif; ?>
								            </tr>
							            </table>
						            </td>
						            <td valign="top">
							            <table style="  border: 1px solid #eee;  border-radius: 5px;  margin-left: 1%;  box-sizing: border-box;  width: 99%;background-color: #fdfdfd;  margin-bottom: 5px;  padding: 5px 15px;display: inline-block;">
								            <tbody style="  width: 100%;  display: block;">
									            <tr>
										            <td nowrap="nowrap" style="  width: 100%;  display: block;">
											            <b><?php print t('Order #:'); ?></b>
											            <span style="padding-right: 5px;"><?php print $order_link; ?></span>
										            </td>
									            </tr>
									            <tr>
										            <td nowrap="nowrap" style="  width: 100%;  display: block;">
											            <b><?php print t('Order Date: '); ?></b>
											            <span style="padding-right: 5px;"><?php print $order_created; ?></span>
										            </td>
									            </tr>
									            <tr>
										            <td width="98%" style="  width: 100%;  display: block;">
											            <b><?php print t('Payment Method:'); ?></b>
											            <span style="padding-right: 5px;"><?php print $order_payment_method; ?></span>
										           </td>
									            </tr>
									            <tr>
										            <td nowrap="nowrap" style="  width: 100%;  display: block;">
											            <b><?php print t('E-mail:'); ?></b>
											            <span style="padding-right: 5px;"><?php print $order_email; ?></span>
										            </td>
									            </tr>
								            </tbody>
							            </table>
						            </td>
                    </tr>
                    <tr>
                        <td colspan="2">
						              <table width="100%" style="  text-align: center;border-collapse: collapse;">
							              <thead style="background: #f5f9f9;  line-height: 34px;  font-size: 15px;">
								              <tr>
									              <th style="border: 1px solid #eee;">
										              <span>ردیف</span>
									              </th>
									              <th style="border: 1px solid #eee;">
										              <span>کد محصول</span>
									              </th>
									              <th style="border: 1px solid #eee;">
										              <span>شرح محصول یا خدمات</span>
									              </th>
									              <th style="border: 1px solid #eee;">
									              	<span>توضیحات</span>
									              </th>
									              <th style="border: 1px solid #eee;">
									              	<span>تعداد</span>
									              </th>
									              <th style="border: 1px solid #eee;">
									              	<span>مبلغ واحد(تومان)</span>
									              </th>
									              <th style="border: 1px solid #eee;">
									              	<span>مبلغ کل(تومان)</span>
									              </th>
								              </tr>
							              </thead>
							              <tbody style="line-height: 35px;">
								              <?php $index = 1;?>
								              <?php foreach ($products as $product): ?>
								            	<tr>
								            		<td style="border: 1px solid #eee;">
								            			<span><?php print $index; $index++;?></span>
								            		</td>
								            		<td style="border: 1px solid #eee;">
								            			<span><?php print $product->model; ?></span>
								            		</td>
								            		<td style="border: 1px solid #eee;">
								            			<span><?php print $product->title; ?></span>
								            		</td>
								            		<td style="border: 1px solid #eee;">
								            			<span><?php print $product->details; ?></span>
								            		</td>
								            		<td style="border: 1px solid #eee;">
								            			<span><?php print $product->qty; ?></span>
								            		</td>
								            		<td style="border: 1px solid #eee;">
								            			<span><?php print $product->individual_price; ?></span>
								            		</td>
								            		<td style="border: 1px solid #eee;">
								            			<span><?php print $product->total_price; ?></span>
								            		</td>
								            	</tr>
								              <?php endforeach; ?>
							              </tbody>
						              </table>
                        </td>
                    </tr>
                    <tr style="font-weight: bold;   height: 40px;">
                        <td nowrap="nowrap" width="84%" style="text-align: left;">
                          <span style="  font-size: 15px;  padding: 4px 10px;  width: 140px;  text-align: right;  box-sizing: border-box;  display: inline-block;"><?php print t('Products Subtotal:'); ?>&nbsp;</span>
                        </td>
                        <td style="min-width: 215px;  text-indent: 15px;">
                          <span><?php print $order_subtotal; ?></span>
                        </td>
                    </tr>
                    <tr>
                        <td style="border-top: 1px solid #eee !important; height: 15px;"></td>
                        <td style="border-top: 1px solid #eee !important; height: 15px;"></td>
                    </tr>
                    <?php if ($shipping_method && $shippable): ?>
                    <tr>
                        <td nowrap="nowrap" style="text-align:right;">
                          <span style="  font-size: 15px;  padding: 10px;  display: inline-block;  border-right: 4px solid #eee;  width: 140px;   text-align: right;  box-sizing: border-box;"><b><?php print t('Shipping Method:'); ?></b><span>
                        </td>
                        <td width="98%" style="  display: none;">
                          <span><?php print $order_shipping_method; ?><span>
                        </td>
                    </tr>
                    <?php endif; ?>
                    <?php foreach ($line_items as $item): ?>
                    <?php if ($item['type'] == 'subtotal' || $item['type'] == 'total')  continue; ?>
                    <tr>
                        <td nowrap="nowrap" style="text-align: left;">
                          <span style="  font-size: 15px;  padding: 4px 10px;  width: 140px;  text-align: right;  box-sizing: bor                       display: inline-block;"><?php print $item['title']; ?>:<span>
                        </td>
                        <td style="min-width: 215px;  text-indent: 15px;">
                          <span><?php print $item['formatted_amount']; ?><span>
                        </td>
                    </tr>
                    <?php endforeach; ?>
                    <tr>
                        <td style="border-top: 1px solid #eee !important; height: 15px;"></td>
                        <td style="border-top: 1px solid #eee !important; height: 15px;"></td>
                    </tr>
                    <tr>
                        <td nowrap="nowrap" style="text-align: left;">
                          <span style="  font-size: 15px;  padding: 4px 10px;  width: 140px;  text-align: right;  box-sizing: border-box;   display: inline-block;"><b><?php print t('Total for this Order:'); ?>&nbsp;</b></span>
                        </td>
                        <td style="min-width: 215px;  text-indent: 15px;">
                          <b><?php print $order_total; ?></b>
                        </td>
                    </tr>
                    </table>
                  </td>
                </tr>
              </table>
            </td>
          </tr>
        </table>
      </td>
    </tr>
    </table>
  </div>
</div>
</div>



