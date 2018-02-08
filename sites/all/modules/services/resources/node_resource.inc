<?php

function _node_resource_definition() {
  $node_resource = array(
    'node' => array(
      'operations' => array(
        'retrieve' => array(
          'help' => 'Retrieve a node',
          'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/node_resource'),
          'callback' => '_node_resource_retrieve',
          'args' => array(
            array(
              'name' => 'nid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => 'The nid of the node to retrieve',
            ),
          ),
          'access callback' => '_node_resource_access',
          'access arguments' => array('view'),
          'access arguments append' => TRUE,
        ),
        'create' => array(
          'help' => 'Create a node',
          'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/node_resource'),
          'callback' => '_node_resource_create',
          'args' => array(
            array(
              'name' => 'node',
              'optional' => FALSE,
              'source' => 'data',
              'description' => 'The node data to create',
              'type' => 'array',
            ),
          ),
          'access callback' => '_node_resource_access',
          'access arguments' => array('create'),
          'access arguments append' => TRUE,
        ),
        'update' => array(
          'help' => 'Update a node',
          'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/node_resource'),
          'callback' => '_node_resource_update',
          'args' => array(
            array(
              'name' => 'nid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => 'The nid of the node to update',
            ),
            array(
              'name' => 'node',
              'optional' => FALSE,
              'source' => 'data',
              'description' => 'The node data to update',
              'type' => 'array',
            ),
          ),
          'access callback' => '_node_resource_access',
          'access arguments' => array('update'),
          'access arguments append' => TRUE,
        ),
        'delete' => array(
          'help' => t('Delete a node'),
          'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/node_resource'),
          'callback' => '_node_resource_delete',
          'args' => array(
            array(
              'name' => 'nid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => 'The nid of the node to delete',
            ),
          ),
          'access callback' => '_node_resource_access',
          'access arguments' => array('delete'),
          'access arguments append' => TRUE,
        ),
        'index' => array(
          'help' => 'List all nodes',
          'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/node_resource'),
          'callback' => '_node_resource_index',
          'args' => array(
            array(
              'name' => 'page',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'The zero-based index of the page to get, defaults to 0.',
              'default value' => 0,
              'source' => array('param' => 'page'),
            ),
            array(
              'name' => 'fields',
              'optional' => TRUE,
              'type' => 'string',
              'description' => 'The fields to get.',
              'default value' => '*',
              'source' => array('param' => 'fields'),
            ),
            array(
              'name' => 'parameters',
              'optional' => TRUE,
              'type' => 'array',
              'description' => 'Parameters array',
              'default value' => array(),
              'source' => array('param' => 'parameters'),
            ),
            array(
              'name' => 'pagesize',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Number of records to get per page.',
              'default value' => variable_get('services_node_index_page_size', 20),
              'source' => array('param' => 'pagesize'),
            ),
            array(
              'name' => 'options',
              'optional' => TRUE,
              'type' => 'array',
              'description' => 'Additional query options.',
              'default value' => array(
                'orderby' => array(
                  'sticky' => 'DESC',
                  'created' => 'DESC'
                )
              ),
              'source' => array('param' => 'options'),
            ),
          ),
          'access arguments' => array('access content'),
        ),
      ),
      'targeted_actions' => array(
        'attach_file' => array(
          'help' => 'Upload and attach file(s) to a node. POST multipart/form-data to node/123/attach_file',
          'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/node_resource'),
          'callback' => '_node_resource_attach_file',
          'access callback' => '_node_resource_access',
          'access arguments' => array('update'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'nid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => 'The nid of the node to attach a file to',
            ),
            array(
              'name' => 'field_name',
              'optional' => FALSE,
              'source' => array('data' => 'field_name'),
              'description' => 'The file field name',
              'type' => 'string',
            ),
            array(
              'name' => 'attach',
              'optional' => TRUE,
              'source' => array('data' => 'attach'),
              'description' => 'Attach the file(s) to the node. If FALSE, this clears ALL files attached, and attaches the files',
              'type' => 'file',
              'default value' => TRUE,
            ),
            array(
              'name' => 'field_values',
              'optional' => TRUE,
              'source' => array('data' => 'field_values'),
              'description' => 'The extra field values',
              'type' => 'array',
              'default value' => array(),
            ),
          ),
        ),
      ),
      'relationships' => array(
        'files' => array(
          'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/node_resource'),
          'help'   => 'This method returns files associated with a node.',
          'access callback' => '_node_resource_access',
          'access arguments' => array('view'),
          'access arguments append' => TRUE,
          'callback' => '_node_resource_load_node_files',
          'args'     => array(
            array(
              'name' => 'nid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => 'The nid of the node whose files we are getting',
            ),
            array(
              'name' => 'file_contents',
              'type' => 'int',
              'description'  => t('To return file contents or not.'),
              'source' => array('path' => 2),
              'optional' => TRUE,
              'default value' => TRUE,
            ),
            array(
              'name'         => 'image_styles',
              'type'         => 'int',
              'description'  => t('To return image styles or not.'),
              'source'       => array('path' => 3),
              'optional'     => TRUE,
              'default value' => FALSE,
            ),
          ),
        ),
      ),
    ),
  );
  if (module_exists('comment')) {
    $comments = array(
      'file'                    => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/node_resource'),
      'help'                    => 'This method returns the number of new comments on a given node.',
      'access callback'         => 'user_access',
      'access arguments'        => array('access comments'),
      'access arguments append' => FALSE,
      'callback'                => '_node_resource_load_node_comments',
      'args'                    => array(
        array(
          'name'         => 'nid',
          'type'         => 'int',
          'description'  => t('The node id to load comments for.'),
          'source'       => array('path' => 0),
          'optional'     => FALSE,
        ),
        array(
          'name'         => 'page',
          'type'         => 'int',
          'description'  => t('nth of comments to load.'),
          'source'       => array('param' => 'page'),
          'optional'     => TRUE,
        ),
      ),
    );
    $node_resource['node']['relationships']['comments'] =  $comments;
  }
  return $node_resource;
}

