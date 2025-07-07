/**
 * @file main_gen.c
 * @description Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/
#include "main_gen.h"
#include "ui.h"

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

lv_obj_t * main_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    static bool style_inited = false;

    if(!style_inited) {
        
        style_inited = true;
    }

    lv_obj_t * lv_obj_1 = lv_obj_create(NULL);
        lv_obj_set_width(lv_obj_1, lv_pct(100));
    lv_obj_set_height(lv_obj_1, lv_pct(100));
    lv_obj_set_style_layout(lv_obj_1, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_row(lv_obj_1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(lv_obj_1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(lv_obj_1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * button = lv_button_create(lv_obj_1);
    lv_obj_set_name(button, "button");

    lv_obj_t * lv_label_1 = lv_label_create(button);
    lv_label_set_text(lv_label_1, "Toggle Button");

    lv_obj_t * arc = lv_arc_create(lv_obj_1);
    lv_obj_set_name(arc, "arc");

    lv_obj_t * bar = lv_bar_create(lv_obj_1);
    lv_bar_set_mode(bar, LV_BAR_MODE_NORMAL);
    lv_obj_set_name(bar, "bar");

    lv_obj_t * checkbox = lv_checkbox_create(lv_obj_1);
    lv_checkbox_set_text(checkbox, "Checkbox");
    lv_obj_set_name(checkbox, "checkbox");


    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_1;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/