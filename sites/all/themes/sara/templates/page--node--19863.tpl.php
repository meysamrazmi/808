<header id="header">
        <section class="bottom" id="main-menu">
			<?php print render($page['menu']); ?>
        </section>
</header>
<link href="https://fonts.googleapis.com/css?family=Roboto:100:300,400|Material+Icons" rel=stylesheet>
<link as=style href=/sites/all/themes/sara/templates/moshavereh/css/app.f0eb2ada.css rel=preload>
<link as=style href=/sites/all/themes/sara/templates/moshavereh/css/chunk-vendors.818b432d.css rel=preload>
<link as=script href=/sites/all/themes/sara/templates/moshavereh/js/app.a749b275.js rel=preload>
<link as=script href=/sites/all/themes/sara/templates/moshavereh/js/chunk-vendors.0e932203.js rel=preload>
<link href=/sites/all/themes/sara/templates/moshavereh/css/chunk-vendors.818b432d.css rel=stylesheet>
<link href=/sites/all/themes/sara/templates/moshavereh/css/app.f0eb2ada.css rel=stylesheet>
<div class="tabs">
    <?php print render($tabs); ?>
</div>
<noscript><strong>We're sorry but moshavereh doesn't work properly without JavaScript enabled. Please enable it to continue.</strong></noscript>
<div id=app></div>
<script src=/sites/all/themes/sara/templates/moshavereh/js/chunk-vendors.0e932203.js></script>
<script src=/sites/all/themes/sara/templates/moshavereh/js/app.a749b275.js></script>


    <footer id="footer">
            <div class="container">
                    <div id="footer_contact" class="span7">
						<?php print drupal_render($page['footer_contact']); ?>
                    </div>
                    <div id="footer_about" class="span4">
						<?php print drupal_render($page['footer_about']); ?>
                    </div>
            </div>
            <div id="footer_third">
				<?php print drupal_render($page['footer_third']); ?>
            </div>
    </footer>
