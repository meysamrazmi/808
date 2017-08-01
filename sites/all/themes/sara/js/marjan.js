var $ = jQuery;
$(document).ready(function () {
    
    /*erasing pane-uc-order when its empty*/
    if (!$('.page-user .pane-uc-orders-user .view-uc-orders-user div').length) {
        $('.pane-uc-orders-user').remove();
    }
    
    /*adjust position of bookmark icon and admin-tabs in node-page*/
    $('.page-node:not(.page-gallery):not(.page-shop):not(.page-pedia) div.tabs').css({'top':$('#page-title').height()});
    
    /*shop*/
    $('.node.node-product.view-mode-full .group-left > .display-price,.node.node-product-kit.view-mode-full .group-left > .display-price').prepend('<span>قیمت نهایی:</span>');
    
    /*ancher of pedia node*/
    if($('.page-node.page-pedia .field-type-node-reference').length){
        $('.page-node.page-pedia .view-mode-full .group-anchor > div').prepend('<div class="divanchors"></div>');
        $('.page-node.page-pedia .flag-outer-bookmarks').css({'top': 91});
        $('.page-node.page-pedia .field-type-node-reference').each(function(){
            var anchclass = $(this).attr('class').split(" ")[1].substr(17);
            var spananch = $(this).find('.field-label').text().slice(0,-2);
            $('.divanchors').append('<a class="'+ anchclass +'" href="#'+anchclass+'"><span>'+spananch+'</span></a>');
            $(this).attr('id', anchclass);
        });
        if($('.page-node.page-pedia #comments').length){
            $('.divanchors').append('<a class="commentanch" href="#comments"><span>نظرات</span></a>');
        }
        
        /*creating default image for pedia node refrenced node*/
        $('.page-node.page-pedia .field-type-node-reference > div.field-items > div').each(function(){
            if(!$(this).find('.field-type-image').length){
                $(this).find('.group-header').prepend('<img src="http://civil808.com/sites/all/themes/sara/images/nophoto.png" width="240" height="140" alt="no-picutre">');
            }
        });
    }
    $('.divanchors a , .page-moshaver a.moshaver-links:not(.b)').click(function(e) {
        e.preventDefault();
        $('html, body').animate({
            scrollTop: $($(this).attr('href')).offset().top - 50
        }, 700); 
    });
    
    /*closing landing-job submittion*/
    $('.page-node-14314 #webform-client-form-14314 .form-actions,.page-node-14314 #webform-client-form-14314  .captcha').remove();
    
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
    
    /*removing 2 taxonomy from pedia ui*/
    $('.field-name-field-dastebandimemar .field-items .field-item').each(function() {
	   if($(this).text() == 'رشته' || $(this).text() == 'نوع'){
	   	$(this).remove();
	   }
    });
    $('.page-pedia.page-tag h1#page-title').after('<a href="/pedia" class="mainpedia" target="_blank">صفحه اصلی دانشنامه</a>');
    
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



