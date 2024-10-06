#include "randString.c"

Action()
{	
    char username[17]; 
    char password[17]; 
    char firstName[17]; 
    char lastName[17];
    char address1[31]; 
    char address2[31]; 


    generate_random_string(username, 16); 
    generate_random_string(password, 16); 
    generate_random_string(firstName, 16); 
    generate_random_string(lastName, 16);
    generate_random_string(address1, 30); 
    generate_random_string(address2, 30);


    lr_save_string(username, "login");
    lr_save_string(password, "password");
    lr_save_string(firstName, "firstname");
    lr_save_string(lastName, "lastName");
    lr_save_string(address1, "address1");
    lr_save_string(address2, "address2");
    lr_start_transaction("UC6_Register");
	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_header("Priority", 
		"u=2");


	lr_start_transaction("open_web_tours");

	
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


	lr_end_transaction("open_web_tours",LR_AUTO);
	lr_think_time(21);

	lr_start_transaction("click_Signup");
	web_reg_find("Text=First time registering? Please complete the form below.",LAST);
	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("click_Signup",LR_AUTO);

	lr_start_transaction("send_reg_Info");

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
		"Name=address2", "Value={address}", ENDITEM, 
		"Name=register.x", "Value=51", ENDITEM, 
		"Name=register.y", "Value=4", ENDITEM, 
		LAST);

	lr_end_transaction("send_reg_Info",LR_AUTO);

	lr_think_time(15);

	lr_start_transaction("login_aft_reg");
	web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",LAST);
	web_image("button_next.gif", 
		"Src=/WebTours/images/button_next.gif", 
		"Snapshot=t7.inf", 
		LAST);

	lr_end_transaction("login_aft_reg",LR_AUTO);



	lr_start_transaction("logout");
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t4.inf", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	lr_end_transaction("UC6_Register",LR_AUTO);

	return 0;
}