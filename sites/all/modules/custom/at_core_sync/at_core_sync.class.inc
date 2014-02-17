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

  public function __construct($entity_type, $entity) {
    $this->entity = $entity;
    $this->entity_type = $entity_type;
    $this->core_id = get_core_id_from_entity($entity_type, $entity);
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
    if ($this->core_id) {
      return ATSync::requestToCore($this->address . '/' . $this->core_id, array(), 'DELETE');
    }
  }

  public function updateCoreID($id) {
    $this->entity->field_core_id = array(
      LANGUAGE_NONE => array(
        array(
          'value' => $id,
        ),
      ),
    );
    field_attach_update($this->entity_type, $this->entity);
    $this->core_id = $id;
  }

  public static function setMessage($message = NULL, $type = 'status', $repeat = TRUE) {
    if (user_access('administer site configuration')) {
      drupal_set_message($message, $type, $repeat);
    }
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
      $this->updateCoreID($response->id);
    }

    _asd($data, $this->address, $response);

    return !empty($response->id) ? $response->id : FALSE;
  }
}

/**
 * Intermediate class for all nested entities in contest by Core API entities ( by path http://api/contest/{id}/* )
 */
abstract class ATSyncNestedInContest extends ATSync {
  public $contest = NULL;
  public $contest_core_id = '';
  public $address_contest = 'contest/';

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    $this->contest = get_contest_for_entity($entity);
    $this->contest_core_id = get_core_id_from_entity('node', $this->contest);
    if (!$this->contest_core_id) {
      // Synchronize contest if not synchronized
      $sync = _get_class_by_entity('node', $this->contest);
      $this->contest_core_id = $sync->synchronize();
    }
    $this->address_contest .= $this->contest_core_id . '/';
  }
}

/**
 * Class for synchronization custom object
 */
class ATSyncCustom extends ATSyncNestedInContest {
  public $address = 'staff';
  public $name = '';
  public $type = '';
  public $phone = '';
  public $description = '';

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);
    // Load membership.
    $og_group_ref = $entity_wrapper->{OG_AUDIENCE_FIELD}[0]->raw();
    $og_membership = og_get_membership('node', $og_group_ref, AIRTRIBUNE_CUSTOMOBJECT_TYPE, $this->entity->id);
    $ogm_wrapper = entity_metadata_wrapper('og_membership', $og_membership);
    // Get values.
    $this->name = $entity->title;
    $tracker = $ogm_wrapper->field_tracker->value();
    // todo check phone & tracker for empty valies
    $this->tracker = $tracker ? $tracker : '-';
    $this->phone = ($phone = get_phone($og_membership)) ? $phone : '+000000';
    $this->type = $entity_wrapper->field_customobject_type->value();
    $description = $entity_wrapper->field_plain_body->value();
    $this->description = $description ? $description['value'] : '';
    // Change address.
    $this->address = $this->address_contest . $this->address;
  }

  public function synchronize() {
    $data = array(
      'name' => $this->name,
      'type' => $this->type,
      'phone' => $this->phone,
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
    _asd($data, $this->address, $response);
    return !empty($response->id) ? $response->id : FALSE;
  }
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
 * Class for synchronization person
 */
class ATSyncPerson extends ATSync {
  public $address = 'person';

  public function synchronize() {
    $profile2 = profile2_load_by_user($this->entity);
    if (!isset($profile2['pilot'])) {
      ATSync::setMessage('Core API: User is not a pilot, no need to synchronize');
      return FALSE;
    }

    $data = array(
      'name' => $profile2['main']->field_full_name[LANGUAGE_NONE][0]['given'],
      'surname' => $profile2['main']->field_full_name[LANGUAGE_NONE][0]['family'],
      'country' => $profile2['pilot']->field_address[LANGUAGE_NONE][0]['country'],
      'email' => $this->entity->mail,
      'reg_date' => date('Y,m,d', $this->entity->created),
      'phone' => get_phone($profile2['pilot']),
    );

    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request($data, "PUT");
    }
    else {
      $response = $this->request($data);
      $this->updateCoreID($response->id);
    }

    _asd($data, $this->address, $response);

    return !empty($response->id) ? $response->id : FALSE;
  }
}

