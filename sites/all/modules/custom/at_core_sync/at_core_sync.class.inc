<?

abstract class ATSync {
    public $entity;
    public $entity_type;
    public $id = FALSE;
    public $address = FALSE;
    public $domain = "http://airtribune.com/";
    public $port = 8085;
    public function __construct($entity, $entity_type) {
        $this->entity = $entity;
        $this->entity_type = $entity_type;
    }
    public function request($data, $method = "POST"){
      /*$options = array(
        "method" => $method,
        "data" => http_build_query($data),
      );
      drupal_set_message(print_r($options, TRUE));
      $result = drupal_http_request("http://airtribune.com:8085/contest", $options);
      return json_decode($result->data);*/
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
          curl_setopt($handle, CURLOPT_POSTFIELDS, http_build_query($data));
          break;        
        case 'PUT':
          curl_setopt($handle, CURLOPT_CUSTOMREQUEST, 'PUT');
          curl_setopt($handle, CURLOPT_POSTFIELDS, http_build_query($data));
          break;        
        case 'DELETE':
          curl_setopt($handle, CURLOPT_CUSTOMREQUEST, 'DELETE');
          break;
      }
      $response = curl_exec($handle);
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
    abstract public function onDelete();
}

class ContestSync extends ATSync {
  public $address = "contest";
  public function onInsert(){
    $node = $this->entity;
    drupal_set_message(print_r($node->field_timezone, TRUE));
    $data = array(
      'hq_coords' => $node->field_hq_location['und'][0]['lat'] . ',' . $node->field_hq_location['und'][0]['lon'],
      'title' => $node->title,
      'start_time' => strtotime($node->field_dates['und'][0]['value']),
      'end_time' => strtotime ($node->field_dates['und'][0]['value2']),
      'place' => $node->field_city['und'][0]['value'],
      'country' => $node->field_country['und'][0]['iso2'],
      'timezone' => $node->field_dates['und'][0]['timezone'],
    );
    $response = $this->request($data);
    $id = $response->id;    
    drupal_set_message(print_r($response, TRUE));
    $this->updateCoreID($id);
  }
  public function onUpdate(){
    $node = $this->entity;
    drupal_set_message(print_r($node->field_timezone, TRUE));
    $data = array(
      'hq_coords' => $node->field_hq_location['und'][0]['lat'] . ',' . $node->field_hq_location['und'][0]['lon'],
      'title' => $node->title,
      'start_time' => strtotime($node->field_dates['und'][0]['value']),
      'end_time' => strtotime ($node->field_dates['und'][0]['value2']),
      'place' => $node->field_city['und'][0]['value'],
      'country' => $node->field_country['und'][0]['iso2'],
      'timezone' => $node->field_dates['und'][0]['timezone'],
    );
    $response = $this->request($data);
    $id = $response->id;    
    drupal_set_message(print_r($response, TRUE));
    $this->updateCoreID($id);
  }
  public function onDelete(){
    // delete code
  }
}

class UserSync extends ATSync {
  public $address = "person";
  public function onInsert(){
    // insert code
  }
  public function onUpdate(){
    // update code
  }
  public function onDelete(){
    // delete code
  }
}

class PersonSync extends ATSync {
  public $address = "person";
  public function onInsert(){
    // insert code
  }
  public function onUpdate(){
    // update code
  }
  public function onDelete(){
    // delete code
  }
}
