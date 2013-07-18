<?php

/**
 * @file
 * Contain class that handles page cache expiration for different entities.
 */

class MemcacheStoragePC {

  /**
   * Executes expiration actions for node.
   *
   * @param $node
   *   Node object.
   * @param $action
   *   Action that has been executed.
   */
  public static function expireNode($node, $action) {

    if (empty($node->nid) || empty($node->type)) {
      return;
    }

    // See if cache settings was overriden for this node type.
    $settings_overriden = variable_get('memcache_storage_pc_node_override_defaults_' . $node->type);

    $variable_suffix = '';
    if (!empty($settings_overriden)) {
      // If page cache settings was overriden for this node type we
      // should add "_[NODE-TYPE]" to every variable name we use here.
      $variable_suffix = '_' . $node->type;
    }

    $enabled_actions = variable_get('memcache_storage_pc_node_actions' . $variable_suffix, array());
    $enabled_actions = array_filter($enabled_actions);

    // Do not process current action if it is not selected by administrator.
    if (!in_array($action, $enabled_actions)) {
      return;
    }

    $expire_urls = array();

    // Expire front page.
    $expire_front_page = variable_get('memcache_storage_pc_node_expire_front_page' . $variable_suffix, MEMCACHE_STORAGE_PC_NODE_EXPIRE_FRONT_PAGE);
    if ($expire_front_page) {
      $expire_urls['front'] = '<front>';
    }

    // Expire node page.
    $expire_node_page = variable_get('memcache_storage_pc_node_expire_node_page' . $variable_suffix, MEMCACHE_STORAGE_PC_NODE_EXPIRE_NODE_PAGE);
    if ($expire_node_page) {
      $expire_urls['node-' . $node->nid] = 'node/' . $node->nid;
    }

    // Expire taxonomy term pages.
    $expire_term_pages = variable_get('memcache_storage_pc_node_expire_term_pages' . $variable_suffix, MEMCACHE_STORAGE_PC_NODE_EXPIRE_TERM_PAGES);
    if (module_exists('taxonomy') && $expire_term_pages) {
      $urls = self::expireNodeTermPages($node);
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Expire node reference's pages.
    $expire_node_references = variable_get('memcache_storage_pc_node_expire_reference_pages' . $variable_suffix, MEMCACHE_STORAGE_PC_NODE_EXPIRE_REFERENCE_PAGES);
    if (module_exists('node_reference') && $expire_node_references) {
      $urls = self::expireNodeReferences($node);
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Expire custom pages.
    $expire_custom_urls = variable_get('memcache_storage_pc_node_expire_custom' . $variable_suffix, MEMCACHE_STORAGE_PC_NODE_EXPIRE_CUSTOM);
    if ($expire_custom_urls) {
      $pages = variable_get('memcache_storage_pc_node_expire_custom_pages' . $variable_suffix);
      $urls = self::expireCustomPages($pages, array('node' => $node));
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Flush page cache for expired urls.
    if (!empty($expire_urls)) {
      self::flushCache($expire_urls);
    }
  }

  /**
   * Executes expiration actions for comment.
   *
   * @param $comment
   *   Comment object.
   * @param $action
   *   Action that has been executed.
   */
  public static function expireComment($comment, $action) {

    // Some actions may be executed one after another. To avoid
    // duplicate executions we should check whether was already flushed.
    static $cache_flushed = FALSE;
    if ($cache_flushed) {
      return;
    }

    if (empty($comment->cid) || empty($comment->nid)) {
      return;
    }

    // Load node for this comment.
    $node = node_load($comment->nid);
    if (empty($node->type)) {
      return;
    }

    // See if cache settings was overriden for this node type.
    $settings_overriden = variable_get('memcache_storage_pc_comment_override_defaults_' . $node->type);

    $variable_suffix = '';
    if (!empty($settings_overriden)) {
      // If page cache settings was overriden for this node type we
      // should add "_[NODE-TYPE]" to every variable name we use here.
      $variable_suffix = '_' . $node->type;
    }

    $enabled_actions = variable_get('memcache_storage_pc_comment_actions' . $variable_suffix, array());
    $enabled_actions = array_filter($enabled_actions);

    // Do not process current action if it is not selected by administrator.
    if (!in_array($action, $enabled_actions)) {
      return;
    }

    $expire_urls = array();

    // Expire front page.
    $expire_front_page = variable_get('memcache_storage_pc_comment_expire_front_page' . $variable_suffix, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_FRONT_PAGE);
    if ($expire_front_page) {
      $expire_urls['front'] = '<front>';
    }

    // Expire comment page.
    $expire_comment_page = variable_get('memcache_storage_pc_comment_expire_comment_page' . $variable_suffix, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_COMMENT_PAGE);
    if ($expire_comment_page) {
      $expire_urls['comment-' . $comment->cid] = 'comment/' . $comment->cid;
    }

    // Expire comment's node page.
    $expire_node_page = variable_get('memcache_storage_pc_comment_expire_node_page' . $variable_suffix, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_NODE_PAGE);
    if ($expire_node_page) {
      $expire_urls['node-' . $comment->nid] = 'node/' . $comment->nid;
    }

    // Expire comment's node term pages.
    $expire_node_term_pages = variable_get('memcache_storage_pc_comment_expire_node_term_pages' . $variable_suffix, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_NODE_TERM_PAGES);
    if (module_exists('taxonomy') && $expire_node_term_pages) {
      $urls = self::expireNodeTermPages($node);
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Expire comment's node references.
    $expire_node_references = variable_get('memcache_storage_pc_comment_expire_node_reference_pages' . $variable_suffix, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_NODE_REFERENCE_PAGES);
    if (module_exists('node_reference') && $expire_node_references) {
      $urls = self::expireNodeReferences($node);
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Expire custom pages.
    $expire_custom_urls = variable_get('memcache_storage_pc_comment_expire_custom' . $variable_suffix, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_CUSTOM);
    if ($expire_custom_urls) {
      $pages = variable_get('memcache_storage_pc_comment_expire_custom_pages' . $variable_suffix);
      $urls = self::expireCustomPages($pages, array('comment' => $comment));
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Flush page cache for expired urls.
    if (!empty($expire_urls)) {
      self::flushCache($expire_urls);
    }

    $cache_flushed = TRUE;
  }

  /**
   * Executes expiration actions for user.
   *
   * @param $user
   *   User object.
   * @param $action
   *   Action that has been executed.
   */
  public static function expireUser($user, $action) {

    if (empty($user->uid)) {
      return;
    }

    $enabled_actions = variable_get('memcache_storage_pc_user_actions', array());
    $enabled_actions = array_filter($enabled_actions);

    // Do not process current action if it is not selected by administrator.
    if (!in_array($action, $enabled_actions)) {
      return;
    }

    $expire_urls = array();

    // Expire front page.
    $expire_front_page = variable_get('memcache_storage_pc_user_expire_front_page', MEMCACHE_STORAGE_PC_USER_EXPIRE_FRONT_PAGE);
    if ($expire_front_page) {
      $expire_urls['front'] = '<front>';
    }

    // Expire user page.
    $expire_user_page = variable_get('memcache_storage_pc_user_expire_user_page', MEMCACHE_STORAGE_PC_USER_EXPIRE_USER_PAGE);
    if ($expire_user_page) {
      $expire_urls['user-' . $user->uid] = 'user/' . $user->uid;
    }

    // Expire custom pages.
    $expire_custom_urls = variable_get('memcache_storage_pc_user_expire_custom', MEMCACHE_STORAGE_PC_USER_EXPIRE_CUSTOM);
    if ($expire_custom_urls) {
      $pages = variable_get('memcache_storage_pc_user_expire_custom_pages');
      $urls = self::expireCustomPages($pages, array('user' => $user));
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Flush page cache for expired urls.
    if (!empty($expire_urls)) {
      self::flushCache($expire_urls);
    }
  }

  /**
   * Flush page cache for a given urls.
   *
   * @param $urls
   */
  private static function flushCache($urls) {
    foreach ($urls as $key => $url) {

      // Every URL may contain |wildcard suffix, so we should check this.
      $url_parts = explode('|', $url);
      if (count($url_parts) > 1) {
        $wildcard = TRUE;
        array_pop($url_parts);
        $url = implode('|', $url_parts);
      }
      else {
        $wildcard = FALSE;
      }

      $url = url($url, array('absolute' => TRUE));

      // Clear cached page data.
      cache_clear_all($url, 'cache_page', $wildcard);
    }
  }

  /**
   * Find all taxonomy terms in node fields and build urls for them.
   *
   * @param $node
   * @return array
   */
  private static function expireNodeTermPages($node) {

    $terms = array();
    $field_info = field_info_fields();
    $field_instances = field_info_instances('node', $node->type);

    foreach ($field_instances as $name => $instance) {
      if ($field_info[$name]['type'] == 'taxonomy_term_reference') {
        $new_terms = field_get_items('node', $node, $name);
        if (is_array($new_terms) && !empty($new_terms)) {
          $terms = array_merge($new_terms, $terms);
        }
        $old_terms = isset($node->original) && !empty($node->original) ? field_get_items('node', $node->original, $name) : array();
        if (is_array($old_terms) && !empty($old_terms)) {
          $terms = array_merge($old_terms, $terms);
        }
      }
    }

    $urls = array();
    foreach ($terms as $term) {
      $urls['term-' . $term['tid']] = 'taxonomy/term/' . $term['tid'];
    }

    return $urls;
  }

  /**
   * Find all node references in node fields and build urls for them.
   *
   * @param $node
   * @return array
   */
  private static function expireNodeReferences($node) {

    $references = array();
    $field_info = field_info_fields();
    $field_instances = field_info_instances('node', $node->type);

    foreach ($field_instances as $name => $instance) {
      if ($field_info[$name]['type'] == 'node_reference') {
        $new_references = field_get_items('node', $node, $name);
        if (is_array($new_references) && !empty($new_references)) {
          $references = array_merge($new_references, $references);
        }
        $old_references = isset($node->original) && !empty($node->original) ? field_get_items('node', $node->original, $name) : array();
        if (is_array($old_references) && !empty($old_references)) {
          $references = array_merge($old_references, $references);
        }
      }
    }

    $urls = array();
    foreach ($references as $reference) {
      $urls['reference-' . $reference['nid']] = 'node/' . $reference['nid'];
    }

    return $urls;
  }

  /**
   * Create expiration urls for custom pages.
   *
   * @param $pages
   *   Unformated string from user input raw.
   *
   * @param $token_options
   *   Options for token replacements.
   *
   * @return array
   */
  static private function expireCustomPages($pages, $token_options) {

    $urls = array();

    $pages = explode("\n", $pages);
    foreach ($pages as $index => $page) {
      $page = trim($page);
      if (!empty($page)) {

        // Replace only urls with tokens.
        if (token_scan($page)) {
          $page = token_replace($page, $token_options);
        }

        $urls['custom-' . $index] = $page;
      }
    }

    return $urls;
  }

}
