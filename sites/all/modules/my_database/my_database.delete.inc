<?php

/**
 * Delete record from db
 * 
 * $id = unical id of the record
 * 
 * return (bool) state deleted record or not
 */

function deleteRecord($id) {
	return db_delete('custom_table')->condition('id', $id)->execute();
}

/**
 * my-db/delete/% page callback
 */

function delete_record_page($id) {
	if (deleteRecord($id)) {
		drupal_set_message(t('Record deleted successfully!'), 'status');
	}
	else {
		drupal_set_message(t('Error occured!'), 'error');
	}
	drupal_goto($_SERVER['HTTP_REFERER']);
}
