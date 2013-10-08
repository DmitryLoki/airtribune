<?php
/**
 * @file
 * Main NodeSymlinks callbacks
 */

/**
 * Delete menulink and alias of given item.
 *
 * It is not needed to have item fully loaded.
 * Required keys are 'link_path' and 'mlid'.
 */
function nodesymlinks_item_delete(stdClass $item) {
  // Delete alias.
  if (module_exists('path')) {
    path_delete(array('source' => $item->link_path));
  }
  // Delete menu item.
  menu_link_delete($item->mlid);
  // Delete our stored copy.
  db_delete('nodesymlinks_link_storage')
    ->condition('mlid', $item->mlid)
    ->execute();
}

/**
 * Load all duplicate menulinks from database for given node nid.
 *
 * Returns array of mlid and link_path.
 */
function nodesymlinks_get_items_by_nid($nid) {
  return db_query("SELECT mlid, link_path FROM {menu_links} WHERE module = :module AND link_path LIKE :link_path", array(':module' => 'nodesymlinks', ':link_path' => "node/$nid/mid/%"))->fetchAllAssoc('mlid');
}

/**
 * Implements hook_nodeapi() OP: Valide.
 *
 * @see nodesymlinks_nodeapi()
 */
function _nodesymlinks_nodeapi_validate(&$node, $op) {
  // Check if aliases are unique.
  if (module_exists('path') && isset($node->menu['nodesymlinks']) && !empty($node->menu['nodesymlinks']['items'])) {
    $items = (array) $node->menu['nodesymlinks']['items'];
    $language = isset($node->language) ? $node->language : '';
    $unique_paths = array();
    if (variable_get('nodesymlinks_check_menuitem', 1) && empty($node->menu['link_title']) && count($items)) {
      form_set_error('menu][link_title', t('You have some nodesymlinks defined but primary node menu item is empty. Please create node menu item first.'));
    }

    foreach ($items as $i => &$item) {
      $item['alias']['path'] = $path = trim($item['alias']['path']);
      if (!empty($item['alias']['path'])) {
        // Check if paths are unique in this form.
        if (in_array($path, $unique_paths)) {
          form_set_error("menu][nodesymlinks][items][$i][alias][path", t('The path is already in use.'));
        }
        else {
          $unique_paths[] = $path;
        }

        if (module_exists('pathauto')) {
          // Check if the path is not empty when pathauto is switched off.
          if (empty($item['alias']['pathauto']) && empty($item['alias']['path'])) {
            form_set_error("menu][nodesymlinks][items][$i][alias][path", t('The path is empty.'));
          }
          // Check if path is unique in the DB.
          else {
            $system_path = nodesymlinks_create_item_path($item, $node);
            if (db_query("SELECT COUNT(pid) FROM {url_alias} WHERE alias = :alias AND source <> :source AND language = :language",
              array(
                ':alias' => $path,
                ':source' => $system_path,
                ':language' => $language)
              )->fetchField()) {
              form_set_error("menu][nodesymlinks][items][$i][alias][path", t('The path is already in use.'));
            }

          }
        }
        // Without pathauto.
        elseif (!empty($item['alias']['path'])) {
          $system_path = nodesymlinks_create_item_path($item, $node);
          if (db_query("SELECT COUNT(pid) FROM {url_alias} WHERE alias = :alias AND source <> :source AND language = :language",
            array(
              ':alias' => $path,
              ':source' => $system_path,
              ':language' => $language)
            )->fetchField()) {
            form_set_error("menu][nodesymlinks][items][$i][alias][path", t('The path is already in use.'));
          }
        }
      }
    }
  }
}

/**
 * Implements hook_nodeapi() OP: Insert & Update.
 *
 * @see nodesymlinks_nodeapi()
 */
