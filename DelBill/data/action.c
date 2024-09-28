Action()
{

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

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Priority", 
		"u=4");

	lr_think_time(6);

	web_submit_form("login.pl", 
		"Snapshot=t3.inf", 
		ITEMDATA, 
		"Name=username", "Value=user1", ENDITEM, 
		"Name=password", "Value=password1", ENDITEM, 
		LAST);

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t4.inf", 
		LAST);

	web_add_header("Origin", 
		"http://localhost:1080");

	web_submit_form("itinerary.pl", 
		"Snapshot=t6.inf", 
		ITEMDATA, 
		"Name=1", "Value=on", ENDITEM, 
		LAST);

	return 0;
}