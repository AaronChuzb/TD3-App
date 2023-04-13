/*
 * @Date: 2023-04-13 17:27:57
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-04-13 17:53:52
 */
#include "Home.h"

Page::PageType Home;

static void event_btn1_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
  if (code == LV_EVENT_CLICKED)
  { // 点击事件
  lv_obj_clean(Home.PageContent);
  lv_obj_del(Home.PageContent);
    PageManager.Page_Back(1);
  }
}

static void Created()
{
  Home.PageContent = create_new_screen();

  lv_obj_t *block_obj = lv_obj_create(Home.PageContent);
  lv_obj_set_style_bg_color(block_obj, lv_color_hex(0x000000), LV_STATE_DEFAULT);
  lv_obj_set_align(block_obj, LV_ALIGN_CENTER);
  lv_obj_set_size(block_obj, 50, 50);

  lv_obj_t *btn1 = lv_btn_create(Home.PageContent);                  /*创建btn1*/
  lv_obj_add_event_cb(btn1, event_btn1_handler, LV_EVENT_ALL, NULL); /*设置btn1回调函数*/
  lv_obj_set_pos(btn1, 20, 40);

  lv_obj_t *label = lv_label_create(btn1); /*btn1内创建label*/
  lv_label_set_text(label, "Go Back");
}

static void Update(void)
{
}

static void Destroy(void)
{
}

static void Method(void *btn, int event)
{
}

void Home_Init()
{
  strcpy(Home.name, "Home");

  Home.BeforeEnter = NULL;
  Home.Created = Created;
  Home.Update = Update;
  Home.Destroy = Destroy;
  Home.Method = Method;
  if (PageManager.Page_Register(Home))
  {
    // setstatus("Home", Home.PageContent);
  }
}