/**
 * Class for synchronization pilot
 */
class ATSyncPilot extends ATSyncNestedInContest {
  public $address = 'paraglider';
  public $core_id = '';
  public $tracker = NULL;
  public $person = NULL;
  public $phone = NULL;
  public $country = NULL;

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    $this->person = user_load($this->entity->etid, TRUE);
    $this->profile = profile2_load_by_user($this->person);
    $this->core_id = get_core_id_from_entity('user', $this->person);
    $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);
    $this->tracker = $entity_wrapper->field_tracker->value();
    $this->address = $this->address_contest . $this->address;
  }

  public function synchronize() {
    $entity_wrapper = entity_metadata_wrapper('og_membership', $this->entity);
    $pilot_wrapper = entity_metadata_wrapper('profile2', $this->profile['pilot']);
    // Send only if status is confirmed
    if ($entity_wrapper->field_pg_contestant_status->value() != AIRTRIBUNE_PG_CONTESTANT_CONFIRMED) {
      // todo remove from cores if not conf
        return FALSE;
    }
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
      'country' => $pilot_wrapper->field_address->country->value(),
    );

    $this->address .= '/' . $this->core_id;
    $response = $this->request($data, "PUT");

    _asd($data, $this->address, $response);
    return !empty($response->id) ? $response->id : FALSE;
  }
}

/**
 * Class for synchronization winddummy
 */
class ATSyncWindDummy extends ATSync {
  public $address = 'contest/';
  public $person_core_id = '';
  public $contest = NULL;
  public $contest_core_id = '';
  public $tracker = NULL;
  public $person = NULL;

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    $this->contest = node_load($this->entity->gid, NULL, TRUE);
    $this->contest_core_id = get_core_id_from_entity('node', $this->contest);
    $this->person = user_load($this->entity->etid, TRUE);
    $this->tracked_core_id = get_core_id_from_entity('user', $this->person);
    $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);
    $this->tracker = $entity_wrapper->field_tracker->value();
  }

  public function synchronize() {
    // Send only if status is confirmed
    if ($this->entity->field_pg_contestant_status[LANGUAGE_NONE][0]['value'] != 4) {
      return FALSE;
    }
    if (!$this->contest_core_id) {
      // Synchronize contest if not synchronized
      $sync = _get_class_by_entity('node', $this->contest);
      $this->contest_core_id = $sync->synchronize();
    }
    $this->person->field_phone = $this->entity->field_phone;
    if (!$this->tracked_core_id) {
      // Synchronize person if not synchronized
      $sync = _get_class_by_entity('user', $this->person);
      $this->tracked_core_id = $sync->synchronize();
    }
    else {
      $resp = ATSync::requestToCore('person/' . $this->tracked_core_id, '', 'GET');
      if (isset($resp->error)) {
        ATSync::setMessage($resp->error . '. ' . $resp->message, 'error');
        return FALSE;
      }
      // Synchronize person for save phone
      $sync = _get_class_by_entity('user', $this->person);
      $this->tracked_core_id = $sync->synchronize();
    }
    $this->address = implode('/', array('contest', $this->contest_core_id, 'winddummy'));
    $data = array(
      'person_id' => $this->tracked_core_id,
      'glider' => $this->entity->field_paraglider_manufacturer[LANGUAGE_NONE][0]['value'],
      'contest_number' => $this->entity->field_contestant_number[LANGUAGE_NONE][0]['value'],
    );

    $this->core_id = FALSE;
    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request($data, "PUT");
    }
    else {
      $response = $this->request($data);
    }

    _asd($data, $this->address, $response);

    return !empty($response->id) ? $response->id : FALSE;
  }
}

// todo day delete
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
    $this->address = $this->address_contest . $this->address . '/' . $this->day_dmy;
  }

  public function synchronize() {
    $data = array(
      'title' => $this->entity->title,
      'date' => $this->day_dmy,
      'status' => $this->day_status,
    );
    $response = $this->request($data, "PUT");
    _asd($data, $this->address, $response);
    return !empty($response->id) ? $response->id : FALSE;
  }
}

