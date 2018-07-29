<?php

/***********api version code admin menu**********/
function api_version_lists(){
    $query = db_select("api_code_version" , "version")
        ->fields("version")->execute()->fetchAll();

    foreach ($query as $data) {
        $rows[] = array(
            array('data' => $data->url),
            array('data' => $data->method),
            array('data' => $data->source_name),
            array('data' => $data->version),
            array('data' => $data->last_function),
            array('data' => l(t('Edit'), 'admin/structure/services/apiversion/edit/' . $data->id)  . ' - ' . l(t('Delete'), 'admin/structure/services/apiversion/delete/' . $data->id)),
        );
    }

    return theme('table', array('header'=>array(t('url'), t('method'),t('source'),t('version'), t('last_function'), t('action')), 'rows'=>$rows));
}
function add_api_version_form($from, &$form_state , $id = 0){
    try {
        $data = (array) db_select("api_code_version" , "version")
            ->fields("version")->condition("id" , $id)->execute()->fetch();

        $form['id'] = array('#type' => 'hidden', '#value' => $id);

        $form['url'] = array(
            '#type' => 'textfield',
            '#title' => t('مسیر api'),
            '#description' => t('مسیر api را وارد کنید'),
            '#default_value' => (!empty($data["url"]))? $data["url"] : '',
        );
        $form['method'] = array(
            '#type' => 'textfield',
            '#title' => t('method'),
            '#description' => t('متد ریکوئست'),
            '#default_value' => (!empty($data["method"]))? $data["method"] : '',
        );
        $form['source'] = array(
            '#type' => 'textfield',
            '#title' => t('نوع فرستنده'),
            '#description' => t('نوع فرستنده درخواست، android , ios , ...'),
            '#default_value' => (!empty($data["source_name"]))? $data["source_name"] : '',
        );
        $form['version'] = array(
            '#type' => 'textfield',
            '#title' => t('ورژن'),
            '#description' => t('ورژن فرستنده کد'),
            '#default_value' => (isset($data["version"]))? $data["version"] : '',
        );
        $form['last_function'] = array(
            '#type' => 'textfield',
            '#title' => t('آخرین تابعی'),
            '#description' => t('نام دقیق آخرین تابعی که در این ورژن استفاده می شود.'),
            '#default_value' => (!empty($data["last_function"]))? $data["last_function"] : '',
        );
        $form['description'] = array(
            '#type' => 'textarea',
            '#title' => t('توضیحات'),
            '#description' => t('توضیح برای داکیمومنت کردن'),
            '#default_value' => (!empty($data["description"]))? $data["description"] : '',
        );

        $form['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Save')
        );

        return $form;
    } catch (Exception $e) {
        echo 'Caught exception: ',  $e->getMessage(), "\n";
    }
}
function add_api_version_form_validate($from, &$form_state){
    try{
        if(empty($form_state['values']['url']) && strlen($form_state['values']['url']) == 0) form_set_error('url', t('مسیر اجباری است'));
        if(empty($form_state['values']['method']) && strlen($form_state['values']['method']) == 0) form_set_error('method', t('متود اجباری است'));
        if(empty($form_state['values']['source']) && strlen($form_state['values']['source']) == 0) form_set_error('source', t('نام منبع اجباری است'));
        if(empty($form_state['values']['version']) && strlen($form_state['values']['version']) == 0) form_set_error('version', t('ورژن اجباری است'));
        if(empty($form_state['values']['last_function']) && strlen($form_state['values']['last_function']) == 0) form_set_error('last_function', t('نام تابع اجباری است'));
    }
    catch (Exception $e) {
        drupal_set_message($e->getMessage() , 'error');
        watchdog('Submit api code version failed', $e->getMessage(), WATCHDOG_CRITICAL);
    }
}
function add_api_version_form_submit($from, &$form_state){
    try{
        db_merge('api_code_version')
            ->key(array('id' => $form_state["values"]["id"]))
            ->fields(array(
                'url' => $form_state["values"]["url"] ,
                'method' => $form_state["values"]["method"] ,
                'source_name' => $form_state["values"]["source"] ,
                'version' => $form_state["values"]["version"] ,
                'last_function' => $form_state["values"]["last_function"] ,
                'description' => $form_state["values"]["description"] ,
                'created' => time()
            ))
            ->execute();

        drupal_set_message('تغییرات با موفقیت ذخیره شد.');
    } catch (Exception $e) {
        drupal_set_message($e->getMessage() , 'error');
        watchdog('Submit api code version failed', $e->getMessage(), WATCHDOG_CRITICAL);
    }
}
function api_version_delete($id){

    $deleted = db_delete('api_code_version')
        ->condition('id', $id)
        ->execute();

    drupal_goto('admin/structure/services/apiversion');
}
/************************/
