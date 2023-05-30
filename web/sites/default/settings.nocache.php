<?php

// Disable cache
$config['system.performance']['css']['preprocess'] = false;
$config['system.performance']['js']['preprocess'] = false;

$settings['container_yamls'][] = DRUPAL_ROOT . '/sites/dev.services.yml';
$settings['container_yamls'][] = __DIR__ . '/services.local.yml';
$settings['cache']['bins']['dynamic_page_cache'] = 'cache.backend.null';
$settings['cache']['bins']['render'] = 'cache.backend.null';
$settings['cache']['bins']['page'] = 'cache.backend.null';

$config['config_split.config_split.local']['status'] = true;
$config['config_split.config_split.develop']['status'] = true;

$settings['config_exclude_modules'][] = 'devel';
$settings['config_exclude_modules'][] = 'stage_file_proxy';
