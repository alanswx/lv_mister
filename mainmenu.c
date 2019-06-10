#include "lvgl/lvgl.h"
#include "lv_ex_conf.h"

#include "iniedit.h"

#if LV_EX_KEYBOARD || LV_EX_MOUSEWHEEL
#include "lv_drv_conf.h"
#endif

#if LV_EX_KEYBOARD
#include "lv_drivers/indev/keyboard.h"
#endif

#if LV_EX_MOUSEWHEEL
#include "lv_drivers/indev/mousewheel.h"
#endif

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

if (!strcasecmp(lv_list_get_btn_text(list_btn),"Edit Ini File"))
	create_ini_list( );
if (!strcasecmp(lv_list_get_btn_text(list_btn),"Github Issue Checkbox"))
	test_group_github();
if (!strcasecmp(lv_list_get_btn_text(list_btn),"WiFi"))
create_wifi_list();
if (!strcasecmp(lv_list_get_btn_text(list_btn),"WiFi 2"))
create_wifi_list2();

    return LV_RES_OK; /*Return OK because the list is not deleted*/
}

void group_focus_cb(lv_group_t * group)
{
}
void group_style_cb(lv_style_t * style)
{
}

void create_main( )
{
    lv_theme_t *th;
    th = lv_theme_night_init(210, NULL);

    lv_theme_set_current(th);

    //th = lv_theme_get_current();    /*If `LV_THEME_LIVE_UPDATE  1` `th` is not used directly so get the real theme after set*/
    lv_obj_t * scr = lv_cont_create(NULL, NULL);
   lv_scr_load(scr);
    lv_cont_set_style(scr, th->bg);

#if 0
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
style_sb.body.padding.hor = 3;          /*Horizontal padding on the right*/
style_sb.body.padding.inner = 8;        /*Scrollbar width*/

/*Create a page*/
lv_obj_t * page = lv_page_create(lv_scr_act(), NULL);
lv_obj_set_size(page, LV_HOR_RES, LV_VER_RES);
lv_obj_align(page, NULL, LV_ALIGN_CENTER, 0, 0);
lv_page_set_style(page, LV_PAGE_STYLE_SB, &style_sb);           /*Set the scrollbar style*/
lv_page_set_sb_mode(page, LV_SB_MODE_AUTO);                     /*Show scroll bars is scrolling is possible*/
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



    lv_obj_t * list = lv_list_create(scr, NULL);
    lv_obj_t * list_btn;
    list_btn = lv_list_add(list, SYMBOL_GPS,  "GPS",  NULL);
    lv_obj_set_size(list, LV_HOR_RES , LV_VER_RES );
    lv_btn_set_toggle(list_btn, true);
    lv_list_add(list, SYMBOL_WIFI, "WiFi", list_release_action);
    lv_list_add(list, SYMBOL_GPS, "GPS", list_release_action);
    lv_list_add(list, SYMBOL_AUDIO, "Audio", list_release_action);
    lv_list_add(list, SYMBOL_VIDEO, "Video", list_release_action);
    lv_list_add(list, SYMBOL_CALL, "Call", list_release_action);
    lv_list_add(list, SYMBOL_BELL, "Bell", list_release_action);
    lv_list_add(list, SYMBOL_FILE, "File", list_release_action);
    lv_list_add(list, SYMBOL_CUT,  "Cut",  list_release_action);
    lv_list_add(list, SYMBOL_COPY, "Copy", list_release_action);
    lv_list_add(list, SYMBOL_FILE, "File", list_release_action);
    lv_list_add(list, SYMBOL_EDIT, "Edit", list_release_action);
    lv_list_add(list, SYMBOL_CUT,  "Cut",  list_release_action);
    lv_list_add(list, SYMBOL_COPY, "Copy", list_release_action);
    lv_group_add_obj(g, list);


}

void create_main2( )
{
    lv_theme_t *th;
    th = lv_theme_night_init(250, NULL);

    lv_theme_set_current(th);

    //th = lv_theme_get_current();    /*If `LV_THEME_LIVE_UPDATE  1` `th` is not used directly so get the real theme after set*/
    lv_obj_t * scr = lv_cont_create(NULL, NULL);
   lv_scr_load(scr);
    lv_cont_set_style(scr, th->bg);

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

/*********************
 * Create new styles
 ********************/
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
lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
lv_list_set_style(list, LV_LIST_STYLE_BG, &lv_style_transp_tight);
lv_list_set_style(list, LV_LIST_STYLE_SCRL, &lv_style_transp_tight);
lv_list_set_style(list, LV_LIST_STYLE_BTN_REL, &style_btn_rel); /*Set the new button styles*/
lv_list_set_style(list, LV_LIST_STYLE_BTN_PR, &style_btn_pr);

    lv_obj_t * list_btn;
    list_btn = lv_list_add(list, SYMBOL_EDIT, "Edit Ini File", list_release_action);
    lv_obj_set_size(list, LV_HOR_RES , LV_VER_RES );
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

