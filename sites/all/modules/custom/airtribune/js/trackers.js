jQuery(document).ready(function() {

	var getTimeStr = function(h,m,s) {
		return (h<10?"0":"") + h + ":" + (m<10?"0":"") + m + ":" + (s<10?"0":"") + s;
	}

	var data = {};
	var tbl = jQuery("#manage-pilots-confirmed");
	var resortEnabled = /custom_order=test/.test(document.location.search) || !/order/.test(document.location.search);
	var sortOrder = /sort=desc/.test(document.location.search)?"desc":"asc";

	var run = function() {
		jQuery.ajax({
			url: "http://api.airtribune.com/v0.2/tracker",
			dataType: "json",
			success: function(result) {

				var needResort = false;

				for (var i = 0; i< result.length; i++) {
					var rw = {id:result[i].id,key:null,text:"No data"};
					if (result[i].last_point && result[i].last_point[3]>0) {
						var d = Math.floor((new Date).getTime()/1000 - result[i].last_point[3]);
						rw.key = result[i].last_point[3];
						rw.text = getTimeStr(Math.floor(d/3600),Math.floor(d%3600/60),d%60);
					}
					if (data[rw.id]) {
						if (data[rw.id].key != rw.key) {
							data[rw.id].key = rw.key;
							data[rw.id].text = rw.text;
							data[rw.id].dom.innerHTML = rw.text;
							needResort = true;
						}
					}
					else {
						var dom = document.getElementById(rw.id+"-time");
						if (dom) {
							data[rw.id] = {
								id: rw.id,
								key: rw.key,
								text: rw.text,
								dom: dom,
								trDom: jQuery("#"+rw.id+"-time").closest("tr")
							}
							console.log(data[rw.id]);
							dom.innerHTML = rw.text;
							needResort = true;
						}
					}
				}

				if (resortEnabled && needResort) {
					var keys = [];
					for (var id in data) {
						keys.push({id:id,key:data[id].key});
					}
					keys.sort(function(a,b) {
						if (a.key == null && b.key == null) return 0;
						if (a.key == null) return -1;
						if (b.key == null) return 1;
						return sortOrder=="desc" ? b.key-a.key : a.key-b.key;
					});
					for (var i = 0; i < keys.length; i++) {
						tbl.prepend(data[keys[i].id].trDom);
					}
				}

				setTimeout(run,3000);
			}
		});
	}
	run();

/*
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
					jQuery("#"+rw.id+"-time").empty().append(rw.diff).data("extr-field",rw.last_point[3]);
					jQuery("#"+rw.id+"-bat").empty().append(rw.last_point[4]).data("extr-field",rw.last_point[4]||0);
					jQuery("#manage-pilots-confirmed").trigger("update");
				}
				setTimeout(run,3000);
			}
		});
	}
	run();

	if (false && jQuery.tablesorter) {
		console.log("tablesorter",jQuery.tablesorter,jQuery("#manage-pilots-confirmed"));
		jQuery("#manage-pilots-confirmed").tablesorter({textExtraction:function(node) {
			return node.innerHTML;
			return jQuery(node).data("extr-field") || jQuery(node).text();
		}});
	}
*/

});
