/**
 * @file demo1_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "demo1_gen.h"
#include "lvgl_editor_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * demo1_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    static bool style_inited = false;

    if (!style_inited) {

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0xF5F7FA), 0);

    lv_obj_t * box_0 = box_create(lv_obj_0);
    lv_obj_set_align(box_0, LV_ALIGN_TOP_MID);
    lv_obj_set_y(box_0, 170);
    lv_obj_set_x(box_0, -100);
    lv_obj_bind_flag_if_not_eq(box_0, &l1, LV_OBJ_FLAG_HIDDEN, 1);
    
    lv_obj_t * box_1 = box_create(lv_obj_0);
    lv_obj_set_align(box_1, LV_ALIGN_TOP_MID);
    lv_obj_set_y(box_1, 170);
    lv_obj_set_x(box_1, 100);
    lv_obj_bind_flag_if_not_eq(box_1, &l2, LV_OBJ_FLAG_HIDDEN, 1);
    
    lv_obj_t * belt_0 = belt_create(lv_obj_0);
    lv_obj_set_align(belt_0, LV_ALIGN_TOP_MID);
    lv_obj_set_y(belt_0, 260);
    
    lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
    lv_obj_set_align(lv_obj_1, LV_ALIGN_TOP_MID);
    lv_obj_set_y(lv_obj_1, 220);
    lv_obj_set_x(lv_obj_1, -120);
    lv_obj_add_style(lv_obj_1, &light, 0);
    lv_obj_bind_style(lv_obj_1, &light_active, 0, &l1, 1);
    lv_obj_bind_style(lv_obj_1, &light_inactive, 0, &l1, 0);
    
    lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_0);
    lv_obj_set_align(lv_obj_2, LV_ALIGN_TOP_MID);
    lv_obj_set_y(lv_obj_2, 220);
    lv_obj_set_x(lv_obj_2, 120);
    lv_obj_add_style(lv_obj_2, &light, 0);
    lv_obj_bind_style(lv_obj_2, &light_active, 0, &l2, 1);
    lv_obj_bind_style(lv_obj_2, &light_inactive, 0, &l2, 0);
    
    lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_0);
    lv_obj_set_style_bg_color(lv_obj_3, lv_color_hex(0xE4E7EB), 0);
    lv_obj_set_style_border_color(lv_obj_3, lv_color_hex(0xCBD2D9), 0);
    lv_obj_set_style_border_width(lv_obj_3, 4, 0);
    lv_obj_set_style_border_side(lv_obj_3, LV_BORDER_SIDE_TOP, 0);
    lv_obj_set_style_radius(lv_obj_3, 0, 0);
    lv_obj_set_width(lv_obj_3, lv_pct(100));
    lv_obj_set_height(lv_obj_3, LV_SIZE_CONTENT);
    lv_obj_set_align(lv_obj_3, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_layout(lv_obj_3, LV_LAYOUT_FLEX, 0);
    lv_obj_set_style_pad_top(lv_obj_3, 20, 0);
    lv_obj_set_style_pad_bottom(lv_obj_3, 30, 0);
    lv_obj_set_style_pad_hor(lv_obj_3, 20, 0);
    lv_obj_set_style_flex_main_place(lv_obj_3, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
    lv_obj_t * move_left_btn = lv_button_create(lv_obj_3);
    lv_obj_set_name(move_left_btn, "move_left_btn");
    lv_obj_add_style(move_left_btn, &btn, 0);
    lv_obj_t * lv_label_0 = lv_label_create(move_left_btn);
    lv_label_set_text(lv_label_0, "Move Left");
    
    lv_obj_t * move_right_btn = lv_button_create(lv_obj_3);
    lv_obj_set_name(move_right_btn, "move_right_btn");
    lv_obj_add_style(move_right_btn, &btn, 0);
    lv_obj_t * lv_label_1 = lv_label_create(move_right_btn);
    lv_label_set_text(lv_label_1, "Move Right");

    LV_TRACE_OBJ_CREATE("finished");

    lv_obj_set_name(lv_obj_0, "demo1");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

