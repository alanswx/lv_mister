#include "lvgl/lvgl.h"
#include "lv_ex_conf.h"

#include "iniedit.h"
#include "browser.h"
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

lv_obj_t *win=NULL;

static lv_res_t my_cleanup_action(lv_obj_t * cb) {
printf("cleanup clicked\n");

//lv_win_clean(win);
    lv_obj_t * page = lv_win_get_content(win);
    if (page) {
		lv_page_clean(page);
    }
#if 0
    lv_obj_t * page = lv_win_get_content(win);
    if (page) {lv_obj_t * scrl = lv_page_get_scrl(page);
    if (scrl) lv_obj_clean(scrl);
}
#endif

//lv_obj_clean(lv_win_get_content(win));
    return LV_RES_OK;
}
static lv_res_t my_setup_action(lv_obj_t * cb) {
printf("setup clicked\n");
create_main_menu_inside(win);
    return LV_RES_OK;
}
static bool lv_list_is_list_bytype(lv_obj_t * list_img,const char *typename)
{
    lv_obj_type_t type;

    lv_obj_get_type(list_img, &type);
    uint8_t cnt;
    for(cnt = 0; cnt < LV_MAX_ANCESTOR_NUM; cnt++) {
        if(type.type[cnt] == NULL) break;
        if(!strcmp(type.type[cnt], typename))
            return true;
    }
    return false;
}
lv_obj_t * lv_list_get_btn_bytype(const lv_obj_t * btn,const char *type)
{
    lv_obj_t * cb = lv_obj_get_child(btn, NULL);
    if(cb== NULL) return NULL;

    while(lv_list_is_list_bytype(cb,type) == false) {
        cb= lv_obj_get_child(btn, cb);
        if(cb== NULL) break;
    }

    return cb;
}

static lv_res_t cb_release_action(lv_obj_t * cb)
{
    /*A check box is clicked*/
    printf("%s state: %d\n", lv_cb_get_text(cb), lv_cb_is_checked(cb));
    return LV_RES_OK;
}
static lv_res_t list_text_action(lv_obj_t * list_btn) {
    printf("List element click ta:%s\n", lv_list_get_btn_text(list_btn));
if (lv_list_get_btn_text(list_btn)==NULL || strlen(lv_list_get_btn_text(list_btn))==0) {
lv_obj_t *ta= lv_list_get_btn_bytype(list_btn,"lv_ta");
printf("about to focus\n");
lv_group_focus_obj(ta);
}
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
if (!strcasecmp(lv_list_get_btn_text(list_btn),"Checkbox")) {
}
if (!strcasecmp(lv_list_get_btn_text(list_btn),"Checkbox 2")) {
}

    return LV_RES_OK;
}
/*Will be called on click of a button of a list*/
static lv_res_t list_release_action(lv_obj_t * list_btn)
{
    printf("List element click:%s\n", lv_list_get_btn_text(list_btn));
if (lv_list_get_btn_text(list_btn)==NULL) {

printf("NULL text\n");
//lv_cb_set_checked(lv_obj_t * cb, bool checked);

}

if (!strcasecmp(lv_list_get_btn_text(list_btn),"Edit Ini File")) {

    lv_obj_t * page = lv_win_get_content(win);
    if (page) {
		lv_page_clean(page);
    }

	create_ini_list3(win );
    return LV_RES_OK;
}
if (!strcasecmp(lv_list_get_btn_text(list_btn),"Setup WiFi")) {

    lv_obj_t * page = lv_win_get_content(win);
    if (page) {
		lv_page_clean(page);
    }

	create_wifi_list3(win );
    return LV_RES_OK;
}

if (!strcasecmp(lv_list_get_btn_text(list_btn),"Rom Browser")) {

    lv_obj_t * page = lv_win_get_content(win);
    if (page) {
		lv_page_clean(page);
    }

	create_rombrowser_list(win,"NES" );
    return LV_RES_OK;
}



if (!strcasecmp(lv_list_get_btn_text(list_btn),"Github Issue Checkbox"))
	test_group_github();
if (!strcasecmp(lv_list_get_btn_text(list_btn),"WiFi"))
create_wifi_list();
if (!strcasecmp(lv_list_get_btn_text(list_btn),"WiFi 2"))
create_wifi_list2();

    return LV_RES_OK; /*Return OK because the list is not deleted*/
}

