Action()
{

	lr_start_transaction("UC5_DelSel");

	lr_start_transaction("01_OpenWebTours");

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_auto_header("Priority", 
		"u=4");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_custom_request("header.html", 
		"URL=http://localhost:1080/WebTours/header.html", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t3.inf", 
		"Mode=HTTP", 
		LAST);

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Priority", 
		"u=5, i");

	web_custom_request("hp_logo.png", 
		"URL=http://localhost:1080/WebTours/images/hp_logo.png", 
		"Method=GET", 
		"Resource=1", 
		"RecContentType=image/png", 
		"Referer=http://localhost:1080/WebTours/header.html", 
		"Snapshot=t4.inf", 
		LAST);

	web_custom_request("webtours.png", 
		"URL=http://localhost:1080/WebTours/images/webtours.png", 
		"Method=GET", 
		"Resource=1", 
		"RecContentType=image/png", 
		"Referer=http://localhost:1080/WebTours/header.html", 
		"Snapshot=t6.inf", 
		LAST);

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	web_custom_request("nav.pl", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t7.inf", 
		"Mode=HTTP", 
		LAST);

	lr_end_transaction("01_OpenWebTours",LR_AUTO);

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Priority", 
		"u=4");

	lr_think_time(22);

	web_custom_request("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t9.inf", 
		"Mode=HTTP", 
		"Body=userSession=139980.150101256HcAAccipQHAiDDDDtDcAVpDHDicf&username=use1&password=pass1234&login.x=0&login.y=0&JSFormSubmit=off", 
		LAST);

	web_concurrent_start(NULL);

	web_custom_request("error.pl", 
		"URL=http://localhost:1080/cgi-bin/error.pl?error=badPassword", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t10.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("nav.pl_2", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?username=use1&password=pass1234", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t11.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_think_time(18);

	lr_start_transaction("02_Login");

	web_custom_request("login.pl_2", 
		"URL=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?username=use1&password=pass1234", 
		"Snapshot=t12.inf", 
		"Mode=HTTP", 
		"Body=userSession=139980.150101256HcAAccipQHAiDDDDtDcAVpDHDicf&username=user1&password=pass1234&login.x=61&login.y=7&JSFormSubmit=off", 
		LAST);

	web_concurrent_start(NULL);

	web_custom_request("nav.pl_3", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t13.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("login.pl_3", 
		"URL=http://localhost:1080/cgi-bin/login.pl?intro=true", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t14.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	web_concurrent_start(NULL);

	web_custom_request("flights.gif", 
		"URL=http://localhost:1080/WebTours/images/flights.gif", 
		"Method=GET", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t15.inf", 
		LAST);

	web_custom_request("in_home.gif", 
		"URL=http://localhost:1080/WebTours/images/in_home.gif", 
		"Method=GET", 
		"Resource=1", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t16.inf", 
		LAST);

	web_custom_request("itinerary.gif", 
		"URL=http://localhost:1080/WebTours/images/itinerary.gif", 
		"Method=GET", 
		"Resource=1", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t17.inf", 
		LAST);

	web_custom_request("signoff.gif", 
		"URL=http://localhost:1080/WebTours/images/signoff.gif", 
		"Method=GET", 
		"Resource=1", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t18.inf", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("02_Login",LR_AUTO);

	lr_start_transaction("03_OpenBills");

	web_revert_auto_header("Origin");

	lr_think_time(13);

	web_custom_request("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t19.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_custom_request("nav.pl_4", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t20.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("itinerary.pl", 
		"URL=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t21.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	web_concurrent_start(NULL);

	web_custom_request("cancelreservation.gif", 
		"URL=http://localhost:1080/WebTours/images/cancelreservation.gif", 
		"Method=GET", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t22.inf", 
		LAST);

	web_custom_request("cancelallreservations.gif", 
		"URL=http://localhost:1080/WebTours/images/cancelallreservations.gif", 
		"Method=GET", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t23.inf", 
		LAST);

	web_concurrent_end(NULL);

	web_concurrent_start(NULL);

	web_custom_request("in_itinerary.gif", 
		"URL=http://localhost:1080/WebTours/images/in_itinerary.gif", 
		"Method=GET", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t24.inf", 
		LAST);

	web_custom_request("home.gif", 
		"URL=http://localhost:1080/WebTours/images/home.gif", 
		"Method=GET", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t25.inf", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("03_OpenBills",LR_AUTO);

	lr_start_transaction("04_DelBill");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(38);

	web_custom_request("itinerary.pl_2", 
		"URL=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t26.inf", 
		"Mode=HTTP", 
		"Body=1=on&flightID=0-7-JD&removeFlights.x=49&removeFlights.y=7&.cgifields=1", 
		LAST);

	lr_end_transaction("04_DelBill",LR_AUTO);

	lr_think_time(15);

	lr_start_transaction("05_Logout");

	web_custom_request("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t27.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("nav.pl_5", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"Snapshot=t28.inf", 
		"Mode=HTTP", 
		LAST);

	lr_end_transaction("05_Logout",LR_AUTO);

	lr_end_transaction("UC5_DelSel",LR_AUTO);

	return 0;
}