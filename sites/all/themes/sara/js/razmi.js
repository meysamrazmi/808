var $ = jQuery;
$(document).ready(function () {
	
$(window).scroll(function () {
    if ($(this).scrollTop() > 100) {
        $('.pane-menu-main-civil').addClass("topfix");
    } else {
        $('.pane-menu-main-civil').removeClass("topfix");
    }
});
if($('#backtotop').length == 0) {
	$("body").append("<div id='backtotop'>بالای صفحه</div>");
}
$(window).scroll(function() {
	if($(this).scrollTop() > 500) {
		$('#backtotop').fadeIn();	
	} else {
		$('#backtotop').fadeOut();
	}
});

$('#backtotop').click(function() {
    $("html, body").bind("scroll mousedown DOMMouseScroll mousewheel keyup", function() {
		$('html, body').stop();
	});
	$('html,body').animate({ scrollTop: 0 }, 1200);
	return false; 
});
/*-------------------------------------------initial part------------------------------------------------------------------------------*/
/*hiding tabs*/
if($('.tabs').html().length < 40 ){
	$('.tabs').css({'display' : 'none'});
}
if($('body.no-container').length){
	$('.container.main').removeClass('container');
}
/*-------------------------------------------------------------------------------------------------------------------------------*/

if($('.page-saze .view-all-new').length){
	if(!$('.page-saze .view-all-new .more-link').length){
		$('.page-saze .view-all-new').append('<div class="more-link"><a href="/news">+ مشاهده موارد بیشتر  </a></div>');
	}
}
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*this block is for securing a little more courses registration that user couldnt change the prices*/
if($('#node-1997').length){
	var selected_text = $("#edit-submitted-courseinfo-course-cost option:selected").text();
	var selected_value = document.getElementById("edit-submitted-courseinfo-course-cost").value;
	document.getElementById("edit-submitted-courseinfo-course-cost").innerHTML = '<option value="'+selected_value+'">'+selected_text+'</option>';
	
	selected_text = $("#edit-submitted-courseinfo-course-name option:selected").text();
	selected_value = document.getElementById("edit-submitted-courseinfo-course-name").value;
	document.getElementById("edit-submitted-courseinfo-course-name").innerHTML = '<option value="'+selected_value+'">'+selected_text+'</option>';	
	
	selected_text = $("#edit-submitted-courseinfo-enabaled option:selected").text();
	selected_value = document.getElementById("edit-submitted-courseinfo-enabaled").value;
	document.getElementById("edit-submitted-courseinfo-enabaled").innerHTML = '<option value="'+selected_value+'">'+selected_text+'</option>';	
}
/*-------------------------------------------------------------------------------------------------------------------------------*/
$('.messages').click(function() {
	$(this).css({
		'display': 'none'
	});
});
/*-------------------------------------------------------------------------------------------------------------------------------*/
$(function() {
  /* Generic selector to be used anywhere*/
  $("div#eng-nav ul li a").click(function(e) {
	/* Get the href dynamically*/
	var destination = $(this).attr('href');
	/* Prevent href=“#” link from changing the URL hash (optional)*/
	e.preventDefault();
	/* Animate scroll to destination*/
	$('html, body').animate({
	  scrollTop: ($(destination).offset().top - 100)
	}, 1000);
  });
});
/*-------------------------------------------------------------------------------------------------------------------------------*/
$(function() {
  /* Generic selector to be used anywhere*/
  $("#pbd-panel ul.pbd-menu a").click(function(e) {
	/* Get the href dynamically*/
	var destination = $(this).attr('href');
	/* Prevent href=“#” link from changing the URL hash (optional)*/
	e.preventDefault();
	/* Animate scroll to destination*/
	$('html, body').animate({
	  scrollTop: ($(destination).offset().top)
	}, 1000);
  });
});

// $(document).bind('scroll',function(e){
$(window).scroll(function (e) {
	$('#pbd-panel .panel-pane').each(function(){
		if ($(this).offset().top < window.pageYOffset + 150 &&  $(this).offset().top + $(this).height() > window.pageYOffset + 150 ) {
			// window.location.hash = $(this).attr('id');
			// var urlId = '#' + $(this).attr('id'); 
			// history.replaceState(null, null, urlId);

			$('#pbd-panel ul.pbd-menu a[href$="' + $(this).attr('id') + '"]').parent().prev().removeClass('active');
			$('#pbd-panel ul.pbd-menu a[href$="' + $(this).attr('id') + '"]').parent().addClass('active');
			$('#pbd-panel ul.pbd-menu a[href$="' + $(this).attr('id') + '"]').parent().next().removeClass('active');
		
		}
	});
});
/*-------------------------------------------------------------------------------------------------------------------------------*/
$(window).scroll(function(e) {
	sct = $(window).scrollTop();
	
	if(sct>10){
		if(!$('#wheel').hasClass('fade')){
			$('#wheel').addClass('fade');
			$('#wheel').stop(true,true).fadeOut();
		}
	}else{
		if($('#wheel').hasClass('fade')){
			$('#wheel').removeClass('fade');
			$('#wheel').stop(true,true).fadeIn();
		}
	}
});
/*-------------------------------------------------------------------------------------------------------------------------------*/
if(screen.width >= 767){
var eng_nav_fixed = function(x){
$(window).scroll(function(e) {
	sct = $(window).scrollTop();
	if (sct > (x.parent().offset().top - 80) ) {
			x.css({'position': 'fixed','top':'50px'});
		} else {
			x.css({'position': 'absolute','top':'0px'});
	}
});
}
var eng_nav_fixed_do = function(){
	if($('.eng808-nav-exclusive').length) eng_nav_fixed($('.eng808-nav-exclusive'));
	if($('.eng808-nav-foreign').length) eng_nav_fixed($('.eng808-nav-foreign'));
	if($('.eng808-nav-exam').length) eng_nav_fixed($('.eng808-nav-exam'));
	if($('.eng808-nav-courses').length) eng_nav_fixed($('.eng808-nav-courses'));
	if($('.eng808-nav-news').length) eng_nav_fixed($('.eng808-nav-news'));
	if($('.eng808-nav-shop').length) eng_nav_fixed($('.eng808-nav-shop'));
	if($('.eng808-nav-sourses').length) eng_nav_fixed($('.eng808-nav-sourses'));
}
if($('.eng808-nav').length){
	eng_nav_fixed_do();
}
} else{
$('.page-eng .panels-flexible-region-15-courses').css({ "margint-top" : $('.panels-flexible-region-15-nav_courses').height() });
$('.page-eng .panels-flexible-region-15-course1').css({ "margint-top" : $('.panels-flexible-region-15-nav_courses').height() });
$('.page-eng .panels-flexible-region-15-course1_ ').css({ "margint-top" : $('.panels-flexible-region-15-nav_courses').height() });
}
/*-------------------------------------------------------------------------------------------------------------------------------*/
if ($('.all-contents').length){
	var totop = $('.all-contents').offset().top;
	var totop = totop - 600;
	$(window).scroll(function () {
		if ($(this).scrollTop() > totop) {
			if (!$('.all-contents').hasClass('counting')){		
/*			} else{*/
				$('.all-contents').addClass('counting');
				countup($('.all-contents'));
				countup($('.created-contents'));
				countup($('.our-coworker'));
				countup($('.all-users'));
				countup($('.our-spicials'));
				countup($('.our-vip'));
			}
		}
	});
}
/*-------------------------------------------------------------------------------------------------------------------------------*/
if ($('#menu-toggle').length){
	var menu = $('.page-civil #content .pane-menu-main-civil');
	$('#menu-toggle').click(function () {
			if (!menu.hasClass('opend')){
				$(this).addClass('opend');
				menu.addClass('opend');
				menu.css({ 'height' : '100%' , 'opacity': '1' });
			} 			else {
				$(this).removeClass('opend');
				menu.removeClass('opend');
				setTimeout(menu.css({ 'height' : '0' , 'opacity': '0' }), 500);
			}
	});
}
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*front page*/
/*for front shop section*/
if($('.view-conference-news').length) 	applyHeight($('div#views_slideshow_cycle_teaser_section_conference_news-block_3') , $('.view-conference-news .views-slideshow-cycle-main-frame-row') , 0);
/*--------*/
$('.page-civil .main-four .views-row').each(function(){
	if(!$(this).find('.views-field-field-posterfilm').length){
		$(this).find('.views-field-nothing').css({'display' : 'none'});
	}
});

/*-------------------------------------------------------------------------------------------------------------------------------*/
$('.tb-megamenu .nav-collapse').css({ 'max-height' : screen.height + 5 });
$('.tb-megamenu-button').addClass('first');
$('.tb-megamenu-button').click(function() {
  if($(this).hasClass('first')) {
	$(this).removeClass('first');
  }
});
/*-------------------------------------------------------------------------------------------------------------------------------*/
$('.menu-mlid-6400').replaceWith('<li data-id="8832" data-level="1" data-type="menu_item" data-alignsub="justify" data-group="0" data-hidewcol="0" data-hidesub="0" class="tb-megamenu-item level-1 mega mega-align-justify dropdown leaf" style="position: inherit;"> <a href="/search/google" class="dropdown-toggle">جستجو<span class="caret"></span>          </a>  <div data-class="" data-width="" class="tb-megamenu-submenu dropdown-menu mega-dropdown-menu nav-child">  <div class="mega-dropdown-inner">    <div class="tb-megamenu-row row-fluid">  <div data-showblocktitle="0" data-class="" data-width="12" data-hidewcol="" id="tb-megamenu-column-35" class="tb-megamenu-column span12  mega-col-nav">  <div class="tb-megamenu-column-inner mega-inner clearfix">        <div data-type="block" data-block="search--form" class="tb-megamenu-block tb-block tb-megamenu-block">  <div class="block-inner">    <div id="block-search-form" class="block block-search odd">      <div class="content">    <form class="google-cse" action="/search/google" method="post" id="search-block-form--2" accept-charset="UTF-8"><div><div class="container-inline">      <h2 class="element-invisible">فرم جستجو</h2>    <div class="form-item form-type-textfield form-item-search-block-form">  <label class="element-invisible" for="edit-search-block-form--4">جستجو </label> <input title="عبارتی را که می&zwnj;خواهید جستجو گردد را وارد نمایید." type="text" id="edit-search-block-form--4" name="search_block_form" value="" size="15" maxlength="128" class="form-text"></div><div class="form-actions form-wrapper" id="edit-actions--3"><input type="submit" id="edit-submit--2" name="op" value="جستجو" class="form-submit"></div><input type="hidden" name="form_build_id" value="form-uJGhrcfjItMclRoB2SX-01xel0dQRoW3-ATj7uAXlOQ"><input type="hidden" name="form_token" value="DOUoK0RVXRvmr2GKLHDNcKnjvNmaJJV3QLckKCXagns"><input type="hidden" name="form_id" value="search_block_form"></div></div></form>  </div></div>  </div></div>  </div></div></div>  </div></div></li>');
/*-------------------------------------------------------------------------------------------------------------------------------*/
$('.add-to-cart .form-actions').click(function(){
	$(this).children('input')[0].click();
});
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*
* برای پاک کردن آیتم های وب فرمی که به سبد خرید اضافه می شوند
* و قسمت دوم هم برای اینکه قسمت before هم لینک دار باشد
* قسمت سوم هم برای اینکه تو مرحله تسویه کلید "بازگشت به سبد خرید" وجود داشته باشد.
*/
$('div#cart-form-pane td.remove').click(function(){
	if( $(this).find('a').length ){
		$(this).find('a')[0].click();	
	}
	$(this).children('input')[0].click();
});
$('.uc-cart-checkout-form .form-actions #edit-cancel').replaceWith('<a href="/cart" id="edit-cancel" class="back-to-cart">بازگشت به سبد خرید</a>');
$('tr.line-item-not_vip td').click(function(){
	$(location).attr('href', '/landing/vip')
})
/*-------------------------------------------------------------------------------------------------------------------------------*/
prices();
/*thid line code os for adding class to every backend item*/
$('.field-name-field-backend').find('.field-item').each(function(){
	$(this).parent().addClass($(this).text().replace(/ /gi, "-"));
});

/*-------------------------------------------------------------------------------------------------------------------------------*/
/*
*
*برای تخفیفات نوروزی آموزشگاه بخش نرم افزار
*
$('.page-software .views-field-field-edu-price').each(function(i){
	var list_price_t = $(this).find('.field-content').text();
	var list_price = parseInt(list_price_t);
	var real_price = function(num , length){
		if(length > 4 && length < 8){
			num = num *1000;
		}else if(length > 8 ){
			num = num * 1000000;
		}
		return num;
	}
	var real_price_display = function(num){
		var price_display= "";
		if(num > 100000000){
			price_display = num.toString().substring(0,3) + ','+num.toString().substring(3,6) + ','+num.toString().substring(6,9);
		}else	if(num > 10000000){
			price_display = num.toString().substring(0,2) + ','+num.toString().substring(2,5) + ','+num.toString().substring(5,8);
		}else	if(num > 1000000){
			price_display = num.toString().substring(0,1) + ','+num.toString().substring(1,4) + ','+num.toString().substring(4,7);
		}else if(num > 100000){
			price_display = num.toString().substring(0,3) + ','+num.toString().substring(3,6);
		}else if(num > 10000){
			price_display = num.toString().substring(0,2) + ','+num.toString().substring(2,5);
		}else if(num > 1000){
			price_display = num.toString().substring(0,1) + ','+num.toString().substring(1,4);
		}else {
			price_display = num.toString();
		}
		return price_display;
	}
	list_price = real_price(list_price , list_price_t.length);
	list_price = (list_price*0.8);
	var price_dis = real_price_display(list_price);
	var takhfif = $(this).html();
	$(this).html(takhfif + '<div class="college-takhfif"><span class="college-takhfif-label">هزینه کلاس برای شما: </span><span class="college-takhfif">' + price_dis + ' ریال</span></div>');
});*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*
*برای تیک تخفیف ثبت نام همایش سقف های پس کشیده
*/
$('#edit-submitted-2-5708-conf-posttensioning-register').prop('checked', true);
$('#edit-submitted-sharif-takhfif-1').change(function() {
	if ($(this).is( ":checked" ) ) {
		$('#edit-submitted-2-5708-conf-posttensioning-register').prop('checked', false);
		$('#edit-submitted-2-5948-conf-posttensioning-register-sharif').prop('checked', true);
	}
	else{
		$('#edit-submitted-2-5708-conf-posttensioning-register').prop('checked', true);
		$('#edit-submitted-2-5948-conf-posttensioning-register-sharif').prop('checked', false);
	}
}); 
/*-------------------------------------------------------------------------------------------------------------------------------*/
var registerr = function(){
	if($.urlParam('product') != null ){
		$('#edit-submitted-courses-products input#edit-submitted-courses-products-' + $.urlParam('product')).prop('checked',true);
	}
}
if($('.page-form.page-college-register').length){
	setTimeout(registerr, 500);
}
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*this section is for each course side bar block*/
if($('.views-field-field-product').length){
	$('.views-field-field-link').each(function(){
		$(this).css({display : 'none'});
	});
}
if($('.node-product.view-mode-question .display-price').length){
	$('.views-field-field-edu-price').each(function(){
		$(this).css({display : 'none'});
	});
}
$('.node-product.view-mode-question .attribute .form-checkbox').each(function(){
	$(this).prop('checked',true);
});
$('.node-product.view-mode-question .attribute .form-item:last-child > .form-checkbox').each(function(){
	$(this).prop('checked',false);
	$(this).click();
});
/*-------------------------------------------------------------------------------------------------------------------------------*/
klickmore($('.node-product-kit .field-name-body') , 300);
klickmore($('.node-product .field-name-body') , 300);
klickmore($('.panels-flexible-row-11-9 .panels-flexible-region') , 250);
klickmore($('.related.videos') , 500);
/*-------------pedia--------------*/
/*if( $( ".node-type-architect").length ){
	if ( $(".field-type-node-reference").length ){
		klickmore($('.page-pedia.page-node .field-name-field-body') , 200);
	}
}*/
klickmore($('#block-mefibs-mefibs-glrnew-page-2-f #edit-mefibs-form-f-dakheli-wrapper > .views-widget') , 250);
klickmore($('#block-mefibs-mefibs-glrnew-page-2-f #edit-mefibs-form-f-noesakht-wrapper > .views-widget') , 250);
klickmore($('.page-college #mini-panel-college_top > div > div') , 250);


$('.klick-for-more').click(function(){
	if($(this).hasClass('closed')){
		$(this).parent().css({'max-height' : $(this).parent().children('div:nth-child(1)').height() + 100 , 'padding-bottom':'100px'});
		$(this).html('<span>بستن</span>');
		$(this).removeClass('closed');
		$(this).addClass('opend');
	}else{
		if($(this).hasClass('150')){
			$(this).parent().css({'max-height' : 150 });
		}else if($(this).hasClass('200')){
			$(this).parent().css({'max-height' : 200 });
		}else if($(this).hasClass('250')){
			$(this).parent().css({'max-height' : 250 });
		}else if($(this).hasClass('300')){
			$(this).parent().css({'max-height' : 300 });
		}else if($(this).hasClass('350')){
			$(this).parent().css({'max-height' : 350 });
		}else if($(this).hasClass('400')){
			$(this).parent().css({'max-height' : 400 });
		}else if($(this).hasClass('450')){
			$(this).parent().css({'max-height' : 450 });
		}else if($(this).hasClass('500')){
			$(this).parent().css({'max-height' : 500 });
		}
		$(this).html('<span>مشاهده بیشتر</span>');
		$(this).removeClass('opend');
		$(this).addClass('closed');
		$(this).parent().css({'padding-bottom':'0px'});
	}
});
/*----------------------------------------------مربوط به فروشگاه---------------------------------------------------------*/
$('#mini-panel-shop_sidebar .views-exposed-widget').each(function(){
	if($(this).height() > 300){
		var temp = $(this).html();
		$(this).html(temp + '<div class="klick-for-more side closed"><span>مشاهده بیشتر</span></div>');
		$(this).css({'max-height' : 300 , 'overflow': 'hidden'});
	}
});
$('.klick-for-more.side').click(function(){
	if($(this).hasClass('closed')){
		$(this).parent().css({'max-height' : $(this).parent().children('.views-widget').height() + 100 , 'padding-bottom' : '50px !important' });
		$(this).html('<span>بستن</span>');
		$(this).removeClass('closed');
		$(this).addClass('opend');
	}else{
		$(this).parent().css({'max-height' : 300  });
		$(this).html('<span>مشاهده بیشتر</span>');
		$(this).removeClass('opend');
		$(this).addClass('closed');
	}
});
$('.page-shop div#edit-populate-wrapper input#edit-populate').attr('placeholder' , 'جستجو در بین تمامی محصولات');
$('.page-pedia div#edit-title-wrapper input#edit-title').attr('placeholder' , 'کلمات کلیدی خود را وارد کنید');
$('.page-gallery div#edit-populate-wrapper input#edit-populate').attr('placeholder' , 'جستجو در گالری');
$('div#edit-populate-wrapper input#edit-populate').attr('placeholder' , 'کلمات کلیدی خود را وارد کنید');

$('#mini-panel-shop_sidebar .panel-pane').parent().append('<div class="click-to-open"><button class="primary">فیلتر ها</button></div>');   
$('#mini-panel-shop_sidebar .click-to-open').click(function(){
	if($(this).parent().hasClass('opened')){
		shop_filter_close();
	}else{
		$(this).parent().addClass('opened');
		shop_filter_open();
	}
});
if($.urlParam("mefibs-form-f-mefibs_block_id") != null || ($.urlParam("items_per_page") != null && $.urlParam("p") != null)) {

}else{
	setTimeout(function(){
		$('#views-exposed-form-taxonomy-term-page-1-mefibs-form-f input[type="checkbox"]').each(function(){
			$(this).prop('checked', false);
		});
		$('#edit-mefibs-form-f-submit-taxonomy-term').click();
	}, 1000);
}
/*if(window.location.href.indexOf("mefibs-form-f-mefibs_block_id") > -1 || (window.location.href.indexOf("items_per_page") > -1 && window.location.href.indexOf("p") > -1)) {
}else{
	setTimeout(function(){
		$('#views-exposed-form-glrnew-page-2-mefibs-form-f input[type="checkbox"]').each(function(){
			$(this).prop('checked', false);
		});
		$('#edit-mefibs-form-f-submit-taxonomy-term').click();
	}, 1000);
}*/
if($("#uc-cart-view-form table").length) $("#uc-cart-view-form table").table_to_div({prefix:'cart-div'});$('.cart-div_عزل.cart-div_row input').replace_tag('button');
$('form#uc-zarinpal-pay-submission-form input#edit-submit, input#edit-back, .uc-cart-checkout-form #edit-continue ,tr.review-button-row .form-actions input').replace_tag('button', true );
$('tr.review-button-row #edit-back').addClass('primary');
$('#uc-cart-view-form .form-actions input').replace_tag('button', true );
$('.cart-div_تعداد input').keyup(function(){
	var id = $(this).attr('id');
	$('#uc-cart-view-form table').find('#'+ id).val($(this).val());
});  

$('.important4 .pane-title').after('<a class="more" href="/shop/808-movie-packages" target="_blank" style="position: relative;z-index: 100;left: 0;float: left;padding: 9px 15px;color: #fff;background: linear-gradient(to bottom left,#2196F3,#673AB7);font-size: 15px;border-radius: 2px;font-weight: 500;margin: 10px 0 0 10px;">+مشاهده تمامی پکیج ها</a>');

$('#edit-panes-quotes-quotes-quote-option-flatrate-4-0 + label').append('<a href="http://bit.ly/tipax808" target="_blank">لیست شهرستان ها</a>');

/*-------------------------------------------------------------------------------------------------------------------------------*/
var temp1 = $('div#block-views-exp-taxonomy-term-page-1 #edit-stock-wrapper');
if(temp1.find('input').attr('value') == '1'){
	temp1.append('<span class="stocknotify on"></span>');
}else{
	temp1.append('<span class="stocknotify off"></span>');
}
$('.stocknotify').click(function(){
	if($(this).hasClass('off')){
		$(this).parent().find('input').val(1);
		$(this).removeClass('off');
		$(this).addClass('on');
		$(this).parent().parent().find('.form-submit').click();
	}else{
		$(this).parent().find('input').val(0);
		$(this).html('<span>مشاهده بیشتر</span>');
		$(this).removeClass('on');
		$(this).addClass('off');
		$(this).parent().parent().find('.form-submit').click();
	}
});


/*-------------------------------------------------------------------------------------------------------------------------------*/
if($('.courses').length){
	$('.courses .views-row .views-field-field-image').each(function(){
		// $(this).parent().children('.views-field-title').css({'width' : '76%'});
		// $(this).parent().children('.views-field-body').css({'width' : '76%'});
	});
}
/*-------------------------------------------------------------------------------------------------------------------------------*/
if($('.page-cart').length){
	if($('.page-checkout').length){
		if($('.page-review').length){
			$('div#uc_Progressbar .bullet:nth-child(3)').addClass('current');
			$('div#uc_Progressbar .bullet:nth-child(1) , div#uc_Progressbar .bullet:nth-child(2)').addClass('done');
		}else {
			$('div#uc_Progressbar .bullet:nth-child(2)').addClass('current');
			$('div#uc_Progressbar .bullet:nth-child(1)').addClass('done');
		}
	}else {
		$('div#uc_Progressbar .bullet:nth-child(1)').addClass('current');
	}
}
/*-------------------------------------------------------------------------------------------------------------------------------*/
$('#block-panels-mini-user-panel h2').click(function(){
	if($(this).parent().hasClass('opened')){
		$('#useroverlay').css({'opacity' : '0'});
		setTimeout(function(){$('#useroverlay').css({'display':'none'});}, 800);
		$(this).parent().removeClass('opened');
	}else{
		$(this).parent().addClass('opened');
		$('#useroverlay').css({'display':'block'});
		setTimeout(function(){$('#useroverlay').css({'opacity' : '1'});}, 10);
	}
});
$('#useroverlay').click(function(){
	$('#useroverlay').css({'opacity' : '0'});
	setTimeout(function(){$('#useroverlay').css({'display':'none'});}, 800);
	$('#block-panels-mini-user-panel').removeClass('opened');
});
$('#block-panels-mini-user-panel h2.block-title').html(function(){
	if($('.pane-block-42 .user_pic a').length){
		return $('.pane-block-42 .user_pic a').html() +'<span class="message-num">'+ $('.unreads').text() +'</span>' +'<span class="num-items">'+ $('.cart-block-summary-items .num-items').text() +'</span>';
	}else{
		return $('.pane-block-42 .user_pic').html() +'<span class="message-num">'+ $('.unreads').text() +'</span>' +'<span class="num-items">'+ $('.cart-block-summary-items .num-items').text() +'</span>';
	}
});
if($('.cart-block-summary-items .num-items').text() == 0){
	$('#block-panels-mini-user-panel').addClass('no-item');
}
if(!$('.unreads').length){
	$('#block-panels-mini-user-panel').addClass('no-message');
}

/*-------------------------------------------------------------------------------------------------------------------------------*/
$('#edit-panes-webform-nid3403-0-edu-2 , #edit-panes-webform-nid3403-0-edu-1').click(function(){
	if ($('#edit-panes-webform-nid3403-0-edu-1').is( ":checked" ) ) {
		$('#coupon-pane').find('.form-text').val('firstclass');
	}
	if ($('#edit-panes-webform-nid3403-0-edu-2').is( ":checked" ) ) {
		$('#coupon-pane').find('.form-text').val('halfcourse');
	}
	$('fieldset#coupon-pane #edit-panes-coupon-apply').after('<span class="do-it">کلیک کنید تا اعمال شود.</span>');

});
$('#edit-submitted-courseinfo-quantity').on('change', function (e) {
	var optionSelected = $("option:selected", this);
	var valueSelected = this.value * 120000;
	$('input#edit-submitted-price').val(humanizeNumber(valueSelected));
});
$('#edit-submitted-bdwn-prdkht-1').on('change', function (e) {
	if(!$(this).is( ":checked" ) ) {
		$(this).prop('checked', true);
	}
	$('.webform-submit').click();
});

/*-------------------------------------------------------------------------------------------------------------------------------*/
if($('.page-event').length){
	$('.container.main').removeClass('container');
}
/*-------------------------------------------------------------------------------------------------------------------------------*/
var comments = $('body:not(.node-type-questions) .comment-form');
comments.on('focus', 'textarea', function () {
	CommentOpen($(this));
});
// Open Notifications
CommentOpen = function(comment) {
	comment.parents('.comment-form').addClass('writing').find('.form-actions').slideDown();
	$('html').unbind("click", CommentClose);
};
CommentClose = function() {
	comments.removeClass('writing').find('.form-actions').slideUp();
//	$('html').unbind("click", CommentClose);
};
comments.click(function(event){
	event.stopPropagation();
});
$('html').click(function(event){
	CommentClose();
});
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*picture gallery section*/
if($('.author-section').length){
	if($(this).find('.author_desc').html().length < 10){
		$('.author-section').css({'display' : 'none'});
	}
}
/*--------*/
if($('.view-glrnew').length){
	$(this).find('.views-row').each(function(i){
		var temp = parseInt($(this).find('.views-field-field-gallerynewimage-1').find('.field-content').text());
		var temp1 = parseInt($(this).find('.views-field-field-pictures').find('.field-content').text());
		$(this).find('.views-field-field-gallerynewimage-1').find('.field-content').html(temp + temp1)
		
	});
}
/*--------*/
$('.short_link').on("click",function(){
	$(this).select();
});
/*-----------------------------برای گالری محتوای بعدی و قبلی-------------------------------------------*/
$(window).scroll(function () {
	if($('.page-gallery').length){
		if ($('#footer').offset().top - $(this).scrollTop() < 381) {
			$('.page-gallery.page-picture .field-name-before-picture').css({'opacity':'0'});
			$('.page-gallery.page-picture .field-name-next-picture').css({'opacity':'0'});
			$('.page-gallery.page-videos .field-name-next-film').css({'opacity':'0'});
			$('.page-gallery.page-videos .field-name-before-film').css({'opacity':'0'});
		} 
		else{
			$('.page-gallery.page-picture .field-name-before-picture').css({'opacity':'1'});
			$('.page-gallery.page-picture .field-name-next-picture').css({'opacity':'1'});
			$('.page-gallery.page-videos .field-name-next-film').css({'opacity':'1'});
			$('.page-gallery.page-videos .field-name-before-film').css({'opacity':'1'});
		}
	}
});
/*-------------------------------------------مربوط به کاربر------------------------------------------------------------------------------*/

/*question-tab*/
var select = $('.page-user-myquestions #quicktabs-user_questions_tab #qt-user_questions_tab-ui-tabs3');
select.find('td.views-field-field-prove-advisor').each(function(){
	if($(this).text() == 1){
		$(this).addClass("advisor-proved");
		$(this).attr("title" , "تایید شده توسط مشاور");
	}else if($(this).text() == 0){
		$(this).addClass("no-advisor-prove");
		$(this).attr("title" , "تایید نشده");
	}
	$(this).text("");
});
select.find('td.views-field-field-prove-asker').each(function(){
	if($(this).text() == 1){
		$(this).addClass("asker-proved");
		$(this).attr("title" , "تایید شده توسط نویسنده سوال");
	}else if($(this).text() == 0){
		$(this).addClass("no-asker-prove");
		$(this).attr("title" , "تایید نشده");
	}
	$(this).text("");
});

/*bookmark table*/
if(!$('.page-user #block-system-main .content .pane-quicktabs-user-bookmark').length){
	$('.page-user #block-system-main .content .row-17-main-row .region-17-center-inside').prepend('<div class="pane-quicktabs pane-quicktabs-user-bookmark"><h2 class="pane-title">نشان شده ها</h2><div class="pane-content empty-msg"><span> هیچ محتوایی نشان نشده است. </span><span>با کلیک بر روی آیکن <span class="icon"></span> در کنار هر محتوا، آن را به لیست نشان شده های خود بیفزایید.</span><a class="btn btn-primary" target="_blank" href="/pedia">محتوای تخصصی</a></div></div>');
}

/*userpoints section*/
if($('.page-user-points #userpoints-list-transactions tbody .empty.message').length){
	$('.page-user-points #userpoints-list-transactions').css({'display' : 'none'});
	$('.page-user-points #block-system-main .content').append('<div class="empty-userpoint"><span>برای شما هیچ اعتباری ثبت نشده است!</span><a href="/user/' + Drupal.settings.Uid + '/money/charge" class="btn btn-primary" target="_blank">افزایش اعتبار</a></div>');
}

/*solded content*/
if($('.user-sale-report #qt-sold_content_tab-ui-tabs1 .item-list').length){
	$('.user-sale-report #qt-sold_content_tab-ui-tabs1 .item-list a').each(function(){
		$url = $(this).attr('href');
		$(this).attr('href', $url+'#quicktabs-sold_content_tab=0');
	});
}
if($('.user-sale-report #qt-sold_content_tab-ui-tabs2 .item-list').length){
	$('.user-sale-report #qt-sold_content_tab-ui-tabs2 .item-list a').each(function(){
		$url = $(this).attr('href');
		$(this).attr('href', $url+'#quicktabs-sold_content_tab=1');
	});
}
if($('.user-sale-report #qt-sold_content_tab-ui-tabs3 .item-list').length){
	$('.user-sale-report #qt-sold_content_tab-ui-tabs3 .item-list a').each(function(){
		$url = $(this).attr('href');
		$(this).attr('href', $url+'#quicktabs-sold_content_tab=2');
	});
}	

/*messages section*/
$('.privatemsg-author-name a').each(function(){
	$(this).parents('.privatemsg-message').addClass('others');
});
if($('.privatemsg-message-participants a').length){
	var temp = $('.privatemsg-message-participants a').attr('href').split("/");
	if(temp[2] == "2"){
		$('.page-user-messages-view form').css({'display' : 'none'});
	}
}

$('form#privatemsg-new #edit-recipient').after('<div class="advisor-link"><a title="میتوانید با مشاوران اختصاصی سایت رفع اشکال کنید" class="btn small-btn" href="/landing/advisor">لیست مشاوران</a></div>');

/*login section*/
$('#login-link').text('ورود');
$('#register-link').text('ثبت نام');

$('#login-link , #register-link').click(function(){
	if($('#login-link.lt-active').length){
		$(this).parents('body').addClass('page-login');
		$('body').removeClass('page-register');
	}else if($('#register-link.lt-active').length){
		$(this).parents('body').addClass('page-register');
		$('body').removeClass('page-login');
	}	
});
/*tabs section*/
$('.tabs li').each(function(){
	var href = $(this).find('a').attr('href');
	$(this).addClass(href.split('/').join(' '));
});
$('.view-uc-orders-user tr').each(function(){
	var stts = $(this).find('.views-field-order-status');
	if(stts.hasClass('ارسال-شد')){
		$(this).addClass('sent');
	}else if(stts.hasClass('تکمیل-شد') || stts.hasClass('Payment-received')){
		$(this).addClass('payed');
	}else if(stts.hasClass('در-حال-بررسی')){
		$(this).addClass('in-progress');
	}
});
$('th.active img').each(function(){
	if($(this).attr('title') == 'نزولی'){
		$(this).parent().addClass('desc');
	}
});
$('.uc-order-action').each(function(){
	$(this).addClass($(this).attr('title'));
});
/*for avoiding multiple picture*/
$('div#quicktabs-user_contents .ui-tabs-panel .views-row,div#block-quicktabs-user-bookmark .ui-tabs-panel .views-row').each(function(){
	if($(this).children('div:nth-child(3)').length){
		$(this).children('div:nth-child(1)').remove();
	}
});
/*for customizing active-bar under the user quick-tabs*/
$('div#quicktabs-user_contents .ui-tabs-panel').each(function(){
	$(this).append('<span></span>');
});
if ($('.page-user .quicktabs-ui-wrapper').length){
	$('.page-user .quicktabs-ui-wrapper .ui-tabs-nav').append('<span class="active-bar"></span>');
	$('.active-bar').each(function(){
		$(this).css({'width': $(this).parent().parent().find('li.ui-state-active').width() , 'left' : $(this).parent().parent().find('li.ui-state-active').position().left });
	});
	$('.page-user .quicktabs-ui-wrapper .ui-tabs-nav li a').click(function(e){
		//e.preventDefault();
		//to adjust position().left when it has an scroll
		var ul = $(this).parent().parent();
		if(ul[0].scrollWidth != ul.width()){
			ul.find('.active-bar').css({'width' : $(this).parent().width() , 'left' : $(this).parent().position().left - (ul[0].scrollWidth - ul.width() - ul.scrollLeft()) });
		}else{
			ul.find('.active-bar').css({'width' : $(this).parent().width() , 'left' : $(this).parent().position().left });
		}
		/*for better changing content between tabs*/
		var hoverr = $(this).parents('.page-user .quicktabs-ui-wrapper').children('*').eq($(this).parent().index() + 1);
		hoverr.addClass('started');
		setTimeout(function(){
			hoverr.addClass('action');
			setTimeout(function(){
				hoverr.removeClass('action');
				setTimeout(function(){
					hoverr.removeClass('started');
				}, 200);
			}, 1000);
		}, 10);
	});
}

if($('.user-sale-report').length && !$('.user-sale-report .pane-content div').length){
	// $('.user-sale-report').remove();
}
if($('#edit-profile-main-field-bool').length){
	$('#edit-profile-main-field-bool').remove();
}
//changing the position of "login with linkedin"
if($('#user-login').length){
	var items = $('#user-login .item-list');
	$('#user-login .item-list').remove();
	$('#user-login > div').append(items);
	var register = $('.linkedin.register');
	$('#user-register-form .linkedin.register').remove();
	$('#user-register-form > div').prepend(register);
}
// add plus sign '+' when user has more than 500 connection
if($('.linkedin-num-connections').length && parseInt($('.linkedin-num-connections span:last-child').text()) > 499){
	$('.linkedin-num-connections span:last-child').addClass('capped');
}
//change the direction of summery if it contains persian text
$('.linkedin-position-summary').each(function(){
	var text = $(this);
	$.getScript('/sites/all/themes/sara/js/lib/persian-rex.js', function(){
		if (persianRex.letter.test(text.text().substring(0,1)))
			text.addClass('rtl');
	});
});
//added user secondery menu. because ther is a problem with user/edit pages
if($('.page-edit.page-linkedin, .page-edit.page-addresses').length){
	if($('#content > .tabs .secondary').length){
		$('#content > .tabs .secondary').prepend('<li class="user edit"><a href="/user/'+ Drupal.settings.Uid +'/edit">حساب</a></li>'
			+'<li class="user edit main"><a href="/user/'+ Drupal.settings.Uid +'/edit/main">اطلاعات اصلی</a></li>'
			+'<li class="user edit bank"><a href="/user/'+ Drupal.settings.Uid +'/edit/bank">بانک</a></li>'
		);
	}
}
$('.bootstrap-filestyle > .group-span-filestyle').each(function(){
	$(this).parents('.form-item').addClass('boot-filestyle');
});
if(Drupal.settings.SameUser){
	$('body').addClass('same-user');
}else{
	$('body').addClass('not-same-user');
}
$('.لغو').each(function(){
	$(this).addClass('laghv');
});
$('.عزل').each(function(){
	$(this).addClass('azl');
});
$('.موافقت--رد-کردن').each(function(){
	$(this).addClass('accept');
});
$('.all-members .views-field-field-experts a').each(function(){
	if($('.page-landing-members').length){
		$(this).attr('href', '/landing/members?field_experts_tid='+$(this).text())
	}else{
		$(this).attr('href', '')
	}
});
$('.all-members .views-field-status-link .add.not-login a').click(function(e){
	e.preventDefault();
	$('#block-panels-mini-user-panel h2.block-title').click();
});

if($('.view-represation').length){
	$('.view-represation .views-widget-filter-field_experts_tid').before('<span class="more-filter" title="فیلتر های بیشتر"></span>');
	$('.more-filter').click(function(){
		$(this).toggleClass('opened');
		$(this).prevUntil('.views-widget-filter-field_full_name_value_1').animate({width:'toggle'},0);
	});
}
if($('#edit-field-education-degree-value').val() || 
	$('#field_education_field_value').val() || 
	$('#edit-field-university-value').val() || 
	$('#edit-field-job-value').val() || 
	$('#edit-field-about-me-value').val())
{
	$('.more-filter').click()
}
/*user-profile required fields*/
$("#edit-profile-main-field-experts , #edit-profile-main-field-job , #edit-profile-main-field-university , #edit-profile-main-field-education-field , #edit-profile-main-field-education-degree , #edit-profile-main-field-mobile , #edit-profile-main-field-full-name").attr('title', 'برای تکمیل پروفایل اجباری است');

/*-------------------------------------------مربوط به ویدئو------------------------------------------------------------------------------*/
/*for iframe*/
$('.page-iframe .mejs-overlay-play ,.page-iframe .mejs-overlay-play *').click(function(){
	$('.page-iframe h2.pane-title').css({'display' : 'none'});
	$('.page-iframe h2.pane-title').addClass('none');
});
/*for download link*/
$('fieldset.group-links .fieldset-wrapper').html($('.mediaelement-download-link').outerHTML() + $('fieldset.group-links .fieldset-wrapper').html());
/*for iframe link*/
if($('.field-name-iframe').length){
	$('.embed-section .title').click(function(){
		if(!$(this).parents('.field-name-iframe').hasClass('opened')){
			$('div#videoIframe').slideDown();
			$(this).parents('.field-name-iframe').addClass('opened');
		}else {
			$('div#videoIframe').slideUp();
			$(this).parents('.field-name-iframe').removeClass('opened');		
		}
	});
	$('#videoIframe .iframe-close').click(function(){
		$('div#videoIframe').slideUp();
		$(this).parents('.field-name-iframe').removeClass('opened');		
	});
}
$('iframe').each(function(){
	$(this).attr('allowFullScreen' , 'true').attr('webkitallowfullscreen' , 'true').attr('mozallowfullscreen' , 'true').css({'max-width' : '840px'});
});
/*for video time*/
if($('.mejs-container').length){
	var time = '';
	if($('.field-name-field-film-time').length){
		time = '<div class="film-time manual">' + $('.mejs-container').parents('.node').children().children('.field-name-field-film-time').find('.hms').text() + '</div>';
	}
	$('.mejs-clear').html(time);
	setTimeout(function(){
		if(parseInt($('.mejs-container').find('.mejs-duration').text()) > 1 && time.length < 2){
			$('.mejs-container').addClass('second-value');
			time += '<div class="film-time">' + $('.mejs-container').find('.mejs-duration').text() + '</div>';
			$('.mejs-clear').html(time);
		}
	}, 3000);
}
$('.mejs-overlay-play ,.mejs-overlay-play * ,.mejs-playpause-button').click(function(e){
	$('.film-time').css({'display' : 'none'});
	$('.film-time').addClass('none');
});
/*for video suggestion after it's finished*/
$('video').on('ended', function myHandler(e) {
	$(this).parents('.mediaelement-video').addClass('ended');
	$(this).parents('.node').find('.video-finished').addClass('ended');
});
$('.mejs-play button').click(function(){
	$(this).parents('.ended').removeClass('ended');
	$(this).parents('.node').find('.ended').removeClass('ended');
});
/*for video ads in start*/
$('.page-videos.node-type-film .mediaelement-video').addClass('ads-enabled');
$('.ads-enabled .mejs-overlay-play ,.ads-enabled .mejs-overlay-play * ,.ads-enabled .mejs-playpause-button').click(function(e){
	if(!$(this).parents('.node').find('.video-finished').hasClass('noads')){
		e.preventDefault();
		var player = new MediaElementPlayer('video');
		player.pause();
		$(this).parents('.node').find('.video-finished').addClass('started');
		setTimeout(function(){
			$('.started').addClass('noads');
			$('.started').removeClass('started');
			$('.ads-enabled').removeClass('ads-enabled');
			player.play();
		}, 5000);
	}
});
/*for responsive page*/
$('.page-gallery #comments h2').click(function(){
	if($(this).parents('#comments').hasClass('opened')){
		$(this).parents('#comments').children('form').slideUp();
		$(this).parents('.opened').removeClass('opened');
	}else{
		$(this).parents('#comments').children('form').slideDown();
		$(this).parents('#comments').addClass('opened');
	}
});
$('.page-gallery .social-share').addClass('changed');
$('.page-gallery .social-share').html('<h2>اشتراک</h2><div class="social-share">' + $('.page-gallery .social-share').html() + '</div>');
$('.social-share.changed').removeClass('social-share');

$('.page-gallery .changed h2').click(function(){
	if($(this).parents('.changed').hasClass('opened')){
		$(this).parents('.changed').children('.social-share').slideUp();
		$(this).parents('.opened').removeClass('opened');
	}else{
		$(this).parents('.changed').children('.social-share').slideDown();
		$(this).parents('.changed').addClass('opened');
	}
});
/*video playlist*/
var nidd = 'node' + $('.view-playlist.view-display-id-page .view-header').text().trim();
$('.playlist .views-row').each(function(){
	if($(this).hasClass(nidd)){
		$(this).addClass('active');
		var scroll = $(this).position().top;
		$('#block-views-playlist-block-1 .playlist').animate({
		scrollTop: (scroll)
		}, 1000);
	}
});
/**/
$('#block-views-playlist-block-1').find('.block-title').text($('#block-views-playlist-block-1').find('.view-header').text().trim());
/**/
$('.page-playlist video').on('ended', function myHandler(e) {
	$('.playlist .views-row').each(function(){
		if($(this).hasClass(nidd)){
			$(location).attr('href', $(this).next().find('.views-field-title a').attr('href'));
		}
	});
});
if($('.page-playlist').length){
	var player = new MediaElementPlayer('video');
	player.play();	
}
if($('#block-views-playlist-block-2').length){
	var flag = false;
	$('.playlist-items .views-field-php').each(function(){
		if($(this).find('a').length){
			flag = true;
		}
	});
	if(!flag){
		$('#block-views-playlist-block-2').remove();
	}	
}
initialise();
$('div#block-views-playlist-block-1 .block-title').click(function(){
	$(this).parent().toggleClass('opened');
});
/*cannot play bideo for some browser*/
if($('.me-cannotplay').length){
	$('.me-cannotplay').prepend('<div class="description"><p>فرمت این ویدئو در مرورگر شما قابل پخش نیست</p><p>از نسخه های به روز مرورگر های <a class="chrome" href="https://www.google.com/chrome" target="_blank">Chrome</a> و <a class="firefox&#10;" href="https://www.mozilla.org/en-US/firefox/products/?v=b" target="_blank">Firefox</a> استفاده نمایید.</p></div>');
}
/*-----------------------------------------------------------------------------------------------------------------*/
$('.civil-slide .views-field.views-field-field-image').each(function(){
	if(!$(this).next().length){
		$(this).find('img').css({'z-index' : '1'});
	}
});
/*-----------------------------------------------------------------------------------------------------------------*/
if($('#comments').length){
	if($('#comments').children().length < 3){
		// $('#comments').remove();
	}
}
/*-----------------------------------------------------------------------------------------------------------------*/
if($('.menu-column').length){
	var to_top = $('.menu-column').offset().top - 50;
	$(window).scroll(function () {
		if ($(this).scrollTop() > to_top) {
			$('.menu-column').addClass("fix");
		} else {
			$('.menu-column').removeClass("fix");
		}
	});
}
/*-----------------------------------------------------------------------------------------------------------------*/
$('input#edit-price').keyup(function(){
	$(this).parents('form').find('#smile span').text((parseInt($(this).val() * 1.2,10)));
});
/*-----------------------------------------------------------------------------------------------------------------*/
if($('.page-college-search').length && $('.view-courses .views-exposed-widgets .filters').length == 0){
	$('.page-college-search .view-courses .views-exposed-widgets').append('<button class="filters primary"><span>فیلتر ها</span></button>');
}

$('.view-courses .views-exposed-widgets .filters').click(function(e){
	e.preventDefault();
	$(this).parents('.view-filters').toggleClass('open');
	$(this).toggleClass('open');
	$('#edit-field-course-step-value-wrapper, #edit-field-course-type-value-wrapper').slideToggle(400);
});

/*-----------------pedia-----------------*/

$('.page-pedia div#block-mefibs-8e49d13e1295a3847928ee45c286e415').append('<div class="scrollingdown"></div>');
$('.page-pedia div#block-mefibs-8e49d13e1295a3847928ee45c286e415 div.scrollingdown').click(function(){
	
	$('html, body').animate({
		scrollTop: $("#block-system-main").offset().top
	}, 1000);
	
});
if($('.view-pediareverse .views-row').length && $('.view-pediareverse .views-row').html().length < 2){
	$('.view-pediareverse .views-row').parents('.block-views').remove();
}

$('.node-teaser.node-college .field-name-field-course-step .field-item').each(function(){
	switch ($(this).text()) { 
		case 'در حال ثبت نام': 
			$(this).addClass("sabtenam");
			break;
		case 'در حال برگزاری': 
			$(this).addClass("bargozari");
			break;
	}
});

$('#privatemsg-new .text-format-wrapper').append('<span class="tazakkor">طبق <a href="/landing/law" target="_blank">قوانین سایت</a> ، فرستادن شماره تلفن و ایمیل ممنوع می باشد و در صورت مشاهده، پیغام توسط مدیریت ویرایش می شود.</span>');

/*-----------------------------------------------------------------------------------------------------------------*/
/* $('td.privatemsg-list-participants a').each(function(i){
	if(i > 5) return;
	var href = $(this).attr('href').split('/');
	var element = $(this);
	var html = '';
	$.ajax({url: "/user/"+ href[2] +"#mini-panel-user_header", success: function(result){
		html = $.parseHTML(result);
		var img = $(html).find('.pane-block-47 .user-pic a').html();
		element.prepend(img);
		element.addClass('has-img');
	}});
}); */
$('td.privatemsg-list-participants a, .privatemsg-message-participants a').each(function(i){
	if(i < 3 && i > 7) return;
	var href = $(this).attr('href').split('/');
	var element = $(this);
	var html = '';
	$.ajax({
		url: "/user/"+ href[2] +"/ajax/picture", 
		success: function(result){
			var img = $.parseHTML(result.data);
			element.prepend(img);
			element.addClass('has-img');
		}
	});
});
/*-----------------------------------------------------------------------------------------------------------------*/
// add wave action to some elements for default:
$('.btn, button, .btn-primary, .cancel-address-link, a#edit-cancel, .btn-danger, .address-link, a.all-members, .jcarousel-next-horizontal, #footer a, input[type="submit"], ul.secondary a, ul.primary li a, .ui-tabs-nav li a, .pager li > a, .userpoints-links a, .row-17-6-inside .region-first .pane-content a, ul.sidebar_menu_user a').each(function(){
	if($(this).css('position') == 'absolute'){
		$(this).addClass('pos-abs');
	}
	$(this).addClass('has-wave');
});
$('.has-wave').each(function(){
	$(this).prepend('<span class="click-wave"></span>');
});
//wave action for bottuns same as in material
$('.has-wave').mousedown(function(parameter){
	var element = $(this).find('.click-wave');
	var w = element.width();
	var h = element.height();
	if(w < h){w = h;}
	var x = parameter.pageX - $(this).offset().left ;
	var y = parameter.pageY - $(this).offset().top;
	w = w + Math.abs(w/2 - x)*2 + 10; //calculating the required minimum
	if( !isdark( rgb2hex(element.parent().css("background-color") ) ) ){ element.addClass('whiter');}
	element.prepend('<div style="width:'+ w +'px; height:'+ w +'px; top:'+ (y - w/2) +'px; left:'+ (x - w/2) +'px; transform:scale(0);"></div>');
	setTimeout(function(){
		element.find('div').addClass('scale1');
	}, 10);
}).on('mouseup mouseleave', function(parameter){
	var element = $(this).find('.click-wave');
	element.find('div').addClass('opacity0');
	setTimeout(function(){
		element.find('div:last-child').remove();
	}, 1500);
});
/*-----------------------------------------------------------------------------------------------------------------*/
window.cleard_error_msg = false;
var interval = setInterval( function(){
	// stopping the Interval when the output array were finished
	if (window.cleard_error_msg) {
		clearInterval(interval);
	}
	initialise();
},1000);











}); /*===> end of document.ready-function*/
/*#################################################*/
$(window).resize(function() {
/*for front shop section*/
if($('.view-conference-news').length)
	applyHeight($('div#views_slideshow_cycle_teaser_section_conference_news-block_3') , $('.view-conference-news .views-slideshow-cycle-main-frame-row') , 0);
/*---------------------------------مربوط به ویدئو----------------------------*/




/*------------------------------------------------------------*/
initialise();
});

