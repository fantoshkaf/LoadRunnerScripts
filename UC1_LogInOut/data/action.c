Action()
{

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
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("01_OpenWebTours",LR_AUTO);

	lr_start_transaction("02_Login");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Priority", 
		"u=4");

	lr_think_time(38);

	web_submit_form("login.pl", 
		"Snapshot=t3.inf", 
		ITEMDATA, 
		"Name=username", "Value=User1", ENDITEM, 
		"Name=password", "Value=password1", ENDITEM, 
		LAST);

	lr_end_transaction("02_Login",LR_AUTO);

	lr_think_time(18);

	lr_start_transaction("03_Logout");

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t4.inf", 
		LAST);

	lr_end_transaction("03_Logout",LR_AUTO);

	return 0;
}