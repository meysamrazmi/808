var $ = jQuery;
$(document).ready(function () {
	//completing personal information for conference registration
	if(Drupal.settings.bought_product){
		//for users who allready submitted the form 
		$('.view-conference-information .view-content .views-row:not(:first-child)').each(function(){
			var row = $(this).find('tbody').html();
			$('.view-conference-information .view-content .views-row:first-child').find('tbody').append(row);
			$(this).css({'display' : 'none'});
		});

		$('.view-conference-information .view-content .views-row:first-child tbody tr').each(function(){
			var text = $(this).find('td:nth-child(5)').text();
			$.each(Drupal.settings.product_attributes, function(key, value){
				if($.inArray(text, value) !== -1)
					Drupal.settings.product_attributes.splice(key, 1)
			})
			$(this).find('td:nth-child(6)').css({'width':'150px'}).append('<a href="/user/'+ Drupal.settings.Uid +'/orders/'+ $(this).find('td:nth-child(6)').text() +'/print" target="_blank" class="blue-btn btn small-btn" style="margin-right: 15px;">چاپ بلیط</a>');
		});

		var completed = $('.view-conference-information .view-content .views-row:first-child').find('tbody tr').length;
		attrLnegth  = Drupal.settings.bought_product - completed;

		if(attrLnegth > 0){
			$('.webform-client-form-17894 > div').prepend('<div class="message alert alert-warning"><div class="info-pm">برای تکمیل ثبت نام می بایست اطلاعات تمامی افرادی که برای آن ها بلیت تهیه شده است را با ایجاد سطر جدید (در صورت لزوم)، کامل کنید.</div><div class="alert-pm"><span></span></div><div class="row-num"><span>'+(attrLnegth-1)+'</span> سطر دیگر باید اضافه گردد</div></div>');
			
			if(attrLnegth == 1){
				$('.webform-client-form-17894 .message .row-num').css({'display' : 'none'});
				$('#edit-users_information-0 [name="add_row_users_information"]').css({"display" : "none"});
			}
			$('#edit-users_information-0 [name="add_row_users_information"]').click(function(e){
				if($('#edit-users_information-0-table  tbody tr').length >= attrLnegth+1){
					e.preventDefault();
					$(this).css({"display" : "none"});
				}
			});
			//auto fill of city and order_id inputs
			var CityInputs = function(){
				$('#edit-users_information-0 tbody tr:not(:last-child) td:nth-child(5) input, #edit-users_information-0 tbody tr:not(:last-child) td:nth-child(6) input').prop( "readonly", true );
				$('div#edit-users_information-0 tbody tr:not(:last-child)').each(function(i){
					$(this).find('td:nth-child(5) input').val(Drupal.settings.product_attributes[i][0])
					$(this).find('td:nth-child(6) input').val(Drupal.settings.product_attributes[i][1])
				});
			}

			CityInputs();
			Drupal.behaviors.exampleModule = {attach: function (context, settings) {
				$('.webform-client-form-17894 > div .message .row-num > span').text(attrLnegth - ($('#edit-users_information-0-table  tbody tr').length-1));
				CityInputs();
				if($('#edit-users_information-0-table  tbody tr').length >= attrLnegth+1){
					$('#edit-users_information-0 [name="add_row_users_information"]').css({"display" : "none"});
				}
			}};
			
			//prevent form submitting of uncomplete data
			$('.webform-client-form-17894 .form-actions .form-submit').click(function(e){
				if($('#edit-users_information-0-table  tbody tr').length < attrLnegth+1){
					$('.webform-client-form-17894 > div  .message .alert-pm > span').text('اطلاعات تعداد افراد ثبت نام شده کافی نمی باشد!');
					$('.webform-client-form-17894 > div  .submit-warning').css({'visibility' : 'unset'});
					e.preventDefault();
				}
			});
		}else{
			$('.webform-client-form-17894').css({"display" : "none"});
		}
	}else{
		$('.webform-client-form-17894').css({"display" : "none"});
	}
});