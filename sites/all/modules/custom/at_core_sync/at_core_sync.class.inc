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
    $this->core_id = get_id_from_entity($this->entity_type, $this->entity);
  }
  public static function requestToCore($address, $data = array(), $method = "POST") {
    $handle = curl_init();
    $url = at_core_sync_get_api_url() . '/' . $address;
    curl_setopt($handle, CURLOPT_URL, $url);
    curl_setopt($handle, CURLOPT_PORT, 80);
    curl_setopt($handle, CURLOPT_TIMEOUT, 30);
    curl_setopt($handle, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($handle, CURLOPT_SSL_VERIFYHOST, FALSE);
    curl_setopt($handle, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_setopt($handle, CURLOPT_HTTPHEADER, array('Expect:') );

    switch ($method) {
      case 'GET':
        break;

      case 'POST':
        curl_setopt($handle, CURLOPT_POST, TRUE);
        curl_setopt($handle, CURLOPT_POSTFIELDS, $data);
        break;

      case 'PUT':
        curl_setopt($handle, CURLOPT_CUSTOMREQUEST, 'PUT');
        curl_setopt($handle, CURLOPT_POSTFIELDS, $data);
        break;

      case 'DELETE':
        curl_setopt($handle, CURLOPT_CUSTOMREQUEST, 'DELETE');
        break;
    }
    $response = curl_exec($handle);
    $code = curl_getinfo($handle, CURLINFO_HTTP_CODE);
    switch ($code) {
      case 200:
        ATSync::setMessage(t("Core API: Request completed."));
        break;

      case 201:
        ATSync::setMessage(t("Core API: Resource is successfully created."));
        break;

      case 202:
        ATSync::setMessage(t("Core API: Request accepted."));
        break;

      case 400:
        ATSync::setMessage(t("Core API[400]: Request has error. Check fields and send again."), 'error');
        ATSync::setMessage(print_r($response, TRUE), 'error');
        break;

      case 401:
        ATSync::setMessage(t("Core API[401]: You need to auth before send this request."), 'error');
        break;

      case 403:
        ATSync::setMessage(t("Core API[403]: Requested operation not avaible."), 'error');
        break;

      case 404:
        ATSync::setMessage(t("Core API[404]: Resource not found, (!url)", array('!url' => l($url, $url))), 'error');
        ATSync::setMessage(print_r($response, TRUE), 'error');
        break;

      case 405:
        ATSync::setMessage(t("Core API[405]: Method <i>!method</i> is not allowed for resource !url.",array('!method' => $method, '!url' => l($url, $url))), 'error');
        break;

      case 409:
        ATSync::setMessage(t("Core API[409]: Conflict happened. See server response for details."), 'error');
        ATSync::setMessage(print_r($response, TRUE), 'error');
        break;

      case 500:
        ATSync::setMessage(t("Core API[500]: Format error or server restrictions."), 'error');
        ATSync::setMessage(print_r($response, TRUE), 'error');
        break;

      case 502:
      case 504:
        ATSync::setMessage(t("Core API is unreachable at (!url) (server error), request queued.", array('!url' => l($url, $url))), 'error');
        watchdog("at_core_sync", t("Core API is unreachable at (!url), request queued.", array('!url' => l($url, $url))));
        break;

      case 0:
        ATSync::setMessage(t("Core API is unreachable at (!url) (timeout), request queued.", array('!url' => l($url, $url))), 'error');
        watchdog("at_core_sync", t("Core API is unreachable at (!url), request queued.", array('!url' => l($url, $url))));
        break;

      default:
        ATSync::setMessage(t("Core API: unknown response. Mechod <i>!method</i>, resource !url.", array('!method' => $method, '!url' => l($url, $url))), 'warning');
        watchdog("at_core_sync", t("Core API: unknown response. Code !code, mechod <i>!method</i>, resource !url.", array('!method' => $method, '!url' => l($url, $url), '!code' => $code)), array(), WATCHDOG_WARNING);
        break;
    }
    return json_decode($response);
  }

  public function request($data, $method = "POST") {
    return ATSync::requestToCore($this->address, $data, $method);    
  }

  public function updateCoreID($id) {
    $this->entity->field_core_id = array(
      "und" => array(
        array(
          "value" => $id,
        ),
      ),
    );
    field_attach_update($this->entity_type, $this->entity);
    $this->core_id = $id;
  }

  public function setMessage($message = NULL, $type = 'status', $repeat = TRUE) {
    if (user_access('administer site configuration')) {
      drupal_set_message($message, $type, $repeat);
    }
  }

  abstract public function synchronize();
  abstract public function check();
  
}

/**
 * Class for synchronization pg_contest
 */
class ATSyncContest extends ATSync {
  public $address = "contest";
  public function synchronize() {
    $node = $this->entity;
    $data = array(
      'hq_coords' => $node->field_hq_location['und'][0]['lat'] . ',' . $node->field_hq_location['und'][0]['lon'],
      'title' => $node->title,
      'start_time' => strtotime($node->field_dates['und'][0]['value']),
      'end_time' => strtotime($node->field_dates['und'][0]['value2']),
      'place' => $node->field_city['und'][0]['value'],
      'country' => $node->field_country['und'][0]['iso2'],
      'timezone' => $node->field_time_zone['und'][0]['value'],
      'retrieve_id' => $node->field_device_id['und'][0]['value'],
    );
    if ($this->core_id) {
      // change address if contest already in Core
      $this->address .= '/' . $this->core_id;
      $response = $this->request(json_encode($data), "PUT");
    }
    else {
      $response = $this->request(http_build_query($data));
      $this->updateCoreID($response->id);
    }
    return !empty($response->id) ? $response->id : FALSE;
  }

  public function check() {
  }
}

/**
 * Class for synchronization custom_object (transport) see #3446
 */
class ATSyncCustom extends ATSync {
  public $address = "transport";
  public function synchronize() {
    $description_field = $this->entity->field_plain_body;
    $description_field = array_pop($description_field);
    $description = isset($description_field[0]['value']) ? $description_field[0]['value'] : '';
    $data = array(
      'type' => $this->entity->field_customobject_type[LANGUAGE_NONE][0]['value'],
      'title' => $this->entity->title,
      'description' => $description,
    );

    if ($this->core_id) {
      // change address if contest already in Core
      $this->address .= '/' . $this->core_id;
      $response = $this->request(json_encode($data), "PUT");
    }
    else {
      $response = $this->request(http_build_query($data));
      $this->updateCoreID($response->id);
    }
    return !empty($response->id) ? $response->id : FALSE;
  }

  public function check() {
  }
}

class ATSyncTrackedObject extends ATSync {
  public $address = "contest/";
  public $tracked_core_id = '';
  public $contest = NULL;
  public $contest_core_id = '';
  public $tracker = NULL;
  public $person = NULL;

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    $this->contest = node_load($this->entity->gid, NULL, TRUE);
    $this->core_id = get_id_from_entity('tracked_object', $this->entity);
    $this->contest_core_id = get_id_from_entity('node', $this->contest);
    $this->transport = array_pop(entity_load('ent_customobject', array($this->entity->etid), array(), TRUE));
    $this->tracked_core_id = get_id_from_entity('ent_customobject', $this->transport);
    $tracker_eid = FALSE;
    if(isset($this->entity->field_tracker[LANGUAGE_NONE][0]['target_id'])) {
      $tracker_eid = $this->entity->field_tracker[LANGUAGE_NONE][0]['target_id'];
      if ($tracker_eid) {
        $this->tracker = array_pop(entity_load('ent_tracker', array($tracker_eid), array(), TRUE));
      }
    }
  }

  public function synchronize() {
    if (!$this->contest_core_id) {
      // Synchronize contest if not synchronized
      $sync = _get_class_by_entity('node', $this->contest);
      $this->contest_core_id = $sync->synchronize();
    }
    if (!$this->tracked_core_id) {
      // Synchronize person if not synchronized
      $sync = _get_class_by_entity('ent_customobject', $this->transport);
      $this->tracked_core_id = $sync->synchronize();
    } else {
      $resp = ATSync::requestToCore('transport/' . $this->tracked_core_id, '', 'GET');
      if (isset($resp->error)) {
        ATSync::setMessage($resp->error . '. ' . $resp->message, 'error');
        return FALSE;
      }
    }
    $this->address = implode('/', array('contest', $this->contest_core_id, 'transport'));
    $data = array(
      'transport_id' => $this->tracked_core_id,
    );
    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request(json_encode($data), "PUT");
    }
    else {
      $response = $this->request(http_build_query($data));
    }
    return !empty($response->id) ? $response->id : FALSE;
  }

  public function check() {
  }
}

