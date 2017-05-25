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



});


/*for firing some scripts after ajax */
Drupal.behaviors.adminBehavior = {attach: function (context, settings) {
$('.field-name-field-pictures legend:not(.has-btn), .field-name-field-image legend:not(.has-btn)').append('<span class="for-alt">برای پر کردن فیلد های تصاویر <a>کلیک کنید.</a></span>');
$('.field-name-field-pictures legend, .field-name-field-image legend').addClass('has-btn');
	
	
	
}};

