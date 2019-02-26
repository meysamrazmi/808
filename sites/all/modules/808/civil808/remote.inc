<?php

function remote_subscription_form($form, &$form_state , $uid){
    try{
        /*check that user is being administrator*/
        global $user;
        if(!in_array("administrator" , $user->roles)) drupal_goto("/");

        /*find the previous merchant ID of customer*/
        $query = db_select("remote_login_subscription" , "subscription");
        $query->fields("subscription" , array("merchant"));
        $query->condition("uid" , $uid);
        $merchant = $query->execute()->fetchCol();
        $merchant = join(" , " , $merchant);

        $form['uid'] = array('#type' => 'hidden', '#value' => $uid);
        $form['domain'] = array(
            '#type' => 'textfield',
            '#title' => t('دامنه مورد استفاده'),
            '#size' => 60,
            '#maxlength' => USERNAME_MAX_LENGTH,
            '#required' => TRUE,
            '#description' => t('دامنه سایت خود را وارد کنید.'),
        );
        $form['name'] = array(
            '#type' => 'textfield',
            '#title' => t('نام شرکت'),
            '#size' => 60,
            '#maxlength' => USERNAME_MAX_LENGTH,
            '#required' => TRUE,
        );
        $list = array("uid" => "آیدی کاربر" , "name" => "نام کاربری" , "mail" => "ایمیل" , "full_name" => "نام و نام خانوادگی");
        $form['setting'] = array(
            '#type' => 'select',
            '#title' => t('تنظیمات دریافت اطلاعات'),
            '#options' => $list,
            '#multiple' => TRUE,
            '#required' => TRUE,
            '#description' => t('اطلاعاتی از کاربر را که نیاز دارید دریافت کنید وارد نمایید.'),
        );
        $form['file'] = array(
            '#type' => 'file',
            '#title' => t('Choose a file'),
            '#description' => t('فقط از فرمت های jpg jpeg png استفاده کنید.'),
        );
        $form['merchant'] = array(
            '#prefix' => '<div><label>کدهای بازرگانی شما : </label>',
            '#markup' => $merchant,
            '#suffix' => '</div>',
        );
        $form['submit'] = array(
            '#type' => 'submit',
            '#value' => t('save'),
        );

        return $form;
    }catch (Exception $e){
        drupal_set_message($e->getMessage() , 'error');
    }
}
function remote_subscription_form_validate($form, &$form_state){
    try{
    }
    catch (Exception $e){
        drupal_set_message($e->getMessage() , 'error');
    }
}
function remote_subscription_form_submit($form, &$form_state){
    try{
        $validators = array();
        $file = file_save_upload('file', $validators, 'public://');
        if (!empty($file->fid)) {
            // Change the file status from temporary to permanent.
            $file->status = FILE_STATUS_PERMANENT;
            file_save($file);
            // Required to be able to reference this file.
            file_usage_add($file, 'civil808', 'files', $file->fid);
        }

        /*generate a merchant ID for customer*/
        $merchant = hash_hmac("sha256" , $form_state["values"]["domain"] , "saze@civil@808" . $form_state["values"]["uid"] , false);
        $merchant = substr($merchant , 0 , 15);

        /*
         * insert customer information in db
         * */
        db_insert("remote_login_subscription")
            ->fields(array(
                "domain" => $form_state["values"]["domain"],
                "uid" => $form_state["values"]["uid"],
                "merchant" => $merchant,
                "setting" => serialize(array_values($form_state["values"]["setting"])),
                "name" => $form_state["values"]["name"],
                "logo_fid" => $file->fid,
                "created" => REQUEST_TIME,
            ))->execute();
    }
    catch (Exception $e){
        drupal_set_message($e->getMessage() , 'error');
    }
}


