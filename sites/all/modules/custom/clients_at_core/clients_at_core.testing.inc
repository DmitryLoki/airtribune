<?php
/**
 * @file
 * Contains classes for Client connection testing.
 */

/**
 * Test basic connection to CoreAPI.
 */
class ClientsConnectionCoreGetAllUsers implements ClientsConnectionTestingInterface {

  function testLabels() {
    return array(
      'label' => t('Get all users'),
      'description' => t('Test the basic connection to the site by logging in the user.'),
      'button' => t('Connect'),
    );
  }

  /**
   * Execute the test.
   *
   * Connection test handlers should return the raw data they got back from the
   * connection for display to the user.
   *
   * @param $connection
   *  The connection handler.
   * @param $form_values
   *  The form values for the test form element. The values for elements added
   *  to the form are in $form_values['params'].
   *
   * @return
   *  Data from the remote connection. This is output to the form as raw data.
   */
  function test($connection, &$form_values) {
    try {
      $users = $connection->makeRequest('user', 'GET');
    }
    catch (Exception $e) {
      drupal_set_message(t('Could not log in to the remote site, got error message "@message".', array(
        '@message' => $e->getMessage(),
      )), 'warning');
      return;
    }

    if (is_array($users)) {
      drupal_set_message(t('Loaded @count users', array('@count'  => count($users))));
    }
    else {
      drupal_set_message(t('Could not load users.'), 'warning');
    }

    return $users;
  }

}

class ClientsConnectionCoreGetUser implements ClientsConnectionTestingInterface {

  function testLabels() {
    return array(
      'label' => t('Test user retrieval'),
      'description' => t('Load a user from CoreAPI.'),
      'button' => t('Load user'),
    );
  }

  function testForm($element) {
    $element['params']['pers_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Pers ID'),
      '#description' => t('For example, <code>pers-140211-3284629059</code>'),
      '#size' => 30,
      '#required' => TRUE,
    );

    return $element;
  }

  function test($connection, &$form_values) {
    $pers_id = $form_values['params']['pers_id'];

    try {
      $user = $connection->makeRequest('user/' . $pers_id, 'GET');
    }
    catch (Exception $e) {
      drupal_set_message(t('Could not retrieve a user from the CoreAPI, got error message "@message".', array(
        '@message' => $e->getMessage(),
      )), 'warning');
      return;
    }

    if (is_object($user) && isset($user->email)) {
      drupal_set_message(t('Sucessfully retrieved user @name (@mail).', array(
        '@name' => $user->name,
        '@mail'  => $user->email,
        )));
    }

    return $user;
  }

}

class ClientsConnectionCoreGetUserToken implements ClientsConnectionTestingInterface {

  function testLabels() {
    return array(
      'label' => t('Test token retrieval'),
      'description' => t('Get user auth token for CoreAPI.'),
      'button' => t('Get token'),
    );
  }

  function testForm($element) {
    $element['params']['username'] = array(
      '#type' => 'textfield',
      '#title' => t('username / mail'),
      '#default_value' => 'test',
      '#size' => 30,
      '#required' => TRUE,
    );
    $element['params']['password'] = array(
      '#type' => 'textfield',
      '#title' => t('password'),
      '#default_value' => 'test',
      '#size' => 30,
      '#required' => TRUE,
    );
    return $element;
  }

  function test($connection, &$form_values) {
    try {
      $result = $connection->getAuthToken($form_values['params']['username'], $form_values['params']['password']);
    }
    catch (Exception $e) {
      drupal_set_message(t('Could not retrieve a user from the CoreAPI, got error message "@message".', array(
        '@message' => $e->getMessage(),
      )), 'warning');
      return;
    }

    if (is_object($user) && isset($user->email)) {
      drupal_set_message(t('Sucessfully retrieved user @name (@mail).', array(
        '@name' => $user->name,
        '@mail'  => $user->email,
      )));
    }

    return $user;
  }

}

class ClientsConnectionATCoreCreateSponsor implements ClientsConnectionTestingInterface {

  function testLabels() {
    return array(
      'label' => t('Create a sponsor'),
      'description' => t('Create a sponsor in CoreAPI from an array of data.'),
      'button' => t('Create'),
    );
  }

  function testForm($element) {
    $element['params']['pers_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Pers ID'),
      '#description' => t('For example, <code>pers-140211-3284629059</code>'),
      '#size' => 30,
      '#required' => TRUE,
    );

    $sample_data = '{
    "url": "http://gopro.com",
    "image": ""
}';
    $element['params']['data'] = array(
      '#type' => 'textarea',
      '#rows' => 10,
      '#title' => t('Data'),
      '#description' => t('The POST data to pass for the entity, as either a JSON.') . '<br>'
        . t('Sample data:') . '<br>'
        . "<pre>$sample_data</pre>",
    );

    return $element;
  }

  function test($connection, &$form_values) {
    $path = 'user/' . $form_values['params']['pers_id'] . '/sponsor';
    $data = drupal_json_decode($form_values['params']['data']);

    try {
      $result = $connection->makeRequest($path, 'POST', $data);
    }
    catch (Exception $e) {
      drupal_set_message($e->getMessage(), 'warning');
      return;
    }

    return $result;
  }

}

