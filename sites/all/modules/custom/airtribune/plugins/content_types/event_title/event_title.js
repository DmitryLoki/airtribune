jQuery(function ($) {
  var timeLabel = $('#event-title .field-name-field-time-zone'),
    offset = Drupal.settings.airtribune_event_offset;
  function getTimeStr(h, m) {
    h = Math.abs(h);
    m = Math.abs(m);
    return (h < 10 ? "0" : "") + h + ":" + (m < 10 ? "0" : "") + m;
  }
  function setLocalTime(){
    var currentTime = new Date().getTime(),
      localTime = new Date(currentTime + offset*1000);

    timeLabel.html(getTimeStr(localTime.getUTCHours(),localTime.getUTCMinutes()));
    setTimeout(setLocalTime, 60*1000)
  }
  setLocalTime()
});