/**
 * Class for synchronization person
 */
class ATSyncPerson extends ATSync {
  public $address = "person";
  public function synchronize() {
    $profile2 = profile2_load_by_user($this->entity);
    if (!isset($profile2['pilot'])) {
      ATSync::setMessage("Core API: User is not a pilot, no need to synchronize");
      return FALSE;
    }

    $data = array(
      'name' => $profile2['main']->field_full_name[LANGUAGE_NONE][0]['given'],
      'surname' => $profile2['main']->field_full_name[LANGUAGE_NONE][0]['family'],
      'country' => $profile2['pilot']->field_address[LANGUAGE_NONE][0]['country'],
      'email' => $this->entity->mail,
      'reg_date' => date("Y,m,d", $this->entity->created),
    );

    if (!empty($this->entity->field_phone[LANGUAGE_NONE][0]['number'])) {
      $full_number = '';
      $number = $this->entity->field_phone[LANGUAGE_NONE][0]['number'];
      $countrycode = $this->entity->field_phone[LANGUAGE_NONE][0]['country_codes'];
      $cc = cck_phone_countrycodes();
        $full_number = '';
        if ($countrycode && isset($cc[$countrycode])) {
          $full_number = $cc[$countrycode]['code'] . $number;
      }
      $data['phone'] = $full_number;
    }
    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request(json_encode($data), "PUT");
    }
    else {
      $response = $this->request(http_build_query($data));
      $this->updateCoreID($response->id);
    }
    return !empty($response->id) ? $response->id : FALSE;
  }

  public function check() {
  }
}

