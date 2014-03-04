<?php

/**
 * Abstract class with commin synchronisation functions
 */
abstract class ATSync {
  public $entity;
  public $entity_type;
  public $id = FALSE;
  public $address = FALSE;
  public $core_id = FALSE;
  public $address_contest = 'contest/';

  public function __construct($entity_type, $entity) {
    $this->entity = $entity;
    $this->entity_type = $entity_type;
    $this->core_id = get_core_id_from_entity($entity_type, $entity);
    $this->contest = get_contest_for_entity($entity_type, $entity);
    $this->contest_core_id = get_core_id_from_entity('node', $this->contest);
    if (!empty($this->contest_core_id)) {
      $this->address_contest .= $this->contest_core_id;
    }
  }

  public static function requestToCore($address, $data = array(), $method = "POST") {
    $data = json_encode($data);
    $handle = curl_init();
    $url = at_core_sync_get_api_url() . '/' . $address;
    curl_setopt($handle, CURLOPT_URL, $url);
    curl_setopt($handle, CURLOPT_PORT, at_core_sync_get_port());
    curl_setopt($handle, CURLOPT_TIMEOUT, 30);
    curl_setopt($handle, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($handle, CURLOPT_SSL_VERIFYHOST, FALSE);
    curl_setopt($handle, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_setopt($handle, CURLOPT_HTTPHEADER, array(
      'Expect:',
      'Content-Type: application/json',
    ));

    switch ($method) {
      case 'GET':
        break;

      case 'POST':
        curl_setopt($handle, CURLOPT_POST, TRUE);
        curl_setopt($handle, CURLOPT_POSTFIELDS, $data);
        break;

      case 'PUT':
      case 'PATCH':
        curl_setopt($handle, CURLOPT_CUSTOMREQUEST, $method);
        curl_setopt($handle, CURLOPT_POSTFIELDS, $data);
        break;

      case 'DELETE':
        curl_setopt($handle, CURLOPT_CUSTOMREQUEST, 'DELETE');
        break;
    }
    $response = curl_exec($handle);
    $code = curl_getinfo($handle, CURLINFO_HTTP_CODE);
    $request_array = array(
      'code' => $code,
      'method' => $method,
      'url' => $url,
    );
    $request_info = t('!request_info', array('!request_info' => '<pre>' . print_r($request_array, TRUE) . '</pre>'));
    $head = t('Core API[!code]: ', array('!code' => $code));
    $url = l($url, $url);
    switch ($code) {
      case 200:
        ATSync::setMessage($head . t('Request completed.'));
        break;

      case 201:
        ATSync::setMessage($head . t('Resource is successfully created.'));
        break;

      case 202:
        ATSync::setMessage($head . t('Request accepted.'));
        break;

      case 204:
        ATSync::setMessage($head . t('No content. Deleted.'));
        break;

      case 400:
        ATSync::setMessage($head . t('Request has error. Check fields and send again.'), 'error');
        ATSync::setMessage(print_r($response, TRUE), 'error');
        break;

      case 401:
        ATSync::setMessage($head . t('You need to auth before send this request.'), 'error');
        break;

      case 403:
        ATSync::setMessage($head . t('Requested operation not available.'), 'error');
        break;

      case 404:
        ATSync::setMessage($head . t('Resource not found, (!url)', array('!url' => $url)), 'error');
        ATSync::setMessage(print_r($response, TRUE), 'error');
        break;

      case 405:
        ATSync::setMessage($head . t('Method <i>!method</i> is not allowed for resource !url.', array(
            '!method' => $method,
            '!url' => $url,
          )), 'error');
        break;

      case 409:
        ATSync::setMessage($head . t('Conflict happened. See server response for details.', array('!code' => $code)), 'error');
        ATSync::setMessage(print_r($response, TRUE), 'error');
        break;

      case 500:
        ATSync::setMessage($head . t('Format error or server restrictions.', array('!code' => $code)), 'error');
        ATSync::setMessage(print_r($response, TRUE), 'error');
        break;

      case 502:
      case 504:
        $message = $head . t('is unreachable (server error), request queued.') . $request_info;
        ATSync::setMessage($message, 'error');
        watchdog('at_core_sync', $message);
        break;

      case 0:
        $message = $head . t('is unreachable (timeout), request queued.') . $request_info;
        ATSync::setMessage($message, 'error');
        watchdog('at_core_sync', $message);
        break;

      default:
        $message = $head . t('unknown response') . $request_info;
        ATSync::setMessage($message, 'warning');
        watchdog('at_core_sync', $message, array(), WATCHDOG_WARNING);
        break;
    }
    // Debug.
    $full_request = $method . ' ' . at_core_sync_get_api_url() . '/' . $address;
    _asd($data, $full_request , $response);

    return json_decode($response);
  }

  public function request($data, $method = 'POST') {
    return ATSync::requestToCore($this->address, $data, $method);
  }

  public function patch($values = array()) {
    foreach ($values as $k => $v) {
      $results[] = ATSync::requestToCore($this->address, array($k => $v), 'PATCH');
    }
    return $results;
  }

  public function delete() {
    if (!empty($this->core_id)) {
      return ATSync::requestToCore($this->address . '/' . $this->core_id, array(), 'DELETE');
    } else if (!empty($this->day_dmy)) {
      return ATSync::requestToCore($this->address, array(), 'DELETE');
    }
  }

  public function updateCoreID($id) {
    $entity = $this->entity;
    $entity_type = $this->entity_type;
    if ($entity_type == 'og_membership') {
      $entity_type = $entity->entity_type;
      $entity = entity_load_single($entity->entity_type, $entity->etid);
    }
        $entity->field_core_id = array(
      LANGUAGE_NONE => array(
        array(
          'value' => $id,
        ),
      ),
    );
    list($entity_id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
    field_attach_update($entity_type, $entity);
    entity_get_controller($entity_type)->resetCache(array($entity_id));
    $this->core_id = $id;
  }

  public static function setMessage($message = NULL, $type = 'status', $repeat = TRUE) {
    if (user_access('administer site configuration')) {
      drupal_set_message($message, $type, $repeat);
    }
  }

  /**
   * Synchronize one or several fields of object.
   *
   * @param array $data - associative array, where key - name of field, value - new value for field.
   * @return string - Core ID
   */
  public function synchronizePatch($data = array()) {
    if (empty($this->core_id)) {
      $this->synchronize();
    }
    $this->address .= '/' . $this->core_id;
    $response = $this->request($data, "PATCH");
    return !empty($response->id) ? $response->id : FALSE;
  }

  /**
   * Get object stored in Core.
   *
   * @return stdClass
   */
  public function getFromCore() {
    $response = NULL;
    if (!empty($this->core_id)) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request(NULL, "GET");
    }
    return $response;
  }

  abstract public function synchronize();
}

/**
 * Class for synchronization pg_contest
 */
class ATSyncContest extends ATSync {
  public $address = 'contest';

  public function synchronize() {
    $contest = $this->entity;
    $contest_wrapper = entity_metadata_wrapper('node', $contest);
    $this->core_id = get_core_id_from_entity('node', $contest);
    // todo refactor with $contest_wrapper
    $data = array(
      'title' => $contest->title,
      'lat' => substr($contest->field_hq_location[LANGUAGE_NONE][0]['lat'], 0, 8),
      'lon' => substr($contest->field_hq_location[LANGUAGE_NONE][0]['lon'], 0, 8),
      'start_time' => strtotime($contest->field_dates[LANGUAGE_NONE][0]['value']),
      'end_time' => strtotime($contest->field_dates[LANGUAGE_NONE][0]['value2']),
      'place' => $contest->field_city[LANGUAGE_NONE][0]['value'],
      'country' => $contest->field_country[LANGUAGE_NONE][0]['iso2'],
      'timezone' => $contest->field_time_zone[LANGUAGE_NONE][0]['value'],
      'retrieve_id' => !empty($contest->field_device_id[LANGUAGE_NONE][0]['value']) ? $contest->field_device_id[LANGUAGE_NONE][0]['value'] : '',
    );
    if ($this->core_id) {
      // change address if contest already in Core
      $this->address .= '/' . $this->core_id;
      $response = $this->request($data, "PUT");
    }
    else {
      $response = $this->request($data);
      if (!empty($response->id)) {
        $this->updateCoreID($response->id);
      }
    }
    return !empty($response->id) ? $response->id : FALSE;
  }
}

/**
 * Intermediate class for all nested entities in contest by Core API entities ( by path http://api/contest/{id}/* )
 */
abstract class ATSyncNestedInContest extends ATSync {

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    if (!$this->contest_core_id) {
      // Synchronize contest if not synchronized
      $sync = _get_class_by_entity('node', $this->contest);
      $this->contest_core_id = $sync->synchronize();
      if (!$this->contest_core_id) {
        ATSync::setMessage(t('Core API: Contest synchronize error.'));
        return FALSE;
      }
    }
    $this->address_contest .= '/';
    // Change address.
    $this->address = $this->address_contest . $this->address;
  }
}

/**
 * Class for synchronization custom object
 */
abstract class ATSyncCustom extends ATSyncNestedInContest {
  public $name = '';
  public $type = '';
  public $phone = '';
  public $email = '';
  public $description = '';

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    $og_membership = $entity;
    // We get membership, so load referenced entity.
    $entity_type = $entity->entity_type;
    $entity = entity_load_single($entity_type, $entity->etid);
    $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);
    // Get values.
    $description = '';
    if ($entity_type == 'ent_customobject') {
      $this->name = $entity->title;
      $this->type = $entity_wrapper->field_customobject_type->value();
      $description = $entity_wrapper->field_plain_body->value();
    }
    elseif ($entity_type == 'user') {
      $this->name = get_full_name($entity);
      $this->email = $entity->mail;
    }
    $this->tracker = get_tracker('og_membership', $og_membership);
    $this->phone = ($phone = get_phone($og_membership)) ? $phone : '+000000';
    $this->description = $description ? $description['value'] : '';
  }

  public function synchronize() {
    $data = array(
      'name' => $this->name,
      'type' => $this->type,
      'phone' => $this->phone,
      'email' => $this->email,
      'tracker' => $this->tracker,
      'description' => $this->description,
    );
    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request($data, "PUT");
    }
    else {
      $response = $this->request($data);
      $this->updateCoreID($response->id);
    }
    return !empty($response->id) ? $response->id : FALSE;
  }
}

