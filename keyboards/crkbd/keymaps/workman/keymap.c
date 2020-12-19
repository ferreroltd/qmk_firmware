#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 4
#define _WORKMAN 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  SCREENSOT_MAC,
  INSPECT
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_SCREENSOT_MAC SCREENSOT_MAC
#define KC_INSPECT INSPECT
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_WORKMAN] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     D,     R,     W,     B,                      J,     F,     U,     P,  SCLN,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     A,     S,     H,     T,     G,                      Y,     N,     E,     O,     I,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     M,     C,     V,                      K,     L,  COMM,   DOT,  SLSH,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, LOWER, ALTKN,      SPC, RAISE, ENT \
                              //`--------------------'  `--------------------'
  ),

    [_QWERTY] = LAYOUT_kc( \
    //,-----------------------------------------.                ,-----------------------------------------.
          TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        CTLTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSFT,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    ALTKN, LOWER, GUIEI,      SPC, RAISE, ENT \
                                //`--------------------'  `--------------------'
    ),


  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     1,     2,  LPRN,  RPRN,  UNDS,                   MINS,     7,     8,     9,   DOT,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB, MUTE,     F2,  LCBR,  RCBR,  PIPE,                   PLUS,     4,     5,     6,  HOME,  ASTR,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT, XXXXX, XXXXX,  LBRC,  RBRC,  BSLS,                      0,     1,    2 ,    3,   EQL,   RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, LOWER, ALTKN,      SPC, RAISE, ENT \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TILD, GRAVE, XXXXX, XXXXX,   ENT, XXXXX,                   LEFT,  DOWN,    UP, RIGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT, XXXXX, XXXXX, XXXXX,   SPC, RIGHT,                  ALTKN, GUIEI,  LBRC,  RBRC,  BSLS,  TILD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, LOWER, ALTKN,      SPC, RAISE, ENT \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
  VOLD,MS_WH_LEFT, MS_WH_RIGHT, MS_UP,   VOLU,  MUTE,           XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  XXXXX, LTOG, MS_LEFT, MS_DOWN, MS_RIGHT, XXXXX,               XXXXX, MS_BTN1,MS_BTN2, XXXXX, INSPECT, SCREENSOT_MAC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  XXXXX,LMOD, LHUD,MS_WH_UP,MS_WH_DOWN, XXXXX,                  XXXXX, XXXXX, XXXXX, MS_ACCEL1, MS_ACCEL2, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, LOWER, ALTKN,      SPC, RAISE, ENT \
                              //`--------------------'  `--------------------'
  )

};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case SCREENSOT_MAC:
      SEND_STRING(SS_LGUI(SS_LSFT(SS_LCTL("4"))));
      break;
    case INSPECT:
      SEND_STRING(SS_LGUI(SS_RALT("i")));
      break;
  }
  return true;
}
