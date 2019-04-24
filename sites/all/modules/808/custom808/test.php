<?php
global $user;
if (arg(0) == 'user' && is_numeric(arg(1))) {
        global $user;
        $uid = arg(1);
        $user_p = user_load($uid);
        $profile = profile2_load_by_user($user_p);

        /*This part is for VIP or ADVISOR link box*/
        if (isset($profile['advisor']->pid) && isset($profile['advisor']->field_darbareye['und']) && isset($profile['advisor']->field_darbareye['und'][0]['value']) && isset($user_p->roles[10])) {
            print '<div class="advisorbanner">
            <h5>مشاور در زمینه ' . $profile['advisor']->field_darbareye['und'][0]['value'] . '</h5>
            <a href="/messages/new/' . $user_p->uid . ' " class="btn small-btn" target="_blank">ارتباط با مشاور</a>
        </div>';
        } else if (isset($profile['vip']->pid) && isset($user_p->roles[8])) {
            print '<div>
        <div class="advisorbanner">
            <h5>مشاهده فعالیت های حرفه ای تخصصی کاربر</h5>
        </div>
        <a href="/user/' . $user_p->uid . '/vip" class="btn small-btn" target="_blank">مشاهده</a>
        </div>';
        }
        /*----------------------------------------*/
        print '<div class="user-info">';
        /*---------------------------------------------------------------------------------------------------------------*/
        print '<div class="region-right">';
        /*----------------------------------------*/
        /*This part is for the user's information*/
        print '<div class="profile-information">';
        if (isset($profile['main']->field_full_name['und']) && isset($profile['main']->field_full_name['und'][0]['value']) && strlen($profile['main']->field_full_name['und'][0]['value']) > 3) {
            print '<div class="field field-name-field-full-name field-type-text field-label-inline clearfix">
               <div class="field-label">نام و نام خانوادگی: </div>
               <div class="field-items"><div class="field-item">' . $profile["main"]->field_full_name["und"][0]["value"] . '</div></div>
               </div>';
        }
        if (isset($profile['main']->field_education_degree['und']) && isset($profile['main']->field_education_degree['und'][0]['value']) && strlen($profile['main']->field_education_degree['und'][0]['value']) > 3) {
            print '<div class="field field-name-field-education-degree field-type-text field-label-inline clearfix">
               <div class="field-label">مقطع تحصیلی: </div>
               <div class="field-items"><div class="field-item">' . $profile["main"]->field_education_degree["und"][0]["value"] . '</div></div>
               </div>';
        }
        if (isset($profile['main']->field_education_field['und']) && isset($profile['main']->field_education_field['und'][0]['value']) && strlen($profile['main']->field_education_field['und'][0]['value']) > 3) {
            print '<div class="field field-name-field-education-field field-type-text field-label-inline clearfix">
               <div class="field-label">رشته تحصیلی: </div>
               <div class="field-items"><div class="field-item">' . $profile["main"]->field_education_field["und"][0]["value"] . '</div></div>
               </div>';
        }
        if (isset($profile['main']->field_university['und']) && isset($profile['main']->field_university['und'][0]['value']) && strlen($profile['main']->field_university['und'][0]['value']) > 3) {
            print '<div class="field field-name-field-university field-type-text field-label-inline clearfix">
               <div class="field-label">دانشگاه: </div>
               <div class="field-items"><div class="field-item">' . $profile["main"]->field_university["und"][0]["value"] . '</div></div>
               </div>';
        }
        if (isset($profile['main']->field_job['und']) && isset($profile['main']->field_job['und'][0]['value']) && strlen($profile['main']->field_job['und'][0]['value']) > 3) {
            print '<div class="field field-name-field-job field-type-text field-label-inline clearfix">
               <div class="field-label">شغل: </div>
               <div class="field-items"><div class="field-item">' . $profile["main"]->field_job["und"][0]["value"] . '</div></div>
               </div>';
        }
        if (isset($profile['main']->field_job_place['und']) && isset($profile['main']->field_job_place['und'][0]['value']) && strlen($profile['main']->field_job_place['und'][0]['value']) > 3) {
            print '<div class="field field-name-field-job-place field-type-text field-label-inline clearfix">
               <div class="field-label">محل کار: </div>
               <div class="field-items"><div class="field-item">' . $profile["main"]->field_job_place["und"][0]["value"] . '</div></div>
               </div>';
        }
        if (isset($profile['main']->field_job_title['und']) && isset($profile['main']->field_job_title['und'][0]['value']) && strlen($profile['main']->field_job_title['und'][0]['value']) > 3) {
            print '<div class="field field-name-field-job-title field-type-text field-label-inline clearfix">
               <div class="field-label">سمت: </div>
               <div class="field-items"><div class="field-item">' . $profile["main"]->field_job_title["und"][0]["value"] . '</div></div>
               </div>';
        }
        if (isset($profile['main']->field_about_me['und']) && isset($profile['main']->field_about_me['und'][0]['value']) && strlen($profile['main']->field_about_me['und'][0]['value']) > 3) {
            print '<div class="field field-name-field-about-me field-type-text-long field-label-inline clearfix">
               <div class="field-label">کوتاه درباره خودم: </div>
               <div class="field-items"><div class="field-item">' . $profile["main"]->field_about_me["und"][0]["value"] . '</div></div>
               </div>';
        }
        if (isset($profile['main']->field_experts['und']) && count($profile['main']->field_experts['und']) > 0) {
            print '<div class="field field-name-user-experts field-type-ds field-label-inline clearfix">
               <div class="field-label">تخصص ها: </div>
               <div class="field-items"><div class="field-item">';
            foreach ($profile['main']->field_experts['und'] as $value) {
                $expert = db_select("taxonomy_term_data", "term")
                    ->fields("term", array("name"))
                    ->condition("tid", $value["tid"])->execute()->fetch()->name;
                print '<a href="/taxonomy/term/' . $value['tid'] . '" target="_blank" class="btn small-btn has-wave">' . $expert . '</a>';
            }
            print '</div></div></div>';
        }
        /*----------------------------------------*/
        /*This part is for checking the completion of the profile*/
        print '<div class="field field-name-field-emailtext field-type-text field-label-inline clearfix">
	<div class="field-label">نشانی پست الکترونیکی:&nbsp;</div>
	<div class="field-items">
	<div class="field-item even">' . $user_p->mail . '</div></div></div>';

        $output = '';
        $items = 0;
        if (!isset($profile['main']->field_full_name['und'][0]) || strlen($profile['main']->field_full_name['und'][0]['value']) < 5) {
            $items += 1;
        }
        if (!isset($profile['main']->field_education_degree['und'][0]) || strlen($profile['main']->field_education_degree['und'][0]['value']) < 5) {
            $items += 1;
        }
        if (!isset($profile['main']->field_education_field['und'][0]) || strlen($profile['main']->field_education_field['und'][0]['value']) < 5) {
            $items += 1;
        }
        if (!isset($profile['main']->field_university['und'][0]) || strlen($profile['main']->field_university['und'][0]['value']) < 5) {
            $items += 1;
        }
        if (!isset($profile['main']->field_job['und'][0]) || strlen($profile['main']->field_job['und'][0]['value']) < 5) {
            $items += 1;
        }
        if (!isset($profile['main']->field_about_me['und'][0]) || strlen($profile['main']->field_about_me['und'][0]['value']) < 5) {
            $items += 1;
        }
        /* 	if(!isset($profile['main']->field_skills['und'][0]) || strlen($profile['main']->field_skills['und'][0]['value']) < 5){
                $items += 1;
            }	 */
        if (!isset($profile['main']->field_mobile['und'][0]) || strlen($profile['main']->field_mobile['und'][0]['value']) < 5) {
            $items += 1;
        }
        if (!isset($profile['main']->field_experts['und'][0])) {
            $items += 1;
        }
        if ($items > 0) {
            $output .= '<a href="/user/' . $user_p->uid . '/edit/main?destination=user" class="btn btn-primary">تکمیل پروفایل</a>';
        }
        if (!isset($user_p->picture->fid)) {
            $output .= '<a href="/user/' . $user_p->uid . '/edit?destination=user" class="btn btn-primary">افزودن تصویر پروفایل</a>';
            $items += 1;
        }
        /*
        if(!isset($user_p->linkedin['public-profile-url'])){
            $output .= '<a href="/user/'. $user_p->uid .'/edit/linkedin?destination=user" class="btn btn-primary">اتصال به LinkedIn</a>';
            $items += 1 ;
        }
        */
        if ($items > 0) {
            print '<div class="profile-percent progress"><div style="width: ' . (9 - $items) / 9 * 100 . '%" class="progress-bar"><span>' . number_format((9 - $items) / 9 * 100) . ' %</span></div></div>';
            print '<p class="description profile-percent">با تکمیل پروفایل خود از یک ماه کاربری VIP سایت بهره مند شوید.';
            print $output . '</p>';
        } else {

            if (!isset($profile['main']->field_profile_complete['und'][0]) || $profile['main']->field_profile_complete['und'][0]['value'] == 0) {
                $profile['main']->field_profile_complete['und'][0]['value'] = 1;
                profile2_save($profile['main']);
                $from = 'info@civil808.com';
                $subject_admin = 'تکمیل پروفایل' . $user_p->uid;
                $to_admin = 'saze808@gmail.com';
                $body_admin = '<p>کاربری پروفایل خود را تکمیل کرده است.</p><p><a href="http://civil808.com/user/' . $user_p->uid . '/edit">http://civil808.com/user/' . $user_p->uid . '/edit</a></p>';
                simple_mail_send($from, $to_admin, $subject_admin, $body_admin);

                drupal_goto('/user/' . $user_p->uid);
            }

            //25.000 points to users who completed their profiles

            /*if(!isset($profile['main']->field_bool['und'][0]) || $profile['main']->field_bool['und'][0]['value'] == 0){
               //change it to 1 to prevent of adding points more than one time
               $profile['main']->field_bool['und'][0]['value'] = 1;
               //profile2_save($profile['main']);
               //adding points to user
               $params = array (
                   'tid' => 2537,
                   'uid' => $user_p->uid,
                   'points' => 25000,
                   'operation' => 'completing profile',
               );
               $st = userpoints_userpointsapi($params);


               //sending an email to saze808@gmail.com
                   $from = 'info@civil808.com';
                   $subject_admin = 'تکمیل پروفایل'. $user_p->uid;
                   $to_admin = 'saze808@gmail.com';
                   $body_admin = '<p>کاربری پروفایل خود را تکمیل کرده است.</p><p><a href="http://civil808.com/user/'.$user_p->uid.'/edit">http://civil808.com/user/'.$user_p->uid.'/edit</a></p>';
                   simple_mail_send($from, $to_admin, $subject_admin, $body_admin);

               drupal_goto('/user/'. $user_p->uid);
           }*/
        }
        print '</div>';
        /*----------------------------------------*/
        print '</div>';
        /*---------------------------------------------------------------------------------------------------------------*/
        print '<div class="region-middle">';
        /*----------------------------------------*/
        /*This part is for relation ships*/
        print '<div class="profile-relations">';
        $query = db_select('user_relationships', 'relation');
        $query->fields('relation', array('requestee_id'));
        $query->condition('relation.requester_id', $user_p->uid);
        $query->condition('relation.approved', 1);
        $relations = $query->execute()->fetchCol();
        /*$relations is an array that contains all uids that in relationships with user*/

        print '<h3 class = "relation-title">تعداد روابط : ' . count($relations) . '</h3>';
        if (empty($relations)) {
            print '<a href = "/landing/members" target="_blank" class = "btn">مشاهده تمام کاربران</a>';
        } else {
            /*first print the pictures of the users that have picture*/
            print '<div class = "picture">';
            $counter = 0;
            $no_picture = array();
            $query = db_select("users", "user");
            $query->leftJoin("file_managed", "image", "image.fid = user.picture");
            $query->fields("user", array("name"));
            $query->fields("image", array("uri"));
            $query->condition("user.uid", $relations, "IN");
            $related_users = $query->execute()->fetchAll();
            foreach ($related_users as $related_user) {
                if ($counter > 3) break;

                if (!empty($related_user->uri)) {
                    $counter++;
                    print theme(
                        'image_style',
                        array(
                            'style_name' => 'userprofilrfront',
                            'path' => $related_user->uri,
                            'alt' => $related_user->name,
                            'title' => $related_user->name
                        )
                    );
                } else {
                    array_push($no_picture, $related_user);
                }
            }
            if ($counter <= 3 && !empty($no_picture)) {
                foreach ($no_picture as $row) {
                    if ($counter > 3) break;
                    if (empty($row->uri)) {
                        print '<img src="http://civil808.com/sites/all/themes/sara/images/profile2front.jpg">';
                        $counter++;
                    }
                }
            }
            print '<a class = "btn" href="/user/' . $user_p->uid . '/relationships"></a>';
            print '</div>';
        }
        print '</div>';
        /*----------------------------------------*/
        /*This part is for charging account*/
        print '<div class="user-points">';
        print '<div class="pane-content-user-points">';
        print '<h3 class="pane-title">اعتبار</h3>
                <div class="item-list">
                    <ul class="userpoints-points">
                        <li class="first last">
                            <em class="placeholder">عمومی</em>: ';
        echo formatMoney(userpoints_get_current_points($user_p->uid, 'all'));
        print ' تومان 
                         </li>
                    </ul>
                </div>';
        $output = '';
        $num = 0;
        if ($user->uid == $user_p->uid) {
            $output .= '<li><a href="/user/' . $user_p->uid . '/money/charge" class="userpoints-charg">شارژ حساب</li>';
            $output .= '<li><a href="/user/' . $user_p->uid . '/money/reward" class="userpoints-reward">درخواست وجه</li>';
            $num++;
            $num++;
        }
        if (userpoints_admin_access('add')) {
            $output .= '<li><a href="/admin/config/people/userpoints/add/' . $user_p->uid . '" class="userpoints-adjust">ایجاد تراکنش</li>';
            $num++;
        }

        if (strlen($output) > 0) {
            print '<ul class="links userpoints-links num' . $num . '">' . $output . '</ul>';
        }
        print '</div>';
        print '</div>';
        /*----------------------------------------*/
        /*This part is for user bank cart*/
        if ($user->uid == $user_p->uid || in_array("administrator", $user->roles)) {
            print '<div class="profile-bank">';
            $query = db_select("profile", "profile");
            $query->join("field_data_field_bank_cart_num", "bank_cart_num", "bank_cart_num.entity_id = profile.pid and bank_cart_num.bundle = 'bank' ");
            $query->addField("bank_cart_num", "field_bank_cart_num_value", "cart");
            $query->condition("profile.uid", $user_p->uid)->condition("profile.type", "bank");
            $cart = $query->execute()->fetch();
            if (empty($cart)) {
                print '<h3>بانک</h3><dl class="userpoints-links"><a href="/user/' . $user_p->uid . '/edit/bank" target="_blank">افزودن شماره حساب</a></dl>';
            } else {
                print ' <div class="panel-pane pane-entity-field-extra pane-user-profile-bank user-bank">
                    <div class="pane-content"><a id="profile-bank"></a>
                        <h3>بانک</h3>
                        <dl>
                          <div class="ds-1col entity entity-profile2 profile2-bank view-mode-account clearfix">
                              <div class="field field-name-field-bank-cart-num field-type-text field-label-inline clearfix">
                                  <div class="field-label">شماره کارت بانکی: </div>
                                  <div class="field-items"><div class="field-item even">' . $cart->cart . '</div></div>
                              </div>
                          </div>
                        </dl>
                    </div>
                    </div>';
            }
            print '</div>';
        }
        /*----------------------------------------*/
        print '</div>';
        /*---------------------------------------------------------------------------------------------------------------*/
        print '<div class="region-left">';
        /*----------------------------------------*/
        /*This part is for relation ships*/
        print '<div class="left-info">';
        if ($user->uid == $user_p->uid) {
            if (!has_linkedin_account($user->uid)) {
                print '<div class="linkedin integration"><a href="/linkedin/' . $user->uid . '/connect">اتصال به LinkedIn</a></div>';
            } else {
                print '<div class="linkedin view"><a href="/user/' . $user->uid . '/linkedin">پروفایل LinkedIn</a></div>';
            }
            if (!isset($user_p->roles['8'])) {
                print '<div class="vip link"><a href="/landing/vip" target="_blank">ارتقا به عضویت VIP</a></div>';
            } else {
                print '<div class="vip view"><a href="/landing/vip" target="_blank">کاربر VIP</a></div>';
            }
            print '<div class="send-message"><a href="/messages/new/60" target="_blank">پیغام به مدیریت سایت</a></div>';
            print '<div class="connections"><a href="/user/' . $user_p->uid . '/relationships" target="_blank">روابط</a></div>';
            print '<div class="joyride_start_link"><a href="#" class="joyride-start-link">راهنمای صفحه کاربر</a></div>';

            //for printing conference tickets
            $query = db_select('uc_orders', 'o');
            $query->join('uc_order_products', 'p', 'o.order_id = p.order_id');
            $results = $query->fields('o', array('order_id'))
                ->fields('p', array('qty', 'data'))
                ->condition('o.uid', $user->uid)
                ->condition('p.nid', '17782')
                ->condition('o.order_status', array('completed', 'pending'), 'IN')
                ->execute()
                ->fetchAll();
            if (count($results) > 0) {
                print '<div class="conference"><a href="/form/complete-information" target="_blank">تکمیل اطلاعات و پرینت بلیط <span>همایش طراحی عملکردی</span></a></div>';
            }
        } else {
            if (has_linkedin_account($user->uid)) {
                print '<div class="linkedin view"><a href="/user/' . $user->uid . '/linkedin">پروفایل LinkedIn</a></div>';
            }
            if (isset($user_p->roles['8'])) {
                print '<div class="vip view"><a href="/landing/members?rid=8" target="_blank">کاربر VIP</a></div>';
            }
            if ($user_p->uid != 2) {
                print '<div class="send-message"><a href="/messages/new/' . $user_p->uid . '" target="_blank">ارسال پیغام به این کاربر</a></div>';

                /*--------------------------------------------------------------------------------------------*/
                $action_types = array('add' => 1, 'remove' => 1, 'requested' => 1, 'received' => 1);
                $destination = drupal_get_destination();
                $destination = $destination['destination'];

                $from_us = user_relationships_load(array('requester_id' => $user->uid, 'requestee_id' => $user_p->uid));

                foreach ($from_us as $relationship) {
                    if ($relationship->approved && user_relationships_ui_check_access('view', NULL, $relationship)) {
                        if (user_relationships_ui_check_access('delete', NULL, $relationship)) {
                            print '<span class="azl">';
                            print theme('user_relationships_remove_link', array('uid' => $user->uid, 'rid' => $relationship->rid));
                            print '</span>';
                        } else {
                            print '<span class="azl"><a>';
                            print user_relationships_type_get_name($relationship) . ($relationship->is_oneway ? ($relationship->requester_id == $user->uid ? t(' (You to Them)') : t(' (Them to You)')) : NULL);
                            print '</a></span>';
                        }
                    } else if (!$relationship->approved) {
                        print '<span class="laghv">';
                        print l('لغو درخواست ارتباط', "user/{$loged_in_user->uid}/relationships/requested/{$relationship->rid}/cancel", array(
                            'attributes' => array('class' => array('user_relationships_popup_link')),
                            'query' => array('destination' => $destination)
                        ));
                        print '</span>';
                    }
                }

                $to_us = user_relationships_load(array('requester_id' => $user_p->uid, 'requestee_id' => $user->uid));
                foreach ($to_us as $relationship) {
                    if (!$relationship->approved && user_relationships_user_access('maintain @relationship relationships', $relationship)) {
                        print '<span class="accept">';
                        print l('تایید درخواست این کاربر', "user/{$user->uid}/relationships/requested/{$relationship->rid}/approve", array(
                            'attributes' => array('class' => array('user_relationships_popup_link')),
                            'query' => array('destination' => $destination)
                        ));
                        print '</span>';
                    }
                }

                $relationships = user_relationships_get_requestable_rtypes($user, $user_p, 'full');
                if ($relationships) {
                    // If configured, create direct links.
                    if (variable_get('user_relationships_show_direct_links', 1)) {
                        // Create a single link, or one for each relationship type.
                        foreach ($relationships as $relationship_type) {
                            print '<span class="add">';
                            print theme('user_relationships_request_relationship_direct_link', array('relate_to' => $user_p, 'relationship_type' => $relationship_type));
                            print '</span>';
                        }
                    } // just one generic link pointing to a page with dropdown.
                    else {
                        print '<span class="add">';
                        print theme('user_relationships_request_relationship_link', array('relate_to' => $user_p));
                        print '</span>';
                    }
                }
            }
            /*--------------------------------------------------------------------------------------------*/
            if ($user->uid == 0) {
                print '<span class="add not-login"><a href="/user/login"> ایجاد ارتباط </a></span>';
            }
        }
        print '<div class="ad_video"><a href="/node/20991" target="_blank">ویژگی های پروفایل کاربری</a></div>';
        print '</div>';
        /*----------------------------------------*/
        print '</div>';
        /*---------------------------------------------------------------------------------------------------------------*/
        print '</div>';
    }
