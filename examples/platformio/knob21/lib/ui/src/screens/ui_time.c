#include "../ui.h"

extern int selected_index;
extern int HF_number;

lv_obj_t *ui_time;
lv_obj_t *ui_Roller1;
lv_obj_t *ui_Button4;
lv_obj_t *ui_Button5;
lv_obj_t *ui_Image3;
lv_obj_t *ui_Image4;

static lv_obj_t *create_text_button(lv_obj_t *parent, const char *text, int x_offset)
{
    lv_obj_t *button = lv_btn_create(parent);
    lv_obj_set_size(button, 132, 58);
    lv_obj_align(button, LV_ALIGN_BOTTOM_MID, x_offset, -60);
    lv_obj_set_style_radius(button, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(button, lv_color_hex(0xF36C21), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label = lv_label_create(button);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(label);

    return button;
}

void ui_time_screen_init(void)
{
    ui_time = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_time, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_time, lv_color_hex(0x101820), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_time, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *title = lv_label_create(ui_time);
    lv_label_set_text(title, "Set Target");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 62);

    ui_Roller1 = lv_roller_create(ui_time);
    lv_roller_set_options(
        ui_Roller1,
        "16 C\n17 C\n18 C\n19 C\n20 C\n21 C\n22 C\n23 C\n24 C\n25 C\n26 C\n27 C\n28 C\n29 C\n30 C",
        LV_ROLLER_MODE_INFINITE
    );
    lv_roller_set_visible_row_count(ui_Roller1, 3);
    lv_roller_set_selected(ui_Roller1, selected_index, LV_ANIM_OFF);
    lv_obj_set_size(ui_Roller1, 180, 176);
    lv_obj_align(ui_Roller1, LV_ALIGN_CENTER, 0, -6);
    lv_obj_set_style_text_color(ui_Roller1, lv_color_hex(0xCAD3DD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Roller1, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Roller1, lv_color_hex(0x17232E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Roller1, lv_color_hex(0xF36C21), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Roller1, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);

    lv_obj_t *hint = lv_label_create(ui_time);
    lv_label_set_text(hint, "Rotate knob, then press OK");
    lv_obj_set_style_text_color(hint, lv_color_hex(0x9AA7B2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(hint, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(hint, LV_ALIGN_CENTER, 0, 120);

    ui_Button4 = create_text_button(ui_time, "Back", -78);
    ui_Button5 = create_text_button(ui_time, "OK", 78);

    ui_Image3 = NULL;
    ui_Image4 = NULL;
    (void)HF_number;

    lv_obj_add_event_cb(ui_Button4, ui_event_Button4, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button5, ui_event_Button5, LV_EVENT_ALL, NULL);
}
