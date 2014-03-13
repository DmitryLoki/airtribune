jQuery(function ($) {

  var getTimeStr = function (h, m, s) {
    return (h < 10 ? "0" : "") + h + ":" + (m < 10 ? "0" : "") + m + ":" + (s < 10 ? "0" : "") + s;
  }

  var resortEnabled = /custom_order=test/.test(document.location.search);
  var sortOrder = /sort=desc/.test(document.location.search) ? "desc" : "asc";

  $('select.form-select-at_tracker').each(function (i, select) {
    updateTrackerStatusSpanId(select);
    handleSelectChange(select);
  });

  var run = function () {
    jQuery.ajax({
      url: Drupal.settings.at_core_sync.apiUrl + "/tracker",
      dataType: "json",
      success: function (result) {

        var statusSpans = $('.tracker-status[id$="-time"]');

        statusSpans.each(function(i, span) {
          var spanId = span.getAttribute('id'),
            trackerInfo = result.filter(function(tracker){
              return tracker.last_point && tracker.last_point.id + '-time' == spanId;
            })[0];

          if(!trackerInfo) return;
          span.trackerInfo = trackerInfo;

          if(trackerInfo.last_point.timestamp > 0) {
            var d = Math.floor((new Date).getTime()/1000 - trackerInfo.last_point.timestamp);
            span.innerHTML = getTimeStr(Math.floor(d/3600),Math.floor(d%3600/60),d%60);
          }

          if(trackerInfo.last_point.battery > 0) {
            $(span).closest('tr').find('.tracker-status[id$="-bat"]').html(trackerInfo.last_point.battery + '%');
          }

        });

        if (resortEnabled) {
          var keys = [];
          var tbl = statusSpans.closest('table');

          statusSpans.each(function(i, span){
            keys.push({key: span.trackerInfo.last_point.timestamp, span:span});
          });

          keys.sort(function (a, b) {
            if (a.key == null && b.key == null) return 0;
            if (a.key == null) return -1;
            if (b.key == null) return 1;
            return sortOrder == "desc" ? b.key - a.key : a.key - b.key;
          });
          for (var i = 0; i < keys.length; i++) {
            tbl.prepend($(keys[i].span).closest('tr'));
          }
        }

        setTimeout(run, 3000);
      }
    });
  }

  run();

  function updateTrackerStatusSpanId(select) {
    var $select = $(select),
      trackerName = $select.val(),
      tr = $select.closest('tr'),
      trackerStatusSpan = tr.find('.tracker-status');

    trackerStatusSpan.attr('id', trackerName !== 'none' ? (trackerName + '-time') : '');
  }

  function handleSelectChange(select) {
    var $select = $(select),
      form = $select.closest('form');

    var success = Drupal.ajax[$select.attr('id')].options.success;
    Drupal.ajax[$select.attr('id')].options.success = function (res, status) {
      success(res, status);
      updateTrackerStatusSpanId(select);
    }
  }
});
