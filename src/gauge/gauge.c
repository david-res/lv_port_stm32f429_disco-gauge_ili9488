#include "../lv_examples/lv_examples.h"
#include "gauge.h"

LV_IMG_DECLARE(guage_bg_bar);
LV_EVENT_CB_DECLARE(reset_boost_peak);

int NeedleVal = 253;
float boostValue = 0.0;
float boostPeak = 2.0;
float egt = 520.0;
float oilt = 102.0;
float iat = 35.5;
float afr = 14.7;
float ign[5] = {0.0,0.0,0.0,0.0,0.0};
float ignPeak[5] = {0.0,0.0,0.0,0.0,0.0};

void my_task(lv_task_t * task);

lv_obj_t *gauge1;
int gauge_val = 0;
int counting = 1;
float power = 0.8;
static void reset_boost_peak(lv_obj_t * obj, lv_event_t event)
{

    if(event == LV_EVENT_CLICKED) {
        printf("Clicked\n");
        boostPeak = 22.0;
        boostValue = -220.2;
        afr = 8.8;
        egt = 1200.2;
        oilt = 99.1;
        iat = - 9.1;
        ign[1] = -10.0;
        ignPeak[0] = -10.0;
        NeedleVal = 240;
        lv_ex_get_started_guage();
    }
}