/**
 * Class for synchronization race
 */
class ATSyncRace extends ATSync {
  public $address = 'contest/';

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    $gid = _airtribune_get_gid($entity_type, $entity);
    $this->contest = node_load($gid, NULL, TRUE);
    $this->contest_core_id = get_core_id_from_entity('node', $this->contest);
  }

  public function synchronize() {
    geophp_load();
    $day_id = $this->entity->field_day_ref[LANGUAGE_NONE][0]['target_id'];
    if (!isset($this->contest)) {
      ATSync::setMessage(t('ATSyncRace: Unable to load contest'));
      return FALSE;
    }
    $time_zone = $this->contest->field_time_zone[LANGUAGE_NONE][0]['value'];

    if (!$this->contest_core_id) {
      ATSync::setMessage(t('Core API: Contest not synchronized yet.'));
      return FALSE;
    }

    $this->address = implode('/', array('contest', $this->contest_core_id, 'race'));
    $title = 'Task ' . $this->entity->field_race_number[LANGUAGE_NONE][0]['value'];
    $data = array(
      //'title' => $this->entity->title,
      'title' => $title,
    );
    $data['start_time'] = strtotime($this->entity->field_race_start_end[LANGUAGE_NONE][0]['value'] . ' ' . $time_zone);
    $data['end_time'] = strtotime($this->entity->field_race_start_end[LANGUAGE_NONE][0]['value2'] . ' ' . $time_zone);
    $window_time['open_time'] = strtotime($this->entity->field_pg_race_window_open_close[LANGUAGE_NONE][0]['value'] . ' ' . $time_zone);
    $window_time['close_time'] = strtotime($this->entity->field_pg_race_window_open_close[LANGUAGE_NONE][0]['value2'] . ' ' . $time_zone);
    $racetype_ref = $this->entity->field_pg_racetype_ref[LANGUAGE_NONE][0]['target_id'];
    $racetype = array_pop(entity_load(AIRTRIBUNE_RACETYPE_ENTITY_TYPE, array($racetype_ref), array(), TRUE));
    switch ($racetype->type) {
      case 'pg_racetype_rtg':
        $data['race_type'] = 'racetogoal';
        break;

      case 'pg_racetype_od':
        $data['race_type'] = 'opendistance';
        if (isset($racetype->field_pg_race_azimuth[LANGUAGE_NONE][0]['value']) && is_numeric($racetype->field_pg_race_azimuth[LANGUAGE_NONE][0]['value'])) {
          $data['bearing'] = $racetype->field_pg_race_azimuth[LANGUAGE_NONE][0]['value'];
        }
        break;

      case 'pg_racetype_sr':
        $data['race_type'] = 'speedrun';
        break;
    }
    $point_ref = array();
    foreach ($racetype->field_pg_race_points[LANGUAGE_NONE] as $pref) {
      $point_ref[] = $pref['target_id'];
    }
    $points = entity_load(AIRTRIBUNE_POINT_ENTITY_TYPE, $point_ref, array(), TRUE);
    $checkpoints = array();
    $checkpoints['type'] = 'FeatureCollection';
    $checkpoints['features'] = array();
    $delta = 0;
    foreach ($points as $point) {
      $point_data = array();
      $point_data['type'] = 'Feature';
      $point_data['geometry'] = array();
      $contest_point_ref = $point->field_point_ref[LANGUAGE_NONE][0]['target_id'];
      $contest_point = array_pop(entity_load(AIRTRIBUNE_CONTEST_POINT_ENTITY_TYPE, array($contest_point_ref), array(), TRUE));
      $wkt = $contest_point->field_point_location[LANGUAGE_NONE][0]['geom'];
      $geom = geoPHP::load($wkt);
      $coordinates = json_decode($geom->out('json'), TRUE);

      $point_data['geometry'] = $coordinates;
      $point_data['properties'] = array();
      $point_data['properties']['radius'] = $point->field_point_radius[LANGUAGE_NONE][0]['value'];
      $point_data['properties']['name'] = $contest_point->title;

      if ($point->field_point_type[LANGUAGE_NONE][0]['value'] == 'exit') {
        $point_data['properties']['checked_on'] = $point->field_point_type[LANGUAGE_NONE][0]['value'];
      }

      $point_data['properties']['checkpoint_type'] = 'ordinal';
      if (!empty($point->field_point_ss_es[LANGUAGE_NONE][0]['value'])) {
        $point_data['properties']['checkpoint_type'] = $point->field_point_ss_es[LANGUAGE_NONE][0]['value'];
      }
      if ($delta == 0) {
        $point_data['properties']['checkpoint_type'] = 'to';
        $point_data['properties']['open_time'] = $window_time['open_time'];
        $point_data['properties']['close_time'] = $window_time['close_time'];
      }
      switch ($data['race_type']) {
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
            $point_data['properties']['open_time'] = $data['start_time'];
            $point_data['properties']['close_time'] = $data['end_time'];
          }

          break;

        case 'opendistance':
          if (($delta == count($points) - 1) || in_array($point_data['properties']['checkpoint_type'], array('ss'))) {
            $point_data['properties']['open_time'] = $data['start_time'];
            $point_data['properties']['close_time'] = $data['end_time'];
          }
          break;
      }
      $delta++;
      $checkpoints['features'][] = $point_data;
    }
    $data_url = $data;
    $data_url .= '&checkpoints=' . json_encode($checkpoints);
    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $edit = array(
        'title' => $title,
        'checkpoints' => $checkpoints,
      );
      $response = $this->request(json_encode($edit), "PUT");
    }
    else {
      $response = $this->request($data_url);
      if (!empty($response->id)) {
        $this->updateCoreID($response->id);
      }
    }

    _asd(json_encode($data_url), $this->address, $response);

    if (!empty($response->id)) {
      return $response->id;
    }
    else {
      return FALSE;
    }
  }

  public function pushTracks() {
    $fid = !empty($this->entity->field_pg_race_tracks[LANGUAGE_NONE][0]['fid']) ? $this->entity->field_pg_race_tracks[LANGUAGE_NONE][0]['fid'] : FALSE;
    if ($fid) {
      if (!$this->contest) {
        ATSync::setMessage(t('ATSyncRace: Unable to load contest'));
        return FALSE;
      }
      $time_zone = $this->contest->field_time_zone[LANGUAGE_NONE][0]['value'];
      if (!$this->contest_core_id) {
        ATSync::setMessage(t('Core API: Contest not synchronized yet.'));
        return FALSE;
      }

      $this->address = implode('/', array('contest', $this->contest_core_id, 'race'));
      if ($this->core_id) {
        $this->address = implode('/', array(
          'contest',
          $this->contest_core_id,
          'race',
          $this->core_id,
          'track_archive'
        ));
        $url = 'url=' . file_create_url(file_load($fid)->uri);
        $response = $this->request($url);
        _asd($url, $this->address, $response);
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

  public function synchronize() {
    $wrapper = entity_metadata_wrapper(AIRTRIBUNE_TRACKER_TYPE, $this->entity);
    $field_tracker_type = $wrapper->field_tracker_type->value();
    $field_device_id = $wrapper->field_device_id->value();
    $device_type = $field_tracker_type->title;
    $data = array(
      'device_id' => $field_device_id,
      'device_type' => $device_type,
      'name' => $this->entity->title,
    );

    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $data_update['name'] = $data['name'];
      $response = $this->request($data_update, 'PUT');
    }
    else {
      $response = $this->request($data);
      $this->updateCoreID($response->id);
    }
    _asd($data, $this->address, $response);
    return !empty($response->id) ? $response->id : FALSE;
  }

  public function assignee($person_id = '', $contest_id = '') {
    $response = FALSE;
    $data = array(
      'name' => $this->entity->title,
      'assignee' => $person_id,
      'contest_id' => $contest_id,
    );
    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request($data, 'PUT');
      _asd($data, $this->address, $response);
    }
    return $response;
  }
}