$(window).load(function(){
initialise();
if($('.page-form.page-college-register').length){
	if($.urlParam('product') != null ){
		$('#edit-submitted-products').find('input#edit-submitted-products-' + $.urlParam('product')).prop('checked',true);
	}
}
/*-------------------------------------------------------*/
if($('.page-college-search').length){
	if(window.location.href.indexOf("field_course_type_value") > -1 || window.location.href.indexOf("field_course_step_value") > -1){
		$('.view-courses .views-exposed-widgets .filters , .view-courses .view-filters').addClass('open');
		$('#edit-field-course-step-value-wrapper, #edit-field-course-type-value-wrapper').slideToggle(400);
	}
}
/*-------------------------------------------------------*/




});
/*#################################################*/

function initialise(){
	/*this line is for changing the height of twe columns in college's topics*/
		setTimeout(applyHeight($(".college-body-right") , $(".college-body-left") , 0), 1000);
	/*-------------------------------------------------------*/
	if($('.courses').length){
		$('.courses .views-row .views-field-field-image').each(function(){
			$(this).parent().addClass('has-image');
		});
	}
	if($('.node-college.node-teaser').length){
		$('.node-college.node-teaser .field-name-field-image').each(function(){
			$(this).parents('.node').addClass('has-image');
		});
	}
	/*----------------for responsive-------------------*/
	if (window.matchMedia('(max-width: 768px)').matches) {
		video_comment_share_open();
		video_playlist_side_to_main();
	} else {
		video_comment_share_close();
		video_playlist_main_to_side();
	}

	if (window.matchMedia('(max-width: 979px)').matches) {
		shop_filter_close();
	} else {
		shop_filter_open();
	}
	/*-----------------------------------------------------------------------------------------------------------------*/
	applyHeight($('.node-product-kit .group-right') , $('.node-product-kit .group-left'));
	applyHeight($('.node-product .group-right') , $('.node-product .group-left'));
	
	/*-----------------------------------------------------------------------------------------------------------------*/
	var boot_file_selector = $(
	'div#edit-support-ticket-upload .file-widget, div#edit-field-hw-video .file-widget'+
	', input#edit-picture-upload'+
	', #user-profile-form .form-item input.form-file'+
	', input.form-file');
	if(boot_file_selector.length){
		$.getScript('/sites/all/themes/sara/js/lib/bootstrap-filestyle.min.js', function(){
		$(":file").filestyle({buttonText: "انتخاب فایل", buttonName: "btn-primary",placeholder: "فایلی انتخاب نشده"});
		});
	}

	/*this is for pnotify messages*/
	/*$('.ui-state-error .ui-pnotify-text').each(function(){
		if($(this).text().indexOf("public_html") > 0 || $(this).text().indexOf("module") > 0 || $(this).text().indexOf("Undefined") > 0 ){
			$(this).parents(".ui-widget").addClass("admin-error");
			window.cleard_error_msg = true;
		}
	});*/

    $('.messagwrapper .error, .messagwrapper .warning').each(function(){
        if($(this).text().indexOf("public_html") > 0 || $(this).text().indexOf("module") > 0 || $(this).text().indexOf("Undefined") > 0 ){
            $(this).parents(".messagwrapper").addClass("admin-error");
            window.cleard_error_msg = true;
        }
    });
  
}
/*-------------------------------------------------------*/
var applyHeight = function (x, y, z) {
	z = z || 0;
	if (x.height() < y.height()) {
		x.height(y.height() + (z));
	} else if (x.height() >= y.height()) {
		y.height(x.height() + (z));
	} else
		return false;
	return true;
};
/*-------------------------------------------------------*/
/**/var countup = function(x){var $dd = parseInt(x.text());jQuery({someValue: 0}).animate({someValue: $dd }, {duration: 3000,easing:'swing', /* can be anything*/step: function() { /* called on every step*/x.text(Math.ceil(this.someValue));}});}/**/ 
$.urlParam = function(name){var results = new RegExp('[\?&]' + name + '=([^&#]*)').exec(window.location.href); if (results==null){return null;} else{return results[1] || 0;}}/**/
jQuery.fn.outerHTML = function() {return jQuery('<div />').append(this.eq(0).clone()).html();};
$.fn.table_to_div = function(options) {
  var settings = $.extend({}, {prefix: 'tg',target:''}, options);
  return this.each(function() {   
    var output = "";
    var data = "";
    settings.prefix = settings.prefix+"_";
    columns = [];
    table_target = $(this);
    var tr_count=0;
    //LOOP OVER ALL ROWS
    $(table_target).find('tr').each(function(){
      var col_count = 0;
      //LOW OVER EACH COLUMN IN THE ROW
      $(this).find('th,td').each(function(){        
        var element = $(this).html();        
        if(tr_count ==0){
          //HEADER COLUMN
          columns.push($(this).html());
        }else{
          //CONTENT COLUMN, strip leading and trailing whitespace
          data+= '      <div class="'+settings.prefix+columns[col_count].replace(/\s+/g,'')+' '+settings.prefix+'row">\n';
          data+= '         <label>'+columns[col_count]+'</label>\n';
          data+= '         <span>'+element.replace(/^\s\s*/, '').replace(/\s\s*$/, '')+'</span>\n';
          data+= '      </div>\n'; 
        }   
        col_count++;
      });
      if(tr_count != 0){
        output+='   <div class="'+settings.prefix+tr_count+' '+settings.prefix+'group">\n';
        output+= data;
        output+= '   </div>\n';
        data = "";
      }
      tr_count++;     
    });      
    output = '<div class="'+settings.prefix+'container">\n'+output+'</div>\n';
    if(settings.target.length > 0){
      $(settings.target).html(output);
    }else{
      $(table_target).before(output);
    }        
  });
};
$.fn.replace_tag = function(target , val) {
  target = target || 'div';
  val = val || false;
  return this.each(function() {   
  	var el = $(this),
    attrs = {
        "id": el.attr('id'),
        "value": el.attr('value'),
        "name": el.attr('name'),
        "type": el.attr('type'),
        "class": el.attr('class'),
        "styles": el.attr('style')
    };
	if(val){
		el.replaceWith($('<'+ target +'></'+ target +'>').html(el.html()).attr(attrs).text(attrs.value));
	}else{
		el.replaceWith($('<'+ target +'></'+ target +'>').html(el.html()).attr(attrs));
	}
  });
};

