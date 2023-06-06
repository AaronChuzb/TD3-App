/*
 * @Date: 2023-04-13 15:09:32
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-06-06 23:24:17
 */
#include "StartUp.h"
#include "HAL/HAL.h"

Page::PageType StartUp;
Page *Start_Manager;

bool light1 = false;
bool light2 = false;
bool light3 = false;
bool light4 = false;
bool beep = false;

static void event_btn1_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
  if (code == LV_EVENT_CLICKED)
  { // 点击事件

    StartUp.Destroy();
    Start_Manager->Page_Push("Home");
  }
}

static void bt14_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
  if (code == LV_EVENT_CLICKED)
  { // 点击事件
    if(light1){
      digitalWrite(14, 0);
      light1 = false;
    } else {
      digitalWrite(14, 1);
      light1 = true;
    }
  }
}

static void bt13_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
  if (code == LV_EVENT_CLICKED)
  { // 点击事件
    if(light2){
      digitalWrite(13, 0);
      light2 = false;
    } else {
      digitalWrite(13, 1);
      light2 = true;
    }
  }
}

static void bt12_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
  if (code == LV_EVENT_CLICKED)
  { // 点击事件
    if(light3){
      digitalWrite(12, 0);
      light3 = false;
    } else {
      digitalWrite(12, 1);
      light3 = true;
    }
  }
}

static void bt11_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
  if (code == LV_EVENT_CLICKED)
  { // 点击事件
    if(light4){
      digitalWrite(11, 0);
      light4 = false;
    } else {
      digitalWrite(11, 1);
      light4 = true;
    }
  }
}

static void beep_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
  if (code == LV_EVENT_CLICKED)
  { // 点击事件
    if(beep){
      digitalWrite(4, 0);
      beep = false;
    } else {
      digitalWrite(4, 1);
      beep = true;
    }
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
  // lv_obj_t *block_obj = lv_obj_create(StartUp.PageContent);
  // lv_obj_set_style_bg_color(block_obj, lv_color_hex(0xafafaf), LV_STATE_DEFAULT);
  // lv_obj_set_align(block_obj, LV_ALIGN_CENTER);
  // lv_obj_set_size(block_obj, 50, 50);

  lv_obj_t *btn1 = lv_btn_create(StartUp.PageContent);               /*创建btn1*/
  lv_obj_add_event_cb(btn1, event_btn1_handler, LV_EVENT_ALL, NULL); /*设置btn1回调函数*/
  lv_obj_set_pos(btn1, 20, 40);

  lv_obj_t *label = lv_label_create(btn1); /*btn1内创建label*/
  lv_label_set_text(label, "To Home");
  lv_obj_add_flag(btn1, LV_OBJ_FLAG_IGNORE_LAYOUT);

  // lv_obj_t *label1 = lv_label_create(StartUp.PageContent);
  // lv_label_set_text(label1, HAL::Get_Bat().c_str());

  lv_obj_t *btn14 = lv_btn_create(StartUp.PageContent);
  lv_obj_add_event_cb(btn14, bt14_handler, LV_EVENT_ALL, NULL);
  lv_obj_t *label14 = lv_label_create(btn14); /*btn1内创建label*/
  lv_label_set_text(label14, "IO14");

  lv_obj_t *btn13 = lv_btn_create(StartUp.PageContent);
  lv_obj_add_event_cb(btn13, bt13_handler, LV_EVENT_ALL, NULL);
  lv_obj_t *label13 = lv_label_create(btn13); /*btn1内创建label*/
  lv_label_set_text(label13, "IO13");

  lv_obj_t *btn12 = lv_btn_create(StartUp.PageContent);
  lv_obj_add_event_cb(btn12, bt12_handler, LV_EVENT_ALL, NULL);
  lv_obj_t *label12 = lv_label_create(btn12); /*btn1内创建label*/
  lv_label_set_text(label12, "IO12");

  lv_obj_t *btn11 = lv_btn_create(StartUp.PageContent);
  lv_obj_add_event_cb(btn11, bt11_handler, LV_EVENT_ALL, NULL);
  lv_obj_t *label11 = lv_label_create(btn11); /*btn1内创建label*/
  lv_label_set_text(label11, "IO11");

  lv_obj_t *btnbeep = lv_btn_create(StartUp.PageContent);
  lv_obj_add_event_cb(btnbeep, beep_handler, LV_EVENT_ALL, NULL);
  lv_obj_t *labelbeep = lv_label_create(btnbeep); /*btn1内创建label*/
  lv_label_set_text(labelbeep, "beep");

  lv_obj_set_flex_flow(StartUp.PageContent, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_flex_align(StartUp.PageContent, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);


}

static void Update(void)
{
}

static void Destroy(void)
{
  // 页面销毁动画
  // lv_anim_t a;
  // lv_anim_init(&a);
  // lv_anim_set_var(&a, StartUp.PageContent);
  // lv_anim_set_values(&a, lv_obj_get_x(StartUp.PageContent), -lv_obj_get_width(StartUp.PageContent));
  // lv_anim_set_time(&a, 300);
  // lv_anim_set_exec_cb(&a, anim_x_cb);
  // lv_anim_set_path_cb(&a, lv_anim_path_linear);
  // lv_anim_start(&a);
  Start_Manager->Destroy_Animation(StartUp);
  // 动画结束后删除对象
  lv_obj_del_delayed(StartUp.PageContent, 300);
  // lv_obj_clean(StartUp.PageContent);
  // lv_obj_del(StartUp.PageContent);
}

static void Method(void *btn, int event)
{
}

void StartUp_Init(Page *PageManager)
{
  strcpy(StartUp.name, "StartUp");
  StartUp.BeforeEnter = NULL;
  StartUp.Created = Created;
  StartUp.Update = Update;
  StartUp.Destroy = Destroy;
  StartUp.Method = Method;
  Start_Manager = PageManager;
  Start_Manager->Page_Register(StartUp);
}