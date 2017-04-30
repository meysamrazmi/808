jQuery(document).ready(function(){
  
  jQuery('.uc_webform-product-grid tbody tr').each(function(){
    jQuery(this).append("<td><input type='button' value='Clear' class='clear-radios'></td>");
  });
  
  jQuery('.clear-radios').click(function(){
    jQuery(this).parent().parent().find('input').attr("checked", false);
  });
});