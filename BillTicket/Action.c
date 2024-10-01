Action()
{

	lr_start_transaction("UC3_BillTicket");
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
		"Snapshot=t16.inf", 
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
		"Snapshot=t17.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);

	lr_end_transaction("02_Login",LR_AUTO);



	lr_start_transaction("03_OpenFlights");
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

	lr_end_transaction("03_OpenFlights",LR_AUTO);

	lr_start_transaction("04_SearchFlights");
	web_reg_save_param_ex(
		"ParamName=outboundFlight",
		"LB=outboundFlight\" value\=\"",
		"RB=\"",
		"Ordinal=ALL",
		LAST);

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

	lr_end_transaction("04_SearchFlights",LR_AUTO);
	lr_think_time(15);

	lr_start_transaction("05_SelectFlight");


	lr_save_string(lr_paramarr_random("outboundFlight"),"SelOutboundFlight");
	web_reg_find("Text=<b>Payment Details</font></b>",
		LAST);

web_submit_form("reservations.pl_2", 
		"Snapshot=t20.inf", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={SelOutboundFlight}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={pref}", ENDITEM,
		"Name=seatType", "Value={type}", ENDITEM,
		"Name=reserveFlights.x", "Value=45", ENDITEM, 
		"Name=reserveFlights.y", "Value=14", ENDITEM, 
		LAST);
	
	lr_end_transaction("05_SelectFlight",LR_AUTO);

	lr_think_time(23);

	lr_start_transaction("06_PayForFlight");
 

	web_reg_find("Text=Thank you for booking through Web Tours.",
		LAST);

	web_submit_form("reservations.pl_3", 
		"Snapshot=t21.inf", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={address1}", ENDITEM, 
		"Name=address2", "Value={address2}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=creditCard", "Value={card}", ENDITEM, 
		"Name=expDate", "Value={expCard}", ENDITEM, 
		"Name=saveCC", "Value=<OFF>", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={pref}", ENDITEM,
		"Name=seatType", "Value={type}", ENDITEM,
		"Name=outboundFlight", "Value={SelOutboundFlight}", ENDITEM, 
		"Name=buyFlights.x", "Value=62", ENDITEM, 
		"Name=buyFlights.y", "Value=9", ENDITEM, 
		LAST);

	lr_end_transaction("06_PayForFlight",LR_AUTO);
	lr_end_transaction("07_Login",LR_AUTO);

	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	lr_start_transaction("03_Logout");

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t4.inf", 
		LAST);

	lr_end_transaction("07_Logout",LR_AUTO);
	lr_end_transaction("UC3_BillTicket",LR_AUTO);

	return 0;
}