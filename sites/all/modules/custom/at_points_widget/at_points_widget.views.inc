<?php

function at_points_widget_views_query_alter(&$view, &$query){
  if ($view->name == 'points_widget') {
    dpm($query);
    $query->has_aggregate = TRUE;
    $query->fields['id_1']['function'] = 'min';
    $query->groupby[] = array('field' => 'id');
  }
}