if (javascriptLoaderVersion == 2) {
	var jsDir = '/authored_framework/include/js/v2/'
	document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer-common.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'collapsemenu.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'items.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'mouseevents.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'elsevier2.js" type="text/javascript"></script>')
} else if (javascriptLoaderVersion == 3) {
	var jsDir = '/authored_framework/include/js/v3/'
	document.write('<script language="JavaScript" src="' + jsDir + 'elsevier2.js" type="text/javascript"></script>')
	var isHome = false
	if (location.pathname.indexOf('/homepage.cws_home') > -1) isHome = true
	if (!isHome) {
		jsDir = '/authored_framework/include/js/v3/menu/'
		document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer.js" type="text/javascript"></script>')
		document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer-common.js" type="text/javascript"></script>')
		document.write('<script language="JavaScript" src="' + jsDir + 'collapsemenu.js" type="text/javascript"></script>')
		document.write('<script language="JavaScript" src="' + jsDir + 'items.js" type="text/javascript"></script>')
		document.write('<script language="JavaScript" src="' + jsDir + 'mouseevents.js" type="text/javascript"></script>')
	} else {
		jsDir = '/authored_framework/include/js/v3/homemenu/'
		document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer.js" type="text/javascript"></script>')
		document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer-common.js" type="text/javascript"></script>')
		document.write('<script language="JavaScript" src="' + jsDir + 'collapsemenu.js" type="text/javascript"></script>')
		document.write('<script language="JavaScript" src="' + jsDir + 'homeItems.js" type="text/javascript"></script>')
		document.write('<script language="JavaScript" src="' + jsDir + 'mouseevents.js" type="text/javascript"></script>')
		
	}
} else if (javascriptLoaderVersion == 4) {
	var jsDir = '/authored_framework/include/js/v4/'
	document.write('<script language="JavaScript" src="' + jsDir + 'elsevier2.js" type="text/javascript"></script>')
	jsDir = '/authored_framework/include/js/v4/menu/'
	document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer-common.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'collapsemenu.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'mouseevents.js" type="text/javascript"></script>')
} else if (javascriptLoaderVersion == 5) {
	var jsDir = '/authored_framework/include/js/v5/menu/'
	document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer-common.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'mouseevents.js" type="text/javascript"></script>')
	jsDir = '/authored_framework/include/js/v5/'
	document.write('<script language="JavaScript" src="' + jsDir + 'elsevier2.js" type="text/javascript"></script>')
} else if (javascriptLoaderVersion == 99) {
	var jsDir = '/authored_framework/include/js/v99/menu/'
	document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer-common.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'collapsemenu.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'mouseevents.js" type="text/javascript"></script>')
	jsDir = '/authored_framework/include/js/v99/'
	document.write('<script language="JavaScript" src="' + jsDir + 'elsevier2.js" type="text/javascript"></script>')
} else {
	var jsDir = '/authored_framework/include/js/'
	document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'dynlayer-common.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'collapsemenu.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'items.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'mouseevents.js" type="text/javascript"></script>')
	document.write('<script language="JavaScript" src="' + jsDir + 'elsevier2.js" type="text/javascript"></script>')
}
