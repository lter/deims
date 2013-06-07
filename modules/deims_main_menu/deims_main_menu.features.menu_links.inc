<?php
/**
 * @file
 * deims_main_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function deims_main_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:<front>
  $menu_links['main-menu:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: main-menu:about/sites
  $menu_links['main-menu:about/sites'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'about/sites',
    'router_path' => 'about/sites',
    'link_title' => 'Research sites',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
    'parent_path' => 'node/32',
  );
  // Exported menu link: main-menu:contact
  $menu_links['main-menu:contact'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact Us',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
    'parent_path' => 'people',
  );
  // Exported menu link: main-menu:data
  $menu_links['main-menu:data'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'data',
    'router_path' => 'data',
    'link_title' => 'Data',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: main-menu:http://www.lternet.edu/
  $menu_links['main-menu:http://www.lternet.edu/'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'http://www.lternet.edu/',
    'router_path' => '',
    'link_title' => 'LTER Network',
    'options' => array(
      'attributes' => array(
        'title' => 'Long Term Ecological Research Network',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-45',
  );
  // Exported menu link: main-menu:node/32
  $menu_links['main-menu:node/32'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/32',
    'router_path' => 'node/%',
    'link_title' => 'About',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '1',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: main-menu:node/33
  $menu_links['main-menu:node/33'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/33',
    'router_path' => 'node/%',
    'link_title' => 'About Sub Page',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
    'parent_path' => 'node/32',
  );
  // Exported menu link: main-menu:people
  $menu_links['main-menu:people'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'people',
    'router_path' => 'people',
    'link_title' => 'People',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '1',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: main-menu:people/researchers
  $menu_links['main-menu:people/researchers'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'people/researchers',
    'router_path' => 'people/researchers',
    'link_title' => 'Researchers',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
    'parent_path' => 'people',
  );
  // Exported menu link: main-menu:power-search/data-set
  $menu_links['main-menu:power-search/data-set'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'power-search/data-set',
    'router_path' => 'power-search/data-set',
    'link_title' => 'Power Search Data Set',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About');
  t('About Sub Page');
  t('Contact Us');
  t('Data');
  t('Home');
  t('LTER Network');
  t('People');
  t('Power Search Data Set');
  t('Research sites');
  t('Researchers');


  return $menu_links;
}