/**
 * Returns the results of a node_load() for the specified node.
 *
 * This returned node may optionally take content_permissions settings into
 * account, based on a configuration setting.
 *
 * @param $nid
 *   NID of the node we want to return.
 * @return
 *   Node object or FALSE if not found.
 *
 * @see node_load()
 */
function _node_resource_retrieve($nid) {
	
	$query = db_select('node' , 'n');
	$query->fields('n' , array('nid' , 'uid' , 'title' , 'type' , 'created' , 'changed' , 'status'));
	$query->condition('n.nid', $nid);
	$node = $query->execute()->fetch();
	$node->url = "http://civil808.com/node/".$nid;
	
	$query = db_select('field_data_field_experts' , 'e');
	$query->addField('e' , 'field_experts_tid' , 'tid');
	$query->condition('e.entity_id' , $nid);
	$tids = $query->execute()->fetchAll();
	$node->field_experts = $tids;
	
	if($node->type == "questions"){
		$query = $query = db_select('field_data_body' , 'b');
		$query->fields('b' , array('body_value'));
		$query->condition('b.entity_id', $nid);
		$node->body = $query->execute()->fetch()->body_value;

		$query = db_select('field_data_field_files' , 'feild_file');
		$query->join('file_managed' , 'file' , 'file.fid = feild_file.field_files_fid');
		$query->fields('file', array('fid' , 'filename', 'uri' ,  'filemime' , 'filesize' , 'type' , 'timestamp'));
		$query->condition('feild_file.entity_id' , $nid);
		$query->condition('feild_file.entity_type' , 'node');
		$query->condition('feild_file.bundle' , 'questions');
		$results = $query->execute()->fetchAll();
		if(!empty($results)) $node->field_files = $results;
		
		
		global $user;
		$query = db_select('flagging' , 'f')
					->condition('fid' , 3)
					->condition('entity_id' , $nid)
					->condition('uid' , $user->uid);
		$count = $query->countQuery()->execute()->fetchField();
		
		if($count > 0) $node->follow_status = 1;
		else $node->follow_status = 0;

		$query = db_select('users' , 'u');
		$query->leftJoin('file_managed' , 'f' , 'u.picture = f.fid');
		$query->fields('u' , array('uid' , 'name' , 'mail' , 'created'));
		$query->addField('f' , 'uri' , 'picture');
		$query->condition('u.uid', $node->uid);
		$author = $query->execute()->fetch();
		
		$criteria = array();
		$criteria['entity_id'] = $node->nid;
		$criteria['entity_type'] = "node";
		$criteria['function'] = "sum";
		$vote_points = votingapi_select_results($criteria);
		$vote_points = $vote_points[0]['value'];
		
		global $user;
		$query = db_select('votingapi_vote', 'v');
		$query->fields('v' , array('value'));
		$query->condition('v.entity_type' , 'node');
		$query->condition('v.entity_id' , $node->nid);
		$query->condition('v.uid' , $user->uid);
		$user_vote = $query->execute()->fetchObject();
		return ["node" => $node, "author" => $author, "vote_points" => $vote_points , "user_vote" => $user_vote->value];
	}
	if($node->type == "architect"){
		$query = $query = db_select('field_data_field_architecttext' , 't');
		$query->fields('t' , array('field_architecttext_value'));
		$query->condition('t.entity_id', $nid);
		$node->body = $query->execute()->fetch()->field_architecttext_value;

        $query = db_select('field_data_field_arch_picture' , 'p');
		$query->join('file_managed' , 'f' , 'p.field_arch_picture_fid = f.fid');
		$query->fields('f' , array('uri'));
		$query->condition('p.entity_id', $nid);
		$results = $query->execute()->fetchAll();
		$node->picture = $results;
		
		$query = db_select('field_data_field_dastebandimemar' , 'node_kind');
		$query->join('taxonomy_term_data' , 'taxonomy' , 'node_kind.field_dastebandimemar_tid = taxonomy.tid');
		$query->fields('taxonomy' , array('name'));
		$query->condition('node_kind.entity_id', $nid);
		$query->condition('node_kind.field_dastebandimemar_tid', array(2519, 2522), "NOT IN");
		$results = $query->execute()->fetchAll();
		$node->kind = $results;

		return $node;
	}
	return null;
}

