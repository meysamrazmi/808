<header id="header">
        <section class="bottom" id="main-menu">
			<?php print render($page['ads3']); ?>
        </section>
</header>

<link href=/sites/all/themes/sara/templates/shop/css/app.d428209d46c0236eadc0df1c2e2920ad.css rel=stylesheet>
<div class="tabs">
    <?php print render($tabs); ?>
</div>
<div id=app></div>
<script type=text/javascript src=/sites/all/themes/sara/templates/shop/js/manifest.66a22d3f859f24f8689f.js></script>
<script type=text/javascript src=/sites/all/themes/sara/templates/shop/js/vendor.5e695ee7c20ec2de077f.js></script>
<script type=text/javascript src=/sites/all/themes/sara/templates/shop/js/app.86e82ae2ae9a34c59b99.js></script>


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
