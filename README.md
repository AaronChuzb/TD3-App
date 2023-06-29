<!--
 * @Date: 2023-04-13 18:03:10
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-06-29 15:07:47
-->
# 基于LVGL的页面管理框架

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

简介

用于TD3项目UI交互方案。

目前更新进度：

1. 完成简单页面切换功能



## 内容列表

- [使用](#使用)
  - [配置模拟器环境](#配置模拟器环境)
  - [修改项目](#修改项目)
- [项目结构](#项目结构)
- [相关仓库](#相关仓库)
- [维护者](#维护者)
- [如何贡献](#如何贡献)
- [使用许可](#使用许可)


## 使用

开发阶段的项目运行于模拟器环境。且基于PlatformIO。

### 1. 配置模拟器环境


请先拉取模拟器代码：
- [lv_platformio](https://github.com/lvgl/lv_platformio)

并且按照该仓库下的教程搭建vscode模拟器开发环境。

### 2. 修改项目

- 修改根目录下platformio.ini文件，具体相关配置项请参考PlatformIO说明。

```sh
[platformio]
default_envs = emulator_64bits

; Shared options
[env]
build_flags =
  ; Don't use lv_conf.h. Tweak params via platfom.ini.
  -D LV_CONF_SKIP
  -D LV_CONF_INCLUDE_SIMPLE
  -D LV_CONF_INCLUDE_SIMPLE
  ; -D LV_USE_PERF_MONITOR
  ; -D LV_USE_MEM_MONITOR
  -D LV_DISP_DEF_REFR_PERIOD="10"
  ; Enable LVGL demo, remove when working on your own project
  -D LV_USE_DEMO_WIDGETS=1
  -D LV_FONT_MONTSERRAT_26
  -D LV_FONT_MONTSERRAT_10
  ; Add more defines below to overide lvgl:/src/lv_conf_simple.h
lib_deps =
  ; Use direct URL, because package registry is unstable
  ;lvgl@~7.11.0
  lvgl=https://github.com/lvgl/lvgl/archive/refs/tags/v8.2.0.zip
lib_archive = false


[env:emulator_64bits]
platform = native@^1.1.3
extra_scripts = support/sdl2_build_extra.py
build_flags =
  ${env.build_flags}
  ; -D LV_LOG_LEVEL=LV_LOG_LEVEL_INFO
  -D LV_LOG_PRINTF=1
  ; Add recursive dirs for hal headers search
  !python -c "import os; print(' '.join(['-I {}'.format(i[0].replace('\x5C','/')) for i in os.walk('hal/sdl2')]))"
  -lSDL2
  ; SDL drivers options
  -D LV_LVGL_H_INCLUDE_SIMPLE
  -D LV_DRV_NO_CONF
  -D USE_SDL
  -D SDL_HOR_RES=240
  -D SDL_VER_RES=320  
  -D SDL_ZOOM=1
  -D SDL_INCLUDE_PATH="\"SDL2/SDL.h\""

  ; LVGL memory options, setup for the demo to run properly
  ; -D LV_MEM_CUSTOM=1
  -D LV_MEM_SIZE="(48U * 1024U)"
  
lib_deps =
  ${env.lib_deps}
  ; Use direct URL, because package registry is unstable
  ;lv_drivers@~7.9.0
  lv_drivers=https://github.com/lvgl/lv_drivers/archive/refs/tags/v8.3.0.zip
build_src_filter =
  +<*>
  +<../hal/sdl2>
  ; Force compile LVGL demo, remove when working on your own project
  +<../.pio/libdeps/emulator_64bits/lvgl/demos>


```

- 更改**main.c**为**main.cpp**
- 修改main.cpp文件如下
```sh
#include "lvgl.h"
#include "app_hal.h"
#include "App/App.h"
#include "demos/lv_demos.h"

int main(void)
{
	lv_init();

	hal_setup();

  // lv_demo_widgets();
  App_Init();
  

	hal_loop();
}
```

随后又编译即可



## 项目结构

- Pages: 页面文件
- App.cpp
- App.h
- Page.cpp: 页面管理框架实现
- Page.h

## 维护者

[@AaronChuzb](https://github.com/AaronChuzb)。

## 如何贡献

非常欢迎你的加入！[提一个 Issue](https://github.com/AaronChuzb/TD3-App/issues/new) 或者联系作者邮箱aaronchu_cn@163.com。


标准 Readme 遵循 [Contributor Covenant](http://contributor-covenant.org/version/1/3/0/) 行为规范。


## 使用许可

[MPL-2.0 License](LICENSE) © Aaron Chu