// Cookies
function setCookie(name, value, days) {
    if (days) {
        var date = new Date();
        date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
        var expires = "; expires=" + date.toGMTString();
    }
    else var expires = "";               
    document.cookie = name + "=" + value + expires + "; path=/";
}
function getCookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for (var i = 0; i < ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) == ' ') c = c.substring(1, c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length, c.length);
    }
    return null;
}
function eraseCookie(name) {setCookie(name, "", -1);}
/*-------------------------------------------------------*/
var klickmore = function(temp , x){
	if(temp.height() > x){
		temp.html(temp.html() + '<div class="klick-for-more '+ x +' closed"><span>مشاهده بیشتر</span></div>');
		temp.css({'max-height' : x , 'overflow': 'hidden' , 'position': 'relative' , 'transition' : 'all 0.5s'});
	}
};
function humanizeNumber(n) {
  n = n.toString()
  while (true) {
    var n2 = n.replace(/(\d)(\d{3})($|,|\.)/g, '$1,$2$3')
    if (n == n2) break
    n = n2
  }
  return n
}
/*for video comments responsive*/
function video_comment_share_open(){
   $('.page-gallery #comments > form').slideUp();
   $('.page-gallery #comments.opened').removeClass('opened'); 
   $('.page-gallery .changed .social-share').slideUp();
   $('.page-gallery .changed.opened').addClass('opened');	
}
function video_comment_share_close(){
   $('.page-gallery #comments > form').slideDown();
   $('.page-gallery #comments').addClass('opened'); 
   $('.page-gallery .changed .social-share').slideDown();
   $('.page-gallery .changed').addClass('opened');
}
/*for video comments responsive*/
function video_playlist_side_to_main(){
	$('.group-header .field-name-field-film-time').after($('.region-ads1 div#block-views-playlist-block-1'));
	$('.region-ads1 div#block-views-playlist-block-1').remove();
	$('div#block-views-playlist-block-1').addClass('opened');
}
function video_playlist_main_to_side(){
	$('.region-ads1').prepend($('.group-header div#block-views-playlist-block-1'));
	$('.group-header div#block-views-playlist-block-1').remove();
	$('div#block-views-playlist-block-1').removeClass('opened');
}

