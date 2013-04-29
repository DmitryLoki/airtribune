<?

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
    public function request($data, $method = "POST"){
      $handle = curl_init();
      $url = $this->domain . $this->address;
      curl_setopt($handle, CURLOPT_URL, $url);
      curl_setopt($handle, CURLOPT_PORT, $this->port);
      curl_setopt($handle, CURLOPT_RETURNTRANSFER, true);
      curl_setopt($handle, CURLOPT_SSL_VERIFYHOST, false);
      curl_setopt($handle, CURLOPT_SSL_VERIFYPEER, false);

      switch($method)
      {      
        case 'GET':
          break; 
        case 'POST':
          curl_setopt($handle, CURLOPT_POST, true);
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
      _d('code:');
      _d(curl_getinfo($handle, CURLINFO_HTTP_CODE));
      return json_decode($response);
    }
    public function updateCoreID($id){
      $this->entity->field_core_id = array(
        "und" => array(
          array(
            "value" => $id,
          ),
        ),
      );
      entity_save($this->entity_type, $this->entity);
    }
    abstract public function onInsert();
    abstract public function onUpdate();
}

/**
 * Class for synchronization pg_contest
 */
class ATSyncContest extends ATSync {
  public $address = "contest";
  public function onInsert(){
    $node = $this->entity;
    $data = array(
      'hq_coords' => $node->field_hq_location['und'][0]['lat'] . ',' . $node->field_hq_location['und'][0]['lon'],
      'title' => $node->title,
      'start_time' => strtotime($node->field_dates['und'][0]['value']),
      'end_time' => strtotime ($node->field_dates['und'][0]['value2']),
      'place' => $node->field_city['und'][0]['value'],
      'country' => $node->field_country['und'][0]['iso2'],
      'timezone' => $node->field_dates['und'][0]['timezone'],
    );
    $response = $this->request(http_build_query($data));
    $id = $response->id;
    $this->updateCoreID($id);
    return $id;
  }
  public function onUpdate(){
    $node = $this->entity;

    if(empty($node->field_core_id['und'][0]['value'])) {
      return $this->onInsert();
    }

    $id = $node->field_core_id['und'][0]['value'];
    $this->address .= '/' . $id;
    $data = array(
      'hq_coords' => $node->field_hq_location['und'][0]['lat'] . ',' . $node->field_hq_location['und'][0]['lon'],
      'title' => $node->title,
      'start_time' => strtotime($node->field_dates['und'][0]['value']),
      'end_time' => strtotime ($node->field_dates['und'][0]['value2']),
      'place' => $node->field_city['und'][0]['value'],
      'country' => $node->field_country['und'][0]['iso2'],
      'timezone' => $node->field_dates['und'][0]['timezone'],
    );

    $response = $this->request(json_encode($data), "PUT");
    drupal_set_message(print_r($response, TRUE));
    return $response->id;
  }
}

/**
 * Class for synchronization pilot
 */
class ATSyncPilot extends ATSync {
  public $address = "person";
  public function onInsert(){
    // insert code
  }
  public function onUpdate(){
    // update code
  }
}

/**
 * Class for synchronization race
 */
class ATSyncRace extends ATSync {
  public $address = "contest/";
  public function onInsert(){
    // insert code
  }
  public function onUpdate(){
    $day_id = $this->entity->field_day_ref['und'][0]['target_id'];
    $contest_id = $this->entity->og_group_ref['und'][0]['target_id'];
    $contest = node_load($contest_id);
    if (!$contest) {
      drupal_set_message(t('ATSyncRace: Unable to load contest'));
      return false;
    }
    $contest_core_id = FALSE;
    if (empty($contest->field_core_id['und'][0]['value'])){
      if($sync = _get_class_by_entity($contest, "node")){
        $contest_core_id = $sync->onInsert();
      }
    } else {
      $contest_core_id = $contest->field_core_id['und'][0]['value'];
    }
    if (!$contest_core_id) {
      drupal_set_message(t('ATSyncRace: Unable to get contest core id'));
      return false;
    }
    $this->address = implode('/', array('contest', $contest_core_id, 'race'));
    _d($this->address . " address");
    
    $checkpoints = array(
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
    );
    
    $data = array(
      'title' => $this->entity->title,
      'race_type' => 'SpeedRun',
      'start_time' => 12345678890,
      'end_time' => 12345678898,
      'bearing' => 12,
      //'checkpoints' => array(1,2,3,4,5), //json_encode($checkpoints),
    );
    $url = http_build_query($data);
    $url .= '&checkpoints='.json_encode($checkpoints);
    _d($url);
    $response = $this->request($url, "POST");
    _d($response);
    return $response->id;
    // update code
  }
}

function _d($var) {
  drupal_set_message(print_r($var, TRUE));
}