/**
 * Class for synchronization staff
 */
class ATSyncStaff extends ATSyncCustom {
  public $address = 'staff';
}

/**
 * Class for synchronization staff
 */
class ATSyncOrganizer extends ATSyncCustom {
  public $address = 'organizer';
}

class ATSyncTrackedObject extends ATSyncNestedInContest {
  public $address = 'contest/';
  public $tracked_core_id = '';
  public $tracker = NULL;
  public $transport = NULL;

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
  }

  public function synchronize() {
    // todo rewrite - sync customobject on membership update
    return;
    $customobject = entity_load_single(AIRTRIBUNE_CUSTOMOBJECT_TYPE, $this->entity->etid);
    $sync = _get_class_by_entity(AIRTRIBUNE_CUSTOMOBJECT_TYPE, $customobject);
    $sync->synchronize();
  }
}

/**
 * Class for synchronization user
 */
class ATSyncUser extends ATSync {
  public function synchronize() {
    $profile = profile2_load_by_user($this->entity);
    $user_wrapper = entity_metadata_wrapper('user', $this->entity);
    if (empty($profile['main']) || empty($profile['pilot'])) {
      ATSync::setMessage('Core API: User has no profiles.');
      return FALSE;
    }
    if ($this->core_id) {
      return $this->core_id;
    }
    else {
      // Generate new person id, and save user.
      // During saving user will be synced with LDAP.
      $person_id = generate_person_id();
      // Save field values without saving user entity. This need to avoid recursion on hook_entity_update().
      $this->entity->field_core_id[LANGUAGE_NONE][0]['value'] = $person_id;
      field_attach_update('user', $this->entity);
      // Save entity, this is needed to run syncing user with LDAP. Function ATSyncUser->sync will be called one
      // more time, but in next time we already have core_id in entity, so no problems with recursion.
      $user_wrapper->save();
      return $person_id;
    }
  }
}

