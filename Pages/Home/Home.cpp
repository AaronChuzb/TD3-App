/*
 * @Date: 2023-04-13 17:27:57
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-04-14 16:01:36
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

static lv_anim_timeline_t *anim_timeline = NULL;

static lv_obj_t *obj1 = NULL;
static lv_obj_t *obj2 = NULL;
static lv_obj_t *obj3 = NULL;
static lv_obj_t *obj4 = NULL;
static lv_obj_t *obj5 = NULL;
static lv_obj_t *obj6 = NULL;
static lv_obj_t *obj7 = NULL;
static lv_obj_t *obj8 = NULL;
static lv_obj_t *obj9 = NULL;

static const lv_coord_t obj_width = 60;
static const lv_coord_t obj_height = 60;

static void anim_x_cb(void *var, int32_t v)
{
  lv_obj_set_x((_lv_obj_t *)var, v);
  // lv_obj_set_width(Home.PageContent, SDL_HOR_RES - v);
}

static void set_width(void *var, int32_t v)
{
  lv_obj_set_width((lv_obj_t *)var, v);
}

static void set_height(void *var, int32_t v)
{
  lv_obj_set_height((lv_obj_t *)var, v);
}

static void anim_timeline_create(void)
{
  /* obj1 */
  lv_anim_t a1;
  lv_anim_init(&a1);
  lv_anim_set_var(&a1, obj1);
  lv_anim_set_values(&a1, 0, obj_width);
  lv_anim_set_early_apply(&a1, false);
  lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)set_width);
  lv_anim_set_path_cb(&a1, lv_anim_path_overshoot);
  lv_anim_set_time(&a1, 300);

  lv_anim_t a2;
  lv_anim_init(&a2);
  lv_anim_set_var(&a2, obj1);
  lv_anim_set_values(&a2, 0, obj_height);
  lv_anim_set_early_apply(&a2, false);
  lv_anim_set_exec_cb(&a2, (lv_anim_exec_xcb_t)set_height);
  lv_anim_set_path_cb(&a2, lv_anim_path_ease_out);
  lv_anim_set_time(&a2, 300);

  /* obj2 */
  lv_anim_t a3;
  lv_anim_init(&a3);
  lv_anim_set_var(&a3, obj2);
  lv_anim_set_values(&a3, 0, obj_width);
  lv_anim_set_early_apply(&a3, false);
  lv_anim_set_exec_cb(&a3, (lv_anim_exec_xcb_t)set_width);
  lv_anim_set_path_cb(&a3, lv_anim_path_overshoot);
  lv_anim_set_time(&a3, 300);

  lv_anim_t a4;
  lv_anim_init(&a4);
  lv_anim_set_var(&a4, obj2);
  lv_anim_set_values(&a4, 0, obj_height);
  lv_anim_set_early_apply(&a4, false);
  lv_anim_set_exec_cb(&a4, (lv_anim_exec_xcb_t)set_height);
  lv_anim_set_path_cb(&a4, lv_anim_path_ease_out);
  lv_anim_set_time(&a4, 300);

  /* obj3 */
  lv_anim_t a5;
  lv_anim_init(&a5);
  lv_anim_set_var(&a5, obj3);
  lv_anim_set_values(&a5, 0, obj_width);
  lv_anim_set_early_apply(&a5, false);
  lv_anim_set_exec_cb(&a5, (lv_anim_exec_xcb_t)set_width);
  lv_anim_set_path_cb(&a5, lv_anim_path_overshoot);
  lv_anim_set_time(&a5, 300);

  lv_anim_t a6;
  lv_anim_init(&a6);
  lv_anim_set_var(&a6, obj3);
  lv_anim_set_values(&a6, 0, obj_height);
  lv_anim_set_early_apply(&a6, false);
  lv_anim_set_exec_cb(&a6, (lv_anim_exec_xcb_t)set_height);
  lv_anim_set_path_cb(&a6, lv_anim_path_ease_out);
  lv_anim_set_time(&a6, 300);

  /* obj4 */
  lv_anim_t a7;
  lv_anim_init(&a7);
  lv_anim_set_var(&a7, obj4);
  lv_anim_set_values(&a7, 0, obj_width);
  lv_anim_set_early_apply(&a7, false);
  lv_anim_set_exec_cb(&a7, (lv_anim_exec_xcb_t)set_width);
  lv_anim_set_path_cb(&a7, lv_anim_path_overshoot);
  lv_anim_set_time(&a7, 300);

  lv_anim_t a8;
  lv_anim_init(&a8);
  lv_anim_set_var(&a8, obj4);
  lv_anim_set_values(&a8, 0, obj_height);
  lv_anim_set_early_apply(&a8, false);
  lv_anim_set_exec_cb(&a8, (lv_anim_exec_xcb_t)set_height);
  lv_anim_set_path_cb(&a8, lv_anim_path_ease_out);
  lv_anim_set_time(&a8, 300);

  /* obj5 */
  lv_anim_t a9;
  lv_anim_init(&a9);
  lv_anim_set_var(&a9, obj5);
  lv_anim_set_values(&a9, 0, obj_width);
  lv_anim_set_early_apply(&a9, false);
  lv_anim_set_exec_cb(&a9, (lv_anim_exec_xcb_t)set_width);
  lv_anim_set_path_cb(&a9, lv_anim_path_overshoot);
  lv_anim_set_time(&a9, 300);

  lv_anim_t a10;
  lv_anim_init(&a10);
  lv_anim_set_var(&a10, obj5);
  lv_anim_set_values(&a10, 0, obj_height);
  lv_anim_set_early_apply(&a10, false);
  lv_anim_set_exec_cb(&a10, (lv_anim_exec_xcb_t)set_height);
  lv_anim_set_path_cb(&a10, lv_anim_path_ease_out);
  lv_anim_set_time(&a10, 300);

  /* obj6 */
  lv_anim_t a11;
  lv_anim_init(&a11);
  lv_anim_set_var(&a11, obj6);
  lv_anim_set_values(&a11, 0, obj_width);
  lv_anim_set_early_apply(&a11, false);
  lv_anim_set_exec_cb(&a11, (lv_anim_exec_xcb_t)set_width);
  lv_anim_set_path_cb(&a11, lv_anim_path_overshoot);
  lv_anim_set_time(&a11, 300);

  lv_anim_t a12;
  lv_anim_init(&a12);
  lv_anim_set_var(&a12, obj6);
  lv_anim_set_values(&a12, 0, obj_height);
  lv_anim_set_early_apply(&a12, false);
  lv_anim_set_exec_cb(&a12, (lv_anim_exec_xcb_t)set_height);
  lv_anim_set_path_cb(&a12, lv_anim_path_ease_out);
  lv_anim_set_time(&a12, 300);

  /* Create anim timeline */
  anim_timeline = lv_anim_timeline_create();
  lv_anim_timeline_add(anim_timeline, 0, &a1);
  lv_anim_timeline_add(anim_timeline, 0, &a2);
  lv_anim_timeline_add(anim_timeline, 200, &a3);
  lv_anim_timeline_add(anim_timeline, 200, &a4);
  lv_anim_timeline_add(anim_timeline, 400, &a5);
  lv_anim_timeline_add(anim_timeline, 400, &a6);
  lv_anim_timeline_add(anim_timeline, 600, &a7);
  lv_anim_timeline_add(anim_timeline, 600, &a8);
  lv_anim_timeline_add(anim_timeline, 800, &a9);
  lv_anim_timeline_add(anim_timeline, 800, &a10);
  lv_anim_timeline_add(anim_timeline, 1000, &a11);
  lv_anim_timeline_add(anim_timeline, 1000, &a12);
}

