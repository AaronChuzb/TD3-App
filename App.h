/*
 * @Date: 2023-04-13 15:07:53
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-04-14 11:53:26
 */
#ifndef APP_H
#define APP_H

#include <lvgl.h>
#include "Page.h"
#include "Pages/StartUp/StartUp.h"
#include "Pages/Home/Home.h"

extern Page PageManager;
void App_Init();
lv_obj_t *create_new_screen(void);

#endif