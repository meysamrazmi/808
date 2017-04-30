<?php

/**
 * @file
 * Webform module product component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_product() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'mandatory' => 0,
    'product' => NULL,
    'extra' => array(
      'width' => '',
      'unique' => 0,
      'disabled' => 0,
      'title_display' => 0,
      'description' => '',
      'attributes' => array(),
      'private' => FALSE,
      'product' => NULL,
    ),
  );
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_product() {
  return array(
    'uc_webform_product' => array(
      'render element' => 'element',
      'file' => 'components/product.inc',
      'path' => drupal_get_path('module', 'uc_webform'),
    ),
    'uc_webform_display_product' => array(
      'render element' => 'element',
      'file' => 'components/product.inc',
      'path' => drupal_get_path('module', 'uc_webform'),
    ),
    'uc_webform_render_product' => array(
      'render element' => 'element',
      'file' => 'components/product.inc',
      'path' => drupal_get_path('module', 'uc_webform'),
    ),
  );
}

/**
 * Implements _webform_edit_component().
 * http://api.lullabot.com/_webform_edit_component/7
 */
function _webform_edit_product($component) {
  $form = array();

  // Disabling the description if not wanted.
  $form['description'] = array();
  
  $form['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Default quantity'),
    '#default_value' => $component['value'],
    '#description' => t('The default quantity of product.'),
    '#size' => 5,
    '#maxlength' => 10,
    '#weight' => 0,
    '#id' => 'email-value',
  );

  // Most options are stored in the "extra" array, which stores any settings
  // unique to a particular component type.
  $form['extra']['product'] = array(
    '#type' => 'textfield',
    '#title' => t('Product'),
    // Notice: Undefined index: product in _webform_edit_product()
    '#default_value' => $component['extra']['product'],
    '#weight' => -3,
    '#size' => 60,
    '#description' => t('Please select a product. Only products that do not contain attributes will be displayed.'),
    '#autocomplete_path' => 'uc_webform/autocomplete',
  );
  $form['display']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('Width of the textfield.') . ' ' . t('Leaving blank will use the default size.'),
    '#size' => 5,
    '#maxlength' => 10,
    '#weight' => 0,
    '#parents' => array('extra', 'width'),
  );
  $form['display']['disabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disabled'),
    '#return_value' => 1,
    '#description' => t('Make this field non-editable. Useful for setting an unchangeable default value.'),
    '#weight' => 3,
    '#default_value' => $component['extra']['disabled'],
    '#parents' => array('extra', 'disabled'),
  );

  if (isset($component['extra']['width'])) {
    $form['display']['width']['#default_value'] = $component['extra']['width'];
  }

  return $form;
}

/**
 * Implements _webform_render_component().
 * http://api.lullabot.com/_webform_render_component/7
 */
function _webform_render_product($component, $value = NULL, $filter = TRUE) {
  $stock_description = "";
  $product_info = explode('_', $component['extra']['product'], 2);
  $node = node_load($product_info[0]);
  if(!$node) {
    return;
  }
  $sku = $product_info[1];
  if (module_exists('uc_stock')) {
    $stock_level = uc_stock_level($sku);
  }
  else {
    $stock_level = FALSE;
  }

  // Check stock levels. The product is only selectable if it is in stock.
  if (($stock_level === FALSE) or (intval($stock_level) > 0)) {
    // Product is available.
    $product = array(
      'title' => check_plain($node->title),
      'price' => round($node->sell_price, 2),
    );
    // TODO Please change this theme call to use an associative array for the
    // $variables parameter.
    if(isset($value)) {
      $val = isset($value[2]) ? $value[2] : $value[0];
    } else {
      $val = $component['value'];
    }
    $element = array(
      '#type' => 'textfield',
      '#title' => check_plain($component['name']),
      '#title_display' => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
      '#weight' => $component['weight'],
      '#description' => $component['extra']['description'],
      '#default_value' => check_plain($val),
      '#field_prefix' => t('Quantity:') . ' ',
      '#field_suffix' => theme('uc_webform_render_product', $product),
      '#required' => $component['mandatory'],
      '#pre_render' => array('webform_element_title_display'),
      '#disabled' => $component['extra']['disabled'],
      '#sku' => $sku,
      '#element_validate' => array('_webform_render_product_validate'),
    );
    
   // $element['#value'] = $component['value'];
    //var_dump($component);
    // This is so that products whose quantity is disabled are added to the
    // cart correctly.
    if ($component['extra']['disabled']) {
      $element['#value'] = check_plain($val);
    }
    if (isset($component['extra']['width'])) {
      $element['#size'] = $component['extra']['width'];
    }
  }
  else {
    // Product is out of stock.
    $stock_description .= check_plain($node->title) . ' ' . t('is out of stock.') . '<br />';

    $element = array(
      '#type' => 'item',
      '#title' => check_plain($component['name']),
      '#default_value' => '',
      '#value' => '',
      '#description' => $stock_description . $component['extra']['description'],
    );
  }

  // Change the 'width' option to the correct 'size' option.
  if ($component['extra']['width'] > 0) {
    $element['#size'] = $component['extra']['width'];
  }

  return $element;
}

