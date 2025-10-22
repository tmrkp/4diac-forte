/**
 * @file belt_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "belt_gen.h"
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

lv_obj_t * belt_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    lv_obj_t * lv_obj_0 = lv_obj_create(parent);
    lv_obj_set_width(lv_obj_0, 420);
    lv_obj_set_height(lv_obj_0, 40);
    lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0xCBD2D9), 0);
    lv_obj_set_style_border_width(lv_obj_0, 0, 0);
    lv_obj_set_style_radius(lv_obj_0, lv_pct(100), 0);
    lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

    lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
    lv_obj_set_width(lv_obj_1, 32);
    lv_obj_set_height(lv_obj_1, 32);
    lv_obj_set_style_border_width(lv_obj_1, 0, 0);
    lv_obj_set_style_radius(lv_obj_1, lv_pct(100), 0);
    lv_obj_set_align(lv_obj_1, LV_ALIGN_LEFT_MID);
    lv_obj_set_x(lv_obj_1, 4);
    lv_obj_set_style_bg_color(lv_obj_1, lv_color_hex(0x3E4C59), 0);
    
    lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_0);
    lv_obj_set_width(lv_obj_2, 32);
    lv_obj_set_height(lv_obj_2, 32);
    lv_obj_set_style_border_width(lv_obj_2, 0, 0);
    lv_obj_set_style_radius(lv_obj_2, lv_pct(100), 0);
    lv_obj_set_align(lv_obj_2, LV_ALIGN_RIGHT_MID);
    lv_obj_set_x(lv_obj_2, -4);
    lv_obj_set_style_bg_color(lv_obj_2, lv_color_hex(0x3E4C59), 0);
    
    lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_0);
    lv_obj_set_width(lv_obj_3, 380);
    lv_obj_set_height(lv_obj_3, 2);
    lv_obj_set_style_border_width(lv_obj_3, 0, 0);
    lv_obj_set_style_bg_color(lv_obj_3, lv_color_hex(0x3E4C59), 0);
    lv_obj_set_style_radius(lv_obj_3, 0, 0);
    lv_obj_set_align(lv_obj_3, LV_ALIGN_TOP_MID);
    lv_obj_set_y(lv_obj_3, 4);
    
    lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_0);
    lv_obj_set_width(lv_obj_4, 380);
    lv_obj_set_height(lv_obj_4, 2);
    lv_obj_set_style_border_width(lv_obj_4, 0, 0);
    lv_obj_set_style_bg_color(lv_obj_4, lv_color_hex(0x3E4C59), 0);
    lv_obj_set_style_radius(lv_obj_4, 0, 0);
    lv_obj_set_align(lv_obj_4, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_y(lv_obj_4, -4);

    LV_TRACE_OBJ_CREATE("finished");

    lv_obj_set_name(lv_obj_0, "belt_#");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

