<?php

/**
 * @file
 * Webform module hidden component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_hidden_product() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'mandatory' => 0,
    'extra' => array(
      'width' => '',
      'unique' => 0,
      'disabled' => 0,
      'title_display' => 0,
      'description' => '',
      'attributes' => array(),
      'private' => FALSE,
      'hidden_product' => NULL,
    ),
  );
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_hidden_product() {
  return array(
    'uc_webform_display_hidden_product' => array(
      'render element' => 'element',
      'file' => 'components/hidden_product.inc',
      'path' => drupal_get_path('module', 'uc_webform'),
    ),
    '_webform_render_hidden_product' => array(
      'render element' => 'element',
      'file' => 'components/hidden_product.inc',
      'path' => drupal_get_path('module', 'uc_webform'),
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_hidden_product($component) {
  $form = array();

  $form['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Quantity'),
    '#default_value' => $component['value'],
    '#description' => t('The quantity of product.'),
    '#size' => 5,
    '#maxlength' => 10,
    '#weight' => 0,
    '#required' => TRUE,
  );
  $form['extra']['hidden_product'] = array(
    '#type' => 'textfield',
    '#title' => t('Hidden Product'),
    '#default_value' => $component['extra']['hidden_product'],
    '#weight' => -3,
    '#size' => 60,
    '#description' => t('Please select a product. Only products that do not contain attributes will be displayed.'),
    '#autocomplete_path' => 'uc_webform/autocomplete',
  );
  // Hide the description box.
  $form['extra']['description'] = array();
  // Hide the display options.
  $form['display'] = array('#type' => 'markup');

  return $form;
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_hidden_product($component, $value = NULL, $filter = TRUE) {
  $element = array(
    '#type' => 'hidden',
    '#title' => $filter ? _webform_filter_xss($component['name']) : $component['name'],
    '#default_value' => $filter ? _webform_filter_values($component['value']) : $component['value'],
    '#weight' => $component['weight'],
  );

  if (isset($value[0])) {
    $element['#default_value'] = $value[0];
  }

  return $element;
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_hidden_product($component, $value, $format = 'html') {

  $product_info = explode('_', $component['extra']['hidden_product'], 2);
  $node = node_load($product_info[0]);
  $result_info = array(t('Title: @title<br/>SKU: @sku<br/>Quantity: @quantity', array(
    '@title' => $node->title,
    '@sku' => $product_info[1],
    '@quantity' => $value[2],
  )));


  $element = array(
    '#title' => t('@name (hidden)', array('@name' => $component['name'])),
    '#weight' => $component['weight'],
    '#theme' => 'uc_webform_display_hidden_product',
    '#theme_wrappers' => $format == 'html' ? array('webform_element', 'webform_element_wrapper') : array('webform_element_text'),
    '#post_render' => array('webform_element_wrapper'),
    '#component' => $component,
    '#format' => $format,
    '#value' => $result_info,
  );

  // TODO: This check is unusual. It shows hidden fields in e-mails but not
  // when viewing in the browser unless you're an administrator. This should be
  // a more logical check. See these related issues:
  // http://drupal.org/node/313639
  // http://drupal.org/node/781786
  if ($format == 'html') {
    $element['#access'] = user_access('edit all webform submissions') || user_access('access all webform results');
  }

  return $element;
}

/**
 * Theme function to render an product component.
 */
function theme_uc_webform_display_hidden_product($element) {
  // TODO: Should this theme uc_webform_display_hidden_product be declared in
  // hook_theme()?
  return $element['element']['#value'][0];
}

/**
 * Implementation of _webform_submit_component().
 */
function _webform_submit_hidden_product($component, $value) {

  // Save the product component type.
  $return[0] = 'hidden_product';
  // Save the nid of the product.
  $return[1] = $component['extra']['hidden_product'];
  // Save the quantity.
  $return[2] = $value;

  return $return;
}

/**
 * Implements _webform_analysis_component().
 */
function _webform_analysis_hidden_product($component, $sids = array()) {
  $results = db_query("SELECT data, no FROM {webform_submitted_data} WHERE nid = :nid AND cid = :cid ", array(':nid' => $component['nid'], ':cid' => $component['cid']));

  $total = 0;
  while ($result = $results->fetchAssoc()) {
    if ($result['no'] == 2) {
      $total += $result['data'];
    }
  }
  $product_info = explode('_', $component['extra']['hidden_product'], 2);

  $product_node = node_load($product_info[0]);

  $rows[0] = array(t($product_info[1]), $total);

  return array(
    'table_rows' => $rows,
  );
}

/**
 * Implements _webform_table_component().
 */
function _webform_table_hidden_product($component, $value) {
  return check_plain(empty($value[2]) ? '' : $value[2]);
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_headers_hidden_product($component, $export_options) {
  $header = array();
  $product_info = explode('_', $component['extra']['hidden_product'], 2);

  $header[0] = '';
  $header[1] = check_plain($component['name']);
  $header[2] = $product_info[1] . ' ' . t('Quantity');
  return $header;
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_data_hidden_product($component, $export_options, $value) {
  return check_plain(empty($value[2]) ? '' : $value[2]);
}
