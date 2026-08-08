// Simple thermostat UI for the ESP32-S3 round display.

#include "ui.h"

#include <stdint.h>

typedef enum {
    KNOB_LEFT = 0,
    KNOB_RIGHT,
} knob_event_t;

typedef enum {
    BUTTON_SINGLE_CLICK = 4,
    BUTTON_LONG_PRESS_START = 7,
} button_event_t;

uint8_t HF_ui_screen_id = 1;
uint8_t HF_open = 0;

int selected_index = 8;
int options_max_num = 14;
char *options[] = {
    "16", "17", "18", "19", "20", "21", "22", "23",
    "24", "25", "26", "27", "28", "29", "30"
};
int options2[] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

int HF_number = 24;
int HF_current_temp = 22;

static void load_screen(lv_obj_t **screen, void (*init_cb)(void), uint8_t screen_id)
{
    HF_ui_screen_id = screen_id;
    _ui_screen_change(screen, LV_SCR_LOAD_ANIM_FADE_ON, 80, 0, init_cb);
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
    if (power > 100) {
        power = 100;
    }

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

        lv_roller_set_selected(ui_Roller1, selected_index, LV_ANIM_ON);
        HF_number = options2[selected_index];
        return;
    }

    if (event_code == KNOB_LEFT && HF_number < 30) {
        HF_number++;
    } else if (event_code == KNOB_RIGHT && HF_number > 16) {
        HF_number--;
    }

    selected_index = HF_number - 16;

    if (HF_ui_screen_id == 1) {
        thermostat_refresh_home();
    } else if (HF_ui_screen_id == 3) {
        thermostat_refresh_working();
    }
}

void LVGL_button_event(void *event)
{
    uintptr_t event_code = (uintptr_t)event;

    if (event_code == BUTTON_LONG_PRESS_START) {
        selected_index = HF_number - 16;
        if (ui_Roller1) {
            lv_roller_set_selected(ui_Roller1, selected_index, LV_ANIM_OFF);
        }
        load_screen(&ui_time, ui_time_screen_init, 2);
        return;
    }

    if (event_code != BUTTON_SINGLE_CLICK) {
        return;
    }

    if (HF_ui_screen_id == 2) {
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
        selected_index = HF_number - 16;
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
    lv_disp_t *dispp = lv_disp_get_default();
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
