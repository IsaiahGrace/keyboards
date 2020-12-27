#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// e.g: A more complex effect, relying on external methods and state, with
// dedicated init and run methods
//extern uint8_t musical_lights_active;
uint8_t musical_lights_tolerance;
struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} musical_lights_base;

uint8_t led_grid[][3] = {
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},    {0,0,0},    {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}
};

void musical_lights_init() {
  uint8_t led_min = 0;
  uint8_t led_max = 47;
  musical_lights_base.red = 0;
  musical_lights_base.green = 62;
  musical_lights_base.blue = 255;
  musical_lights_tolerance = 70;
   
  
  // This code is run when this LED program is selected...
  // Set some inital random lighting, just so the keyboard isnt black.
  /*
  uint32_t random = 0;
  for (uint8_t i = led_min; i < led_max; i++) {
    if (!(random & 0xFFFFFFF0))
      random = rand();
    
    led_grid[i][0] = random & 0x1 ? 0xFF : 0x10;
    led_grid[i][1] = random & 0x2 ? 0xFF : 0x10;
    led_grid[i][2] = random & 0x4 ? 0xFF : 0x10;
    
    random >>= 3;
  }
  */
}

void musical_lights_run() {
  uint8_t led_min = 0;
  uint8_t led_max = 47;
  
  uint32_t rand_int = rand();
  int32_t pixel[] = {0,0,0};
  int32_t base[] = {
    (int32_t) (musical_lights_base.red),
    (int32_t) (musical_lights_base.green),
    (int32_t) (musical_lights_base.blue)
  };
  
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
    // Actually set the colors...
    // This should make a pretty boarder, hopefully
    /*
    if (i > 35 || (i % 12 == 0) || (i % 12 == 11))
      rgb_matrix_set_color(i,pixel[1],pixel[2],pixel[0]);
    else
      rgb_matrix_set_color(i,pixel[0], pixel[1], pixel[2]);
    */
    // Save the colors to the array, so we can mutate them again!
    led_grid[i][0] = pixel[0];
    led_grid[i][1] = pixel[1];
    led_grid[i][2] = pixel[2];
  }
}

int main() {
  musical_lights_init();
  uint8_t colors[][3] = {{0,62,255},{0,255,149},{222,255,0},{0,0,0}};
  uint8_t tols[] = {70,70,70,0};
    
  for (int n = 0; n < 4; n++) {
    musical_lights_base.red = colors[n][0];
    musical_lights_base.green = colors[n][1];
    musical_lights_base.blue = colors[n][2];
    musical_lights_tolerance = tols[n];
    
    for (int i = 0; i < 500; i++) {
      musical_lights_run();
      printf("%3d,%3d,%3d\n",led_grid[1][0],led_grid[1][1],led_grid[1][2]);
    }
  }
  return EXIT_SUCCESS;
}
