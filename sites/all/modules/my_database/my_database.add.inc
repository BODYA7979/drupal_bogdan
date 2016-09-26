<?php

/**
 * @return add record form
 */

function my_db_add_form($form, &$form_state) {
	return [
		'add_record' => [
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
			],
			'submit' => [
				'#type' => 'submit',
				'#value' => t('Add'),
			],
		],
	];
}

/**
 * Implements form_validate()
 */

function my_db_add_form_validate($form, &$form_state) {
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
 * Implements form_submit()
 */

function my_db_add_form_submit($form, &$form_state) {
	$form_state['rebuild'] = TRUE;
	
	$db_data = array();
	
	foreach($form_state['values'] as $key => $value) {
		$db_data[$key] = $value;
	}
	
	if (addRecord($db_data)) {
		drupal_set_message(t('Data successfully inserted!'), 'status');
	}
	else {
		drupal_set_message(t('Error occured! Data not inserted'), 'error');
	}
}

/**
 * helper function addRecord($data)
 * 
 * $data = array which contains {field_name} => {field_value}
 * @return (bool) status inserting to db
 * 
 */

function addRecord($data) {
	return db_insert('custom_table')->fields(array('number' => $data['number'], 'teaser' => $data['teaser'], 'text' => $data['text']))->execute();
}
