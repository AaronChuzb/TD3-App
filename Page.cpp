#include "Page.h"
#include "Arduino.h"

uint16_t page_index = 0;

lv_style_t light_style;
lv_style_t dark_style;

void my_timer(lv_timer_t *timer)
{
  // lv_obj_clean(timer->user_data);
  // lv_obj_t *page = (lv_obj_t *)timer->user_data;
  lv_obj_clean((lv_obj_t *)timer->user_data);
}





// 全局样式初始化
void style_init(void)
{
  // 暗色主题初始化
  lv_style_init(&dark_style);
  lv_style_set_bg_color(&dark_style, lv_color_hex(0x000000));
  lv_style_set_radius(&dark_style, 0);
  lv_style_set_pad_all(&dark_style, 0);
  lv_style_set_border_side(&dark_style, LV_BORDER_SIDE_NONE);
  // 亮色主题初始化
  lv_style_init(&light_style);
  lv_style_set_bg_color(&light_style, lv_color_hex(0xffffff));
  lv_style_set_radius(&light_style, 0);
  lv_style_set_pad_all(&light_style, 0);
  lv_style_set_border_side(&light_style, LV_BORDER_SIDE_NONE);
}

// 页面对象创建
lv_obj_t *Page::create_new_screen(int style)
{
  lv_obj_t *main_obj = lv_obj_create(NULL);
  lv_obj_clean(main_obj);
  lv_obj_set_size(main_obj, LV_HOR_RES, LV_VER_RES);
  if (style == 1)
  {
    lv_obj_add_style(main_obj, &light_style, 0);
  }
  else
  {
    lv_obj_add_style(main_obj, &dark_style, 0);
  }
  return main_obj;
}

// 页面状态栏创建
void Page_StatusBar_Init(lv_obj_t *pageContent)
{
  // 状态栏初始化
  static lv_style_t obj_layout_style; // 容器的样式
  lv_style_init(&obj_layout_style);
  lv_style_set_pad_all(&obj_layout_style, 0);
  lv_style_set_bg_opa(&obj_layout_style, 50);
  lv_style_set_text_font(&obj_layout_style, &lv_font_montserrat_14);
  lv_style_set_border_side(&obj_layout_style, LV_BORDER_SIDE_NONE);
  lv_style_set_radius(&obj_layout_style, 0);
  lv_style_set_text_color(&obj_layout_style, lv_color_hex(0xffffff));
  lv_obj_t *panel = lv_obj_create(pageContent);
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
}

void Page::Page_Init(uint16_t lenPages)
{
  style_init();
  PageNum = lenPages;
  PageList[lenPages];
  PageStack[lenPages];
  // 初始化默认页面
  cur_page.Created = NULL;
  cur_page.Destroy = NULL;
  StackTop = 0;
}

// 注册页面
bool Page::Page_Register(PageType Page)
{
  PageList[page_index] = Page;
  page_index++;
  return true;
}

// 页面入栈
bool Page::Page_Push(char *name)
{
  PageType page;
  // 在路由表中查找改页面，未找到跳转失败。
  for (int i = 0; i < PageNum; i++)
  {
    if (strcmp(PageList[i].name, name) == 0)
    {
      page = PageList[i];
      break;
    }
  }
  // 防止堆栈溢出
  if (StackTop >= PageNum - 1)
  {
    return false;
  }
  StackTop++;
  PageStack[StackTop] = page;
  new_page = PageStack[StackTop];
  old_page = cur_page;
  cur_page = new_page;

  // 移除旧页面状态栏

  //
  cur_page.Created();
  // lv_scr_load(cur_page.PageContent);
  // 不删除就屏幕对象指针，会导致返回页面空指针异常
  if (cur_page.show_status_bar == 1)
  {
    Page_StatusBar_Init(cur_page.PageContent);
  }
  lv_scr_load_anim(cur_page.PageContent, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
  // Page_StatusBar_Init();
  if (old_page.Destroy != NULL)
  {
    old_page.Destroy();
    lv_timer_t *timer = lv_timer_create(my_timer, 300, old_page.PageContent);
    lv_timer_set_repeat_count(timer, 1);
  }
}

// 页面入栈
bool Page::Page_Replace(char *name)
{
  PageType page;
  // 在路由表中查找改页面，未找到跳转失败。
  for (int i = 0; i < PageNum; i++)
  {
    if (strcmp(PageList[i].name, name) == 0)
    {
      page = PageList[i];
      break;
    }
  }
  if (StackTop >= PageNum - 1)
  {
    return false;
  }
  PageStack[StackTop] = page;
  new_page = PageStack[StackTop];
  old_page = cur_page;
  cur_page = new_page;
  cur_page.Created();
  if (cur_page.show_status_bar == 1)
  {
    Page_StatusBar_Init(cur_page.PageContent);
  }
  lv_scr_load_anim(cur_page.PageContent, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, true);
}

bool Page::Page_Back(uint16_t delt)
{
  // 防止堆栈溢出
  if (StackTop == 0)
  {
    return false;
  }
  while (delt > 0)
  {
    StackTop--;
    delt -= 1;
  }
  old_page = cur_page;
  cur_page = PageStack[StackTop];
  cur_page.Created();
  if (cur_page.show_status_bar == 1)
  {
    Page_StatusBar_Init(cur_page.PageContent);
  }
  lv_scr_load_anim(cur_page.PageContent, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, false);
  if (old_page.Destroy != NULL)
  {
    old_page.Destroy();
    lv_timer_t *timer = lv_timer_create(my_timer, 300, old_page.PageContent);
    lv_timer_set_repeat_count(timer, 1);
  }
}
