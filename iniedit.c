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

static lv_obj_t *gwin=NULL;


static lv_res_t cb_release_action(lv_obj_t * cb)
{
    /*A check box is clicked*/
    printf("%s state: %d\n", lv_cb_get_text(cb), lv_cb_is_checked(cb));

    return LV_RES_OK;
}
static void group_style_cb(lv_style_t * style)
{
}
void print_obj_type(lv_obj_t *f) {
lv_obj_type_t buf;
lv_obj_get_type(f, &buf);
for (int i = 0; i< LV_MAX_ANCESTOR_NUM ; i++)
{
  if (buf.type[i])  {
	printf("%s\n",buf.type[i]);
}
}
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
void create_ini_list( )
{
    lv_theme_t *th;
    th = lv_theme_night_init(15, NULL);

    lv_theme_set_current(th);

    //th = lv_theme_get_current();    /*If `LV_THEME_LIVE_UPDATE  1` `th` is not used directly so get the real theme after set*/
    lv_obj_t * scr = lv_cont_create(NULL, NULL);
   lv_scr_load(scr);
    lv_cont_set_style(scr, th->bg);

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




/********************************************
 * Create a container for the check boxes
 ********************************************/

/*Create  border style*/
static lv_style_t style_border;
lv_style_copy(&style_border, &lv_style_pretty_color);
style_border.glass = 1;
style_border.body.empty = 1;


/*Create a container*/
lv_obj_t * cont = page;
lv_cont_set_layout(cont, LV_LAYOUT_COL_L);      /*Arrange the children in a column*/
#if 0
cont = lv_cont_create(scr, NULL);
lv_cont_set_layout(cont, LV_LAYOUT_COL_L);      /*Arrange the children in a column*/
lv_cont_set_fit(cont, true, true);              /*Fit the size to the content*/
lv_obj_set_style(cont, &style_border);
lv_page_glue_obj(cont, true);
#endif

/**************************
 * Create check boxes
 *************************/

/*Create check box*/
lv_obj_t * cb;
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


cb = lv_cb_create(cont,NULL);
lv_cb_set_text(cb, "Map MENU key map to RGUI in Minimig");
lv_cb_set_action(cb, cb_release_action);
    lv_group_add_obj(g, cb);

/*Copy the previous check box*/
cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "Force scandoubler on VGA output always");

/*Copy the previous check box*/
cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "YPbPr on VGA output");

/*Copy the previous check box*/
cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "composite sync on HSync signal of VGA output");

/*Copy the previous check box*/
cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "connect VGA to scaler output");

/*Copy the previous check box*/
cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "96khz/16bit HDMI audio");

/*Create a one lined test are with password mode*/
#if 1
lv_obj_t * tcont = lv_cont_create(cont,NULL);
lv_cont_set_layout(tcont, LV_LAYOUT_ROW_M);
lv_cont_set_fit(tcont, true, true);              /*Fit the size to the content*/
lv_obj_set_style(tcont, &style_border);
lv_page_glue_obj(tcont, true);

lv_obj_t * ta;
lv_obj_t * title = lv_label_create(tcont, NULL);
lv_label_set_text(title, "VIDPID of keyrah:");

ta= lv_ta_create(tcont,NULL);
//lv_ta_set_style(ta,LV_TA_STYLE_BG, &style_bg);                     /*Apply the background style*/
lv_ta_set_one_line(ta, true);
lv_ta_set_cursor_type(ta, LV_CURSOR_LINE);
lv_ta_set_text(ta, "0x18d80002");
    lv_group_add_obj(g, ta);
#endif

cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "another checkbox");

/*Create a drop down list*/
tcont = lv_cont_create(cont,NULL);
lv_cont_set_layout(tcont, LV_LAYOUT_ROW_M);
lv_cont_set_fit(tcont, true, true);              /*Fit the size to the content*/
lv_obj_set_style(tcont, &style_border);
lv_page_glue_obj(tcont, true);
    lv_group_add_obj(g, tcont);

title = lv_label_create(tcont, NULL);
lv_label_set_text(title, "Video Resolution:");
lv_obj_t * ddl1 = lv_ddlist_create(tcont, NULL);
lv_ddlist_set_draw_arrow(ddl1, true);
lv_ddlist_set_options(ddl1, "1280x720@60\n"
                            "1024x768@60\n"
                            "720x480@60\n"
                            "720x576@50\n"
                            "fill these in");
