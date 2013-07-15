(function ($) {

  Drupal.behaviors.day_feature = {
    attach: function (context) {
      var timeHelperText = $("#time-counter"),
        helperText = $('.help-text'),
        d;
      if (typeof Drupal.settings.Day != 'undefined' && typeof Drupal.settings.Day.start_time != 'undefined') {
        var setTime = function () {

          d = Math.floor((Drupal.settings.Day.start_time - new Date().getTime()) / 1000);
          var absD = Math.abs(d);
          timeHelperText.html((d > 0 ? "-" : "") + getTimeStr(Math.floor(absD / 3600), Math.floor(absD % 3600 / 60), absD % 60));

          if (d < 0) {
            var isRaceStateReady = timeHelperText.parents('.race-links').hasClass('race-block-activated');
            setOnlineTimeView(isRaceStateReady);
          }
          setTimeout(setTime, 1000);
        };
        setTime();
      }

      $('.race-links').each(function (i, raceBlock) {
        var $raceBlock = $(raceBlock);
        var $raceButton = $raceBlock.parents('.views-field-day-pg-race-play-link');
        var raceData = getRaceDataFromRaceBlock($raceBlock);

        if (!raceData.isOnline) {
          $raceButton.hide();
        }

        if (!raceData.raceId || !raceData.contestId) {
          return;
        }

        requestRaceState(raceData, function response(raceInfo) {
          if (raceInfo && raceInfo.length > 0 && !$.isEmptyObject(raceInfo)) {
            console.log('enable links in ', $raceBlock);
            //make links clickable
            setHrefAttr($raceBlock.find('a.race-link.2d'), raceData.raceEid, '2d', raceData.isOnline);
            setHrefAttr($raceBlock.find('a.race-link.3d'), raceData.raceEid, '3d', raceData.isOnline);
            $raceButton.show();
            $raceBlock.addClass('race-block-activated');
            if(raceData.isOnline) {
              setOnlineTimeView(true);
            }
          } else {
            if(raceData.isOnline) {
              setOnlineTimeView(false);
            } else {
              raceData.requestType = 'online';
            }
            setTimeout(function () {
              requestRaceState(raceData, response);
            }, 10000)
          }
        });
      });

      function setOnlineTimeView(isRaceStateReady) {
        var raceBlock = timeHelperText.parents('.race-links');
        if (d <= 0) {
          raceBlock.removeClass('race-awaiting');
          if (isRaceStateReady) {
            raceBlock.addClass('race-online');
            helperText.text('Race is on');
            timeHelperText.show();
          } else {
            raceBlock.removeClass('race-online');
            timeHelperText.hide();
            helperText.text('Button will be here as soon as task is set.');
          }
        }
      }

      function getTimeStr(h, m, s) {
        h = Math.abs(h);
        m = Math.abs(m);
        s = Math.abs(s);
        return (h < 10 ? "0" : "") + h + ":" + (m < 10 ? "0" : "") + m + ":" + (s < 10 ? "0" : "") + s;
      }

      function requestRaceState(raceData, responseCallback) {
        /*'http://api.airtribune.com/v0.1.4/contest/cnts-130607-2736547863/race/r-23be3210-f0f7-49c3-b071-63da6cd56e61/tracks'*/
        $.ajax({
          url: Drupal.settings.pgRace.coreApiAddress + '/contest/' + raceData.contestId + '/race/' + raceData.raceId + '/tracks?type=' + raceData.requestType,
          dataType:"json",
          success: responseCallback,
          error: function () {
            responseCallback(null);
          }});
      }

      function getRaceDataFromRaceBlock($raceBlock) {
        var raceData = {
          contestId: $raceBlock.data('contest-cid'),
          raceId: $raceBlock.data('race-cid'),
          raceEid: $raceBlock.data('race-eid'),
          isOnline: $raceBlock.data('view-type') != undefined
        }

        raceData.requestType = raceData.isOnline || !hasTracksLoaded($raceBlock) ? 'online' : 'competition_aftertask';

        return raceData;
      }

      function hasTracksLoaded($raceBlock) {
        return $raceBlock.parents('div.event-day').find('.views-field-field-pg-race-tracks').length>0;
      }

      function setHrefAttr(link, raceEid, mode, isOnline) {
        link.attr('href', '/play/' + raceEid + '/' + mode + (isOnline ? '/online' : ''))
      }
    }
  }

})(jQuery);