/**
 * Class for synchronization pilot
 */
class ATSyncPilot extends ATSync {
  public $address = "contest/";
  public $person_core_id = '';
  public $contest = NULL;
  public $contest_core_id = '';
  public $tracker = NULL;
  public $person = NULL;

  public function __construct($entity_type, $entity) {
    parent::__construct($entity_type, $entity);
    $this->contest = node_load($this->entity->gid, NULL, TRUE);
    $this->contest_core_id = get_id_from_entity('node', $this->contest);
    $this->person = user_load($this->entity->etid, TRUE);
    $this->tracked_core_id = get_id_from_entity('user', $this->person);
    $tracker_eid = $this->entity->field_tracker[LANGUAGE_NONE][0]['target_id'];
    if ($tracker_eid) {
      $this->tracker = array_pop(entity_load('ent_tracker', array($tracker_eid), array(), TRUE));
    }
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
    } else {
      $resp = ATSync::requestToCore('person/' . $this->tracked_core_id, '', 'GET');
      if (isset($resp->error)) {
        ATSync::setMessage($resp->error . '. ' . $resp->message, 'error');
        return FALSE;
      }
      // Synchronize person for save phone
      $sync = _get_class_by_entity('user', $this->person);
      $this->tracked_core_id = $sync->synchronize();
    }
    $this->address = implode('/', array('contest', $this->contest_core_id, 'paraglider'));
    $data = array(
      'person_id' => $this->tracked_core_id,
      'glider' => $this->entity->field_paraglider_manufacturer[LANGUAGE_NONE][0]['value'],
      'contest_number' => $this->entity->field_contestant_number[LANGUAGE_NONE][0]['value'],
    );

