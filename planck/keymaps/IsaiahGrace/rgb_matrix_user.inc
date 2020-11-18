// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(musical_lights)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include <stdlib.h>
  
// e.g: A more complex effect, relying on external methods and state, with
// dedicated init and run methods
//extern uint8_t musical_lights_active;
extern uint8_t musical_lights_tolerance;
extern uint8_t tolerance; // see keymap.c definitions
extern struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} musical_lights_base;

uint8_t counter;

// #define MUTATION_STEP 1 // Just hardcode 1 for now. the algorithm will have to change if this is >1
// We're on a STM32F303, a pretty good ARM 32bit processor.
// This means we can do some pretty fun things!

uint8_t PROGMEM led_grid[][3] = {
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},    {0,0,0},    {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}
};


static void musical_lights_init(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max); // what does this do?
  // This code is run when this LED program is selected...
  counter = 0;
  // Set some inital random lighting, just so the keyboard isnt black.
  uint32_t random = 0;
  for (uint8_t i = led_min; i < led_max; i++) {
    if (!(random & 0xFFFFFFF0))
      random = rand();
    
    led_grid[i][0] = random & 0x1 ? 0xFF : 0x10;
    led_grid[i][1] = random & 0x2 ? 0xFF : 0x10;
    led_grid[i][2] = random & 0x4 ? 0xFF : 0x10;
    
    random >>= 3;
  }
  //musical_lights_active = 1;
}

static bool musical_lights_run(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max); // what does this do?
  
  // This will slow down the animation speed
  // This means i'm running the code 2/3 times
  if (!(++counter % 3))
    // lmao I won't do this if you pay me to code. Just doing if for fun here
    goto end; 

  uint32_t rand_int = rand();
  int32_t pixel[] = {0,0,0};
  int32_t base[] = {
    (int32_t) (musical_lights_base.red),
    (int32_t) (musical_lights_base.green),
    (int32_t) (musical_lights_base.blue)
  };

  // If the base colors are all zero, and the lights are off, just return
  //if (!(musical_lights_active || base[0] || base[1] || base[2]))
  //  goto end; // LMAO, I've never used goto before. but I guess it works here. Sorry 
  
  //musical_lights_active = 0;
  
  int32_t lower[] = {
    (int32_t) (base[0] - musical_lights_tolerance),
    (int32_t) (base[1] - musical_lights_tolerance),
    (int32_t) (base[2] - musical_lights_tolerance)
  };
  int32_t upper[] = {
    (int32_t) (base[0] + musical_lights_tolerance),
    (int32_t) (base[1] + musical_lights_tolerance),
    (int32_t) (base[2] + musical_lights_tolerance)
  };
    
  int8_t mutate_mask; // SIGNED!

  for (uint8_t i = led_min; i < led_max; i++) {
    // refresh the random int. We'll use most of the bits.
    // Wikipedia seems to think that not all of the bits are random...
    // I can't find the definition for this libraries rand()
    if (!(i % 10)) { 
      rand_int = rand();
    }
    // TODO: If the colors change too fast: chance to mutate, chance to stay the same
    // TODO: If the colors change too slow: increase MUTATION_STEP

    pixel[0] = led_grid[i][0];
    pixel[1] = led_grid[i][1];
    pixel[2] = led_grid[i][2];
    
    for (uint8_t j = 0; j < 3; j++) {
      mutate_mask = 0;
      // mutate_mask will help us know if we MUST add or MUST subtract...
      if (pixel[j] <= lower[j])
	mutate_mask = 1;
      if (pixel[j] >= upper[j])
	mutate_mask = -1;
      pixel[j] += mutate_mask;
      
      // If we're inside the bounds, mutate!
      if (!mutate_mask) {
	pixel[j] += rand_int & 0x1 ? 1 : -1;
	rand_int >>= 1;
      }
      
      // apply limits
      if (pixel[j] > 255)
	pixel[j] = 255;
      if (pixel[j] < 0)
	pixel[j] = 0;
    }
    // active?
    //musical_lights_active |= pixel[0] | pixel[1] | pixel[2];

    // Actually set the colors...
    // This should make a pretty boarder, hopefully
    if (i > 35 || (i % 12 == 0) || (i % 12 == 11))
      rgb_matrix_set_color(i,pixel[1],pixel[2],pixel[0]);
    else
      rgb_matrix_set_color(i,pixel[0], pixel[1], pixel[2]);
    
    // Save the colors to the array, so we can mutate them again!
    led_grid[i][0] = pixel[0];
    led_grid[i][1] = pixel[1];
    led_grid[i][2] = pixel[2];
  }

 end:
  return led_max < DRIVER_LED_TOTAL; // Why? what does this do?
}

static bool musical_lights(effect_params_t* params) {
  if (params->init) musical_lights_init(params);
  return musical_lights_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
