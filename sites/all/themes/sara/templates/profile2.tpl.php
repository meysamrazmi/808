<?php

/**
 * @file
 * Default theme implementation for profiles.
 *
 * Available variables:
 * - $content: An array of comment items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $title: The (sanitized) profile type label.
 * - $url: The URL to view the current profile.
 * - $page: TRUE if this is the main view page $url points too.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity-profile
 *   - profile-{TYPE}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>
<?php

$loged_in_user = user_load($GLOBALS['user']->uid);

	$path = explode("/", current_path());
	if( ($path[0] == 'user' || $path[0] == 'users') && isset($path[1]) && is_numeric($path[1])){
		$user = user_load(intval($path[1]));
	}else{
		$user = $loged_in_user;
	}


?>
<div class="overlay"></div>
<div class="costum <?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <div class="content"<?php print $content_attributes; ?>>
      <div class="top">


		  <?php
//            var_dump($content);
//            die();
		  if(isset($content['field_about_me']['#items'][0]['value'])){
            $html = '<div class="card">
                        <b>سوابق خدمات حرفه ای من</b>
                        <br><p>';

	          $html = $html .$content['field_about_me']['#items'][0]['value'];
            $html = $html.'</p></div>';
            print $html;
            }

		  ?>

          <div class="left">
              <?php

              if($loged_in_user->uid == $user->uid) {

                  if(!empty($content)) {
	                  print '<div class="field-name-edit-vip-profile">
                        
                            <a href="/user/'.
		                  $user->uid

		                  .'/edit/vip">
                            ویرایش اطلاعات
                            </a>
                        
                    </div>';
                  }else {

	                  header("Location: /user/{$user->uid}/edit/vip");
	                  die();

                  }


              }


              if(isset($content['field_episode'])){
	              $link = 'modal-show';

                print '<div class="field-name-field-episode">
                      <a class="modal-show">
                      نمایش فیلم معرفی
                        </a>
                  </div>';
              }
              

              if(isset($content['field_publish_file'])){
                  $link = generate_file_address($content['field_publish_file']['#items'][0]['uri']);
	              print '<div class="field-name-field-publish-file">
                        <span class="file">
                            <a href="'.
		              $link
		              .'">
                            دانلود ضمیمه
                            </a>
                        </span>
                    </div>';
              }




	          ?>
          </div>
      </div>


	            <?php
                if(isset($content['field_experience'])){
                    $html = '<div class="work-experience">
                              <div class="section-label">سوابق شغلی</div>
                                <div class="flex">';
	                for($i=0; $i < sizeof($content['field_experience']['#items']) ; $i++){
		                $val = $content['field_experience']['#items'][$i]['value'];
		                $html = $html.'<div class="card">
                            <div class="md-icon"></div>
                            <div class="work-experience-co">'.
			                $content['field_experience'][$i]['entity']['field_collection_item'][$val]['field_company']['#items'][0]['value']
			                .'  <div class="card-divider"></div>
                            </div> 
                            <div class="work-experience-job">'.
			                $content['field_experience'][$i]['entity']['field_collection_item'][$val]['field_job']['#items'][0]['value']
			                .'</div>
                            <div class="work-experience-period">
                           از '
			                .$content['field_experience'][$i]['entity']['field_collection_item'][$val]['field_start_month'][0]['#markup'].' '
			                .$content['field_experience'][$i]['entity']['field_collection_item'][$val]['field_yearof'][0]['#markup']
			                .' تا ';
                            if(isset($content['field_experience'][$i]['entity']['field_collection_item'][$val]['field_end_month'][0]['#markup'])){
                                $html = $html.$content['field_experience'][$i]['entity']['field_collection_item'][$val]['field_end_month'][0]['#markup'].' '
	                                .$content['field_experience'][$i]['entity']['field_collection_item'][$val]['field_active_time'][0]['#markup'];
                            }else{
                                $html = $html.'کنون';
                            }
			                $html = $html
			                .'</div>
                            </div>';

	                }
	                $html = $html.'</div>
                                        </div>';
	                print $html;
                }
	            ?>

      <div class="modal">
          <div class="modal-header">
              <span>نمایش ویدیو</span>
              <a class="close"></a>
          </div>
          <?php
          $link = '';
          if(isset($content['field_episode'])){
	          $link = generate_file_address($content['field_episode']['#items'][0]['uri']);
              $video_attrs = array(
                  'src' => $link,
                  'width' => '840px',
                  'height' => '447px',
                  'videoWidth' => '840px',
                  'videoHeight' => '447px',
                  'controls' => true,
              );
              $video_sett =  array(
                  'download_link' => true,
                  'download_text' => 'download'
              );
              print theme('mediaelement_video', array('attributes' => $video_attrs, 'settings' => $video_sett));
              //'poster ' => '/sites/default/files/conference-4-film' ,
          }

          ?>
      </div>
  </div>
</div>

<style>
    .profile2-vip .top .card{
        background: #fff;
        padding: 15px;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        /*white-space: pre-line;*/
        margin-bottom:   15px;
        width: 75%;
        font-size: 14px;
        border-radius: 3px;

    }
    .top {
        display: flex;
    }
    .left {
        width: 25%;
        margin-right: 15px;
    }
    span.file a {
        display: inline-block;
        width: 100%;
        white-space: nowrap;
        overflow: hidden;
        vertical-align: middle;
        margin-bottom: 15px;
        padding: 15px;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        /*background: linear-gradient(to bottom left, rgba(136, 40, 218, 0.7), rgba(73, 118, 245, 0.7));*/
        background: #fff;
        position: relative;
        color: #424242 !important;
        font-weight: 500;
        border-radius: 3px;
        font-size: 15px;
    }
    span.file a *{
        position: relative;
    }
    span.file a:after {
        transition: 0.5s;
        content: ' ';
        position: absolute;
        background: #1976D2;
        opacity: 0.2;
        right: 0;
        top: 0;
        bottom: 0;
        width: 0%;
    }
    span.file:hover a:after {
        width: 100%;
    }
    span.file:hover a:before {
        color: #0D47A1;
    }

    span.file a:before {
        transition: 0.5s;
        content: "\f162";
        font-family: mat;
        color: #2196F3;
        font-size: 24px;
        position: absolute;
        line-height: 54px;
        left: 15px;
        top: 0px;
    }
    span.file-size,
    span.file img {
        display: none;
    }


    .field-name-field-episode {
        margin-bottom: 15px;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        /*background: linear-gradient(to bottom left, rgba(73, 118, 245, 0.7) ,rgba(136, 40, 218, 0.7));*/
        background: #fff;
        position: relative;
        color: #424242;
        border-radius: 5px;
        font-size: 15px;
        font-weight: 500;
    }
    .field-name-field-episode a{
        color: #424242!important;
        display: block;
        padding: 15px;
        position: relative;
        cursor: pointer;
    }
    .field-name-field-episode a:before {
        transition: 0.5s;

        content: "\f381";
        font-family: mat;
        color: #f44336;
        font-size: 24px;
        line-height: 54px;
        position: absolute;
        left: 15px;
        top: 0px;
    }
    .field-name-field-episode a:after {
        transition: 0.5s;
        content: ' ';
        position: absolute;
        background: #f44336;
        opacity: 0.2;
        right: 0;
        top: 0;
        bottom: 0;
        width: 0%;
    }
    .field-name-field-episode a:hover:after {
        width: 100%;
    }
    .field-name-field-episode a:hover:before {
        color: #b71c1c;
    }




    .field-name-edit-vip-profile {
        margin-bottom: 15px;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        /*background: linear-gradient(to bottom left, rgba(73, 118, 245, 0.7) ,rgba(136, 40, 218, 0.7));*/
        background: #fff;
        position: relative;
        color: #424242;
        border-radius: 5px;
        font-size: 15px;
        font-weight: 500;
    }
    .field-name-edit-vip-profile a{
        color: #424242!important;
        display: block;
        padding: 15px;
        position: relative;
        cursor: pointer;
    }
    .field-name-edit-vip-profile a:before {
        transition: 0.5s;

        content: "\f3eb";
        font-family: mat;
        color: #009688;
        font-size: 24px;
        line-height: 54px;
        position: absolute;
        left: 15px;
        top: 0px;
    }
    .field-name-edit-vip-profile a:after {
        transition: 0.5s;
        content: ' ';
        position: absolute;
        background: #009688;
        opacity: 0.2;
        right: 0;
        top: 0;
        bottom: 0;
        width: 0%;
    }
    .field-name-edit-vip-profile a:hover:after {
        width: 100%;
    }
    .field-name-edit-vip-profile a:hover:before {
        color: #00796B;
    }

    .work-experience {
        /*display: flex;*/
    }

    .work-experience .card {
        width: 50%;
    }
    .work-experience .card:nth-child(odd) {
        margin-left: 7.5px;
    }
    .work-experience .card:nth-child(even) {
        margin-right: 7.5px;
    }
    .work-experience .section-label {
        padding: 10px 0;
        font-size: 15px;
        font-weight: 500;
        position: relative;
        width: 100%;
    }
    .work-experience .section-label:before {
        content: "\f0d6";
        font-family: mat;
        font-size: 24px;
        color: #0077b5;
        vertical-align: middle;
        right: 0;
        margin-left: 10px;
    }
    .field-collection-view {
        background: #fff;
        padding: 15px;
        box-shadow: rgba(0,0,0,0.117647) 0 1px 6px, rgba(0,0,0,0.117647) 0 1px 4px;
        margin: 0;
    }
    .field-collection-container{
        border: none;
    }

    .card {
        background: #fff;
        padding: 15px;
        box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
        margin-bottom:   15px;
        width: 100%;
        font-size: 14px;
        border-radius: 3px;
        position: relative;
        font-family: fanum;
    }
    .card .card-divider {
        margin: 0 5px;
        border-bottom: 1px solid #EEEEEE;
    }
    .work-experience .card .card-divider {
        margin-left: 65px;
        border-bottom: 1px solid #EEEEEE;
    }
    .work-experience .card .work-experience-co {
        margin-left: 36px;
        font-family: fanum;
        font-size: 14px;
        font-weight: 500;
        margin-bottom: 5px;
    }
    .work-experience .card .work-experience-job {
        font-family: fanum;
        font-weight: 500;
        font-size: 13px;
        color: #9E9E9E;
        margin-bottom: 5px;
    }
    .work-experience .card .work-experience-period {
        font-family: fanum;
        font-size: 11px;
        color: #9E9E9E;
    }
    .work-experience .card .md-icon:before {
        content: '\f0d7';
        font-family: mat;
        color: #E0E0E0;
        font-size: 36px;
        position: absolute;
        left: 15px;
        top: 15px;
    }
    .flex {
        display: flex;
    }
    body.page-user .top .left .field-name-field-publish-file {
        display: block !important;
    }
    body.page-user:not(.role-administrator):not(.role-همکاران):not(.role-editor):not(.role-vip):not(.same-user) .field-name-field-publish-file {
        display: block !important;
    }
    #content .modal{
        display: none;
        padding: 10px;
        top: 5%;
        width: auto;
        left: 15%;
        right: 15%;
        margin-left: 0;
        z-index: 1001;
    }
    .mediaelement-video {
        max-width: 100%;
        margin: auto;
    }
    #content .modal-header {
        position: relative;
    }
    #content .modal-header a.close {
        color: #424242!important;
    }
    #content .modal-header a.close:before {
        content: '\f156';
        font-family: mat;
        position: absolute;
        left: 10px;
        top: 10px;
        color: #424242;
    }
    div.overlay {
        display: none;
        position: fixed;
        z-index: 1000;
        left: 0 ;
        right: 0;
        top: 0;
        bottom: 0;
        background: rgba(0,0,0,0.5);
    }
    @media screen and (max-width: 768px) {
        .work-experience .card {
            width: 100%;
        }
        .profile2-vip .top .card{
            width: 100%;
        }
        .top {
            display: block;
        }
        .left {
            width: 100%;
            margin-right: 0px;
            display: flex;
        }
        .field-name-field-episode {
            width: 50%;
        }
        .field-name-field-publish-file {
            width: 50%;
            margin-right: 15px;
        }
        .flex {
            display: block;
        }
        .work-experience .card:nth-child(odd) {
            margin-left: 0px;
        }
        .work-experience .card:nth-child(even) {
            margin-right: 0px;
        }
        #content .modal{
            display: none;
            padding: 10px;
            top: 20%;
            width: auto;
            left: 5%;
            right: 5%;
            margin-left: 0;
            z-index: 1001;
        }
    }
</style>

<script>
    $(document).ready(function () {
		$('.modal-show').click(function () {
			$('.modal').fadeIn()
			$('.overlay').fadeIn()
		})

        $('.modal-header .close, .overlay').click(function () {
			$('.modal').fadeOut()
			$('.overlay').fadeOut()
		})

        if($('.field-name-field-episode').length == 0 &&
            $('.field-name-field-publish-file').length == 0 &&
            $('.field-name-edit-vip-profile').length == 0) {

                $('.profile2-vip .top .card').css('width','100%')
                $('.left').css('width','0%')
        }

	})


</script>