/**
 * Creates a new node based on submitted values.
 *
 * Note that this function uses drupal_form_submit() to create new nodes,
 * which may require very specific formatting. The full implications of this
 * are beyond the scope of this comment block. The Googles are your friend.
 *
 * @param $node
 *   Array representing the attributes a node edit form would submit.
 * @return
 *   An associative array contained the new node's nid and, if applicable,
 *   the fully qualified URI to this resource.
 *
 * @see drupal_form_submit()
 */
function _node_resource_create($node) {
  global $user;
  // Adds backwards compatability with regression fixed in #1083242
  $node = _services_arg_value($node, 'node');
  if (!isset($node['name'])) {
    // Assign username to the node from $user created at auth step.
    if (isset($user->name)) {
      $node['name'] = $user->name;
    }
  }
  if(!isset($node['language'])) {
    $node['language'] = LANGUAGE_NONE;
  }
  // Validate the node. If there is validation error Exception will be thrown
  // so code below won't be executed.
  _node_resource_validate_type($node);
    
	$newNode= new stdClass();
	/*
	foreach($node as $key=>$value){
		$newNode->$key = $value;
	}
	*/
	
	$newNode->type  = $node['type'];
	$newNode->title  = $node['title'];
	$newNode->body['und'][0]['value'] = $node['body'];
	$newNode->body['und'][0]['summary'] = '';
	$newNode->body['und'][0]['format'] = 'full_html';
	$newNode->field_experts  = $node['field_experts'];
	$newNode->uid  = $user->uid;
	$newNode->language = 'fa';
	$newNode->status = 0;
	$newNode->comment = 2;
	$newNode = node_submit($newNode);
	node_save($newNode);
	return $newNode;
	
	/*
  // Load the required includes for drupal_form_submit
  module_load_include('inc', 'node', 'node.pages');

  $node_type = $node['type'];

  // Setup form_state
  $form_state = array();
  $form_state['values'] = $node;
  $form_state['values']['op'] = variable_get('services_node_save_button_' . $node_type . '_resource_create', t('Save'));
  $form_state['programmed_bypass_access_check'] = FALSE;
  $form_state['no_cache'] = TRUE;

  // Build a stub node object for the form in a similar way as node_add() does,
  // but always make the node author default to the current user (if the user
  // has permission to change it, $form_state['values'] will override this
  // default when the form is submitted).
  $stub_node = (object) array_intersect_key($node, array_flip(array('type', 'language')));
  $stub_node->name = $user->name;

  // Contributed modules may check the triggering element in the form state.
  // The triggering element is usually set from the browser's POST request, so
  // we'll automatically set it as the submit action from here.
  $stub_form_state = array(
    'no_cache' => TRUE,
    'build_info' => array(
      'args' => array((object) $stub_node),
    ),
  );
  $stub_form = drupal_build_form($node_type . '_node_form', $stub_form_state);
  $form_state['triggering_element'] = $stub_form['actions']['submit'];

  drupal_form_submit($node_type . '_node_form', $form_state, (object)$stub_node);

  if ($errors = form_get_errors()) {
    return services_error(implode(" ", $errors), 406, array('form_errors' => $errors));
  }
  // Fetch $nid out of $form_state
  $nid = $form_state['nid'];
  // Only add the URI for servers that support it.
  $node = array('nid' => $nid);
  */
  if ($uri = services_resource_uri(array('node', $nid))) {
    $node['uri'] = $uri;
  }
  return $node;
}

