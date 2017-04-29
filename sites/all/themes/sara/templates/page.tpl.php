<?php
/**
 * @file
 * Theme implementation to display a single Drupal page.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see andromeda_preprocess_page()
 */
?>
<script type="text/javascript" src="/sites/all/themes/sara/js/bootstrap.min.js"></script> 
<?php if($page['logonew'] || $page['header'] || $page['socialnew'] || $page['ads3']) : ?>
<header id="header">
	<?php if($page['logonew'] || $page['header'] || $page['socialnew']) : ?>
		<section class="top">
			<?php if($page['logonew']) : ?>
				<div class="logo">
					<?php print drupal_render($page['logonew']); ?>
				</div>
			<?php endif; ?>
			<?php if($page['header']) : ?>
				<div class="ads headads">
					<?php print drupal_render($page['header']); ?>
				</div>
			<?php endif; ?>
			<?php if($page['socialnew']) : ?>
				<div id="socialnew" class="header-third">
					<?php print drupal_render($page['socialnew']); ?>
				</div>
			<?php endif; ?>
		</section>
	<?php endif; ?>
	<?php if($page['ads3']):?>
		<section class="bottom" id="main-menu">
			<?php print render($page['ads3']); ?>
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

  <?php if ($page['tab2']): //in the condition statement there was $is_front statement ?>
	<?php //this if is for the first row of old front page
		if($page['tab2'] || $page['tab1'] || $page['tab3'] || $page['slideshow']): ?>  
		<div class="container">
			<div class="row">
				<?php if($page['tab2'] || $page['tab1'] || $page['tab3']): ?>  
				<div class="span5">
					<div class="tab-content">
						<?php if($page['tab2']): ?>
							<div class="active tab-pane" id="profile"><?php print render($page['tab2']); ?></div>
						<?php endif; ?>
						<?php if($page['tab1']): ?>
							<div class="tab-pane" id="home"><?php print render($page['tab1']); ?></div>
						<?php endif; ?>
						<?php if($page['tab3']): ?>
							<div class="tab-pane" id="home"><?php print render($page['tab3']); ?></div>
						<?php endif; ?>
					</div>
				</div>
				<?php endif; ?>		
			
				<!-- slideshow section in old front page and section. it has been used just in old front page -->  
				<?php if($page['slideshow']): ?>
					<div class="span7 slideshow">
						<!-- Left Slider Section -->
						<div class="left">
							<?php echo render($page['slideshow']); ?>
						</div><!--left -->
					</div>
				<?php endif; ?>
		
			</div>
		</div>
	<?php endif; ?>

	<?php //this if is for the main part of pld front page
	if($page['front'] || $page['ads'] || $page['ads1'] || $page['ads2']): ?>  
		<div class="container front">
			<?php if($page['ads'] || $page['ads1'] || $page['ads2']): ?>  
				<div class="row with-sidebar with-left-sidebar">
			<?php else: ?>	
				<div class="row no-sidebar no-left-sidebar">
			<?php endif; ?>
		
				<?php if($page['front']): ?>
					<div class="span9 right">
						<?php print render($page['front']);?>
					</div>
				<?php endif; ?>
			
				<div class="span3 left leftads">
					<?php
					if($page['ads'])
						print '<div class="ads">'.render($page['ads']).'</div>';
			
						if($page['ads1'])
						print '<div class="ads1">'.render($page['ads1']).'</div>';
			
					if($page['ads2'])
						print '<div class="ads2">'.render($page['ads2']).'</div>';
					?>
				</div>
			</div>
			<?php print $feed_icons; ?>
		</div>
	<?php endif; ?>
        
<?php else: ?>
  <div class="container main">
    <?php
		if($page['ads'] || $page['ads1'])  {
			print '<div class="row with-sidebar with-left-sidebar">';
			print '<div class="span9 right">';
		}else if($page['ads2']){
			print '<div class="row with-sidebar with-right-sidebar">';		
			print '<div class="span3 right rightads"><div class="ads2">'.render($page['ads2']).'</div></div>';
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
			if($page['ads'] || $page['ads1'])  {
				print '<div class="span3 left leftads">';
				if($page['ads'])
					print '<div class="ads">'.render($page['ads']).'</div>';
		
				if($page['ads1'])
					print '<div class="ads1">'.render($page['ads1']).'</div>';
	
				print '</div>';
			}
        ?>
    </div>
  </div>
<?php endif; ?>

	<?php if($page['bottom2'] ): ?>
		<div class="container under-main bottoms up-footer">
			<?php if($page['bottom2']): ?>
				<div class="row first-row bottom-row-2">
					<?php print '<div class="row bottom2">'.render($page['bottom2']).'</div>'; ?>
				</div>
			<?php endif; ?>
		</div>
	<?php endif; ?>

	<?php if($page['hor1'] || $page['hor2'] || $page['hor3'] || $page['hor4'] || $page['bottom1']): ?>
		<div class="under-main online-users-section">
			<?php if($page['hor1'] || $page['hor2'] || $page['hor3'] || $page['hor4']): ?>
				<div class="row">
					<?php if($page['hor1']): ?>
						<div class="span3 hor1">
							<?php	print render($page['hor1']); ?>
						</div>
					<?php endif; ?>
					<?php if($page['hor2']): ?>
						<div class="span3 hor2">
							<?php print render($page['hor2']); ?>
						</div> 
					<?php endif; ?>
					<?php if($page['hor3']): ?>
						<div class="span3 hor3">
							<?php print render($page['hor3']); ?>
						</div>
					<?php endif; ?>
					<?php if($page['hor4']): ?>
						<div class="span3 hor4">
							<?php print render($page['hor4']); ?>
						</div>
					<?php endif; ?>
				</div>
			<?php endif; ?>
			<?php if($page['bottom1']): ?>
				<div class="row bottom1">
					<?php print render($page['bottom1']); ?>
				</div>
			<?php endif; ?>
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