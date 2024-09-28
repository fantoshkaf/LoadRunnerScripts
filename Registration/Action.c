Action()
{

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_header("Priority", 
		"u=2");

	lr_start_transaction("UC6_Register");
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
	lr_think_time(21);

	lr_start_transaction("02_ClickSignup");
	web_reg_find("Text=First time registering? Please complete the form below.",LAST);
	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("02_ClickSignup",LR_AUTO);

	lr_start_transaction("03_SendRegInfo");

	web_add_header("Origin", 
		"http://localhost:1080");
	web_reg_find("Text=Thank you, <b>{login}</b>, for registering and welcome to the Web Tours family.",LAST);
	web_submit_form("login.pl_2", 
		"Snapshot=t6.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={password}", ENDITEM, 
		"Name=firstName", "Value={firstname}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={address1}", ENDITEM, 
		"Name=address2", "Value={firstname}", ENDITEM, 
		"Name=register.x", "Value=51", ENDITEM, 
		"Name=register.y", "Value=4", ENDITEM, 
		LAST);

	lr_end_transaction("03_SendRegInfo",LR_AUTO);

	lr_think_time(15);

	lr_start_transaction("04_LoginAfterReg");
	web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",LAST);
	web_image("button_next.gif", 
		"Src=/WebTours/images/button_next.gif", 
		"Snapshot=t7.inf", 
		LAST);

	lr_end_transaction("04_LoginAfterReg",LR_AUTO);

	lr_end_transaction("UC6_Register",LR_AUTO);

	return 0;
}