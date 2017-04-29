<?php
// $Id$

/**
 * @file
 * Default theme implementation to display a node.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="teaser-img">
  <a href="<?php print $node_url; ?>">
    <span class="img-id">آخرین مهلت ارسال پیشنهاد</span>
    <span class="dl"><?=format_date($node->field_active_time['und'][0]['value'] * 60 * 60 * 24 + $node->created, 'custom', 'd')?></span>
    <span class="ds"><?=format_date($node->field_active_time['und'][0]['value'] * 60 * 60 * 24 + $node->created, 'custom', 'M Y')?>
      <br/>
      <?=format_date($node->field_active_time['und'][0]['value'] * 60 * 60 * 24 + $node->created, 'custom', 'H:s')?>
    </span>
  </a>
  </div>
  <div class="content"<?php print $content_attributes; ?>>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php if($submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>
</div>