lv_group_t *group;
static void group_focus_cb(lv_group_t * group)
{
    lv_obj_t * f = lv_group_get_focused(group);

    /*Get the wondows content object */
    lv_obj_t * par =  lv_obj_get_parent(f);  /*The content object is page so first get scrollable object*/
    if(par) par = lv_obj_get_parent(par);    /*Then get the page itself*/

    /*If the focused object is on the window then scrol lteh window to make it visible*/
    if(par == lv_win_get_content(win)) {
        lv_win_focus(win, f, 200);
    }
}

static void group_style_cb(lv_style_t * style)
{
}

void create_main_window_info(lv_obj_t *win)
{
/*Create a scroll bar style*/
static lv_style_t style_sb;
lv_style_copy(&style_sb, &lv_style_plain);
style_sb.body.main_color = LV_COLOR_BLACK;
style_sb.body.grad_color = LV_COLOR_BLACK;
style_sb.body.border.color = LV_COLOR_WHITE;
style_sb.body.border.width = 1;
style_sb.body.border.opa = LV_OPA_70;
style_sb.body.radius = LV_RADIUS_CIRCLE;
style_sb.body.opa = LV_OPA_60;

/*Create a window*/
lv_win_set_title(win, "Mister");                        /*Set the title*/
lv_win_set_style(win, LV_WIN_STYLE_SB, &style_sb);              /*Set the scroll bar style*/
lv_win_set_layout(win, LV_LAYOUT_PRETTY);
//lv_win_set_layout(win, LV_LAYOUT_OFF);


/*Add control button to the header*/
lv_win_add_btn(win, SYMBOL_SETTINGS, my_setup_action);            /*Add a setup button*/
lv_win_add_btn(win, SYMBOL_CLOSE,my_cleanup_action/*lv_win_close_action*/);           /*Add close button and use built-in close action*/


}

void create_text_window( )
{
    lv_theme_t *th;
    //th = lv_theme_night_init(250, NULL);
    th = lv_theme_material_init(250,NULL);

    lv_theme_set_current(th);
static lv_group_t * g;
    g = lv_group_create();
//    lv_group_set_focus_cb(g, group_focus_cb);
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
    win = lv_win_create(lv_scr_act(), NULL);
    create_main_window_info(win);
    lv_obj_t *ta=lv_ta_create(win, NULL);
    lv_group_add_obj(g, ta);
    ta=lv_ta_create(win, NULL);
    lv_group_add_obj(g, ta);
    lv_obj_t * list = lv_list_create(win, NULL);
//    lv_obj_set_size(list, lv_page_get_scrl_width(lv_win_get_content(win)), lv_obj_get_height(lv_win_get_content(win)) );

    lv_obj_t * li;
    li = lv_list_add(list, SYMBOL_EDIT, "Edit Ini File", list_release_action);
    li =lv_list_add(list, SYMBOL_AUDIO, NULL, list_text_action );
    ta = lv_ta_create(li, NULL);
    lv_group_add_obj(g, ta);
    lv_ta_set_one_line( ta, true);
     lv_list_add(list, SYMBOL_EDIT, "Edit Ini File", list_release_action);
     lv_list_add(list, SYMBOL_EDIT, "Edit Ini File", list_release_action);
     lv_list_add(list, SYMBOL_EDIT, "Edit Ini File", list_release_action);
     lv_list_add(list, SYMBOL_EDIT, "Edit Ini File", list_release_action);
    lv_group_add_obj(g, list);

}

