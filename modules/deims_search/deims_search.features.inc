<?php
/**
 * @file
 * deims_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function deims_search_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function deims_search_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function deims_search_default_search_api_index() {
  $items = array();
  $items['data_set_index'] = entity_import('search_api_index', '{
    "name" : "Data Set Index",
    "machine_name" : "data_set_index",
    "description" : "An index build especially for searching data sets.",
    "server" : "database_server",
    "item_type" : "node",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "title" : { "type" : "text", "boost" : "5.0" },
        "status" : { "type" : "boolean" },
        "author" : { "type" : "integer", "entity_type" : "user" },
        "log" : { "type" : "text", "boost" : "2.0" },
        "field_related_publications" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_keywords" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_abstract" : { "type" : "text" },
        "field_core_areas" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_related_sites" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_data_sources" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_data_set_id" : { "type" : "text", "boost" : "5.0" },
        "field_short_name" : { "type" : "text" },
        "field_maintenance" : { "type" : "text" },
        "field_project_roles" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "project_role" },
        "field_doi" : { "type" : "text", "boost" : "2.0" },
        "field_publication_date" : { "type" : "date" },
        "search_api_language" : { "type" : "string" },
        "search_api_viewed" : { "type" : "text" },
        "search_api_access_node" : { "type" : "list\\u003Cstring\\u003E" },
        "body:value" : { "type" : "text" },
        "field_date_range:value" : { "type" : "date" },
        "field_date_range:value2" : { "type" : "date" },
        "field_project_roles:field_related_person" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 1,
          "weight" : "-10",
          "settings" : { "default" : "0", "bundles" : { "data_set" : "data_set" } }
        },
        "search_api_alter_node_access" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : { "field_keywords:parents_all" : "field_keywords:parents_all" } }
        },
        "search_api_alter_add_viewed_entity" : { "status" : 1, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "log" : true,
              "field_abstract" : true,
              "field_data_set_id" : true,
              "field_short_name" : true,
              "field_maintenance" : true,
              "field_doi" : true,
              "body:value" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "log" : true,
              "field_abstract" : true,
              "field_data_set_id" : true,
              "field_short_name" : true,
              "field_maintenance" : true,
              "field_doi" : true,
              "body:value" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 1,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "log" : true,
              "field_keywords" : true,
              "field_abstract" : true,
              "field_core_areas" : true,
              "field_data_set_id" : true,
              "field_short_name" : true,
              "field_maintenance" : true,
              "field_doi" : true,
              "search_api_viewed" : true,
              "body:value" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "log" : true,
              "field_abstract" : true,
              "field_data_set_id" : true,
              "field_short_name" : true,
              "field_maintenance" : true,
              "field_doi" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function deims_search_default_search_api_server() {
  $items = array();
  $items['database_server'] = entity_import('search_api_server', '{
    "name" : "Database Server",
    "machine_name" : "database_server",
    "description" : "",
    "class" : "search_api_db_service",
    "options" : {
      "database" : "default:default",
      "min_chars" : "3",
      "indexes" : { "data_set_index" : {
          "title" : {
            "table" : "search_api_db_data_set_index_title",
            "type" : "text",
            "boost" : "5.0"
          },
          "status" : {
            "table" : "search_api_db_data_set_index_status",
            "type" : "boolean",
            "boost" : "1.0"
          },
          "author" : {
            "table" : "search_api_db_data_set_index_author",
            "type" : "integer",
            "boost" : "1.0"
          },
          "log" : {
            "table" : "search_api_db_data_set_index_log",
            "type" : "text",
            "boost" : "2.0"
          },
          "field_related_publications" : {
            "table" : "search_api_db_data_set_index_field_related_publications",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_keywords" : {
            "table" : "search_api_db_data_set_index_field_keywords",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_abstract" : {
            "table" : "search_api_db_data_set_index_field_abstract",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_core_areas" : {
            "table" : "search_api_db_data_set_index_field_core_areas",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_related_sites" : {
            "table" : "search_api_db_data_set_index_field_related_sites",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_data_sources" : {
            "table" : "search_api_db_data_set_index_field_data_sources",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_data_set_id" : {
            "table" : "search_api_db_data_set_index_field_data_set_id",
            "type" : "text",
            "boost" : "5.0"
          },
          "field_short_name" : {
            "table" : "search_api_db_data_set_index_field_short_name",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_maintenance" : {
            "table" : "search_api_db_data_set_index_field_maintenance",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_project_roles" : {
            "table" : "search_api_db_data_set_index_field_project_roles",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_doi" : {
            "table" : "search_api_db_data_set_index_field_doi",
            "type" : "text",
            "boost" : "2.0"
          },
          "field_publication_date" : {
            "table" : "search_api_db_data_set_index_field_publication_date",
            "type" : "date",
            "boost" : "1.0"
          },
          "search_api_language" : {
            "table" : "search_api_db_data_set_index_search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "search_api_viewed" : {
            "table" : "search_api_db_data_set_index_search_api_viewed",
            "type" : "text",
            "boost" : "1.0"
          },
          "search_api_access_node" : {
            "table" : "search_api_db_data_set_index_search_api_access_node",
            "type" : "list\\u003Cstring\\u003E",
            "boost" : "1.0"
          },
          "body:value" : {
            "table" : "search_api_db_data_set_index_body_value",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_project_roles:field_related_person" : {
            "table" : "search_api_db_data_set_index_field_project_roles_field_related_",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_date_range:value" : {
            "table" : "search_api_db_data_set_index_field_date_range_value",
            "type" : "date",
            "boost" : "1.0"
          },
          "field_date_range:value2" : {
            "table" : "search_api_db_data_set_index_field_date_range_value2",
            "type" : "date",
            "boost" : "1.0"
          }
        }
      }
    },
    "enabled" : "1",
    "rdf_mapping" : []
  }');
  return $items;
}