    $this->core_id = FALSE;
    // Check paraglider resource
    /*
    $resp = ATSync::requestToCore($this->address . '/' . $this->person_core_id, '', 'GET');
    if (isset($resp->id)) {
      $this->core_id = $resp->id;
    }
    */
    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request(json_encode($data), "PUT");
    }
    else {
      $response = $this->request(http_build_query($data));
    }
    return !empty($response->id) ? $response->id : FALSE;
  }

  public function check() {
  }
}

/**
 * Class for synchronization race
 */
class ATSyncRace extends ATSync {
  public $address = "contest/";
  public function synchronize() {
    geophp_load();
    $day_id = $this->entity->field_day_ref[LANGUAGE_NONE][0]['target_id'];
    $contest_nid = $this->entity->og_group_ref[LANGUAGE_NONE][0]['target_id'];
    $contest = node_load($contest_nid, NULL, TRUE);
    if (!$contest) {
      ATSync::setMessage(t('ATSyncRace: Unable to load contest'));
      return FALSE;
    }
    $time_zone = $contest->field_time_zone[LANGUAGE_NONE][0]['value'];

    $contest_core_id = get_id_from_entity('node', $contest);
    if (!$contest_core_id) {
      ATSync::setMessage(t("Core API: Contest not synchronized yet."));
      return FALSE;
    }

    $this->address = implode('/', array('contest', $contest_core_id, 'race'));

    $data = array(
      'title' => $this->entity->title,
    );
    $data['start_time'] = strtotime($this->entity->field_race_start_end[LANGUAGE_NONE][0]['value'] . ' ' . $time_zone);
    $data['end_time'] = strtotime($this->entity->field_race_start_end[LANGUAGE_NONE][0]['value2'] . ' ' . $time_zone);
    $window_time['open_time'] = strtotime($this->entity->field_pg_race_window_open_close[LANGUAGE_NONE][0]['value'] . ' ' . $time_zone);
    $window_time['close_time'] = strtotime($this->entity->field_pg_race_window_open_close[LANGUAGE_NONE][0]['value2'] . ' ' . $time_zone);
    $racetype_ref = $this->entity->field_pg_racetype_ref[LANGUAGE_NONE][0]['target_id'];
    $racetype = array_pop(entity_load('ent_racetype', array($racetype_ref), array(), TRUE));
    switch ($racetype->type) {
      case "pg_racetype_rtg":
        $data['race_type'] = 'racetogoal';
        break;

      case "pg_racetype_od":
        $data['race_type'] = 'opendistance';
        $data['bearing'] = $racetype->field_pg_race_azimuth[LANGUAGE_NONE][0]['value'];
        break;

      case "pg_racetype_sr":
        $data['race_type'] = 'speedrun';
        break;
    }
    $point_ref = array();
    foreach ($racetype->field_pg_race_points[LANGUAGE_NONE] as $pref) {
      $point_ref[] = $pref['target_id'];
    }
    $points = entity_load("ent_point", $point_ref, array(), TRUE);
    $checkpoints = array();
    $checkpoints['type'] = "FeatureCollection";
    $checkpoints['features'] = array();
    $delta = 0;
    foreach ($points as $point) {
      $point_data = array();
      $point_data['type'] = 'Feature';
      $point_data['geometry'] = array();
      $contest_point_ref = $point->field_point_ref[LANGUAGE_NONE][0]['target_id'];
      $contest_point = array_pop(entity_load('ent_contest_point', array($contest_point_ref), array(), TRUE));
      $wkt = $contest_point->field_point_location[LANGUAGE_NONE][0]['geom'];
      $geom = geoPHP::load($wkt);
      $coordinates = json_decode($geom->out('json'), true);
      /**
       * Reverse lat an lon
       * @see Issue #3031-48
       */
      $coordinates['coordinates'] = array_reverse($coordinates['coordinates']);
      $point_data['geometry']= $coordinates;
      $point_data['properties'] = array();
      $point_data['properties']['radius'] = $point->field_point_radius[LANGUAGE_NONE][0]['value'];
      $point_data['properties']['name'] = $contest_point->title;

      if ($point->field_point_type[LANGUAGE_NONE][0]['value'] == 'exit') {
        $point_data['properties']['checked_on'] = $point->field_point_type[LANGUAGE_NONE][0]['value'];
      }

      $point_data['properties']['checkpoint_type'] = "ordinal";
      if (!empty($point->field_point_ss_es[LANGUAGE_NONE][0]['value'])) {
        $point_data['properties']['checkpoint_type'] = $point->field_point_ss_es[LANGUAGE_NONE][0]['value'];
      }
      if ($delta == 0) {
        $point_data['properties']['checkpoint_type'] = "to";
        $point_data['properties']['open_time'] = $window_time['open_time'];
        $point_data['properties']['close_time'] = $window_time['close_time'];
      }
      switch ($data['race_type']) {
        case "speedrun":
        case "racetogoal":
          if ($delta == count($points) - 1) {
            $point_data['properties']['checkpoint_type'] = "goal";

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

        case "opendistance":
          // @TODO: rules for open distance
          break;
      }
      $delta++;
      $checkpoints['features'][] = $point_data;
    }
    $data_url = http_build_query($data);
    $data_url .= '&checkpoints=' . json_encode($checkpoints);
    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $edit = array(
        "title" => $this->entity->title,
        "checkpoints" => $checkpoints,
      );
      $response = $this->request(json_encode($edit), "PUT");
    } else {
      $response = $this->request($data_url);
      if (!empty($response->id)) {
        $this->updateCoreID($response->id);
      }
    }
    if (!empty($response->id)) {
      return $response->id; 
    } else {
      return FALSE;
    }
  }