/*
 * Helper function to validate node type information.
 *
 * @param $node
 *   Array representing the attributes a node edit form would submit.
 */
function _node_resource_validate_type($node) {
  if (!isset($node['type'])) {
    return services_error(t('Missing node type'), 406);
  }
  // Wanted to return a graceful error instead of a blank nid, this should
  // allow for that.
  $types = node_type_get_types();
  $node_type = $node['type'];
  if (!isset($types[$node_type])) {
    return services_error(t('Node type @type does not exist.', array('@type' => $node_type)), 406);
  }
  $allowed_node_types = variable_get('services_allowed_create_content_types', $types);
  if (!isset($allowed_node_types[$node_type])) {
    return services_error(t("This node type @type can't be processed via services", array('@type' => $node_type)), 406);
  }
}

/**
 * Updates a new node based on submitted values.
 *
 * Note that this function uses drupal_form_submit() to create new nodes,
 * which may require very specific formatting. The full implications of this
 * are beyond the scope of this comment block. The Googles are your friend.
 *
 * @param $nid
 *   Node ID of the node we're editing.
 * @param $node
 *   Array representing the attributes a node edit form would submit.
 * @return
 *   The node's nid.
 *
 * @see drupal_form_submit()
 */
function _node_resource_update($nid, $node) {
	return $nid;
  // Adds backwards compatability with regression fixed in #1083242
  $node = _services_arg_value($node, 'node');

  $node['nid'] = $nid;

  $old_node = node_load($nid);
  if (empty($old_node->nid)) {
    return services_error(t('Node @nid not found', array('@nid' => $old_node->nid)), 404);
  }

  // If no type is provided use the existing node type.
  if (empty($node['type'])) {
    $node['type'] = $old_node->type;
  }
  elseif ($node['type'] != $old_node->type) {
    // Node types cannot be changed once they are created.
    return services_error(t('Node type cannot be changed'), 406);
  }
  
	foreach($node as $key=>$value){
		$old_node->$key = $node->$key;
	}
	return $old_node;
	node_save($old_node);
	return $old_node;
	
/*
  // Validate the node. If there is validation error Exception will be thrown
  // so code below won't be executed.
  _node_resource_validate_type($node);

  // Load the required includes for drupal_form_submit
  module_load_include('inc', 'node', 'node.pages');

  $node_type = $node['type'];
  node_object_prepare($old_node);

  // Setup form_state.
  $form_state = array();
  $form_state['values'] = $node;
  $form_state['values']['op'] = variable_get('services_node_save_button_' . $node_type . '_resource_update', t('Save'));
  $form_state['node'] = $old_node;
  $form_state['programmed_bypass_access_check'] = FALSE;

  // Contributed modules may check the triggering element in the form state.
  // The triggering element is usually set from the browser's POST request, so
  // we'll automatically set it as the submit action from here.
  $stub_form = drupal_get_form($node_type . '_node_form', (object) $old_node);
  $form_state['triggering_element'] = $stub_form['actions']['submit'];

  drupal_form_submit($node_type . '_node_form', $form_state, $old_node);

  if ($errors = form_get_errors()) {
    return services_error(implode(" ", $errors), 406, array('form_errors' => $errors));
  }

  $node = array('nid' => $nid);
  if ($uri = services_resource_uri(array('node', $nid))) {
    $node['uri'] = $uri;
  }
  return $node;*/
}

