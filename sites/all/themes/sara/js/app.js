var $ = jQuery;
$(document).ready(function () {
    $('.node-projectnew .title.comment-form').text('ارسال پیشنهاد جدید');
  
	if($('header#header').length){
		menutop = $('header#header').offset().top;
		$(window).scroll(function() {
			if($(window).scrollTop() > menutop) {
				$('body').addClass("fixed");
				if(!$('#main-menu').hasClass('tfixed')){
					$('#main-menu').addClass('tfixed');
				}
			}else {
				$('body').removeClass("fixed");
				if($('#main-menu').hasClass('tfixed')){
					$('#main-menu').removeClass('tfixed');
				}
			}
		});	
	}
   $('.radio audio').wrap('<div class="middle"></div>').parents('.middle').before('<div class="left"></div>').after('<div class="right"></div>');

});


/*! A fix for the iOS orientationchange zoom bug.
 Script by @scottjehl, rebound by @wilto.
 MIT License.
*/
(function(w){
  // This fix addresses an iOS bug, so return early if the UA claims it's something else.
  if( !( /iPhone|iPad|iPod/.test( navigator.platform ) && navigator.userAgent.indexOf( "AppleWebKit" ) > -1 ) ){
    return;
  }
  
    var doc = w.document;

    if( !doc.querySelector ){return;}

    var meta = doc.querySelector( "meta[name=viewport]" ),
        initialContent = meta && meta.getAttribute( "content" ),
        disabledZoom = initialContent + ",maximum-scale=1",
        enabledZoom = initialContent + ",maximum-scale=10",
        enabled = true,
    x, y, z, aig;

    if( !meta ){return;}

    function restoreZoom(){
        meta.setAttribute( "content", enabledZoom );
        enabled = true;
    }

    function disableZoom(){
        meta.setAttribute( "content", disabledZoom );
        enabled = false;
    }
  
    function checkTilt( e ){
    aig = e.accelerationIncludingGravity;
    x = Math.abs( aig.x );
    y = Math.abs( aig.y );
    z = Math.abs( aig.z );
        
    // If portrait orientation and in one of the danger zones
        if( !w.orientation && ( x > 7 || ( ( z > 6 && y < 8 || z < 8 && y > 6 ) && x > 5 ) ) ){
      if( enabled ){
        disableZoom();
      }         
        }
    else if( !enabled ){
      restoreZoom();
        }
    }
  
  w.addEventListener( "orientationchange", restoreZoom, false );
  w.addEventListener( "devicemotion", checkTilt, false );

})(this);


// make it safe to use console.log always
(function(a){function b(){}for(var c="assert,count,debug,dir,dirxml,error,exception,group,groupCollapsed,groupEnd,info,log,markTimeline,profile,profileEnd,time,timeEnd,trace,warn".split(","),d;!!(d=c.pop());){a[d]=a[d]||b;}})
(function(){try{console.log();return window.console;}catch(a){return (window.console={});}}());

(function($) {

    $.scrollToElement = function( $element, speed ) {

        speed = speed || 750;

        $("html, body").animate({
            scrollTop: $element.offset().top,
            scrollLeft: $element.offset().left
        }, speed);
        return $element;
    };

    $.fn.scrollTo = function( speed ) {
        speed = speed || "normal";
        return $.scrollToElement( this, speed );
    };
    
    jQuery.fn.labelify = function(settings) {
      settings = jQuery.extend({
        text: "title",
        labelledClass: ""
      }, settings);
      var lookups = {
        title: function(input) {
          return $(input).attr("title");
        },
        label: function(input) {
          return $("label[for=" + input.id +"]").text();
        }
      };
      var lookup;
      var jQuery_labellified_elements = $(this);
      return $(this).each(function() {
        if (typeof settings.text === "string") {
          lookup = lookups[settings.text]; // what if not there?
        } else {
          lookup = settings.text; // what if not a fn?
        };
        // bail if lookup isn't a function or if it returns undefined
        if (typeof lookup !== "function") {return;}
        var lookupval = lookup(this);
        if (!lookupval) {return;}

        // need to strip newlines because the browser strips them
        // if you set textbox.value to a string containing them
        $(this).data("label",lookup(this).replace(/\n/g,''));
        $(this).focus(function() {
          if (this.value === $(this).data("label")) {
            this.value = this.defaultValue;
            $(this).removeClass(settings.labelledClass);
          }
        }).blur(function(){
          if (this.value === this.defaultValue) {
            this.value = $(this).data("label");
            $(this).addClass(settings.labelledClass);
          }
        });

        var removeValuesOnExit = function() {
          jQuery_labellified_elements.each(function(){
            if (this.value === $(this).data("label")) {
              this.value = this.defaultValue;
              $(this).removeClass(settings.labelledClass);
            }
          })
        };

        $(this).parents("form").submit(removeValuesOnExit);
        $(window).unload(removeValuesOnExit);

        if (this.value !== this.defaultValue) {
          // user already started typing; don't overwrite their work!
          return;
        }
        // actually set the value
        this.value = $(this).data("label");
        $(this).addClass(settings.labelledClass);

      });
    };
})(jQuery);