?>

<style>
    #joyRideTipContent { display: none; }

    /* Default styles for the container */
    .joyride-tip-guide {
        position: absolute;
        background: #000;
        background: rgba(0,0,0,0.8);
        display: none;
        width: 300px;
        z-index: 101;
        top: 0; /* keeps the page from scrolling when calculating position */
        left: 0;
        -moz-border-radius: 4px;
        -webkit-border-radius: 4px;
        border-radius: 4px;
    }

    .joyride-content-wrapper {
        padding: 10px 10px 15px 15px;
    }

    /* Mobile */
    @media only screen and (max-width: 767px) {
        .joyride-tip-guide {
            width: 95% !important;
            -moz-border-radius: 0;
            -webkit-border-radius: 0;
            border-radius: 0;
            left: 2.5% !important;
        }
        .joyride-tip-guide-wrapper {
            width: 100%;
        }
    }


    /* Add a little css triangle pip, older browser just miss out on the fanciness of it */
    .joyride-tip-guide span.joyride-nub {
        display: block;
        position: absolute;
        left: 22px;
        width: 0;
        height: 0;
        border: solid 14px;
        border: solid 14px;
    }

    .joyride-tip-guide span.joyride-nub.top {
        /*
        IE7/IE8 Don't support rgba so we set the fallback
        border color here. However, IE7/IE8 are also buggy
        in that the fallback color doesn't work for
        border-bottom-color so here we set the border-color
        and override the top,left,right colors below.
        */
        border-color: #000;
        border-color: rgba(0,0,0,0.8);
        border-top-color: transparent !important;
        border-left-color: transparent !important;
        border-right-color: transparent !important;
        top: -28px;
        bottom: none;
    }

    .joyride-tip-guide span.joyride-nub.bottom {
        /*
        IE7/IE8 Don't support rgba so we set the fallback
        border color here. However, IE7/IE8 are also buggy
        in that the fallback color doesn't work for
        border-top-color so here we set the border-color
        and override the bottom,left,right colors below.
        */
        border-color: #000;
        border-color: rgba(0,0,0,0.8) !important;
        border-bottom-color: transparent !important;
        border-left-color: transparent !important;
        border-right-color: transparent !important;
        bottom: -28px;
        bottom: none;
    }

    .joyride-tip-guide span.joyride-nub.right {
        border-color: #000;
        border-color: rgba(0,0,0,0.8) !important;
        border-top-color: transparent !important;
        border-right-color: transparent !important;
        border-bottom-color: transparent !important;
        top: 22px;
        bottom: none;
        left: auto;
        right: -28px;
    }

    .joyride-tip-guide span.joyride-nub.left {
        border-color: #000;
        border-color: rgba(0,0,0,0.8) !important;
        border-top-color: transparent !important;
        border-left-color: transparent !important;
        border-bottom-color: transparent !important;
        top: 22px;
        left: -28px;
        right: auto;
        bottom: none;
    }

    /* Typography */
    .joyride-tip-guide h1,.joyride-tip-guide h2,.joyride-tip-guide h3,.joyride-tip-guide h4,.joyride-tip-guide h5,.joyride-tip-guide h6 {
        line-height: 1.25;
        margin: 0;
        font-weight: bold;
        color: #fff;
    }
    .joyride-tip-guide h1 { font-size: 30px; }
    .joyride-tip-guide h2 { font-size: 26px; }
    .joyride-tip-guide h3 { font-size: 22px; }
    .joyride-tip-guide h4 { font-size: 18px; }
    .joyride-tip-guide h5 { font-size: 16px; }
    .joyride-tip-guide h6 { font-size: 14px; }
    .joyride-tip-guide p {
        margin: 0 0 18px 0;
    }
    .joyride-tip-guide a {
        color: rgb(255,255,255);
        text-decoration: none;
        border-bottom: dotted 1px rgba(255,255,255,0.6);
    }
    .joyride-tip-guide a:hover {
        color: rgba(255,255,255,0.8);
        border-bottom: none;
    }

    /* Button Style */
    .joyride-tip-guide .joyride-next-tip {
        width: auto;
        padding: 6px 18px 4px;
        font-size: 13px;
        text-decoration: none;
        color: rgb(255,255,255);
        border: solid 1px rgb(0,60,180);
        background: rgb(0,99,255);
        background: -moz-linear-gradient(top, rgb(0,99,255) 0%, rgb(0,85,214) 100%);
        background: -webkit-gradient(linear, left top, left bottom, color-stop(0%,rgb(0,99,255)), color-stop(100%,rgb(0,85,214)));
        background: -webkit-linear-gradient(top, rgb(0,99,255) 0%,rgb(0,85,214) 100%);
        background: -o-linear-gradient(top, rgb(0,99,255) 0%,rgb(0,85,214) 100%);
        background: -ms-linear-gradient(top, rgb(0,99,255) 0%,rgb(0,85,214) 100%);
        filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#0063ff', endColorstr='#0055d6',GradientType=0 );
        background: linear-gradient(top, rgb(0,99,255) 0%,rgb(0,85,214) 100%);
        text-shadow: 0 -1px 0 rgba(0,0,0,0.5);
        -webkit-border-radius: 2px;
        -moz-border-radius: 2px;
        border-radius: 2px;
        -webkit-box-shadow: 0px 1px 0px rgba(255,255,255,0.3) inset;
        -moz-box-shadow: 0px 1px 0px rgba(255,255,255,0.3) inset;
        box-shadow: 0px 1px 0px rgba(255,255,255,0.3) inset;
    }

    .joyride-next-tip:hover {
        color: rgb(255,255,255) !important;
        border: solid 1px rgb(0,60,180) !important;
        background: rgb(43,128,255);
        background: -moz-linear-gradient(top, rgb(43,128,255) 0%, rgb(29,102,211) 100%);
        background: -webkit-gradient(linear, left top, left bottom, color-stop(0%,rgb(43,128,255)), color-stop(100%,rgb(29,102,211)));
        background: -webkit-linear-gradient(top, rgb(43,128,255) 0%,rgb(29,102,211) 100%);
        background: -o-linear-gradient(top, rgb(43,128,255) 0%,rgb(29,102,211) 100%);
        background: -ms-linear-gradient(top, rgb(43,128,255) 0%,rgb(29,102,211) 100%);
        filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#2b80ff', endColorstr='#1d66d3',GradientType=0 );
        background: linear-gradient(top, rgb(43,128,255) 0%,rgb(29,102,211) 100%);
    }

    .joyride-timer-indicator-wrap {
        width: 50px;
        height: 3px;
        border: solid 1px rgba(255,255,255,0.1);
        position: absolute;
        right: 17px;
        bottom: 16px;
    }
    .joyride-timer-indicator {
        display: block;
        width: 0;
        height: inherit;
        background: rgba(255,255,255,0.25);
    }

    .joyride-close-tip {
        position: absolute;
        right: 10px;
        top: 10px;
        color: rgba(255,255,255,0.4) !important;
        text-decoration: none;
        font-family: Verdana, sans-serif;
        font-size: 10px;
        font-weight: bold;
        border-bottom: none !important;
    }

    .joyride-close-tip:hover {
        color: rgba(255,255,255,0.9) !important;
    }

    .joyride-modal-bg {
        position: fixed;
        height: 100%;
        width: 100%;
        background: rgb(0,0,0);
        background: transparent;
        background: rgba(0,0,0, 0.5);
        -ms-filter:"progid:DXImageTransform.Microsoft.Alpha(Opacity=50)";
        filter: alpha(opacity=50);
        opacity: 0.5;
        z-index: 100;
        display: none;
        top: 0;
        left: 0;
        cursor: pointer;
    }
