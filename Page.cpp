#include "Page.h"
uint16_t page_index = 0;

void Page::Page_Init(uint16_t lenPages)
{
  PageNum = lenPages;
  PageList[lenPages];
  PageStack[lenPages];
  // 初始化默认页面
  cur_page.Created  = NULL;

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
  for (int i = 0; i < PageNum; i++)
  {
    
    if (strcmp(PageList[i].name, name) == 0)
    {
      // PageList[0].Created();
      page = PageList[i];
      // page.Created();
    }
    else
    {
     
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
  old_page  = cur_page;
  cur_page = new_page;
  cur_page.Created();
  
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
}
