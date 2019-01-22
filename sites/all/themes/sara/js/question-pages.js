$ = jQuery;
$(document).ready(function(){
    // tinyMCE.init({
        // mode : "textareas"
    // });
    /*preprocess*/
    var body = $('.page-question.node-type-questions');
    $('.page-question-list .field-name-field-experts a').each(function(){
        $(this).wrap( '<div class="field-item"></div>');
    });

    /*experts functionality*/
    $('.page-question .field-name-field-experts a').each(function(){
        var href = $(this).attr('href');
        var arr = href.split("/");
        $(this).attr('tid' , arr[3]);
        $(this).after('<div class="information"><div class="pic"></div><div class="data"><div></div><div></div></div></div>');
    });
    var ajax;
    $('.page-question .field-name-field-experts .field-item > a').on('mouseenter' , function(){
        $(this).parent().addClass('open');
        if(!$(this).next(".information").hasClass("filled")){
            var tid = $(this).attr('tid');
            var element = $(this);
            ajax = $.ajax({
                type: 'GET',
                url: '/experts/information/' + tid,
                success: function(result){
                    if(result['expert'] === true) element.next('.information').html('<div class="pic"><image src="'+ result['pic'] +'"/></div><div class="data"><div class="q-count">  سوالات این تخصص : ' + result['question_count'] + ' </div><div class="u-count"> کاربران این تخصص : ' + result['user_count'] + '</div><a href="/taxonomy/term/' + result['tid'] +' " target="_blank">بیشتر...</a></div>');
                    else element.next('.information').html('<div class="pic"><image src="'+ result['pic'] +'"/></div><div class="data"><div class="q-count">  سوالات این تگ : ' + result['question_count'] + ' </div><a href="/taxonomy/term/' + result['tid'] +' " target="_blank">بیشتر...</a></div>');
                    element.next('.information').addClass("filled");
                    
                },
                error: function (xhr) {
                }
            });    
        }
    });
    $('.page-question .field-name-field-experts .field-item').on('mouseleave' , function(){
        $(this).removeClass('open');
        if(ajax){
            ajax.abort();
        }
    });    

    /*change experts link*/
    $('.page-question .field-name-field-experts .field-item').each(function(){
        var a = $(this).find('a');
        a.attr('href', '/question/list?field_experts_tid='+ a.text());
        a.attr('target', '_blank');
    });
    $('.page-question-list .views-field-field-experts a').each(function(){
        $(this).attr('href', '/question/list?field_experts_tid='+$(this).text());
    });

    /*check question is published or not*/
    if(Drupal.settings.status){
        body.addClass(Drupal.settings.status);
        body.find('#comments form').slideUp();
        body.find('#comments h2.title.comment-form').removeClass('open');
    }else{
        body.find('#comments h2.title.comment-form').addClass('open');
    }
    
    /*the answer button functionality*/
    body.find('#comments h2.title.comment-form').click(function(){
        if(!Drupal.settings.status){
            $(this).toggleClass('open');
            body.find('#comments form').slideToggle();
        }
    });

    /*check if there is proved comment */
    var asker_proove = advisor_prove = 0;
    body.find('.content .comment').each(function(){
        if($(this).find('.field-name-field-prove-asker .field-item').text() == '1'){
            $(this).addClass("proved_by_asker");
            asker_proove = 1;
            /*
            var temp = $(this).outerHTML();
            var temp1 = $(this).prev().outerHTML();
            $(this).remove();
            $(this).prev().remove();
            $('#comments > h2:nth-child(3)').after(temp1 + temp);
            */
        }
    });
    body.find('.content .comment').each(function(){
        if($(this).find('.field-name-field-prove-advisor .field-item').text() == '1'){
            $(this).addClass("proved_by_advisor");
            advisor_prove = 1;
            /*
            var temp = $(this).outerHTML();
            var temp1 = $(this).prev().outerHTML();
            $(this).remove();
            $(this).prev().remove();
            $('#comments > h2:nth-child(3)').after(temp1 + temp);
            */
        }
    });
    
    /*add title for proved comments*/
    body.find('#comments > .comment:last-of-type').addClass("last-comment-advisor");
    body.find('.content .comment .field-name-field-prove-asker').attr('title','تایید شده توسط نویسنده سوال');
    body.find('.content .comment.proved_by_advisor > div.group-left').attr('title','تایید شده توسط مشاور');
    body.find('.content .comment.author-advisor > div.group-left').attr('title','پاسخ داده شده توسط مشاور');
    
    /*check for enable prove button or not*/
    if(asker_proove == 0 && (Drupal.settings.Uid == Drupal.settings.asker || body.hasClass('role-administrator'))){
        body.find('.content .comment').each(function(){
            var comment_id = $(this).prev().attr('id');
            var cid = comment_id.substr(comment_id.indexOf("-") + 1);
            if(!$(this).parent().hasClass("indented")) {
                $(this).find('.group-left ul').append('<li id="' + cid + '" class="asker_aprove"><a>تایید نویسنده سوال</a></li>');
            }
        });
    }
    if((advisor_prove == 0) && (body.hasClass('role-advisor') || body.hasClass('role-administrator'))){
        body.find('.content .comment').each(function(){
            if(!$(this).hasClass("author-advisor")){
                var comment_id = $(this).prev().attr('id');
                var cid = comment_id.substr(comment_id.indexOf("-") + 1);
                if(!$(this).parent().hasClass("indented")) {
                    $(this).find('.group-left ul').append('<li id="' + cid + '" class="advisor_aprove"><a>تایید مشاور</a></li>');
                }
            }
        });
    }

    /*proved comment ajax method*/
    body.find('.advisor_aprove > a').on('click', function(){
        $(this).after('<div class="ajax-progress ajax-progress-throbber"><div class="throbber"></div></div>');
        var cid = $(this).parent().attr('id');

        $.ajax({
            type: 'POST',
            url: '/comment/prove/advisor/'+ cid,
            success: function(result){
                if(result[0] == 1){
                    $('#'+ result[1]).closest('.comment').addClass("proved_by_advisor");
                    body.find('.content .comment').each(function(){
                        $(this).find('.group-left .advisor_aprove').remove();
                    });
                    $('#'+ result[1]).find('.ajax-progress.ajax-progress-throbber').hide();
                }
            },
            error: function (xhr) {
                console.log(xhr);
            }
        });
    });
    body.find('.asker_aprove > a').on('click', function(){
        $(this).after('<div class="ajax-progress ajax-progress-throbber"><div class="throbber"></div></div>');
        var cid = $(this).parent().attr('id');
        $.ajax({
            type: 'POST',
            url: '/comment/prove/asker/'+ cid,
            success: function(result){
                if(result[0] == 1){
                    $('#'+ result[1]).closest('.comment').addClass("proved_by_asker");
                    body.find('.content .comment').each(function(){
                        $(this).find('.group-left .asker_aprove').remove();
                    });
                    $('#'+ result[1]).find('.ajax-progress.ajax-progress-throbber').hide();
                }
            },
            error: function (xhr) {
                console.log(xhr);
            }
        });
    });

    /*statistic part */
    body.find('#comments h2.title.comment-form').attr('id', 'answer-question');
    body.find('.answer_link > a').click(function(e) {
        e.preventDefault();
        if(body.hasClass('not-logged-in')){
            body.find("#block-panels-mini-user-panel h2.block-title").click();
        }
        else{
            $('html, body').animate({
                scrollTop: ($('#answer-question').offset().top - 80)
            }, 700);
        }
    });
    
    /*social share*/
    $('.field-name-question-statistic .statistics').prepend('<div class="share-title">اشتراک</div>');
    body.find('.node-questions.view-mode-full > .group-header .field-name-question-statistic .statistics .share-title').click(function(){
        $('.node-questions.view-mode-full > .group-header .field-name-field-social-share').toggleClass('open');
        $('.node-questions.view-mode-full > .group-header .field-name-field-social-share .field-items').slideToggle();
    });

    /*unpublished*/
    $('.node-questions.view-mode-full.node-unpublished > .group-header .flag-outer.flag-outer-follow-question').before('<div class="not-published-btn"> تایید نشده </div>');

    /*creating edit link for authenicate user*/
    if(Drupal.settings.Uid == Drupal.settings.asker){
        var pagenid = window.location.pathname.split('/')[2];
        $('.node-questions.view-mode-full > .group-header .flag-outer.flag-outer-follow-question').before('<div class="edit-link"><a href="/node/'+ pagenid +'/edit" target="_blank" >ویرایش</a></div>');
    }
});


Drupal.behaviors.question_pages = {attach: function (context, settings) {
	
	$('.node-questions .comment-form .username:not(.has-img)').each(function(i){
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


    /*delete reply of reply comment*/
        $('.page-question.node-type-questions').find('.indented').each(function () {
        $(this).find('.group-left .group-more').each(function () {
                console.log($(this).find('ul').children().length);
                if ($(this).find('ul').children().length > 1) {
                    $(this).find('.comment-reply').css({"display": "none"});
                }
                else if ($(this).find('ul').children().length == 1) {
                    $(this).css({"display": "none"});
                }
            }
        );

    });
}};