function _nodesymlinks_nodeapi_insert_update(&$node, $op) {
  $count_deleted = $count_saved = 0;

  // Check if a menu item will be created and keep $items consistent.
  $items = array();
  if (!empty($node->menu['nodesymlinks']['items'])) {
    $items = $node->menu['nodesymlinks']['items'];
  }

  $saved_items = array();

  // Save all menulinks from form (insert/update is handled by Menu API).
  foreach ($items as &$item) {
    // Load defaults and process item before save.
    nodesymlinks_item_process($item, $node);
    if (!$item['is_new']) {
      $saved_items[] = $item['mlid'];
    }

    if ($mlid = nodesymlinks_item_save($item, $node)) {
      ++$count_saved;
      if ($item['is_new']) {
        $saved_items[] = $mlid;
      }
    }
    else {
      drupal_set_message(t('There was an error when saving the menu link.'), 'error');
    }
  }

  // Detect which items exists in database, but it was not saved.
  // Delete them.
  $db_items = nodesymlinks_get_items_by_nid($node->nid);
  $items_to_delete = array_diff(array_keys($db_items), $saved_items);
  while ($mlid = array_pop($items_to_delete)) {
    nodesymlinks_item_delete($db_items[$mlid]);
    ++$count_deleted;
  }

  drupal_set_message(
      format_plural($count_saved, 'Saved 1 nodesymlink.', 'Saved @count nodesymlinks.') . ' ' .
      format_plural($count_deleted, 'Deleted 1 nodesymlink.', 'Deleted @count nodesymlinks.')
  );
}

/**
 * Implements hook_nodeapi() OP: Delete.
 *
 * @see nodesymlinks_nodeapi()
 */
function _nodesymlinks_nodeapi_delete(&$node, $op) {
  // Delete all menu module links that point to this node.
  $result = db_query("SELECT mlid FROM {menu_links} WHERE link_path LIKE 'node/:nid/mid/%' AND module = ':module' ", array(':module' => 'nodesymlinks', ':nid' => $node->nid));
  while ($mlid = $result->fetchField()) {
    menu_link_delete($mlid);
  }
  // Care about our aliases.
  db_delete('url_alias')
    ->condition('source', $node->nid, 'LIKE')
    ->execute();
  // Delete our nodesymlinks storage.
  db_delete('nodesymlinks_link_storage')
    ->condition('nid', $node->nid)
    ->execute();
}

/**
 * Implements hook_nodeapi() OP: Prepare & Presave.
 *
 * @see nodesymlinks_nodeapi()
 */
function _nodesymlinks_nodeapi_prepare_presave(&$node, $op) {
  // Prepare the node for the edit form so that $node->menu always exists.
  $items = array();
  if (isset($node->nid)) {
    // Check all menus if a link does not exist in the default menu.
    $result = db_query("SELECT mlid FROM {menu_links} WHERE module = 'nodesymlinks' AND link_path LIKE :link_path ORDER BY mlid ASC", array(':link_path' => "node/$node->nid/mid/%"));
    while ($row = $result->fetchAssoc()) {
      $items[$row['mlid']] = $item = menu_link_load($row['mlid']);
      $items[$row['mlid']]['fragment'] = empty($item['options']['fragment']) ? '' : $item['options']['fragment'];
      if (module_exists('path')) {
        $items[$row['mlid']]['alias'] = db_query("SELECT pid, alias as path FROM {url_alias} WHERE source = :source AND language = :language", array(':source' => $items[$row['mlid']]['link_path'], ':language' => $node->language))->fetchAssoc();
      }
    }
  }
  // Set default values.
  $node->nodesymlinks['items'] = $items;
}

/**
 * Helper function to generate custom nodesymlinks form item.
 */
