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
  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <div class="submitted">
    <?php //print $submitted; ?>
  </div>
  <div class="header">
    <div class="c1">
    <?php //print_r($node) ?>
      <span class="user"><label><?=t('Project owner')?></label>: <?=l($node->name,'user/'.$node->uid)?></span>
      <span class="budget"><label><?=t('Project budget')?></label>: <?=$node->field_price_range['und'][0]['value']?></span>
    </div>
    <div class="c2">
    <?php 
      $end = $node->field_active_time['und'][0]['value'] * 24 * 60 * 60 + $node->created;
      if(time() < $end) {
        print '<label>'.t('Remind time for your submittion').'</label><br/><span class="interval">'.format_interval($end-time())."</span>";
      }
    ?>
    </div>

    <div class="c3">
      <span class="cubmit_count"><label><?=t('Project submittions')?></label>: <?=$node->comment_count?></span>
    </div>
    <div class="c4"></div>  
  </div>
  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>

  </div>

  </div>

<!--  این قسمت مربوط به همون نمایش نمیسنده تاریخ محتوایی است که لینک آن در تب های افقی تو ایجاد هر محتوا می باشد  --> 
    <?php if($relative_nodes): ?>
      <div class="relatives">
        <h2 class="title comment-form"><?=t('Relative contents')?></h2>
        <?php print theme('links', array('links'=>$relative_nodes)); ?>
      </div>
    <?php endif; ?>
    

  <?php
	global $user;
	if (!$user->uid) {
		print '<li class="comment_forbidden first last"><span>';
		print render($content['links']['comment']['#links']['comment_forbidden']['title']);
		print '</span></li>';
	}
	print render($content['comments']); 
  ?>

</div>
