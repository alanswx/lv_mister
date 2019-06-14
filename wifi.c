#include "lvgl/lvgl.h"
#include "lv_ex_conf.h"

#include "window.h"

#if LV_EX_KEYBOARD || LV_EX_MOUSEWHEEL
#include "lv_drv_conf.h"
#endif

#if LV_EX_KEYBOARD
#include "lv_drivers/indev/keyboard.h"
#endif

#if LV_EX_MOUSEWHEEL
#include "lv_drivers/indev/mousewheel.h"
#endif

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


static lv_res_t list_checkbox_action(lv_obj_t * list_btn) {
    printf("List element click cb:%s\n", lv_list_get_btn_text(list_btn));
if (lv_list_get_btn_text(list_btn)==NULL || strlen(lv_list_get_btn_text(list_btn))==0) {
lv_obj_t *cb= lv_list_get_btn_bytype(list_btn,"lv_cb");
if (cb) {
printf(" got a checkbox\n");
	if (lv_cb_is_checked(cb))
		lv_cb_set_checked(cb, false);
	else
		lv_cb_set_checked(cb, true);

}
}

    return LV_RES_OK;
}
static lv_res_t list_text_action(lv_obj_t * list_btn) {
    printf("List element click ta:%s\n", lv_list_get_btn_text(list_btn));
//if (lv_list_get_btn_text(list_btn)==NULL || strlen(lv_list_get_btn_text(list_btn))==0) {
lv_obj_t *ta= lv_list_get_btn_bytype(list_btn,"lv_ta");
printf("about to focus\n");
lv_group_focus_obj(ta);
//}
    return LV_RES_OK;

}
static lv_res_t list_ddl_action(lv_obj_t * list_btn) {
    printf("List element click ta:%s\n", lv_list_get_btn_text(list_btn));
lv_obj_t *ta= lv_list_get_btn_bytype(list_btn,"lv_ddlist");
if (ta) {
printf("about to focus\n");
lv_group_focus_obj(ta);
}
    return LV_RES_OK;

}

static void group_focus_cb(lv_group_t * group) {

// checkbox
// container
// page

printf("group_focus_cb\n");
    if (group) {
printf("group_focus_cb2\n");
    lv_obj_t * f = lv_group_get_focused(group);



    // f should be checkbox
    if (f) {


printf("group_focus_cb3\n");
	lv_obj_t * par =  lv_obj_get_parent(f);  /*The content object is page so first get scrollable object*/
    if(par)
     {
	lv_obj_t * page =  lv_obj_get_parent(par);  /*The content object is page so first get scrollable object*/
	if (page) {
print_obj_type(page);
printf("group_focus_cb4 page: %x\n",page);
    //    	lv_page_focus(page, f, 200);
}
}
}
}
}
void create_wifi_list3( lv_obj_t *win)
{

static lv_group_t * g;
    g = lv_group_create();
    lv_group_set_focus_cb(g, group_focus_cb);
//lv_group_set_style_mod_cb(g, group_style_cb);
#if LV_EX_KEYBOARD
    lv_indev_drv_t rael_kb_drv;
    rael_kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    rael_kb_drv.read = keyboard_read;
    lv_indev_t * real_kb_indev = lv_indev_drv_register(&rael_kb_drv);
    lv_indev_set_group(real_kb_indev, g);
#endif

#if LV_EX_MOUSEWHEEL
    lv_indev_drv_t enc_drv;
    enc_drv.type = LV_INDEV_TYPE_ENCODER;
    enc_drv.read = mousewheel_read;
    lv_indev_t * enc_indev = lv_indev_drv_register(&enc_drv);
    lv_indev_set_group(enc_indev, g);
#endif
/*Create styles for the buttons*/
static lv_style_t style_btn_rel;
static lv_style_t style_btn_pr;
lv_style_copy(&style_btn_rel, &lv_style_btn_rel);
style_btn_rel.body.main_color = LV_COLOR_MAKE(0x30, 0x30, 0x30);
style_btn_rel.body.grad_color = LV_COLOR_BLACK;
style_btn_rel.body.border.color = LV_COLOR_SILVER;
style_btn_rel.body.border.width = 1;
style_btn_rel.body.border.opa = LV_OPA_50;
style_btn_rel.body.radius = 0;

lv_style_copy(&style_btn_pr, &style_btn_rel);
style_btn_pr.body.main_color = LV_COLOR_MAKE(0x55, 0x96, 0xd8);
style_btn_pr.body.grad_color = LV_COLOR_MAKE(0x37, 0x62, 0x90);
style_btn_pr.text.color = LV_COLOR_MAKE(0xbb, 0xd5, 0xf1);


    lv_obj_t * list = lv_list_create(win, NULL);
//lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
//lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
lv_list_set_style(list, LV_LIST_STYLE_BG, &lv_style_transp_tight);
lv_list_set_style(list, LV_LIST_STYLE_SCRL, &lv_style_transp_tight);
lv_list_set_style(list, LV_LIST_STYLE_BTN_REL, &style_btn_rel); /*Set the new button styles*/
lv_list_set_style(list, LV_LIST_STYLE_BTN_PR, &style_btn_pr);
    lv_obj_set_size(list, lv_page_get_scrl_width(lv_win_get_content(win)), lv_obj_get_height(lv_win_get_content(win)) );
    lv_group_add_obj(g, list);

    lv_list_add(list, SYMBOL_FILE, "BACK", list_release_action);


    lv_obj_t * list_btn;
    lv_obj_t *li;
    lv_obj_t * cb;
    lv_obj_t * ta;
    lv_obj_t * title;

    li=lv_list_add(list, NULL, NULL, list_checkbox_action);
    cb = lv_cb_create(li, NULL);
    lv_cb_set_text(cb, "Use WiFi");

    li=lv_list_add(list, NULL, NULL, list_ddl_action );
    title = lv_label_create(li, NULL);
lv_label_set_text(title, "SSID:");
lv_obj_t * ddl1 = lv_ddlist_create(li, NULL);
lv_ddlist_set_draw_arrow(ddl1, true);
lv_ddlist_set_options(ddl1, "----\n"
                            "AT&T\n"
                            "Starbucks\n"
                            "Comcast\n"
                            "FreeWiFi\n"
                            "SchoolNet");
    lv_group_add_obj(g, ddl1);




    li=lv_list_add(list, NULL, NULL, list_text_action );
    title = lv_label_create(li, NULL);
    lv_label_set_text(title, "Password:");
    ta = lv_ta_create(li, NULL);
    lv_ta_set_one_line(ta, true);
    lv_ta_set_text(ta, "");
    lv_group_add_obj(g, ta);
    lv_ta_set_one_line( ta, true);




}
