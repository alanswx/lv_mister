#include "lvgl/lvgl.h"
#include "lv_ex_conf.h"


lv_obj_t * password=NULL;

static lv_res_t list_release_action(lv_obj_t * list_btn)
{
    printf("List element click:%s\n", lv_list_get_btn_text(list_btn));

    if (password) lv_obj_set_hidden(password,false);
    return LV_RES_OK; /*Return OK because the list is not deleted*/
}
static lv_res_t btn_click_action(lv_obj_t * btn)
{
    uint8_t id = lv_obj_get_free_num(btn);

    printf("Button %d is released\n", id);

    /* The button is released.
     * Make something here */

    return LV_RES_OK; /*Return OK if the button is not deleted*/
}
void create_wifi_list( )
{
    lv_theme_t *th;
    th = lv_theme_night_init(0, NULL);

    lv_theme_set_current(th);

    //th = lv_theme_get_current();    /*If `LV_THEME_LIVE_UPDATE  1` `th` is not used directly so get the real theme after set*/
    lv_obj_t * scr = lv_cont_create(NULL, NULL);
    lv_scr_load(scr);
    lv_cont_set_style(scr, th->bg);
/*Crate the list*/
lv_obj_t * list1 = lv_list_create(lv_scr_act(), NULL);
lv_obj_set_size(list1, 250, 300);
lv_obj_align(list1, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 40);
    lv_btn_set_toggle(list1, true);
/*Add list elements*/
lv_list_add(list1, SYMBOL_WIFI, "Hotspot1", list_release_action);
lv_list_add(list1, SYMBOL_WIFI, "Hotspot2", list_release_action);
lv_list_add(list1, SYMBOL_WIFI, "hotspot3", list_release_action);
lv_list_add(list1, SYMBOL_WIFI, "Starbucks", list_release_action);
lv_list_add(list1, SYMBOL_WIFI, "DoCoMo", list_release_action);

/*Create a label above the list*/
lv_obj_t * label;
label = lv_label_create(lv_scr_act(), NULL);
lv_label_set_text(label, "Select WiFi");
lv_obj_align(label, list1, LV_ALIGN_OUT_TOP_MID, 0, -10);



/*Create a one lined test are with password mode*/
lv_obj_t * ta2 = password = lv_ta_create(lv_scr_act(), NULL);
lv_obj_set_hidden(password,true);
lv_obj_align(ta2, list1, LV_ALIGN_OUT_RIGHT_TOP, 0,0);
//lv_ta_set_style(ta2,LV_TA_STYLE_BG, &style_bg);                     /*Apply the background style*/
lv_ta_set_one_line(ta2, true);
lv_ta_set_cursor_type(ta2, LV_CURSOR_LINE);
lv_ta_set_pwd_mode(ta2, true);
lv_ta_set_text(ta2, "Password");

lv_obj_t * plabel;
plabel = lv_label_create(lv_scr_act(), NULL);
lv_label_set_text(plabel, "Password");
lv_obj_align(plabel, password, LV_ALIGN_OUT_TOP_MID, 0, -10);

/*Create a normal button*/
lv_obj_t * join_btn= lv_btn_create(lv_scr_act(), NULL);
lv_cont_set_fit(join_btn, true, true); /*Enable resizing horizontally and vertically*/
lv_obj_align(join_btn, password, LV_ALIGN_OUT_BOTTOM_MID, 0, -10);
lv_obj_set_free_num(join_btn, 1);   /*Set a unique number for the button*/
lv_btn_set_action(join_btn, LV_BTN_ACTION_CLICK, btn_click_action);

/*Add a label to the button*/
label = lv_label_create(join_btn, NULL);
lv_label_set_text(label, "Join");





}


static lv_res_t ddlist_action(lv_obj_t * ddlist)
{
    uint8_t id = lv_obj_get_free_num(ddlist);

    char sel_str[32];
    lv_ddlist_get_selected_str(ddlist, sel_str);
    printf("Ddlist %d new option: %s \n", id, sel_str);

    return LV_RES_OK; /*Return OK if the drop down list is not deleted*/
}


void create_wifi_list2( ) {
    lv_theme_t *th;
    th = lv_theme_night_init(0, NULL);

    lv_theme_set_current(th);

    lv_obj_t * scr = lv_cont_create(NULL, NULL);
    lv_scr_load(scr);
    lv_cont_set_style(scr, th->bg);
/*Crate the list*/

lv_obj_t * label;
label = lv_label_create(lv_scr_act(), NULL);
lv_label_set_text(label, "Select WiFi");

/*Create a one lined test are with password mode*/
lv_obj_t * plabel;
plabel = lv_label_create(lv_scr_act(), NULL);
lv_label_set_text(plabel, "Password");
lv_obj_align(plabel, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 60);

lv_obj_t * ta2 = password = lv_ta_create(lv_scr_act(), NULL);
//lv_obj_set_hidden(password,true);
lv_obj_align(ta2, plabel, LV_ALIGN_OUT_BOTTOM_LEFT, 0,10);
//lv_ta_set_style(ta2,LV_TA_STYLE_BG, &style_bg);                     /*Apply the background style*/
lv_ta_set_one_line(ta2, true);
lv_ta_set_cursor_type(ta2, LV_CURSOR_LINE);
lv_ta_set_pwd_mode(ta2, true);
lv_ta_set_text(ta2, "Password");

/*Create a normal button*/
lv_obj_t * join_btn= lv_btn_create(lv_scr_act(), NULL);
lv_cont_set_fit(join_btn, true, true); /*Enable resizing horizontally and vertically*/
lv_obj_align(join_btn, password, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
lv_obj_set_free_num(join_btn, 1);   /*Set a unique number for the button*/
lv_btn_set_action(join_btn, LV_BTN_ACTION_CLICK, btn_click_action);

/*Add a label to the button*/
lv_obj_t * blabel = lv_label_create(join_btn, NULL);
lv_label_set_text(blabel, "Join");

/*Create a drop down list*/
lv_obj_t * ddl1 = lv_ddlist_create(lv_scr_act(), NULL);
lv_ddlist_set_draw_arrow(ddl1, true);
lv_ddlist_set_options(ddl1, "Apple net\n"
                            "Banana 2\n"
                            "Starbucks is really wide\n"
                            "DoCoMo\n"
                            "ATT Wireless\n"
                            "Orange");
lv_obj_align(ddl1, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
lv_obj_set_free_num(ddl1, 1);               /*Set a unique ID*/
lv_ddlist_set_action(ddl1, ddlist_action);  /*Set a function to call when anew option is chosen*/


}
