/*
 * @Date: 2023-04-13 15:07:38
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-04-13 17:37:05
 */
#include "App.h"

Page PageManager;
lv_obj_t *page_obj_content;
lv_style_t page_style;

void style_init(void)
{
  lv_style_init(&page_style);
  lv_style_set_bg_color(&page_style, lv_color_hex(0x000000));
  lv_style_set_radius(&page_style, 0);
  lv_style_set_pad_all(&page_style, 0);
  lv_style_set_border_side(&page_style, LV_BORDER_SIDE_NONE);
}

void App_Init()
{

  style_init();
  page_obj_content = lv_obj_create(NULL);
  lv_obj_add_style(page_obj_content, &page_style, 0);
  lv_scr_load(page_obj_content);
  PageManager.Page_Init(10);
  StartUp_Init();
  Home_Init();
  PageManager.Page_Push("StartUp");
  
  
}

void setstatus(char *name, lv_obj_t *obj){
   lv_obj_t * label1 = lv_label_create(obj);
  lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
  lv_label_set_text(label1, name);
}



lv_obj_t *create_new_screen(void)
{
  lv_obj_t *main_obj = lv_obj_create(page_obj_content);
  lv_obj_clean(main_obj);
  lv_obj_set_size(main_obj, 150, 300); // 根据个人屏幕大小修改
  return main_obj;
}