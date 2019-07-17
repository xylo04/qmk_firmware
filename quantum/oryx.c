#include "oryx.h"

 __attribute__((weak))
void raw_hid_receive_kb(uint8_t *command_data, uint8_t length) { ; }

 __attribute__((weak))
void raw_hid_receive_user(uint8_t *command_data, uint8_t length) { ; }

 void raw_hid_receive( uint8_t *data, uint8_t length ) {

     uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);

     dprintf("HID command %u\n", *command_id);

     switch(*command_id) {

         case hid_id_protocol_version:
            command_data[0] = ORYX_PROTOCOL_VERSION >> 8;
            command_data[1] = ORYX_PROTOCOL_VERSION & 0xFF;
            break;

         case hid_get_keyboard_info:
            switch(command_data[0]) {
                case hid_info_get_genuine_ez:
                    command_data[1] = 1;
                    break;
                case hid_info_get_mcu_type:
                    #if defined(__AVR__)
                        command_data[1] = 0;
                    #elif defined(PROTOCOL_CHIBIOS)
                        command_data[1] = 1;
                    #elif defined(PROTOCOL_CHIBIOS)
                        command_data[1] = 2;
                    #else
                        command_data[1] = 0xFF;
                    #endif
                    break;
                default:
                    command_data[0] = hid_unhandled;
            }
            break;
        case hid_jump_bootloader:
            // Send response to host before rebooting
            raw_hid_send(data, length);
            reset_keyboard();
            break;
        case hid_eeprom_reset:
            eeconfig_init();
            // send raw hid response before re-initializing the keyboard
            raw_hid_send(data, length);
            // re-initialize the hardware features to read values from eeprom
            keyboard_init();
            return; break;
		case hid_keymap_get_keycode:
		{
			uint16_t keycode = dynamic_keymap_get_keycode( command_data[0], command_data[1], command_data[2] );
			command_data[3] = keycode >> 8;
			command_data[4] = keycode & 0xFF;
			break;
		}
		case hid_keymap_set_keycode:
			dynamic_keymap_set_keycode( command_data[0], command_data[1], command_data[2], ( command_data[3] << 8 ) | command_data[4] );
			break;
		case hid_keymap_set_to_default:
			dynamic_keymap_reset();
			break;
		case hid_keymap_get_layer_num:
			command_data[0] = dynamic_keymap_get_layer_count();
			break;
		case hid_keymap_get_buffer:
		{
			uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
			uint16_t size = command_data[2];
			dynamic_keymap_macro_get_buffer( offset, size, &command_data[3] );
			break;
		}
		case hid_keymap_set_buffer:
		{
			uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
			uint16_t size = command_data[2];
			dynamic_keymap_macro_set_buffer( offset, size, &command_data[3] );
			break;
		}
        case hid_rgb_set_hsv:
            #if defined(RGB_MATRIX_ENABLE)
                rgb_matrix_sethsv_noeeprom(command_data[0], command_data[1], command_data[2]);
            #elif defined(RGBLIGHT_ENABLE)
                rgblight_sethsv_noeeprom(command_data[0], command_data[1], command_data[2]);
            #endif
            break;
        case hid_rgb_set_mode:
            #if defined(RGB_MATRIX_ENABLE)
                rgb_matrix_mode_noeeprom(command_data[0]);
            #elif defined(RGBLIGHT_ENABLE)
                rgblight_mode_noeeprom(command_data[0]);
            #endif
            break;
        case hid_rgb_set_enable:
            #if defined(RGB_MATRIX_ENABLE)
                if (command_data[0]) {
                    rgb_matrix_enable_noeeprom();
                } else {
                    rgb_matrix_disable_noeeprom();
                }
            #elif defined(RGBLIGHT_ENABLE)
                if (command_data[0]) {
                    rgblight_enable_noeeprom();
                } else {
                    rgblight_disable_noeeprom();
                }
            #endif
            break;
        case hid_keyboard_command:
            raw_hid_receive_kb(command_data, length-1);
            break;
        case hid_user_command:
            raw_hid_receive_user(command_data, length-1);
            break;
        default:
            *command_id = hid_unhandled;
			break;
    }

     raw_hid_send(data, length);
}



void eeconfig_init_kb(void) {
    dynamic_keymap_reset();
    eeconfig_init_user();
}
