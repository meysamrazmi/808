<?php
//field_isvip یه فیلد رابط به تکسونومیه که یه دونه ترم داره و توضیحات اون ترم عدد 1 هست
global $user;
//که تو اینجا هم چک میکنه که اگر ترم مربوطه به این نود ست شده بود و کاربر نقش طلایی داشت if اجرا بشه که میگم کجای این کد این if اول بسته میشه
if ((isset($node->field_isvip['und']) && $node->field_isvip['und'][0]['tid']==1760 ) AND (in_array('Vip', $user->roles)) ):
?>
<!--By Bijanzand.com -->

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>

   <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
	  ?>

</div>
  <?php print render($content['links']); ?>

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
	if (!$user->uid) {
		print '<li class="comment_forbidden first last"><span>';
		print render($content['links']['comment']['#links']['comment_forbidden']['title']);
		print '</span></li>';
	}
	print render($content['comments']); 
  ?>

</div>
<!--  تا به اینجای کار به غیر از اون نمایش فیلم ها مثل بقیه است  که همه ی انها تو اون if اولیه است یعنی نمایش به صورت عادی  -->


<!-- این پایان همون if اولیه است که بعد این ادامه اش شروع میشه -->
<?php elseif (isset($node->field_isvip['und']) && $node->field_isvip['und'][0]['tid'] == 1760): ?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>
	<?php /*
		*
		* برای تخفیفات ویژه نوروزی و برای چاپ بنر بالاییش
		*
		$flag = true;
		if(isset($node->field_isvip['und'])){
			for ( $i=0 ; $i < count( $node->field_isvip['und'] ) ; $i++){
				if( $node->field_isvip['und'][$i]['tid'] == 2217) // no discount will be applied
					$flag=false;
			}
		}
		if($flag){
			print '<div id="takhfifdar"></div>';
		}*/
	?>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
    ?>

    <?php
		$a = new HtmlFixer();
		$b = explode("<!--break-->", render($content));
		$clean_html = $a->getFixedHtml($b[0]);
		print $clean_html;
    ?>

    	  <?php if (isset($content['field_videomaghalat'])) {
			    	  print render($content['field_videomaghalat']);
		  }
		  if (isset($content['field_videoamozesh'])) {
			    	  print render($content['field_videoamozesh']);
		  }
		  if (isset($content['field_videoarticle'])) {
			    	  print render($content['field_videoarticle']);
		  }
		  if (isset($content['field_videoradio'])) {
			    	  print render($content['field_videoradio']);
		  }
		  if (isset($content['field_publish_file'])) {
			print render($content['field_publish_file']);
		  }
		  if (isset($content['social-share'])) {
			print render($content['social-share']);
		  }

		?>
  </div>
  <div class="cta-new cta-new-vip">
		<div class="cta-column cta-1-column">
			<div class="cta-1-row cta-row">
				<div class="cta-icon"></div>
				<span class="cta-label">نوع فایل دریافتی :</span>
				<h2 class="cta-meghdar"><?php
					if (isset($content['field_noefile'])){
						print render($content['field_noefile']);
					}?>
				</h2>
			</div>
			<div class="cta-2-row cta-row">
				<div class="cta-icon"></div>
				<span class="cta-label"> اعتبار مورد نیاز :</span>
				<?php /*
				*
				* برای تخفیفات نوروزی
				*
				if($flag){
					print '<h2 class="cta-meghdar takhfif">' . (intval($point_needed)*0.6) .' تومان <span class="bef-price">' . $point_needed . ' تومان </span></h2>';
				} else{
					 print '<h2 class="cta-meghdar">' . $point_needed .' تومان </h2>';
				 }*/
					print '<h2 class="cta-meghdar">' . $point_needed .' تومان </h2>';
				 ?>
			</div>
			<div class="cta-row cta-btn">
				<a href="/article/ac/1480">عضویت ویژه</a>
			</div>
			<div class="cta-row cta-btn cta-2-btn">
			<?=l('شارژ حساب' , 'user/'. $user->uid .'/money/charge')?>
			</div>
		</div>
		<div class="cta-column cta-2-column">
			<h2 class=""><?=$is_content_available_vip['message']?></h2>
			<h2 class="cta-free">برای کاربران ویژه رایگان است</h2>
			<div class="cta-row cta-btn">
			<?=l(t('Pay and View this node'), 'pay/node/'.$nid)?>
			</div>
		</div>
	</div>

  <?php print render($content['links']); ?>

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
	if (!$user->uid) {
		print '<li class="comment_forbidden first last"><span>';
		print render($content['links']['comment']['#links']['comment_forbidden']['title']);
		print '</span></li>';
	}
	print render($content['comments']); 
  ?>

