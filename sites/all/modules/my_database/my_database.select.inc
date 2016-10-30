<?php

/**
 * my-db/all page callback
 */

function all_records_page() {
	$records = getAllRecords();
	$header = array(t('id'), t('number'), t('teaser'), t('text'), t('Actions'));
	$rows = array();
	foreach ($records as $record) {
		$link_update = l('Update', 'my-db/update/'.$record['id']);
		$link_delete = l('Delete', 'my-db/delete/'.$record['id']);
		
		$rows[] = array($record['id'], $record['number'], $record['teaser'], $record['text'], $link_update.' '.$link_delete);
	}
	return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * @return (array) with all fields specified record selected by id
 */

function getRecordOnID($id) {
	return db_select('custom_table', 'c')->fields('c')->condition('id', $id)->execute()->fetchAssoc();
}

/**
 * @return (array) with all records from custom_table
 */

function getAllRecords() {
	$records = array();
	$query = db_select('custom_table', 'c')
		->fields('c')
		->orderBy('id', 'ASC')
		->execute();
	while($record = $query->fetchAssoc()) {
        $records[] = $record;
    }
    return $records;
}
