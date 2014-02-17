(function ($) {

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


      // @todo
      if (Drupal.settings.pg_race.task_watch != 'undefined') {
        $.each(Drupal.settings.pg_race.task_watch, function(index, pg_race_watch_settings) {
          $.each(pg_race_watch_settings, function(i, pg_race_watch_setting) {
            function_name = pg_race_watch_setting.function_name;
            window[function_name](pg_race_watch_setting);
            //~ pg_race_frontpage_live_events_links(pg_race_watch_setting);
          });
        });
      }
    }
  }

  //~ function pg_race_frontpage_live_events_links(race_watch_setting) {
    //~ alert('tset 2');
  //~ }
})(jQuery);

  // Name of this function is passed in pg_race_watch_setting.function_name
  function pg_race_frontpage_live_events_links(race_watch_setting) {
    console.log(race_watch_setting);
  }
