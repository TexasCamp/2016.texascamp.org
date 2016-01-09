<?php
/**
 * @file
 * Provide views data and handlers.
 */

/**
 * Implements hook_views_plugins().
 */
function md_portfolio_views_plugins() {
  return array(
    'module' => 'md_portfolio',
    'style' => array(
      'md_portfolio_mdp_plugin_style' => array(
        'title' => t('MD - Style Portfolio'),
        'path' => mdp_path . '/plugins/mdp',
        'handler' => 'MdPortfolioPluginStyle',
        'parent' => 'default',
        'theme' => 'md_portfolio_mdp_plugin_style',
        'theme path' => mdp_path . '/templates/mdp',
        'theme file' => 'theme.inc',
        'uses fields' => true,
        'uses row plugin' => true,
        'uses grouping' => FALSE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
    'row' => array(
      'md_portfolio_mdp_plugin_rows' => array(
        'title' => t('MD - Plugin Portfolio'),
        'path' => mdp_path . '/plugins/mdp',
        'handler' => 'MdPortfolioPluginRows',
        'theme' => 'md_portfolio_mdp_plugin_rows',
        'theme path' => mdp_path . '/templates/mdp',
        'theme file' => 'theme.inc',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
    'pager' => array(
      'md_load_more' => array(
        'title' => t('MD - load more page'),
        'handler' => 'md_portfolio_load_more',
        'uses options' => true,
        'parent' => 'full',
      ),
    ),
  );
}
