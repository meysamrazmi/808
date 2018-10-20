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
    <a href="/user/register" target="_blank" class="join btn-primary">عضویت در civil808</a>
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
        padding: 15px 15px 30px 15px;
        margin: auto;
    }
    #main .company-name{
        display: inline-block;
        font-size: 15px;
        padding: 10px;
        vertical-align: top;
    }
    #main .company-name label{
        display: inline;
        font-size: 15px;
        padding: 0px 4px;
    }
    #main .company-logo{
        position: absolute;
        top: 0px;
        left: 300px;
    }
    #main .company-logo img{
        height: 50px;
    }

    #main .content .form-item{
        display: flex;
        justify-content: space-between;
        padding: 5px 30px;
    }
    #main .content .form-item label{
        padding: 5px;
        margin: 5px;
    }
    #main .content .form-item input{
        padding: 5px;
        margin: 5px;
    }
    #main #edit-submit{
        margin: 10px 30px 0px 30px;
    }
    #main a.join{
        position: absolute;
        bottom: 20px;
        right: 310px;
    }
</style>