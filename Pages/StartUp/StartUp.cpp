/*
 * @Date: 2023-04-13 17:27:57
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-08-11 23:43:07
 */
#include "StartUp.h"

Page::PageType StartUp;
Page *StartUp_Manager;
lv_obj_t *progress;
uint8_t progress_value = 0;
lv_timer_t *timer;



// static void event_btn1_handler(lv_event_t *e)
// {
//   lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
//   if (code == LV_EVENT_CLICKED)
//   { // 点击事件
//     StartUp_Manager->Page_Replace("Home");
//   }
// }

static void update_progress(lv_timer_t *timer)
{
    progress_value++;
    if (progress_value > 100) {
        // progress_value = 0;
        lv_timer_del(timer);
        StartUp_Manager->Page_Replace("Home");
    }
    lv_bar_set_value(progress, progress_value, LV_ANIM_OFF);
}

static void Created()
{
  // lv_scr_load_anim(page, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, false);
  // lv_obj_t *btn1 = lv_btn_create(StartUp.PageContent);               /*创建btn1*/
  // lv_obj_add_event_cb(btn1, event_btn1_handler, LV_EVENT_ALL, NULL); /*设置btn1回调函数*/
  // lv_obj_set_pos(btn1, 20, 40);

  // lv_obj_t *label = lv_label_create(btn1); /*btn1内创建label*/
  // lv_label_set_text(label, "To Home");

  lv_obj_t *label1 = lv_label_create(StartUp.PageContent);
  lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#ffffff Welcome!#");
  // lv_style_set_text_color(&obj_layout_style, lv_color_hex(0xffffff));
  
  lv_obj_align(label1, LV_ALIGN_CENTER, 0, -20); // 居中对齐，向上偏移20个像素

  progress = lv_bar_create(StartUp.PageContent);
  lv_obj_set_size(progress, LV_HOR_RES - 40, 10); // 设置进度条大小
  lv_obj_align(progress, LV_ALIGN_CENTER, 0, 20); // 居中对齐，向下偏移20个像素
  lv_bar_set_range(progress, 0, 100);             // 设置进度条范围

  timer = lv_timer_create(update_progress, 50, NULL);
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

void StartUp_Init(Page *PageManager)
{
  strcpy(StartUp.name, "StartUp");
  StartUp.show_status_bar = 0;
  StartUp.BeforeEnter = NULL;
  StartUp.Created = Created;
  StartUp.Update = Update;
  StartUp.Destroy = Destroy;
  StartUp.Method = Method;
  StartUp.PageContent = PageManager->create_new_screen(0);
  StartUp_Manager = PageManager;
  PageManager->Page_Register(StartUp);
}