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



/*
 * custom taxonomy term page
 *
 */
function taxonomy_term_page($term){
    // If there is a menu link to this term, the link becomes the last part of
    // the active trail, and the link name becomes the page title. Thus, we must
    // explicitly set the page title to be the term title.
    drupal_set_title($term->name);
    // Build breadcrumb based on the hierarchy of the term.
    $current = (object) array(
        'tid' => $term->tid,
    );
    // @todo This overrides any other possible breadcrumb and is a pure hard-coded
    //   presumption. Make this behavior configurable per vocabulary or term.
    $breadcrumb = array();
    while ($parents = taxonomy_get_parents($current->tid)) {
        $current = array_shift($parents);
        $breadcrumb[] = l($current->name, 'taxonomy/term/' . $current->tid);
    }
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb = array_reverse($breadcrumb);
    drupal_set_breadcrumb($breadcrumb);
    drupal_add_feed('taxonomy/term/' . $term->tid . '/feed', 'RSS - ' . $term->name);
    // Set the term path as the canonical URL to prevent duplicate content.
    $uri = entity_uri('taxonomy_term', $term);
    drupal_add_html_head_link(array('rel' => 'canonical', 'href' => url($uri['path'], $uri['options'])), TRUE);
    // Set the non-aliased path as a default shortlink.
    drupal_add_html_head_link(array('rel' => 'shortlink', 'href' => url($uri['path'], array_merge($uri['options'], array('alias' => TRUE)))), TRUE);

    // Normally we would call taxonomy_term_show() here, but for backwards
    // compatibility in Drupal 7 we do not want to do that (it produces different
    // data structures and HTML markup than what Drupal 7 released with). Calling
    // taxonomy_term_view() directly provides essentially the same thing, but
    // allows us to wrap the rendered term in our desired array structure.
    $build['term_heading'] = array(
        '#prefix' => '<div class="term-listing-heading">',
        '#suffix' => '</div>',
        'term' => taxonomy_term_view($term, 'full'),
    );
    if($term->vid == 28) {
        $query = db_select("taxonomy_index", "t_index");
        $query->join("node", "node", "node.nid = t_index.nid");
        $query->fields("node", array("nid", "type"));
        $query->condition("t_index.tid", $term->tid);
        $contents = $query->execute()->fetchAll();
        if (!empty($contents)) {
            $nodes = array();
            foreach ($contents as $content) {
                if (!isset($nodes[$content->type])) $nodes[$content->type] = array();
                array_push($nodes[$content->type], $content->nid);
            }
            foreach ($nodes as $type => $nids) {
                $name = db_select("node_type")->fields("node_type", array("name"))->condition("type", $type)->execute()->fetch()->name;
                $view_mode = "question";
                if (
                    strcmp($type, "gallerynew") == 0 ||
                    strcmp($type, "film") == 0 ||
                    strcmp($type, "product") == 0
                ) {
                    $view_mode = "teaser";
                }
                $nodes = node_load_multiple($nids);
                if (!isset($build[$type])) $build[$type] = array();
                $build[$type]["#prefix"] = '<div id="node_type_' . $type . '"><h2 class="title">' . $name . '</h2>';
                $build[$type]["#suffix"] = '</div>';
                $build[$type]["term"] = node_view_multiple($nodes, $view_mode);
            }
        }
        else {
            $build['no_content'] = array(
                '#prefix' => '<p>',
                '#markup' => t('There is currently no content classified with this term.'),
                '#suffix' => '</p>',
            );
        }
    }else{
        if ($nids = taxonomy_select_nodes($term->tid, TRUE, variable_get('default_nodes_main', 10))) {
            $nodes = node_load_multiple($nids);
            $build += node_view_multiple($nodes);
            $build['pager'] = array(
                '#theme' => 'pager',
                '#weight' => 5,
            );
        }
        else {
            $build['no_content'] = array(
                '#prefix' => '<p>',
                '#markup' => t('There is currently no content classified with this term.'),
                '#suffix' => '</p>',
            );
        }
    }
    return $build;
}