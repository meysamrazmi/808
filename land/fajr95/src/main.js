$(function() {
	$.scrollify({
		section:".panel",
		//sectionName:false,
		interstitialSection :".footer",
		scrollSpeed:500,
		// before:function(i,panels) {
			// var ref = panels[i].attr("data-section-name");
		
			// $("ul.navigat .active").removeClass("active");
		
			// $("ul.navigat").find("li#" + ref + "").addClass("active");
		// }
		// afterRender:function() {
			// var pagination = "<ul class=\"pagination\">";
			// var activeClass = "";
			// $(".panel").each(function(i) {
				// activeClass = "";
				// if(i===0) {
				// activeClass = "active";
				// }
				// pagination += "<li><a class=\"" + activeClass + "\" href=\"#" + $(this).attr("data-section-name") + "\"><span class=\"hover-text\">" + $(this).attr("data-section-name").charAt(0).toUpperCase() + $(this).attr("data-section-name").slice(1) + "</span></a></li>";
			// });
		
			// pagination += "</ul>";
			// $(".home").append(pagination);
		// }
		
	});
	
	
	

	$(".scroll,.scroll-btn").click(function(e) {
		e.preventDefault();
		$.scrollify.next();
	});	
	
	$("ul.navigat li").click(function(e) {
		e.preventDefault();
		$.scrollify.move('#'+ $(this).attr('id'));
	});
	
    AOS.init({
      offset: 200,
      duration: 600,
      easing: 'ease-in-sine',
      delay: 100,
    });
	

});

function shopp(){
	$.scrollify.move('#shop');
}