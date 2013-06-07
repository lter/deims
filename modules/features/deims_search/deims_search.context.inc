<?php
/**
 * @file
 * deims_search.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function deims_search_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'power-search-dataset';
  $context->description = 'Context active when power-search dataset view is active';
  $context->tag = 'power-search';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'power_search:page' => 'power_search:page',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-2' => array(
          'module' => 'block',
          'delta' => '2',
          'region' => 'sidebar_second',
          'weight' => '-24',
        ),
        'facetapi-ITxEg0MfybG0KHcAPLp5FrQadV0u53Pb' => array(
          'module' => 'facetapi',
          'delta' => 'ITxEg0MfybG0KHcAPLp5FrQadV0u53Pb',
          'region' => 'sidebar_second',
          'weight' => '-23',
        ),
        'facetapi-PiBwCvHTKS098tS3l8xiXANkRgML0fgE' => array(
          'module' => 'facetapi',
          'delta' => 'PiBwCvHTKS098tS3l8xiXANkRgML0fgE',
          'region' => 'sidebar_second',
          'weight' => '-22',
        ),
        'facetapi-12vwdt60WQbSqrE5qYYbACy6Hce8TJMz' => array(
          'module' => 'facetapi',
          'delta' => '12vwdt60WQbSqrE5qYYbACy6Hce8TJMz',
          'region' => 'sidebar_second',
          'weight' => '-21',
        ),
        'facetapi-NGUoauuOFpfNjiBnrl3oqP4qorvzbAFD' => array(
          'module' => 'facetapi',
          'delta' => 'NGUoauuOFpfNjiBnrl3oqP4qorvzbAFD',
          'region' => 'sidebar_second',
          'weight' => '-20',
        ),
        'facetapi-8zXTfogsHevG8UxypJOay2cvS4LdJwav' => array(
          'module' => 'facetapi',
          'delta' => '8zXTfogsHevG8UxypJOay2cvS4LdJwav',
          'region' => 'sidebar_second',
          'weight' => '-19',
        ),
        'facetapi-wbAbqFTnaDvvopHtkM6i0C12AAQChrD0' => array(
          'module' => 'facetapi',
          'delta' => 'wbAbqFTnaDvvopHtkM6i0C12AAQChrD0',
          'region' => 'sidebar_second',
          'weight' => '-18',
        ),
        'facetapi-4QeT28EEBsdAwhY9HYXtHmVpjxPqmZq6' => array(
          'module' => 'facetapi',
          'delta' => '4QeT28EEBsdAwhY9HYXtHmVpjxPqmZq6',
          'region' => 'sidebar_second',
          'weight' => '-17',
        ),
        'facetapi-o72vHscWUXiRajmVofPLLMafGkdAw5Fj' => array(
          'module' => 'facetapi',
          'delta' => 'o72vHscWUXiRajmVofPLLMafGkdAw5Fj',
          'region' => 'sidebar_second',
          'weight' => '-16',
        ),
        'views--exp-power_search-page' => array(
          'module' => 'views',
          'delta' => '-exp-power_search-page',
          'region' => 'three_33_top',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Context active when power-search dataset view is active');
  t('power-search');
  $export['power-search-dataset'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'site-wide-context';
  $context->description = 'A context for default site-wide settings.';
  $context->tag = 'site-wide';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'superfish-1' => array(
          'module' => 'superfish',
          'delta' => '1',
          'region' => 'menu_bar',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context for default site-wide settings.');
  t('site-wide');
  $export['site-wide-context'] = $context;

  return $export;
}
