<?php
function sara_user($op, &$edit, &$account, $category = NULL) {
	global $user;
	if ($op == 'view'){
        $account->content['e-mail'] = array(
          '#type' => 'user_profile_category',
          '#title' => t('User e-mail adress'),
          '#weight' => -9,
        );
        $account->content['e-mail']['e-mail'] = array(
            '#type' => 'user_profile_item',
            '#title' => t('E-mail'),
            '#value' => $user->mail,
          );
    }
}

/**
 * Implements template_preprocess_html().
 */
function sara_preprocess_html(&$variables) {
  $settings = variable_get('theme_andromeda_settings', '') ? variable_get('theme_andromeda_settings', '') : array();
    
  if ($variables['is_front']) {
    $variables['classes_array'][] = 'front';
  } else {
    $variables['classes_array'][] = 'not-front';
  }
  if (!empty($variables['page']['slideshow'])) {
    $variables['classes_array'][] = 'with-slideshow';
  }
  if (!empty($variables['page']['sidebar'])) {
    $variables['classes_array'][] = 'with-sidebar';
  }
  if (!empty($settings['toggle_slogan'])) {
    $variables['classes_array'][] = 'with-slogan';
  }
  if (theme_get_setting('andromeda_show_front_page_title') && $variables['is_front']) {
    $variables['classes_array'][] = 'with-front-page-title';
  }
  if(theme_get_setting('andromeda_logo_position') == 'right') {
    $variables['classes_array'][] = 'logo-on-right';
  }
  
  //by meysam razmi to adding classes based on url alias
  $path = drupal_get_path_alias();
  $aliases = explode('/', $path);
  foreach($aliases as $alias) {
    $variables['classes_array'][] = 'page-' . drupal_clean_css_identifier($alias);
  }
  
  //adding less files based on their addresses to have a faster loading
  switch($aliases[0]){
	case 'user':
		drupal_add_css(drupal_get_path('theme', 'sara') . 'css/less/user-pages.min.css');
		break;
	case 'shop':
		drupal_add_css(drupal_get_path('theme', 'sara') . 'css/less/shop-pages.min.css');
		break;
	case 'college':
		drupal_add_css(drupal_get_path('theme', 'sara') . 'css/less/college-pages.min.css');
		break;
	case 'colleges':
		drupal_add_css(drupal_get_path('theme', 'sara') . 'css/less/college-pages.min.css');
		break;
	case 'gallery':
		drupal_add_css(drupal_get_path('theme', 'sara') . 'css/less/gallery-pages.min.css');
		break;
	case 'pedia':
		drupal_add_css(drupal_get_path('theme', 'sara') . 'css/less/pedia-pages.min.css');
		break;
	case 'moshaver':
		drupal_add_css(drupal_get_path('theme', 'sara') . 'css/less/landing-pages.min.css');
		break;
	case 'landing':
		drupal_add_css(drupal_get_path('theme', 'sara') . 'css/less/landing-pages.min.css');
		break;
	case 'question':
		drupal_add_css(drupal_get_path('theme', 'sara') . 'css/less/question-pages.min.css');
		drupal_add_css(drupal_get_path('theme', 'sara') . 'css/less/mh.min.css');
		drupal_add_js(drupal_get_path('theme', 'sara') . '/js/question-pages.min.js');
		break;
  }
  if (strpos($_SERVER['HTTP_USER_AGENT'], 'MSIE') || strpos($_SERVER['HTTP_USER_AGENT'], 'Trident/7')){
	  drupal_add_css(drupal_get_path('theme', 'sara') . '/less/ie.css.less');
  }

  //by meysam razmi to adding classes based on logged in user
  global $user;
    if(isset($user)){
		$variables['classes_array'][] = 'uid-'. drupal_clean_css_identifier($user->uid);
	}else{
		$variables['classes_array'][] = 'uid-0';
	}
    $roles = explode('/', implode($user->roles));
	foreach($user->roles as $role) {
		$variables['classes_array'][] = 'role-'. drupal_clean_css_identifier($role);
	}
	
 	if(arg(0) == 'node' && is_numeric(arg(1))){
		$node = node_load(arg(1));
		if(in_array($node->type, array('article', 'podcast', 'blog', 'page', 'publication', 'education', 'designteam'))){
			$variables['classes_array'][] = 'default-page';
			if(in_array($node->type, array('publication', 'education', 'designteam'))){
				$variables['classes_array'][] = 'points-needed';
			}
		}
		//adding class to the body based on node field  
		if(isset($node->field_body_classes['und'][0])){
			$variables['classes_array'][] = $node->field_body_classes['und'][0]['value'];
		}
	}

	
	if($aliases[0] == 'question' && isset($aliases[1]) && is_numeric($aliases[1])){
		$node = node_load($aliases[1]);
		drupal_add_js(array('asker' => $node->uid), 'setting');
		if($node->status == 0){
			drupal_add_js(array('status' => 'not-published'), 'setting');
		}
	}
}