//lv_obj_set_free_num(ddl1, 1);               /*Set a unique ID*/
//lv_ddlist_set_action(ddl1, ddlist_action);  /*Set a function to call when anew option is chosen*/
    lv_group_add_obj(g, ddl1);

cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "pal mode");

tcont = lv_cont_create(cont,NULL);
lv_cont_set_layout(tcont, LV_LAYOUT_ROW_M);
lv_cont_set_fit(tcont, true, true);              /*Fit the size to the content*/
lv_obj_set_style(tcont, &style_border);
lv_page_glue_obj(tcont, true);
title = lv_label_create(tcont, NULL);
lv_label_set_text(title, "Font:");

ta= lv_ta_create(tcont,NULL);
//lv_ta_set_style(ta,LV_TA_STYLE_BG, &style_bg);                     /*Apply the background style*/
lv_ta_set_one_line(ta, true);
lv_ta_set_cursor_type(ta, LV_CURSOR_LINE);
lv_ta_set_text(ta, "/font/myfont.pf");
lv_group_add_obj(g, ta);

/*Align the container to the middle*/
lv_obj_align(cont, NULL, LV_ALIGN_CENTER, 0, 0);
}

void create_ini_list2( lv_obj_t *win)
{
gwin=win;
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
//lv_obj_t * page = lv_page_create(win, NULL);
//lv_obj_set_size(page, LV_HOR_RES, LV_VER_RES);
//lv_obj_align(page, NULL, LV_ALIGN_CENTER, 0, 0);
//lv_page_set_style(page, LV_PAGE_STYLE_SB, &style_sb);           /*Set the scrollbar style*/
//lv_page_set_sb_mode(page, LV_SB_MODE_AUTO);                     /*Show scroll bars is scrolling is possible*/




/********************************************
 * Create a container for the check boxes
 ********************************************/

/*Create  border style*/
static lv_style_t style_border;
lv_style_copy(&style_border, &lv_style_pretty_color);
style_border.glass = 1;
style_border.body.empty = 1;


/*Create a container*/
lv_obj_t * cont;
//lv_cont_set_layout(cont, LV_LAYOUT_COL_L);      /*Arrange the children in a column*/
#if 1
cont = lv_cont_create(win, NULL);
lv_cont_set_layout(cont, LV_LAYOUT_COL_L);      /*Arrange the children in a column*/
lv_cont_set_fit(cont, true, true);              /*Fit the size to the content*/
lv_obj_set_style(cont, &style_border);
lv_page_glue_obj(cont, true);
#endif

/**************************
 * Create check boxes
 *************************/

/*Create check box*/
lv_obj_t * cb;
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


cb = lv_cb_create(cont,NULL);
lv_cb_set_text(cb, "Map MENU key map to RGUI in Minimig");
lv_cb_set_action(cb, cb_release_action);
    lv_group_add_obj(g, cb);

/*Copy the previous check box*/
cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "Force scandoubler on VGA output always");

/*Copy the previous check box*/
cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "YPbPr on VGA output");

/*Copy the previous check box*/
cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "composite sync on HSync signal of VGA output");

/*Copy the previous check box*/
cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "connect VGA to scaler output");

/*Copy the previous check box*/
cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "96khz/16bit HDMI audio");

/*Create a one lined test are with password mode*/
#if 1
lv_obj_t * tcont = lv_cont_create(cont,NULL);
lv_cont_set_layout(tcont, LV_LAYOUT_ROW_M);
lv_cont_set_fit(tcont, true, true);              /*Fit the size to the content*/
lv_obj_set_style(tcont, &style_border);
lv_page_glue_obj(tcont, true);

lv_obj_t * ta;
lv_obj_t * title = lv_label_create(tcont, NULL);
lv_label_set_text(title, "VIDPID of keyrah:");

ta= lv_ta_create(tcont,NULL);
//lv_ta_set_style(ta,LV_TA_STYLE_BG, &style_bg);                     /*Apply the background style*/
lv_ta_set_one_line(ta, true);
lv_ta_set_cursor_type(ta, LV_CURSOR_LINE);
lv_ta_set_text(ta, "0x18d80002");
    lv_group_add_obj(g, ta);
