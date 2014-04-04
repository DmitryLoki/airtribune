<?php
/**
 * @file
 * Contains classes for Client connections handlers.
 */

/**
 * Class for Drupal client connections, REST D7.
 */
class clients_connection_drupal_rest_at_core extends clients_connection_base {

  // ============================================ Connection form methods.

  /**
   * Extra form elements specific to a class's edit form.
   *
   * @param $form_state
   *  The form state from the main form, which you probably don't need anyway.
   *
   * @see clients_connection_form()
   * @see clients_connection_form_submit()
   */
  function connectionSettingsFormAlter(&$form, &$form_state) {
    $form['endpoint']['#default_value'] = '';//at_core_sync_get_api_url();
    $form['endpoint']['#description'] = t('Remote service URL e.g. http://site.com/service-endpoint');
  }

  /**
   * Submit handler for saving/updating connections of this class.
   *
   * @see clients_connection_form_submit()
   */
  function connectionSettingsForm_submit($form, &$form_state) {
    // This is here to show an example of how this method works.
    parent::connectionSettingsForm_submit($form, $form_state);
  }

  // ============================================ Resource retrieval.

  /**
   * Common helper for reacting to an error from a REST call.
   *
   * Gets the error from the response, logs the error message,
   * and throws an exception, which should be caught by the module making use
   * of the Clients connection API.
   *
   * @param $response
   *  The REST response data, decoded.
   *
   * @throws Exception
   */
  function handleRestError($response) {
    if ($response->code != 200) {
      watchdog('clients', 'Error with REST request. Error was code @code with error "@error" and message "@message".', array(
        '@code'     => $response->code,
        '@error'    => $response->error,
        '@message'  => $response->status_message,
      ));

      throw new Exception(t("Clients connection error, got message '@message'.", array(
        '@message' => $response->status_message,
      )), $response->code);
    }
  }

  /**
   * API function to request a remote resource.
   *
   * (This function has a rubbish name and parameters for historical reasons:
   * XMLRPC connection classes were developed first.)
   *
   * @param $method
   *  The path of the remote resource to retrieve.
   * @param $method_params
   *  A flat array of further parameters for the request. This should contain:
   *  - The HTTP method.
   *  - (optional) An array of data for the request, such as POST data.
   *
   * @return
   *  Whatever is returned from the remote site.
   */
  function callMethodArray($method, $method_params = array()) {
    $resource_path = $method;
    $http_method = array_shift($method_params);
    // The data array doesn't have to be present, so we have to fiddle about
    // to make sure we don't pass a NULL for it to makeRequest().
    if (count($method_params)) {
      $data = array_shift($method_params);
    }
    else {
      $data = array();
    }

    return $this->makeRequest($resource_path, $http_method, $data);
  }

  /**
   * Make a REST request.
   *
   * Examples:
   * Retrieve a user:
   *  makeRequest('user/{pers-id}', 'GET');
   * Create a sponsor:
   *  makeRequest('user/{pers-id}/sponsor', 'POST', $data);
   *
   * @param $resource_path
   *  The path of the resource. Eg, 'race', 'user/pers-140211-3284629059', etc.
   * @param $http_method
   *  The HTTP method. One of 'GET', 'POST', 'PUT', 'DELETE'. For an explanation
   *  of how the HTTP method affects the resource request, see the Services
   *  documentation at http://drupal.org/node/783254.
   * @param $data = array()
   *  (Optional) An array of data to pass to the request.
   *
   * @return
   *  The data from the request response.
   */
  function makeRequest($resource_path, $http_method, $data = array()) {
    if ($http_method != 'GET' && !isset($this->token)) {
      $this->getAuthToken();
    }

    $data = drupal_json_encode($data);

    $headers = array(
      'Accept' => 'application/json',
    );

    $options = array(
      'headers' => $headers,
      'method'  => $http_method,
      'data'    => $data,
      'token'    => $this->token,
    );

    $response = drupal_http_request($this->endpoint . '/' . $resource_path, $options);

    $this->handleRestError($response);

    $result = json_decode($response->data);
    return $result;
  }

  /**
   * Get the auth token.
   *
   * @throws
   *  An exception if the CoreAPI does not return a token.
   */
  function getAuthToken($username, $password) {
    if (isset($this->token)) {
      return $this->token;
    }

    $headers = array(
      'Content-Type' => 'application/json',
    );

    $data = drupal_json_encode(array(
      'username' => $username,
      'password' => $password,
    ));
    $options = array(
      'headers' => $headers,
      'method'  => 'POST',
      'data'    => $data,
    );

    $response = drupal_http_request($this->endpoint . '/user/auth', $options);
    if ($response->code == 200) {
      $data = json_decode($response->data);
      return $data->token;
    }
    else {
      throw new Exception(t("Unable to get a auth token from the CoreAPI."));
    }
  }

  function usersList() {
    $headers = array(
      'Content-Type' => 'application/json',
    );

    $options = array(
      'headers' => $headers,
      'method'  => 'GET',
//      'data'    => $data,
    );

    $response = drupal_http_request($this->endpoint . '/user', $options);
    $data = json_decode($response->data);

    // Check if login was successful.
    $this->handleRestError($response);

    // Set our cookie for subsequent requests.
    $this->cookie = $data->session_name . '=' . $data->sessid;

    return $data;
  }

}
