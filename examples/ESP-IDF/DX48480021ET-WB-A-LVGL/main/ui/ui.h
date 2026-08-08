// Simple thermostat UI for LVGL 9.1

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "components/ui_comp.h"
#include "components/ui_comp_hook.h"
#include "ui_events.h"

void ui_Screen1_screen_init(void);
extern lv_obj_t *ui_Screen1;
extern lv_obj_t *ui_Image1;
void ui_event_background(lv_event_t *e);
extern lv_obj_t *ui_background;
void ui_event_Button1(lv_event_t *e);
extern lv_obj_t *ui_Button1;
void ui_event_Button2(lv_event_t *e);
extern lv_obj_t *ui_Button2;
extern lv_obj_t *ui_LabelHomeTitle;
extern lv_obj_t *ui_LabelHomeCurrent;
extern lv_obj_t *ui_LabelHomeSet;
extern lv_obj_t *ui_LabelHomeMode;
extern lv_obj_t *ui_LabelHomeHint;
extern lv_obj_t *ui_LabelHomeAction;

void ui_time_screen_init(void);
void ui_event_time(lv_event_t *e);
extern lv_obj_t *ui_time;
extern lv_obj_t *ui_Roller1;
void ui_event_Button4(lv_event_t *e);
extern lv_obj_t *ui_Button4;
void ui_event_Button5(lv_event_t *e);
extern lv_obj_t *ui_Button5;
extern lv_obj_t *ui_Image3;
extern lv_obj_t *ui_Image4;

void ui_working_screen_init(void);
extern lv_obj_t *ui_working;
extern lv_obj_t *ui_Spinner1;
extern lv_obj_t *ui_Bar1;
void ui_event_Button6(lv_event_t *e);
extern lv_obj_t *ui_Button6;
extern lv_obj_t *ui_Label1;
extern lv_obj_t *ui_Label2;
extern lv_obj_t *ui_Label3;

extern lv_obj_t *ui____initial_actions0;

LV_IMG_DECLARE(ui_img_back480_png);
LV_IMG_DECLARE(ui_img_1kaorou_png);
LV_IMG_DECLARE(ui_img_6shutiao_png);
LV_IMG_DECLARE(ui_img_5liupai_png);
LV_IMG_DECLARE(ui_img_4pisa_png);
LV_IMG_DECLARE(ui_img_3danta_png);
LV_IMG_DECLARE(ui_img_2kaoji_png);
LV_IMG_DECLARE(ui_img_start_png);
LV_IMG_DECLARE(ui_img_1522004715);
LV_IMG_DECLARE(ui_img_362584155);
LV_IMG_DECLARE(ui_img_174066631);
LV_IMG_DECLARE(ui_img_min_png);
LV_IMG_DECLARE(ui_img_1620963198);

void LVGL_knob_event(void *event);
void LVGL_button_event(void *event);
void thermostat_refresh_home(void);
void thermostat_refresh_working(void);
void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
