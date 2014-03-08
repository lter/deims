<?php
/**
 * @file
 * deims_person.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function deims_person_field_default_fields() {
  $fields = array();

  // Exported field: 'node-person-field_address'.
  $fields['node-person-field_address'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_address',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'addressfield',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'addressfield',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => array(
        0 => array(
          'element_key' => 'node|person|field_address|und|0',
          'thoroughfare' => '',
          'premise' => '',
          'locality' => '',
          'administrative_area' => '',
          'postal_code' => '',
          'country' => 'US',
        ),
      ),
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'above',
          'module' => 'bdp',
          'settings' => array(),
          'type' => 'addressfield_bdp_address',
          'weight' => '4',
        ),
        'default' => array(
          'label' => 'above',
          'module' => 'addressfield',
          'settings' => array(
            'format_handlers' => array(
              0 => 'address',
            ),
            'use_widget_handlers' => 1,
          ),
          'type' => 'addressfield_default',
          'weight' => '4',
        ),
        'eml' => array(
          'label' => 'hidden',
          'module' => 'eml',
          'settings' => array(),
          'type' => 'addressfield_eml_address',
          'weight' => '2',
        ),
        'full' => array(
          'label' => 'above',
          'module' => 'addressfield',
          'settings' => array(
            'format_handlers' => array(
              0 => 'address',
            ),
            'use_widget_handlers' => 1,
          ),
          'type' => 'addressfield_default',
          'weight' => '4',
        ),
        'iso' => array(
          'label' => 'above',
          'module' => 'iso',
          'settings' => array(),
          'type' => 'addressfield_iso_address',
          'weight' => '4',
        ),
      ),
      'ds_extras_field_template' => '',
      'entity_type' => 'node',
      'field_name' => 'field_address',
      'label' => 'Address',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'addressfield',
        'settings' => array(
          'available_countries' => array(),
          'format_handlers' => array(
            'address' => 'address',
            'address-hide-country' => 0,
            'organisation' => 0,
            'name-full' => 0,
            'name-oneline' => 0,
          ),
        ),
        'type' => 'addressfield_standard',
        'weight' => '4',
      ),
      'workbench_access_field' => 0,
    ),
  );

  // Exported field: 'node-person-field_associated_biblio_author'.
  $fields['node-person-field_associated_biblio_author'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_associated_biblio_author',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(
        'biblio_contributor_data' => array(
          'columns' => array(
            'target_id' => 'cid',
          ),
          'table' => 'biblio_contributor_data',
        ),
      ),
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => '0',
      'module' => 'entityreference',
      'settings' => array(
        'delete_on_parent_delete' => '',
        'handler' => 'base',
        'handler_settings' => array(
          'behaviors' => array(
            'views-select-list' => array(
              'status' => 0,
            ),
          ),
          'sort' => array(
            'type' => 'none',
          ),
          'target_bundles' => array(),
        ),
        'target_type' => 'biblio_contributor',
      ),
      'translatable' => '0',
      'type' => 'entityreference',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '11',
        ),
        'default' => array(
          'label' => 'above',
          'module' => 'token_formatters',
          'settings' => array(
            'check_access' => 1,
            'link' => '1',
            'text' => '[entity:label] r',
          ),
          'type' => 'token_formatters_entity_reference',
          'weight' => '11',
        ),
        'eml' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '10',
        ),
        'full' => array(
          'label' => 'above',
          'module' => 'entityreference',
          'settings' => array(
            'links' => 1,
            'view_mode' => '',
          ),
          'type' => 'entityreference_entity_view',
          'weight' => '8',
        ),
        'iso' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '11',
        ),
      ),
      'ds_extras_field_template' => '',
      'entity_type' => 'node',
      'field_name' => 'field_associated_biblio_author',
      'label' => 'Associated Biblio Author',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'entityreference',
        'settings' => array(
          'match_operator' => 'CONTAINS',
          'path' => '',
          'size' => '60',
        ),
        'type' => 'entityreference_autocomplete',
        'weight' => '12',
      ),
      'workbench_access_field' => 0,
    ),
  );

  // Exported field: 'node-person-field_email'.
  $fields['node-person-field_email'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_email',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'email',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'email',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'inline',
          'module' => 'bdp',
          'settings' => array(),
          'type' => 'bdp_electronicMailAddress',
          'weight' => '5',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'email',
          'settings' => array(),
          'type' => 'email_default',
          'weight' => '5',
        ),
        'eml' => array(
          'label' => 'hidden',
          'module' => 'eml',
          'settings' => array(),
          'type' => 'eml_electronicMailAddress',
          'weight' => '5',
        ),
        'full' => array(
          'label' => 'inline',
          'module' => 'email',
          'settings' => array(),
          'type' => 'email_default',
          'weight' => '5',
        ),
        'iso' => array(
          'label' => 'inline',
          'module' => 'iso',
          'settings' => array(),
          'type' => 'addressfield_iso_address',
          'weight' => '5',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_email',
      'label' => 'Email',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'email',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'email_textfield',
        'weight' => '5',
      ),
    ),
  );

  // Exported field: 'node-person-field_fax'.
  $fields['node-person-field_fax'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_fax',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'telephone',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'telephone',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'inline',
          'module' => 'bdp',
          'settings' => array(
            'phonetype' => 'facsimile',
          ),
          'type' => 'telephone_bdp_phone',
          'weight' => '7',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'telephone',
          'settings' => array(
            'title' => '',
          ),
          'type' => 'telephone_link',
          'weight' => '7',
        ),
        'eml' => array(
          'label' => 'hidden',
          'module' => 'eml',
          'settings' => array(
            'phonetype' => 'facsimile',
          ),
          'type' => 'telephone_eml_phone',
          'weight' => '4',
        ),
        'full' => array(
          'label' => 'inline',
          'module' => 'telephone',
          'settings' => array(
            'title' => '',
          ),
          'type' => 'telephone_link',
          'weight' => '7',
        ),
        'iso' => array(
          'label' => 'inline',
          'module' => 'iso',
          'settings' => array(
            'phonetype' => 'facsimile',
          ),
          'type' => 'telephone_iso_phone',
          'weight' => '7',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_fax',
      'label' => 'Fax',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'telephone',
        'settings' => array(
          'placeholder' => '',
        ),
        'type' => 'telephone_default',
        'weight' => '8',
      ),
    ),
  );

  // Exported field: 'node-person-field_list_in_directory'.
  $fields['node-person-field_list_in_directory'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_list_in_directory',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          0 => '',
          1 => '',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => '0',
      'type' => 'list_boolean',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => array(
        0 => array(
          'value' => 1,
        ),
      ),
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '9',
        ),
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '9',
        ),
        'eml' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '11',
        ),
        'full' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '9',
        ),
        'iso' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '9',
        ),
      ),
      'ds_extras_field_template' => '',
      'entity_type' => 'node',
      'field_name' => 'field_list_in_directory',
      'label' => 'List in Directory',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(
          'display_label' => 1,
        ),
        'type' => 'options_onoff',
        'weight' => '4',
      ),
    ),
  );

  // Exported field: 'node-person-field_name'.
  $fields['node-person-field_name'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_name',
      'foreign keys' => array(),
      'indexes' => array(
        'family' => array(
          0 => 'family',
        ),
        'given' => array(
          0 => 'given',
        ),
      ),
      'locked' => '0',
      'module' => 'name',
      'settings' => array(
        'allow_family_or_given' => 0,
        'autocomplete_separator' => array(
          'credentials' => ', ',
          'family' => ' -',
          'generational' => ' ',
          'given' => ' -',
          'middle' => ' -',
          'title' => ' ',
        ),
        'autocomplete_source' => array(
          'credentials' => array(),
          'family' => array(),
          'generational' => array(
            'generational' => 'generational',
          ),
          'given' => array(),
          'middle' => array(),
          'title' => array(
            'title' => 'title',
          ),
        ),
        'components' => array(
          'credentials' => 0,
          'family' => 'family',
          'generational' => 'generational',
          'given' => 'given',
          'middle' => 'middle',
          'title' => 'title',
        ),
        'generational_options' => '-- --
Jr.
Sr.
I
II
III
IV
V
VI
VII
VIII
IX
X',
        'labels' => array(
          'credentials' => 'Credentials',
          'family' => 'Last Name',
          'generational' => 'Suffix',
          'given' => 'First Name',
          'middle' => 'Middle Name or Initial',
          'title' => 'Prefix',
        ),
        'max_length' => array(
          'credentials' => '255',
          'family' => '63',
          'generational' => '15',
          'given' => '63',
          'middle' => '127',
          'title' => '31',
        ),
        'minimum_components' => array(
          'credentials' => 0,
          'family' => 'family',
          'generational' => 0,
          'given' => 'given',
          'middle' => 0,
          'title' => 0,
        ),
        'sort_options' => array(
          'generational' => 0,
          'title' => 'title',
        ),
        'title_options' => '-- --
Mr.
Mrs.
Miss
Ms.
Dr.
Prof.',
      ),
      'translatable' => '0',
      'type' => 'name',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'inline',
          'module' => 'bdp',
          'settings' => array(),
          'type' => 'name_bdp_individualName',
          'weight' => '0',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'name',
          'settings' => array(
            'format' => 'default',
            'markup' => 0,
            'multiple' => 'default',
            'multiple_and' => 'text',
            'multiple_delimiter' => ', ',
            'multiple_delimiter_precedes_last' => 'never',
            'multiple_el_al_first' => 1,
            'multiple_el_al_min' => 3,
            'output' => 'default',
          ),
          'type' => 'name_formatter',
          'weight' => '0',
        ),
        'eml' => array(
          'label' => 'hidden',
          'module' => 'eml',
          'settings' => array(),
          'type' => 'name_eml_individualName',
          'weight' => '0',
        ),
        'full' => array(
          'label' => 'inline',
          'module' => 'name',
          'settings' => array(
            'format' => 'default',
            'markup' => 0,
            'multiple' => 'default',
            'multiple_and' => 'text',
            'multiple_delimiter' => ', ',
            'multiple_delimiter_precedes_last' => 'never',
            'multiple_el_al_first' => 1,
            'multiple_el_al_min' => 3,
            'output' => 'default',
          ),
          'type' => 'name_formatter',
          'weight' => '0',
        ),
        'iso' => array(
          'label' => 'inline',
          'module' => 'iso',
          'settings' => array(),
          'type' => 'name_iso_individualName',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_name',
      'label' => 'Name',
      'required' => 1,
      'settings' => array(
        'component_css' => '',
        'component_layout' => 'default',
        'credentials_inline' => 1,
        'field_type' => array(
          'credentials' => 'text',
          'family' => 'text',
          'generational' => 'select',
          'given' => 'text',
          'middle' => 'text',
          'title' => 'select',
        ),
        'generational_field' => 'select',
        'inline_css' => array(
          'credentials' => '',
          'family' => '',
          'generational' => '',
          'given' => '',
          'middle' => '',
          'title' => '',
        ),
        'override_format' => 'default',
        'show_component_required_marker' => 0,
        'size' => array(
          'credentials' => '35',
          'family' => '20',
          'generational' => '5',
          'given' => '20',
          'middle' => '20',
          'title' => '6',
        ),
        'title_display' => array(
          'credentials' => 'description',
          'family' => 'description',
          'generational' => 'description',
          'given' => 'description',
          'middle' => 'description',
          'title' => 'description',
        ),
        'title_field' => 'select',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'name',
        'settings' => array(),
        'type' => 'name_widget',
        'weight' => '1',
      ),
    ),
  );

  // Exported field: 'node-person-field_organization'.
  $fields['node-person-field_organization'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_organization',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(
        'node' => array(
          'columns' => array(
            'target_id' => 'nid',
          ),
          'table' => 'node',
        ),
      ),
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => '0',
      'module' => 'entityreference',
      'settings' => array(
        'delete_on_parent_delete' => 'if-unused',
        'handler' => 'base',
        'handler_settings' => array(
          'behaviors' => array(
            'views-select-list' => array(
              'status' => 0,
            ),
          ),
          'sort' => array(
            'type' => 'none',
          ),
          'target_bundles' => array(
            'organization' => 'organization',
          ),
        ),
        'target_type' => 'node',
      ),
      'translatable' => '0',
      'type' => 'entityreference',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'above',
          'module' => 'bdp',
          'settings' => array(
            'element' => '',
            'multiple' => 0,
          ),
          'type' => 'entityreference_bdp_element',
          'weight' => '3',
        ),
        'default' => array(
          'label' => 'above',
          'module' => 'entityreference',
          'settings' => array(
            'link' => FALSE,
          ),
          'type' => 'entityreference_label',
          'weight' => '3',
        ),
        'eml' => array(
          'label' => 'hidden',
          'module' => 'entityreference',
          'settings' => array(
            'link' => FALSE,
          ),
          'type' => 'entityreference_label',
          'weight' => '1',
        ),
        'full' => array(
          'label' => 'above',
          'module' => 'entityreference',
          'settings' => array(
            'link' => 0,
          ),
          'type' => 'entityreference_label',
          'weight' => '3',
        ),
        'iso' => array(
          'label' => 'above',
          'module' => 'iso',
          'settings' => array(
            'element' => '',
            'multiple' => 0,
          ),
          'type' => 'entityreference_iso_element',
          'weight' => '3',
        ),
      ),
      'ds_extras_field_template' => '',
      'entity_type' => 'node',
      'field_name' => 'field_organization',
      'label' => 'Organization',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'inline_entity_form',
        'settings' => array(
          'fields' => array(),
          'type_settings' => array(
            'allow_existing' => 1,
            'clone_button' => 0,
            'delete_references' => 0,
            'match_operator' => 'CONTAINS',
          ),
        ),
        'type' => 'inline_entity_form',
        'weight' => '4',
      ),
      'workbench_access_field' => 0,
    ),
  );

  // Exported field: 'node-person-field_person_id'.
  $fields['node-person-field_person_id'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_person_id',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'number',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'number_integer',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '10',
        ),
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '10',
        ),
        'eml' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '8',
        ),
        'full' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '10',
        ),
        'iso' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '10',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_person_id',
      'label' => 'Person ID',
      'required' => 0,
      'settings' => array(
        'max' => '',
        'min' => '',
        'prefix' => '',
        'suffix' => '',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'number',
        'settings' => array(),
        'type' => 'number',
        'weight' => '11',
      ),
    ),
  );

  // Exported field: 'node-person-field_person_role'.
  $fields['node-person-field_person_role'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_person_role',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          'LPI' => 'Lead Principal Investigator',
          'COPI' => 'co-Principal Investigator',
          'FA' => 'Faculty Associate',
          'PDA' => 'Post Doctoral Associate',
          'OP' => 'Other Professional',
          'GS' => 'Graduate Student',
          'US' => 'Undergraduate Student',
          'OS' => 'Other Staff',
          'SC' => 'Secretary Clerical',
          'DA' => 'Data Manager',
          'PUB' => 'Publisher',
          'CO' => 'Contact Person',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => '0',
      'type' => 'list_text',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'inline',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => '2',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => '2',
        ),
        'eml' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '7',
        ),
        'full' => array(
          'label' => 'inline',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => '2',
        ),
        'iso' => array(
          'label' => 'inline',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => '2',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_person_role',
      'label' => 'Role',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(
          'apply_chosen' => '',
        ),
        'type' => 'options_select',
        'weight' => '3',
      ),
    ),
  );

  // Exported field: 'node-person-field_person_title'.
  $fields['node-person-field_person_title'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_person_title',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'inline',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '1',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '1',
        ),
        'eml' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '9',
        ),
        'full' => array(
          'label' => 'inline',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '1',
        ),
        'iso' => array(
          'label' => 'inline',
          'module' => 'iso',
          'settings' => array(),
          'type' => 'iso_text',
          'weight' => '1',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_person_title',
      'label' => 'Title',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '2',
      ),
    ),
  );

  // Exported field: 'node-person-field_phone'.
  $fields['node-person-field_phone'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_phone',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'telephone',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'telephone',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'inline',
          'module' => 'bdp',
          'settings' => array(
            'phonetype' => 'voice',
          ),
          'type' => 'telephone_bdp_phone',
          'weight' => '6',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'telephone',
          'settings' => array(
            'title' => '',
          ),
          'type' => 'telephone_link',
          'weight' => '6',
        ),
        'eml' => array(
          'label' => 'hidden',
          'module' => 'eml',
          'settings' => array(
            'phonetype' => 'voice',
          ),
          'type' => 'telephone_eml_phone',
          'weight' => '3',
        ),
        'full' => array(
          'label' => 'inline',
          'module' => 'telephone',
          'settings' => array(
            'title' => '',
          ),
          'type' => 'telephone_link',
          'weight' => '6',
        ),
        'iso' => array(
          'label' => 'inline',
          'module' => 'iso',
          'settings' => array(
            'phonetype' => 'voice',
          ),
          'type' => 'telephone_iso_phone',
          'weight' => '6',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_phone',
      'label' => 'Phone',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'telephone',
        'settings' => array(
          'placeholder' => '',
        ),
        'type' => 'telephone_default',
        'weight' => '7',
      ),
    ),
  );

  // Exported field: 'node-person-field_url'.
  $fields['node-person-field_url'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_url',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'url',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'url',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '12',
        ),
        'default' => array(
          'label' => 'above',
          'module' => 'url',
          'settings' => array(
            'nofollow' => FALSE,
            'trim_length' => 80,
          ),
          'type' => 'url_default',
          'weight' => '12',
        ),
        'eml' => array(
          'label' => 'hidden',
          'module' => 'eml',
          'settings' => array(),
          'type' => 'eml_onlineUrl',
          'weight' => '6',
        ),
        'full' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'iso' => array(
          'label' => 'above',
          'module' => 'iso',
          'settings' => array(),
          'type' => 'iso_onlineUrl',
          'weight' => '12',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_url',
      'label' => 'URL',
      'required' => 0,
      'settings' => array(
        'title_fetch' => 0,
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'url',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'url_external',
        'weight' => '6',
      ),
      'workbench_access_field' => 0,
    ),
  );

  // Exported field: 'node-person-field_user_account'.
  $fields['node-person-field_user_account'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_user_account',
      'foreign keys' => array(
        'users' => array(
          'columns' => array(
            'target_id' => 'uid',
          ),
          'table' => 'users',
        ),
      ),
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => '0',
      'module' => 'entityreference',
      'settings' => array(
        'handler' => 'base',
        'handler_settings' => array(
          'behaviors' => array(
            'views-select-list' => array(
              'status' => 0,
            ),
          ),
          'sort' => array(
            'type' => 'none',
          ),
          'target_bundles' => array(),
        ),
        'target_type' => 'user',
      ),
      'translatable' => '0',
      'type' => 'entityreference',
    ),
    'field_instance' => array(
      'bundle' => 'person',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'bdp' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '8',
        ),
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '8',
        ),
        'eml' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '12',
        ),
        'full' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '11',
        ),
        'iso' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '8',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_user_account',
      'label' => 'User Account',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'entityreference',
        'settings' => array(
          'match_operator' => 'CONTAINS',
          'path' => '',
          'size' => '60',
        ),
        'type' => 'entityreference_autocomplete',
        'weight' => '10',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Address');
  t('Associated Biblio Author');
  t('Email');
  t('Fax');
  t('List in Directory');
  t('Name');
  t('Organization');
  t('Person ID');
  t('Phone');
  t('Role');
  t('Title');
  t('URL');
  t('User Account');

  return $fields;
}
