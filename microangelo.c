#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#include "motors.h"
// #include "artwork.h"
// #include "filereader.h"

void init(void);

void draw_square(Motor* motorX, Motor* motorY);

const uint LED_PIN = 25;

int main() {

    bi_decl(bi_program_description("MicroAngelo Binary"));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));    

    stdio_init_all(); 
      
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    Motor motorX = { .dirPin = MOTOR_X_DIR, .step = MOTOR_X_STEP, 
			.enable = MOTOR_X_EN};
	Motor motorY = { .dirPin = MOTOR_Y_DIR, .step = MOTOR_Y_STEP, 
			.enable = MOTOR_Y_EN};

	init();
    
    // while (1) {
    //     // gpio_put(LED_PIN, 0);
    //     // sleep_ms(250);
    //     // gpio_put(LED_PIN, 1);
    //     // puts("This is microangelo, built and ready to draw!\n");
    //     // sleep_ms(1000);



    // }
	draw_square(&motorX, &motorY);
 }

void init() {
    // Initialize pins //
    gpio_init(MOTOR_X_STEP);
    gpio_init(MOTOR_Y_STEP);
    gpio_init(MOTOR_X_DIR);
    gpio_init(MOTOR_Y_DIR);
    gpio_init(MOTOR_X_EN);
    gpio_init(MOTOR_Y_EN);

    // Set pin gpio directions and initial values //
    gpio_set_dir(MOTOR_X_STEP, GPIO_OUT);
    gpio_set_dir(MOTOR_Y_STEP, GPIO_OUT);
    gpio_set_dir(MOTOR_X_DIR, GPIO_OUT);
    gpio_set_dir(MOTOR_Y_DIR, GPIO_OUT);
    gpio_set_dir(MOTOR_X_EN, GPIO_OUT);
    gpio_set_dir(MOTOR_Y_EN, GPIO_OUT);

    gpio_put(MOTOR_X_EN, 1);
    gpio_put(MOTOR_Y_EN, 1);

}

// Artwork** read_artworks() {

// 	Artwork** artworks = malloc(sizeof(Artwork*) * 7);
// 	artworks[0] = filereader("artwork-files/basic.txt");
// 	artworks[1] = filereader("artwork-files/beginner.txt");
// 	artworks[2] = filereader("artwork-files/apprentice.txt");
// 	artworks[3] = filereader("artwork-files/journeyman.txt");
// 	artworks[4] = filereader("artwork-files/master.txt");
// 	artworks[5] = filereader("artwork-files/square.txt");
// 	artworks[6] = '\0';

// 	return artworks;

// }

void draw_square(Motor* motorX, Motor* motorY) {

	gpio_put(motorX->dirPin, FORWARD);
	gpio_put(motorX->enable, 0);

	for (int i = 0; i < 7000; ++i) {
		gpio_put(motorX->step, 1);
		sleep_us(STEP_DELAY);
		gpio_put(motorX->step, 0);
		sleep_us(SPEED - STEP_DELAY);

	}
	gpio_put(motorX->enable, 1);

	sleep_ms(1000);

	gpio_put(motorY->dirPin, FORWARD);
	gpio_put(motorY->enable, 0);

	for (int i = 0; i < 7000; ++i) {
		gpio_put(motorY->step, 1);
		sleep_us(STEP_DELAY);
		gpio_put(motorY->step, 0);
		sleep_us(SPEED - STEP_DELAY);
	}	
	gpio_put(motorY->enable, 1);

	sleep_ms(1000);

	gpio_put(motorX->dirPin, BACKWARD);
	gpio_put(motorX->enable, 0);

	for (int i = 0; i < 7000; ++i) {
		gpio_put(motorX->step, BACKWARD);
		sleep_us(STEP_DELAY);
		gpio_put(motorX->step, 0);
		sleep_us(SPEED - STEP_DELAY);

	}
	gpio_put(motorX->enable, 1);

	sleep_ms(1000);

	gpio_put(motorY->dirPin, 0);
	gpio_put(motorY->enable, 0);

	for (int i = 0; i < 7000; ++i) {
		gpio_put(motorY->step, 1);
		sleep_us(STEP_DELAY);
		gpio_put(motorY->step, 0);
		sleep_us(SPEED - STEP_DELAY);
	}	
	gpio_put(motorY->enable, 1);

}


