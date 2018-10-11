<?php

/**
 * Implementation of hook_views_query_alter().
 */
function dayscript_views_query_alter(&$view, &$query) {
    if ($view->name == 'resultados_' && isset($_GET["orderby"])) {
      
      $view->query->orderby[FALSE]['direction'] = $_GET["orderby"];
  }
}

/**
 * Implementation of hook_views_pre_render().
 */
function dayscript_views_pre_render(&$view) {
  if ($view->name == 'resultados_') {
    $pagerCount = db_query("SELECT count(nid) AS total FROM {node} n WHERE n.type ='article'")->fetchField();
    $view->query->pager->current_page = isset($_GET['page']) ? $_GET['page'] : 0;
    $view->query->pager->total_items = $pagerCount;
    $view->query->pager->totla_pages = round($pagerCount/$view->query->pager->options['items_per_page']);
    $view->query->pager->update_page_info();
  }
}