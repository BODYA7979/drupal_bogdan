<?php

/**
 * my-db/update/% title callback
 */

function update_record_title($id = '') {
	return t('Edit record with id: '.$id);
}

/**
 * my-db/update/% page callback
 */

function update_record_page($id) {
	$form = drupal_get_form('my_db_edit_form');
	return $form;
}

/**
 * @return (array) with edit record form elements
 */

function my_db_edit_form() {
	$data = getRecordOnID(arg(2));
	return [
		'number' => [
			'#type' => 'textfield',
			'#title' => t('Number'),
			'#rules' => [
				'numeric'
			],
			'#filters' => [
				'trim',
				'strip_tags',
			],
			'#required' => true,
			'#default_value' => $data['number'],
		],
		'teaser' => [
			'#type' => 'textfield',
			'#title' => t('Teaser'),
			'#rules' => [
				'alpha_numeric',
			],
			'#filter' => [
				'trim',
				'strip_tags',
			],
			'#required' => true,
			'#default_value' => $data['teaser'],
		],
		'text' => [
			'#type' => 'textarea',
			'#title' => t('Text'),
			'#rules' => [
				'alpha_numeric',
			],
			'#filter' => [
				'trim',
				'strip_tags',
			],
			'#required' => true,
			'#default_value' => $data['text'],
		],
		'id' => [
			'#type' => 'hidden',
			'#value' => $data['id'],
		],
		'submit' => [
			'#type' => 'submit',
			'#value' => t('Save'),
		],
	];
}

/**
 * edit record form validation
 */

function my_db_edit_form_validate($form, &$form_state) {
	if (!ctype_digit($form_state['values']['number'])) {
		form_set_error('number', t('Number must contain only digits'));
	}
	if (mb_strlen($form_state['values']['number']) > 10) {
		form_set_error('number', t('Number must be less than 10 chars'));
	}
	if (mb_strlen($form_state['values']['teaser'] > 150)) {
		form_set_error('teaser', t('Teaser must be less than 150 chars'));
	}
}

/**
 * edit record form submit
 */

function my_db_edit_form_submit($form, &$form_state) {
	$form_state['rebuild'] = TRUE;
	
	$db_data = array();
	
	foreach($form_state['values'] as $key => $value) {
		$db_data[$key] = $value;
	}
	
	if (updateRecord($db_data['id'], $db_data)) {
		drupal_set_message(t('Data successfully updated!'), 'status');
	}
	else {
		drupal_set_message(t('Data not changed!'), 'error');
	}
}

/**
 * this function update record
 * $id - id of the record
 * $db_data - (array) which contain key(field) => value(field_value).
 */

function updateRecord($id, $db_data) {
	return db_update('custom_table')->fields(array('number' => $db_data['number'], 'teaser' => $db_data['teaser'], 'text' => $db_data['text']))->condition('id', $id)->execute();
}
