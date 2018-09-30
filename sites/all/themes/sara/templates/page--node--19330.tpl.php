<header id="header">
        <section class="bottom" id="main-menu">
			<?php print render($page['ads3']); ?>
        </section>
</header>

<link href=/sites/all/themes/sara/templates/shop/css/app.ee12424e24ab3e1c0dfd64f5de0184f8.css rel=stylesheet>
<div class="tabs">
    <?php print render($tabs); ?>
</div>
<div id=app></div>
<script type=text/javascript src=/sites/all/themes/sara/templates/shop/js/manifest.fd38440cb259b5d0df9f.js></script>
<script type=text/javascript src=/sites/all/themes/sara/templates/shop/js/vendor.5e695ee7c20ec2de077f.js></script>
<script type=text/javascript src=/sites/all/themes/sara/templates/shop/js/app.963d2bf3bbbfc23a68e8.js></script>

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
