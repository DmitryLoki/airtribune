<?php

/**
 * Abstract class with commin synchronisation functions
 */
abstract class ATSync {
  public $entity;
  public $entity_type;
  public $id = FALSE;
  public $address = FALSE;
  public function __construct($entity, $entity_type) {
    $this->entity = $entity;
    $this->entity_type = $entity_type;
  }
  public static function requestToCore($address, $data = array(), $method = "POST") {
    $handle = curl_init();
    $url = at_core_sync_get_api_url() . '/' . $address;
    curl_setopt($handle, CURLOPT_URL, $url);
    curl_setopt($handle, CURLOPT_PORT, 80);
    curl_setopt($handle, CURLOPT_TIMEOUT, 5);
    curl_setopt($handle, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($handle, CURLOPT_SSL_VERIFYHOST, FALSE);
    curl_setopt($handle, CURLOPT_SSL_VERIFYPEER, FALSE);

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
        drupal_set_message(t("Core API: Request completed."));
        break;

      case 201:
        drupal_set_message(t("Core API: Resource is successfully created."));
        break;

      case 202:
        drupal_set_message(t("Core API: Request accepted."));
        break;

      case 400:
        drupal_set_message(t("Core API[400]: Request has error. Check fields and send again."), 'error');
        drupal_set_message(print_r($response, TRUE), 'error');
        break;

      case 401:
        drupal_set_message(t("Core API[401]: You need to auth before send this request."), 'error');
        break;

      case 403:
        drupal_set_message(t("Core API[403]: Requested operation not avaible."), 'error');
        break;

      case 404:
        drupal_set_message(t("Core API[404]: Resource not found, (!url)", array('!url' => l($url, $url))), 'error');
        break;

      case 409:
        drupal_set_message(t("Core API[409]: Conflict happened. See server response for details."), 'error');
        drupal_set_message(print_r($response, TRUE), 'error');
        break;

      case 500:
        drupal_set_message(t("Core API[500]: Format error or server restrictions."), 'error');
        drupal_set_message(print_r($response, TRUE), 'error');
        break;

      case 502:
      case 504:
      case 0:
        drupal_set_message(t("Core API is unreachable at (!url), request queued.", array('!url' => l($url, $url))), 'error');
        watchdog("at_core_sync", t("Core API is unreachable at (!url), request queued.", array('!url' => l($url, $url))));
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
    $core_id = get_id_from_contest($node);
    // change address if contest already in Core
    if ($core_id) {
      $this->address .= '/' . $core_id;
    }
    $data = array(
      'hq_coords' => $node->field_hq_location['und'][0]['lat'] . ',' . $node->field_hq_location['und'][0]['lon'],
      'title' => $node->title,
      'start_time' => strtotime($node->field_dates['und'][0]['value']),
      'end_time' => strtotime($node->field_dates['und'][0]['value2']),
      'place' => $node->field_city['und'][0]['value'],
      'country' => $node->field_country['und'][0]['iso2'],
      'timezone' => $node->field_dates['und'][0]['timezone'],
    );
    if ($core_id) {
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
 * Class for synchronization person
 */
class ATSyncPerson extends ATSync {
  public $address = "person";
  public function synchronize() {
    $profile2 = profile2_load_by_user($this->entity);
    if (!isset($profile2['pilot'])) {
      drupal_set_message("Core API: User is not a pilot, no need to synchronize");
      return FALSE;
    }
    $core_id = get_id_from_user($this->entity);
    if ($core_id) {
      $this->address = implode('/', array('person', $core_id));
    }
    $data = array(
      'name' => $profile2['main']->field_full_name[LANGUAGE_NONE][0]['given'],
      'surname' => $profile2['main']->field_full_name[LANGUAGE_NONE][0]['family'],
      'country' => $profile2['pilot']->field_address[LANGUAGE_NONE][0]['country'],
      'email' => $this->entity->mail,
      'reg_date' => date("Y,m,d", $this->entity->created),
    );
    if ($core_id) {
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
  public function synchronize() {
    // Send only if status is confirmed
    if ($this->entity->field_pg_contestant_status[LANGUAGE_NONE][0]['value'] != 4) {
      return FALSE;
    }
    $contest = node_load($this->entity->gid);
    $contest_core_id = get_id_from_contest($contest);
    if (!$contest_core_id) {
      // Synchronize contest if not synchronized
      $sync = _get_class_by_entity($contest, 'node');
      $contest_core_id = $sync->synchronize();
    }
    $person = user_load($this->entity->etid);
    $person_id = get_id_from_user($person);
    if (!$person_id) {
      // Synchronize pilot if not synchronized
      $sync = _get_class_by_entity($person, 'user');
      $person_id = $sync->synchronize();
    }
    $this->address = implode('/', array('contest', $contest_core_id, 'paraglider'));
    $data = array(
      'person_id' => $person_id,
      'glider' => $this->entity->field_paraglider_manufacturer[LANGUAGE_NONE][0]['value'],
      'contest_number' => $this->entity->field_contestant_number[LANGUAGE_NONE][0]['value'],
    );
    $core_id = FALSE;
    if ($core_id) {
      $response = $this->request(json_encode($data), "PUT");
    }
    else {
      $response = $this->request(http_build_query($data));
      //$this->updateCoreID($response->id);
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
    $contest = node_load($contest_nid);
    if (!$contest) {
      drupal_set_message(t('ATSyncRace: Unable to load contest'));
      return FALSE;
    }
    get_id_from_entity($this->entity);
    $contest_core_id = get_id_from_contest($contest);
    if (!$contest_core_id) {
      drupal_set_message(t("Core API: Contest not synchronized yet."));
      return FALSE;
    }

    $this->address = implode('/', array('contest', $contest_core_id, 'race'));
    if ($race_core_id = get_race_id_from_race($this->entity)) {
      $this->address = implode('/', array('contest', $contest_core_id, 'race', $race_core_id));
    }

    $data = array(
      'title' => $this->entity->title,
      //'bearing' => 12,
    );
    $data['start_time'] = strtotime($this->entity->field_race_start_end[LANGUAGE_NONE][0]['value']);
    $data['end_time'] = strtotime($this->entity->field_race_start_end[LANGUAGE_NONE][0]['value2']);
    $racetype_ref = $this->entity->field_pg_racetype_ref[LANGUAGE_NONE][0]['target_id'];
    $racetype = array_pop(entity_load('ent_racetype', array($racetype_ref)));
    switch ($racetype->type) {
      case "pg_racetype_rtg":
        $data['race_type'] = 'racetogoal';
        break;

      case "pg_racetype_od":
        $data['race_type'] = 'opendistance';
        break;

      case "pg_racetype_sr":
        $data['race_type'] = 'speedrun';
        break;
    }
    $point_ref = array();
    foreach ($racetype->field_pg_race_points[LANGUAGE_NONE] as $pref) {
      $point_ref[] = $pref['target_id'];
    }
    $points = entity_load("ent_point", $point_ref);
    $checkpoints = array();
    $checkpoints['type'] = "FeatureCollection";
    $checkpoints['features'] = array();
    $delta = 0;
    foreach ($points as $point) {
      $point_data = array();
      $point_data['type'] = 'Feature';
      $point_data['geometry'] = array();
      $contest_point_ref = $point->field_point_ref[LANGUAGE_NONE][0]['target_id'];
      $contest_point = array_pop(entity_load('ent_contest_point', array($contest_point_ref)));
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
      
      if (!empty($point->field_point_ss_es[LANGUAGE_NONE][0]['value'])) {
        $point_data['properties']['checkpoint_type'] = $point->field_point_ss_es[LANGUAGE_NONE][0]['value'];
      }
      if ($delta == 0) {
        $point_data['properties']['checkpoint_type'] = "to";
      }
      if ($delta == count($points) - 1) {
        $point_data['properties']['checkpoint_type'] = "goal";
      }
      $delta++;
      $point_data['properties']['open_time'] = $data['start_time'];
      $point_data['properties']['close_time'] = $data['end_time'];
      $checkpoints['features'][] = $point_data;
    }
    $data_url = http_build_query($data);
    $data_url .= '&checkpoints=' . json_encode($checkpoints);
    if ($race_core_id) {
      $data = array(
        'title' => $this->entity->title,
      );
      $response = $this->request(json_encode($data), "PUT");
    }    
    else {
      $response = $this->request($data_url);
      $this->updateCoreID($response->id);
    }
    $fid = !empty($this->entity->field_pg_race_tracks[LANGUAGE_NONE][0]['fid']) ? $this->entity->field_pg_race_tracks[LANGUAGE_NONE][0]['fid'] : FALSE;
    if ($fid) {
      $this->address .= "/track_archive";
      _d('url='.file_create_url(file_load($fid)->uri));
      $track = $this->request('url='.file_create_url(file_load($fid)->uri));
      _d($track);  
    }
    if (!empty($response->id)) {
      
      //_d(file_create_url($this->entity->field_pg_race_tracks[LANGUAGE_NONE][0]['uri']));
      return $response->id; 
    } else {
      return FALSE;
    }
  }

  public function check() {
  }
}