function shop_filter_close(){
   $('#mini-panel-shop_sidebar .panel-pane').slideUp();
   $('#mini-panel-shop_sidebar .opened').removeClass('opened');
}
function shop_filter_open(){
   $('#mini-panel-shop_sidebar .panel-pane').slideDown();
}
function prices() {
	$('.node-product , .node-product-kit').each(function(){
	    // prevent relative products to be parsed
	    if($(this).parents('.node-product').length || $(this).parents('.node-product-kit').length)
	        return

        var el = $(this)
        var is_teaser = true
        if(!$(this).hasClass('node-teaser')){
	        el = $(this).children('div')
            is_teaser = false
        }
		var list_price = get_uc_price(el.children('.list-price'));
		var display_price = get_uc_price(el.children('.display-price'));
		
		if (list_price <= display_price){
            (is_teaser)? el.children('.list-price').css('visibility','hidden') : el.children('.list-price').css('display','none')

			//there is no other discount enabled so we show vip price
            if(!el.find('.vip-price').length && (!is_teaser || $('.role-Vip').length) && $(this).hasClass('apply-vip-discount')) {
            	//for full view mode or teaser mode just when he is vip
                el.children('.display-price')
                    .after('<div class="vip-price"><span class="title">قیمت برای کاربران <a href="/landing/vip" class="" style="color: #512DA8;border-bottom: 1px dotted;" target="_blank">VIP</a>:</span><span class="uc-price">' + money_format(display_price * 0.9) + ' تومان</span></div>')
                    .find('.uc-price').css('color','rgba(244, 67, 54, 0.8)');

                if ($('.role-Vip').length) {
                    el.find('.vip-price')
                        .append(uc_discount_theme(display_price * 0.1, '10% تخفیف VIP: '))
                        .find('.title').text('قیمت برای شما:')
                    el.children('.display-price').addClass('vip-enabled')
                    $(this).addClass('vijeh');
                }
            }
		}else{
			if(!el.find('.list-price .uc-takhfif').length)
				el.children('.list-price').append(uc_discount_theme(list_price - display_price))
			$(this).addClass('vijeh')
		}
	});
	//deal with relative products
	$('.node-product, .node-product-kit').find('.node-product').each(product_teaser_prices);
	$('.node-product, .node-product-kit').find('.node-product-kit').each(product_teaser_prices);

	// theme for uc_discount
    function uc_discount_theme(price , title){
        if(title === undefined) title = 'تخفیف شما: '
        return '<div class="product-info uc-takhfif"><span class="uc-takhfif-label">'+ title +'</span><span class="uc-takhfif">' + money_format(price) + ' تومان</span></div>'
    }

    //for relative products
    function product_teaser_prices(){
		var el = $(this)
        var list_price = get_uc_price(el.find('.list-price'));
        var display_price = get_uc_price(el.find('.display-price'));

        if (list_price <= display_price){
			el.find('.list-price').css('visibility','hidden');

            //there is no other discount enabled so we show vip price
			if(!el.find('.vip-price').length && $('.role-Vip').length && $(this).hasClass('apply-vip-discount')) {
				el.addClass('vijeh')
				.children('.display-price')
					.after('<div class="vip-price"><span class="uc-price">' + money_format(display_price * 0.9) + ' تومان</span></div>')
					.find('.uc-price').css('color','rgba(244, 67, 54, 0.8)');

				el.children('.display-price').addClass('vip-enabled')
			}
        }else{
            if(!el.find('.list-price .uc-takhfif').length)
				el.find('.list-price').append(uc_discount_theme(list_price - display_price));
			el.addClass('vijeh');
        }
    }

    // return number value of uc_price
    function get_uc_price(el){
        return parseInt(el.find('.uc-price').text().split(" تومان")[0].split(",").join(""))
    }
}

