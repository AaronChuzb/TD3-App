/*
 * @Date: 2023-04-13 15:07:38
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-04-14 15:13:59
 */
#include "App.h"

Page PageManager;
lv_obj_t *main_win;
lv_style_t page_style;
lv_style_t content_style;

void style_init(void)
{
  lv_style_init(&page_style);
  lv_style_set_bg_color(&page_style, lv_color_hex(0x000000));
  lv_style_set_radius(&page_style, 0);
  lv_style_set_pad_all(&page_style, 0);
  lv_style_set_border_side(&page_style, LV_BORDER_SIDE_NONE);

  lv_style_init(&content_style);
  lv_style_set_radius(&content_style, 0);
  lv_style_set_pad_all(&content_style, 0);
  lv_style_set_border_side(&content_style, LV_BORDER_SIDE_NONE);
}

void App_Init()
{

  style_init();
  // 根节点
  main_win = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(main_win, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_size(main_win, LV_HOR_RES, LV_VER_RES);
  lv_obj_set_pos(main_win, 0, 0);
  lv_obj_add_style(main_win, &page_style, 0);

  // lv_obj_set_flex_flow(main_win, LV_FLEX_FLOW_COLUMN);

  lv_obj_t *status_bar = lv_obj_create(main_win);
  lv_obj_set_size(status_bar, LV_HOR_RES, 20);
  // lv_obj_align(status_bar, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
  // lv_obj_set_pos(status_bar, 0, 0);
  lv_obj_add_style(status_bar, &page_style, 0);

  lv_scr_load(main_win);

  PageManager.Page_Init(10);
  // 状态栏初始化
  static lv_style_t obj_layout_style; // 容器的样式
  lv_style_init(&obj_layout_style);
  lv_style_set_pad_all(&obj_layout_style, 0);
  lv_style_set_bg_opa(&obj_layout_style, 50);
  lv_style_set_text_font(&obj_layout_style, &lv_font_montserrat_14);
  lv_style_set_border_side(&obj_layout_style, LV_BORDER_SIDE_NONE);
  lv_style_set_radius(&obj_layout_style, 0);
  lv_style_set_text_color(&obj_layout_style, lv_color_hex(0xffffff));

  lv_obj_t *panel = lv_obj_create(main_win);
  lv_obj_set_size(panel, 240, 20);
  lv_obj_add_style(panel, &obj_layout_style, 0);
  lv_obj_set_pos(panel, 0, 0);
  lv_obj_set_scrollbar_mode(panel, LV_SCROLLBAR_MODE_OFF);

  lv_obj_set_layout(panel, LV_LAYOUT_FLEX);
  // lv_obj_set_style_base_dir(panel, LV_BASE_DIR_RTL, 0);
  lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  // lv_obj_align(panel, LV_ALIGN_RIGHT_MID, 0, 0);

  lv_obj_t *label_wifi = lv_label_create(panel);
  lv_label_set_text(label_wifi, LV_SYMBOL_WIFI);
  lv_obj_t *label_time = lv_label_create(panel);
  lv_label_set_text(label_time, "00:00");
  // lv_obj_align(label_time, LV_ALIGN_LEFT_MID, 0, 0);
  // lv_timer_t * timer = lv_timer_create(lv_timer_update_time, 1000, label_time);

  // lv_obj_t *label = lv_label_create(panel);
  // lv_label_set_text(label, " ");
  lv_obj_t *label_bat = lv_label_create(panel);
  lv_label_set_text(label_bat, LV_SYMBOL_BATTERY_EMPTY);
  lv_obj_t *label_batchar = lv_label_create(label_bat);
  lv_obj_set_style_text_font(label_batchar, &lv_font_montserrat_14, 0);
  lv_label_set_text(label_batchar, LV_SYMBOL_CHARGE);
  lv_obj_center(label_batchar);
  // lv_obj_align(label_batchar, LV_ALIGN_LEFT_MID, 0, 0);

  StartUp_Init();
  Home_Init();
  PageManager.Page_Push("StartUp");
}

void setstatus(char *name, lv_obj_t *obj)
{
  lv_obj_t *label1 = lv_label_create(obj);
  lv_label_set_recolor(label1, true); /*Enable re-coloring by commands in the text*/
  lv_label_set_text(label1, name);
}

lv_obj_t *create_new_screen(void)
{

  lv_obj_t *content = lv_obj_create(main_win);
  lv_obj_clean(content);
  lv_obj_set_size(content, LV_HOR_RES, LV_VER_RES - 20); // 根据个人屏幕大小修改
  lv_obj_set_pos(content, 0, 20);                        // 根据个人屏幕大小修改
  lv_obj_add_style(content, &content_style, 0);

  return content;
}