/**
 * Implements template_preprocess_block().
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function sara_preprocess_block(&$variables, $hook) {
  // Classes describing the position of the block within the region.
  if ($variables['block_id'] == 1) {
    $variables['classes_array'][] = 'first';
  }
  // The last_in_region property is set in zen_page_alter().
  if (isset($variables['block']->last_in_region)) {
    $variables['classes_array'][] = 'last';
  }
  $variables['classes_array'][] = $variables['block_zebra'];

  $variables['title_attributes_array']['class'][] = 'block-title';
}

/**
 * Implements template_preprocess_node().
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered.
 */
function sara_preprocess_node(&$variables) {
  global $user;
  $node = $variables['node'];
  // fix teaser for all nodes
  if ($variables['elements']['#view_mode'] == 'teaser') {
    $variables['theme_hook_suggestions'] = array('node__teaser', 'node__teaser__'.$node->type);
  } else {
    $nodes = db_select('node','n')->extend('PagerDefault')->extend('TableSort')->fields('n', array())->limit(5)->condition('type', $node->type)->condition('nid', $node->nid, '!=')->orderBy('RAND()')->execute()->fetchAll();
    $variables['relative_nodes'] = false;
    foreach ($nodes as $key => $n) {
      $variables['relative_nodes'][] = array('title' => $n->title, 'href'=> 'node/'.$n->nid);
    }
  }
  
  if($node->type == 'event') {
    $count = db_select('m_buyed_nodes','e')->fields('e', array('id'))->condition('uid', $user->uid)->condition('nid', $node->nid)->execute()->rowCount();
    $variables['available_count'] = $node->field_count['und'][0]['value'] - $count;

    $is_buyed = db_select('m_buyed_nodes','e')
        ->fields('e', array())
        ->condition('nid', $node->nid)
        ->condition('uid', $user->uid)
        ->execute()->fetch();
    if($is_buyed)
      $variables['buyed_value'] = $is_buyed->value;
    else
      $variables['buyed_value'] = -1;
  }
  else if($variables['elements']['#view_mode'] != 'teaser' && $node->type == 'education') {
    $is_buyed = db_select('m_buyed_nodes','e')->fields('e', array())->condition('uid', $user->uid)->condition('nid', $node->nid)->execute()->fetch();
    $variables['buyed_value'] = $is_buyed;
    $node->buyed_value = $is_buyed;
    $variables['edu_form'] = drupal_get_form('edu_form', $node);
  }
	//todo: make this section based on site setting
	//for vip discount
	if($node->type == 'college'){
		$variables['classes_array'][] = 'apply-vip-discount';
	}
	else if(($node->type == 'product' || $node->type == 'product_kit') && in_array_r('2441', $node->field_backend)){ // 2441 is for "پکیج های s1 تا s30 "
		$variables['classes_array'][] = 'apply-vip-discount';
	}

  $variables['date'] = '<time>'.format_date($node->created, 'custom', 'j F Y').'</time>';
    $variables['author_about_me'] = '';
    $profile = profile2_load_by_user($node->uid);
    if (isset($profile['main']->field_about_me['und'][0])) {
        $variables['author_about_me'] = $profile['main']->field_about_me['und'][0]['value'];
    } 

  // Display post information only on certain node types.
  if (variable_get('node_submitted_' . $node->type, TRUE)) {
    $bub = "<span class='bubble'>•</span>";

    $txt = "$bub by !username $bub !datetime $bub !comments";
    if($node->type == 'projectnew')
      $txt = "$bub owner !username $bub !datetime $bub !comments";
    if($node->type == 'publication')
      $txt = "$bub !datetime $bub !comments";

    $variables['display_submitted'] = TRUE;
    $variables['submitted'] = t($txt, array('!username' => $variables['name'], 
            '!datetime' => $variables['date'], 
            '!comments' => l(format_comment_count($node->comment_count, $node->type == 'projectnew'), 'node/'.$variables['nid'], array('fragment' => 'comments', 'attributes'=> array('class' => array("offers-link"))))));

    $variables['user_picture'] = theme_get_setting('toggle_node_user_picture') ? theme('user_picture', array('account' => $node)) : '';
  }
  else {
    $variables['display_submitted'] = FALSE;
    $variables['submitted'] = '';
    $variables['user_picture'] = '';
  }

   // if there is an audio file available
  if (isset($node->field_episode['und'][0]['fid']) || isset($node->field_episode_remote['und'][0]['value'])) {
    if(isset($node->field_episode['und'][0]['fid'])) {
    // field_audio stores the fid - load the file object
      $audio_file = file_load($node->field_episode['und'][0]['fid']);
      $url = file_create_url($audio_file->uri);
    } else {
      $url = $node->field_episode_remote['und'][0]['value'];
    }
    // set up the attributes to be sent to theme_mediaelement_audio()
    $audio_attrs = array(
      'src' => $url,
      'width' => '400px',
      'download_link' => '',
    );

    // create the HTML to insert in the template file using theme_mediaelement_audio()
    $variables['audio_player'] = theme('mediaelement_audio', array('attributes' => $audio_attrs, 'settings' => array()));
  }

  // global points
  if (isset($node->field_point_needed['und'][0])) {
  //خط پایین برای این است که تو پیغام خطایی که نمایش میخواهد بدهد مبلغ را نشان دهد
    $variables['point_needed'] = $node->field_point_needed['und'][0]['value'];
  
	if($node->field_point_needed['und'][0]['value'] > 0){
      $sql = "SELECT * FROM {m_buyed_nodes} WHERE uid = :uid AND nid = :id";
      if( $row = db_query($sql, array(':id' => $node->nid, ':uid' => $user->uid ))->fetch()){//if the result of this query is 1  then the value of is_content_available is true else show the teaser mode
        $variables['is_content_available'] = array(
          'value' => true,
          'message' => '',
          );
		  $variables['is_content_available_vip'] = array(
          'value' => true,
          'message' => '',
          );
      } else {
        if ($variables['elements']['#view_mode'] != 'teaser') {
          $variables['theme_hook_suggestions'] = array('node__needpay');
        }
        $variables['is_content_available'] = array(
          'value' => false,
          'message' => 'برای مشاهده کامل این محتوا می بایست مبلغ مورد نیاز را از اعتبار خود پرداخت کنید',
          );
		  $variables['is_content_available_vip'] = array(
          'value' => false,
          'message' => 'برای مشاهده کامل این محتوا می بایست مبلغ مورد نیاز را از اعتبار خود پرداخت کنید',
          );
      }
    }
  }

  if (isset($node->field_podcast_headers['und'])) {
    foreach ($node->field_podcast_headers['und'] as $key => $value) {
      $variables['podcast_headers'][] = array(
        'data' => $value['value']
        );
    }
  }

  switch ($variables['type']) {
    case 'blog' :
      if (array_key_exists('field_blog_picture', $variables['content'])) {
        $variables['classes_array'][] = 'node-blog-has-picture';
      }
      $variables['title_classes'] = 'node-title';
      break;
  }
}