/**
 * Class for synchronization pilot
 */
abstract class ATSyncPilot extends ATSyncNestedInContest {
  public $core_id = '';
  public $tracker = NULL;
  public $person = NULL;
  public $phone = NULL;
  public $country = NULL;
  public $pilot = NULL;

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    $this->person = user_load($this->entity->etid, TRUE);
    $this->profile = profile2_load_by_user($this->person);
    $this->core_id = get_core_id_from_entity('user', $this->person);
    $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);
    $this->pilot = $entity_wrapper;
    $this->tracker = get_tracker($this->entity_type, $this->entity);
  }

  public function synchronize() {
    // Do not write to Core API, if status is not confirmed / winddummy.
    if (!in_array(
      $this->pilot->field_pg_contestant_status->value(),
      array(AIRTRIBUNE_PG_CONTESTANT_CONFIRMED, AIRTRIBUNE_PILOT_STATUS_WINDDUMMY)
    )) {
      return FALSE;
    }
    $entity_wrapper = entity_metadata_wrapper('og_membership', $this->entity);
    $pilot_wrapper = entity_metadata_wrapper('profile2', $this->profile['pilot']);
    if (!$this->core_id) {
      // Synchronize person if not synchronized
      $sync = _get_class_by_entity('user', $this->person);
      $this->core_id = $sync->synchronize();
    }
    $data = array(
      'id' => $this->core_id,
      'name' => get_full_name($this->person),
      'glider' => $entity_wrapper->field_paraglider_manufacturer->value(),
      'contest_number' => $entity_wrapper->field_contestant_number->value(),
      'phone' => get_phone($this->entity),
      'tracker' => $this->tracker,
      'country' => $pilot_wrapper->field_address->country->value(),
    );

    $this->address .= '/' . $this->core_id;
    $response = $this->request($data, "PUT");
    return !empty($response->id) ? $response->id : FALSE;
  }
}

