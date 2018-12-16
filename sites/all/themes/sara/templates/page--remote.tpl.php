<?php
/**
 * @file
 * Theme implementation to display a single Drupal page.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 */
?>
<?php
/*
  * The data of this page comes from remote.inc in civil808.module
  * also check civil808_menu
  * */
?>


<section id="main">
    <?php print render($page['content']['system_main']); ?>
</section>

