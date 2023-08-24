
var ajaxSettings = {
	url: '/node/49',
	dialogType: 'modal',
	dialog: { width: 600 },
};
var myAjaxObject = Drupal.ajax(ajaxSettings);
myAjaxObject.execute();