/*remote login form*/
function remote_login_form($form, &$form_state , $token){
    try{
        /*check if token is valid or not*/
        $query = db_select("remote_login_log" , "log");
        $query->fields("log" , array());
        $query->condition("log.token" , $token);
        $log = $query->execute()->fetch();
        if(empty($log)){
            /*if token is not valid return back with error parameter*/
            update_user($token , 0 , "error");
            drupal_goto($_SERVER["HTTP_REFERER"] . "?status=401&error=Unauthorized");
        }
        global $user;
        if($user->uid > 0) {
            /*if user is already logged in just return back with success status and token*/
            update_user($token , $user->uid , "successful");
            drupal_goto($log->callback . "?status=200&token=" . $token);
        }

        /*get destination site name and logo to show in remote login page*/
        $query = db_select("remote_login_subscription" , "subscription");
        $query->leftJoin("file_managed" , "file" , "file.fid = subscription.logo_fid");
        $query->fields("subscription" , array("name"));
        $query->fields("file" , array("uri"));
        $query->condition("subscription.merchant" , $log->merchant);
        $company = $query->execute()->fetch();
        if(!empty($company->uri)) $company->uri = image_style_url("medium" , $company->uri);

        /*login form for user
         * It shows in page--remote.tpl.php
         */
        $form['callback'] = array('#type' => 'hidden', '#value' => $log->callback);
        $form['token'] = array('#type' => 'hidden', '#value' => $token);

	    $form['description'] = array(
		    '#prefix' => '<div class="description">
							<div class="title">ورود به سایت از طریق 808</div>
							<div class="company-logo">
								<img src="' . $company->uri . '"/>
								<i></i>
								<img src="https://civil808.com/sites/all/themes/sara/logo.png" style="max-width: 95px;">
							</div>
							<div class="company-name"><label>نام شرکت : </label>' . $company->name . '</div>
						  </div>',
		    '#markup' => '',
	    );
	    $form['div'] = array(
		    '#type' => 'fieldset',
		    '#collapsible' => FALSE,
	    );
        $form['div']['username_email'] = array(
            '#type' => 'textfield',
            '#title' => t('نام کاربری یا نشانی پست الکترونیک'),
            '#size' => 60,
            '#maxlength' => USERNAME_MAX_LENGTH,
            '#required' => TRUE,
        );
        $form['div']['password'] = array(
            '#type' => 'password',
            '#title' => t('Password'),
            '#required' => TRUE,
        );

        $form['div']['submit'] = array(
            '#type' => 'submit',
            '#value' => 'ورود',
	        '#suffix' => '<a href="/user/register" target="_blank" class="join">عضویت در civil808</a>',
        );
        return $form;
    }catch (Exception $e){
        drupal_set_message($e->getMessage() , 'error');
    }
}
function remote_login_form_validate($form, &$form_state){
    try{
        /*check username or email exists or not*/
        $username_email = trim($form_state["values"]["username_email"]);
        $query = db_select("users" , "user");
        $query->fields("user" , array("name"));
        $or = db_or();
        $or->condition("user.name" , $username_email , "LIKE");
        $or->condition("user.mail" , $username_email , "LIKE");
        $query->condition($or);
        $username = $query->execute()->fetch();
        if(empty($username)) form_set_error('username_email', t('نام کاربری یا ایمیل اشتباه است.'));
        $username = $username->name;

        /*check password correctness*/
        $uid = user_authenticate($username, $form_state["values"]["password"]);
        if(!$uid) form_set_error('password', t('رمز عبور اشتباه است.'));

        $form_state["values"]["uid"] = $uid;
    }catch (Exception $e){
        drupal_set_message($e->getMessage() , 'error');
    }
}
function remote_login_form_submit($form, &$form_state){
    try{
        $uid = $form_state["values"]["uid"];
        global $user;
        $user = user_load($uid);
        user_login_finalize();
        update_user($form_state["values"]["token"] , $user->uid , "successful");
        $form_state["redirect"] = $form_state["values"]["callback"] . "?status=200&token=" . $form_state["values"]["token"];

    }catch (Exception $e){
        drupal_set_message($e->getMessage() , 'error');
    }
}

/*update user status and uid in remote_login_log*/
function update_user($token , $uid , $status){
    db_update("remote_login_log")
        ->fields(array(
            'uid' => $uid,
            'status' => $status
        ))
        ->condition('token', $token)
        ->execute();
}