/**
 * Delete a node given its nid.
 *
 * @param int $nid
 *   Node ID of the node we're deleting.
 * @return bool
 *   Always returns true.
 */
function _node_resource_delete($nid) {
  node_delete($nid);
  return TRUE;
}

/**
 * Return an array of optionally paged nids baed on a set of criteria.
 *
 * An example request might look like
 *
 * http://domain/endpoint/node?fields=nid,vid&parameters[nid]=7&parameters[uid]=1
 *
 * This would return an array of objects with only nid and vid defined, where
 * nid = 7 and uid = 1.
 *
 * @param $page
 *   Page number of results to return (in pages of 20).
 * @param $fields
 *   The fields you want returned.
 * @param $parameters
 *   An array containing fields and values used to build a sql WHERE clause
 *   indicating items to retrieve.
 * @param $page_size
 *   Integer number of items to be returned.
 * @param $options
 *   Additional query options.
 * @return
 *   An array of node objects.
 *
 * @todo
 *   Evaluate the functionality here in general. Particularly around
 *     - Do we need fields at all? Should this just return full nodes?
 *     - Is there an easier syntax we can define which can make the urls
 *       for index requests more straightforward?
 */
function _node_resource_index($page, $fields, $parameters, $page_size, $options = array()) {
  $node_select = db_select('node', 't')
    ->addTag('node_access');

  services_resource_build_index_query($node_select, $page, $fields, $parameters, $page_size, 'node', $options);

  /*
  if (!user_access('administer nodes')) {
    $node_select->condition('status', 1);
  }*/
	
  $results = services_resource_execute_index_query($node_select);
 
  return services_resource_build_index_list($results, 'node', 'nid');
}

/**
 * Determine whether the current user can access a node resource.
 *
 * @param $op
 *   One of view, update, create, delete per node_access().
 * @param $args
 *   Resource arguments passed through from the original request.
 * @return bool
 *
 * @see node_access()
 */
function _node_resource_access($op = 'view', $args = array()) {
  // Adds backwards compatability with regression fixed in #1083242
  if (isset($args[0])) {
    $args[0] = _services_access_value($args[0], 'node');
  }

  // Make sure we have an object or this all fails, some servers can
  // mess up the types.
  if (is_array($args[0])) {
    $args[0] = (object) $args[0];
  }
  elseif (!is_array($args[0]) && !is_object($args[0])) {  //This is to determine if it is just a string happens on node/%NID
    $args[0] = (object)array('nid' => $args[0]);
  }

  if ($op != 'create' && !empty($args)) {
    $node = node_load($args[0]->nid);
  }
  elseif ($op == 'create') {
    if (isset($args[0]->type)) {
      $node = $args[0]->type;
      return node_access($op, $node);
    }
    else {
      return services_error(t('Node type is required'), 406);
    }
  }
  if (isset($node->nid) && $node->nid) {
    return node_access($op, $node);
  }
  else {
    return services_error(t('Node @nid could not be found', array('@nid' => $args[0]->nid)), 404);
  }
}

