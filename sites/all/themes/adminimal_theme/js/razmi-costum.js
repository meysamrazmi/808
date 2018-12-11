var $ = jQuery;
$(document).ready(function () {

$('.form-textarea-wrapper .grippie').click( function () {
  $('.form-textarea-wrapper textarea').addClass('dir-ltr');
  $('.form-textarea-wrapper textarea').css('direction', 'ltr');

});
$('.field-name-field-pictures span.fieldset-legend').on('hover' , function () {
	$('.field-name-field-pictures legend:not(.has-btn)').append('<span class="for-alt">برای پر کردن فیلد های تصاویر <a>کلیک کنید.</a></span>');
});
$('.field-name-field-pictures legend:not(.has-btn)').append('<span class="for-alt">برای پر کردن فیلد های تصاویر <a>کلیک کنید.</a></span>');
$('.field-name-field-pictures .for-alt').click(function(){
	var t = $('#edit-title').val();
	console.log(t);
	$('.field-name-field-pictures.field-widget-image-image table tbody tr').each(function(i){
		$('#edit-field-pictures-und-'+i+'-alt').val(t);
		console.log($('#edit-field-pictures-und-'+i+'-alt').val());
		$('#edit-field-pictures-und-'+i+'-title').val(t);
	});	
});
$('.field-name-field-image .for-alt').click(function(){
	var t = $('#edit-title').val();
	console.log(t);
	$('.field-name-field-image.field-widget-image-image table tbody tr').each(function(i){
		$('#edit-field-image-und-'+i+'-alt').val(t);
		console.log($('#edit-field-image-und-'+i+'-alt').val());
		$('#edit-field-image-und-'+i+'-title').val(t);
	});	
});
$('.ADRES-CONTEINER .POSTI .DATA ,.ADRES-CONTEINER .PHON .DATA').each(function(){
	$(this).text($(this).text().slice(0,4) +" - "+ $(this).text().slice(4,7) +" - "+ $(this).text().slice(7));
	$(this).attr('dir' , 'ltr');
});

/*-------------------*/
$('select.menu-title-select option').each(function(){
	if($(this).text().indexOf("<") == 0)
		$(this).css({'background': '#fdd'})
})
/*-------------------*/




});


/*for firing some scripts after ajax */
Drupal.behaviors.adminBehavior = {attach: function (context, settings) {
$('.field-name-field-pictures legend:not(.has-btn), .field-name-field-image legend:not(.has-btn)').append('<span class="for-alt">برای پر کردن فیلد های تصاویر <a>کلیک کنید.</a></span>');
$('.field-name-field-pictures legend, .field-name-field-image legend').addClass('has-btn');
	
	
	
}};


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

		if (src != dataSrc && dataSrc != null) {
			el.src = dataSrc
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
		, processScroll2 = function(){
			var aa = $('img.lazy')
			for (var i = 0; i < aa.length; i++) {
				if (elementInViewport(aa[i])) {
					loadImage(aa[i], function () {
						aa[i].removeAttribute('data-src')
						aa[i].classList.remove("lazy")
						aa.splice(i, 1)
					});
				}
			};
		}
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
			processScroll2()
		}
		, processScrollMobile = function(){
			for(var i = 0; i < images.length; i++) {
				loadImage(images[i], function() {
					images[i].removeAttribute('data-src')
					images[i].classList.remove("lazy")
					images.splice(i,1)
				});
			};
			processScroll2()
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