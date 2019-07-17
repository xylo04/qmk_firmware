#pragma once

#if ORYX_ENABLE

#include "quantum.h"

// HID protocol version 1
enum message_id {
  hid_id_protocol_version = 0x01,
  hid_get_keyboard_info,
  hid_jump_bootloader,
  hid_eeprom_reset,

  hid_keymap_get_keycode,
  hid_keymap_set_keycode,
  hid_keymap_set_to_default,
  hid_keymap_get_layer_num,
  hid_keymap_get_buffer,
  hid_keymap_set_buffer,

  hid_rgb_set_hsv,
  hid_rgb_set_mode,
  hid_rgb_set_enable,

  hid_keyboard_command,
  hid_user_command,
  hid_unhandled = 0xFF
};

enum info_id {
  hid_info_get_genuine_ez,
  hid_info_get_mcu_type,

  hid_info_invalid = 0xFF
};

#endif
