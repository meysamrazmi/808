<?php

/**
 * @file
 * Template file for LinkedIn profile as displayed on user page
 * Copy it to your theme's folder if you want to override it.
 *
 * Be sure to check and comply to  http://developer.linkedin.com/docs/DOC-1091 before tweaking.
 */

$profile == $variables['profile'];
?>
<div class="linkedin-profile head-info">
  <?php if ($profile['picture-url']) : ?>
    <a href="<?php print $profile['public-profile-url']['value']; ?>" <?php if ($profile['first-name']['value'] || $profile['last-name']['value']) : ?> title="Public profile of <?php print $profile['first-name']['value'] . ' ' . $profile['last-name']['value']; ?> on www.linkedin.com."<?php endif; ?> >
        <img src="<?php print $profile['picture-url']['value']; ?>" alt="<?php print $profile['first-name']['value'] . ' ' . $profile['last-name']['value']; ?>" />
      </a>
  <?php endif; ?>

  <div class="linkedin-head">
		<?php if ($profile['first-name']['value'] || $profile['last-name']['value']) : ?>
			<a href="<?php print $profile['public-profile-url']['value']; ?>" title="Public profile of <?php print $profile['first-name']['value'] . ' ' . $profile['last-name']['value']; ?> on www.linkedin.com.">
			<h2 class="linkedin-name"><?php print $profile['first-name']['value'] . ' ' . $profile['last-name']['value']; ?></h2>
			</a>
		<?php endif; ?>
	
		<ul>
		<?php 
		foreach ($profile as $key => $value){
			if ($value && !in_array($key, array ('picture-url', 'first-name', 'last-name'))){
				if($value['name'] == 'Positions'){
					$positions = $value['value'];
				} elseif($key == 'public-profile-url'){
					$linkedin = '<li class="linkedin-'. $key .'">View Profile On <a href="'. $value['value'] .'" target="_blank">Linked</a></li>';
				} elseif($key == 'num-connections'){
					print '<li class="linkedin-'. $key .'"><span class="label">connections : </span><span>'. $value['value'] .'</span></li>';
				} elseif($key == 'num-connections-capped'){

				}else{ 
					print '<li class="linkedin-'. $key .'"><span class="label">'. $value['name'] .' : </span><span>'. $value['value'] .'</span></li>';
				}
			}
		}
		if(isset($linkedin)) print $linkedin;
		?>
		</ul>
  </div>
</div>

<?php if(isset($positions)):
// mdump($positions,true);
?>
<div class="linkedin-positions">
	<h2>Experience</h2>
	<?php
		if(isset($positions['position'][0]['id']))
			$positions = $positions['position'];
		foreach ($positions as $position) : ?>
		<div class="linkedin-position<?php ($position['is-current'] == TRUE) ? print ' linkedin-position-current' : ''; ?> linkedin-profile">
			<h4><?php 
				($position['is-current'] == TRUE) ? print t('Currently') . ' ' : ''; 
				if ($position['title']){ 
					print $position['title']; 
				}
				if ($position['company']['name']){
					print ' at '. $position['company']['name']; 
				} ?>
			</h4>
			
			<p><?php 
				if ($position['start-date']['year']){
					if ($position['end-date']['year'])
						print t('From') . ' '; 
					else
						print t('Since') . ' '; 
					if ($position['start-date']['month']) 
						print $position['start-date']['month'] . '/'; 
					print $position['start-date']['year'] .' '; 
				}
				if ($position['end-date']['year']){
					if ($position['start-date']['year'])
						print ' ' . t('to') . ' '; 
					else 
						t('Until') . ' '; 
					if ($position['end-date']['month'])
						print $position['end-date']['month'] . '/'; 
					print $position['end-date']['year']; 
				}else
					print '- ' . t('Present') ; 
				?>
			</p>
			<ul class="linkedin-company">
				<?php if(isset($position['company'])){
					print isset($position['company']['name'])?'<h5 class="company-name">'. $position['company']['name'] .'</h5>': '';
					print isset($position['company']['size'])?'<li class="company-size">size : '. $position['company']['size'] .'</li>': '';
					print isset($position['company']['type'])?'<li class="company-type">type : '. $position['company']['type'] .'</li>': '';
					print isset($position['company']['industry'])?'<li class="company-industry">industry : '. $position['company']['industry'] .'</li>': '';
				}
				print isset($position['location'])?'<li class="company-location">location : '. $position['location']['name'] .'</li>': '';
				?>
			</ul>
			
			<?php if ($position['summary'])
				print '<div class="linkedin-position-summary">'. $position['summary'] .'</div>';
			?>
		</div>
	<?php endforeach; ?>
</div>
<?php endif; ?>

