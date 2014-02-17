<?php

// @todo: Replace AIRTRIBUNE_VIS_STATE_{ONLINE | AWAITING | REPLAY} constants

// PG_RACE_WATCH_STATUS_EMPTY - in case something goes wrong or no start-finish data
define('PG_RACE_WATCH_STATUS_EMPTY', 0);
define('PG_RACE_WATCH_STATUS_AWAITING', 1);
define('PG_RACE_WATCH_STATUS_STARTING', 2);
define('PG_RACE_WATCH_STATUS_IS_LIVE', 3);
define('PG_RACE_WATCH_STATUS_FINISHED', 4);

class  RaceWatch {
  static private $now_utc;
  private $entity_race;
  private $race_status;
  //~ private $race_timer;
  private $race_contest;
  private $time_offset;
  private $open_close;
  private $start_end;

  /**
   * Class constructor
   *
   * @todo: Add entity check
   */
  function __construct($entity) {
    if (empty($this->now_utc)) {
      $this->now_utc = time();
    }
    $this->entity_race = $entity;
  }

  /**
   * Get event entity for the current race.
   */
  private function getEventEntity() {
    if (!isset($this->race_contest)) {
      $items = field_get_items(AIRTRIBUNE_RACE_ENTITY_TYPE, $this->entity_race, OG_AUDIENCE_FIELD);
      if (!empty($items)) {
        $item = array_shift($items);
        $contest_id = $item['target_id'];
        $contest = node_load($contest_id);
        if (!empty($contest->nid)) {
          $this->race_contest = $contest;
        }
      }
    }
    return $this->race_contest;
  }

  /**
   * Get time offset for the current event.
   */
  private function getTimeOffset() {
    if (!isset($this->time_offset)) {
      $contest = $this->getEventEntity();
      $contest_time = airtribune_extract_time_from_contest($contest);
      //~ dsm($contest_time);
      $this->time_offset = $contest_time['offset'];
    }
    return $this->time_offset;
  }

