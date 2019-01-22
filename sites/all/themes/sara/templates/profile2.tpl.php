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
<div class="costum <?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <div class="content"<?php print $content_attributes; ?>>
      <div class="top">
		  <?php
		    print render($content['field_about_me']);
		  ?>
          <div class="left">
              <div class="field-name-field-episode">
                  نمایش فیلم
              </div>
	          <?php
                if(isset($content['field_publish_file']['#items'][0]['uri'])){
                    $link = generate_file_address($content['field_publish_file']['#items'][0]['uri']);
                    print '<div class="field-name-field-publish-file"><span class="file"><a href="'. $link .'">دانلود ضمیمه</a></span></div>';
                }
	          ?>
		      <?php
	    	      print render($content['field_publish_file']);
		      ?>
          </div>
      </div>
      <div>
		  <?php
		    print render($content['field_experience']);
		  ?>
      </div>
  </div>
</div>


<style>
.profile2-vip .top .field-name-field-about-me{
    background: #fff;
    padding: 15px;
    box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
    white-space: pre-line;
    margin-bottom: 10px;
    width: 65%;
    font-size: 14px;
}
.top {
    display: flex;
}
.left {
    width: 35%;
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
    background: linear-gradient(to bottom left, rgba(136, 40, 218, 0.7), rgba(73, 118, 245, 0.7));
    position: relative;
    color: #fff !important;
    border-radius: 5px;
    font-size: 15px;
}
span.file a:before {
    content: "\f162";
    font-family: mat;
    font-size: 36px;
    position: absolute;
    left: 15px;
    top: 6px;
}
span.file-size,
span.file img {
    display: none;
}
.field-name-field-episode {
    margin-bottom: 15px;
    padding: 15px;
    box-shadow: rgba(0, 0, 0, 0.117647) 0px 1px 6px, rgba(0, 0, 0, 0.117647) 0px 1px 4px;
    background: linear-gradient(to bottom left, rgba(73, 118, 245, 0.7) ,rgba(136, 40, 218, 0.7));
    position: relative;
    color: #fff;
    border-radius: 5px;
    font-size: 15px;
    cursor: pointer;
}
.field-name-field-episode:before {
    content: "\f381";
    font-family: mat;
    font-size: 40px;
    position: absolute;
    left: 15px;
    top: 5px;
}



.field-name-field-experience .field-label {
    padding: 10px;
    font-size: 15px;
    font-weight: 500;
    position: relative;
}
.field-name-field-experience .field-label:before {
    content: "\f0d7";
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
</style>