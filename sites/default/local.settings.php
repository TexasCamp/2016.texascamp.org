<?php

$databases['default']['default'] = array(
  'driver' => 'mysql',
  'database' => 'texascamp',
  'username' => 'root',
  'password' => 'root',
  'host' => '127.0.0.1',
  'prefix' => '',
);

$base_url = "http://texascamp";

// Stage File Proxy
$conf['stage_file_proxy_origin'] = 'http://dev-texascamp.pantheon.io';
$conf['stage_file_proxy_use_imagecache_root'] = TRUE;

// File paths
$conf['file_public_path'] = 'sites/default/files';
$conf['file_private_path'] = 'sites/default/files/private';
$conf['file_temporary_path'] = '/tmp';

# Memcache
// $conf['cache_backends'][] = 'sites/all/modules/memcache/memcache.inc';
// $conf['cache_default_class'] = 'MemCacheDrupal';
# If building a multisite, change the value below for each site.
// $conf['memcache_key_prefix'] = 'localhost';

// Performance
$conf['preprocess_css'] = 0;
$conf['preprocess_js'] = 0;
$conf['cache'] = 0;
$conf['block_cache'] = 0;
$conf['cdn_status'] = 0;
