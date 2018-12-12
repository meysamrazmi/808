<?php
	global $user;
	$for_vip = $vip = 0;
	if (isset($node->field_isvip['und']) && $node->field_isvip['und'][0]['tid']==1760)//display for vip users
		$for_vip = 1;
	if(in_array('Vip', $user->roles))
		$vip = 1;
?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>
  <?php
	/*
	* برای تخفیفات ویژه نوروزی و برای چاپ بنر بالاییش
	*/
  $festival = false;
  /*
  if(isset($node->field_isvip['und'])){
	  for ( $i=0 ; $i < count( $node->field_isvip['und'] ) ; $i++){
		  if( $node->field_isvip['und'][$i]['tid'] == 2217) // no discount will be applied
			  $festival=false;
	  }
  }*/

      /*if(strcmp($node->type , "designteam") == 0)
      {
          $field_publication = array();
          if(!empty($node->field_publication808['und'])) {
              foreach ($node->field_publication808['und'] as $row) {
                  array_push($field_publication, $row['tid']);
              }
          }

          $field_discount = array();
          if(!empty($node->field_isvip['und'])) {
              foreach ($node->field_isvip['und'] as $row) {
                  array_push($field_discount, $row['tid']);
              }
          }
          if(in_array(2174 , $field_publication) && !in_array_r(2217 , $field_discount)) $festival = true;
          else $festival = false;
      }*/

	if($festival){
		print '<div id="takhfifdar"></div>';
	}/**/
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
	if (!$for_vip || (!$vip)){
		$a = new HtmlFixer();
		if (isset($content['field_files'])) {
		    unset($content['field_files']);
		}		
		$content['body'][0]['#markup'] = $a->getFixedHtml(explode("<!--break-->", render($content['body'][0]['#markup']))[0]);
	}

    if($node->type == 'designteam' && isset($node->field_podcast_sample['und'][0])){
      $video_attrs = array(
          'src' => $node->field_podcast_sample['und'][0]['value'],
      );
      $video_sett =  array(
          'download_link' => TRUE,
          'download_text' => 'دانلود',
      );
      print '<div class="inine-audio" style="display: inline-block;background: #000;padding-top: 0;border-radius: 5px;margin: 15px 0 25px;">'.
          theme('mediaelement_audio', array('attributes' => $video_attrs, 'settings' => $video_sett))
            . '</div>';
      print '<style>.inine-audio .mejs-container {border: none !important;} .inine-audio .film-time {display: none;}</style>';
    }

	print render($content);
  ?>
  </div>

  <?php if (!$for_vip || (!$vip)): ?>
  <div class="node-pay">
      <div class="col-2">
          <h2 class="">
              <? if ($for_vip){
                  echo $is_content_available_vip['message'];
                  echo '</h2><h2 class="cta-free">برای کاربران ویژه رایگان است';
              }else{
                  echo $is_content_available['message'];
              }
              ?>
          </h2>
          <div style="display: flex;justify-content: space-around;">
              <a href="/article/ac/1480" class="btn-primary" target="_blank">عضویت ویژه</a>
              <a href="/user/<?php echo $user->uid;?>/money/charge" class="btn-primary" target="_blank">شارژ حساب</a>
          </div>
      </div>
      <div class="col-1">
          <div class="cta-1-row cta-row">
				<span class="cta-icon"></span>
				<span class="n-label">نوع فایل دریافتی :</span>
				<span class="meghdar"><?php  print (isset($content['field_noefile']))? render($content['field_noefile']) : '';	?></span>
          </div>
          <?php if(isset($node->field_point_needed_list['und'])):
		      $point_needed_list = $node->field_point_needed_list['und'][0]['value'];
		      ?>
              <div class="cta-2-row cta-row">
                  <div class="cta-icon"></div>
                  <span class="n-label"> اعتبار مورد نیاز :</span>
                  <span class="meghdar" style="color: #F44336;"><?php print formatMoney($point_needed_list);?> تومان</span>
              </div>
              <div class="cta-2-row cta-row">
                  <div class="cta-icon"></div>
                  <span class="n-label"> با <?php print ($point_needed_list - $point_needed) / $point_needed_list * 100;?>% به مناسبت جشنواره :</span>
                  <span class="meghdar" style="color: #F44336;"><?php print formatMoney($point_needed);?> تومان</span>
              </div>
          <?php else:?>
              <div class="cta-2-row cta-row">
                  <div class="cta-icon"></div>
                  <span class="n-label"> اعتبار مورد نیاز :</span>
                  <span class="meghdar" style="color: #F44336;"><?php print formatMoney($point_needed);?> تومان</span>
              </div>
          <?php endif;?>
          <div class="cta-2-row cta-row">
              <div class="cta-icon"></div>
              <?php
				if($festival){ //festival time
                    print '<span class="n-label" style="width: 80%;">با 20% تخفیف برای جشنواره عید فطر :</span><span class="meghdar" style="color: #4CAF50;">' . formatMoney(round(($point_needed * 0.8), -1)) .' تومان </span>';
				} else if(!$for_vip){ //normal vip discount
                    print '<span class="n-label">برای کاربران vip :</span><span class="meghdar" style="color: #4CAF50;">' . formatMoney(round(($point_needed * 0.9), -1)) .' تومان </span>';
				 }
              ?>
          </div>
            <a href="/pay/node/<?php echo $node->nid; ?>" class="btn-green" style="margin-top: 15px;">پرداخت <?php echo formatMoney(isset($user->roles[8])? round(($point_needed * 0.9), -1) : $point_needed);?> تومان و مشاهده محتوا</a>
      </div>
  </div>

  <?php endif; ?>  
  <?php
	if (!$user->uid) {
		$comment_forbidden = $content['links']['comment']['#links']['comment_forbidden'];
		unset($content['links']['comment']['#links']['comment_forbidden']);
	}
	print render($content['links']); 
  ?>

    <?php if ($node->type == 'publication'): /*advertise for showing Ebooks in app*/?>
        <div class="app-ebook" style="text-align: center;">
            <a href="/app" target="_blank"><img src="/sites/all/themes/sara/images/app-wild-banner3.jpg"/>
        </div>
    <?php endif; ?>

  <?php if ($display_submitted): ?>
	<div class="author-section">
		<h5 class="author-section-title">درباره نویسنده</h5>
		<div class="author">
			<?php 
				print $user_picture; 
				$p = profile2_load_by_user($uid);
				echo '<h3>'. $p['main']->field_full_name['und'][0]['value'] .'</h3>';
			?>
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
    print relative_qa_render($node->nid , $node->type);
  ?>

  <?php
	if (!$user->uid) {
		print '<li class="comment_forbidden first last"><span>';
		print render($comment_forbidden['title']);
		print '</span></li>';
	}
	print render($content['comments']); 
  ?>
</div>
