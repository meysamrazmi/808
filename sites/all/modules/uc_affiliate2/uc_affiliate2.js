(function ($) {
    $('#edit-products-all').click(function() {
        new_value = false;
        
        if($('#edit-products-all').is( ":checked" )) {
            new_value = true;    
        }
        
        $('.form-checkbox').each(function() {
            if($(this).attr('id') != 'edit-products-all') {
                $('#' + $(this).attr('id')).prop('checked', new_value);
            }
        });
    });
}(jQuery));
