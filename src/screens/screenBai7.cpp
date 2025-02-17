#include "screenBai6.h"
#include "Arduino.h"
lv_obj_t *createScreenBai7()
{
  lv_obj_t *screen = lv_obj_create(nullptr);
  lv_obj_set_style_bg_color(screen, lv_color_make(0, 0, 0), LV_PART_MAIN);

  lv_obj_t *buttonParent = lv_button_create(screen);
  Serial.printf("buttonParent: %p \n", buttonParent);

  lv_obj_set_size(buttonParent, lv_pct(80), lv_pct(80));
  lv_obj_align(buttonParent, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_bg_color(buttonParent, lv_color_make(255, 0, 0), LV_PART_MAIN);

  lv_obj_t *labelParent = lv_label_create(buttonParent);
  lv_label_set_text(labelParent, "buttonParent");
  lv_obj_align(labelParent, LV_ALIGN_TOP_LEFT, 0, 0);

  lv_obj_t *button = lv_button_create(buttonParent);
  Serial.printf("button: %p \n", button);

  lv_obj_set_size(button, lv_pct(50), lv_pct(50));
  lv_obj_align(button, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_bg_color(buttonParent, lv_color_make(0, 255, 0), LV_PART_MAIN);
  lv_obj_add_flag(button, LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, "Button");
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);

  // lv_obj_add_event(
  //     button,
  //     [](lv_event_t *e)
  //     {
  //       Serial.printf("button click\n");
  //     },
  //     LV_EVENT_CLICKED, nullptr);

  lv_obj_add_event(
      buttonParent,
      [](lv_event_t *e)
      {
        auto target = lv_event_get_target_obj(e);
        auto current = lv_event_get_current_target_obj(e);
        Serial.printf("target: %p - current: %p\n", target, current);
      },
      LV_EVENT_CLICKED, nullptr);
  return screen;
};
