#include "lvgl/lvgl.h"
#include "lv_ex_conf.h"

#include "iniedit.h"
void create_main_menu_inside(lv_obj_t *win);
void create_main_window_info(lv_obj_t *win);

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
#if 0
lv_obj_t * txt = lv_label_create(win, NULL);
lv_label_set_text(txt, "This is the content of the window\n\n"
                       "You can add control buttons to\nthe window header\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "See the scroll bar on the right!");
#endif
    return LV_RES_OK;
}
static lv_res_t cb_release_action(lv_obj_t * cb)
{
    /*A check box is clicked*/
    printf("%s state: %d\n", lv_cb_get_text(cb), lv_cb_is_checked(cb));

    return LV_RES_OK;
}
/*Will be called on click of a button of a list*/
static lv_res_t list_release_action(lv_obj_t * list_btn)
{
    printf("List element click:%s\n", lv_list_get_btn_text(list_btn));

if (!strcasecmp(lv_list_get_btn_text(list_btn),"Edit Ini File")) {
    lv_obj_t * page = lv_win_get_content(win);
    if (page) {lv_obj_t * scrl = lv_page_get_scrl(page);
    if (scrl) lv_obj_clean(scrl);}
	create_ini_list2(win );
printf("create ini list2\n");
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

void create_main_window( )
{
    lv_theme_t *th;
    //th = lv_theme_night_init(250, NULL);
    th = lv_theme_material_init(250,NULL);

    lv_theme_set_current(th);

    win = lv_win_create(lv_scr_act(), NULL);
    create_main_window_info(win);
create_main_menu_inside(win);
#if 0
    // create the main window
#if 0
/*Add some dummy content*/
lv_obj_t * txt = lv_label_create(win, NULL);
lv_label_set_text(txt, "This is the content of the window\n\n"
                       "You can add control buttons to\nthe window header\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "You can scroll it\n\n"
                       "See the scroll bar on the right!");
    lv_obj_set_size(txt, lv_page_get_scrl_width(win), lv_obj_get_height(win) / 2);

#else
    lv_obj_t * scr = win; 
#if 0
    lv_obj_t * scr = lv_cont_create(win, NULL);
   //lv_scr_load(scr);
lv_cont_set_layout(scr, LV_LAYOUT_COL_L);      /*Arrange the children in a column*/
//lv_cont_set_fit(scr, true, true);              /*Fit the size to the content*/
//    lv_obj_set_size(scr, lv_page_get_scrl_width(win), lv_obj_get_height(win) / 2);

    lv_cont_set_style(scr, th->bg);
#endif

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
#if 0
/*********************
 * Create new styles
 ********************/
/*Create a scroll bar style*/
//static lv_style_t style_sb;
lv_style_copy(&style_sb, &lv_style_plain);
style_sb.body.main_color = LV_COLOR_BLACK;
style_sb.body.grad_color = LV_COLOR_BLACK;
style_sb.body.border.color = LV_COLOR_WHITE;
style_sb.body.border.width = 1;
style_sb.body.border.opa = LV_OPA_70;
style_sb.body.radius = LV_RADIUS_CIRCLE;
style_sb.body.opa = LV_OPA_60;
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

/**************************************
 * Create a list with modified styles
 **************************************/

    lv_obj_t * list = lv_list_create(scr, NULL);
//lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
//lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
lv_list_set_style(list, LV_LIST_STYLE_BG, &lv_style_transp_tight);
lv_list_set_style(list, LV_LIST_STYLE_SCRL, &lv_style_transp_tight);
lv_list_set_style(list, LV_LIST_STYLE_BTN_REL, &style_btn_rel); /*Set the new button styles*/
lv_list_set_style(list, LV_LIST_STYLE_BTN_PR, &style_btn_pr);
    lv_obj_set_size(list, lv_page_get_scrl_width(lv_win_get_content(win)), lv_obj_get_height(lv_win_get_content(win)) );

    lv_obj_t * list_btn;
    list_btn = lv_list_add(list, SYMBOL_EDIT, "Edit Ini File", list_release_action);
    //lv_obj_set_size(list, LV_HOR_RES , LV_VER_RES );

    lv_btn_set_toggle(list_btn, true);
    lv_list_add(list, SYMBOL_GPS,  "Github Issue Checkbox",  list_release_action);
    lv_list_add(list, SYMBOL_WIFI, "WiFi", list_release_action);
    lv_list_add(list, SYMBOL_WIFI, "WiFi 2", list_release_action);
    lv_list_add(list, SYMBOL_AUDIO, "Audio", list_release_action);
    lv_list_add(list, SYMBOL_VIDEO, "Video", list_release_action);
    lv_list_add(list, SYMBOL_CALL, "Call", list_release_action);
    lv_list_add(list, SYMBOL_BELL, "Bell", list_release_action);
    lv_list_add(list, SYMBOL_FILE, "File", list_release_action);
    lv_list_add(list, SYMBOL_EDIT, "Edit", list_release_action);
    lv_list_add(list, SYMBOL_CUT,  "Cut",  list_release_action);
    lv_list_add(list, SYMBOL_COPY, "Copy", list_release_action);
    lv_list_add(list, SYMBOL_FILE, "File", list_release_action);
    lv_list_add(list, SYMBOL_EDIT, "Edit", list_release_action);
    lv_list_add(list, SYMBOL_CUT,  "Cut",  list_release_action);
    lv_list_add(list, SYMBOL_COPY, "Copy", list_release_action);
    lv_group_add_obj(g, list);
#endif
#endif
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

    lv_obj_t * list = lv_list_create(win, NULL);
//lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
//lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
lv_list_set_style(list, LV_LIST_STYLE_BG, &lv_style_transp_tight);
lv_list_set_style(list, LV_LIST_STYLE_SCRL, &lv_style_transp_tight);
lv_list_set_style(list, LV_LIST_STYLE_BTN_REL, &style_btn_rel); /*Set the new button styles*/
lv_list_set_style(list, LV_LIST_STYLE_BTN_PR, &style_btn_pr);
    lv_obj_set_size(list, lv_page_get_scrl_width(lv_win_get_content(win)), lv_obj_get_height(lv_win_get_content(win)) );

    lv_obj_t * list_btn;
    list_btn = lv_list_add(list, SYMBOL_EDIT, "Edit Ini File", list_release_action);
    //lv_obj_set_size(list, LV_HOR_RES , LV_VER_RES );

    lv_btn_set_toggle(list_btn, true);
    lv_list_add(list, SYMBOL_GPS,  "Github Issue Checkbox",  list_release_action);
    lv_list_add(list, SYMBOL_WIFI, "WiFi", list_release_action);
    lv_list_add(list, SYMBOL_WIFI, "WiFi 2", list_release_action);
    lv_list_add(list, SYMBOL_AUDIO, "Audio", list_release_action);
    lv_list_add(list, SYMBOL_VIDEO, "Video", list_release_action);
    lv_list_add(list, SYMBOL_CALL, "Call", list_release_action);
    lv_list_add(list, SYMBOL_BELL, "Bell", list_release_action);
    lv_list_add(list, SYMBOL_FILE, "File", list_release_action);
    lv_list_add(list, SYMBOL_EDIT, "Edit", list_release_action);
    lv_list_add(list, SYMBOL_CUT,  "Cut",  list_release_action);
    lv_list_add(list, SYMBOL_COPY, "Copy", list_release_action);
    lv_list_add(list, SYMBOL_FILE, "File", list_release_action);
    lv_list_add(list, SYMBOL_EDIT, "Edit", list_release_action);
    lv_list_add(list, SYMBOL_CUT,  "Cut",  list_release_action);
    lv_list_add(list, SYMBOL_COPY, "Copy", list_release_action);
    lv_group_add_obj(g, list);
}
