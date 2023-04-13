/*
 * @Date: 2023-04-13 15:09:32
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-04-13 17:42:52
 */
#include "StartUp.h"

Page::PageType StartUp;

static void event_btn1_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
  if (code == LV_EVENT_CLICKED)
  { // 点击事件
  lv_obj_clean(StartUp.PageContent);
  lv_obj_del(StartUp.PageContent);
    PageManager.Page_Push("Home");
  }
}

static void Created()
{
  StartUp.PageContent = create_new_screen();
  lv_obj_t *block_obj = lv_obj_create(StartUp.PageContent);
  lv_obj_set_style_bg_color(block_obj, lv_color_hex(0xafafaf), LV_STATE_DEFAULT);
  lv_obj_set_align(block_obj, LV_ALIGN_CENTER);
  lv_obj_set_size(block_obj, 50, 50);

  lv_obj_t *btn1 = lv_btn_create(StartUp.PageContent);                  /*创建btn1*/
  lv_obj_add_event_cb(btn1, event_btn1_handler, LV_EVENT_ALL, NULL); /*设置btn1回调函数*/
  lv_obj_set_pos(btn1, 20, 40);

  lv_obj_t * label = lv_label_create(btn1);/*btn1内创建label*/
    lv_label_set_text(label, "To Home");
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

void StartUp_Init()
{
  strcpy(StartUp.name, "StartUp");
  StartUp.BeforeEnter = NULL;
  StartUp.Created = Created;
  StartUp.Update = Update;
  StartUp.Destroy = Destroy;
  StartUp.Method = Method;
  PageManager.Page_Register(StartUp);
}