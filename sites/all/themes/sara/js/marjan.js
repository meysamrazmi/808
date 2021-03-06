var $ = jQuery;
$(document).ready(function () {
    
    /*erasing pane-uc-order when its empty*/
    if (!$('.page-user .pane-uc-orders-user .view-uc-orders-user div').length) {
        $('.pane-uc-orders-user').remove();
    }
    
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



	/* tag pedias js*/
	all_pedia_js();

	/*using owl in user relation page*/
	if($('.page-user-relationships #block-views-user-experts-suggestion-users').length){
		$('.view-display-id-suggestion_users > .view-content').addClass('owl-carousel');
	}
    
    /*using owl in first page video block*/
    if($('.front .crousal-galley .view-content').length){
		$('.front .crousal-galley .view-content').addClass('owl-carousel');
	}

    /*-----------------landing BIM --------------*/

    if($('.page-landing.page-bim #relatives.films-section .view-tags-content .view-content').length){
        $('.page-landing.page-bim #relatives.films-section .view-tags-content .view-content .views-row').each(function () {
            if($(this).find('.field-name-title a').attr('href') == '/landing/bim'){
                $(this).remove();
            }
        });
    }
	if($('.page-landing.page-bim .view-tags-content').length){
        $('.page-landing.page-bim .view-tags-content .view-content').addClass('owl-carousel');
	}
	if($('.page-landing.page-bim .view-tag-content').length){
        $('.page-landing.page-bim .view-tag-content .view-content').addClass('owl-carousel');
	}
    if($('.page-seismosoft.page-node-20681 .view-tags-content').length){
        $('.page-seismosoft.page-node-20681 .view-tags-content .view-content').addClass('owl-carousel');
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
    
    /*closing landing-job submittion*/
    /*$('.page-node-14314 #webform-client-form-14314 .form-actions,.page-node-14314 #webform-client-form-14314  .captcha').remove();*/
    /*adjusting view-empty result for bookmarks*/
    if($('.page-user-bookmarks #block-system-main > div > div > div.view-empty').length){
        $('.page-user-bookmarks #block-system-main').css({
            'display':'block'
        });
    }
    
    /*creating hint for bookmarks*/
    if ($('.flag-outer-bookmarks,.flag-outer-bookmark-tag').length){
        $('.flag-outer-bookmarks,.flag-outer-bookmark-tag').append('<div class="flag-hint"><span>این مطلب را به لیست نشان شده ها اضافه کنید</span></div>')
    }
	if ($('.flag-outer-notify-product-existing-status').length){
        $('.flag-outer-notify-product-existing-status').append('<span class="flag-product-hint">زمانی که  این محصول موجود است به من اطلاع بده</span>');
		$('.flag-outer-notify-product-existing-status').addClass('btn');
    }
    if($('#college-elmi-block > div > div > div > div.views-row').length){
        $('#college-elmi-block > div > div > div > div.views-row').each(function(){
            if(!$(this).find('.views-field-field-image').length){
               // $(this).prepend('<img src="https://civil808.com/sites/all/themes/sara/images/nophoto.png" width="117" height="98" alt="no-picutre">');
            }
        });
    }
     
    $(".user-left-links .column-inside .region-first .pane-content .azl a").text('در ارتباط');
    $(".page-user .main-tab .tabs.primary .myresults a").text('نتایج آزمون');
    
	$("#user-register-form .field-name-field-laws label").empty();
	$("#user-register-form .field-name-field-laws label").append('<a href="https://civil808.com/node/865" target="_blank" title="قوانین سایت">شرایط و قوانین</a>&nbsp;سایت را می پذیرم.<span class="form-required" title="این فیلد اجباری است.">*</span>');
	
	$("#user-profile-form .field-name-field-laws label").empty();
	$("#user-profile-form .field-name-field-laws label").append('<a href="https://civil808.com/node/865" target="_blank" title="قوانین سایت">شرایط و قوانین</a>&nbsp;سایت را می پذیرم.<span class="form-required" title="این فیلد اجباری است.">*</span>');
    
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
    // add homepage link to every tag pages
    $('.page-pedia.page-tags h1#page-title').after('<a href="/pedia" class="mainpedia1" target="_blank">صفحه اصلی دانشنامه</a>');

    //add a blog link to pedia homepage
    $('.page-pedia:not(.page-node):not(.page-tags):not(.page-tag) h1#page-title').after('<a href="/node/14053" class="btn mainpedia" target="_blank">دانشنامه چیست</a>');

	$('.page-eng .pane-jquery-countdown-timer-jquery-countdown-timer').append('<a style="font-size:16px;color: #000000;margin: 15px auto;display: block;max-width: 373px;background-color: #90CAF6;padding: 20px 16px;border-radius: 11px;text-align: center;" href="/node/19807" target="_blank"> مشاوره تخصصی آزمون ورود به حرفه عمران و معماری به همراه ورکشاپ رایگان آموزشی </a>');
    $('.page-eng .pane-jquery-countdown-timer-jquery-countdown-timer').append('<a style="font-size:16px;color: #000000;margin: 15px auto;display: block;max-width: 373px;background-color: #90CAF6;padding: 20px 16px;border-radius: 11px;text-align: center;" href="/node/20190" target="_blank"> برای ثبت نام دوره حضوری ورود به حرفه کلیک کنید </a>');

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
                $(this).parent.prepend('<img src="https://civil808.com/sites/all/themes/sara/images/nophoto.png" width="'+w+'" height="'+h+'" alt="no-picutre">');
            }
        });
    }
}
*/

