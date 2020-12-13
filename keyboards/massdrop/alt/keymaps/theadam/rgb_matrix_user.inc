RGB_MATRIX_EFFECT(SOLID_REACTIVE_MULTIWIDE2)
RGB_MATRIX_EFFECT(BREATHING_CHANGE)
RGB_MATRIX_EFFECT(CHRISTMAS_RAINDROPS)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool effect_runner_reactive_splash_solid(uint8_t start, effect_params_t* params, reactive_splash_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t count = g_last_hit_tracker.count;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;
        for (uint8_t j = start; j < count; j++) {
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], rgb_matrix_config.speed);
            hsv           = effect_func(hsv, dx, dy, dist, tick);
        }
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#define ADD_H_AMOUNT 85
#define SUB_V_AMOUNT 5
#define HALF_BAND_SIZE 3
#define TIMING tick / 3
#define DIST_ROLLOUT 80.0
#define CENTER_TIME 2000.0

float ease(float perc) {
  return perc * perc * perc * perc;
}

#define DIST_BASE 50.0
#define COLOR_CHANGE 120

static HSV SOLID_REACTIVE_WIDE2_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    if (dist <= DIST_BASE && tick < CENTER_TIME) {
      uint16_t max_h = rgb_matrix_config.hsv.h + COLOR_CHANGE;

      double effect = ease((1 - (dist / DIST_BASE)) * (1.0 - (tick/CENTER_TIME)));

      uint16_t new_h = hsv.h + effect * COLOR_CHANGE;

      if (new_h > max_h) {
        new_h = max_h;
      }

      hsv.h = new_h % 255;
    }

    return hsv;
}

bool SOLID_REACTIVE_MULTIWIDE2(effect_params_t* params) {
  return effect_runner_reactive_splash_solid(0, params, &SOLID_REACTIVE_WIDE2_math);
}

static uint8_t step = 0;
bool BREATHING_CHANGE(effect_params_t* params) {
    if (params->init) {
      step = (rand() % 70) + 30;
    }
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV      hsv  = rgb_matrix_config.hsv;
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    hsv.h = (((time / 128) * step) + hsv.h) % 255;
    RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}


static void christmas_raindrops_set_color(int i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;
    HSV hsv = {0, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v};

    uint8_t wiggle_h = (rand() % 10) - 5;
    uint8_t wiggle_v = rand() % 128;
    hsv.h   = (255 + ((rand() % 2) * 85 + wiggle_h)) % 255;
    hsv.v   = 255 - wiggle_v;
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool CHRISTMAS_RAINDROPS(effect_params_t* params) {
    if (!params->init) {
        // Change one LED every tick, make sure speed is not 0
        if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 10 == 0) {
            christmas_raindrops_set_color(rand() % DRIVER_LED_TOTAL, params);
        }
        return false;
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (int i = led_min; i < led_max; i++) {
        christmas_raindrops_set_color(i, params);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
