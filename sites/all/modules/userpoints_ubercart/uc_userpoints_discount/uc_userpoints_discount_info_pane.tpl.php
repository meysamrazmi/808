<div id="discount_info_pane">
  <div id="discountable_total">
    <span id="discountable_total_label">
      <?php print t('Discountable total from this order'); ?>
    </span>
    <span id="discountable_total_value">
      <?php print $discountable_total; ?>
    </span>
  </div>
  <div id="discount_max">
    <span id="discount_max_label">
      <?php print t('Maximum you can discount the order by'); ?>
    </span>
    <span id="discount_max_value">
      <?php print $discount_max; ?>
    </span>
  </div>
  <div id="discount_points_available">
    <span id="discount_points_available_label">
      <?php print t('Your !points available to use', userpoints_translation()); ?>
    </span>
    <span id="discount_points_available_value">
      <?php print $discount_points_available; ?>
    </span>
  </div>
</div>
