#include "../ui.h"

extern int HF_number;
extern int HF_current_temp;
extern uint8_t HF_open;

static lv_timer_t *control_timer = NULL;

static void control_update_cb(lv_timer_t *timer)
{
    (void)timer;

    if (!HF_open) {
        return;
    }

    if (HF_current_temp < HF_number) {
        HF_current_temp++;
    } else if (HF_current_temp > HF_number) {
        HF_current_temp--;
    }

    thermostat_refresh_working();
}

void ui_working_screen_init(void)
{
    ui_working = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_working, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_working, lv_color_hex(0x101820), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_working, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Spinner1 = lv_spinner_create(ui_working);
    lv_obj_set_size(ui_Spinner1, 430, 430);
    lv_obj_center(ui_Spinner1);
    lv_obj_remove_flag(ui_Spinner1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_color(ui_Spinner1, lv_color_hex(0x263745), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_Spinner1, lv_color_hex(0xF36C21), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_Spinner1, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_Spinner1, 18, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_Label2 = lv_label_create(ui_working);
    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label2, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_Label2, LV_ALIGN_TOP_MID, 0, 86);

    ui_Label3 = lv_label_create(ui_working);
    lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_Label3, LV_ALIGN_CENTER, 0, -20);

    ui_Bar1 = lv_bar_create(ui_working);
    lv_bar_set_range(ui_Bar1, 0, 100);
    lv_bar_set_value(ui_Bar1, 0, LV_ANIM_OFF);
    lv_obj_set_size(ui_Bar1, 250, 18);
    lv_obj_align(ui_Bar1, LV_ALIGN_CENTER, 0, 52);
    lv_obj_set_style_radius(ui_Bar1, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_Bar1, 9, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Bar1, lv_color_hex(0x263745), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Bar1, lv_color_hex(0xF36C21), LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_Button6 = lv_button_create(ui_working);
    lv_obj_set_size(ui_Button6, 136, 64);
    lv_obj_align(ui_Button6, LV_ALIGN_BOTTOM_MID, 0, -62);
    lv_obj_set_style_radius(ui_Button6, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Button6, lv_color_hex(0xF36C21), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Button6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label1 = lv_label_create(ui_Button6);
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_Label1);

    thermostat_refresh_working();

    if (control_timer == NULL) {
        control_timer = lv_timer_create(control_update_cb, 1200, NULL);
    }

    lv_obj_add_event_cb(ui_Button6, ui_event_Button6, LV_EVENT_ALL, NULL);
}