void create_main_window( )
{
    lv_theme_t *th;
    //th = lv_theme_night_init(250, NULL);
    th = lv_theme_material_init(250,NULL);

    lv_theme_set_current(th);

    win = lv_win_create(lv_scr_act(), NULL);
    create_main_window_info(win);
create_main_menu_inside(win);

}

void create_main_menu_inside(lv_obj_t *win){
static lv_group_t * g;
    g = lv_group_create();
    lv_group_set_focus_cb(g, group_focus_cb);
lv_group_set_style_mod_cb(g, group_style_cb);
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

    //lv_ta_create(win, NULL);
    //lv_group_add_obj(g, win);
#if 1
    lv_obj_t * list = lv_list_create(win, NULL);
//lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
//lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
lv_list_set_style(list, LV_LIST_STYLE_BG, &lv_style_transp_tight);
lv_list_set_style(list, LV_LIST_STYLE_SCRL, &lv_style_transp_tight);
lv_list_set_style(list, LV_LIST_STYLE_BTN_REL, &style_btn_rel); /*Set the new button styles*/
lv_list_set_style(list, LV_LIST_STYLE_BTN_PR, &style_btn_pr);
    lv_obj_set_size(list, lv_page_get_scrl_width(lv_win_get_content(win)), lv_obj_get_height(lv_win_get_content(win)) );
    lv_group_add_obj(g, list);

    lv_obj_t * list_btn;
    list_btn = lv_list_add(list, SYMBOL_EDIT, "Edit Ini File", list_release_action);
    //lv_obj_set_size(list, LV_HOR_RES , LV_VER_RES );

    lv_btn_set_toggle(list_btn, true);
    lv_list_add(list, SYMBOL_WIFI, "Setup WiFi", list_release_action);

//    lv_list_add(list, SYMBOL_GPS,  "Github Issue Checkbox",  list_release_action);
//    lv_list_add(list, SYMBOL_WIFI, "WiFi", list_release_action);
//    lv_list_add(list, SYMBOL_WIFI, "WiFi 2", list_release_action);
    lv_list_add(list, SYMBOL_DIRECTORY, "Rom Browser", list_release_action);
#if 0
    lv_list_add(list, SYMBOL_AUDIO, "Audio", list_release_action);
    lv_list_add(list, SYMBOL_VIDEO, "Video", list_release_action);
    lv_list_add(list, SYMBOL_STOP, "Checkbox", list_checkbox_action);
    lv_list_add(list, SYMBOL_OK, "Checkbox 2", list_checkbox_action);
    lv_obj_t *li=lv_list_add(list, SYMBOL_AUDIO, NULL, list_checkbox_action);
    lv_obj_t * cb;
    cb = lv_cb_create(li, NULL);
    lv_cb_set_text(cb, "Potato");
    li=lv_list_add(list, SYMBOL_AUDIO, NULL, list_text_action );
    lv_obj_t * ta;
    ta = lv_ta_create(li, NULL);
    lv_group_add_obj(g, ta);
    lv_ta_set_one_line( ta, true);
    lv_list_add(list, SYMBOL_DIRECTORY, "Rom Browser", list_release_action);

    lv_list_add(list, SYMBOL_FILE, "File", list_release_action);
    lv_list_add(list, SYMBOL_EDIT, "Edit", list_release_action);
    lv_list_add(list, SYMBOL_CUT,  "Cut",  list_release_action);
    lv_list_add(list, SYMBOL_COPY, "Copy", list_release_action);
    lv_list_add(list, SYMBOL_FILE, "File", list_release_action);
    lv_list_add(list, SYMBOL_EDIT, "Edit", list_release_action);
    lv_list_add(list, SYMBOL_CUT,  "Cut",  list_release_action);
    lv_list_add(list, SYMBOL_COPY, "Copy", list_release_action);
#endif
#endif
}