/*for firing some scripts after ajax */
Drupal.behaviors.myBehavior = {attach: function (context, settings) {
    initialise();
	/*------------------------------------------------- فروشگاه -------------------------------------------------------*/
	prices();
	$('.field-name-unavailable').each(function(){
		$(this).parent().children('.add-to-cart').css({'display' : 'none'});
	});
	$('.group-left .field-name-unavailable #unavailable').parents(".node").addClass("node-unavailable");
	// $('.group-footer  .view-relative-contents  .view-content').children().each(function(){
		// if($(this).children().children('.field-name-unavailable').length){
			// $(this).children().children('.add-to-cart').css({'display' : 'none'});
		// }
	// });

	/*------------------------------------------------- مربوط به کاربر -------------------------------------------------------*/
	$('div#quicktabs-user_contents .ui-tabs-panel .views-row, div#block-quicktabs-user-bookmark .ui-tabs-panel .views-row,div#quicktabs-user_bookmark .ui-tabs-panel .views-row').each(function(){
		if($(this).children('div:nth-child(3)').length){
			$(this).children('div:nth-child(1)').remove();
		}
	});
	$('.comment-form .form-type-textarea label').each(function(){
		if($(this).text().indexOf("Comment") >= 0){
			$(this).text('نظر خود را بنویسید');
		}
	});
if($('.form-managed-file').find('.file-resup-wrapper').length){$('.form-managed-file').addClass('has-resumeable')}


	$('#block-block-45').find('.close-banner').click(function(){
		$(this).parents('#block-block-45').slideUp();
		setCookie('banner', '1', 1);
	});
	if(getCookie('banner')){
		$('#block-block-45').slideUp();
	}
	
	if(!$('[id*=edit-panes-payment-payment-method-other] ~ span').length){
		$('[id*=edit-panes-payment-payment-method-other] + label').text('سایر (کارت به کارت، انتقال وجه به مستر کارت، واریز به حساب و ...)').after('<span>جهت كسب اطلاعات بيشتر از نحوه پرداخت ميتوانيد با آي دي مديريت موسسه ٨٠٨ در تلگرام در ارتباط باشيد: <a href="http://t.me/mojtaba808" target="_blank">@mojtaba808</a></span>');
	}
	$('[id*=edit-panes-payment-payment-method-other]').change(function(){
		$('[id*=edit-panes-payment-payment-method-other] ~ span').slideDown();
	});
	
	if($('.page-user-myresults #block-system-main > .content').children().length == 0){
		$('.page-user-myresults #block-system-main').css({'display' : 'none'});
	}
	else if($('.page-user-myresults #block-system-main > .content').children().length > 0){
		$('.page-user-myresults .empty-result').css({'display' : 'none'});
	}
}};
/*----------------------------------------------------------------------*/
/*
 * this section suggests the latest news/articles to users who already scrolled half the page
 * note: that we created a module to pull data from an address
 * see module "custom_808_ajax" for more info
 */