/**
 * Implementation of hook_page_alter()
 */
function sara_page_alter(&$page) {
  //disabling advagg on specific pages to prevent js error
  $path = drupal_get_path_alias();
  $aliases = explode('/', $path);
  if ((isset($aliases[0]) && $aliases[0] == '808calendar') || (isset($aliases[2]) && $aliases[2] == 'take') ) {//
    $GLOBALS['conf']['advagg_enabled'] = FALSE;
    $GLOBALS['conf']['preprocess_css'] = FALSE;
    $GLOBALS['conf']['preprocess_js'] = FALSE;
  }
}

/**
 * Implements template_preprocess_page().
 */
function sara_preprocess_page(&$variables) {
  global $user;
  $variables['user_points'] = userpoints_get_current_points($user->uid, 'all');

  // Get the entire main menu tree
  $main_menu_tree = menu_tree_all_data('main-menu');

  // Add the rendered output to the $main_menu_expanded variable
  $variables['main_menu_expanded'] = menu_tree_output($main_menu_tree);

  if (!$GLOBALS['user']->uid) {
    $user_links = array(
      'links' => array(
        'login' => array(
          'title' => t('Login'),
          'href' => 'user/login',
        ),
        'register' => array(
          'title' => t('Register'),
          'href' => 'user/register',
        ),
      ),
    );
  }
  else {
    $user_links = array(
      'links' => array(
        'account' => array(
          'title' => t('My account'),
          'href' => 'user/' . $GLOBALS['user']->uid,
        ),
        'logout' => array(
          'title' => t('Logout'),
          'href' => 'user/logout',
        ),
      ),
    );
  }
  $variables['user_links'] = theme('links', $user_links);
  
  $variables['classes_array'][] = 'wrapper-body';
  
}

