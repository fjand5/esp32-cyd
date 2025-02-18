#include "screenBai8.h"
#include "Arduino.h"
char buf[32]={0};
lv_obj_t *createScreenBai8()
{
  lv_obj_t *screen = lv_obj_create(nullptr);
  lv_obj_set_style_bg_color(screen, lv_color_white(), LV_PART_MAIN);

  lv_obj_t *label = lv_label_create(screen);
  lv_obj_set_width(label, 300);
  lv_obj_set_height(label, 50);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_46, LV_PART_MAIN);
  
  
  lv_label_set_long_mode(label, LV_LABEL_LONG_DOT);
  
  lv_label_set_text_static(label, buf);
  
  itoa(millis(),buf,10);
  lv_label_set_text_static(label, nullptr);

  return screen;
};