  /**
   * Check task current status
   *
   * @todo
   */
  function raceStatus() {
    if (!isset($this->race_status)) {
      $entity_race = $this->entity_race;
      $wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACE_ENTITY_TYPE, $entity_race);

      $start_end = $wrapper->{AIRTRIBUNE_RACE_START_END_FIELD}->value();
      if (!empty($start_end)) {
        $start_end = array(
          'value' => strtotime($start_end['value']),
          'value2' => strtotime($start_end['value2']),
        );
      }




      $open_close = $wrapper->{AIRTRIBUNE_PG_RACE_WINDOW_OPEN_CLOSE_FIELD}->value();
      if (!empty($open_close)) {
        $open_close = array(
          'value' => strtotime($open_close['value']),
          'value2' => strtotime($open_close['value2']),
        );
      }

      $this->open_close = $open_close;
      $this->start_end = $start_end;



      // No time data to check status
      if (empty($open_close['value']) || empty($open_close['value2']) || empty($start_end['value']) || empty($start_end['value2'])) {
        $status = PG_RACE_WATCH_STATUS_EMPTY;
      }

      $now_utc = $this->now_utc;

      $offset = $this->getTimeOffset();
      $now_local = $now_utc + $offset;

      // @todo: consider offset for start/end and open/close

      if ($now_local < $open_close['value']) {
        dsm('awaiting');
        $status = PG_RACE_WATCH_STATUS_AWAITING;
      }
      elseif ($now_local >= $open_close['value'] && $now_local < $start_end['value']) {
        dsm('starting');
        $status = PG_RACE_WATCH_STATUS_STARTING;
      }
      // @todo: check second part of the condition
      elseif ($now_local >= $start_end['value'] && $now_local < $start_end['value2']) {
        dsm('is life');
        $status = PG_RACE_WATCH_STATUS_IS_LIVE;
      }
      else {
        dsm('finished');
        $status = PG_RACE_WATCH_STATUS_FINISHED;
      }

//~ dsm_once($start_end, 'se');
//~ dsm_once($open_close, 'oc');
//~ dsm($now_utc);




      $this->race_status = $status;
      $this->race_status = PG_RACE_WATCH_STATUS_IS_LIVE;
    }
    return $this->race_status;
  }

  /**
   * Check data to that could be used for links rendering
   *
   * @todo
   */
  function raceLinksInfo() {
    $status = $this->raceStatus();

    $raceLinksInfo = array();

    switch ($status) {
      case PG_RACE_WATCH_STATUS_IS_LIVE :
        //~ $raceLinksInfo['links']['live_2d'] = array();

        $raceLinksInfo['links']['live'] = $this->raceLiveInfo();
        break;
      case PG_RACE_WATCH_STATUS_FINISHED :
        $raceResultsInfo = $this->raceResultsInfo();
        if (!empty($raceResultsInfo)) {
          $raceLinksInfo['links']['results'] = $raceResultsInfo;
        }

        //~ $raceLinksInfo['links']['replay_2d'] = array();
        //~ $raceLinksInfo['links']['replay_3d'] = array();
        $raceLinksInfo['links']['leader_board'] = array(
          'path' => "play/{$this->entity_race->id}/leaderboard",
        );

        $raceReplayInfo = $this->raceReplayInfo();
        $raceLinksInfo['links']['replay'] = $raceReplayInfo;
        break;
    }

    return $raceLinksInfo;
  }

  /**
   * Return absolute value for time to/after race start
   *
   * Value is returned in UNIX timestamp form as delta from $now_local
   * By default, value is returned as ABS().
   *
   * @todo
   */
  function raceTimer($signed = FALSE) {
    //~ if (!isset($this->race_timer)) {
      //~ return $race_timer;
    //~ }
    $status = $this->raceStatus();

    if (!in_array($status, array(PG_RACE_WATCH_STATUS_EMPTY, PG_RACE_WATCH_STATUS_FINISHED))) {
      $open_close = $this->open_close;
      $start_end = $this->start_end;

      $now_utc = $this->now_utc;
      $offset = $this->getTimeOffset();
      $now_local = $now_utc + $offset;

      // Get time delta relative to $now_utc
      switch ($status) {
        case PG_RACE_WATCH_STATUS_AWAITING :
          $race_timer = abs($now_local - $open_close['value']);
          break;
        case PG_RACE_WATCH_STATUS_STARTING :
          $race_timer = abs($now_local - $start_end['value']);
          break;
        case PG_RACE_WATCH_STATUS_IS_LIVE :
          $race_timer = abs($now_local - $start_end['value']);
          break;
      }
      return $race_timer;
    }


    // @todo: Remove
    //~ return '00:11:22';
  }

  /**
   * Return race start time
   *
   * @todo
   */
  function raceStartTime() {
    $status = $this->raceStatus();
    if (!in_array($status, array(PG_RACE_WATCH_STATUS_EMPTY, PG_RACE_WATCH_STATUS_FINISHED))) {
      $open_close = $this->open_close;
      $start_time = $open_close['value'];
      return $start_time;
    }
  }

  /**
   * Return path to race results file or FALSE
   *
   * @todo: optimize scoring categories loading
   */
  function raceResultsInfo() {
    $resultsInfo['day'] = array();
    $resultsInfo['competition'] = array();

    $entity_race = $this->entity_race;
    $entity_event = $this->getEventEntity();

    //~ $entities = entity_load('ent_race', array(86));
    //~ $entity = array_shift($entities);
    //~ $entity_race = $entity;

    // @todo: maybe this data could be transfered from views
    // or maybe use "day_results" views results
    $wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACE_ENTITY_TYPE, $entity_race);


    $pattern = 'event/:event_nid/race/:race_id/results/:category_id/:type';

    $placeholders = array(
      ':event_nid' => $entity_event->nid,
      ':race_id' => $entity_race->id,
    );

    $results = array(
      'day' => $wrapper->{AIRTRIBUNE_DAY_RESULTS_FIELD}->value(),
      'competition' => $wrapper->{AIRTRIBUNE_COMPETITION_RESULTS_FIELD}->value(),
    );

    foreach ($results as $type => $items) {
      $placeholders[':type'] = $type;
      foreach ($items as $item) {

        $target_id = $item->field_scoring_category_ref['und'][0]['target_id'];
        $node = node_load($target_id);
        $category = $node->field_pg_scoring_category['und'][0]['value'];

        $placeholders[':category_id'] = $target_id;
        $resultsInfo[$type][] = array(
          'category' => $category,
          'path' => strtr($pattern, $placeholders),
        );
      }
    }

    //~ dsm_once($entity_race, 'entity');
    //~ dsm_once($results, 'results');
    //~ dsm_once($day_results, 'day_results');
    //~ dsm_once($competition_results, 'competition_results');
    //~ dsm_once($resultsInfo, 'info');

    return $resultsInfo;
  }

  /**
   * Return path to race replay
   *
   * @todo
   */
  function raceReplayInfo() {
    $raceReplayInfo['2d'] = array();
    $raceReplayInfo['3d'] = array();

    $raceReplayInfo['2d']['path'] = "play/{$this->entity_race->id}/2d";
    $raceReplayInfo['3d']['path'] = "play/{$this->entity_race->id}/ge";
    return $raceReplayInfo;
  }

  /**
   * Return path to race live
   *
   * @todo
   */
  function raceLiveInfo() {
    $raceReplayInfo['2d'] = array();
    $raceReplayInfo['3d'] = array();

    $raceReplayInfo['2d']['path'] = "play/{$this->entity_race->id}/2d";
    $raceReplayInfo['3d']['path'] = "play/{$this->entity_race->id}/ge";
    return $raceReplayInfo;
  }

  /**
   * Return open_close & start_end data
   *
   * @todo
   */
  function getTimeInfo() {
    $data = array();
    $status = $this->raceStatus();
    if ($status != PG_RACE_WATCH_STATUS_EMPTY) {
      $data = array(
        'open' => $this->open_close['value'],
        'close' => $this->open_close['value2'],
        'start' => $this->start_end['value'],
        'end' => $this->start_end['value2'],
        'now_local' => $this->now_utc + $this->getTimeOffset(),
        'now_utc' => $this->now_utc,
        'offset' => $this->getTimeOffset(),
      );
    }
    return $data;
  }
}