function _nodesymlinks_form_field(array $item, stdClass $node) {

  // Load default properties.
  $item += array(
    'link_title' => isset($item['link_title']) ? $item['link_title'] : '',
    'mlid' => 0,
    'plid' => 0,
    'menu_name' => 'navigation',
    'weight' => 0,
    'options' => array(),
    'module' => 'nodesymlinks',
    'expanded' => 0,
    'hidden' => 0,
    'has_children' => 0,
    'customized' => 0,
  );

  $item_form = array();
  $item_form['#tree'] = TRUE;

  // @TODO Maybe we can simplify this - whole array can be stored in Value type
  foreach (array('mlid', 'module', 'hidden', 'has_children', 'customized', 'options', 'expanded') as $key) {
    $item_form[$key] = array(
      '#type' => 'value',
      '#value' => $item[$key],
    );
  }

  // Generate list of possible parents (not including this item or descendants).
  $menu_parent_options = menu_parent_options(menu_get_menus(), $item, $node->type);
  // Generate all tree $item['mlid'] == 0
  $menu_default_parent = !empty($item['parents']) ? $item['parents'] : $item['menu_name'] . ':' . $item['plid'];
  if (!isset($menu_parent_options[$menu_default_parent])) {
    $menu_default_parent = array('primary-links:0');
  }

  $item_form['parents'] = array(
    '#type' => 'select',
    '#default_value' => $menu_default_parent,
    '#options' => $menu_parent_options,
    '#multiple' => FALSE,
    '#description' => '',
    '#attributes' => array('class' => array('menu-title-select')),
  );

  $item_form['link_title'] = array(
    '#type' => 'textfield',
    // Check_plain() is not necessary here
    // (and it translates titles to HTML entities).
    '#default_value' => $item['link_title'],
    '#description' => '',
    '#required' => FALSE,
    '#size' => 10,
  );

  if (module_exists('path')) {
    $language = isset($node->language) ? $node->language : '';

    $item_form['alias'] = array('#tree' => TRUE);

    if (module_exists('pathauto')) {
      // Find if there is an automatic alias pattern for this node type.
      $pattern = pathauto_pattern_load_by_entity('nodesymlinks', $node->type, $language);

      // If there is a pattern, show the automatic alias checkbox.
      if ($pattern) {
        if (!isset($item['alias']['pathauto'])) {
          if (!empty($node->nid) && !empty($item['mlid'])) {
            // If this is not a new node, compare it's current alias to the
            // alias that would be genereted by pathauto. If they are the same,
            // then keep the automatic alias enabled.
            $pathauto_alias = nodesymlinks_pathauto_create_alias($item, $node);
            $item['alias']['pathauto'] = isset($item['alias']['path']) && $item['alias']['path'] == $pathauto_alias;
          }
          else {
            // If this is a new node, enable the automatic alias.
            $item['alias']['pathauto'] = TRUE;
          }
        }

        // Automatic alias.
        $item_form['alias']['pathauto'] = array(
          '#type' => 'checkbox',
          '#default_value' => $item['alias']['pathauto'],
        );
      }
    }

    $path = !empty($item['alias']['path']) ? $item['alias']['path'] : '';

    $item_form['alias']['path'] = array(
      '#type' => 'textfield',
      '#default_value' => $path,
      '#maxlength' => 128,
      '#size' => 10,
      '#access' => user_access('create url aliases'),
    );

    if ($path) {
      $item_form['alias']['pid'] = array(
        '#type' => 'value',
        '#value' => db_query("SELECT pid FROM {url_alias} WHERE alias = :alias AND language = :language", array(':alias' => $path, ':language' => $language))->fetchField()
      );
    }
  }

  $item_form['fragment'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($item['fragment']) ? $item['fragment'] : '',
    '#maxlength' => 128,
    '#size' => 10,
    '#access' => user_access('create url aliases'),
  );

  $item_form['weight'] = array(
    '#type' => 'weight',
    '#delta' => 50,
    '#default_value' => $item['weight'],
    '#description' => '',
  );

  $item_form['delete'] = array(
    '#type' => 'checkbox',
    '#title' => '',
  );

  return $item_form;
}

/**
 * Implements hook_form_alter().
 *
 * Adds nodesymlinks item fields to the node form.
 */