void lv_ex_get_started_guage(void)
{

	lv_task_t * task = lv_task_create(my_task, 10, LV_TASK_PRIO_MID, NULL);


//	lv_obj_t * obj0 = lv_obj_create(lv_scr_act(), NULL);
//	lv_obj_set_width(obj0, 320);
//	lv_obj_set_height(obj0, 240);
//	lv_obj_set_x(obj0,0);
//	lv_obj_set_y(obj0,0);

    lv_obj_t *tabview;
    tabview = lv_tabview_create(lv_scr_act(), NULL);
	lv_obj_set_width(tabview, 240);
	lv_obj_set_height(tabview, 320);
	lv_obj_set_x(tabview,0);
	lv_obj_set_y(tabview,0);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Gauge");
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Status");

	lv_obj_t *gauge_cont = lv_cont_create(tab1, NULL);
	lv_obj_clean_style_list(gauge_cont, LV_OBJ_PART_MAIN);
//	lv_obj_set_x(gauge_cont, 0);
//	lv_obj_set_y(gauge_cont, 0);
	lv_obj_set_width(gauge_cont, 240);
	lv_obj_set_height(gauge_cont, 320);

	lv_obj_t *param_cont = lv_obj_create(tab2, NULL);
	lv_obj_clean_style_list(param_cont, LV_OBJ_PART_MAIN);
//	lv_obj_set_x(param_cont, 280);
//	lv_obj_set_y(param_cont, 0);
	lv_obj_set_width(param_cont, 240);
	lv_obj_set_height(param_cont, 320);

	static lv_color_t needleC[1]; // Gauge Needle Color
	needleC[0].full = 0xF840;	  //0x0272;
	static lv_color_t needleCenter;
	needleCenter.full = 0x39E7;

	static lv_color_t boostPeakText;
	boostPeakText.full = 0xF840;

	static lv_style_t style1;
	lv_style_init(&style1);
	lv_style_set_bg_color(&style1, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_add_style(tabview,LV_OBJ_PART_MAIN, &style1);
	lv_style_set_border_width(&style1, LV_STATE_DEFAULT, 0);
	lv_style_set_radius(&style1, LV_STATE_DEFAULT, 0);

	static lv_style_t boostStyle;
	
	lv_style_init(&boostStyle);
	lv_style_set_text_color(&boostStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE); //
	//lv_style_set_text_font(&text1, LV_STATE_DEFAULT, &eurostile_extended_black_24px);  /*Set a larger font*/
	lv_style_set_text_font(&boostStyle, LV_STATE_DEFAULT, &lv_font_montserrat_24);  /*Set a larger font*/

	static lv_style_t boostPeakStyle;
	lv_style_init(&boostPeakStyle);
	if (boostPeak > 0){
	lv_style_set_text_color(&boostPeakStyle, LV_STATE_DEFAULT, boostPeakText); //
	}
	else{lv_style_set_text_color(&boostPeakStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	}
	//lv_style_set_text_font(&text1, LV_STATE_DEFAULT, &eurostile_extended_black_24px);  /*Set a larger font*/
	lv_style_set_text_font(&boostPeakStyle, LV_STATE_DEFAULT, &lv_font_montserrat_28);  /*Set a larger font*/

	static lv_style_t afrStyle;
	lv_style_init(&afrStyle);
	lv_style_set_text_color(&afrStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE); //
	//lv_style_set_text_font(&text1, LV_STATE_DEFAULT, &eurostile_extended_black_24px);  /*Set a larger font*/
	lv_style_set_text_font(&afrStyle, LV_STATE_DEFAULT, &lv_font_montserrat_24);  /*Set a larger font*/

	static lv_style_t paramStyle;
	lv_style_init(&paramStyle);
	lv_style_set_text_color(&paramStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE); //
	//lv_style_set_text_font(&text1, LV_STATE_DEFAULT, &eurostile_extended_black_24px);  /*Set a larger font*/
	lv_style_set_text_font(&paramStyle, LV_STATE_DEFAULT, &lv_font_montserrat_18);  /*Set a larger font*/

	static lv_style_t ignStyle;
	lv_style_init(&ignStyle);
	lv_style_set_text_color(&ignStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE); //
	//lv_style_set_text_font(&text1, LV_STATE_DEFAULT, &eurostile_extended_black_24px);  /*Set a larger font*/
	lv_style_set_text_font(&ignStyle, LV_STATE_DEFAULT, &lv_font_montserrat_14);  /*Set a larger font*/

	static lv_style_t ignPeakStyle;
	lv_style_init(&ignPeakStyle);
	lv_style_set_text_color(&ignPeakStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE); //
	//lv_style_set_text_font(&text1, LV_STATE_DEFAULT, &eurostile_extended_black_24px);  /*Set a larger font*/
	lv_style_set_text_font(&ignPeakStyle, LV_STATE_DEFAULT, &lv_font_montserrat_14);  /*Set a larger font*/

	static lv_style_t ignLed;
	lv_style_init(&ignLed);
	lv_style_set_bg_color(&ignLed, LV_LED_PART_MAIN, LV_COLOR_RED); // Set needle circle colo
	//lv_style_set_size(&ignLed, LV_LED_PART_MAIN, 6); // Ser needle Circle radiuos
	lv_style_set_border_color(&ignLed, LV_STATE_DEFAULT, LV_COLOR_RED);

	static lv_style_t needle1;
	lv_style_init(&needle1);
	lv_style_set_line_width(&needle1, LV_STATE_DEFAULT, 7);			  // Set needle width
	lv_style_set_line_rounded(&needle1, LV_STATE_DEFAULT, true);	  // Set needle end rounded corners
	lv_style_set_size(&needle1, LV_STATE_DEFAULT, 34);				  // Set needle Circle radius
	lv_style_set_bg_color(&needle1, LV_STATE_DEFAULT, LV_COLOR_GRAY); // Set needle circle color

	static lv_style_t settings_wheeel;
	lv_style_init(&settings_wheeel);
	lv_style_set_text_color(&settings_wheeel, LV_STATE_DEFAULT, LV_COLOR_WHITE); //
	//lv_style_set_text_font(&text1, LV_STATE_DEFAULT, &eurostile_extended_black_24px);  /*Set a larger font*/
	lv_style_set_text_font(&settings_wheeel, LV_STATE_DEFAULT, &lv_font_montserrat_22);  /*Set a larger font*/

	// lv_obj_t * settings = lv_label_create(obj0, NULL);
	// lv_obj_set_x(settings, 5);
	// lv_obj_set_y(settings, 5);
	// lv_obj_add_style(settings,LV_OBJ_PART_MAIN, &settings_wheeel);
	// lv_label_set_text(settings, LV_SYMBOL_SETTINGS);

	lv_obj_t *guage_bg = lv_img_create(gauge_cont, NULL); // gauge_cont is the parent object
	lv_img_set_src(guage_bg, &guage_bg_bar);

	gauge1 = lv_gauge_create(guage_bg, NULL);
	lv_obj_clean_style_list(gauge1, LV_GAUGE_PART_MAJOR);	  // Reset the gauge scale styles
	lv_obj_clean_style_list(gauge1, LV_GAUGE_PART_MAIN);	  // Reset the gauge scale styles
	lv_obj_add_style(gauge1, LV_GAUGE_PART_NEEDLE, &needle1); // Add style to the needle object
	lv_gauge_set_scale(gauge1, 266, 0, 0);
	lv_gauge_set_angle_offset(gauge1, -43);
	lv_gauge_set_range(gauge1, 0, 750);
	lv_gauge_set_needle_count(gauge1, 1, needleC);
	lv_obj_set_size(gauge1, 240, 240);
	lv_obj_align(gauge1, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * boostVal = lv_label_create(gauge_cont, NULL);
    if (boostValue>=0 && boostValue < 10){lv_obj_set_x(boostVal, 217);} // 0-9.9
    else if (boostValue>=10 && boostValue <100){lv_obj_set_x(boostVal, 186);}
    else if (boostValue>-10 && boostValue <0){lv_obj_set_x(boostVal, 206);}
    else if (boostValue>-100 && boostValue <=-10){lv_obj_set_x(boostVal, 175);}
    else if (boostValue>-1000 && boostValue <=-100){lv_obj_set_x(boostVal, 144);}
        lv_obj_set_y(boostVal, 230);
        lv_obj_add_style(boostVal,LV_OBJ_PART_MAIN, &boostStyle);
        lv_label_set_text_fmt(boostVal, "%.1f", boostValue); // %.1f sets two digits after the decimal point
	lv_obj_t * boostPeakVal = lv_label_create(gauge_cont, NULL);
	if (boostPeak>=0 && boostPeak < 10){lv_obj_set_x(boostPeakVal, 224);} // 0-9.9
	else if (boostPeak>=10 && boostPeak <100){lv_obj_set_x(boostPeakVal, 199);}
		lv_obj_set_y(boostPeakVal, 260);
		lv_obj_add_style(boostPeakVal,LV_OBJ_PART_MAIN, &boostPeakStyle);
		lv_obj_set_click(boostPeakVal, true);
		lv_obj_set_event_cb(boostPeakVal, reset_boost_peak);
		lv_label_set_text_fmt(boostPeakVal, "%.1f", boostPeak); // %.1f sets two digits after the decimal point

    lv_obj_t * afrLable = lv_label_create(param_cont, NULL);
        lv_obj_set_x(afrLable, 5);
        lv_obj_set_y(afrLable, 5);
        lv_obj_add_style(afrLable,LV_OBJ_PART_MAIN, &afrStyle);
        lv_label_set_text(afrLable,"AFR");
	lv_obj_t * afrVal = lv_label_create(param_cont, NULL);
	lv_obj_align(afrVal, afrLable, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
		lv_obj_set_y(afrVal, 5);
		lv_obj_add_style(afrVal,LV_OBJ_PART_MAIN, &afrStyle);

		if(afr < 13.5){
			lv_label_set_recolor(afrVal, true);
			lv_label_set_text_fmt(afrVal,"#CCCC00 %.2f#", afr);
		}// %.1f sets two digits after the decimal point
		else if (afr > 13.5 && afr < 15.7){
			lv_label_set_recolor(afrVal, true);
			lv_label_set_text_fmt(afrVal,"#00CC00 %.2f#", afr); // %.1f sets two digits after the decimal point
		}
		else if (afr > 15.7){
			lv_label_set_recolor(afrVal, true);
			lv_label_set_text_fmt(afrVal,"#CC0000 %.2f#", afr); // %.1f sets two digits after the decimal point
		}

	lv_obj_t * egtLabel = lv_label_create(param_cont, NULL);
		lv_obj_set_x(egtLabel, 5);
		lv_obj_set_y(egtLabel, 40);
		lv_obj_add_style(egtLabel,LV_OBJ_PART_MAIN, &paramStyle);
		lv_label_set_text(egtLabel,"EGT");
	lv_obj_t * egtVal = lv_label_create(param_cont, NULL);
		lv_obj_align(egtVal, egtLabel, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
		lv_obj_set_y(egtVal, 40);
		lv_obj_add_style(egtVal,LV_OBJ_PART_MAIN, &paramStyle);
		lv_label_set_text_fmt(egtVal,"%.1fc", egt); // %.1f sets two digits after the decimal point

	lv_obj_t * oiltLabel = lv_label_create(param_cont, NULL);
		lv_obj_set_x(oiltLabel, 5);
		lv_obj_set_y(oiltLabel, 70);
		lv_obj_add_style(oiltLabel,LV_OBJ_PART_MAIN, &paramStyle);
		lv_label_set_text(oiltLabel,"OIL");
	lv_obj_t * oiltVal = lv_label_create(param_cont, NULL);
	lv_obj_align(oiltVal, oiltLabel, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
		lv_obj_set_y(oiltVal, 70);
		lv_obj_add_style(oiltVal,LV_OBJ_PART_MAIN, &paramStyle);
		lv_label_set_text_fmt(oiltVal,"%.1fc", oilt); // %.1f sets two digits after the decimal point

	lv_obj_t * iatLabel = lv_label_create(param_cont, NULL);
		lv_obj_set_x(iatLabel, 5);
		lv_obj_set_y(iatLabel, 100);
		lv_obj_add_style(iatLabel,LV_OBJ_PART_MAIN, &paramStyle);
		lv_label_set_text(iatLabel,"IAT");
	lv_obj_t * iatVal = lv_label_create(param_cont, NULL);
	lv_obj_align(iatVal, iatLabel, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
		//lv_obj_set_x(iatVal, 407);
		lv_obj_set_y(iatVal, 100);
		lv_obj_add_style(iatVal,LV_OBJ_PART_MAIN, &paramStyle);
		lv_label_set_text_fmt(iatVal,"%.1fc", iat); // %.1f sets two digits after the decimal point

	lv_obj_t * cyl1Label = lv_label_create(param_cont, NULL);
		lv_obj_set_x(cyl1Label, 5);
		lv_obj_set_y(cyl1Label, 140);
		lv_obj_add_style(cyl1Label,LV_OBJ_PART_MAIN, &ignStyle);
		lv_label_set_text(cyl1Label,"CYL1");
	lv_obj_t * cyl2Label = lv_label_create(param_cont, NULL);
		lv_obj_set_x(cyl2Label, 5);
		lv_obj_set_y(cyl2Label, 160);
		lv_obj_add_style(cyl2Label,LV_OBJ_PART_MAIN, &ignStyle);
		lv_label_set_text(cyl2Label,"CYL2");
	lv_obj_t * cyl3Label = lv_label_create(param_cont, NULL);
		lv_obj_set_x(cyl3Label, 5);
		lv_obj_set_y(cyl3Label, 180);
		lv_obj_add_style(cyl3Label,LV_OBJ_PART_MAIN, &ignStyle);
		lv_label_set_text(cyl3Label,"CYL3");
	lv_obj_t * cyl4Label = lv_label_create(param_cont, NULL);
		lv_obj_set_x(cyl4Label, 5);
		lv_obj_set_y(cyl4Label, 200);
		lv_obj_add_style(cyl4Label,LV_OBJ_PART_MAIN, &ignStyle);
		lv_label_set_text(cyl4Label,"CYL4");
	lv_obj_t * cyl5Label = lv_label_create(param_cont, NULL);
		lv_obj_set_x(cyl5Label, 5);
		lv_obj_set_y(cyl5Label, 220);
		lv_obj_add_style(cyl5Label,LV_OBJ_PART_MAIN, &ignStyle);
		lv_label_set_text(cyl5Label,"CYL5");

	lv_obj_t * cyl1Val = lv_label_create(param_cont, NULL);
	if (ign[0] == 0 ) {lv_obj_set_x(cyl1Val, 120);}
	else if (ign[0] >-10 && ign[0]<0){lv_obj_set_x(cyl1Val, 200);}
	else if (ign[0] <=-10 && ign[0]-100){lv_obj_set_x(cyl1Val, 367);}
		lv_obj_set_y(cyl1Val, 140);
		lv_obj_add_style(cyl1Val,LV_OBJ_PART_MAIN, &ignStyle);
		lv_label_set_text_fmt(cyl1Val,"%.1f", ign[0]); // %.1f sets two digits after the decimal point
	lv_obj_t * cyl2Val = lv_label_create(param_cont, NULL);
	if (ign[1] == 0 ) {lv_obj_set_x(cyl2Val, 120);}
	else if (ign[1] >-10 && ign[1]<0){lv_obj_set_x(cyl2Val, 200);}
	else if (ign[1] <=-10 && ign[1]-100){lv_obj_set_x(cyl2Val, 367);}
		lv_obj_set_y(cyl2Val, 160);
		lv_obj_add_style(cyl2Val,LV_OBJ_PART_MAIN, &ignStyle);
		lv_label_set_text_fmt(cyl2Val,"%.1f", ign[1]); // %.1f sets two digits after the decimal point
	lv_obj_t * cyl3Val = lv_label_create(param_cont, NULL);
	if (ign[2] == 0 ) {lv_obj_set_x(cyl3Val, 120);}
	else if (ign[2] >-10 && ign[2]<0){lv_obj_set_x(cyl3Val, 200);}
	else if (ign[2] <=-10 && ign[2]-100){lv_obj_set_x(cyl3Val, 367);}
		lv_obj_set_y(cyl3Val, 180);
		lv_obj_add_style(cyl3Val,LV_OBJ_PART_MAIN, &ignStyle);
		lv_label_set_text_fmt(cyl3Val,"%.1f", ign[2]); // %.1f sets two digits after the decimal point
	lv_obj_t * cyl4Val = lv_label_create(param_cont, NULL);
	if (ign[3] == 0 ) {lv_obj_set_x(cyl4Val, 120);}
	else if (ign[3] >-10 && ign[3]<0){lv_obj_set_x(cyl4Val, 200);}
	else if (ign[3] <=-10 && ign[3]-100){lv_obj_set_x(cyl4Val, 367);}
		lv_obj_set_y(cyl4Val, 200);
		lv_obj_add_style(cyl4Val,LV_OBJ_PART_MAIN, &ignStyle);
		lv_label_set_text_fmt(cyl4Val,"%.1f", ign[3]); // %.1f sets two digits after the decimal point
	lv_obj_t * cyl5Val = lv_label_create(param_cont, NULL);
	if (ign[4] == 0 ) {lv_obj_set_x(cyl5Val, 120);}
	else if (ign[4] >-10 && ign[4]<0){lv_obj_set_x(cyl5Val, 200);}
	else if (ign[4] <=-10 && ign[4]-100){lv_obj_set_x(cyl5Val, 367);}
	lv_obj_set_y(cyl5Val, 220);
		lv_obj_add_style(cyl5Val,LV_OBJ_PART_MAIN, &ignStyle);
		lv_label_set_text_fmt(cyl5Val,"%.1f", ign[4]); // %.1f sets two digits after the decimal point

	lv_obj_t * cyl1ValPeak = lv_label_create(param_cont, NULL);
	if (ignPeak[0] == 0 ) {lv_obj_set_x(cyl1ValPeak, 180);}
		else if (ignPeak[0] >-10 &&ignPeak[0]<0){lv_obj_set_x(cyl1ValPeak, 446);}
		else if (ignPeak[0] <=-10 && ignPeak[0]-100){lv_obj_set_x(cyl1ValPeak, 435);}
		lv_obj_set_y(cyl1ValPeak, 140);
		lv_obj_add_style(cyl1ValPeak,LV_OBJ_PART_MAIN, &ignPeakStyle);
		lv_label_set_text_fmt(cyl1ValPeak,"%.1f", ignPeak[0]); // %.1f sets two digits after the decimal point
	lv_obj_t * cyl2ValPeak = lv_label_create(param_cont, NULL);
	if (ignPeak[1] == 0 ) {lv_obj_set_x(cyl2ValPeak, 180);}
	else if (ignPeak[1] >-10 &&ignPeak[1]<0){lv_obj_set_x(cyl2ValPeak, 446);}
	else if (ignPeak[1] <=-10 && ignPeak[1]-100){lv_obj_set_x(cyl2ValPeak, 435);}
		lv_obj_set_y(cyl2ValPeak, 160);
		lv_obj_add_style(cyl2ValPeak,LV_OBJ_PART_MAIN, &ignPeakStyle);
		lv_label_set_text_fmt(cyl2ValPeak,"%.1f", ignPeak[1]); // %.1f sets two digits after the decimal point
	lv_obj_t * cyl3ValPeak = lv_label_create(param_cont, NULL);
	if (ignPeak[2] == 0 ) {lv_obj_set_x(cyl3ValPeak, 180);}
	else if (ignPeak[2] >-10 &&ignPeak[2]<0){lv_obj_set_x(cyl3ValPeak, 446);}
	else if (ignPeak[2] <=-10 && ignPeak[2]-100){lv_obj_set_x(cyl3ValPeak, 435);}
		lv_obj_set_y(cyl3ValPeak, 180);
		lv_obj_add_style(cyl3ValPeak,LV_OBJ_PART_MAIN, &ignPeakStyle);
		lv_label_set_text_fmt(cyl3ValPeak,"%.1f", ignPeak[2]); // %.1f sets two digits after the decimal point
	lv_obj_t * cyl4ValPeak = lv_label_create(param_cont, NULL);
	if (ignPeak[3] == 0 ) {lv_obj_set_x(cyl4ValPeak, 180);}
	else if (ignPeak[3] >-10 &&ignPeak[3]<0){lv_obj_set_x(cyl4ValPeak, 446);}
	else if (ignPeak[3] <=-10 &&ignPeak[3]-100){lv_obj_set_x(cyl4ValPeak, 435);}
		lv_obj_set_y(cyl4ValPeak, 200);
		lv_obj_add_style(cyl4ValPeak,LV_OBJ_PART_MAIN, &ignPeakStyle);
		lv_label_set_text_fmt(cyl4ValPeak,"%.1f", ignPeak[3]); // %.1f sets two digits after the decimal point
	lv_obj_t * cyl5ValPeak = lv_label_create(param_cont, NULL);
	if (ignPeak[4] == 0 ) {lv_obj_set_x(cyl5ValPeak, 180);}
	else if (ignPeak[4] >-10 &&ignPeak[4]<0){lv_obj_set_x(cyl5ValPeak, 446);}
	else if (ignPeak[4] <=-10 &&ignPeak[4]-100){lv_obj_set_x(cyl5ValPeak, 435);}
		lv_obj_set_y(cyl5ValPeak, 220);
		lv_obj_add_style(cyl5ValPeak,LV_OBJ_PART_MAIN, &ignPeakStyle);
		lv_label_set_text_fmt(cyl5ValPeak,"%.1f", ignPeak[4]); // %.1f sets two digits after the decimal point

	lv_obj_t * led1 = lv_led_create(param_cont, NULL);
	lv_obj_align(led1, cyl1Val, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
//	lv_obj_align_x(led1, cyl1Val, 5, 0);
	lv_obj_set_size(led1, 12, 12);
		lv_obj_add_style(led1,LV_OBJ_PART_MAIN, &ignLed);
		if (ign[0]<0){lv_led_on(led1);}
		else {lv_led_off(led1);}
	lv_obj_t * led2 = lv_led_create(param_cont, NULL);
	lv_obj_align(led2, cyl2Val, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
		lv_obj_set_size(led2, 12, 12);
		lv_obj_add_style(led2,LV_OBJ_PART_MAIN, &ignLed);
		if (ign[1]<0){lv_led_on(led2);}
		else {lv_led_off(led2);}
	lv_obj_t * led3 = lv_led_create(param_cont, NULL);
	lv_obj_align(led3, cyl3Val, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
		lv_obj_set_size(led3, 12, 12);
		lv_obj_add_style(led3,LV_OBJ_PART_MAIN, &ignLed);
		lv_led_off(led3);
	lv_obj_t * led4 = lv_led_create(param_cont, NULL);
	lv_obj_align(led4, cyl4Val, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
		lv_obj_set_size(led4, 12, 12);
		lv_obj_add_style(led4,LV_OBJ_PART_MAIN, &ignLed);
		lv_led_off(led4);
//	lv_obj_t * led5 = lv_led_create(param_cont, NULL);
//	lv_obj_align(led5, cyl5Val, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
//		lv_obj_set_size(led5, 12, 12);
//		lv_obj_add_style(led5,LV_OBJ_PART_MAIN, &ignLed);
//		lv_led_off(led5);
}


void my_task(lv_task_t * task)
{
	/*Use the user_data*/
	if(gauge_val>=750) {
		gauge_val = 750;
		counting = 0;
	}
	if(gauge_val<=0) {
		gauge_val = 0;
		counting = 1;
	}

	if(counting == 1){
		lv_gauge_set_value(gauge1, 0, gauge_val+=50);
//		gauge_val++;
	} else
	lv_gauge_set_value(gauge1, 0, gauge_val-=10);
}
