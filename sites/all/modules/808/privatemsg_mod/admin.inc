<?php

function administer_messages(){
	$q = db_select('pm_message','pm')->extend('PagerDefault')->extend('TableSort')->limit(50);
	$q->join('pm_index', 'thread', 'thread.mid = pm.mid AND pm.author != thread.recipient');
	$q->fields('thread', array('thread_id', 'recipient'));
	$q->fields('pm', array('author', 'subject', 'body', 'timestamp', 'mid'));
	$rows = $q->orderBy('pm.timestamp', 'DESC')->execute();
	$count = $rows->rowCount();
	$tabale_header = array(
		'#',
		t('message id'),
		t('Sender'),
		'reciver',
		t('Receiver'),
		t('Subject'),
		t('Message'),
		t('Date'),
		'threar-id',
		t('Operations')
	);
	$table_rows = array();
	$i = 0;
	foreach ($rows as $r) {
		$user = user_load($r->author);
		$recipient = user_load($r->recipient);
		if($i != 0 && $table_rows[$i-1][8] == $r->thread_id && $table_rows[$i-1][1] == $r->mid){
			$table_rows[$i-1][3] .= '<br>'. $r->recipient;
			$table_rows[$i-1][4] .= '<br>'. l($recipient->name, 'user/'.$recipient->uid);
			continue;
		}
		$table_rows[] = array(
			$count--,
			$r->mid,
			l($user->name, 'user/'.$user->uid),
			$r->recipient,
			l($recipient->name, 'user/'.$recipient->uid),
			l($r->subject,'/messages/view/'. $r->thread_id),
			nl2br($r->body),
			format_date($r->timestamp),
			$r->thread_id,
			l(t('Edit'), '/messages/edit/'. $r->thread_id .'/'. $r->mid, array('query' => array('destination' => 'admin/content/messages'))) .'<br>'. l(t('Delete'), '/messages/delete/'. $r->thread_id .'/'. $r->mid, array('query' => array('destination' => 'admin/content/messages'))),
		);
		$i++;
	}
	return theme('table', array('header' => $tabale_header, 'rows' => $table_rows)).theme('pager');	
}
