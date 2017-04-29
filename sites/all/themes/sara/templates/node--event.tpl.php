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
<?php
  $disabled = ($node->field_time['und'][0]['value'] < time());
  if($buyed_value != -1)
    $disabled = true;
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

  <div class="clearfix">
    <div class="half first">
      <?=t('Event Time')?>: <?=format_date($node->field_time['und'][0]['value'], 'custom', 'D d M Y H:s')?> <br/>
      <?=t('Event Address')?>: <?=$node->field_address['und'][0]['value']?> 
    </div>
    <div class="half second">
      <?=t('Event Available Tickets')?>: <strong><?=$available_count?></strong> <br/>
    </div>
  </div>
  <div class="content third" <?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>
  <div>
  <?php 
  $tickets = array();
  for ($i = 0 ; $i < count($node->field_tickets['und']); $i++) {
      $tickets[] = array('value' => $node->field_tickets['und'][$i]['safe_value'], 'price' => $node->field_ticket_price['und'][$i]['value']);
  }

  $v = ($disabled) ? 'disabled="disabled"' : '';
  ?>
    <form method="post" action="?q=event/<?=$node->nid?>/register">
      <div class="clearfix">
      <?php foreach ($tickets as $key => $value) {?>
        <label class="half forth">
        <input type="radio" name="ticket" value="<?=$key+1?>" <?=($buyed_value == $key)?'checked':$v?> > <strong><?=$value['price']?> ریال</strong><br/>
         <?=$value['value']?>
        </label>
      <?php } ?>
      </div>
      <div class="copen">
        <?=t('Off code')?>: <input type="text" name="offcode" placeholder="<?=t('Place your off code here')?>" />
      </div>
      <div class="cta">
      <button class="btn-green" <?=($disabled)?$v:''?> ><?=t('Buy Ticket')?></button>
      </div>
    </form>
  </div>

  <?php print render($content['links']); ?>


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

