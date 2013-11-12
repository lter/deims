<?php
/**
 * @file
 * deims_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function deims_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'biblio_authors_to_people';
  $view->description = 'Views for showing and administrating relationships between biblio authors and the people content type.';
  $view->tag = 'default';
  $view->base_table = 'biblio_contributor_data';
  $view->human_name = 'Biblio Authors to People';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Biblio Authors to People';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'cid' => 'cid',
    'name' => 'name',
    'prefix' => 'name',
    'suffix' => 'name',
    'field_name' => 'field_name',
    'field_email' => 'field_email',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'cid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'name' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'prefix' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'suffix' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
  );
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_associated_biblio_author_node']['id'] = 'reverse_field_associated_biblio_author_node';
  $handler->display->display_options['relationships']['reverse_field_associated_biblio_author_node']['table'] = 'biblio_contributor_data';
  $handler->display->display_options['relationships']['reverse_field_associated_biblio_author_node']['field'] = 'reverse_field_associated_biblio_author_node';
  /* Field: Biblio: Author id */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'biblio_contributor_data';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  /* Field: Biblio: Author full name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'biblio_contributor_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  /* Field: Biblio: Author preix */
  $handler->display->display_options['fields']['prefix']['id'] = 'prefix';
  $handler->display->display_options['fields']['prefix']['table'] = 'biblio_contributor_data';
  $handler->display->display_options['fields']['prefix']['field'] = 'prefix';
  $handler->display->display_options['fields']['prefix']['label'] = '';
  $handler->display->display_options['fields']['prefix']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['prefix']['hide_empty'] = TRUE;
  /* Field: Biblio: Author suffix */
  $handler->display->display_options['fields']['suffix']['id'] = 'suffix';
  $handler->display->display_options['fields']['suffix']['table'] = 'biblio_contributor_data';
  $handler->display->display_options['fields']['suffix']['field'] = 'suffix';
  $handler->display->display_options['fields']['suffix']['label'] = '';
  $handler->display->display_options['fields']['suffix']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['suffix']['hide_alter_empty'] = FALSE;
  /* Field: Content: Name */
  $handler->display->display_options['fields']['field_name']['id'] = 'field_name';
  $handler->display->display_options['fields']['field_name']['table'] = 'field_data_field_name';
  $handler->display->display_options['fields']['field_name']['field'] = 'field_name';
  $handler->display->display_options['fields']['field_name']['relationship'] = 'reverse_field_associated_biblio_author_node';
  $handler->display->display_options['fields']['field_name']['label'] = 'Person Name';
  $handler->display->display_options['fields']['field_name']['click_sort_column'] = 'title';
  $handler->display->display_options['fields']['field_name']['settings'] = array(
    'format' => 'default',
    'markup' => 0,
    'output' => 'default',
    'multiple' => 'default',
    'multiple_delimiter' => ', ',
    'multiple_and' => 'text',
    'multiple_delimiter_precedes_last' => 'never',
    'multiple_el_al_min' => '3',
    'multiple_el_al_first' => '1',
  );
  /* Field: Content: Email */
  $handler->display->display_options['fields']['field_email']['id'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['table'] = 'field_data_field_email';
  $handler->display->display_options['fields']['field_email']['field'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['relationship'] = 'reverse_field_associated_biblio_author_node';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'reverse_field_associated_biblio_author_node';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['field_person_title']['id'] = 'field_person_title';
  $handler->display->display_options['fields']['field_person_title']['table'] = 'field_data_field_person_title';
  $handler->display->display_options['fields']['field_person_title']['field'] = 'field_person_title';
  $handler->display->display_options['fields']['field_person_title']['relationship'] = 'reverse_field_associated_biblio_author_node';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'biblio-authors-to-people';
  $export['biblio_authors_to_people'] = $view;

  $view = new view();
  $view->name = 'data_set_services_icon_block';
  $view->description = 'Provides links to the Data Set XML services through their namesake icons';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Data Set Services Icon Block';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Data Set Services Icon Block';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<a href="/node/%1/eml"><img src="/profiles/deims/modules/custom/eml/eml.png" /></a>
<a href="/node/%1/bdp"><img src="/profiles/deims/modules/custom/bdp/bdp.png" /></a>
<a href="/node/%1/iso"><img src="/profiles/deims/modules/custom/iso/iso.gif" /></a>
';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'data_set' => 'data_set',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['data_set_services_icon_block'] = $view;

  $view = new view();
  $view->name = 'dataset_data_source_data_link';
  $view->description = 'Links to the data for a given dataset';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'dataset data source data link';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'dataset data source data link';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_data_sources_target_id']['id'] = 'field_data_sources_target_id';
  $handler->display->display_options['relationships']['field_data_sources_target_id']['table'] = 'field_data_field_data_sources';
  $handler->display->display_options['relationships']['field_data_sources_target_id']['field'] = 'field_data_sources_target_id';
  $handler->display->display_options['relationships']['field_data_sources_target_id']['label'] = 'Content entity referencED from field_data_sources';
  /* Field: Content: File upload */
  $handler->display->display_options['fields']['field_data_source_file']['id'] = 'field_data_source_file';
  $handler->display->display_options['fields']['field_data_source_file']['table'] = 'field_data_field_data_source_file';
  $handler->display->display_options['fields']['field_data_source_file']['field'] = 'field_data_source_file';
  $handler->display->display_options['fields']['field_data_source_file']['relationship'] = 'field_data_sources_target_id';
  $handler->display->display_options['fields']['field_data_source_file']['label'] = '';
  $handler->display->display_options['fields']['field_data_source_file']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_data_source_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_data_source_file']['type'] = 'file_download_link';
  $handler->display->display_options['fields']['field_data_source_file']['settings'] = array(
    'text' => 'Download [file:name]',
  );
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['dataset_data_source_data_link'] = $view;

  $view = new view();
  $view->name = 'directory';
  $view->description = 'Listing of all people associated with the LTER.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Directory';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'People';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_person_role' => 'field_person_role',
    'field_email' => 'field_email',
    'field_phone' => 'field_phone',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_person_role' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => 'priority-low',
    ),
    'field_email' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => 'priority-medium',
    ),
    'field_phone' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => 'priority-medium',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  /* Field: Content: Role */
  $handler->display->display_options['fields']['field_person_role']['id'] = 'field_person_role';
  $handler->display->display_options['fields']['field_person_role']['table'] = 'field_data_field_person_role';
  $handler->display->display_options['fields']['field_person_role']['field'] = 'field_person_role';
  /* Field: Content: Email */
  $handler->display->display_options['fields']['field_email']['id'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['table'] = 'field_data_field_email';
  $handler->display->display_options['fields']['field_email']['field'] = 'field_email';
  /* Field: Content: Phone */
  $handler->display->display_options['fields']['field_phone']['id'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['table'] = 'field_data_field_phone';
  $handler->display->display_options['fields']['field_phone']['field'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['type'] = 'telephone_link';
  $handler->display->display_options['fields']['field_phone']['settings'] = array(
    'title' => '',
  );
  /* Sort criterion: Content: Name (field_name:given) */
  $handler->display->display_options['sorts']['field_name_given']['id'] = 'field_name_given';
  $handler->display->display_options['sorts']['field_name_given']['table'] = 'field_data_field_name';
  $handler->display->display_options['sorts']['field_name_given']['field'] = 'field_name_given';
  $handler->display->display_options['sorts']['field_name_given']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_name_given']['expose']['label'] = 'First Name';
  /* Sort criterion: Content: Name (field_name:family) */
  $handler->display->display_options['sorts']['field_name_family']['id'] = 'field_name_family';
  $handler->display->display_options['sorts']['field_name_family']['table'] = 'field_data_field_name';
  $handler->display->display_options['sorts']['field_name_family']['field'] = 'field_name_family';
  $handler->display->display_options['sorts']['field_name_family']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_name_family']['expose']['label'] = 'Last Name';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'person' => 'person',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: List in Directory (field_list_in_directory) */
  $handler->display->display_options['filters']['field_list_in_directory_value']['id'] = 'field_list_in_directory_value';
  $handler->display->display_options['filters']['field_list_in_directory_value']['table'] = 'field_data_field_list_in_directory';
  $handler->display->display_options['filters']['field_list_in_directory_value']['field'] = 'field_list_in_directory_value';
  $handler->display->display_options['filters']['field_list_in_directory_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Content: Name */
  $handler->display->display_options['filters']['field_name']['id'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['table'] = 'field_data_field_name';
  $handler->display->display_options['filters']['field_name']['field'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_name']['expose']['operator_id'] = 'field_name_op';
  $handler->display->display_options['filters']['field_name']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['field_name']['expose']['operator'] = 'field_name_op';
  $handler->display->display_options['filters']['field_name']['expose']['identifier'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'people';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'People';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Researchers */
  $handler = $view->new_display('page', 'Researchers', 'people_researchers');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Researchers';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'person' => 'person',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: List in Directory (field_list_in_directory) */
  $handler->display->display_options['filters']['field_list_in_directory_value']['id'] = 'field_list_in_directory_value';
  $handler->display->display_options['filters']['field_list_in_directory_value']['table'] = 'field_data_field_list_in_directory';
  $handler->display->display_options['filters']['field_list_in_directory_value']['field'] = 'field_list_in_directory_value';
  $handler->display->display_options['filters']['field_list_in_directory_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Content: Role (field_person_role) */
  $handler->display->display_options['filters']['field_person_role_value']['id'] = 'field_person_role_value';
  $handler->display->display_options['filters']['field_person_role_value']['table'] = 'field_data_field_person_role';
  $handler->display->display_options['filters']['field_person_role_value']['field'] = 'field_person_role_value';
  $handler->display->display_options['filters']['field_person_role_value']['value'] = array(
    'LPI' => 'LPI',
    'COPI' => 'COPI',
  );
  /* Filter criterion: Content: Name */
  $handler->display->display_options['filters']['field_name']['id'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['table'] = 'field_data_field_name';
  $handler->display->display_options['filters']['field_name']['field'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_name']['expose']['operator_id'] = 'field_name_op';
  $handler->display->display_options['filters']['field_name']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['field_name']['expose']['operator'] = 'field_name_op';
  $handler->display->display_options['filters']['field_name']['expose']['identifier'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
    3 => 0,
  );
  $handler->display->display_options['path'] = 'people/researchers';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Researchers';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['directory'] = $view;

  $view = new view();
  $view->name = 'entity_reference_selection_project_role';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_project_role';
  $view->human_name = 'Entity reference selection: project role';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Project role: Person */
  $handler->display->display_options['fields']['field_related_person']['id'] = 'field_related_person';
  $handler->display->display_options['fields']['field_related_person']['table'] = 'field_data_field_related_person';
  $handler->display->display_options['fields']['field_related_person']['field'] = 'field_related_person';
  $handler->display->display_options['fields']['field_related_person']['label'] = '';
  $handler->display->display_options['fields']['field_related_person']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_related_person']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_related_person']['settings'] = array(
    'link' => 0,
  );
  /* Field: Project role: Role */
  $handler->display->display_options['fields']['field_project_role']['id'] = 'field_project_role';
  $handler->display->display_options['fields']['field_project_role']['table'] = 'field_data_field_project_role';
  $handler->display->display_options['fields']['field_project_role']['field'] = 'field_project_role';
  $handler->display->display_options['fields']['field_project_role']['label'] = '';
  $handler->display->display_options['fields']['field_project_role']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_project_role']['element_default_classes'] = FALSE;
  /* Sort criterion: Project role: Person (field_related_person) */
  $handler->display->display_options['sorts']['field_related_person_target_id']['id'] = 'field_related_person_target_id';
  $handler->display->display_options['sorts']['field_related_person_target_id']['table'] = 'field_data_field_related_person';
  $handler->display->display_options['sorts']['field_related_person_target_id']['field'] = 'field_related_person_target_id';
  /* Sort criterion: Project role: Role (field_project_role) */
  $handler->display->display_options['sorts']['field_project_role_value']['id'] = 'field_project_role_value';
  $handler->display->display_options['sorts']['field_project_role_value']['table'] = 'field_data_field_project_role';
  $handler->display->display_options['sorts']['field_project_role_value']['field'] = 'field_project_role_value';

  /* Display: Project roles */
  $handler = $view->new_display('entityreference', 'Project roles', 'entityreference_default');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_related_person' => 'field_related_person',
    'field_project_role' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  /* Display: Default project roles */
  $handler = $view->new_display('entityreference', 'Default project roles', 'entityreference_default_values');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_related_person' => 'field_related_person',
    'field_project_role' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Broken/missing handler */
  $handler->display->display_options['filters']['field_default_value']['id'] = 'field_default_value';
  $handler->display->display_options['filters']['field_default_value']['table'] = 'field_data_field_default';
  $handler->display->display_options['filters']['field_default_value']['field'] = 'field_default_value';
  $handler->display->display_options['filters']['field_default_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_default_value']['value'] = array(
    0 => '0',
  );
  $export['entity_reference_selection_project_role'] = $view;

  return $export;
}
