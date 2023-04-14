/*
 * @Date: 2023-04-13 15:09:32
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-04-14 09:37:11
 */
#include "StartUp.h"

Page::PageType StartUp;

static void event_btn1_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
  if (code == LV_EVENT_CLICKED)
  { // 点击事件

    StartUp.Destroy();
    PageManager.Page_Push("Home");
  }
}

static void anim_x_cb(void *var, int32_t v)
{
  lv_obj_set_x((_lv_obj_t *)var, v);
  // lv_obj_set_size((_lv_obj_t *)var, v, lv_obj_get_height((_lv_obj_t *)var));
  // lv_obj_set_width((_lv_obj_t *)var, SDL_HOR_RES - v);
}

static void Created()
{
  StartUp.PageContent = create_new_screen();
  lv_obj_t *block_obj = lv_obj_create(StartUp.PageContent);
  lv_obj_set_style_bg_color(block_obj, lv_color_hex(0xafafaf), LV_STATE_DEFAULT);
  lv_obj_set_align(block_obj, LV_ALIGN_CENTER);
  lv_obj_set_size(block_obj, 50, 50);

  lv_obj_t *btn1 = lv_btn_create(StartUp.PageContent);               /*创建btn1*/
  lv_obj_add_event_cb(btn1, event_btn1_handler, LV_EVENT_ALL, NULL); /*设置btn1回调函数*/
  lv_obj_set_pos(btn1, 20, 40);

  lv_obj_t *label = lv_label_create(btn1); /*btn1内创建label*/
  lv_label_set_text(label, "To Home");
}

static void Update(void)
{
}

static void Destroy(void)
{
  // 页面销毁动画
  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, StartUp.PageContent);
  lv_anim_set_values(&a, lv_obj_get_x(StartUp.PageContent), -lv_obj_get_width(StartUp.PageContent));
  lv_anim_set_time(&a, 800);
  lv_anim_set_exec_cb(&a, anim_x_cb);
  lv_anim_set_path_cb(&a, lv_anim_path_linear);
  lv_anim_start(&a);
  // 动画结束后删除对象
  lv_obj_del_delayed(StartUp.PageContent, 800);
  // lv_obj_clean(StartUp.PageContent);
  // lv_obj_del(StartUp.PageContent);
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