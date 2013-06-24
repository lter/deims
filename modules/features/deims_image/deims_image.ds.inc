<?php
/**
 * @file
 * deims_image.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function deims_image_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'file|image|default';
  $ds_layout->entity_type = 'file';
  $ds_layout->bundle = 'image';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_fluid';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_file_image_title_text',
        1 => 'file',
        2 => 'field_photo_caption',
        3 => 'field_date',
      ),
      'right' => array(
        4 => 'field_related_people',
        5 => 'field_related_site',
      ),
    ),
    'fields' => array(
      'field_file_image_title_text' => 'left',
      'file' => 'left',
      'field_photo_caption' => 'left',
      'field_date' => 'left',
      'field_related_people' => 'right',
      'field_related_site' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left' => 'div',
      'right' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
  );
  $export['file|image|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'file|image|form';
  $ds_layout->entity_type = 'file';
  $ds_layout->bundle = 'image';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_file_image_title_text',
        1 => 'field_file_image_alt_text',
        2 => 'field_photo_caption',
        3 => 'field_date',
        4 => 'field_related_people',
        5 => 'field_related_site',
        6 => 'filename',
        7 => 'preview',
      ),
      'hidden' => array(
        8 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_file_image_title_text' => 'ds_content',
      'field_file_image_alt_text' => 'ds_content',
      'field_photo_caption' => 'ds_content',
      'field_date' => 'ds_content',
      'field_related_people' => 'ds_content',
      'field_related_site' => 'ds_content',
      'filename' => 'ds_content',
      'preview' => 'ds_content',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
  );
  $export['file|image|form'] = $ds_layout;

  return $export;
}
