Action()
{

	lr_start_transaction("UC2_Search_Flight");
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
		"Snapshot=t16.inf", 
		"Mode=HTML", 
		LAST);


	lr_end_transaction("open_web_tours",LR_AUTO);

	lr_start_transaction("login");
	web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",LAST);
	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Priority", 
		"u=4");

	
	web_submit_form("login.pl", 
		"Snapshot=t17.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);



	lr_start_transaction("open_flights");
		web_reg_save_param_ex(
		"ParamName=Cities",
		"LB=option value=\"",
		"RB=\"",
		"Ordinal=ALL",
		LAST);

	web_reg_find("Text=\<td align\=\"left\"\>Departure City :\</td> \<td\>\<select name\=\"depart\" \>",LAST);
	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t18.inf", 
		LAST);

	lr_end_transaction("open_flights",LR_AUTO);

	lr_start_transaction("search_flights");

	web_add_header("Origin", 
		"http://localhost:1080");
 	lr_save_string(lr_paramarr_random("Cities"),"DepCity");
	do {
    	lr_save_string(lr_paramarr_random("Cities"), "ArrCity");
	} while (strcmp(lr_eval_string("{DepCity}"), lr_eval_string("{ArrCity}")) == 0);
	web_reg_find("Text=Flight departing from <B>{DepCity}</B> to <B>{ArrCity}</B> on <B>{depDate}</B>",LAST);
	web_submit_form("reservations.pl",
		"Snapshot=t19.inf",
		ITEMDATA,
		"Name=depart", "Value={DepCity}", ENDITEM,
		"Name=departDate", "Value={depDate}", ENDITEM,
		"Name=arrive", "Value={ArrCity}", ENDITEM,
		"Name=returnDate", "Value={retDate}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=roundtrip", "Value=<OFF>", ENDITEM,
		"Name=seatPref", "Value={pref}", ENDITEM,
		"Name=seatType", "Value={type}", ENDITEM,
		"Name=findFlights.x", "Value=83", ENDITEM,
		"Name=findFlights.y", "Value=16", ENDITEM,
		LAST);

	lr_end_transaction("search_flights",LR_AUTO);


	lr_start_transaction("logout");
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t4.inf", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	lr_end_transaction("UC2_Search_Flight",LR_AUTO);
	return 0;
}