/**
 * Generates an array of base64 encoded files attached to a node
 *
 * @param $nid
 *   Number. Node ID
 * @param $include_file_contents
 *   Bool Whether or not to include the base64_encoded version of the file.
  * @param $get_image_style
 *   Bool Whether or not to provide image style paths.
 * @return
 *   Array. A list of all files from the given node
 */
function _node_resource_load_node_files($nid, $include_file_contents, $get_image_style) {
  module_load_include('inc', 'services', 'resources/file_resource');
  $node = node_load($nid);

  // Hopefully theres another way to get a nodes fields that are a file, but this was the only way I could do it.
  $fields = field_info_fields();
  $files = array();

  // Loop through all of the fields on the site
  foreach ($fields as $key => $field) {
    //if we are a field type of file
    if ($field['type'] == 'image' || $field['type'] == 'file') {
      // If this field exists on our current node..
      if (isset($node->{$field['field_name']})) {
        // If there are items in the field...
        if (isset($node->{$field['field_name']}[LANGUAGE_NONE])) {
          // Grab the items given and attach them to the array.
          $node_file_field_items = $node->{$field['field_name']}[LANGUAGE_NONE];
          foreach ($node_file_field_items as $file) {
            $files[] = _file_resource_retrieve($file['fid'], $include_file_contents, $get_image_style);
          }
        }
      }
    }
  }

  return $files;
}

/**
 * Returns the comments of a specified node.
 *
 * @param $nid
 *   Unique identifier for the node.
 * @param $count
 *   Number of comments to return.
 * @param $start
 *   Which comment to start with. If present, $start and $count are used together
 *   to create a LIMIT clause for selecting comments. This could be used to do paging.
 * @return
 *   An array of comment objects.
 */
function _node_resource_load_node_comments($nid, $page=0) {
	/*
  $query = db_select('comment', 'c');
  $query->innerJoin('node', 'n', 'n.nid = c.nid');
  $query->addTag('node_access');
  $query->fields('c', array('cid', 'uid')) //add uid by ali
    ->condition('c.nid', $nid);
  if ($count) {
    $query->range($start, $count);
  }
  $result = $query->execute()->fetchAll();
  foreach ($result as $record) {
    $cids[] = $record->cid;
    $uids[] = $record->uid; //add by ali
  }
  !empty($cids) ? $comments = comment_load_multiple($cids) : array();
	*/
	$query = db_select('comment', 'c');
	$query->leftJoin('field_data_comment_body' , 'b' , 'c.cid = b.entity_id');
	$query->fields('c', array('cid', 'pid' ,  'uid' , 'subject' , 'created' , 'changed'));
	$query->addField('b' , 'comment_body_value' , 'body');
	$query->condition('c.nid', $nid);
	$query->condition('c.pid', 0);
	$query->range($page*10, 10);
	$results = $query->execute()->fetchAll();
	if(!empty($results)){
		$cids = array();
        foreach($results as $row){
            array_push($cids , $row->cid);
        }
        $query = db_select('comment', 'c');
        $query->leftJoin('field_data_comment_body' , 'b' , 'c.cid = b.entity_id');
        $query->fields('c', array('cid', 'pid' ,  'uid' , 'subject' , 'created' , 'changed'));
        $query->addField('b' , 'comment_body_value' , 'body');
        $query->condition('c.pid', $cids, "IN");
        $results2 = $query->execute()->fetchAll();
        if(!empty($results2))
            $results = array_merge($results, $results2);

        $cids = array();
		$uids = array(); 
		$comments = array();
		foreach($results as $row){
			array_push($cids , $row->cid);
			array_push($uids , $row->uid);
            $row->field_files = array();
			$comments[$row->cid] = $row;
		}
		$uids = array_unique($uids);
		
		$query = db_select('field_data_field_files' , 'feild_file');
		$query->join('file_managed' , 'file' , 'file.fid = feild_file.field_files_fid');
		$query->fields('feild_file', array('entity_id'));
		$query->fields('file', array('fid' , 'filename', 'uri' ,  'filemime' , 'filesize' , 'type' , 'timestamp'));
		$query->condition('feild_file.entity_id' , $cids , 'IN');
		$query->condition('feild_file.entity_type' , 'comment');
		$query->condition('feild_file.bundle' , 'comment_node_questions');
		$results = $query->execute()->fetchAll();
		foreach($results as $row){
			array_push($comments[$row->entity_id]->field_files , $row);
		}
		
		$query = db_select('votingapi_vote', 'v');
		$query->fields('v' , array('entity_id', 'uid'));
		$query->condition('v.entity_type' , 'comment');
		$query->condition('v.entity_id' , $cids , 'IN');
		$query->groupBy('v.entity_id');
		$query->addExpression('sum(value)', 'vote_points');
		$result = $query->execute()->fetchAll();
		foreach($result as $vote){
			$comments[$vote->entity_id]->comment_vote_points = $vote->vote_points;
		}
		
		global $user;
		$query = db_select('votingapi_vote', 'v');
		$query->fields('v' , array('entity_id', 'value'));
		$query->condition('v.entity_type' , 'comment');
		$query->condition('v.entity_id' , $cids , 'IN');
		$query->condition('v.uid' , $user->uid);
		$result = $query->execute()->fetchAll();
		foreach($result as $vote){
			$comments[$vote->entity_id]->user_vote = $vote->value;
		}
		
		$query = db_select('users' , 'u');
		$query->leftJoin('file_managed' , 'f' , 'u.picture = f.fid');
		$query->fields('u', array('uid' , 'name' , 'mail'));
		$query->addField('f' , 'uri' , 'picture');
		$query->condition('u.uid', $uids , "IN");
		$results = $query->execute()->fetchAll();
		$authors = array();
		foreach($results as $row){
			$row->roles = array();
			$authors[$row->uid] = $row;
		}
		$query = db_select('users_roles' , 'r')
				->fields('r', array('uid' , 'rid'))
				->condition('uid', $uids , "IN")
				->execute()->fetchAll();
		foreach($query as $row){
			array_push($authors[$row->uid]->roles, $row->rid);
		}
		
		$return_authors = array();
		foreach($authors as $author){
			array_push($return_authors, $author);
		}
		 
		$return_comments = array();
		foreach($comments as $comment){
			array_push($return_comments, $comment);
		}
		return ["comments" => $return_comments, "authors" => $return_authors];
	}
	return ["comments" => array()];
}

