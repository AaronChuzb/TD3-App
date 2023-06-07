#ifndef PAGE_H
#define PAGE_H

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include <lvgl.h>
#else
#include "../lvgl/lvgl.h"
#endif

lv_obj_t *create_new_screen(bool hasStatusBar);


class Page
{
public:
  // 生命周期钩子
  typedef void (*EventHook)(void);
  // 回调钩子
  typedef void (*CallBack)(void *, int);
  struct PageType // 页面生命周期
  {
    char name[32];         // 页面名称
    lv_obj_t *PageContent;        // 页面对象
    EventHook BeforeEnter; // 独享路由守卫
    EventHook Created;     // 页面创建回调钩子
    EventHook Update;      // 页面更新
    EventHook Destroy;     // 页面销毁
    CallBack Method;       // 页面事件回调
  } ;
  struct PageType new_page, old_page, cur_page;  // 新页面，旧页面，默认页面
  void Page_Init(uint16_t lenPages = 99); // 页面管理框架初始化
  bool Page_Register(PageType Page);      // 注册页面
  bool Page_Push(char *name);             // 页面跳转
  bool Page_Back(uint16_t delt);          // 返回页数
  void Destroy_Animation(Page::PageType page);
  void Animation_Left_Out(Page::PageType page); // 从右向左退出
  void Animation_Right_In(Page::PageType page); // 从右向左进入
  void Animation_Left_In(Page::PageType page);  // 从左向右进入
  void Animation_Right_Out(Page::PageType page);// 从左向右退出
private:
  PageType PageList[10];  // 页面列表
  PageType PageStack[10]; // 页面堆栈
  uint16_t PageNum;       // 页面数量
  uint16_t StackTop;      // 栈顶
};

#endif