<?

abstract class ATSync {
    public $entity;
    public $id = FALSE;
    public $address = FALSE;
    public $port;
    public function __construct($entity) {
        $this->entity = $entity;
    }
    abstract public function onInsert();
    abstract public function onUpdate();
    abstract public function onDelete();
}

class ContestSync extends ATSync {
  public $address = "/contest";
  public function onInsert(){
    print '1';
  }
  public function onUpdate(){
    print '2';
  }
  public function onDelete(){
    print '3';
  }
}

class PersonSync extends ATSync {
  public $address = "/person";
  public function onInsert(){
    print '1';
  }
  public function onUpdate(){
    print '2';
  }
  public function onDelete(){
    print '3';
  }
}

$class = "PersonSync";
print_r($test = new $class(12));
$test->onDelete();

?>