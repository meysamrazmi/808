<?php
/**
 * @file
 * Theme implementation to display a single Drupal page.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 */
?>
<script type="text/javascript" src="/sites/all/themes/sara/js/bootstrap.min.js"></script> 
<?php if($page['menu']) : ?>
<header id="header">
	<?php if($page['menu']):?>
		<section class="bottom" id="main-menu">
			<?php print render($page['menu']); ?>
		</section>
	<?php endif; ?>
</header>
<?php endif; ?>

<section id="main">
	<?php if($page['highlight']): ?>
		<div class="region-container row-highlight highlight ">
			<?php print render($page['highlight']); ?>
		</div>
	<?php endif; ?>  

	<?php if ($messages): ?>
		<div class="container messagwrapper"> 
			<?php print $messages; ?>
		</div>
	<?php endif; ?>

  <div class="container main">
    <?php
		if($page['leftbar1'])  {
			print '<div class="row with-sidebar with-left-sidebar">';
			print '<div class="span9 right">';
		}else if($page['leftbar2']){
			print '<div class="row with-sidebar with-right-sidebar">';		
			print '<div class="span3 right rightads"><div class="leftbar2">'.render($page['leftbar2']).'</div></div>';
			print '<div class="span9 right">';
		}else{
			print '<div class="row no-sidebar no-left-sidebar no-right-sidebar">';
			print '<div class="right">';
		}
   ?>
	<?php if ($breadcrumb) print '<div id="breadcrumb">'.$breadcrumb.'</div>'; ?>
      <div id="content">
        <?php print render($title_prefix); ?>
          <?php if ($title): ?>
            <h1 class="title" id="page-title">
              <?php print $title; ?>
            </h1>
          <?php endif; ?>
          <?php print render($title_suffix); ?>
          <?php if ($action_links): ?>
            <ul class="action-links">
              <?php print render($action_links); ?>
            </ul>
          <?php endif; ?>
          <?php if ($tabs): ?>
            <div class="tabs">
              <?php print render($tabs); ?>
            </div>
          <?php endif; ?>
          <?php print render($page['help']); ?>
          <?php print render($page['content']); ?>
          <?php print $feed_icons; ?>
        </div>
      </div>
    
        <?php
			if($page['leftbar1'])  {
				print '<div class="span3 left leftads">';
					print '<div class="leftbar1">'.render($page['leftbar1']).'</div>';
				print '</div>';
			}
        ?>
    </div>
  </div>

	<?php if($page['bottom1']): ?>
		<div class="under-main online-users-section">
				<div class="row bottom1">
					<?php print render($page['bottom1']); ?>
				</div>
		</div>
	<?php endif; ?>
</section>

<?php if($page['footer_contact'] || $page['footer_about'] || $page['footer_third'] || $page['bottom3']) : ?>
<footer id="footer">
	<!--[if IE]><div class="Bj-footer"><![endif]-->
	<?php if($page['bottom3']){ print '<div class="row bottom3">'.render($page['bottom3']).'</div>'; }?>

    <?php if($page['footer_contact'] || $page['footer_about']) : ?>
	<div class="container">
		<?php if($page['footer_contact']) : ?>
			<div id="footer_contact" class="span7">
				<?php print drupal_render($page['footer_contact']); ?>
			</div>
		<?php endif; ?>
		<?php if($page['footer_about']) : ?>
			<div id="footer_about" class="span4">
				<?php print drupal_render($page['footer_about']); ?>
			</div>
		<?php endif; ?>  
	</div>
	<?php endif; ?>
	<?php if($page['footer_third']) : ?>
		<div id="footer_third">
			<?php print drupal_render($page['footer_third']); ?>
		</div>
	<?php endif; ?>
  <!--[if IE]> </div> <![endif]-->
</footer>
<?php endif; ?>