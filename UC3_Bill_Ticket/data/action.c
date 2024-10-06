Action()
{

	lr_start_transaction("UC3_BillTicket");

	lr_start_transaction("01_OpenWebTours");

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_auto_header("Priority", 
		"u=0, i");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("01_OpenWebTours",LR_AUTO);

	lr_start_transaction("02_Login");

	web_add_auto_header("Priority", 
		"u=4");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(20);

	web_submit_form("login.pl", 
		"Snapshot=t15.inf", 
		ITEMDATA, 
		"Name=username", "Value=user1", ENDITEM, 
		"Name=password", "Value=password1", ENDITEM, 
		LAST);

	lr_end_transaction("02_Login",LR_AUTO);

	lr_start_transaction("03_OpenFlights");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(9);

	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t16.inf", 
		LAST);

	lr_end_transaction("03_OpenFlights",LR_AUTO);

	lr_start_transaction("04_SearchFlights");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	lr_think_time(12);

	web_submit_form("reservations.pl", 
		"Snapshot=t17.inf", 
		ITEMDATA, 
		"Name=depart", "Value=Denver", ENDITEM, 
		"Name=departDate", "Value=09/28/2024", ENDITEM, 
		"Name=arrive", "Value=Frankfurt", ENDITEM, 
		"Name=returnDate", "Value=09/29/2024", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=roundtrip", "Value=<OFF>", ENDITEM, 
		"Name=seatPref", "Value=None", ENDITEM, 
		"Name=seatType", "Value=Coach", ENDITEM, 
		LAST);

	lr_end_transaction("04_SearchFlights",LR_AUTO);

	lr_think_time(15);

	lr_start_transaction("05_SelectFlight");

	web_submit_form("reservations.pl_2", 
		"Snapshot=t18.inf", 
		ITEMDATA, 
		"Name=outboundFlight", "Value=010;386;09/28/2024", ENDITEM, 
		"Name=reserveFlights.x", "Value=72", ENDITEM, 
		"Name=reserveFlights.y", "Value=15", ENDITEM, 
		LAST);

	lr_end_transaction("05_SelectFlight",LR_AUTO);

	lr_think_time(23);

	lr_start_transaction("06_PayForFlight");

	web_submit_form("reservations.pl_3", 
		"Snapshot=t19.inf", 
		ITEMDATA, 
		"Name=firstName", "Value=name1", ENDITEM, 
		"Name=lastName", "Value=lastName1", ENDITEM, 
		"Name=address1", "Value=Place1", ENDITEM, 
		"Name=address2", "Value=Place1", ENDITEM, 
		"Name=pass1", "Value=name1 lastName1", ENDITEM, 
		"Name=creditCard", "Value=45345", ENDITEM, 
		"Name=expDate", "Value=33/44", ENDITEM, 
		"Name=saveCC", "Value=<OFF>", ENDITEM, 
		LAST);

	lr_end_transaction("06_PayForFlight",LR_AUTO);

	lr_end_transaction("UC3_BillTicket",LR_AUTO);

	return 0;
}