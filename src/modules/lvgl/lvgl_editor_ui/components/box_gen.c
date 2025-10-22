/**
 * @file box_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "box_gen.h"
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

lv_obj_t * box_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    lv_obj_t * lv_obj_0 = lv_obj_create(parent);
    lv_obj_set_width(lv_obj_0, 90);
    lv_obj_set_height(lv_obj_0, 90);
    lv_obj_set_style_border_color(lv_obj_0, lv_color_hex(0x0B69A3), 0);
    lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x40C3F7), 0);
    lv_obj_set_style_border_width(lv_obj_0, 12, 0);
    lv_obj_set_style_radius(lv_obj_0, 16, 0);

    LV_TRACE_OBJ_CREATE("finished");

    lv_obj_set_name(lv_obj_0, "box_#");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

