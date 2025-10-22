/**
 * @file lvgl_editor_ui_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "lvgl_editor_ui_gen.h"

#if LV_USE_XML
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/*----------------
 * Translations
 *----------------*/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Global styles
 *----------------*/

lv_style_t btn;
lv_style_t light;
lv_style_t light_inactive;
lv_style_t light_active;

/*----------------
 * Fonts
 *----------------*/

/*----------------
 * Images
 *----------------*/

/*----------------
 * Subjects
 *----------------*/

lv_subject_t l1;
lv_subject_t l2;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lvgl_editor_ui_init_gen(const char * asset_path)
{
    char buf[256];

    /*----------------
     * Global styles
     *----------------*/

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&btn);
        lv_style_set_bg_color(&btn, lv_color_hex(0x2BB0ED));
        lv_style_set_shadow_color(&btn, lv_color_hex(0x127FBF));

        lv_style_init(&light);
        lv_style_set_width(&light, 14);
        lv_style_set_height(&light, 14);
        lv_style_set_radius(&light, 7);
        lv_style_set_border_width(&light, 0);
        lv_style_set_shadow_width(&light, 10);
        lv_style_set_shadow_opa(&light, 200);

        lv_style_init(&light_inactive);
        lv_style_set_bg_color(&light_inactive, lv_color_hex(0xE12D39));
        lv_style_set_shadow_color(&light_inactive, lv_color_hex(0xE12D39));

        lv_style_init(&light_active);
        lv_style_set_bg_color(&light_active, lv_color_hex(0x27AB83));
        lv_style_set_shadow_color(&light_active, lv_color_hex(0x27AB83));

        style_inited = true;
    }

    /*----------------
     * Fonts
     *----------------*/


    /*----------------
     * Images
     *----------------*/
    /*----------------
     * Subjects
     *----------------*/
    lv_subject_init_int(&l1, 0);
    lv_subject_init_int(&l2, 0);

    /*----------------
     * Translations
     *----------------*/

#if LV_USE_XML
    /* Register widgets */

    /* Register fonts */

    /* Register subjects */
    lv_xml_register_subject(NULL, "l1", &l1);
    lv_xml_register_subject(NULL, "l2", &l2);

    /* Register callbacks */
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
#endif

#if LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manaully from XML using lv_xml_create() */
#endif
}

/* Callbacks */

/**********************
 *   STATIC FUNCTIONS
 **********************/