/**
 * Attaches or overwrites file(s) to an existing node.
 *
 * Example form element used to post files to attach_file:
 * <form action="site.com/endpoint/node/1234/attach_file" method="post"
 * enctype="multipart/form-data">
 * <input name="files[anything1]" type="file" />
 * <input name="files[anything2]" type="file" />
 * <input name="field_name" type="text" value="field_image" />
 * <input name="attach" type="text" value="0" />
 *
 * The name="files[anything]" format is required to use file_save_upload().
 *
 * @param $nid
 *   Node ID of the node the file(s) is being attached to.
 * @param $field_name
 *   Machine name of the field that is attached to the node.
 * @param $attach
 *   Optional. Defaults to true. This means that files will be attached to the
 *   node, alongside existing files. If the maximum number of files have already
 *   been uploaded to this node an error is given.
 *   If false, it removes the files, and attaches the new files uploaded.
 * @return
 *   An array of files that were attached in the form:
 *   array(
 *     array(
 *       fid => N,
 *       uri => http://site.com/endpoint/file/N
 *     ),
 *     ...
 *   )
 *
 * @see file_save_upload()
 * @see file
 */
function _node_resource_attach_file($nid, $field_name, $attach, $field_values) {
  $node = node_load($nid);
  $node_type=$node->type;

  if (empty($node->{$field_name}[LANGUAGE_NONE] )) {
    $node->{$field_name}[LANGUAGE_NONE] = array();
  }

  // Validate whether field instance exists and this node type can be edited.
  _node_resource_validate_node_type_field_name('update', array($node_type, $field_name));

  $counter = 0;
  if ($attach) {
    $counter = count($node->{$field_name}[LANGUAGE_NONE]);
  }
  else {
    $node->{$field_name}[LANGUAGE_NONE] = array();
  }
	
  $options = array('attach' => $attach, 'file_count' => $counter);

  list($files, $file_objs) = _node_resource_file_save_upload($node_type, $field_name, $options);
  // Retrieve the field settings.
  $field = field_info_field($field_name);

  foreach ($file_objs as $key => $file_obj) {
    if (isset($field_values[$key])) {
      foreach ($field_values[$key] as $key => $value) {
        $file_obj->$key = $value;
      }
    }

    $node->{$field_name}[LANGUAGE_NONE][$counter] = (array)$file_obj;
    // Check the field display settings.
    if (isset($field['settings']['display_field'])) {
      // Set the display option.
      $node->{$field_name}[LANGUAGE_NONE][$counter]['display'] = $field['settings']['display_field'];
    }
    $counter++;
  }

  node_save($node);

  return $files;
}