function all_pedia_js() {
    /*ancher of pedia node*/
    $('.page-taxonomy.page-pedia .view-mode-full .group-anchor > div').prepend('<div class="divanchors"></div>');

    if($('.page-taxonomy.page-pedia .node-type-relative').length){
        $('.page-taxonomy.page-pedia .node-type-relative').each(function(){
            var anchclass = $(this).attr('id');
            var spananch = $(this).find('.field-label').text();
            $('.divanchors').append('<a class="'+ anchclass +'" href="#'+anchclass+'"><span>'+spananch+'</span></a>');

            if( (window.matchMedia('(max-width: 600px)').matches && $(this).children('.field-items').children().length > 1) ||
                (window.matchMedia('(max-width: 900px)').matches && $(this).children('.field-items').children().length > 2) ||
                (window.matchMedia('(max-width: 1200px)').matches && $(this).children('.field-items').children().length > 3) ||
                $(this).children('.field-items').children().length > 4) {
                if($(this).attr('id') != 'questions')
                    $(this).children('.field-items').addClass('owl-carousel');
            }
        });

        /*creating default image for tags*/
        $('.page-taxonomy.page-pedia .node-type-relative > div.field-items > div.node').each(function(){
            if(!$(this).find('.field-type-image').length){
                $(this).find('.group-header').prepend('<img src="https://civil808.com/sites/all/themes/sara/images/nophoto.png" width="240" height="140" alt="no-picutre">');
            }
        });

        /*creating default image for pedia node refrenced node ---- with owl crousal
        $('.page-taxonomy.page-pedia .field-type-node-reference > div.field-items .owl-item').each(function(){
            if(!$(this).find('.field-type-image').length){
                $(this).find('.group-header').prepend('<img src="https://civil808.com/sites/all/themes/sara/images/nophoto.png" width="240" height="140" alt="no-picutre">');
            }
        });*/
    }
    else{
        $('.page-taxonomy.page-pedia .view-mode-full .group-anchor > div .flag-outer-bookmark-tag').css('top','40px');
    }

    $('.divanchors a , .page-moshaver a.moshaver-links:not(.b) , .page-moshaver .search-links').click(function(e) {
        e.preventDefault();
        $('html, body').animate({
            scrollTop: $($(this).attr('href')).offset().top - 50
        }, 700);
    });

    if($('.page-taxonomy.page-pedia .node-type-relative .view-user-experts').length){
        $('.page-taxonomy.page-pedia .node-type-relative .view-user-experts').each(function(){
            if( (window.matchMedia('(max-width: 600px)').matches && $(this).find('.view-content').children().length > 1) ||
                (window.matchMedia('(max-width: 900px)').matches && $(this).find('.view-content').children().length > 2) ||
                (window.matchMedia('(max-width: 1200px)').matches && $(this).find('.view-content').children().length > 3) ||
                ($(this).find('.view-content').children().length > 4) ){
                $(this).find('.view-content').addClass('owl-carousel');
            }
        });
    }

    $('.node-type-relative .view-user-experts').each(function(){
        if($(this).children().length == 0){
            var anchorTitle = $(this).parents('.node-type-relative').attr('id');
            $('.page-taxonomy.page-pedia .view-mode-full .group-anchor > div > .divanchors a.' + anchorTitle).remove();
            $(this).parents('.node-type-relative').remove();
        }
    });

    if($('.page-taxonomy.page-pedia').length){
        if(!$('.term-listing-heading > .vocabulary-expert > .group-header > .group-anchor .taxonomy-term-description').length){
            $('.flag-outer-bookmark-tag').remove()
        }
    }

}