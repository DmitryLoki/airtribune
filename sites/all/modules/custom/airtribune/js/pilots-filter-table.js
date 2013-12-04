jQuery(function ($) {
  $(".pane-paragliding-pilots-list-manage table, .pane-paragliding-pilots-list-manage-confirmed table").filterTable({
    minRows: 0,
    label: ""
  });
  var $main_input = $(".filter-table:first input");
  $main_input.keyup(function(){
    $(".filter-table input").not(this).val(jQuery(this).val()).keyup();
  });
  $(".filter-table input").not($main_input).parent().hide();
});