</div>



<?php else:?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>
	<?php /*
		*
		* برای تخفیفات ویژه نوروزی و برای چاپ بنر بالاییش
		*
		$flag = true;
		if(isset($node->field_isvip['und'])){
			for ( $i=0 ; $i < count( $node->field_isvip['und'] ) ; $i++){
				if( $node->field_isvip['und'][$i]['tid'] == 2217) // no discount will be applied
					$flag=false;
			}
		}
		if($flag){
			print '<div id="takhfifdar"></div>';
		}*/

	// We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);

		$a = new HtmlFixer();
		$b = explode("<!--break-->", render($content));
		$clean_html = $a->getFixedHtml($b[0]);
		print $clean_html;

		if (isset($content['field_videomaghalat'])) {
			    	  print render($content['field_videomaghalat']);
		  }
		  if (isset($content['field_videoamozesh'])) {
			    	  print render($content['field_videoamozesh']);
		  }
		  if (isset($content['field_videoarticle'])) {
			    	  print render($content['field_videoarticle']);
		  }
		  if (isset($content['field_videoradio'])) {
			    	  print render($content['field_videoradio']);
		  }
		  if (isset($content['field_publish_file'])) {
			print render($content['field_publish_file']);
		  }
			if (isset($content['social-share'])) {
			print render($content['social-share']);
		  }

		?>
<!--  قسمت زیر فقط زمانی اجرا میشه که محتوا پولی باشه و فقط هم برای نمایش پیغام هست و چیزی رو چک نمیکنه  -->
  </div>

	<div class="cta-new">
		<div class="cta-column cta-1-column">
			<div class="cta-1-row cta-row">
				<div class="cta-icon"></div>
				<span class="cta-label">نوع فایل دریافتی :</span>
				<h2 class="cta-meghdar">
					<?php
					if (isset($content['field_noefile'])) {
						print render($content['field_noefile']);
					}?>
				</h2>
			</div>
			<div class="cta-2-row cta-row">
				<div class="cta-icon"></div>
				<span class="cta-label"> اعتبار مورد نیاز :</span>
				<?php /*
				*
				* برای تخفیفات نوروزی
				*
				if($flag){
					print '<h2 class="cta-meghdar takhfif">' . (intval($point_needed)*0.6) .' تومان <span class="bef-price">' . $point_needed . ' تومان </span></h2>';
				} else{
					 print '<h2 class="cta-meghdar">' . $point_needed .' تومان </h2>';
				 } */
					print '<h2 class="cta-meghdar">' . $point_needed .' تومان </h2>';
				 ?>
			</div>
			<div class="cta-row cta-btn">
				<a href="/article/ac/1480">عضویت ویژه</a>
			</div>
			<div class="cta-row cta-btn cta-2-btn">
			<?=l('شارژ حساب' , 'user/'. $user->uid .'/money/charge')?>
			</div>
		</div>
		<div class="cta-column cta-2-column">
			<h2 class=""><?=$is_content_available['message']?></h2>
			<div class="cta-row cta-btn">
			<?=l(t('Pay and View this node'), 'pay/node/'.$nid)?>
			</div>
		</div>
	</div>

  <?php print render($content['links']); ?>

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


	<?php if(isset($relative_nodes)): ?>
      <div class="relatives">
        <h2 class="title comment-form"><?=t('Relative contents')?></h2>
        <?php print theme('links', array('links'=>$relative_nodes)); ?>
      </div>
    <?php endif; ?>

  <?php
	if (!$user->uid) {
		print '<li class="comment_forbidden first last"><span>';
		print render($content['links']['comment']['#links']['comment_forbidden']['title']);
		print '</span></li>';
	}
	print render($content['comments']); 
  ?>

</div>

<?php endif; ?>