</style>
<script>
    var $ = jQuery;
    $(document).ready(function () {
            $.getScript('/sites/all/libraries/joyride/jquery.joyride-2.0.3.js', function(){

                $('a.joyride-start-link').on('click', function(event) {
                    event.preventDefault();

                    if($('ol#joyride-tips-content').length > 0) $('ol#joyride-tips-content').remove();

                    $('body').append('<ol id="joyride-tips-content" style="visibility: hidden;"><li data-button="شروع" class="user-help-1">  <h4>راهنمای صفحه ی کاربری</h4>  <p>هر زمان که خواستید می توانید دوباره این راهنما را اجرا کنید.</p>  <p>این راهنما شامل معرفی بخش های جدید و راهنمای استفاده از پروفایل وب سایت می باشد.</p></li><li data-class="main-tab li.messages" data-text="بعدی" class="user-help-7" data-options="tipLocation:bottom;">  <h4>پیغام ها</h4>  <p>در آپدیت جدید 808، شما این امکان را دارید که با جامعه بزرگ مهندسین عمران و معماری کشور در ارتباط باشد. برای ارسال پیغام به هر کدام از کاربران سایت، به صفحه کاربری آن شخص مراجعه کرده و در بالای صفحه سمت راست لینک پیغام به این کاربر را کلیک کنید. در این تب نیز می توانید لیست پیغام های خود را ببینید.</p></li><li data-class="main-tab li.points" data-text="بعدی" class="user-help-8" data-options="tipLocation:bottom;">  <h4>اعتبار</h4>  <p>شما با استفاده از صفحه اصلی پروفایل خود می توانید اعتبار فعلی خود را مشاهده کرده و با لینک شارژ حساب، اعتبار خود را افزایش دهید. در این تب همه تراکنش های اعتبار شما لیست می شود. </p></li><li data-class="main-tab li.sharepoints" data-text="بعدی" class="user-help-9" data-options="tipLocation:bottom;">  <h4>سهم از فروش</h4>  <p>اگر از همکاران سایت هستید، می توانید در این بخش لیستی از سهم فروش خود از محتواهای خود در سایت را مشاهده کنید. این مبالغ به صورت اتوماتیک به حسای کاربری شما اضافه می شوند.</p></li><li data-class="main-tab li.linkedin" data-text="بعدی" class="user-help-2" data-options="tipLocation:bottom;">  <h4>اتصال به LinkedIn</h4>  <p>با اتصال اکانت لینکدین خود به سایت، صفحه ای شامل اطلاعات لینکدین شما به پروفایلتان اضافه می شود.</p></li><li data-class="main-tab li.myresults" data-text="بعدی" class="user-help-11" data-options="tipLocation:bottom;">  <h4>نتایج آزمون</h4>  <p>پس از شرکت در آزمون های آزمایشی 808، می توانید نتایج خود را در این تب مشاهده کنید.</p></li><li data-class="main-tab li.relationships" data-text="بعدی" class="user-help-12" data-options="tipLocation:bottom;">  <h4>روابط</h4>  <p>با مراجعه به پروفایل هر یک از کاربران سایت می توانید بر روی دکمه "ارتباط با این کاربر" کلیک کرده و پس از تایید از طرف ایشان، لیست ارتباطات خود را در این بخش مشاهده کنید.</p></li><li data-class="field-name-user-experts" data-text="بعدی" class="user-help-14" data-options="tipLocation:bottom;">  <h4>تخصص ها</h4>  <p>با اضافه کردن تخصص های خود به سایت، از مشاوران اختصاصی 808، مشاوره رایگان دریافت کنید. با دیگر متخصصین حوزه مربوطه آشنا شوید و پروژه های مرتبط با تخصص خود، دریافت کنید.</p></li><li data-class="pane-quicktabs-user-bookmark" data-text="بعدی" class="user-help-10" data-options="tipLocation:top;">  <h4>نشان شده ها</h4>  <p>شما می توانید هر کدام از محتواهای سایت را با استفاده از آیکن سمت راست تیترشان، نشان کرده و لیست آن ها را در این بخش مشاهده کنید.</p></li><li data-class="pane-quicktabs-user-contents" data-text="بعدی" class="user-help-3" data-options="tipLocation:top;scrollSpeed:2000;">  <h4>لیست محتواهای منتشر شده توسط شما</h4>  <p>در این بخش محتواهای تولیدی شما به تفکیک نوع آن ها، برای همه اعضای سایت نمایش داده می شوند.</p></li><li data-class="pane-quicktabs-user-all-boughts " data-text="بعدی" class="user-help-4" options="tipLocation:top;scrollSpeed:900;">  <h4>لیست محصولات خریداری شده</h4>  <p>این بخش شامل تمامی محصولات خریداری شده توسط شما؛ اعم از مقالات، ایبوک ها، ورکشاپ های تخصصی، دوره های آموزشی ترمیک و محصولات فروشگاه 808 است. به منظور تکمیل رزومه شما در سایت، این بخش شامل اطلاعات محدودی از خرید شما بوده و برای همه اعضای سایت قابل مشاهده است. </p></li><li data-class="user-sale-report" data-text="بعدی" class="user-help-5" options="tipLocation:top;scrollSpeed:900;">  <h4>محتواهای فروخته شده</h4>  <p>شما می توانید با مشارکت در تولید محتواهای آموزشی 808، در این بخش فروش محصولات خود را به صورت شفاف دنبال کنید و با مخاطبین خود در ارتباط باشید. این بخش نیز به هدف تکمیل رزومه کاری شما برای عموم قابل مشاهده است.</p></li><li data-class="pane-uc-orders-user" data-text="بعدی" class="user-help-6" options="tipLocation:top;scrollSpeed:900;">  <h4>سفارش ها</h4>  <p>این قسمت شامل جزئیات سفارش های شما در فروشگاه و دوره های آموزشی ترمیک 808 است، شما می توانید با مراجعه به این جدول سفارش های خود را پیگیری کنید. اطلاعات این بخش فقط برای شما قابل مشاهده است.</p></li><li data-button="بستن" class="user-help-13">  <h2>راهنمای صفحه ی کاربری</h2>  <p>هر زمان که خواستید می توانید دوباره این راهنما را اجرا کنید.</p>  <p>این راهنما شامل معرفی بخش های جدید و راهنمای استفاده از پروفایل وب سایت می باشد.</p></li>  </ol>');

                    $('ol#joyride-tips-content').joyride({
                        'tipLocation': 'bottom',         // 'top' or 'bottom' in relation to parent
                        'nubPosition': 'auto',           // override on a per tooltip bases
                        'scrollSpeed': 300,              // Page scrolling speed in ms
                        'timer': 0,                   // 0 = off, all other numbers = time(ms)
                        'startTimerOnClick': false,       // true/false to start timer on first click
                        'nextButton': true,              // true/false for next button visibility
                        'tipAnimation': 'pop',           // 'pop' or 'fade' in each tip
                        'tipAnimationFadeSpeed': 300,    // if 'fade'- speed in ms of transition
                        'cookieMonster': true,           // true/false for whether cookies are used
                        'cookieName': 'JoyRide',         // choose your own cookie name
                        'cookieDomain': false,           // set to false or yoursite.com
                        'tipContainer': 'body',            // Where the tip be attached if not inline
                    });

                    return false;
                });

            });
        })
</script>

