Action()
{

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_header("Priority", 
		"u=2");

	web_custom_request("XjA", 
		"URL=http://o.pki.goog/s/wr3/XjA", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/ocsp-response", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		"EncType=application/ocsp-request", 
		"BodyBinary=0Q0O0M0K0I0\t\\x06\\x05+\\x0E\\x03\\x02\\x1A\\x05\\x00\\x04\\x14\\x12\\xABH\\xB9\\xB7c\\xDA~-\\x86\\xC3\\xDB\\xB3\\xC2w;)7-Z\\x04\\x14\\xC7\\x81\\xF5\\xFD\\x8E\\x88\\xD9\\x00<Mc\\xA2P1$\\xA0\\xCE#\\xFE#\\x02\\x10^0:\\x03\\xA5\\x8A\\xBFB\t:\\xE3\\xD0\\x9E\\xB39\\x8C", 
		LAST);

	lr_start_transaction("UC6_Register");

	lr_start_transaction("01_OpenWebtours");

	web_add_auto_header("Priority", 
		"u=4");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(31);

	web_url("header.html", 
		"URL=http://localhost:1080/WebTours/header.html", 
		"Resource=0", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("01_OpenWebtours",LR_AUTO);

	lr_think_time(21);

	lr_start_transaction("02_ClickSignup");

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

	web_submit_form("login.pl_2", 
		"Snapshot=t6.inf", 
		ITEMDATA, 
		"Name=username", "Value=qwert", ENDITEM, 
		"Name=password", "Value=qwe", ENDITEM, 
		"Name=passwordConfirm", "Value=qwe", ENDITEM, 
		"Name=firstName", "Value=qwe", ENDITEM, 
		"Name=lastName", "Value=qwe", ENDITEM, 
		"Name=address1", "Value=qwe", ENDITEM, 
		"Name=address2", "Value=qwe", ENDITEM, 
		"Name=register.x", "Value=51", ENDITEM, 
		"Name=register.y", "Value=4", ENDITEM, 
		LAST);

	lr_end_transaction("03_SendRegInfo",LR_AUTO);

	lr_think_time(15);

	lr_start_transaction("04_LoginAfterReg");

	web_image("button_next.gif", 
		"Src=/WebTours/images/button_next.gif", 
		"Snapshot=t7.inf", 
		LAST);

	lr_end_transaction("04_LoginAfterReg",LR_AUTO);

	lr_end_transaction("UC6_Register",LR_AUTO);

	return 0;
}