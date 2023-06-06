/*
 * @Date: 2023-04-13 15:07:38
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-06-06 23:22:15
 */
#include "App.h"

Page PageManager;

void App_Init()
{
  // 1. 页面管理框架初始化
  PageManager.Page_Init(10);
  // 2. 单页面组件初始化
  StartUp_Init(&PageManager);
  Home_Init(&PageManager);
  
  /* xxx_Init()
    ... 
    ...
    添加更多页面
    */

  // 3. 页面路由跳转
  PageManager.Page_Push("StartUp");
}