#endif

cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "another checkbox");

/*Create a drop down list*/
tcont = lv_cont_create(cont,NULL);
lv_cont_set_layout(tcont, LV_LAYOUT_ROW_M);
lv_cont_set_fit(tcont, true, true);              /*Fit the size to the content*/
lv_obj_set_style(tcont, &style_border);
lv_page_glue_obj(tcont, true);
    lv_group_add_obj(g, tcont);

title = lv_label_create(tcont, NULL);
lv_label_set_text(title, "Video Resolution:");
lv_obj_t * ddl1 = lv_ddlist_create(tcont, NULL);
lv_ddlist_set_draw_arrow(ddl1, true);
lv_ddlist_set_options(ddl1, "1280x720@60\n"
                            "1024x768@60\n"
                            "720x480@60\n"
                            "720x576@50\n"
                            "fill these in");
//lv_obj_set_free_num(ddl1, 1);               /*Set a unique ID*/
//lv_ddlist_set_action(ddl1, ddlist_action);  /*Set a function to call when anew option is chosen*/
    lv_group_add_obj(g, ddl1);

cb = lv_cb_create(cont, cb);
lv_cb_set_text(cb, "pal mode");

tcont = lv_cont_create(cont,NULL);
lv_cont_set_layout(tcont, LV_LAYOUT_ROW_M);
lv_cont_set_fit(tcont, true, true);              /*Fit the size to the content*/
lv_obj_set_style(tcont, &style_border);
lv_page_glue_obj(tcont, true);
title = lv_label_create(tcont, NULL);
lv_label_set_text(title, "Font:");

ta= lv_ta_create(tcont,NULL);
//lv_ta_set_style(ta,LV_TA_STYLE_BG, &style_bg);                     /*Apply the background style*/
lv_ta_set_one_line(ta, true);
lv_ta_set_cursor_type(ta, LV_CURSOR_LINE);
lv_ta_set_text(ta, "/font/myfont.pf");
lv_group_add_obj(g, ta);

/*Align the container to the middle*/
lv_obj_align(cont, NULL, LV_ALIGN_CENTER, 0, 0);
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

static lv_res_t list_release_action(lv_obj_t * list_btn)
{
    printf("List element click:%s\n", lv_list_get_btn_text(list_btn));
    if (!strcasecmp("Back",lv_list_get_btn_text(list_btn))) {
        lv_obj_t * page = lv_win_get_content(gwin);
        if (page) {
                lv_page_clean(page);
        }

                create_main_menu_inside(gwin);
                return LV_RES_OK;
        }
    return LV_RES_OK;
}
void create_ini_list3( lv_obj_t *win)
{
gwin=win;
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
    lv_group_add_obj(g, list);

    lv_list_add(list, SYMBOL_LEFT, "Back", list_release_action);


    lv_obj_t * list_btn;
    lv_obj_t *li;
    lv_obj_t * cb;

    li=lv_list_add(list, NULL, NULL, list_checkbox_action);
    cb = lv_cb_create(li, NULL);
    lv_cb_set_text(cb, "Map MENU key map to RGUI in Minimig");

    li=lv_list_add(list, NULL, NULL, list_checkbox_action);
    cb = lv_cb_create(li, NULL);
    lv_cb_set_text(cb, "Force scandoubler on VGA output always");
    li=lv_list_add(list, NULL, NULL, list_checkbox_action);
    cb = lv_cb_create(li, NULL);
    lv_cb_set_text(cb, "YPbPr on VGA output");


    li=lv_list_add(list, NULL, NULL, list_checkbox_action);
    cb = lv_cb_create(li, NULL);
    lv_cb_set_text(cb, "composite sync on HSync signal of VGA output");

    li=lv_list_add(list, NULL, NULL, list_checkbox_action);
    cb = lv_cb_create(li, NULL);
    lv_cb_set_text(cb, "connect VGA to scaler output");

    li=lv_list_add(list, NULL, NULL, list_checkbox_action);
    cb = lv_cb_create(li, NULL);
    lv_cb_set_text(cb, "96khz/16bit HDMI audio");


    lv_obj_t * ta;
    lv_obj_t * title;
    li=lv_list_add(list, NULL, NULL, list_text_action );
    title = lv_label_create(li, NULL);
    lv_label_set_text(title, "VIDPID of keyrah:");
    ta = lv_ta_create(li, NULL);
    lv_ta_set_one_line(ta, true);
    lv_ta_set_text(ta, "0x18d80002");
    lv_group_add_obj(g, ta);
    lv_ta_set_one_line( ta, true);

    li=lv_list_add(list, NULL, NULL, list_ddl_action );
    title = lv_label_create(li, NULL);
lv_label_set_text(title, "Video Resolution:");
lv_obj_t * ddl1 = lv_ddlist_create(li, NULL);
lv_ddlist_set_draw_arrow(ddl1, true);
lv_ddlist_set_options(ddl1, "1280x720@60\n"
                            "1024x768@60\n"
                            "720x480@60\n"
                            "720x576@50\n"
                            "fill these in");
    lv_group_add_obj(g, ddl1);

    li=lv_list_add(list, NULL, NULL, list_checkbox_action);
    cb = lv_cb_create(li, NULL);
    lv_cb_set_text(cb, "pal mode");



    li=lv_list_add(list, NULL, NULL, list_text_action );
    title = lv_label_create(li, NULL);
    lv_label_set_text(title, "Font:");
    ta = lv_ta_create(li, NULL);
    lv_ta_set_one_line(ta, true);
    lv_ta_set_text(ta, "/font/myfont.pf");
    lv_group_add_obj(g, ta);
    lv_ta_set_one_line( ta, true);


}

