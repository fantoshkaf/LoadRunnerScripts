Action()
{
	lr_start_transaction("UC5_DelSel");

	lr_start_transaction("01_OpenWebTours");

	
	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_auto_header("Priority", 
		"u=0, i");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);


	lr_end_transaction("01_OpenWebTours",LR_AUTO);

	lr_start_transaction("02_Login");
	web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",LAST);
	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Priority", 
		"u=4");

	
	web_submit_form("login.pl", 
		"Snapshot=t3.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);

	lr_end_transaction("02_Login",LR_AUTO);
		web_reg_save_param_ex(
		"ParamName=flightID",
		"LB=flightID\" value\=\"",
		"RB=\"",
		"Ordinal=ALL",
		LAST);
		lr_start_transaction("03_OpenBills");


	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("03_OpenBills",LR_AUTO);

	lr_start_transaction("04_DelBill");
 	lr_save_string(lr_paramarr_random("flightID"),"RandflightID");
 			web_reg_find("Text={RandflightID}","Fail=Found",
		LAST);
	web_add_header("Origin", 
		"http://localhost:1080");

	web_submit_form("itinerary.pl", 
		"Snapshot=t6.inf", 
		ITEMDATA, 
		"Name=1", "Value=on", ENDITEM, 
		"Name=flightID", "Value={RandflightID}", ENDITEM, 
		"Name=removeFlights.x", "Value=78", ENDITEM, 
		"Name=removeFlights.y", "Value=1", ENDITEM, 
		LAST);
	lr_end_transaction("04_DelBill", LR_AUTO);
	lr_end_transaction("UC5_DelSel", LR_AUTO);


	return 0;
}