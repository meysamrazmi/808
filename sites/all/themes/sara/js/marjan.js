var $ = jQuery;
$(document).ready(function () {
    
    /*erasing pane-uc-order when its empty*/
    if (!$('.page-user .pane-uc-orders-user .view-uc-orders-user div').length) {
        $('.pane-uc-orders-user').remove();
    }

    console.log($('#page-title').height());
    
    /*adjust position of bookmark iconin node-page*/
    $('.page-node:not(.page-gallery):not(.page-shop):not(.page-pedia) div.tabs')
		.css({'top':$('#page-title').height()});

    /*adjust position of admin-tabs in node-page*/
    $('.page-node:not(.page-gallery):not(.page-shop):not(.page-pedia):not(.page-college) .flag-outer-bookmarks')
		.css({'top':-$('#page-title').height()-2});

    /*adjust position of admin-tabs in product-page*/
    if($('.page-shop #page-title').height() >= 80){
        $('.page-shop .flag-outer-bookmarks')
            .css({'top':-$('#page-title').height()-40});
	}

	/*adjust position of bookmark icon and admin-tabs in product-page*/
    $('.page-shop.page-products div.tabs')
        .css({'top':$('#page-title').height()-13});

    /*shop*/
    $('.node.node-product.view-mode-full .group-left > .display-price,.node.node-product-kit.view-mode-full .group-left > .display-price').prepend('<span>قیمت نهایی:</span>');
    
    /*ancher of pedia node*/
	$('.page-node.page-pedia .view-mode-full .group-anchor > div').prepend('<div class="divanchors"></div>');
    
    if($('.page-node.page-pedia .field-type-node-reference').length){
        $('.page-node.page-pedia .field-type-node-reference').each(function(){
            var anchclass = $(this).attr('class').split(" ")[1].substr(17);
            var spananch = $(this).find('.field-label').text().slice(0,-2);
            $('.divanchors').append('<a class="'+ anchclass +'" href="#'+anchclass+'"><span>'+spananch+'</span></a>');
            $(this).attr('id', anchclass);
			
			if( (window.matchMedia('(max-width: 600px)').matches && $(this).children('.field-items').children().length > 1) ||
				(window.matchMedia('(max-width: 900px)').matches && $(this).children('.field-items').children().length > 2) ||
				(window.matchMedia('(max-width: 1200px)').matches && $(this).children('.field-items').children().length > 3) ||
				$(this).children('.field-items').children().length > 4
			 ) {
				$(this).children('.field-items').addClass('owl-carousel');
			}			
        });
        
        /*creating default image for pedia node refrenced node*/
        $('.page-node.page-pedia .field-type-node-reference > div.field-items > div').each(function(){
            if(!$(this).find('.field-type-image').length){
                $(this).find('.group-header').prepend('<img src="http://civil808.com/sites/all/themes/sara/images/nophoto.png" width="240" height="140" alt="no-picutre">');
            }
        });
    }

    if($('.page-node.page-pedia .field-name-user-with-expert').length){
		$('.field-name-user-with-expert').attr('id', 'advisor_experts');
		if($('.view-display-id-pedia_experts_advisors > .view-content').children().length < 4){
				$('.view-display-id-pedia_experts_advisors > .view-content .views-row').css("float", "none");
		}
		if( (window.matchMedia('(max-width: 600px)').matches && $('.view-display-id-pedia_experts_advisors > .view-content').children().length > 1) ||
			(window.matchMedia('(max-width: 900px)').matches && $('.view-display-id-pedia_experts_advisors > .view-content').children().length > 2) ||
			(window.matchMedia('(max-width: 1200px)').matches && $('.view-display-id-pedia_experts_advisors > .view-content').children().length > 3) ||
			($('.view-display-id-pedia_experts_advisors > .view-content').children().length > 4) ){
				$('.view-display-id-pedia_experts_advisors > .view-content').addClass('owl-carousel');
		}
		
		$('.divanchors').append('<a class="advisors" href="#advisor_experts"><span>مشاوران متخصص</span></a>');
	}
	
	if($('.page-node.page-pedia .field-name-all-pedia-experts-user').length){
		$('.field-name-all-pedia-experts-user').attr('id', 'user_experts');
		if($('.view-display-id-pedia_experts_users > .view-content').children().length < 4){
				$('.view-display-id-pedia_experts_users > .view-content .views-row').css("float", "none");
		}
		if( (window.matchMedia('(max-width: 600px)').matches && $('.view-display-id-pedia_experts_users > .view-content').children().length > 1) ||
			(window.matchMedia('(max-width: 900px)').matches && $('.view-display-id-pedia_experts_users > .view-content').children().length > 2) ||
			(window.matchMedia('(max-width: 1200px)').matches && $('.view-display-id-pedia_experts_users > .view-content').children().length > 3) ||
			($('.view-display-id-pedia_experts_users > .view-content').children().length > 4) ){
				$('.view-display-id-pedia_experts_users > .view-content').addClass('owl-carousel');
		}
		
		$('.divanchors').append('<a class="users" href="#user_experts"><span>کاربران متخصص</span></a>');
	}

	/*using owl in user relation page*/
	if($('.page-user-relationships #block-views-user-experts-suggestion-users').length){
		$('.view-display-id-suggestion_users > .view-content').addClass('owl-carousel');
	}
    
    /*using owl in first page video block*/
    if($('.front .crousal-galley .view-content').length){
		$('.front .crousal-galley .view-content').addClass('owl-carousel');
	}

	if($('.page-landing.page-bim .view-tags-content').length){
        $('.page-landing.page-bim .view-tags-content .view-content').addClass('owl-carousel');
	}

	/*runing owl*/
	if($('.owl-carousel').length){
		$.getScript('/sites/all/themes/sara/js/lib/owl.carousel.min.js', function(){
			$('.owl-carousel').not('.view-online-users .owl-carousel').owlCarousel({
				rtl:true,
				loop:true,
				margin:15,
				responsiveClass:true,
				nav:true,
				responsive:{
					0:{items:1},
					400:{items:2, margin:5},
					700:{items:3},
					1000:{items:4}
				}
			});
			$('.owl-prev').text('بعدی')
			$('.owl-next').text('قبلی')
		})
	}

	/*using owl for online-users*/
	/* $('.view-online-users > .view-content').addClass('owl-carousel'); */
	if((window.matchMedia('(max-width: 400px)').matches && $('.view-online-users > .view-content').children().length > 2) ||
		(window.matchMedia('(max-width: 700px)').matches && $('.view-online-users > .view-content').children().length > 4) ||
		($('.view-online-users > .view-content').children().length > 7) ){
			$('.view-online-users > .view-content').addClass('owl-carousel');
	}
	if($('.view-online-users .owl-carousel').length){
		$.getScript('/sites/all/themes/sara/js/lib/owl.carousel.min.js', function(){
			$('.view-online-users .owl-carousel').owlCarousel({
				rtl:true,
				loop:true,
				margin:15,
				responsiveClass:true,
				nav:true,
				dots:false,
				autoplay: true,
				autoPlaySpeed: 2000,
				
				responsive:{
					0:{items:2},
					400:{items:3, margin:5},
					700:{items:5},
					1000:{items:8}
				}
			});
			$('.owl-prev').text('')
			$('.owl-next').text('')
		})
	}

    /*creating default image for pedia node refrenced node ---- with owl crousal*/
    $('.page-node.page-pedia .field-type-node-reference > div.field-items .owl-item').each(function(){
        if(!$(this).find('.field-type-image').length){
            $(this).find('.group-header').prepend('<img src="http://civil808.com/sites/all/themes/sara/images/nophoto.png" width="240" height="140" alt="no-picutre">');
        }
    });

	if($('.page-node.page-pedia #comments').length){
		$('.divanchors').append('<a class="commentanch" href="#comments"><span>نظرات</span></a>');
    }

    $('.divanchors a , .page-moshaver a.moshaver-links:not(.b) , .page-moshaver .search-links').click(function(e) {
        e.preventDefault();
        $('html, body').animate({
            scrollTop: $($(this).attr('href')).offset().top - 50
        }, 700); 
    });
    
    /*closing landing-job submittion*/
    /*$('.page-node-14314 #webform-client-form-14314 .form-actions,.page-node-14314 #webform-client-form-14314  .captcha').remove();*/
    /*adjusting view-empty result for bookmarks*/
    if($('.page-user-bookmarks #block-system-main > div > div > div.view-empty').length){
        $('.page-user-bookmarks #block-system-main').css({
            'display':'block'
        });
    }
    
    /*creating hint for bookmarks*/
    if ($('.flag-outer-bookmarks').length){
        $('.flag-outer-bookmarks').append('<div class="flag-hint"><span>این مطلب را به لیست نشان شده ها اضافه کنید</span></div>')
    }
	if ($('.flag-outer-notify-product-existing-status').length){
        $('.flag-outer-notify-product-existing-status').append('<span class="flag-product-hint">زمانی که  این محصول موجود است به من اطلاع بده</span>');
		$('.flag-outer-notify-product-existing-status').addClass('btn');
    }
    if($('#college-elmi-block > div > div > div > div.views-row').length){
        $('#college-elmi-block > div > div > div > div.views-row').each(function(){
            if(!$(this).find('.views-field-field-image').length){
               // $(this).prepend('<img src="http://civil808.com/sites/all/themes/sara/images/nophoto.png" width="117" height="98" alt="no-picutre">');
            }
        });
    }
     
    $(".user-left-links .column-inside .region-first .pane-content .azl a").text('در ارتباط');
    $(".page-user .main-tab .tabs.primary .myresults a").text('نتایج آزمون');
    
	$("#user-register-form .field-name-field-laws label").empty();
	$("#user-register-form .field-name-field-laws label").append('<a href="http://civil808.com/node/865" target="_blank" title="قوانین سایت">شرایط و قوانین</a>&nbsp;سایت را می پذیرم.<span class="form-required" title="این فیلد اجباری است.">*</span>');
	
	$("#user-profile-form .field-name-field-laws label").empty();
	$("#user-profile-form .field-name-field-laws label").append('<a href="http://civil808.com/node/865" target="_blank" title="قوانین سایت">شرایط و قوانین</a>&nbsp;سایت را می پذیرم.<span class="form-required" title="این فیلد اجباری است.">*</span>');
    
	$('.not-logged-in.not-same-user.profile .user-left-links .add a, .not-logged-in.not-same-user.profile .user-left-links .send-message a').click(function(e){
		e.preventDefault();
		$('#block-panels-mini-user-panel h2.block-title').click();
	});
	
    /*removing 2 taxonomy from pedia ui*/
    $('.field-name-field-dastebandimemar .field-items .field-item').each(function() {
	   if($(this).text() == 'رشته' || $(this).text() == 'نوع'){
	   	$(this).remove();
	   }
    });
	$('.page-pedia.page-tag h1#page-title').after('<a href="/pedia" class="mainpedia" target="_blank">صفحه اصلی دانشنامه</a>');
	
	$('.page-eng .pane-jquery-countdown-timer-jquery-countdown-timer').append('<a style="font-size:16px;color: #000000;margin: 15px auto;display: block;max-width: 373px;background-color: #90CAF6;padding: 20px 16px;border-radius: 11px;text-align: center;" href="/landing/eng97" target="_blank">ثبت نام در همایش آشنایی با آزمون آمادگی ورود به حرفه داخلی و خارجی، رشته عمران و معماری سال 97 </a>');

    /*removing administration content from user-content block*/
    /*----------work fine but until removing it from main tab, i commenting it
    if($('body:not(.role-administrator):not(.role-editor) .pane-quicktabs-user-contents').length){  
	   $('body:not(.role-administrator):not(.role-editor) .pane-quicktabs-user-contents .ui-state-default').each(function(){
	   	   if($(this).attr('aria-controls') == 'qt-user_contents-ui-tabs11'){
	   	   	   $(this).remove();
	   	   }
	   });
        if($('body:not(.role-administrator):not(.role-editor) .pane-quicktabs-user-contents div#qt-user_contents-ui-tabs11').length){
            $('body:not(.role-administrator):not(.role-editor) .pane-quicktabs-user-contents div#qt-user_contents-ui-tabs11').remove();
        }
    }
    */

    /*-----------------------------------------*/
    /*temporary code for put discount description in 4 courses*/
    /*node 16827*/
    if($('.page-16827').length){
        var selector = '.page-16827 .form-item-attributes-37-118 ';
        if ($(selector + 'label').html().substring(18).substring(0, 9) === "1,100,000")
            $(selector)
                .prepend('<div class="option-takhfif">با 350 هزار تومان تخفیف برای 5 نفر اول</div>');
        else if ($(selector + 'label').html().substring(18).substring(0, 9) === "1,200,000")
            $(selector)
                .prepend('<div class="option-takhfif" >با 250 هزار تومان تخفیف برای 5 نفر دوم</div>');
        else if ($(selector + 'label').html().substring(18).substring(0, 9) === "1,250,000")
            $(selector)
                .prepend('<div class="option-takhfif">با 200 هزار تومان تخفیف برای 5 نفر سوم</div>');
        else if ($(selector + 'label').html().substring(18).substring(0, 9) === "1,300,000")
            $(selector)
                .prepend('<div class="option-takhfif">با 150 هزار تومان تخفیف برای 5 نفر چهارم</div>');
    }
	/*node 16828*/
    if($('.page-16828').length){
        var selector2 = '.page-16828 .form-item-attributes-36-117 ';
        if ($(selector2 + 'label').html().substring(16).substring(0, 7) === "600,000")
            $(selector2)
                .prepend('<div class="option-takhfif">با 200 هزار تومان تخفیف برای 4 نفر اول</div>');
        else if ($(selector2 + 'label').html().substring(16).substring(0, 7) === "650,000")
            $(selector2)
                .prepend('<div class="option-takhfif">با 150 هزار تومان تخفیف برای 4 نفر دوم</div>');
        else if ($(selector2 + 'label').html().substring(16).substring(0, 7) === "700,000")
            $(selector2)
                .prepend('<div class="option-takhfif">با 100 هزار تومان تخفیف برای 4 نفر سوم</div>');
        else if ($(selector2 + 'label').html().substring(16).substring(0, 7) === "725,000")
            $(selector2)
                .prepend('<div class="option-takhfif">با 75 هزار تومان تخفیف برای 4 نفر چهارم</div>');
    }
    /*node 18335*/
    if($('.page-18335').length){
        var selector3 =
            '.page-18335 .form-item-attributes-58 #edit-attributes-58--3 .form-item-attributes-58:first-child ';
        if ($(selector3 + ' label').html().substring(23).substring(0,7) === "300,000")
            $(selector3)
                .prepend('<div class="option-takhfif">با 150 هزار تومان تخفیف برای 15 نفر اول</div>');
        else if ($(selector3 + ' label').html().substring(23).substring(0,7) === "375,000")
            $(selector3)
                .prepend('<div class="option-takhfif">با 75 هزار تومان تخفیف برای 5 نفر چهارم</div>');
    }
    /*node 18334    */
    if($('.page-18334').length){
        var selector4 =
            '.page-18334 .form-item-attributes-57 #edit-attributes-57--3 .form-item-attributes-57:first-child ';
        if ($(selector4 + 'label').html().substring(23).substring(0,7) === "300,000")
            $(selector4)
                .prepend('<div class="option-takhfif">با 150 هزار تومان تخفیف برای 5 نفر اول</div>');
        else if ($(selector4 + 'label').html().substring(23).substring(0,7) === "330,000")
            $(selector4)
                .prepend('<div class="option-takhfif">با 120 هزار تومان تخفیف برای 5 نفر دوم</div>');
        else if ($(selector4 + 'label').html().substring(23).substring(0,7) === "350,000")
            $(selector4)
                .prepend('<div class="option-takhfif">با 100 هزار تومان تخفیف برای 5 نفر سوم</div>');
        else if ($(selector4 + 'label').html().substring(23).substring(0,7) === "375,000")
            $(selector4)
                .prepend('<div class="option-takhfif">با 75 هزار تومان تخفیف برای 5 نفر چهارم</div>');

    }
});

/*
function default_pic(x,w,h) {
    //creating default image
    if(x.length){
        x.each(function(){
            if(!$(this).find('.views-field-field-image').length){
                $(this).parent.prepend('<img src="http://civil808.com/sites/all/themes/sara/images/nophoto.png" width="'+w+'" height="'+h+'" alt="no-picutre">');
            }
        });
    }
}
*/