function _nodesymlinks_node_form_alter(&$form, &$form_state) {
  // The submit handlers require that this form is cached,
  // regardless of whether Ajax is used.
  $form_state['cache'] = TRUE;
  $node = $form['#node'];

  // Add JavaScript that will disable the path textfield
  // when the automatic alias checkbox is checked.
  $form['#attached']['js'][] = drupal_get_path('module', 'nodesymlinks') . '/nodesymlinks.js';

  if (isset($form_state['values']['menu']['nodesymlinks']['items'])) {
    $nodesymlinks = (array) $form_state['values']['menu']['nodesymlinks']['items'];
    // @TODO: switch to this for PHP 5.3+
    // $nodesymlinks = array_values(array_filter($nodesymlinks, function($x) {return $x['delete'] != 1; }));
    $array_filter_callback = create_function('$x', 'return $x["delete"] != 1;');
    $nodesymlinks = array_values(array_filter($nodesymlinks, $array_filter_callback));
    $form_state['values']['menu']['nodesymlinks']['items'] = $nodesymlinks;
  }
  else {
    $nodesymlinks = (array) $node->nodesymlinks['items'];
  }

  $form['menu']['nodesymlinks'] = array(
    '#type' => 'fieldset',
     // @TODO: Fix this.
    '#type' => 'container',
    '#title' => t('Show in More Locations'),
    '#access' => user_access('administer menu') && user_access('administer nodesymlinks'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($nodesymlinks) ? TRUE : FALSE,
    '#tree' => TRUE,
    '#weight' => 1,
    '#attributes' => array('class' => array('nodesymlinks-items-form')),
    '#states' => array(
      'invisible' => array(
        'input[name="menu[enabled]"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['menu']['nodesymlinks']['items'] = array(
    '#tree' => TRUE,
    '#theme' => 'nodesymlinks_form_items',
  );

  $delta = 0;
  foreach ($nodesymlinks as $item) {
    $form['menu']['nodesymlinks']['items'][$delta++] = _nodesymlinks_form_field($item, $node);
  }

  if (isset($form_state['nodesymlinks']['item_count'])) {
    $new_max_delta = $form_state['nodesymlinks']['item_count'] - 1;
    for ($delta; $delta <= $new_max_delta; ++$delta) {
      $new_item = array(
        'new_item' => TRUE,
        'link_title' => $node->title,
        'mlid' => 0,
        'alias' => array(),
      );
      $form['menu']['nodesymlinks']['items'][$delta] = _nodesymlinks_form_field($new_item, $node);
    }
  }

  $form['menu']['nodesymlinks']['#description'] = _nodesymlinks_form_description();

  $form['menu']['nodesymlinks']['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete locations'),
    '#submit' => array('nodesymlinks_node_form_submit_delete'),
    '#ajax' => array(
      'callback' => '_nodesymlinks_form_ajax',
      'wrapper' => 'nodesymlinks-items-ajax',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['menu']['nodesymlinks']['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add location'),
    '#submit' => array('nodesymlinks_node_form_submit_add'),
    '#ajax' => array(
      'callback' => '_nodesymlinks_form_ajax',
      'wrapper' => 'nodesymlinks-items-ajax',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  if (isset($form_state['clicked_button'])) {
    $clicked_val = $form_state['clicked_button']['#value'];
    if ($clicked_val == t('Add Location') || $clicked_val == t('Delete Location(s)')) {
      $form['menu']['enabled']['#default_value'] = TRUE;
      $form['menu']['nodesymlinks']['#collapsed'] = FALSE;
    }
  }
}

/**
 * Form description callback.
 */
function _nodesymlinks_form_description() {
  $description = t("This module allows you to show this node's content within multiple places in your site.");
  $description .= '<br />' . t("<b>Parent item:</b> The place where this page's content will appear. It will use the selected parent's breadcrumbs and sidebar. Items in the hierarchy deeper than !maxdepth-1 levels may not appear.", array('!maxdepth' => MENU_MAX_DEPTH, '!maxdepth-1' => MENU_MAX_DEPTH - 1));
  $description .= '<br />' . t('<b>Link title:</b> The link text corresponding to this item that should appear in the menu.');
  if (user_access('create url aliases')) {
    if (module_exists('pathauto')) {
      $description .= '<br />' . t('<b>Pathauto:</b> Optional. When checked, path alias will be generated using Pathauto.');
      $description .= '<br />' . t('<b>Path:</b> Optional. When Pathauto checkbox is unchecked you can write custom unique path alias here.');
    }
    elseif (module_exists('path')) {
      $description .= ' <br />' . t('<b>Path:</b> Optional. You can write custom unique path alias here. If you leave this field empty and node path alias is filled in (URL path settings), default alias will be generated using following pattern: <em>&lt;node-path-alias&gt;_&lt;menu-link-id&gt;</em>');
    }
  }
  $description .= ' <br />' . t('<b>Weight:</b> Optional. In the menu, a higher weight number will sink down and a lower weight will be positioned closer to the top.');
  $description .= ' <br />' . t('<b>Delete:</b> To delete nodesymlinks, first check the "Delete" checkbox in the desired rows, then click "Delete Location(s)".');
  $description .= ' <br />' . t('<b>Saving:</b> When you are done editing, you must click "Save" at the very bottom of the page to save your changes.');
  return $description;
}

/**
 * Ajax callback for form.
 */
function _nodesymlinks_form_ajax($form, $form_state) {
  return $form['menu']['nodesymlinks']['items'];
}

/**
 * Add new symlinks item, submit handler for symlinks at node form.
 *
 * @see nodesymlinks_form_alter()
 */
function nodesymlinks_node_form_submit_add($form, &$form_state) {
  // Set the form to rebuild and run submit handlers.
  if ($_GET['q'] != 'system/ajax') {
    node_form_submit_build_node($form, $form_state);
  }
  $form_state['rebuild'] = TRUE;

  // Make the changes we want to the form state.
  if ($form_state['clicked_button']['#value'] == $form['menu']['nodesymlinks']['add']['#value']) {
    $items = element_children($form['menu']['nodesymlinks']['items']);
    // Define new item count - will be used in form process to add new items.
    $form_state['nodesymlinks']['item_count'] = count($items) + 1;
  }
}

/**
 * Delete selected symlinks items, submit handler for symlinks at node form.
 *
 * @see nodesymlinks_form_alter()
 */
function nodesymlinks_node_form_submit_delete($form, &$form_state) {
  // Set the form to rebuild and run submit handlers.
  if ($_GET['q'] != 'system/ajax') {
    node_form_submit_build_node($form, $form_state);
  }
  $form_state['rebuild'] = TRUE;

  if ($form_state['clicked_button']['#value'] == $form['menu']['nodesymlinks']['delete']['#value']) {
    $item_keys = element_children($form['menu']['nodesymlinks']['items']);
    $values_items = &$form_state['values']['menu']['nodesymlinks']['items'];
    $delete_count = 0;
    foreach ($item_keys as $delta) {
      if (!empty($values_items[$delta]['delete'])) {
        $delete_count++;
      }
    }
    $form_state['nodesymlinks']['item_count'] =- $delete_count;
  }
}

/**
 * Creates and returns item path.
 */
function nodesymlinks_create_item_path(&$item, &$node) {
  return 'node/' . $node->nid . '/mid/' . $item['mlid'];
}

/**
 * Load item defaults and process item before is saved.
 */
function nodesymlinks_item_process(&$item, &$node) {
  $item_defaults = array(
    'link_title' => '',
    'mlid' => 0,
    'plid' => 0,
    'menu_name' => 'navigation',
    'weight' => 0,
    'options' => array(),
    'module' => 'nodesymlinks',
    'expanded' => 0,
    'hidden' => 0,
    'has_children' => 0,
    'customized' => 0,
  );
  // Load defaults.
  $item += $item_defaults;

  // Mark new item, $item[mlid]=0 is changed during menu_link_save, so
  // it can't be used to marking.
  $item['is_new'] = ($item['mlid'] == 0) ? TRUE : FALSE;
  if (!empty($item['parents'])) {
    list($item['menu_name'], $item['plid']) = explode(':', $item['parents']);
  }
  if (!$item['customized']) {
    $item['options']['attributes']['title'] = trim($node->title);
  }

  // @TODO: maybe we can remove this line, if we validate not empty title field
  // and fill the field with the default value.
  $item['link_title'] = trim($item['link_title']) ? trim($item['link_title']) : $node->title;

  $item['link_path'] = nodesymlinks_create_item_path($item, $node);
}

/**
 * Save item to database.
 *
 * Create alias for duplicate menulink if original node
 * has one. Returns TRUE if saving was successfull, else returns FALSE.
 *
 * @return menu link ID or FALSE
 */
function nodesymlinks_item_save(&$item, &$node) {
  // If this function is updated, please update its counterpart in
  // nodesymlinks.install, which exists to restore deleted menu_links during
  // module re-enable.
  $item['options']['fragment'] = empty($item['fragment']) ? '' : $item['fragment'];
  if (menu_link_save($item)) {
    // If the item is new, we need to save it second time - now with real mlid.
    if ($item['is_new']) {
      $item['link_path'] = nodesymlinks_create_item_path($item, $node);
      menu_link_save($item);
    }

    // Because menu_links is wiped out on module disable (not Uninstall),
    // we need to store this for later re-use if we detect a module re-enable.
    if ($item['is_new']) {
      // Save data in our permanent store.
      db_insert('nodesymlinks_link_storage')
        ->fields(array(
          'mlid' => $item['mlid'],
          'nid' => $node->nid,
          'item_data' => serialize($item),
        ))
        ->execute();
    }
    else {
      // Update in permanent store.
      db_update('nodesymlinks_link_storage')
        ->fields(array(
          'nid' => $node->nid,
          'item_data' => serialize($item),
        ))
        ->condition('mlid', $item['mlid'])
        ->execute();
    }

    // Creates appropriate aliases.
    $item['link_path'] = nodesymlinks_create_item_path($item, $node);
    nodesymlinks_item_alias_save($item, $node);

    return $item['mlid'];
  }

  return FALSE;
}

/**
 * Create alias for duplicate menulink if original node.
 */
function nodesymlinks_item_alias_save(&$item, &$node) {
  // TODO: refactor this.
  // Integrate with Path.
  if (module_exists('path')) {
    // We need to know pid to provide "update" otherwise
    // Path creates new alias to the same path.
    $pid = !empty($item['alias']['pid']) ? $item['alias']['pid'] : NULL;
    // Integrate with Pathauto.
    if (module_exists('pathauto')) {
      // Pathauto alias.
      if (!empty($item['alias']['pathauto']) || empty($item['alias']['path'])) {
        $op = ($item['is_new']) ? 'insert' : 'update';
        return nodesymlinks_pathauto_create_alias($item, $node, $op);
      }
      // Custom alias.
      else {
        $path = array(
          'source' => $item['link_path'],
          'alias' => $item['alias']['path'],
          'pid' => $pid,
          'language' => $node->language,
        );
        return path_save($path);
      }
    }
    elseif (!empty($item['alias']['path'])) {
      // Save custom path alias.
      $path = array(
        'source' => $item['link_path'],
        'alias' => trim($item['alias']['path']),
        'pid' => $pid,
        'language' => $node->language,
      );
      return path_save($path);
    }
    else {
      // Create and save default alias based on node path.
      $path_alias = (empty($node->path) || $node->path == 'node/' . $node->nid) ? '' : $node->path . '_' . $item['mlid'];
      $path = array(
        'source' => $item['link_path'],
        'alias' => $path_alias,
        'pid' => $pid,
        'language' => $node->language,
      );
      return path_save($path);
    }
  }
}

/**
 * Function for creating aliases using Pathauto API.
 */
function nodesymlinks_pathauto_create_alias($item, $node, $op = 'return') {
  module_load_include('inc', 'pathauto');
  $language = isset($node->language) ? $node->language : LANGUAGE_NONE;
  $uri = nodesymlinks_create_item_path($item, $node);
  return pathauto_create_alias('nodesymlinks', $op, $uri, array('node' => $node, 'menu-link' => $item), $node->type, $language);
}

/**
 * Generate aliases for all nodesymlinks without aliases.
 */
function _nodesymlinks_pathauto_bulkupdate() {
  $count = 0;
  $results = db_query("SELECT m.mlid, m.link_path, u.source, u.alias
    FROM {menu_links} m LEFT JOIN {url_alias} u ON m.link_path = u.source
    WHERE m.module = 'nodesymlinks' AND u.source IS NULL");

  foreach ($results as $row) {
    list(, $nid) = explode('/', $row->link_path);
    $node = node_load($nid, NULL, TRUE);
    $item = menu_link_load($row->mlid);
    $node->source = $row->source;
    $node->alias = $row->alias;
    if (nodesymlinks_pathauto_create_alias($item, $node, 'bulkupdate')) {
      $count++;
    }
  }

  drupal_set_message(format_plural($count,
                                   'Bulk generation of nodes completed, one alias generated.',
                                   'Bulk generation of nodes completed, @count aliases generated.')
  );
}

/**
 * Theme nodesymlinks form items.
 */
function theme_nodesymlinks_form_items($variables) {
  $form = $variables['form'];
  $output = '<div id="nodesymlinks-items-ajax">';
  $items = element_children($form);
  $rows = array();
  $path = $pathauto = $fragment = FALSE;

  foreach ($items as $delta) {
    $row = array();
    $row[] = $delta;
    // Always uncheck delete checkboxes.
    $form[$delta]['delete']['#checked'] = FALSE;
    $row[] = drupal_render($form[$delta]['delete']);
    $row[] = drupal_render($form[$delta]['parents']);
    $row[] = drupal_render($form[$delta]['link_title']);
    if (isset($form[$delta]['alias']['pathauto'])) {
      $row[] = drupal_render($form[$delta]['alias']['pathauto']);
      $pathauto = TRUE;
    }
    if (isset($form[$delta]['alias']['path'])) {
      $row[] = drupal_render($form[$delta]['alias']['path']);
      $path = TRUE;
    }
    if (isset($form[$delta]['fragment'])) {
      $row[] = drupal_render($form[$delta]['fragment']);
      $fragment = TRUE;
    }
    $row[] = drupal_render($form[$delta]['weight']);
    $rows[] = $row;
  }
  $header = array();
  $header[] = '#';
  $header[] = t('Delete');
  $header[] = t('Parent item');
  $header[] = t('Link title');
  if ($pathauto) {
    $header[] = t('Pathauto');
  }
  if ($path) {
    $header[] = t('Path alias');
  }
  if ($fragment) {
    $header[] = t('Fragment');
  }
  $header[] = t('Weight');
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'nodesymlinks-items')));
  $output .= drupal_render_children($form);
  $output .= '</div>';
  return $output;
}
