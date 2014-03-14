(function ($) {

  // @todo: maybe use window.crontab instead

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


      $(".front_live_events .view-content").append("<div id='live-events-more'><a href='/events/current'>...</a></div>").children("#live-events-more").click(function(){
        length = $(this).closest(".front_live_events").find(".row-wrapper").not((".row-wrapper .row-wrapper")).filter(function(){
              return $(this).css('overflow') == 'hidden';
            }).length;
        if (length) {
          event.preventDefault();
          $(this).closest(".front_live_events").find(".row-wrapper").not((".row-wrapper .row-wrapper")).filter(function(){
              return $(this).css('overflow') == 'hidden';
            }).first().css('overflow', 'visible');
        }
      });

      // @todo: consider time of pageload in crontab_currentTime
      // also, consider case timer == 0 for status change
      //~ pageLoadDelay = Math.floor((new Date().getTime() - pageLoadStart.getTime())  / 1000);
      //~ alert(pageLoadDelay);

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
      if (typeof Drupal.settings.pg_race != 'undefined' && typeof Drupal.settings.pg_race.task_watch != 'undefined' && Drupal.settings.pg_race.task_watch) {
        $.each(Drupal.settings.pg_race.task_watch, function(watch_obj_type, pg_race_watch_settings) {
          $.each(pg_race_watch_settings, function(i, pg_race_watch_setting) {
            // Collect settings for all types of watch objects (be it timer or links, etc.).
            raceId = pg_race_watch_setting.race_id;
            function_name = pg_race_watch_setting.function_name;
            if (!raceWatchRegistry.hasOwnProperty(raceId)) {


              pg_race_watch_setting['open'] = pg_race_watch_setting['now_local'] + 5;
              pg_race_watch_setting['start'] = pg_race_watch_setting['now_local'] + 10;
              pg_race_watch_setting['end'] = pg_race_watch_setting['now_local'] + 20;

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

    // @todo: remove triggered (processed) actions from array. we don't need them any more.
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

    coreApiAddress = raceWatch.settings.core_api_address;
    contestCid = raceWatch.settings.contest_cid;
    raceCid = raceWatch.settings.race_cid;


    // init --> is_live
    if (state_old == 'init' && state_current == 'is_live' ) {
      // add checkCoreDataAvailable into crontab
      // @todo: use crontab_currentTime insead of 0 (because of delay)
      //~ timemark = crontab_currentTime;  // = 0 or 0 + pageload delay
      timemark = 0;  // = 0 or 0 + pageload delay
      action = { 'action' : 'checkCoreDataAvailable' , 'parameters' : { 'raceId' : raceId, 'coreApiAddress' : coreApiAddress, 'contestCid' : contestCid,  'raceCid' : raceCid } };
      pgRaceCrontabAdd (timemark, action);

      // add regular operations (timer update when crontab_currentTime is incremented)
      action = { 'action' : 'changeRaceTimerRendered' , 'parameters' : { 'raceId' : raceId } }
      crontab_regular.push(action);
    }

    // awaiting --> is_live
    // @todo: seems, that this option isn't required
    //~ else if (state_old == 'awaiting' && state_current == 'is_live' ) {
      //~ timemark = crontab_currentTime + 1;
      //~ action = { 'action' : 'checkCoreDataAvailable' , 'parameters' : { 'raceId' : raceId, 'coreApiAddress' : coreApiAddress, 'contestCid' : contestCid,  'raceCid' : raceCid } };
      //~ pgRaceCrontabAdd (timemark, action);
    //~ }

    // awaiting --> starting
    // @todo: change html if required
    else if (state_old == 'awaiting' && state_current == 'starting' ) {
      $('.watch-links-race-id-' + raceId).removeClass('awaiting').addClass('starting');
      $('.day-blog-race-id-' + raceId).removeClass('awaiting').addClass('starting');

      timemark = crontab_currentTime + 1;
      action = { 'action' : 'checkCoreDataAvailable' , 'parameters' : { 'raceId' : raceId, 'coreApiAddress' : coreApiAddress, 'contestCid' : contestCid,  'raceCid' : raceCid } };
      pgRaceCrontabAdd (timemark, action);
    }

    // starting --> is_live
    else if (state_old == 'starting' && state_current == 'is_live' ) {
      $('.watch-links-race-id-' + raceId).removeClass('starting').addClass('is_live');
      $('.day-blog-race-id-' + raceId).removeClass('starting').addClass('is_live');

      timemark = crontab_currentTime + 1;
      action = { 'action' : 'checkCoreDataAvailable' , 'parameters' : { 'raceId' : raceId, 'coreApiAddress' : coreApiAddress, 'contestCid' : contestCid,  'raceCid' : raceCid } };
      pgRaceCrontabAdd (timemark, action);

      action = { 'action' : 'actionSetTimerHelpText' , 'parameters' : { 'raceId' : raceId, 'state_old' : state_old, 'state_current' : state_current } };
      pgRaceCrontabAdd (timemark, action);
    }

    // init --> awaiting
    else if (state_old == 'init' && state_current == 'awaiting' ) {
      // Add regular operations (timer update when crontab_currentTime is incremented)
      action = { 'action' : 'changeRaceTimerRendered' , 'parameters' : { 'raceId' : raceId } }
      crontab_regular.push(action);
    }

    // init --> starting
    else if (state_old == 'init' && state_current == 'starting' ) {
      // Add regular operations (timer update when crontab_currentTime is incremented)
      action = { 'action' : 'changeRaceTimerRendered' , 'parameters' : { 'raceId' : raceId } }
      crontab_regular.push(action);
    }

    // init --> finished
    else if (state_old == 'init' && state_current == 'finished' ) {
      // Add regular operations (timer update when crontab_currentTime is incremented)
      timemark = crontab_currentTime + 1;
      action = { 'action' : 'checkCoreDataAvailableFinished' , 'parameters' : { 'raceId' : raceId, 'coreApiAddress' : coreApiAddress, 'contestCid' : contestCid,  'raceCid' : raceCid } };
      pgRaceCrontabAdd (timemark, action);
    }

    // is_live --> finished
    else if (state_old == 'is_live' && state_current == 'finished' ) {
      // Hide WatchLive links
      $('.watch-links-race-id-'+raceId+' .task-live').hide();
      $('.watch-links-race-id-'+raceId).removeClass('is_live').addClass('finished');
      $('.day-blog-race-id-'+raceId).removeClass('is_live').addClass('finished');
      $('.day-blog-race-id-'+raceId+' .task-timer').hide();

      var dayblog_hidden = $('.day-blog-race-id-'+raceId+' .day-blog-wrapper');
      if (dayblog_hidden.length > 0) {
        $('.day-blog-race-id-'+raceId+'.day-blog').removeClass('no-blog');
        dayblog_hidden.show();
      }

      // Add regular operations (timer update when crontab_currentTime is incremented)
      timemark = crontab_currentTime + 1;
      action = { 'action' : 'checkCoreDataAvailableFinished' , 'parameters' : { 'raceId' : raceId, 'coreApiAddress' : coreApiAddress, 'contestCid' : contestCid,  'raceCid' : raceCid } };
      pgRaceCrontabAdd (timemark, action);
    }

    // @todo: Remove regular operation on status change if required. E.g. timer doesn't need to be updated if status == "current"
  }


  // ------------- SCHEDULED AND REGULAR OPERATIONS ---------------------------

  // @todo

  // Check if data is available for given raceId and set another timemark action if required.
  window.checkCoreDataAvailable = function checkCoreDataAvailable(timemark, parameters) {

    var raceId = parameters['raceId'];
    var coreApiAddress = parameters['coreApiAddress'];
    var contestCid = parameters['contestCid'];
    var raceCid = parameters['raceCid'];

    var raceData = {
      coreApiAddress: parameters['coreApiAddress'],
      raceId: parameters['raceId'],
      raceCid: parameters['raceCid'],
      contestCid: parameters['contestCid'],
      //~ requestType: 'online',
      requestType: 'competition_aftertask',
    };

    // @todo: Check that status is still is_live. Otherwise don't add checks to crontab any more.
    _requestRaceState(raceData, function response(raceInfo) {
      if (raceInfo && raceInfo.length > 0 && !$.isEmptyObject(raceInfo)) {
        // Show links if core is available
        $(".watch-links-race-id-"+raceData.raceId+" .task-live").show();
        //~ components_shown = ['link_live'];
        //~ visualRaceState(components_shown, raceData);
      } else {
        // If there is problem with data retrieval, bind this action to another timemark.
        var raceId = raceData.raceId;
        var coreApiAddress = raceData.coreApiAddress;
        var contestCid = raceData.contestCid;
        var raceCid = raceData.raceCid;

        // Time period and Timemark
        var period = 10;
        var new_timemark = crontab_currentTime + period;

        // add action to crontab
        action = { 'action' : 'checkCoreDataAvailable' , 'parameters' : { 'raceId' : raceId, 'coreApiAddress' : coreApiAddress, 'contestCid' : contestCid,  'raceCid' : raceCid } };
        pgRaceCrontabAdd (new_timemark, action);
      }
    });
  }

  // This is clone of requestRaceState() from pg_race_play_link.js
  function _requestRaceState(raceData, responseCallback) {
    /*'http://api.airtribune.com/v0.1.4/contest/cnts-130607-2736547863/race/r-23be3210-f0f7-49c3-b071-63da6cd56e61/tracks'*/
    $.ajax({
      url: raceData.coreApiAddress + '/contest/' + raceData.contestCid + '/race/' + raceData.raceCid + '/tracks?type=' + raceData.requestType,
      //url: raceData.coreApiAddress + '/contest/' + raceData.contestCid + '/race/' + raceData.raceCid + '/tracks?type=competition_aftertask',
      dataType:"json",
      success: responseCallback,
      error: function () {
        responseCallback(null);
      }});
  }

  // @todo: Move into single function. This is almost the same as checkCoreDataAvailable()
  // Check if data is available for given raceId and set another timemark action if required.
  // @todo: This check seems to be required only for "Leader board" links case.
  window.checkCoreDataAvailableFinished = function checkCoreDataAvailableFinished(timemark, parameters) {

    var raceId = parameters['raceId'];
    var coreApiAddress = parameters['coreApiAddress'];
    var contestCid = parameters['contestCid'];
    var raceCid = parameters['raceCid'];

    var raceData = {
      coreApiAddress: parameters['coreApiAddress'],
      raceId: parameters['raceId'],
      raceCid: parameters['raceCid'],
      contestCid: parameters['contestCid'],
      requestType: 'competition_aftertask',
    };

    _requestRaceState(raceData, function response(raceInfo) {
      if (raceInfo && raceInfo.length > 0 && !$.isEmptyObject(raceInfo)) {

        // Show links if core is available
        $(".watch-links-race-id-"+raceData.raceId+" .task-leaderboard").show();
        // setTimeout(function() {$(".watch-links-race-id-"+raceData.raceId+" .task-leaderboard").show();}, 5000);


        //~ components_shown = ['link_leaderboard'];
        //~ visualRaceState(components_shown, raceData);
      } else {
        // If there is problem with data retrieval, bind this action to another timemark.
        var raceId = raceData.raceId;
        var coreApiAddress = raceData.coreApiAddress;
        var contestCid = raceData.contestCid;
        var raceCid = raceData.raceCid;

        // Time period and Timemark
        var period = 10;
        var new_timemark = crontab_currentTime + period;

        // add action to crontab
        action = { 'action' : 'checkCoreDataAvailableFinished' , 'parameters' : { 'raceId' : raceId, 'coreApiAddress' : coreApiAddress, 'contestCid' : contestCid,  'raceCid' : raceCid } };
        pgRaceCrontabAdd (new_timemark, action);
      }
    });
  }


  // Replace timer help text.
  window.actionSetTimerHelpText = function actionSetTimerHelpText(timemark, parameters) {
    var raceId = parameters['raceId'];

    if (state_old == 'starting' && state_current == 'is_live' ) {
      // @todo: use translated string
      $(".timer-race-id-" + raceId + " .help-text").html("Race is on:");
    }
  }




  // Render and replace race timer html
  window.changeRaceTimerRendered = function changeRaceTimerRendered(index, parameters) {
    raceId = parameters.raceId;
    raceWatch = raceWatchRegistry[raceId];

    now_local = raceWatch['settings']['now_local'];
    start = raceWatch['settings']['start'];
    open = raceWatch['settings']['open'];
    end = raceWatch['settings']['end'];


    // current race status
    status = raceWatch['status']['current'];

    // seconds passed since race start (can be negative)
    diff = now_local - start;

    timer = diff + crontab_currentTime;
    timerRendered = renderRaceTimer(timer);
    $(".timer-race-id-" + raceId + " .time").html(timerRendered);

    // Change status from Awaiting / Starting to Is_live
    // @todo: maybe timer >= 0 because of possible page load delay (if it will be considered)
    if ((status == 'awaiting' || status == 'starting') && timer == 0) {
      raceChangeStatus(raceId, 'is_live', status);
    }

    else if (status == 'awaiting' && (now_local  + crontab_currentTime) >= open) {
      raceChangeStatus(raceId, 'starting', 'awaiting');
    }

    else if (status == 'is_live' && (now_local  + crontab_currentTime) >= end) {
      raceChangeStatus(raceId, 'finished', 'is_live');
    }
  }


  // ------------- HELPER FUNCTIONS ---------------------------

  // @todo
  // Show/Hide links components for current state
  //~ function visualRaceState(components_shown, raceData) {
    //~ console.log(components_shown);
//~
    //~ components_all = ['dayblog', 'timer', 'link_results', 'link_leaderboard', 'link_live'];
    //~ $.each (components_all, function(i, component) {
      //~ // op = ops.replace('raceId', raceData.raceId);
      //~ if ($.inArray(component, components_shown)) {
        //~ //
        //~ // $(op);
      //~ }
      //~ else {
        //~ //
      //~ }
    //~ });
  //~ }

  // Change raceWatch status and trigger "raceStateChange" event.
  function raceChangeStatus(raceId, status_current, status_old) {
    raceWatchRegistry[raceId]['status']['current'] = status_current;
    raceWatchRegistry[raceId]['status']['old'] = status_old;
    raceWatch = raceWatchRegistry[raceId];
    $(document).trigger('raceStateChange', { "raceWatch" : raceWatch , "state_current" : status_current , "state_old" : status_old } );
  }

  // convert time into H:i:s format
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
  // @todo: transform to be able to pass multiple actions
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
        //~ console.log(scheduled_timemark);
      }
    }
    //~ scheduled_timemark = timemark;
  }

})(jQuery);