lv_group_t *group;
lv_obj_t *win;
static void group_focus_cb2(lv_group_t * group)
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
void test_group_github(void)
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
	group = lv_group_create();
    lv_group_set_focus_cb(group, group_focus_cb2);

#if LV_EX_KEYBOARD
    lv_indev_drv_t rael_kb_drv;
    rael_kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    rael_kb_drv.read = keyboard_read;
    lv_indev_t * real_kb_indev = lv_indev_drv_register(&rael_kb_drv);
    lv_indev_set_group(real_kb_indev, group);
#endif

#if LV_EX_MOUSEWHEEL
    lv_indev_drv_t enc_drv;
    enc_drv.type = LV_INDEV_TYPE_ENCODER;
    enc_drv.read = mousewheel_read;
    lv_indev_t * enc_indev = lv_indev_drv_register(&enc_drv);
    lv_indev_set_group(enc_indev, group);
#endif
	/*Create a window*/

	win = lv_win_create(lv_scr_act(), NULL);		/* object for window */
	lv_win_set_title(win, "Pollenarten");		// set title
	lv_win_set_style(win, LV_WIN_STYLE_SB, &style_sb);              /*Set the scroll bar style*/


	/* Create close Window Button*/
	lv_obj_t *closeBtn;
	closeBtn = lv_win_add_btn(win, SYMBOL_CLOSE, NULL);

	lv_group_add_obj(group, closeBtn);		// add close button
	lv_group_focus_obj(closeBtn);




	 /*Create check boxes*/
	int x = 0;
	int nOFnames = 20;	//  get number of pollen to initialize
	uint16_t posX = 0;
	uint16_t posY = 0;
	lv_obj_t * cb;
	uint8_t counter = 0;

	while (x < nOFnames) {			// Initializes the desired pollen

		cb = lv_cb_create(win, NULL);
		lv_obj_set_pos(cb, posX, posY);
		lv_group_add_obj(group, cb);
		lv_cb_set_text(cb, "Name");
		lv_cb_set_action(cb, NULL);		//define what happen when checkbox pushed/released
		//updateCheckbox(cb,counter);
		counter++;
		x++;
		posY = posY + 20;

	}


	/* Create button to step to next page when checkboxes clicked (playlist created) */
	lv_obj_t *label;
	lv_obj_t *btn_play;

	btn_play = lv_btn_create(win, NULL);
	lv_obj_set_pos(btn_play, 90, 80);
	lv_btn_set_action(btn_play, LV_BTN_ACTION_CLICK, NULL);
	label = lv_label_create(btn_play, NULL);
	lv_label_set_text(label, SYMBOL_PLAY);
	lv_group_add_obj(group, btn_play);
}
