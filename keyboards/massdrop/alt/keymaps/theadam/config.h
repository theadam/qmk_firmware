#pragma once

#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CUSTOM_SOLID_REACTIVE_MULTIWIDE2 // Sets the default mode, if none has been set

#define RGB_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX
#define RGB_MATRIX_STARTUP_HUE 127
#define RGB_MATRIX_STARTUP_SAT 255 // Sets the default saturation value, if none has been set
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
#define RGB_MATRIX_STARTUP_SPD 127
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define FORCE_NKRO  // NKRO by default requires to be turned on, this forces it on during keyboard startup regardless of EEPROM setting. NKRO can still be turned off but will be turned on again if the keyboard reboots.

