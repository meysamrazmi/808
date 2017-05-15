var $ = jQuery;
$(document).ready(function () {
    /*erasing pane-uc-order when its empty*/
    if (!$('.page-user .pane-uc-orders-user .view-uc-orders-user div').length) {
        $('.pane-uc-orders-user').remove();
    }
    /*adjust position of bookmark icon and admin-tabs in node-page*/
    $('.page-node li.flag-bookmarks').css({'top':$('#page-title').height()-20});
    $('.page-node div.tabs').css({'top':$('#page-title').height()});
});