/**
 * Class for synchronization winddummy
 */
class ATSyncWindDummy extends ATSyncPilot {
  public $address = 'winddummy';
}

/**
 * Class for synchronization glider
 */
class ATSyncGlider extends ATSyncPilot {
  public $address = 'paraglider';
}

/**
 * Class for synchronization day
 */
class ATSyncDay extends ATSyncNestedInContest {
  public $address = 'day';
  public $title = '';
  public $day_dmy = '';
  public $day_status = NULL;

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    $day_wrapper = entity_metadata_wrapper($entity_type, $entity);
    $contest_time = airtribune_extract_time_from_contest($this->contest);
    $day_timestamp = $this->entity->created;
    // Because datetime in fields set for local, but stored in database as UTC, we substract offset.
    $day_created_time = $day_timestamp - $contest_time['offset'];
    // Change address.
    $this->day_dmy = date("ymd", $day_created_time);
    $this->day_status = $day_wrapper->field_day_status->value();
    $this->address .= '/' . $this->day_dmy;
  }

  public function synchronize() {
    $data = array(
      'title' => $this->entity->title,
      'date' => $this->day_dmy,
      'status' => $this->day_status,
    );
    $response = $this->request($data, "PUT");
    return !empty($response->id) ? $response->id : FALSE;
  }
}

/**
 * Class for synchronization race
 */
