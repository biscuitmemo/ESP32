// Simple thermostat UI for LVGL 9.1

#include "ui.h"

#include <stdint.h>
#include "iot_knob.h"
#include "iot_button.h"

uint8_t HF_ui_screen_id = 1;
uint8_t HF_open = 0;

int selected_index = 8;
int options_max_num = 14;
char *options[] = {
    "16 C", "17 C", "18 C", "19 C", "20 C", "21 C", "22 C", "23 C",
    "24 C", "25 C", "26 C", "27 C", "28 C", "29 C", "30 C"
};
int options2[] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

int HF_number = 24;
int HF_current_temp = 22;

lv_obj_t *ui_Screen1 = NULL;
lv_obj_t *ui_Image1 = NULL;
lv_obj_t *ui_background = NULL;
lv_obj_t *ui_Button1 = NULL;
lv_obj_t *ui_Button2 = NULL;
lv_obj_t *ui_LabelHomeTitle = NULL;
lv_obj_t *ui_LabelHomeCurrent = NULL;
lv_obj_t *ui_LabelHomeSet = NULL;
lv_obj_t *ui_LabelHomeMode = NULL;
lv_obj_t *ui_LabelHomeHint = NULL;
lv_obj_t *ui_LabelHomeAction = NULL;

lv_obj_t *ui_time = NULL;
lv_obj_t *ui_Roller1 = NULL;
lv_obj_t *ui_Button4 = NULL;
lv_obj_t *ui_Button5 = NULL;
lv_obj_t *ui_Image3 = NULL;
lv_obj_t *ui_Image4 = NULL;

lv_obj_t *ui_working = NULL;
lv_obj_t *ui_Spinner1 = NULL;
lv_obj_t *ui_Bar1 = NULL;
lv_obj_t *ui_Button6 = NULL;
lv_obj_t *ui_Label1 = NULL;
lv_obj_t *ui_Label2 = NULL;
lv_obj_t *ui_Label3 = NULL;

lv_obj_t *ui____initial_actions0 = NULL;

static void load_screen(lv_obj_t **screen, void (*init_cb)(void), uint8_t screen_id)
{
    HF_ui_screen_id = screen_id;
    _ui_screen_change(screen, LV_SCR_LOAD_ANIM_FADE_ON, 80, 0, init_cb);
}

static void sync_selected_index(void)
{
    if (HF_number < 16) HF_number = 16;
    if (HF_number > 30) HF_number = 30;
    selected_index = HF_number - 16;
}

void thermostat_refresh_home(void)
{
    if (!ui_LabelHomeSet || !ui_LabelHomeCurrent || !ui_LabelHomeMode) {
        return;
    }

    lv_label_set_text_fmt(ui_LabelHomeSet, "%d C", HF_number);
    lv_label_set_text_fmt(ui_LabelHomeCurrent, "%d C", HF_current_temp);
    lv_label_set_text(ui_LabelHomeMode, HF_open ? "RUNNING" : "STANDBY");
    if (ui_LabelHomeAction) {
        lv_label_set_text(ui_LabelHomeAction, HF_open ? "Stop" : "Start");
        lv_obj_center(ui_LabelHomeAction);
    }
}

void thermostat_refresh_working(void)
{
    if (!ui_Label1 || !ui_Label2 || !ui_Label3 || !ui_Bar1) {
        return;
    }

    int delta = HF_number - HF_current_temp;
    int power = delta <= 0 ? 0 : delta * 18;
    if (power > 100) power = 100;

    lv_label_set_text(ui_Label1, "Stop");
    lv_label_set_text(ui_Label2, delta > 0 ? "Heating" : "Holding");
    lv_label_set_text_fmt(ui_Label3, "%d C / %d C", HF_current_temp, HF_number);
    lv_bar_set_value(ui_Bar1, power, LV_ANIM_ON);
}

void LVGL_knob_event(void *event)
{
    uintptr_t event_code = (uintptr_t)event;

    if (HF_ui_screen_id == 2) {
        if (event_code == KNOB_LEFT && selected_index < options_max_num) {
            selected_index++;
        } else if (event_code == KNOB_RIGHT && selected_index > 0) {
            selected_index--;
        }

        if (ui_Roller1) {
            lv_roller_set_selected(ui_Roller1, selected_index, LV_ANIM_ON);
        }
        HF_number = options2[selected_index];
        return;
    }

    if (event_code == KNOB_LEFT && HF_number < 30) {
        HF_number++;
    } else if (event_code == KNOB_RIGHT && HF_number > 16) {
        HF_number--;
    }

    sync_selected_index();

    if (HF_ui_screen_id == 1) {
        thermostat_refresh_home();
    } else if (HF_ui_screen_id == 3) {
        thermostat_refresh_working();
    }
}

void LVGL_button_event(void *event)
{
    uintptr_t event_code = (uintptr_t)event;
    static uint8_t was_long_press = 0;

    if (event_code == BUTTON_LONG_PRESS_HOLD) {
        if (HF_ui_screen_id != 2) {
            sync_selected_index();
            if (ui_Roller1) {
                lv_roller_set_selected(ui_Roller1, selected_index, LV_ANIM_OFF);
            }
            load_screen(&ui_time, ui_time_screen_init, 2);
        }
        was_long_press = 1;
        return;
    }

    if (event_code != BUTTON_PRESS_UP) {
        return;
    }

    if (was_long_press) {
        was_long_press = 0;
        return;
    }

    if (HF_ui_screen_id == 2) {
        selected_index = lv_roller_get_selected(ui_Roller1);
        HF_number = options2[selected_index];
        thermostat_refresh_home();
        load_screen(&ui_Screen1, ui_Screen1_screen_init, 1);
        return;
    }

    HF_open = !HF_open;
    if (HF_open) {
        load_screen(&ui_working, ui_working_screen_init, 3);
    } else {
        thermostat_refresh_home();
        load_screen(&ui_Screen1, ui_Screen1_screen_init, 1);
    }
}

void ui_event_background(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        HF_open = !HF_open;
        if (HF_open) {
            load_screen(&ui_working, ui_working_screen_init, 3);
        } else {
            thermostat_refresh_home();
        }
    }
}

void ui_event_Button1(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        HF_open = 1;
        load_screen(&ui_working, ui_working_screen_init, 3);
    }
}

void ui_event_Button2(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        sync_selected_index();
        if (ui_Roller1) {
            lv_roller_set_selected(ui_Roller1, selected_index, LV_ANIM_OFF);
        }
        load_screen(&ui_time, ui_time_screen_init, 2);
    }
}

void ui_event_time(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        thermostat_refresh_home();
        load_screen(&ui_Screen1, ui_Screen1_screen_init, 1);
    }
}

void ui_event_Button4(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        thermostat_refresh_home();
        load_screen(&ui_Screen1, ui_Screen1_screen_init, 1);
    }
}

void ui_event_Button5(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        selected_index = lv_roller_get_selected(ui_Roller1);
        HF_number = options2[selected_index];
        thermostat_refresh_home();
        load_screen(&ui_Screen1, ui_Screen1_screen_init, 1);
    }
}

void ui_event_Button6(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        HF_open = 0;
        thermostat_refresh_home();
        load_screen(&ui_Screen1, ui_Screen1_screen_init, 1);
    }
}

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(
        dispp,
        lv_palette_main(LV_PALETTE_ORANGE),
        lv_palette_main(LV_PALETTE_BLUE),
        true,
        LV_FONT_DEFAULT
    );
    lv_disp_set_theme(dispp, theme);

    ui_Screen1_screen_init();
    ui_time_screen_init();
    ui_working_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}