/**
 * Services wrapper for file_save_upload.
 *
 * @see file_save_upload()
 * @see file_managed_file_save_upload()
 */
function _node_resource_file_save_upload($node_type, $field_name, $options= array() ) {
  // The field_name on node_type should be checked in the access callback.
  $instance = field_info_instance('node', $field_name, $node_type);
  $field = field_read_field($field_name);
  $cardinality = $field['cardinality'];

  // If cardinality is not unlimited check the how many 'slots' we have left.
  if (($cardinality > 0) && isset($options['file_count'])) {
    // Already uploaded files
    $file_already_uploaded_count = $options['file_count'];
    // How many files we are going to upload.
    $file_upload_count = count($_FILES['files']['name']);
           // If we add new files and not replace already uploaded.
    if (   (isset($options['attach']) && ($options['attach']) && ($file_already_uploaded_count + $file_upload_count > $cardinality))
           // If we replace existing files.
        || ((!isset($options['attach']) || !$options['attach']) && $file_upload_count > $cardinality)) {
      return services_error(t('You cannot upload so many files.'));
    }
  }

  $destination = file_field_widget_uri($field, $instance );
  if (isset($destination) && !file_prepare_directory($destination, FILE_CREATE_DIRECTORY)) {
    return services_error(t('The upload directory %directory for the file field !name could not be created or is not accessible. A newly uploaded file could not be saved in this directory as a consequence, and the upload was canceled.', array('%directory' => $destination, '!name' => $field_name)));
  }

  $validators = array(
    'file_validate_extensions' =>  (array)$instance['settings']['file_extensions'],
    'file_validate_size' => array(0 => parse_size($instance['settings']['max_filesize'])),
  );

  $files = $file_objs = array();

  foreach ($_FILES['files']['name'] as $key => $val) {

    // Let the file module handle the upload and moving.
    if (!$file = file_save_upload($key, $validators, $destination, FILE_EXISTS_RENAME) ) {
      return services_error(t('Failed to upload file. @upload', array('@upload' => $key)), 406);
    }

    if ($file->fid) {
      // Add info to the array that will be returned/encdoed to xml/json.
      $files[] = array(
        'fid' => $file->fid,
        'uri' => services_resource_uri(array('file', $file->fid)),
      );
      $file_objs[] = $file;
    }
    else {
      return services_error(t('An unknown error occurred'), 500);
    }
  }

  return array($files, $file_objs);
}

/**
 * Helper function to validate data.
 *
 * @param $op
 *   Array representing the attributes a node edit form would submit.
 * @param $args
 *   Resource arguments passed through from the original request (node_type,
 *   field_name).
 *
 * @return bool
 *   TRUE/FALSE based on access.
 */
function _node_resource_validate_node_type_field_name($op = 'create', $args = array()) {
  $node_type = $args[0];
  $field_name = $args[1];

  $temp_node= array('type' => $node_type);

  // An invalid node type throws an exception, and stops before the return below.
  _node_resource_validate_type($temp_node);

  if (!field_info_instance('node', $field_name, $node_type)) {
    return services_error(t('Field name \'@field_name\' not found on node type \'@node_type\'', array('@field_name' => $field_name, '@node_type' => $node_type)), 406);
  }

  return TRUE;
}
