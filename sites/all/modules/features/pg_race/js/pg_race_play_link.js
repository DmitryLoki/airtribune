(function ($) {

  Drupal.behaviors.day_feature = {
    attach: function (context) {
      $('.race-links').each(function (i, raceBlock) {
        var $raceBlock = $(raceBlock);
        var timeHelperText = $raceBlock.find('.time'),
          helperText = $raceBlock.find('.help-text'),
          $raceButton = $raceBlock.parents('.views-field-day-pg-race-play-link'),
          raceTime;

        var setOnlineTime = function () {
          raceTime = Math.floor((raceData.raceStartTime - new Date().getTime()) / 1000);
          var absD = Math.abs(raceTime);
          timeHelperText.html((raceTime > 0 ? "-" : "") + getTimeStr(Math.floor(absD / 3600), Math.floor(absD % 3600 / 60), absD % 60));

          if (raceTime < 0) {
            var isRaceStateReady = timeHelperText.parents('.race-links').hasClass('race-block-activated');
            setOnlineTimeView(isRaceStateReady, raceTime, timeHelperText, helperText);
          }
          setTimeout(setOnlineTime, 1000);
        };

        var setOfflineTime = function() {
          raceTime = (Math.floor(raceData.raceDeadlineTime - raceData.raceStartTime) / 1000);
          timeHelperText.html(getTimeStr(Math.floor(raceTime / 3600), Math.floor(raceTime % 3600 / 60), raceTime % 60));
        }

        var raceData = getRaceDataFromRaceBlock($raceBlock);

        if (!raceData.isOnline) {
          $raceButton.hide();
          setOfflineTime();
        } else {
          setOnlineTime();
        }

        if (!raceData.raceId || !raceData.contestId) {
          return;
        }

        requestRaceState(raceData, function response(raceInfo) {
          if (raceInfo && raceInfo.length > 0 && !$.isEmptyObject(raceInfo)) {
            //make links clickable
            if (raceData.isOnline || raceData.requestType == 'online') {
              // Show online link before upload tracks from file
              isOnline = 'online';
            } else {
              isOnline = false;
            }
            setHrefAttr($raceBlock.find('a.race-link.2d'), raceData.raceEid, '2d', isOnline);
            setHrefAttr($raceBlock.find('a.race-link.3d'), raceData.raceEid, '3d', isOnline);
            $raceButton.show();
            $raceBlock.addClass('race-block-activated');
            if(raceData.isOnline) {
              setOnlineTimeView(true, raceTime, timeHelperText, helperText);
            }
          } else {
            if(raceData.isOnline) {
              setOnlineTimeView(false, raceTime, timeHelperText, helperText);
            } else {
              raceData.requestType = 'online';
            }
            setTimeout(function () {
              requestRaceState(raceData, response);
            }, 10000)
          }
        });
      });

      function setOnlineTimeView(isRaceStateReady, raceTime, timeHelperText, helperText) {
        var raceBlock = timeHelperText.parents('.race-links');
        if (raceTime <= 0) {
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
          raceStartTime: parseInt($raceBlock.data('start-time')),
          raceDeadlineTime: parseInt($raceBlock.data('deadline-time')),
          isOnline: $raceBlock.data('view-type') != undefined
        };

        raceData.requestType = raceData.isOnline || !hasTracksLoaded($raceBlock) ? 'online' : 'competition_aftertask';
        return raceData;
      }

      function hasTracksLoaded($raceBlock) {
        return $raceBlock.parents('div.event-day').find('.views-field-field-pg-race-tracks').length>0;
      }

      function setHrefAttr(link, raceEid, mode, isOnline) {
        link.attr('href', 'http://'+location.host+'/play/' + raceEid + '/' + mode + (isOnline ? '/online' : ''))
      }
    }
  }

})(jQuery);
