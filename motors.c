#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "motors.h"
#include <unistd.h>

void drive_motor(Motor* motor, int dir, int steps) {

	
	digitalWrite(motor->dirPin, dir);
	digitalWrite(motor->enable, LOW);  
	int input = 0;
	flushinp();
	
	while(1) {
		input = getch();		
		if (input == KEY_UP || input == KEY_UP 
				|| input == KEY_LEFT || input == KEY_RIGHT) {
			digitalWrite(motor->enable, HIGH);
			break;
		} else {
			digitalWrite(motor->step, HIGH);
			delayMicroseconds(100);
			digitalWrite(motor->step, LOW);
			delayMicroseconds(1400);

		}

						
	

	}
	// For loop for the distance we want to travel

	// Need to scale the speed so the x and y motors
	// end at the same time.
	}