Drupal.behaviors.custom_808_ajax = {
	'attach': function(context) {
		//we suggest user when he scrolled half the page, and of course not in all pages
		var flag = false, page_flag = false;;
		var pages = ['.page-take' , '.page-cart' , '.page-user' , '.page-file'];
		for (i = 0; i < pages.length; i++) {
			if($(pages[i]).length){
				page_flag = true;
				break;
			}
		}
 		$(window).scroll(function() {
			if (($(this).scrollTop() > ($(document).height() * 0.4)) && flag != true && page_flag != true){ 
				setTimeout(function(){
					// ajax808/all_new/block is the url af a view which we want to suggest to end user
					$.get('/ajax808/all_new/block' , null, views_output);
				}, 15000);
				flag = true;  //for geting the contents for just once
			}
		});
	}
}
/*
 * ajax callback function impletention that parses the result and push it to 
 * the user as pnotify messages
 */
var views_output = function(response) {
    var result1 = $($.parseHTML(Drupal.parseJson(response).data)).find('ul');
	var news = [];
	result1.children('li').each(function(){
		news.push($(this));
	});
	// if the result has at least a row
	if(news.length){
		// send the result array to pnotify_output function to render it as pnotify messages
		pnotify_output(news);			
	}
}
/*
 * render its param array as pnotify messages
 * @param output: an array of news
 */
