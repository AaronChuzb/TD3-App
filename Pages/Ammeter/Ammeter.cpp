/*
 * @Date: 2023-04-13 17:27:57
 * @LastEditors: AaronChu
 * @LastEditTime: 2023-07-24 17:58:31
 */
#include "Ammeter.h"

Page::PageType Ammeter;
Page *Ammeter_Manager;

static lv_obj_t *chart1;
static lv_chart_series_t *ser1;
static lv_chart_series_t *ser2;
double num = 0.0;

static void event_btn1_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e); // 获取回调事件
  if (code == LV_EVENT_CLICKED)
  { // 点击事件
    // Ammeter_Manager->Page_Back(1);
    lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 5);
  }
}

static void event_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);
  if (code == LV_EVENT_VALUE_CHANGED)
  {
    char buf[32];
    lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
    if (strcmp(buf, "0-10") == 0)
    {
      lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 10);
    }
    else if (strcmp(buf, "0-20") == 0)
    {
      lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 20);
    }
    else if (strcmp(buf, "0-100") == 0)
    {
      lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    }
    LV_LOG_USER("Option: %s", buf);
  }
}

/**
 * Create a menu from a drop-down list and show some drop-down list features and styling
 */
void lv_example_dropdown_3(void)
{
  /*Create a normal drop down list*/
  lv_obj_t *dropdown = lv_dropdown_create(Ammeter.PageContent);
  lv_dropdown_set_options(dropdown, "0-10\n"
                                    "0-20\n"
                                    "0-100");

  lv_obj_align(dropdown, LV_ALIGN_TOP_LEFT, 5, 25);
  lv_obj_add_event_cb(dropdown, event_handler, LV_EVENT_ALL, NULL);
  lv_dropdown_set_dir(dropdown, LV_DIR_RIGHT);
  lv_dropdown_set_symbol(dropdown, LV_SYMBOL_RIGHT);
}

static void draw_event_cb(lv_event_t *e)
{
  lv_obj_t *obj = lv_event_get_target(e);

  /*Add the faded area before the lines are drawn*/
  lv_obj_draw_part_dsc_t *dsc = lv_event_get_draw_part_dsc(e);
  if (dsc->part == LV_PART_ITEMS)
  {
    if (!dsc->p1 || !dsc->p2)
      return;

    /*Add a line mask that keeps the area below the line*/
    lv_draw_mask_line_param_t line_mask_param;
    lv_draw_mask_line_points_init(&line_mask_param, dsc->p1->x, dsc->p1->y, dsc->p2->x, dsc->p2->y, LV_DRAW_MASK_LINE_SIDE_BOTTOM);
    int16_t line_mask_id = lv_draw_mask_add(&line_mask_param, NULL);

    /*Add a fade effect: transparent bottom covering top*/
    lv_coord_t h = lv_obj_get_height(obj);
    lv_draw_mask_fade_param_t fade_mask_param;
    lv_draw_mask_fade_init(&fade_mask_param, &obj->coords, LV_OPA_COVER, obj->coords.y1 + h / 8, LV_OPA_TRANSP, obj->coords.y2);
    int16_t fade_mask_id = lv_draw_mask_add(&fade_mask_param, NULL);

    /*Draw a rectangle that will be affected by the mask*/
    lv_draw_rect_dsc_t draw_rect_dsc;
    lv_draw_rect_dsc_init(&draw_rect_dsc);
    draw_rect_dsc.bg_opa = LV_OPA_20;
    draw_rect_dsc.bg_color = dsc->line_dsc->color;

    lv_area_t a;
    a.x1 = dsc->p1->x;
    a.x2 = dsc->p2->x - 1;
    a.y1 = LV_MIN(dsc->p1->y, dsc->p2->y);
    a.y2 = obj->coords.y2;
    lv_draw_rect(dsc->draw_ctx, &draw_rect_dsc, &a);

    /*Remove the masks*/
    lv_draw_mask_free_param(&line_mask_param);
    lv_draw_mask_free_param(&fade_mask_param);
    lv_draw_mask_remove_id(line_mask_id);
    lv_draw_mask_remove_id(fade_mask_id);
  }
  /*Hook the division lines too*/
  else if (dsc->part == LV_PART_MAIN)
  {
    if (dsc->line_dsc == NULL || dsc->p1 == NULL || dsc->p2 == NULL)
      return;

    /*Vertical line*/
    if (dsc->p1->x == dsc->p2->x)
    {
      dsc->line_dsc->color = lv_palette_lighten(LV_PALETTE_GREY, 1);
      if (dsc->id == 3)
      {
        dsc->line_dsc->width = 2;
        dsc->line_dsc->dash_gap = 0;
        dsc->line_dsc->dash_width = 0;
      }
      else
      {
        dsc->line_dsc->width = 1;
        dsc->line_dsc->dash_gap = 6;
        dsc->line_dsc->dash_width = 6;
      }
    }
    /*Horizontal line*/
    else
    {
      if (dsc->id == 2)
      {
        dsc->line_dsc->width = 2;
        dsc->line_dsc->dash_gap = 0;
        dsc->line_dsc->dash_width = 0;
      }
      else
      {
        dsc->line_dsc->width = 2;
        dsc->line_dsc->dash_gap = 6;
        dsc->line_dsc->dash_width = 6;
      }

      if (dsc->id == 1 || dsc->id == 3)
      {
        dsc->line_dsc->color = lv_palette_main(LV_PALETTE_GREEN);
      }
      else
      {
        dsc->line_dsc->color = lv_palette_lighten(LV_PALETTE_GREY, 1);
      }
    }
  }
}

