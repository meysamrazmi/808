$(function() {

	$(".scroll").click(function(e) {
		e.preventDefault();
		$('html, body').animate({
			scrollTop: ($('#intro-down').offset().top)
		}, 700);
	});	
	
	$("ul.navigat li").click(function(e) {
		e.preventDefault();
		$('html, body').animate({
			scrollTop: ($('#'+ $(this).attr('to-id')).offset().top)
		}, 1000);
	});
	
	$("div.off > a.btn").click(function(e) {
		e.preventDefault();
		console.log("okkk");
		$('html, body').animate({
			scrollTop: ($('#uni_products').offset().top)
		}, 1000);
	});
	
	
    // AOS.init({
      // offset: 200,
      // duration: 600,
      // easing: 'ease-in-sine',
      // delay: 100,
    // });
	

});