function pnotify_output(output){
	var myStack = {"dir1":"up", "dir2":"left", "push":"bottom"};
	// for the first row we send the message immediately whiteout any waiting
	new PNotify({
		text: output[0].html() ,
		type: "info",
		styling: "jqueryui",
		delay: 15000,
		icon: false,
		insert_brs: false,
		addclass: "stack-bottomright pnotify-news",
		stack: myStack
	});
	var i = 1;
	// we set the row to be sent automatically after every 45 seconds
	var interval = setInterval( function(){
		// stopping the Interval when the output array were finished
		if (i >= output.length - 1) {
			clearInterval(interval);
		}
		if (3 > $('.ui-pnotify').length) {
			new PNotify({
				text: output[i].html(),
				type: "info",
				styling: "jqueryui",
				animate_speed: "fast",
				delay: 15000,
				icon: false,
				insert_brs: false,
				addclass: "stack-bottomright pnotify-news",
				stack: myStack
			});
		} else {
			// stop showing more than 3 messages
			i--;
		}
		i++;
	},45000);
}


Drupal.parseJson = function (data) {
 // Use native JSON method when available.
 if ( typeof JSON === "object" && JSON.parse ) {
   data = JSON.parse(JSON.stringify(data));
 } 
 else {
   if ((data.substring(0, 1) != '{') && (data.substring(0, 1) != '[')) {
     return { status: 0, data: data.length ? data : Drupal.t('Unspecified error') };
   }
   data = (new Function("return " + data))();
 }
 return data;
};	


