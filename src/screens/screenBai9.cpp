#include "screenBai9.h"
#include "Arduino.h"
#include "Fonts/fonts.h"
static char buf[32]={0};
lv_obj_t *createScreenBai9()
{
  lv_obj_t *screen = lv_obj_create(nullptr);
  lv_obj_set_style_bg_color(screen, lv_color_white(), LV_PART_MAIN);

  lv_obj_t *label = lv_label_create(screen);
  lv_obj_set_width(label, 300);
  lv_obj_set_height(label, 50);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_font(label, &Nunito_Bold_24, LV_PART_MAIN);
  
  
  lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  
  lv_label_set_text(label,"Hãy giữ gìn sự trong sáng của Tiếng Việt");

  return screen;
};
