/*
 * @Date: 2023-04-13 17:27:57
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-07-24 16:34:30
 */
#include "Home.h"

Page::PageType Home;
Page *Home_Manager;



static void event_btn1_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
  if (code == LV_EVENT_CLICKED)
  { // 点击事件
    Home_Manager->Page_Push("Ammeter");
  }
}

static void Created()
{
  lv_obj_t *btn1 = lv_btn_create(Home.PageContent);               /*创建btn1*/
  lv_obj_add_event_cb(btn1, event_btn1_handler, LV_EVENT_ALL, NULL); /*设置btn1回调函数*/
  lv_obj_set_pos(btn1, 30, 40);

  lv_obj_t *label = lv_label_create(btn1); /*btn1内创建label*/
  lv_label_set_text(label, "ele");
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

void Home_Init(Page *PageManager)
{
  strcpy(Home.name, "Home");
  Home.show_status_bar = true;
  Home.BeforeEnter = NULL;
  Home.Created = Created;
  Home.Update = Update;
  Home.Destroy = Destroy;
  Home.Method = Method;
  Home.PageContent = PageManager->create_new_screen();
  Home_Manager = PageManager;
  Home_Manager->Page_Register(Home);
}