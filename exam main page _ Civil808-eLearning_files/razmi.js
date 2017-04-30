var $ = jQuery;
$(document).ready(function () {

	var nav = $('.pane-menu-main-civil');
	$(window).scroll(function () {
        if ($(this).scrollTop() > 100) {
            nav.addClass("topfix");
        } else {
            nav.removeClass("topfix");
        }
    });

	var nava = $('.pane-menu-conference');
	$(window).scroll(function () {
        if ($(this).scrollTop() > 100) {
            nava.addClass("topfixc");
        } else {
            nava.removeClass("topfixc");
        }
		/*addCssToIframe();*/
    });
	
	//panels-flexible-region-11-software
	$('.panels-flexible-row-11-9').hover(function () {
		if (!$(this).hasClass('click')) {
			$(this).addClass('click');
			//$('#cboxOverlay').addClass('college-cover'); 
		}
		else{
			$(this).removeClass('click');
			$('#cboxOverlay').removeClass('college-cover');
		}
		
    });

	$( '.panels-flexible-row-11-8-inside .views-row' ).each(function( index ) {
		var t=index+1;
		var x = $(' .panels-flexible-row-11-8-inside .views-row-'+t+' .views-field-field-enable div' );
		console.log( t + ": " +  x.text() );
		if ( x.text() == '0') {
			x.parent().parent().addClass('enabledcourse');
		}
		else if( x.text() == '1'){
			x.parent().parent().addClass( "disabledcourse" );
		}
	});
	

/*-------------------------------------------------------------------------------------------------------------------------------*/
	
	//var addCssInterval = $interval(addCssToIframe, 500, 0, false);
	/*addCssToIframe();*/
	
/*-------------------------------------------------------------------------------------------------------------------------------*/
	//this line is for changing the height of twe columns in college's topics
//	applyHeight($(".college-body-right") , $(".college-body-left") , ($(".view-courses .view-filters").height()*-1) - 20);
	applyHeight($(".college-body-right") , $(".college-body-left") , 0);
	
/*-------------------------------------------------------------------------------------------------------------------------------*/
	var fixmenu = $('.container.main #block-taxonomy-menu-block-1');
	if (fixmenu.length){
		var topmenu = fixmenu.offset().top;
		topmenu = topmenu +fixmenu.height() ;
		var endfix = $('#block-views-online-users-block').offset().top;
		var newfix = endfix - fixmenu.height() -50;
		
		$(window).scroll(function () {
			if ($(this).scrollTop() > topmenu) {
				fixmenu.addClass("menufix");
				$("#block-panels-mini-sidebar-ads").css("margin-top" , fixmenu.height() );
			} 
			if( $(this).scrollTop() > newfix) {
				fixmenu.removeClass("menufix");
				$("#block-panels-mini-sidebar-ads").css("margin-top" , 0 );
			}
			if( $(this).scrollTop() < topmenu) {
				fixmenu.removeClass("menufix");
				$("#block-panels-mini-sidebar-ads").css("margin-top" , 0 );
			}
		});
	}
	/*var fixmenu2 = $('.courselinks');
	if (fixmenu2.length){
		var topmenu2 = fixmenu2.offset().top-50;
		//topmenu2 = topmenu2 +fixmenu2.height() ;
		//var newfix2 = $('.college-body-right').offset().top + $('.college-body-right').height() - fixmenu2.height() - 50 ;this is working fine
		var newfix2 = $('#taghvim').offset().top - fixmenu2.height() -50  ;

		$(window).scroll(function () {
			if ($(this).scrollTop() > topmenu2) {
				fixmenu2.addClass("menufix2");
			} 
			if( $(this).scrollTop() > newfix2) {
				fixmenu2.removeClass("menufix2");
			}
			if( $(this).scrollTop() < topmenu2) {
				fixmenu2.removeClass("menufix2");
			}
		});
	}
	*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
	//for changing the value of visitors of videos
	$('.page-videos .views-row').each(function (t) {
		i=t+1;
		var x = parseInt($('.videos .views-row-'+i+' .views-field-totalcount .field-content').text() ) ;//.toNum()
		if(x <= 50 ){
			x = (x*3.5);
		}else if(x<300){
			x = (x*3) + 25;
		}else if(x<600){
			x = (x*2.5) + 310;
		}else if(x<1000){
			x = (x*2) + 810;
		}else {
			x = (x*1) + 820;
		}
		console.log( "row-"+i+" : " + $('.videos .views-row-'+i+' .views-field-totalcount .field-content').text()+" ===> "+parseInt(x).toString());
		$('.videos .views-row-'+i+' .views-field-totalcount .field-content').text(parseInt(x).toString());
	});

/*-------------------------------------------------------------------------------------------------------------------------------*/
	var fixdiv = $('.course-info');
	if (fixdiv.length && $('.main').height() > (1.3 * fixdiv.height())){
		var divtop = fixdiv.offset().top;
		var footer = $('#footer');
		
		$(window).scroll(function () {
			if ($(this).scrollTop() > divtop - 66) {
				fixdiv.addClass("fixside");
				fixdiv.removeClass("endfix");
				fixdiv.css("margin-top", "0px" );
			} 
			if( $(this).scrollTop() > footer.offset().top - fixdiv.height() - 80) {
				fixdiv.removeClass("fixside");
				fixdiv.addClass("endfix");
				height = footer.offset().top - fixdiv.height() - divtop;
				$('.endfix').css("margin-top", height );
				//$(".endfix").css({ "margin-top" : height+"px"});
			}
			if( $(this).scrollTop() < divtop - 75) {
				fixdiv.removeClass("fixside");
				fixdiv.removeClass("endfix");
				fixdiv.css("margin-top", "0px" );
			}
		});
	}

/*-------------------------------------------------------------------------------------------------------------------------------*/
	/*if($('.page-herfe').length){
		var filter = $(".view-courses .view-filters").html();
		$(".view-courses .view-filters").html('');
		$(".college-body-right .pane-3 .pane-content").html(filter);
		$(".college-body-right .pane-3 .pane-content form").attr("action" , "/college/herfe");
	}
	*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
	//this block is for securing a little more courses registration that user couldnt change the prices
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
	if($('.page-conference').length){
		//this is for conference webform
		var total = 0;
		var price = [ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ]
		var w = 140000;
		var ow = 70000;
		var c1 = 1680000;
		var c2 = 240000;
		var c3 = 360000;
		var c4 = 240000;
		var ca = 2540000;
		var all = 3100000;
		var owall = 2820000;
		var conferec = 100000;
		var val = ['not','wa','ca','w1','c1','w2','c2','w3','c3','w4','c4','owa','ow1','ow2','ow3','ow4','conference','all','owall'];
		var valprice = [0,560000,2520000,140000,1680000,140000,240000,140000,360000,140000,240000,280000,70000,70000,70000,70000,100000, 3180000,2900000,0];
		
		/*
		we apply price to every array cell
		*/
		
		$('.page-conference .form-checkbox').each(function (i) {
			$('.page-conference #edit-submitted-selectcourse-'+i).change(function() {
				if ($('.page-conference #edit-submitted-selectcourse-'+i).is( ":checked" ) ) {
					price[ i ] = valprice[i];
				}
				else{
					price[i] = 0;
				}
			});
		});
		
		$('.page-conference #edit-submitted-selectcourse-18').change(function() {
				if ($('.page-conference #edit-submitted-selectcourse-18').is( ":checked" ) ) {
					price[ 18 ] = valprice[18];
				}
				else{
					price[18] = 0;
				}
			});
		
		/*
		when user check wa we have to disable all w1-w4 and decrease prices
		*/
		
		$('.page-conference #edit-submitted-selectcourse-1').change(function () {
			if ( $( '.page-conference #edit-submitted-selectcourse-1' ).is( ":checked" ) ){
				price[3] = 0;
				price[5] = 0;
				price[7] = 0;
				price[9] = 0;
				$(".page-conference #edit-submitted-selectcourse-3[type='checkbox']").prop({
					disabled:true
				});
				$(".page-conference #edit-submitted-selectcourse-5[type='checkbox']").prop({
					disabled:true
				});
				$(".page-conference #edit-submitted-selectcourse-7[type='checkbox']").prop({
					disabled:true
				});
				$(".page-conference #edit-submitted-selectcourse-9[type='checkbox']").prop({
					disabled:true
				});
			}
			else{
				$(".page-conference #edit-submitted-selectcourse-3[type='checkbox']").prop({
					disabled:false
				});
				$(".page-conference #edit-submitted-selectcourse-5[type='checkbox']").prop({
					disabled:false
				});
				$(".page-conference #edit-submitted-selectcourse-7[type='checkbox']").prop({
					disabled:false
				});
				$(".page-conference #edit-submitted-selectcourse-9[type='checkbox']").prop({
					disabled:false
				});
			}
		});
		
		/*
		when user check ca we have to disable all c1-c4 and decrease prices
		*/
		
		$('.page-conference #edit-submitted-selectcourse-2').change(function () {
			if ( $( '.page-conference #edit-submitted-selectcourse-2' ).is( ":checked" ) ){
				price[4] = 0;
				price[6] = 0;
				price[8] = 0;
				price[10] = 0;
				$(".page-conference #edit-submitted-selectcourse-4[type='checkbox']").prop({
					disabled:true
				});
				$(".page-conference #edit-submitted-selectcourse-6[type='checkbox']").prop({
					disabled:true
				});
				$(".page-conference #edit-submitted-selectcourse-8[type='checkbox']").prop({
					disabled:true
				});
				$(".page-conference #edit-submitted-selectcourse-10[type='checkbox']").prop({
					disabled:true
				});
			}
			else{
				$(".page-conference #edit-submitted-selectcourse-4[type='checkbox']").prop({
					disabled:false
				});
				$(".page-conference #edit-submitted-selectcourse-6[type='checkbox']").prop({
					disabled:false
				});
				$(".page-conference #edit-submitted-selectcourse-8[type='checkbox']").prop({
					disabled:false
				});
				$(".page-conference #edit-submitted-selectcourse-10[type='checkbox']").prop({
					disabled:false
				});
			}
		});
		
		/*
		when user check owa we have to disable all ow1-ow4 and decrease prices
		*/
		
		$('.page-conference #edit-submitted-selectcourse-11').change(function () {
			if ( $( '.page-conference #edit-submitted-selectcourse-11' ).is( ":checked" ) ){
				price[12] = 0;
				price[13] = 0;
				price[14] = 0;
				price[15] = 0;
				$(".page-conference #edit-submitted-selectcourse-12[type='checkbox']").prop({
					disabled:true
				});
				$(".page-conference #edit-submitted-selectcourse-13[type='checkbox']").prop({
					disabled:true
				});
				$(".page-conference #edit-submitted-selectcourse-14[type='checkbox']").prop({
					disabled:true
				});
				$(".page-conference #edit-submitted-selectcourse-15[type='checkbox']").prop({
					disabled:true
				});
			}
			else{
				$(".page-conference #edit-submitted-selectcourse-12[type='checkbox']").prop({
					disabled:false
				});
				$(".page-conference #edit-submitted-selectcourse-13[type='checkbox']").prop({
					disabled:false
				});
				$(".page-conference #edit-submitted-selectcourse-14[type='checkbox']").prop({
					disabled:false
				});
				$(".page-conference #edit-submitted-selectcourse-15[type='checkbox']").prop({
					disabled:false
				});
			}
		});
		
		/*
		when user check all we have to disable all selectcourses1-10 and decrease prices
		*/
		
		$('.page-conference #edit-submitted-selectcourse-17').change(function() {
			if ( $( '.page-conference #edit-submitted-selectcourse-17' ).is( ":checked" ) ){
				for(var i = 1 ; i<17 ; i++){
					price[i] = 0;
					$(".page-conference #edit-submitted-selectcourse-"+i+"[type='checkbox']").prop({
						disabled:true
					});
				}
				price[18] = 0;
				$(".page-conference #edit-submitted-selectcourse-18[type='checkbox']").prop({
					disabled:true
				});
			}
			else{
				for(var i = 1 ; i<17 ; i++){
					$(".page-conference #edit-submitted-selectcourse-"+i+"[type='checkbox']").prop({
						disabled:false
					});
				}	
				$(".page-conference #edit-submitted-selectcourse-18[type='checkbox']").prop({
					disabled:false
				});
			}
		});
		
		/*
		when user check owall we have to disable all selectcourses2,4,6,8,10-15 and decrease prices
		*/
		
		$('.page-conference #edit-submitted-selectcourse-18').change(function() {
			if ( $( '.page-conference #edit-submitted-selectcourse-18' ).is( ":checked" ) ){
				for(var i = 1 ; i<18 ; i++){
					price[i] = 0;
					$(".page-conference #edit-submitted-selectcourse-"+i+"[type='checkbox']").prop({
						disabled:true
					});
				}
			}
			else{
				for(var i = 1 ; i<18 ; i++){
					$(".page-conference #edit-submitted-selectcourse-"+i+"[type='checkbox']").prop({
						disabled:false
					});
				}	
			}
		});
	
		
		/*
		and finally we sum up the price array and print it in a feild
		erase this :price.length
		*/
		
		$('.page-conference .form-checkbox').change(function () {
		total=0;
		for (var i = 0; i < price.length ; i++) {
			total = total +price[ i ]
		}
		$('input#edit-submitted-mablagh').val(total + "تومان");	
	});
	}

/*-------------------------------------------------------------------------------------------------------------------------------*/
$('.messages').click(function() {
	$(this).css({
		'display': 'none'
	});



});
/*-------------------------------------------------------------------------------------------------------------------------------*/

$(function() {
  // Generic selector to be used anywhere
  $("div#eng-nav ul li a").click(function(e) {
    // Get the href dynamically
    var destination = $(this).attr('href');
    // Prevent href=“#” link from changing the URL hash (optional)
    e.preventDefault();
    // Animate scroll to destination
    $('html, body').animate({
      scrollTop: ($(destination).offset().top - 100)
    }, 1000);
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

var eng_nav = function(){
if($('.eng808-nav-exclusive').length) applyHeight($('.eng808-nav-exclusive').parent().parent() , $('.eng808-nav-exclusive') , 200);
if($('.eng808-nav-foreign').length) applyHeight($('.eng808-nav-foreign').parent().parent() , $('.eng808-nav-foreign') , 200);
if($('.eng808-nav-exam').length) applyHeight($('.eng808-nav-exam').parent().parent() , $('.eng808-nav-exam') , 200);
if($('.eng808-nav-courses').length) applyHeight($('.eng808-nav-courses').parent().parent() , $('.eng808-nav-courses') , 200);
if($('.eng808-nav-news').length) applyHeight($('.eng808-nav-news').parent().parent() , $('.eng808-nav-news') , 200);
if($('.eng808-nav-shop').length)  applyHeight($('.eng808-nav-shop').parent().parent() , $('.eng808-nav-shop') , 200);
if($('.eng808-nav-sourses').length) applyHeight($('.eng808-nav-sourses').parent().parent() , $('.eng808-nav-sourses') , 200);
};

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
	setTimeout(eng_nav, 1000);
	eng_nav_fixed_do();
}


/*-------------------------------------------------------------------------------------------------------------------------------*/




});

$(window).resize(function() {
	//applyHeight($(".college-body-right") , $(".college-body-left") , ($(".view-courses .view-filters").height()*-1) - 20);
	/*addCssToIframe();*/
});
 

var applyHeight = function(x, y , z) {
	if (x.height() < y.height()){
		x.height(y.height() + (z));
	}else if (x.height() > y.height()){
		y.height(x.height() + (z));
	}else 
		return false;
	
	return true;
}

/*
var addCssToIframe = function() {
    if ($('Iframe').contents().find("head") != undefined) {
        $('Iframe')
                .contents()
                .find("head")
                .append(
                        '<link rel="stylesheet" href="http://civil808.com/sites/all/themes/sara/css/razmia-calendar.css" type="text/css" />');
        //$interval.cancel(addCssInterval);
    }
};
*/

