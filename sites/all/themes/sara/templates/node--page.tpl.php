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
    <?php print $submitted; ?>
  </div>
  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
    
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
