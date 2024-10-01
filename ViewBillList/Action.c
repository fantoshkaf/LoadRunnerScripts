Action()
{

	lr_start_transaction("UC4_ViewBills");
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

	lr_start_transaction("03_OpenBills");

	web_reg_find("Text=<b>Itinerary</font></b>",
		LAST);

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("03_OpenBills",LR_AUTO);
	lr_end_transaction("04_Login",LR_AUTO);

	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	lr_start_transaction("03_Logout");

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t4.inf", 
		LAST);

	lr_end_transaction("04_Logout",LR_AUTO);
	lr_end_transaction("UC4_ViewBills",LR_AUTO);

	return 0;
}