/**
 * Validate product entry.
 */
function _webform_render_product_validate($element, &$form_state) {
  // If the user entered a value, make sure that it's a good one.
  if (!empty($element['#value'])) {
    $match = preg_match('/\A[0-9]+\Z/', $element['#value']);
    if (($match == 0) || $match == FALSE) {
      form_error($element, t('Please enter a positive number.'));
    }
  }

  // Check to see that we have enough in stock.
  if (module_exists('uc_stock')) {
    $stock = uc_stock_level($element['#sku']);
  }
  else {
    $stock = FALSE;
  }
  if (($stock !== FALSE) && ($stock < $element['#value'])) {
    $error_msg = t("Only @stock of SKU: @sku remain. Please enter a different amount.", array('@stock' => $stock, '@sku' => $element['#sku']));

    form_error($element, check_plain($error_msg));
  }
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_product($component, $value, $format = 'html') {

  $product_info = explode('_', $component['extra']['product'], 2);
  $node = node_load($product_info[0]);
  $result_info = array(t('Title: @title<br/>SKU: @sku<br/>Quantity: @quantity', array(
    '@title' => $node->title,
    '@sku' => $product_info[1],
    '@quantity' => $value[0],
  )));

  $element = array(
    '#title' => check_plain($component['name']),
    '#weight' => $component['weight'],
    '#theme' => 'uc_webform_display_product',
    '#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
    '#post_render' => array('webform_element_wrapper'),
    '#component' => $component,
    '#format' => $format,
    '#value' => $result_info,
  );

  return $element;
}

/**
 * Theme function to render an product component.
 */
function theme_uc_webform_display_product($element) {
  // TODO: Should this theme uc_webform_display_product be declared in
  // hook_theme()?
  return $element['element']['#value'][0];
}

/**
 * Theme function to render an product component when rendered in a
 * webform.
 */
function theme_uc_webform_render_product($product) {
  // TODO: Should this theme uc_webform_render_product be declared in
  // hook_theme()?
  return '<span>' . check_plain($product['title']) . ', ' . t('Price:') . ' ' . variable_get('uc_currency_sign', '$') . check_plain($product['price']) . '</span>';
}

/**
 * Implementation of _webform_submit_component().
 */
function _webform_submit_product($component, $value) {
//   $return[0] = 'product';
  if (!empty($value)) {
    // Save the nid of the product.
//     $return[1] = $component['extra']['product'];
    // Save the quantity.
    $return[0] = $value;

    return $return;
  }
  else {
    // Save the nid of the product.
//     $return[1] = $component['extra']['product'];
    // Save the quantity.
    $return[0] = 0;

    return $return;
  }
}

/**
 * Implements _webform_analysis_component().
 */
function _webform_analysis_product($component, $sids = array()) {
  $query = db_select('webform_submitted_data', 'wsd')
    ->fields('wsd', array('no', 'data'))
    ->condition('nid', $component['nid'], '=')
    ->condition('cid', $component['cid'], '=');

  $total = 0;
  foreach ($query->execute() as $result) {
    if ($result->no == 0) {
      $total += $result->data;
    }
  }
  $product_info = explode('_', $component['extra']['product'], 2);

  $product_node = node_load($product_info[0]);
  
  $rows[0] = array();
  if(isset($product_info[1])) {
    $rows[0] = array(t($product_info[1]), $total);
  }

  return array(
    'table_rows' => $rows,
  );
}

/**
 * Implements _webform_table_component().
 */
function _webform_table_product($component, $value) {
  return check_plain(empty($value[0]) ? '' : $value[0]);
}

/**
 * Implements _webform_csv_headers_component().
 */
function _webform_csv_headers_product($component, $export_options) {
  $header = array();
  $product_info = explode('_', $component['extra']['product'], 2);

  $header[0] = '';
  $header[1] = check_plain($component['name']);
  $header[2] = $product_info[1] . ' ' . t('Quantity');
  return $header;
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_data_product($component, $export_options, $value) {
  return check_plain(empty($value[0]) ? '' : $value[0]);
}
