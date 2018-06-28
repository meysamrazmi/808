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
  <div class="content"<?php print $content_attributes; ?>>
    <figure class="podcast-audio">
    <img src="http://civil808.com/sites/default/files/default_images/Radio-Titr-News-BackGround.png">
      <?php if (isset($audio_player)) : ?>
        <div class="audio-feature">
          <?php print $audio_player; ?>
        </div>
      <?php endif; ?>
      <?php if (isset($podcast_headers)) : ?>
      <?php print theme('item_list', array('items'=>$podcast_headers, 'attributes' => array('class' => 'podcast-headers'))); ?>
      <?php endif; ?>
    </figure>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>

  <?php print render($content['links']); ?>

    <!-- advertise for showing poscasts in app* -->
    <div class="app-ebook" style="text-align: center;">
        <a href="/app" target="_blank"><img src="/sites/all/themes/sara/images/app-wild-banner-podcast2.jpg"/>
    </div>

<!--  این قسمت مربوط به همون نمایش نمیسنده تاریخ محتوایی است که لینک آن در تب های افقی تو ایجاد هر محتوا می باشد  --> 
    <?php if ($display_submitted): ?>
      <div class="author-section">
		<h5 class="author-section-title">درباره نویسنده</h5>
		<div class="author">
			<?php print $user_picture; ?>
			<h3>
				<?php 
					$p = profile2_load_by_user($uid);
					print $p['main']->field_full_name['und'][0]['value']; 
				?>
			</h3>
			<div class="author_desc">
			<?php print $author_about_me; ?>
			</div>
		</div>
	  </div>
    <?php endif; ?>


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

