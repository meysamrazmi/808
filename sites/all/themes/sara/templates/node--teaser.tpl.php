<?php
/**
 * @file
 * Default theme implementation to display a node.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>
<?php if($node->type == 'publication'): ?>

<?php /*
	* برای تخفیفات نوروزی
	*/
	$flag = false;
		if(isset($node->field_isvip['und'])){
			for ( $i=0 ; $i < count( $node->field_isvip['und'] ) ; $i++){
				if( $node->field_isvip['und'][$i]['tid'] == 2217)
					$flag=false;
			}
		}
		if(isset($point_needed) && $point_needed){
			if( intval($point_needed) < 100){
				$flag=false;
			}
		}else{
			$flag=false;
		}
		if($flag){
			print '<div id="takhfifdar"></div>';
		}
	
?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="teaser-img">
  <a href="<?php print $node_url; ?>">
    <?php if(isset($field_image['und'][0]['uri'])) {
    $hero_image = array(
      'style_name' => 'teaser',
      'path' => $field_image['und'][0]['uri'],
      'width' => '',
      'height' => '',
      'alt' => $title,
      'title' => $title,
      );
    print theme('image_style',$hero_image);
  }
    ?>
  </a>
  </div>
    <h2 <?php print $title_attributes; ?>><i class="fa fa-book hide"></i> <a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <div class="content"<?php print $content_attributes; ?>>
    <?php if($submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>
  </div>
</div>
<?php else: ?>

<?php /*
	* برای تخفیفات نوروزی
	*/
	$flag = false;
		if(isset($node->field_isvip['und'])){
			for ( $i=0 ; $i < count( $node->field_isvip['und'] ) ; $i++){
				if( $node->field_isvip['und'][$i]['tid'] == 2217)
					$flag=false;
			}
		}
		if(isset($point_needed) && $point_needed){
			if( intval($point_needed) < 100){
				$flag=false;
			}
		}else{
			$flag=false;
		}
		if($flag){
			print '<div id="takhfifdar"></div>';
		}
	
?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <h2 <?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>

  <div class="teaser-img">

  <a href="<?php print $node_url; ?>">
    <?php if(isset($field_image['und'][0]['uri'])) {
    $hero_image = array(
      'style_name' => 'teaser',
      'path' => $field_image['und'][0]['uri'],
      'width' => '',
      'height' => '',
      'alt' => $title,
      'title' => $title,
      );
    print theme('image_style',$hero_image);
  }
    ?>
  </a>
  </div>
  <div class="content"<?php print $content_attributes; ?>>
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
    <?= render($content['links']) ?>
  </div>
</div>
<?php endif; ?>
