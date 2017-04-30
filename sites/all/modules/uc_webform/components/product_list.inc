<?php

/**
 * @file
 * Webform module product_list component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_product_list() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'email' => 1,
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
      'products' => NULL,
      'multiple' => NULL,
      'order' => NULL,
    ),
  );
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_product_list() {
  return array(
    'uc_webform_display_product_list' => array(
      'render element' => 'element',
      'file' => 'components/product_list.inc',
      'path' => drupal_get_path('module', 'uc_webform'),
    ),
    'uc_webform_render_product_list' => array(
      'render element' => 'element',
      'file' => 'components/product_list.inc',
      'path' => drupal_get_path('module', 'uc_webform'),
    ),
  );
}

/**
 * Theme function for when a product is displayed in a webform submission.
 */
function theme_uc_webform_display_product_list($variables) {
  $element = $variables['element'];
  $output = '';
  // TODO: Should this theme uc_webform_display_product_list be declared in
  // hook_theme()?
  if (!empty($element['#value'])) {
    $output = (count($element['#value']) > 1) ? theme('item_list', array('items' => $element['#value'])) : $element['#value'][0];
  }
  return $output;
}

/**
 * Theme function for a product when it is rendered as a part of a list.
 */
function theme_uc_webform_render_product_list($products) {
  // TODO: Should this theme uc_webform_render_product_list be declared in
  // hook_theme()?
  $output = array();
  foreach ($products as $key => $product) {
    if (is_array($product) && !empty($product)) {
      $output[$key] = '<span>' . $product['title'] . ', ' . t('Price:') . ' ' . $product['price'] . '</span>';
    }
  }

  return $output;
}

/**
 * Generate the form for editing a component.
 */
