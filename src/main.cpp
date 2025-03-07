/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/integration/framework/arduino.html  */
// These are the default min and maximum values, set to 0 and 4095 to test the screen
#define HMIN 534
#define HMAX 3496
#define VMIN 635
#define VMAX 3395
#define XYSWAP 1 // 0 or 1

#include <lvgl.h>
#include <XPT2046_Touchscreen.h>
#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif
#include "screens/screenBai10.h"
/*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 *Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
 *as the examples and demos are now part of the main LVGL library. */

// #include <examples/lv_examples.h>
// #include <demos/lv_demos.h>

/*Set to your screen resolution and rotation*/

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

SPIClass touchscreenSpi = SPIClass(HSPI);
XPT2046_Touchscreen touchScreen(XPT2046_CS, XPT2046_IRQ); // Param 2 - Touch IRQ Pin - interrupt enabled polling

#if LV_USE_LOG != 0
void my_print(lv_log_level_t level, const char *buf)
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}
#endif

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    /*Copy `px map` to the `area`*/

    /*For example ("my_..." functions needs to be implemented by you)
    uint32_t w = lv_area_get_width(area);
    uint32_t h = lv_area_get_height(area);

    my_set_window(area->x1, area->y1, w, h);
    my_draw_bitmaps(px_map, w * h);
     */

    /*Call it to tell LVGL you are ready*/
    lv_display_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    int32_t x, y;
    bool touched = touchScreen.touched();
    x = touchScreen.getPoint().x;
    y = touchScreen.getPoint().y;
    if (!touched)
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
    else
    {
        data->state = LV_INDEV_STATE_PRESSED;

        data->point.x = map(x, 350, 3800, 1, TFT_WIDTH); /* Touchscreen X calibration */
        data->point.y = map(y, 260, 3800, 1, TFT_HEIGHT); /* Touchscreen Y calibration */
        // Serial.printf("X: %d, Y: %d\n", x, y);
    }
}

/*use Arduinos millis() as tick source*/
static uint32_t my_tick(void)
{
    return millis();
}

void setup()
{
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.begin(115200);
    Serial.println(LVGL_Arduino);
    touchscreenSpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchScreen.begin(touchscreenSpi);
    touchScreen.setRotation(0);
    lv_init();

    /*Set a tick source so that LVGL will know how much time elapsed. */
    lv_tick_set_cb(my_tick);

    /* register print function for debugging */
#if LV_USE_LOG != 0
    lv_log_register_print_cb(my_print);
#endif

    lv_display_t *disp;
#if LV_USE_TFT_ESPI
    /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
    disp = lv_tft_espi_create(TFT_WIDTH, TFT_HEIGHT, draw_buf, sizeof(draw_buf));
    // lv_display_set_rotation(disp, TFT_ROTATION);

#else
    /*Else create a display yourself*/
    disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
#endif

    /*Initialize the (dummy) input device driver*/
    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
    lv_indev_set_read_cb(indev, my_touchpad_read);

    /* Create a simple label
     * ---------------------
     lv_obj_t *label = lv_label_create( lv_screen_active() );
     lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
     lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );

     * Try an example. See all the examples
     *  - Online: https://docs.lvgl.io/master/examples.html
     *  - Source codes: https://github.com/lvgl/lvgl/tree/master/examples
     * ----------------------------------------------------------------

     lv_example_btn_1();

     * Or try out a demo. Don't forget to enable the demos in lv_conf.h. E.g. LV_USE_DEMO_WIDGETS
     * -------------------------------------------------------------------------------------------

     lv_demo_widgets();
     */

    lv_obj_t *screen = createScreenBai10();
    lv_screen_load(screen);

//     lv_obj_set_style_bg_color(screen1, lv_color_make(255, 0, 0), LV_PART_MAIN);
//     lv_obj_set_style_bg_color(screen2, lv_color_make(0, 255, 0), LV_PART_MAIN);

//     lv_screen_load(screen1);

    
//     // lv_obj_add_event(
//     //     screen2,
//     //     [](lv_event_t *e)
//     //     {
//     //         lv_screen_load_anim((lv_obj_t*)lv_event_get_user_data(e), LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 1000, 100, false);
//     //     },
//     //     LV_EVENT_CLICKED, screen1);

//     lv_obj_t *button = lv_button_create(screen);
//     lv_obj_align(button, LV_ALIGN_BOTTOM_RIGHT, 0, 0);

//     lv_obj_t *label = lv_label_create(button);
//     lv_label_set_text(label, "Button");
//     lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
// lv_obj_add_event(
//         button,
//         [](lv_event_t *e)
//         {
//             Serial.println("click");
//         },
//         LV_EVENT_CLICKED, nullptr);
    Serial.println("Setup done");
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);           /* let this time pass */
}
