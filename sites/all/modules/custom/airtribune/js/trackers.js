jQuery(document).ready(function() {

	var getTimeStr = function(h,m,s) {
		return (h<10?"0":"") + h + ":" + (m<10?"0":"") + m + ":" + (s<10?"0":"") + s;
	}

	var run = function() {
		jQuery.ajax({
			url: "http://api.airtribune.com/v0.2/tracker",
			dataType: "json",
			success: function(result) {
				for (var i = 0; i< result.length; i++) {
					var rw = result[i];
					if (rw.last_point && rw.last_point[3]>0) {
						var d = Math.floor((new Date).getTime()/1000 - rw.last_point[3]);
						rw.diff = getTimeStr(Math.floor(d/3600),Math.floor(d%3600/60),d%60);
					}
					else {
						rw.diff = "No data";
					}
					jQuery("#"+rw.id).empty().append(rw.diff);
				}
				setTimeout(run,3000);
			}
		});
	}
	run();
});