class ATSyncRace extends ATSyncNestedInContest {
  public $address = 'race';

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
  }

  public function synchronize() {
    geophp_load();
    $time_zone = $this->contest->field_time_zone[LANGUAGE_NONE][0]['value'];
    $race_wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACE_ENTITY_TYPE, $this->entity);
    $racetype = $race_wrapper->field_pg_racetype_ref->value();
    if (!$racetype) {
      ATSync::setMessage('Race type is not specified, the race sync is stopped.', 'error');
      return FALSE;
    }
    $racetype_wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACETYPE_ENTITY_TYPE, $racetype);
    $title = 'Task ' . $race_wrapper->field_race_number->value();

    $race_time = $race_wrapper->field_race_start_end->value();
    $window_time = $race_wrapper->field_pg_race_window_open_close->value();
    $data['properties'] = array(
      'start_time' => strtotime($race_time['value'] . ' ' . $time_zone),
      'deadline' => strtotime($race_time['value2'] . ' ' . $time_zone),
      'window_open' => strtotime($window_time['value'] . ' ' . $time_zone),
      'window_close' => strtotime($window_time['value2'] . ' ' . $time_zone),
    );
    switch ($racetype->type) {
      case 'pg_racetype_rtg':
        $data['type'] = 'racetogoal';
        $data['properties'] += array(
          'gates_number' => $racetype_wrapper->field_pg_race_gates_number->value(),
          'gates_interval' => $racetype_wrapper->field_pg_race_gates_interval->value(),
        );
        break;

      case 'pg_racetype_od':
        $data['type'] = 'opendistance';
        if (isset($racetype_wrapper->field_pg_race_azimuth)) {
          $data['properties']['bearing'] = (int) $racetype_wrapper->field_pg_race_azimuth->value();
        }
        break;

      case 'pg_racetype_sr':
        $data['type'] = 'speedrun';
        break;
    }
    // Prepare checkpoints.
    $points = $racetype_wrapper->field_pg_race_points->value();
    $checkpoints['type'] = 'FeatureCollection';
    $checkpoints['features'] = array();
    $delta = 0;
    foreach ($points as $point) {
      $contest_point = entity_load_single(AIRTRIBUNE_CONTEST_POINT_ENTITY_TYPE, $point->field_point_ref[LANGUAGE_NONE][0]['target_id']);
      $wkt = $contest_point->field_point_location[LANGUAGE_NONE][0]['geom'];
      $geom = geoPHP::load($wkt);
      $coordinates = json_decode($geom->out('json'), TRUE);
      $point_data = array(
        'type' => 'Feature',
        'geometry' => $coordinates,
        'properties' => array(
          'name' => $contest_point->title,
          'radius' => (int) $point->field_point_radius[LANGUAGE_NONE][0]['value'],
          'checked_on' => $point->field_point_type[LANGUAGE_NONE][0]['value'],
          'checkpoint_type' => 'ordinal',
        )
      );
      if (!empty($point->field_point_ss_es[LANGUAGE_NONE][0]['value'])) {
        $point_data['properties']['checkpoint_type'] = $point->field_point_ss_es[LANGUAGE_NONE][0]['value'];
      }
      if ($delta == 0) {
        $point_data['properties'] += array(
          'checkpoint_type' => 'to',
          'open_time' => $data['properties']['window_open'],
          'close_time' => $data['properties']['window_close'],
        );
      }
      switch ($data['type']) {
        case 'speedrun':
        case 'racetogoal':
          if ($delta == count($points) - 1) {
            $point_data['properties']['checkpoint_type'] = 'goal';
            // Goal as Line
            if ($point->field_point_type[LANGUAGE_NONE][0]['value'] == 'line') {
              $point_data['geometry']['type'] = 'LineString';
              $tmp = $point_data['geometry']['coordinates'];
              $point_data['geometry']['coordinates'] = array($tmp, $tmp);
            }
          }
          if (in_array($point_data['properties']['checkpoint_type'], array('ss', 'es', 'goal'))) {
            $point_data['properties']['open_time'] = $data['properties']['start_time'];
            $point_data['properties']['close_time'] = $data['properties']['deadline'];
          }
          break;
        case 'opendistance':
          if (($delta == count($points) - 1) || in_array($point_data['properties']['checkpoint_type'], array('ss'))) {
            $point_data['properties']['open_time'] = $data['properties']['start_time'];
            $point_data['properties']['close_time'] = $data['properties']['deadline'];
          }
          break;
      }
      $delta++;
      $checkpoints['features'][] = $point_data;
    }
    // Request
    $data += array(
      'checkpoints' => $checkpoints,
      'title' => $title,
    );
    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request($data, "PUT");
    }
    else {
      $response = $this->request($data);
      if (!empty($response->id)) {
        $this->updateCoreID($response->id);
      }
    }
    // Write optimal distance to race.
    if (!empty(floatval($response->optdistance))) {
      $this->entity->field_optdistance[LANGUAGE_NONE][0]['value'] = $response->optdistance;
    } else {
      $this->entity->field_optdistance[LANGUAGE_NONE][0]['value'] = '';
    }
    field_attach_update($this->entity_type, $this->entity);
    return !empty($response->id) ? $response->id : FALSE;
  }

  public function pushTracks() {
    $race_wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACE_ENTITY_TYPE, $this->entity);
    if ($tracks = $race_wrapper->field_pg_race_tracks) {
      if ($this->core_id) {
        $this->address .= '/' . $this->core_id . '/track_archive';
        $file = $tracks->value();
        $data = array('url' => file_create_url($file['uri']));
        $response = $this->request($data);
      }
      else {
        ATSync::setMessage(t('Core API: Unable to send tracks. Race not synchronized yet.'));
        return FALSE;
      }
    }
  }
}

/**
 * Class for synchronization person
 */
class ATSyncTracker extends ATSync {
  public $address = 'tracker';
  public $device_id = '';
  public $tracker_type = '';

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    $wrapper = entity_metadata_wrapper(AIRTRIBUNE_TRACKER_TYPE, $entity);
    $field_tracker_type = $wrapper->field_tracker_type->value();
    $this->device_id = $wrapper->field_device_id->value();
    $this->device_type = $field_tracker_type->title;
  }
  public function synchronize() {
    $data = array(
      'device_id' => $this->device_id,
      'device_type' => $this->device_type,
      'name' => $this->entity->title,
    );

    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request($data, 'PUT');
    }
    else {
      $response = $this->request($data);
      $this->updateCoreID($response->id);
    }
    return !empty($response->id) ? $response->id : FALSE;
  }

  public function assignee($person_id = '') {
    $data = array(
      'owner' => $person_id,
    );
    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request($data, 'PATCH');
      return $response;
    }
    else {
      ATSync::setMessage(t('Core API: This tracker not synchronized yet.'));
      return FALSE;
    }
  }
}
