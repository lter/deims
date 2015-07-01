<?php
/**
 * @file
 * deims_taxa.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function deims_taxa_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'taxa_common_and_sci_name_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_taxa';
  $view->human_name = 'Taxa Common and Sci Name List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Taxa Common and Sci Name List';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Taxa: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_taxa';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  /* Field: Taxa: Common Name */
  $handler->display->display_options['fields']['field_taxa_common']['id'] = 'field_taxa_common';
  $handler->display->display_options['fields']['field_taxa_common']['table'] = 'field_data_field_taxa_common';
  $handler->display->display_options['fields']['field_taxa_common']['field'] = 'field_taxa_common';
  /* Field: Taxa: Scientific Name */
  $handler->display->display_options['fields']['field_taxa_scientific']['id'] = 'field_taxa_scientific';
  $handler->display->display_options['fields']['field_taxa_scientific']['table'] = 'field_data_field_taxa_scientific';
  $handler->display->display_options['fields']['field_taxa_scientific']['field'] = 'field_taxa_scientific';
  /* Sort criterion: Taxa: Common Name (field_taxa_common) */
  $handler->display->display_options['sorts']['field_taxa_common_value']['id'] = 'field_taxa_common_value';
  $handler->display->display_options['sorts']['field_taxa_common_value']['table'] = 'field_data_field_taxa_common';
  $handler->display->display_options['sorts']['field_taxa_common_value']['field'] = 'field_taxa_common_value';
  /* Sort criterion: Taxa: Scientific Name (field_taxa_scientific) */
  $handler->display->display_options['sorts']['field_taxa_scientific_value']['id'] = 'field_taxa_scientific_value';
  $handler->display->display_options['sorts']['field_taxa_scientific_value']['table'] = 'field_data_field_taxa_scientific';
  $handler->display->display_options['sorts']['field_taxa_scientific_value']['field'] = 'field_taxa_scientific_value';
  /* Filter criterion: Taxa: taxa type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_taxa';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'taxa' => 'taxa',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'field_taxa_common' => 'field_taxa_common',
    'field_taxa_scientific' => 'field_taxa_scientific',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_taxa_common' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_taxa_scientific' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'taxa-common-and-sci-name-list';

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Taxas in the entity reference for autocompletes';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_taxa_common' => 'field_taxa_common',
    'field_taxa_scientific' => 'field_taxa_scientific',
    'id' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_taxa_common' => 'field_taxa_common',
    'field_taxa_scientific' => 'field_taxa_scientific',
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxa: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_taxa';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: Taxa: Common Name */
  $handler->display->display_options['fields']['field_taxa_common']['id'] = 'field_taxa_common';
  $handler->display->display_options['fields']['field_taxa_common']['table'] = 'field_data_field_taxa_common';
  $handler->display->display_options['fields']['field_taxa_common']['field'] = 'field_taxa_common';
  /* Field: Taxa: Scientific Name */
  $handler->display->display_options['fields']['field_taxa_scientific']['id'] = 'field_taxa_scientific';
  $handler->display->display_options['fields']['field_taxa_scientific']['table'] = 'field_data_field_taxa_scientific';
  $handler->display->display_options['fields']['field_taxa_scientific']['field'] = 'field_taxa_scientific';
  $export['taxa_common_and_sci_name_list'] = $view;

  return $export;
}