static void add_data(lv_timer_t *timer)
{
  LV_UNUSED(timer);
  static uint32_t cnt = 0;
  lv_chart_set_next_value(chart1, ser1, lv_rand(20, 90));

  // if (cnt % 4 == 0)
  //   lv_chart_set_next_value(chart1, ser2, lv_rand(40, 60));
  num = double(cnt);

  cnt++;
}

/**
 * Add a faded area effect to the line chart and make some division lines ticker
 */
void lv_example_chart_2(void)
{
  /*Create a chart1*/
  chart1 = lv_chart_create(Ammeter.PageContent);
  lv_obj_set_size(chart1, 180, 150);
  // lv_obj_center(chart1);
  lv_chart_set_type(chart1, LV_CHART_TYPE_LINE); /*Show lines and points too*/
  lv_obj_align(chart1, LV_ALIGN_CENTER, 10, -20);
  lv_chart_set_div_line_count(chart1, 5, 7);

  lv_chart_set_axis_tick(chart1, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 1, true, 60);
  lv_chart_set_axis_tick(chart1, LV_CHART_AXIS_PRIMARY_X, 10, 5, 10, 1, true, 10);

  lv_obj_add_event_cb(chart1, draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
  lv_chart_set_update_mode(chart1, LV_CHART_UPDATE_MODE_SHIFT);
  lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 10);
  // lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_X, 0, 30);
  lv_chart_set_point_count(chart1, 20);

  /*Add two data series*/
  ser1 = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
  // ser2 = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_SECONDARY_Y);

  uint32_t i;
  for (i = 0; i < 10; i++)
  {
    lv_chart_set_next_value(chart1, ser1, lv_rand(20, 90));
    // lv_chart_set_next_value(chart1, ser2, lv_rand(30, 70));
  }

  lv_timer_create(add_data, 200, NULL);
}

static void Created()
{
  lv_example_dropdown_3();
  lv_example_chart_2();
  // lv_obj_t *btn1 = lv_btn_create(Ammeter.PageContent);               /*创建btn1*/
  // lv_obj_add_event_cb(btn1, event_btn1_handler, LV_EVENT_ALL, NULL); /*设置btn1回调函数*/
  // lv_obj_set_pos(btn1, 30, 40);

  // lv_obj_t *label = lv_label_create(btn1); /*btn1内创建label*/
  // lv_label_set_text(label, "change");
  lv_obj_t *label = lv_label_create(Ammeter.PageContent); /*btn1内创建label*/
  // lv_label_set_text(label, String(num).c_str());
}

// String a;

static void Update(void)
{
}

static void Destroy(void)
{
}

static void Method(void *btn, int event)
{
}

void Ammeter_Init(Page *PageManager)
{
  strcpy(Ammeter.name, "Ammeter");
  Ammeter.show_status_bar = true;
  Ammeter.BeforeEnter = NULL;
  Ammeter.Created = Created;
  Ammeter.Update = Update;
  Ammeter.Destroy = Destroy;
  Ammeter.Method = Method;
  Ammeter.PageContent = PageManager->create_new_screen();
  Ammeter_Manager = PageManager;
  Ammeter_Manager->Page_Register(Ammeter);
}