//CANVAS
window.onload = function(){
	if($('#smile').length){
		$.getScript('/sites/all/themes/sara/js/lib/floating-dots.js', function(){
			setInterval(createDots, 1000/30);
		});
	}
	
};
//color functions
function isdark(hexcolor){
    var r = parseInt(hexcolor.substr(1,2),16);
    var g = parseInt(hexcolor.substr(3,2),16);
    var b = parseInt(hexcolor.substr(5,2),16);
    var yiq = ((r*299)+(g*587)+(b*114))/1000;
    return (yiq >= 158) ? true : false;
}
//Function to convert rgb color to hex format
function rgb2hex(rgb) {
	var hexDigits = new Array("0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"); 
	rgb = rgb.match(/^rgb\((\d+),\s*(\d+),\s*(\d+)\)$/);
	function hex(x) {
		return isNaN(x) ? "00" : String(hexDigits[(x - x % 16) / 16]) + String(hexDigits[x % 16]);
	}
	if(typeof rgb !== 'undefined' && rgb !== null){
		return "#" + hex(rgb[1]) + hex(rgb[2]) + hex(rgb[3]);
	}
	return "#ffffff";
}

function money_format(x){
    return parseFloat(x, 10).toFixed(0).replace(/(\d)(?=(\d{3})+(?!\d))/g, "$1,").toString()
}

$(document).ready(function () {
	var $q = function(q, res){
		if (document.querySelectorAll) {
			res = document.querySelectorAll(q);
		} else {
			var d=document
				, a=d.styleSheets[0] || d.createStyleSheet();
			a.addRule(q,'f:b');
			for(var l=d.all,b=0,c=[],f=l.length;b<f;b++)
				l[b].currentStyle.f && c.push(l[b]);

			a.removeRule(0);
			res = c;
		}
		return res;
	}
	, addEventListener = function(evt, fn){
		window.addEventListener
			? this.addEventListener(evt, fn, false)
			: (window.attachEvent)
			? this.attachEvent('on' + evt, fn)
			: this['on' + evt] = fn;
	}
	, _has = function(obj, key) {
		return Object.prototype.hasOwnProperty.call(obj, key);
	}

	function loadImage (el, fn) {
		var src = el.getAttribute('src'),
			dataSrc = el.getAttribute('data-src');

		if (src != dataSrc) {
			el.src = el.getAttribute('data-src')
			fn ? fn() : null;
		}
	}

	function elementInViewport(el) {
		var rect = el.getBoundingClientRect()
		return (
			rect.top    >= 0
			&& rect.left   >= 0
			&& rect.top <= (window.innerHeight || document.documentElement.clientHeight)
			&& (rect.width > 0 && rect.height > 0)
		)
	}

	var images = []
		, query = $q('img.lazy')
		, processScroll = function(){
			for (var i = 0; i < images.length; i++) {
				if (elementInViewport(images[i])) {
					loadImage(images[i], function () {
						images[i].removeAttribute('data-src')
						images[i].classList.remove("lazy")
						images.splice(i, 1)
					});
				}
			};
		}
		, processScrollMobile = function(){
			for(var i = 0; i < images.length; i++) {
				loadImage(images[i], function() {
					images[i].removeAttribute('data-src')
					images[i].classList.remove("lazy")
					images.splice(i,1)
				});
			};
		}
	;
	// Array.prototype.slice.call is not callable under our lovely IE8
	for (var i = 0; i < query.length; i++) {
		images.push(query[i])
	}

	processScroll()
	addEventListener('scroll',processScroll)
	addEventListener('touchmove', processScrollMobile)
	var lazyLoading = setInterval(function(){
		if(images.length > 0)
			processScroll()
		else
			clearInterval(lazyLoading);
	}, 3000)
});