function _webform_edit_product_list($component) {
  $products = array();
  $form = array();
  $product_types = uc_product_types();

  // Limit selection to only those products that do *not* contain attributes.
  $attrib_query = db_select('uc_product_attributes', 'pa')
    ->fields('pa', array('nid'));

  $query = db_select('node', 'n')
    ->fields('n', array('nid', 'title'))
    ->condition('n.nid', $attrib_query, 'NOT IN')
    ->condition('n.status', 1, '=');
  // JOIN node with product.
  $query->join('uc_products', 'p', 'n.nid = p.nid');
  $query->addField('p', 'model');

  $query->orderBy('n.title');

  foreach ($query->execute() as $product) {
    $products[$product->nid . '_' . check_plain($product->model)] = check_plain($product->title);
  }

  // Most options are stored in the "extra" array, which stores any settings
  // unique to a particular component type.
  $form['extra']['products'] = array(
    '#type' => 'select',
    '#title' => t('Products'),
    '#default_value' => $component['extra']['products'],
    '#multiple' => TRUE,
    '#description' => t('Please select your products. Only products without attributes are displayed.'),
    '#weight' => -3,
    '#size' => 20,
    '#required' => TRUE,
    '#options' => $products,
  );
  $form['extra']['multiple'] = array(
    '#type' => 'checkbox',
    '#title' => t('Multiple'),
    '#default_value' => $component['extra']['multiple'],
    '#description' => t('Check this option if the user is allowed to select multiple products.'),
    '#weight' => -2,
  );
  $form['extra']['order'] = array(
    '#type' => 'radios',
    '#title' => t('Product Order'),
    '#default_value' => $component['extra']['order'],
    '#multiple' => TRUE,
    '#description' => t('Please select the order in which the products will be displayed.'),
    '#weight' => -3,
    '#size' => 20,
    '#required' => TRUE,
    '#options' => array(
      'order_by_price_asc' => t('Price (ascending)'),
      'order_by_price_desc' => t('Price (descending)'),
      'order_by_title_asc' => t('Title (ascending)'),
      'order_by_title_desc' => t('Title (descending)'),
    ),
  );
  return $form;
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_product_list($component, $value = NULL) {
  $stock_description = "";

  foreach ($component['extra']['products'] as $val) {
    $product_info = explode('_', $val, 2);
    $node = node_load($product_info[0]);

    if (module_exists('uc_stock')) {
      $stock_level = uc_stock_level($product_info[1]);
    }
    else {
      $stock_level = FALSE;
    }

    // Check stock levels. The product is only selectable if it is in stock.
    if (($stock_level === FALSE) or (intval($stock_level) > 0)) {
      $product['title'] = check_plain($node->title);
      $money = round($node->sell_price, 2);
      // Keep trailing zeros.
      $product['price'] = sprintf("%01.2f", $money);
      $products[$val] = $product;
    }
    else {
      $stock_description .= check_plain($node->title) . ' ' . t('is out of stock.') . '<br />';
    }
  }

  // Users may choose to sort the products based on price or title.
  switch ($component['extra']['order']) {
    case 'order_by_price_asc':
      // Obtain a list of columns.
      foreach ($products as $key => $row) {
        $price[$key] = $row['price'];
      }
      // Sort the products with price ascending.
      array_multisort($price, SORT_ASC, $products);
      break;

    case 'order_by_price_desc':
      // Obtain a list of columns.
      foreach ($products as $key => $row) {
        $price[$key] = $row['price'];
      }
      // Sort the products with price descending.
      array_multisort($price, SORT_DESC, $products);
      break;

    case 'order_by_title_asc':
      // Obtain a list of columns.
      foreach ($products as $key => $row) {
        $title[$key] = $row['title'];
      }
      // Sort the products with title ascending.
      array_multisort($title, SORT_ASC, $products);
      break;

    case 'order_by_title_desc':
      // Obtain a list of columns.
      foreach ($products as $key => $row) {
        $title[$key] = $row['title'];
      }
      // Sort the products with title descending.
      array_multisort($title, SORT_DESC, $products);
      break;

  }

  // Add the currency sign back to the price.
  $currency_sign = variable_get('uc_currency_sign', '$');
  foreach ($products as $prod_key => $prod_val) {
    $products[$prod_key]['price'] = $currency_sign . $products[$prod_key]['price'];
  }
  $form_item = array();
  if ($component['extra']['multiple'] == 0) {
    $form_item = array(
      '#type' => 'radios',
      '#title' => check_plain($component['name']),
      '#title_display' => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
      '#weight' => $component['weight'],
      '#description' => $stock_description . _webform_filter_descriptions($component['extra']['description']),
      '#prefix' => '<div class="webform-component-' . $component['type'] . '" id="webform-component-' . $component['form_key'] . '">',
      '#suffix' => '</div>',
      '#pre_render' => array('webform_element_title_display'),
      '#post_render' => array('webform_element_wrapper'),
      '#required' => $component['mandatory'],
      '#options' => theme('uc_webform_render_product_list', $products),
    );
  }
  elseif ($component['extra']['multiple'] == 1) {
    $form_item = array(
      '#type' => 'checkboxes',
      '#title' => check_plain($component['name']),
      '#title_display' => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
      '#weight' => $component['weight'],
      '#description' => $stock_description . _webform_filter_descriptions($component['extra']['description']),
      '#prefix' => '<div class="webform-component-' . $component['type'] . '" id="webform-component-' . $component['form_key'] . '">',
      '#suffix' => '</div>',
      '#pre_render' => array('webform_element_title_display'),
      '#post_render' => array('webform_element_wrapper'),
      '#required' => $component['mandatory'],
      '#options' => theme('uc_webform_render_product_list', $products),
    );
  }
  if (isset($value)) {
    switch ($value[0]) {
      case 'radio_product_list':
        $form_item['#default_value'] = $value[1];
        break;

      case 'checkboxes_product_list':
        array_shift($value);
        $form_item['#default_value'] = $value;
        break;

      default:
        break;

    }
  }
  return $form_item;
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_product_list($component, $value, $format = 'html') {

  $products = array();

  if (isset($value)) {
    foreach ($value as $product) {
      if ($product == 0 || $product == 'checkboxes_product_list' || $product == 'radio_product_list') {
        continue;
      }
      else {
        $product_info = explode('_', $product, 2);
        $node = node_load($product_info[0]);
        $product_title = t('@title, SKU: @sku', array(
          '@title' => $node->title,
          '@sku' => $node->model,
        ));
        array_push($products, $product_title);
      }
    }
  }

  $element = array(
    '#title' => check_plain($component['name']),
    '#weight' => $component['weight'],
    '#theme' => 'uc_webform_display_product_list',
    '#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
    '#post_render' => array('webform_element_wrapper'),
    '#component' => $component,
    '#format' => $format,
    '#value' => $products,
  );

  return $element;
}

/**
 * Implementation of _webform_submit_component().
 */
function _webform_submit_product_list($component, $value) {
  $return = array();
  switch (gettype($value)) {
    case 'string':
      // Value came from a radio select list.
      $return[0] = 'radio_product_list';
      $return[1] = $value;
      break;

    case 'array':
      // Value came from a checkboxes select list.
      $return[0] = 'checkboxes_product_list';
      $count = 1;
      foreach ($value as $product) {
        if ($product != 0) {
          $return[$count] = $product;
          $count++;
        }
      }
      break;
  }

  return $return;
}

/**
 * Calculate and returns statistics about results for this component.
 *
 * Note that this function does not filter for completed checkouts. The
 * _uc_webform_product_list_orders() function handles those.
 */
function _webform_analysis_product_list($component, $sids = array(), $single = FALSE) {

  $rows = array();

  $query = db_select('webform_submitted_data', 'wsd');
  $query->addExpression('COUNT(data)', 'datacount');
  $query->fields('wsd', array('data'))
    ->condition('nid', $component['nid'], '=')
    ->condition('cid', $component['cid'], '=')
    ->groupBy('data');

  foreach ($query->execute() as $product) {
    $product_info = explode('_', $product->data, 2);
    $rows[] = array(
      0 => $product_info[1],
      1 => $product->datacount,
    );
  }

  return array(
    'table_rows' => $rows,
  );
}

/**
 * Return the result of a component value for display in a table.
 */
function _webform_table_product_list($component, $value) {
  $results = '';

  if (isset($value)) {
    foreach ($value as $key => $product) {
      if ($key != 0) {
        $product_info = explode('_', $product, 2);
        $results .= "$product_info[1]<br />";
      }
    }
  }

  return $results;
}

/**
 * Implements _webform_csv_headers_component().
 */
function _webform_csv_headers_product_list($component, $export_options) {
  $headers = array(
    0 => array(),
    1 => array(),
    2 => array(),
  );

  if ($component['extra']['multiple'] && $export_options['select_format'] == 'separate') {
    $headers[0][] = '';
    $headers[1][] = check_plain($component['name']);

    $count = 0;
    foreach ($component['extra']['products'] as $product) {
      if ($count != 0) {
        // Empty column per sub-field in main header.
        $headers[0][] = '';
        $headers[1][] = '';
      }
      $product_info = explode('_', $product, 2);
      $headers[2][] = $product_info[1];
      $count++;
    }
  }
  else {
    $headers[0][] = '';
    $headers[1][] = '';
    $headers[2][] = check_plain($component['name']);
  }

  return $headers;
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_data_product_list($component, $export_options, $value) {
  $return = array();

  // Checkboxes.
  if ($component['extra']['multiple']) {
    foreach ($component['extra']['products'] as $key => $product) {
      $index = array_search($product, (array) $value);
      if ($index !== FALSE) {
        if ($export_options['select_format'] == 'separate') {
          $return[] = 'X';
        }
        else {
          $return[] = $export_options['select_keys'] ? $key : $product;
        }
        unset($value[$index]);
      }
      elseif ($export_options['select_format'] == 'separate') {
        $return[] = '';
      }
    }
  }
  // Radio Buttons.
  else {
    $key = $value[1];
    if ($export_options['select_keys']) {
      $return = $key;
    }
    else {
      $return = isset($component['extra']['products'][$key]) ? $component['extra']['products'][$key] : $key;
    }
  }

  if ($component['extra']['multiple'] && $export_options['select_format'] == 'compact') {
    $return = implode(',', (array) $return);
  }

  return $return;
}
