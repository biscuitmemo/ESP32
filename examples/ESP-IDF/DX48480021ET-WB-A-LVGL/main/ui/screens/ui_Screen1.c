#include "../ui.h"

extern uint8_t HF_open;

static lv_obj_t *create_text_button(lv_obj_t *parent, const char *text, int x_offset, lv_obj_t **label_out)
{
    lv_obj_t *button = lv_button_create(parent);
    lv_obj_set_size(button, 132, 64);
    lv_obj_align(button, LV_ALIGN_BOTTOM_MID, x_offset, -58);
    lv_obj_set_style_radius(button, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(button, lv_color_hex(0xF36C21), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label = lv_label_create(button);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(label);
    if (label_out) *label_out = label;

    return button;
}

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x101820), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_background = lv_obj_create(ui_Screen1);
    lv_obj_set_size(ui_background, 420, 420);
    lv_obj_center(ui_background);
    lv_obj_add_flag(ui_background, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_remove_flag(ui_background, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_background, 210, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_background, lv_color_hex(0x17232E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_background, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_background, lv_color_hex(0xF36C21), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelHomeTitle = lv_label_create(ui_Screen1);
    lv_label_set_text(ui_LabelHomeTitle, "Thermostat");
    lv_obj_set_style_text_color(ui_LabelHomeTitle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelHomeTitle, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_LabelHomeTitle, LV_ALIGN_TOP_MID, 0, 58);

    lv_obj_t *current_caption = lv_label_create(ui_Screen1);
    lv_label_set_text(current_caption, "Current");
    lv_obj_set_style_text_color(current_caption, lv_color_hex(0x9AA7B2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(current_caption, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(current_caption, LV_ALIGN_CENTER, 0, -105);

    ui_LabelHomeCurrent = lv_label_create(ui_Screen1);
    lv_obj_set_style_text_color(ui_LabelHomeCurrent, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelHomeCurrent, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_LabelHomeCurrent, LV_ALIGN_CENTER, 0, -60);

    lv_obj_t *set_caption = lv_label_create(ui_Screen1);
    lv_label_set_text(set_caption, "Target");
    lv_obj_set_style_text_color(set_caption, lv_color_hex(0x9AA7B2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(set_caption, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(set_caption, LV_ALIGN_CENTER, 0, 10);

    ui_LabelHomeSet = lv_label_create(ui_Screen1);
    lv_obj_set_style_text_color(ui_LabelHomeSet, lv_color_hex(0xF36C21), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelHomeSet, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_LabelHomeSet, LV_ALIGN_CENTER, 0, 58);

    ui_LabelHomeMode = lv_label_create(ui_Screen1);
    lv_obj_set_style_text_color(ui_LabelHomeMode, lv_color_hex(0x7EE787), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelHomeMode, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_LabelHomeMode, LV_ALIGN_CENTER, 0, 116);

    ui_Button2 = create_text_button(ui_Screen1, "Set", -78, NULL);
    ui_Button1 = create_text_button(ui_Screen1, HF_open ? "Stop" : "Start", 78, &ui_LabelHomeAction);

    ui_LabelHomeHint = lv_label_create(ui_Screen1);
    lv_label_set_text(ui_LabelHomeHint, "Knob: adjust   Press: start/stop");
    lv_obj_set_style_text_color(ui_LabelHomeHint, lv_color_hex(0x9AA7B2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelHomeHint, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_LabelHomeHint, LV_ALIGN_BOTTOM_MID, 0, -28);

    ui_Image1 = NULL;
    thermostat_refresh_home();

    lv_obj_add_event_cb(ui_background, ui_event_background, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button1, ui_event_Button1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button2, ui_event_Button2, LV_EVENT_ALL, NULL);
}
