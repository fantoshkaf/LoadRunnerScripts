Action()
{

	lr_start_transaction("UC4_ViewBills");

	lr_start_transaction("01_OpenWebtours");

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
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("01_OpenWebtours",LR_AUTO);

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Priority", 
		"u=4");

	lr_think_time(39);

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value=user1", ENDITEM, 
		"Name=password", "Value=password1", ENDITEM, 
		LAST);

	lr_start_transaction("02_Login");

	lr_end_transaction("02_Login",LR_AUTO);

	lr_start_transaction("03_OpenBills");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("03_OpenBills",LR_AUTO);

	lr_end_transaction("UC4_ViewBills",LR_AUTO);

	return 0;
}