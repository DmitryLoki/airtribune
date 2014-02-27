(function ($) {

  // @todo: maybe use window.crontab instead
  // @todo: consider time of pageload in crontab_currentTime

  // Table for scheduled operations.
  // 'timestamp' => array('actions' => array('action', 'parameters' => array()))
  // parameters : raceId, etc. Order of parameters is important - they should be passed into action function.
  // action : checkCoreDateAvailable (function name to be called)
  var crontab = [];
  var crontab_regular = [];
  var raceWatchRegistry = [];

  var crontab_currentTime = 0;
  // Nearest timemark in schedule. Used in crontabWatcher().
  var scheduled_timemark = -1;

  Drupal.behaviors.pg_race_watch = {
    attach: function (context) {
      $(".task-results .links-label a").click(function(event){
        event.preventDefault();
        $(this).closest(".task-results").children(".links-content").toggle();
      });

      $(".task-replay .links-label a").click(function(event){
        event.preventDefault();
        $(this).closest(".task-replay").children(".links-content").toggle();
      });

      $(".task-live .links-label a").click(function(event){
        event.preventDefault();
        $(this).closest(".task-live").children(".links-content").toggle();
      });


      // ------------- EVENTS ---------------------------

      // Actions to be done on crontabTimerIncrement event.
      // http://stackoverflow.com/questions/399867/custom-events-in-jquery
      $(document).on('crontabTimerIncrement', function(e, eventInfo) {
        crontabWatcher();
      });



      // @todo
      // Temporary, the event is triggered 'manually' from functions, that change info.
      // But in the future should be done somehow automatically.
      $(document).on('raceStateChange', function(e, eventInfo) {
        raceWatch = eventInfo['raceWatch'];
        state_current = eventInfo['state_current'];
        state_old = eventInfo['state_old'];
        tmpOnStateChange(raceWatch, state_current, state_old);
      });



      // ------------- SETTINGS PROCESSING ---------------------------

      // @todo
      if (Drupal.settings.pg_race.task_watch != 'undefined') {
        $.each(Drupal.settings.pg_race.task_watch, function(watch_obj_type, pg_race_watch_settings) {
          $.each(pg_race_watch_settings, function(i, pg_race_watch_setting) {
            // Collect settings for all types of watch objects (be it timer or links, etc.).
            raceId = pg_race_watch_setting.race_id;
            function_name = pg_race_watch_setting.function_name;
            if (!raceWatchRegistry.hasOwnProperty(raceId)) {

              pg_race_watch_setting['start'] = pg_race_watch_setting['now_local'] - 10;

              status = pg_race_watch_setting.status;
              raceWatch = {'settings' : pg_race_watch_setting, 'functions' : [function_name], 'status' : { 'current' : status, 'old' : 'init' }};
              raceWatchRegistry[raceId] = raceWatch;
              // @todo: remove 'function_name' and 'status' from 'settings'
            }
            else if (!$.inArray(function_name, raceWatchRegistry[raceId]['functions'])) {
              // Add function_name for current watch object.
              raceWatchRegistry[raceId]['functions'].push(function_name);
            }
          });
        });
      }

      // trigger "raceStateChange" event to initialize all raceWatch objects from [init --> current] state
      $.each (raceWatchRegistry, function(race_id, raceWatch) {
        if (typeof raceWatch != 'undefined') {  // @todo: This is because of assoc arrays iterating problem. Find another solution.
          state_current = raceWatch['status']['current'];
          state_old = raceWatch['status']['old'];
          $(document).trigger('raceStateChange', { "raceWatch" : raceWatch , "state_current" : state_current , "state_old" : state_old } );
        }
      });

      // start crontab timer
      crontabTimer();
    }
  }




  // @todo: maybe use "while" cycle instead of recursion
  function crontabTimer() {
    // Trigger time change in the begining for crontab_currentTime = 0
    $(document).trigger('crontabTimerIncrement');


    setTimeout(crontabTimer, 1000);
    crontab_currentTime = crontab_currentTime + 1;
  }

  // There should be at least two kinds of events: scheduled and regular.
  // Regular are those that process on every crontab_currentTime change, e.g. timer.
  function crontabWatcher() {

    // scheduled crontab operations
    if (crontab_currentTime == scheduled_timemark) {
      scheduled_operations = crontab[scheduled_timemark];

      // execute scheduled operations
      $.each (scheduled_operations, function(i, operation) {
        action = operation['action'];
        parameters = operation['parameters'];
        // @todo:
        window[action](scheduled_timemark, parameters);
      });
    }

    // regular crontab operations
    if (crontab_regular.length > 0) {
      $.each (crontab_regular, function(index, operation) {
        action = operation['action'];
        parameters = operation['parameters'];
        window[action](index, parameters);
      });
    }

    // @todo: remove triggered actions from array. we don't need them any more.
  }

  function setRaceState() {
    //
  }
  function getRaceState() {
    //
  }
  function removeRaceState() {
    //
  }

  // Temporary function instead of statechage() event.
  function tmpOnStateChange(raceWatch, state_current, state_old) {
    //~ console.log(raceWatch);
    $.each (raceWatch['functions'], function(i, function_name) {
      // Function name that would react to raceWatch object status changes.
      window[function_name](raceWatch, state_current, state_old);
    });
  }







  // ------------- RACE STATE CHANGE FUNCTIONS MAPPER ---------------------------

  // @todo:

  // Name of this function is passed in pg_race_watch_setting.function_name.
  window.pg_race_frontpage_live_events_links = function pg_race_frontpage_live_events_links(raceWatch, state_current, state_old){
    var raceId;
    raceId = raceWatch.settings.race_id;

    // init --> is_live
    if (state_old == 'init' && state_current == 'is_live' ) {
      // add checkCoreDataAvailable into crontab
      timemark = 0;
      action = { 'action' : 'checkCoreDataAvailable' , 'parameters' : { 'raceId' : raceId } };
      pgRaceCrontabAdd (timemark, action);

      // add regular operations (timer update when crontab_currentTime is incremented)
      action = { 'action' : 'changeRaceTimerRendered' , 'parameters' : { 'raceId' : raceId } }
      crontab_regular.push(action);
    }

    // awaiting --> is_live
    else if (state_old == 'awaiting' && state_current == 'is_live' ) {
      timemark = crontab_currentTime + 1;
      action = { 'action' : 'checkCoreDataAvailable' , 'parameters' : { 'raceId' : raceId } };
      pgRaceCrontabAdd (timemark, action);
    }

    // init --> awaiting
    else if (state_old == 'init' && state_current == 'awaiting' ) {
      // Add regular operations (timer update when crontab_currentTime is incremented)
      action = { 'action' : 'changeRaceTimerRendered' , 'parameters' : { 'raceId' : raceId } }
      crontab_regular.push(action);
    }
  }


  // ------------- SCHEDULED AND REGULAR OPERATIONS ---------------------------

  // @todo

  // Check if data is available for given raceId and set another timemark action if required.
  window.checkCoreDataAvailable = function checkCoreDataAvailable(timemark, parameters) {
    // If there is problem with data retrieval, bind this action to another timemark.
    var period = 10;
    var new_timemark = crontab_currentTime + period;
    var raceId = parameters['raceId'];
    action = { 'action' : 'checkCoreDataAvailable' , 'parameters' : { 'raceId' : raceId } };
    pgRaceCrontabAdd (new_timemark, action);
  }




  // Render and replace race timer html
  window.changeRaceTimerRendered = function changeRaceTimerRendered(index, parameters) {
    raceId = parameters.raceId;
    raceWatch = raceWatchRegistry[raceId];

    now_local = raceWatch['settings']['now_local'];
    start = raceWatch['settings']['start'];

    status = raceWatch['settings']['status'];

    if (status == 'is_live') {
      diff = now_local - start;
    }
    else if (status == 'awaiting') {
      diff = start - now_local;

    }


    timer = diff + crontab_currentTime;
    timerRendered = renderRaceTimer(timer);
    $(".time.race-id-" + raceId).html(timerRendered);

    // Change status from Awaiting to Is_live
    if (status == 'awaiting' && timer == 0) {
      // @todo: move into separate function like raceChangeStatus
      raceWatchRegistry[raceId]['status']['current'] = 'is_live';
      raceWatchRegistry[raceId]['status']['old'] = 'awaiting';
      raceWatch = raceWatchRegistry[raceId];

      state_current = raceWatch['status']['current'];
      state_old = raceWatch['status']['old'];

      $(document).trigger('raceStateChange', { "raceWatch" : raceWatch , "state_current" : state_current , "state_old" : state_old } );
    }
  }


  // ------------- HELPER FUNCTIONS ---------------------------

  function renderRaceTimer(timer) {
    var absD = Math.abs(timer);
    timerRendered = (timer < 0 ? "-" : "") + _getTimeStr(Math.floor(absD / 3600), Math.floor(absD % 3600 / 60), absD % 60);
    return timerRendered;
  }

  // This is a clone of getTimeStr() from pg_race_play_link.js
  function _getTimeStr(h, m, s) {
    h = Math.abs(h);
    m = Math.abs(m);
    s = Math.abs(s);
    return (h < 10 ? "0" : "") + h + ":" + (m < 10 ? "0" : "") + m + ":" + (s < 10 ? "0" : "") + s;
  }


  // Add action into crontab
  function pgRaceCrontabAdd (timemark, action) {
    if (crontab.hasOwnProperty(timemark)) {
      // @todo: maybe key should be raceId but not just autoincrement
      crontab[timemark].push(action);
    }
    else {
      crontab[timemark] = [ action ];
    }

    // @todo: set initial value for "scheduled_timemark" based on "crontab" (scheduled) data
    // and also all previous timemarks must be removed or not considered

    // Set scheduled_timemark as  minimum valid timemark
    timemarks = Object.keys(crontab);
    if (timemarks.length > 0) {

      valid_timemarks = jQuery.grep(timemarks, function( n, i ) {
        return (n > crontab_currentTime );
      });
      if (valid_timemarks.length > 0) {
        scheduled_timemark = Math.min.apply(Math, valid_timemarks);
        console.log(scheduled_timemark);
      }
    }
    //~ scheduled_timemark = timemark;
  }

})(jQuery);