  public function pushTracks() {
    $fid = !empty($this->entity->field_pg_race_tracks[LANGUAGE_NONE][0]['fid']) ? $this->entity->field_pg_race_tracks[LANGUAGE_NONE][0]['fid'] : FALSE;
    if ($fid) {
      $contest_nid = $this->entity->og_group_ref[LANGUAGE_NONE][0]['target_id'];
      $contest = node_load($contest_nid, NULL, TRUE);
      if (!$contest) {
        ATSync::setMessage(t('ATSyncRace: Unable to load contest'));
        return FALSE;
      }
      $time_zone = $contest->field_time_zone[LANGUAGE_NONE][0]['value'];
      get_id_from_entity($this->entity);
      $contest_core_id = get_id_from_entity('node', $contest);
      if (!$contest_core_id) {
        ATSync::setMessage(t("Core API: Contest not synchronized yet."));
        return FALSE;
      }

      $this->address = implode('/', array('contest', $contest_core_id, 'race'));
      if ($this->core_id) {
        $this->address = implode('/', array('contest', $contest_core_id, 'race', $this->core_id, 'track_archive'));
        $response = $this->request('url='.file_create_url(file_load($fid)->uri));
      } else {
        ATSync::setMessage(t("Core API: Unable to send tracks. Race not synchronized yet."));
        return FALSE;
      }
    }
  }

  public function check() {
  }
}

/**
 * Class for synchronization person
 */
class ATSyncTracker extends ATSync {
  public $address = "tracker";
  public function synchronize() {
    $wrapper = entity_metadata_wrapper('ent_tracker', $this->entity);
    $field = $wrapper->field_tracker_type->value();
    $device_type =  $field->title;
    $data = array(
      'device_id' => $this->entity->identifier,
      'device_type' => $device_type,
      'name' => $this->entity->title,
    );

    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $data_update['name'] = $data['name'];
      $response = $this->request(json_encode($data_update), 'PUT');
    } else {
      $response = $this->request(http_build_query($data));
      $this->updateCoreID($response->id);
    }
    return !empty($response->id) ? $response->id : FALSE;
  }

  public function assignee($person_id = '', $contest_id = '') {
    $data = array(
      'name' => $this->entity->title,
      'assignee' => $person_id,
      'contest_id' => $contest_id,
    );
    if ($this->core_id) {
      $this->address .= '/' . $this->core_id;
      $response = $this->request(json_encode($data), 'PUT');
    }
    return $response;
  }

  public function check() {
  }
}
