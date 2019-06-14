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

static lv_res_t list_release_action(lv_obj_t * list_btn)
{
    printf("List element click:%s\n", lv_list_get_btn_text(list_btn));
    return LV_RES_OK;

}

void create_rombrowser_list( lv_obj_t *win)
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


    lv_list_add(list, SYMBOL_DIRECTORY, "Arcade", list_release_action);
    lv_list_add(list, SYMBOL_FILE, "File", list_release_action);





}