static void btn_start_event_handler(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target(e);

    if (!anim_timeline) {
        anim_timeline_create();
    }

    bool reverse = lv_obj_has_state(btn, LV_STATE_CHECKED);
    lv_anim_timeline_set_reverse(anim_timeline, reverse);
    lv_anim_timeline_start(anim_timeline);
}

static void Created()
{
  Home.PageContent = create_new_screen();

  // lv_obj_t *block_obj = lv_obj_create(Home.PageContent);
  // lv_obj_set_style_bg_color(block_obj, lv_color_hex(0x000000), LV_STATE_DEFAULT);
  // lv_obj_set_align(block_obj, LV_ALIGN_CENTER);
  // lv_obj_set_size(block_obj, 50, 50);

  lv_obj_t *btn1 = lv_btn_create(Home.PageContent);                  /*创建btn1*/
  lv_obj_add_event_cb(btn1, event_btn1_handler, LV_EVENT_ALL, NULL); /*设置btn1回调函数*/
  lv_obj_set_pos(btn1, 0, 20);
  lv_obj_add_flag(btn1, LV_OBJ_FLAG_IGNORE_LAYOUT);

  lv_obj_t *label = lv_label_create(btn1); /*btn1内创建label*/
  lv_label_set_text(label, "Go Back");

  lv_obj_t *btn2 = lv_btn_create(Home.PageContent); /*创建btn1*/
  lv_obj_set_pos(btn2, 100, 20);
  lv_obj_add_flag(btn2, LV_OBJ_FLAG_IGNORE_LAYOUT);
  lv_obj_add_event_cb(btn2, btn_start_event_handler, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_flag(btn2, LV_OBJ_FLAG_IGNORE_LAYOUT);
  lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_t *label2 = lv_label_create(btn2); /*btn1内创建label*/
  lv_label_set_text(label2, "test");

  lv_obj_set_flex_flow(Home.PageContent, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_flex_align(Home.PageContent, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  // lv_anim_t a;
  // lv_anim_init(&a);
  // lv_anim_set_var(&a, Home.PageContent);
  // lv_anim_set_values(&a, SDL_HOR_RES, 0);
  // lv_anim_set_time(&a, 800);
  // lv_anim_set_exec_cb(&a, anim_x_cb);
  // lv_anim_set_path_cb(&a, lv_anim_path_linear);
  // lv_anim_start(&a);

  obj1 = lv_obj_create(Home.PageContent);
  lv_obj_set_size(obj1, obj_width, obj_height);

  obj2 = lv_obj_create(Home.PageContent);
  lv_obj_set_size(obj2, obj_width, obj_height);

  obj3 = lv_obj_create(Home.PageContent);
  lv_obj_set_size(obj3, obj_width, obj_height);

  obj4 = lv_obj_create(Home.PageContent);
  lv_obj_set_size(obj4, obj_width, obj_height);

  obj5 = lv_obj_create(Home.PageContent);
  lv_obj_set_size(obj5, obj_width, obj_height);

  obj6 = lv_obj_create(Home.PageContent);
  lv_obj_set_size(obj6, obj_width, obj_height);

  anim_timeline_create();
  // lv_anim_timeline_set_reverse(anim_timeline, false);
  // lv_anim_timeline_start(anim_timeline);
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