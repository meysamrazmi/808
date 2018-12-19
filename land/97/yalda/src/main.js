$(function() {
    $(document).ready(function () {
        $.getScript('https://civil808.com/sites/all/themes/sara/js/lib/jquery.elevateZoom-3.0.8.min.js', function () {
            $(".images-zoom img").elevateZoom({easing: true, scrollZoom: true});
        });
    });

    // Set the date we're counting down to
    var countDownDate = new Date("Nov 23, 2018 00:00:00").getTime();

// Update the count down every 1 second
    var x = setInterval(function() {

        // Get todays date and time
        var now = new Date().getTime();

        // Find the distance between now and the count down date
        var distance = countDownDate - now;

        // Time calculations for days, hours, minutes and seconds
        var days = Math.floor(distance / (1000 * 60 * 60 * 24));
        var hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
        var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
        var seconds = Math.floor((distance % (1000 * 60)) / 1000);

        // Display the result in the element with id="demo"
        document.getElementById("demo").innerHTML = days + " روز و " + hours + " ساعت و "
            + minutes + " دقیقه و " + seconds + " ثانیه ";

        // If the count down is finished, write some text
        if (distance < 0) {
            clearInterval(x);
            document.getElementById("demo").innerHTML = "EXPIRED";
        }
    }, 1000);

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

    // AOS.init({
      // offset: 200,
      // duration: 600,
      // easing: 'ease-in-sine',
      // delay: 100,
    // });
	

});

