#include "screenBai6.h"
#include "Arduino.h"
lv_obj_t *createScreenBai6()
{
  lv_obj_t *screen = lv_obj_create(nullptr);
  lv_obj_set_style_bg_color(screen, lv_color_make(22, 44, 88), LV_PART_MAIN);

  lv_obj_t *button = lv_button_create(screen);
  lv_obj_set_size(button, lv_pct(30), lv_pct(50));
  lv_obj_align(button, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, "Button");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

  // lv_obj_set_style_bg_color(button, lv_color_make(255, 0, 0), LV_PART_MAIN);

  lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);

  lv_obj_add_event(
      button,
      [](lv_event_t *e)
      {
        if (lv_obj_has_state(lv_event_get_current_target_obj(e), LV_STATE_CHECKED))
        {
          analogWrite(TFT_BL, 255);
          Serial.println("BUTTON is Check");
        }
        else
        {
          Serial.println("BUTTON is NOT Check");
          analogWrite(TFT_BL, 4);
        }
        // lv_screen_load_anim((lv_obj_t*)lv_event_get_user_data(e), LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 1000, 100, false);
      },
      LV_EVENT_VALUE_CHANGED, nullptr);
  return screen;
};
