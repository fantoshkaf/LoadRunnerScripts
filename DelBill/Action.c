Action()
{
    int i;
    lr_start_transaction("UC5_DelSel");

    lr_start_transaction("01_OpenWebTours");

    web_set_sockets_option("SSL_VERSION", "2&3");

    web_add_auto_header("Priority", "u=0, i");
    web_add_auto_header("Upgrade-Insecure-Requests", "1");

    web_reg_find("Text=Welcome to the Web Tours site.", LAST);

    web_url("WebTours",
        "URL=http://localhost:1080/WebTours/",
        "Resource=0",
        "RecContentType=text/html",
        "Referer=",
        "Snapshot=t2.inf",
        "Mode=HTML",
        LAST);

    lr_end_transaction("01_OpenWebTours", LR_AUTO);

    lr_start_transaction("02_Login");

    web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages.", LAST);
    web_add_header("Origin", "http://localhost:1080");
    web_add_auto_header("Priority", "u=4");

    web_submit_form("login.pl",
        "Snapshot=t3.inf",
        ITEMDATA,
        "Name=username", "Value={login}", ENDITEM,
        "Name=password", "Value={password}", ENDITEM,
        LAST);

    lr_end_transaction("02_Login", LR_AUTO);
    
    	lr_start_transaction("03_OpenBills");
    web_reg_save_param_ex("ParamName=c_flightids", "LB=flightID\" value=\"", "RB=\"", "Ordinal=ALL", LAST);
    web_reg_save_param_ex("ParamName=c_cgifields", "LB=cgifields\" value=\"", "RB=\"", "Ordinal=ALL", LAST);
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



    lr_start_transaction("04_DelBill");

    lr_save_string("", "c_buffer");

    for (i=1;i<=atoi(lr_eval_string("{c_flightids_count}"));i++)
    {
    	lr_save_string(lr_paramarr_random("c_cgifields"),"c_rand");

		lr_param_sprintf("c_buffer", "%s%d=on&", lr_eval_string("{c_buffer}"), atoi(lr_eval_string("{c_rand}")));

    }



    for (i=1;i<=atoi(lr_eval_string("{c_flightids_count}"));i++)
    {
        lr_param_sprintf("c_buffer",
        "%sflightID=%s&",
        lr_eval_string("{c_buffer}"),
        lr_paramarr_idx("c_flightids",
        i));

        lr_param_sprintf("c_buffer",
        "%s.cgifields=%s&",
        lr_eval_string("{c_buffer}"),
        lr_paramarr_idx("c_cgifields",
        i));
    }


    lr_save_string(lr_eval_string("{c_buffer}removeFlights.x=57&removeFlights.y=10&"), "c_wcr");

    lr_save_string(lr_eval_string(lr_eval_string("{c_flightids_{c_flightids_count}}")),
    "c_cancelflight");


    web_reg_find("Text={c_cancelflight}", "Fail=Found", LAST);


    web_custom_request("itinerary.pl_2",
    "URL=http://localhost:1080/cgi-bin/itinerary.pl",
    "Method=POST",
    "Resource=0",
    "RecContentType=text/html",
    "Referer=http://localhost:1080/cgi-bin/itinerary.pl",
    "Snapshot=t23.inf",
    "Mode=HTTP",
    "Body={c_wcr}",
    LAST);

    lr_end_transaction("04_DelBill", LR_AUTO);
	lr_start_transaction("05_Logout");
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	web_url("welcome.pl_2", 
    "URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
    "Resource=0", 
    "RecContentType=text/html", 
    "Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
    "Snapshot=t5.inf", 
    "Mode=HTML", 
    LAST);
	lr_end_transaction("05_Logout",LR_AUTO);
    lr_end_transaction("UC5_DelSel", LR_AUTO);

    return 0;
}