function sara_form_alter(&$form, $form_state, $form_id) {
  if ($form_id == "comment_node_projectnew_form" || $form_id == "projectnew_node_form") {
    $form['actions']['submit']['#validate'][] = '_sara_projectnew_comment_form_validate';
  }
}


function _sara_projectnew_comment_form_validate($form, &$form_state) {
  global $user;
  if (form_get_errors()) return;

  $price = ($form['#form_id'] == 'projectnew_node_form')?variable_get('saze808_node', 10000):variable_get('saze808_comment', 10000);
  $points = userpoints_get_current_points($user->uid, 'all');

  if($price > $points)
    form_set_error('', t("You haven't enough point in your account, please charge your account."));
  else {
    // decrese user point and submit comment
    $params = array(
        'uid' => $user->uid,
        'points' => -$price,
        //Fc That 'operation' => t('Offer for project !title', array('!title' => $form['#node']->title)),
      );
    userpoints_userpointsapi($params);
  }
}

function sara_preprocess_comment(&$variables) {
	$path = drupal_get_path_alias();
	$aliases = explode('/', $path);
	if($aliases[0] == 'question' && isset($aliases[1]) && is_numeric($aliases[1])){
		$comment = $variables['elements']['#comment'];
		$author = $comment->uid;
		$user = user_load($author);
		if(user_has_role(10, $user) && $comment->pid == 0){
			$variables['classes_array'][] = "author-advisor";
		}
	}
}


function format_comment_count($count, $is_projectnew = 0) {
  switch ($count) {
    case 0:
      return $is_projectnew?t('No offer'):t('No Comment');
      break;
    case 1:
      return $is_projectnew?t('One offer'):t('One Comment');
      break;
    default:
      return $is_projectnew?t('!i offers', array('!i' => $count)):t('!i Comments', array('!i' => $count));
      break;
  }
}

function sara_menu_tree($variables) {
   return '<ul class="nav navbar-pills">' . $variables['tree'] . '</ul>';
}

function sara_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  
  if ($element['#below']) {
   
// Prevent dropdown functions from being added to management menu as to not affect navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    else {
     
// Add our own wrapper
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
     
// Check if this element is nested within another
      if ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] > 1)) {
        // Generate as dropdown submenu
        $element['#attributes']['class'][] = 'dropdown-submenu';
      }
      else {
        // Generate as standard dropdown
        $element['#attributes']['class'][] = 'dropdown';
        $element['#localized_options']['html'] = TRUE;
        $element['#title'] .= ' <span class="caret"></span>';
      }
     
// Set dropdown trigger element to # to prevent inadvertant page loading with submenu click
      $element['#localized_options']['attributes']['data-target'] = '#';
    }
  }
// Issue #1896674 - On primary navigation menu, class 'active' is not set on active menu item.
// @see http://drupal.org/node/1896674
if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']) || $element['#localized_options']['language']->language == $language_url->language)) {
   $element['#attributes']['class'][] = 'active';
}
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}


/**
* Process variables for user-profile.tpl.php.
*
* The $variables array contains the following arguments:
* - $account
*
* @see user-profile.tpl.php
*/
function sara_preprocess_user_profile(&$variables) {
  $account = $variables['elements']['#account'];
  foreach (element_children($variables['elements']) as $key) {
    $variables['user_profile'][$key] = $variables['elements'][$key];
  }
   $variables['user_profile']['roles'] = implode(', ', array_slice($account->roles, 1));
  field_attach_preprocess('user', $account, $variables['elements'], $variables);
}


function sara_js_alter(&$data) {
	if(drupal_is_front_page()){
		unset($data['script']);		
	}
}