<?php

// @todo: Replace AIRTRIBUNE_VIS_STATE_{ONLINE | AWAITING | REPLAY} constants

// PG_RACE_WATCH_STATUS_EMPTY - in case something goes wrong or no start-finish data
define('PG_RACE_WATCH_STATUS_EMPTY', 0);
define('PG_RACE_WATCH_STATUS_AWAITING', 1);
define('PG_RACE_WATCH_STATUS_IS_LIVE', 2);
define('PG_RACE_WATCH_STATUS_FINISHED', 3);

class  RaceWatch {
  static private $now;
  private $entity_race;
  private $race_status;

  function __construct($entity) {
    if (empty($now)) {
      $this->now = time();
    }
    $this->entity_race = $entity;
  }

  /**
   * Check task current status
   */
  function raceStatus() {
    $this->race_status = PG_RACE_WATCH_STATUS_IS_LIVE;
    return $this->race_status;
  }

  /**
   * Return absolute value for time to/after race start
   */
  function raceTimer() {
    return '00:11:22';
  }
}
