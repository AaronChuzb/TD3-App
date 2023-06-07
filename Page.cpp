#include "Page.h"

lv_obj_t *main_win;
lv_style_t page_style;
lv_style_t content_style;

// 页面总样式初始化
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

// 横向动画函数
static void anim_x_cb(void *var, int32_t v)
{
  lv_obj_set_x((_lv_obj_t *)var, v);
}

// 从右向左退出
void Page::Animation_Left_Out(PageType page)
{
  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, page.PageContent);
  lv_anim_set_values(&a, lv_obj_get_x(page.PageContent), -lv_obj_get_width(page.PageContent));
  lv_anim_set_time(&a, 300);
  lv_anim_set_exec_cb(&a, anim_x_cb);
  lv_anim_set_path_cb(&a, lv_anim_path_linear);
  lv_anim_start(&a);
}
// 从右向左进入
void Page::Animation_Right_In(PageType page)
{
  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, page.PageContent);
  lv_anim_set_values(&a, LV_HOR_RES, 0);
  lv_anim_set_time(&a, 300);
  lv_anim_set_exec_cb(&a, anim_x_cb);
  lv_anim_set_path_cb(&a, lv_anim_path_linear);
  lv_anim_start(&a);
}
// 从左向右进入
void Page::Animation_Left_In(PageType page)
{
  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, page.PageContent);
  lv_anim_set_values(&a, 0, 300);
  lv_anim_set_time(&a, 300);
  lv_anim_set_exec_cb(&a, anim_x_cb);
  lv_anim_set_path_cb(&a, lv_anim_path_linear);
  lv_anim_start(&a);
}
// 从左向右退出
void Page::Animation_Right_Out(PageType page)
{
  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, page.PageContent);
  lv_anim_set_values(&a, 0, lv_obj_get_width(page.PageContent));
  lv_anim_set_time(&a, 300);
  lv_anim_set_exec_cb(&a, anim_x_cb);
  lv_anim_set_path_cb(&a, lv_anim_path_linear);
  lv_anim_start(&a);
}

lv_obj_t *create_new_screen(bool hasStatusBar)
{
  
  lv_obj_t *content = lv_obj_create(main_win);
  lv_obj_clean(content);
  if(hasStatusBar){
    lv_obj_set_size(content, LV_HOR_RES, LV_VER_RES - 20); // 根据个人屏幕大小修改
    lv_obj_set_pos(content, 0, 20); 
  } else {
    lv_obj_set_size(content, LV_HOR_RES, LV_VER_RES); // 根据个人屏幕大小修改
    lv_obj_set_pos(content, 0, 0); 
  }
  lv_obj_add_style(content, &content_style, 0);
  return content;
}

uint16_t page_index = 0;

void Page::Page_Init(uint16_t lenPages)
{
  // 容器初始化
  style_init();
  main_win = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(main_win, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_size(main_win, LV_HOR_RES, LV_VER_RES);
  lv_obj_set_pos(main_win, 0, 0);
  lv_obj_add_style(main_win, &page_style, 0);
  lv_obj_t *status_bar = lv_obj_create(main_win);
  lv_obj_set_size(status_bar, LV_HOR_RES, 20);
  lv_obj_add_style(status_bar, &page_style, 0);
  lv_scr_load(main_win);

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
  if(old_page.Destroy != NULL){
    old_page.Destroy();
  }
  cur_page.Created();
  // if(old_page.PageContent){
  //   Animation_Left_Out(old_page);
  // }
  // Animation_Right_In(cur_page);
  
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
  if(old_page.Destroy != NULL){
    old_page.Destroy();
  }
  cur_page.Created();
  // Animation_Right_Out(old_page);
  // Animation_Left_In(page);
}
