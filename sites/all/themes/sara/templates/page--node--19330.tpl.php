<header id="header">
        <section class="bottom" id="main-menu">
			<?php print render($page['menu']); ?>
        </section>
</header>

<link href=/sites/all/themes/sara/templates/shop/css/app.ed7c132e366781b51b072fb946c78577.css rel=stylesheet>
<div class="tabs">
    <?php print render($tabs); ?>
</div>
<div id=app></div>
<script type=text/javascript src=/sites/all/themes/sara/templates/shop/js/manifest.5b7824995943025a7511.js></script>
<script type=text/javascript src=/sites/all/themes/sara/templates/shop/js/vendor.5e695ee7c20ec2de077f.js></script>
<script type=text/javascript src=/sites/all/themes/sara/templates/shop/js/app.0d5f3a01c1d9f0ba0e18.js></script>

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
