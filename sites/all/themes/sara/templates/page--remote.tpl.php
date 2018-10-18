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


<section id="main">
    <?php print render($page['content']['system_main']); ?>
    <a href="/user/register" target="_blank" class="join">عضویت در civil808</a>
</section>

<style>
    #main{
        margin: 10%;
        position: relative;
    }
    #main .content{
        border-radius: 3px;
        background: #fff;
        max-width: 700px;
        box-shadow: rgba(0,0,0,0.117647) 0 1px 6px, rgba(0,0,0,0.117647) 0 1px 4px;
        overflow: hidden;
        padding: 15px 15px 50px 15px;
        margin: auto;
    }
    #main a.join{
        position: absolute;
    }
</style>