<?php
define(AIRTRIBUNE_CORE_ID_FIELD, 'field_core_id');
define(LANGUAGE_UNDEFINED, 'und');

/**
 * Abstract class with commin synchronisation functions
 */
abstract class ATSync {
  public $entity;
  public $entity_type;
  public $id = FALSE;
  public $address = FALSE;
  public $domain = "http://api.airtribune.com/v0.1/";
  public $port = 80;
  public function __construct($entity, $entity_type) {
    $this->entity = $entity;
    $this->entity_type = $entity_type;
  }
  public function request($data, $method = "POST") {
    $handle = curl_init();
    $url = $this->domain . $this->address;
    curl_setopt($handle, CURLOPT_URL, $url);
    curl_setopt($handle, CURLOPT_PORT, $this->port);
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
        drupal_set_message(t("Core API[404]: Resource not found"), 'error');
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
    // Choose PUT or POST - depends exist contest in Core or not
    if ($core_id) {
      $response = $this->request(json_encode($data), "PUT");
    }
    else {
      $response = $this->request(http_build_query($data));
      $this->updateCoreID($response->id);
    }
    return !empty($response->id) ? $response->id : FALSE;
  }
}

/**
 * Class for synchronization person
 */
class ATSyncPerson extends ATSync {
  public $address = "person";
  public function synchronize() {
    $name = $this->entity->profile_main['field_full_name'][LANGUAGE_UNDEFINED][0];
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
      'name' => $profile2['main']->field_full_name[LANGUAGE_UNDEFINED][0]['given'],
      'surname' => $profile2['main']->field_full_name[LANGUAGE_UNDEFINED][0]['family'],
      'country' => $profile2['pilot']->field_address[LANGUAGE_UNDEFINED][0]['country'],
      'email' => $this->entity->mail,
      'reg_date' => date("Y,m,d", $this->entity->created),
    );
    // Choose PUT or POST - depends exist contest in Core or not
    if ($core_id) {
      $response = $this->request(json_encode($data), "PUT");
    }
    else {
      $response = $this->request(http_build_query($data));
      $this->updateCoreID($response->id);
    }
    return !empty($response->id) ? $response->id : FALSE;
  }
}

/**
 * Class for synchronization pilot
 */
class ATSyncPilot extends ATSync {
  public $address = "contest/";
  public function synchronize() {
    // Send only if status is confirmed
    if ($this->entity->field_pg_contestant_status[LANGUAGE_UNDEFINED][0]['value'] != 4) {
      return FALSE;
    }
    $contest = node_load($this->entity->gid);
    $contest_core_id = get_id_from_contest($contest);
    if (!$contest_id) {
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
      'glider' => $this->entity->field_paraglider_manufacturer[LANGUAGE_UNDEFINED][0]['value'],
      'contest_number' => $this->entity->field_contestant_number[LANGUAGE_UNDEFINED][0]['value'],
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
}

/**
 * Class for synchronization race
 */
class ATSyncRace extends ATSync {
  public $address = "contest/";
  public function synchronize() {
    geophp_load();
    $day_id = $this->entity->field_day_ref[LANGUAGE_UNDEFINED][0]['target_id'];
    $contest_nid = $this->entity->og_group_ref[LANGUAGE_UNDEFINED][0]['target_id'];
    $contest = node_load($contest_nid);
    if (!$contest) {
      drupal_set_message(t('ATSyncRace: Unable to load contest'));
      return FALSE;
    }

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
      'bearing' => 12,
    );
    $data['start_time'] = strtotime($this->entity->field_race_start_end[LANGUAGE_UNDEFINED][0]['value']);
    $data['end_time'] = strtotime($this->entity->field_race_start_end[LANGUAGE_UNDEFINED][0]['value2']);
    $racetype_ref = $this->entity->field_pg_racetype_ref[LANGUAGE_UNDEFINED][0]['target_id'];
    //$racetype = entity_load('ent_racetype', $racetype_ref);
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
    foreach ($racetype->field_pg_race_points[LANGUAGE_UNDEFINED] as $pref) {
      $point_ref[] = $pref['target_id'];
    }
    $points = entity_load("ent_point", $point_ref);
    $checkpoints = array();
    $checkpoints['type'] = "FeatureCollection";
    $checkpoints['features'] = array();
    foreach ($points as $point) {
      $point_data = array();
      $point_data['type'] = 'Feature';
      $point_data['geometry'] = array();
      $wkt = $point->field_point_center[LANGUAGE_UNDEFINED][0]['geom'];
      $geom = geoPHP::load($wkt);
      $coordinates = json_decode($geom->out('json'));
      $point_data['geometry']['type'] = $point->field_point_center[LANGUAGE_UNDEFINED][0]['geo_type'];
      $point_data['geometry']['coordinates'] = "Point";
      $point_data['properties'] = array();
      //_d(db_query("SELECT ST_GeomFromText('".$geom."');")->fetchRow());
      $point_data['properties']['radius'] = $point->field_point_radius[LANGUAGE_UNDEFINED][0]['value'];
      $point_data['properties']['name'] = $point->id;
      $point_data['properties']['type'] = $point->type;
      $checkpoints['features'][] = array($point_data);
    }

    /* working example
     * $checkpoints = array(
      "type" => "FeatureCollection",
      "features" => array(
        array(
          'type' => 'Feature',
          'geometry' => array(
            'type' => 'Point',
            'coordinates' => array(12.4, -10.2)
          ),
          'properties' => array(
            'radius' => 400,
            'name' => 'A012300',
            'checkpoint_type' => 'ordinal',
            'open_time' => 12345678890,
            'close_time' => 12345678898,
          ),
        ),
      ),
    );*/

    $url = http_build_query($data);
    $url .= '&checkpoints=' . json_encode($checkpoints);
    if ($race_core_id) {
      $data = array(
        'title' => $this->entity->title,
      );
      $response = $this->request(json_encode($data), "PUT");
    }
    else {
      $response = $this->request($url);
      $this->updateCoreID($response->id);
    }
    return !empty($response->id) ? $response->id : FALSE;
  }
}

// Debug function
function _d($var) {
  drupal_set_message(print_r($var, TRUE));
}