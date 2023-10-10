#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include "filereader.h"



#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57


Artwork** read_artworks(void);

void draw_artworks(Artwork** artworks, Motor* motorX, Motor* motorY,
		Stylus* stylus, Servo* servo);

void move_pen(Motor* motorX, Motor* motorY);

void pen_menu(void);

void main_menu(void);

void draw_menu(void);

void initialise(void);

void draw_square(Motor* motorX, Motor* motorY);


int main(int argc, char* argv[]) {
    
	// Ncurses Setup
	setlocale(LC_ALL, "");
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);

	Motor motorX = { .dirPin = MOTOR_X_DIR, .step = MOTOR_X_STEP, 
			.enable = ENABLE_X, .logic = LOGIC_X };
	Motor motorY = { .dirPin = MOTOR_Y_DIR, .step = MOTOR_Y_STEP, 
			.enable = ENABLE_Y, .logic = LOGIC_Y };
	Stylus stylus = { .currentX = 0, .currentY = 0, .state = 0 };

	Servo servo = { .state = 0 };

	// RPi Pins Setup
	initialise();
	
	// Read-in art files
	Artwork** artworks = read_artworks();


	main_menu();
	int input = 0;
	
    while (1) {
		input = getch();
		switch(input) {
			case KEY_1:
				draw_artworks(artworks, &motorX, &motorY, &stylus, &servo);
				main_menu();
				break;
			case KEY_2:
				move_pen(&motorX, &motorY); 
				main_menu();
				break;
			case KEY_3:
				exit(0);
		}
	}
	endwin();
    return 0;
}



void draw_artworks(Artwork** artworks, Motor* motorX, Motor* motorY,
		Stylus* stylus, Servo* servo) {

    draw_menu();
	int input = 0;
    while (1) {
		input = getch();
		switch(input) {
			case KEY_1:
				printw("                                       \r");
				printw("Moving the stylus......\r");
				//sketch_artwork(artworks..., motorX, motorY, stylus, servo);
				break;
			case KEY_2:
				printw("                                       \r");
				printw("Drawing a line......\r");
				//sketch_artwork(artworks...., motorX, motorY, stylus, servo);
				break;
			case KEY_3:
				printw("                                       \r");
				printw("Drawing a border......\r");
				//sketch_artworks(artworks[5], motorX, motorY, stylus, servo);
				draw_square(motorX, motorY);
				break;
			case KEY_4:
				printw("                                       \r");
				printw("Drawing the Basic Artwork......\r");
				sketch_artwork(artworks[0], motorX, motorY, stylus, servo);
				break;
			case KEY_5:
				printw("                                       \r");
				printw("Drawing the Beginner Artwork.......\r");
				//sketch_artwork(artworks[1], motorX, motorY, stylus, servo);
				break;
			case KEY_6:
				printw("                                       \r");
				printw("Drawing the Apprentice Artwork......\r");
				//sketch_artwork(artworks[2], motorX, motorY, stylus, servo);
				break;
			case KEY_7:
				printw("                                       \r");
				printw("Drawing the Journeyman Artwork.......\r");
				//sketch_artwork(artworks[3], motorX, motorY, stylus, servo);
				break;
			case KEY_8:
				printw("                                       \r");
				printw("Drawing the Master Artwork...........\r");
				//sketch_artwork(artworks[4], motorX, motorY, stylus, servo);
				break;
			case KEY_9:
				return;
			// else keep looping
		}
	}
}


void draw_square(Motor* motorX, Motor* motorY) {

	digitalWrite(motorX->dirPin, 1);
	digitalWrite(motorX->enable, LOW);

	for (int i = 0; i < 7000; ++i) {
		digitalWrite(motorX->step, HIGH);
		delayMicroseconds(100);
		digitalWrite(motorX->step, LOW);
		delayMicroseconds(1400);

	}
	digitalWrite(motorX->enable, HIGH);

	delay(1);

	digitalWrite(motorY->dirPin, 1);
	digitalWrite(motorY->enable, LOW);

	for (int i = 0; i < 7000; ++i) {
		digitalWrite(motorY->step, HIGH);
		delayMicroseconds(100);
		digitalWrite(motorY->step, LOW);
		delayMicroseconds(1400);
	}	
	digitalWrite(motorY->enable, HIGH);

	delay(1);

	digitalWrite(motorX->dirPin, 0);
	digitalWrite(motorX->enable, LOW);

	for (int i = 0; i < 7000; ++i) {
		digitalWrite(motorX->step, HIGH);
		delayMicroseconds(100);
		digitalWrite(motorX->step, LOW);
		delayMicroseconds(1400);

	}
	digitalWrite(motorX->enable, HIGH);

	delay(1);

	digitalWrite(motorY->dirPin, 0);
	digitalWrite(motorY->enable, LOW);

	for (int i = 0; i < 7000; ++i) {
		digitalWrite(motorY->step, HIGH);
		delayMicroseconds(100);
		digitalWrite(motorY->step, LOW);
		delayMicroseconds(1400);
	}	
	digitalWrite(motorY->enable, HIGH);




}

void move_pen(Motor* motorX, Motor* motorY) {

	pen_menu();
	int input = 0;
    while (1) {
		input = getch();
		switch(input) {
			case KEY_UP:
				printw("Moving Stylus Forwards.....\r");
				drive_motor(motorY, 1, FORWARD, STEPS_PER_REV);
				flushinp();
				break;
			case KEY_RIGHT:
				printw("Moving Stylus to the right......\r");
				drive_motor(motorX, 1, FORWARD, STEPS_PER_REV);
				flushinp();
				break;
			case KEY_LEFT:
				printw("Moving Stylus to the left......\r");
				drive_motor(motorX, 1, BACKWARD, STEPS_PER_REV);
				flushinp();
				break;
			case KEY_DOWN:	
				printw("Moving Stylus Backwards.....\r");
				drive_motor(motorY, 1, BACKWARD, STEPS_PER_REV);
				flushinp();
				break;
			case KEY_5:
				return;

			default:
				digitalWrite(motorX->enable, HIGH);
				digitalWrite(motorY->enable, HIGH);
		}
	} 
}


void initialise() {


	wiringPiSetup();

	// Set up pins
	pinMode(MOTOR_X_STEP, OUTPUT);
	pinMode(MOTOR_Y_STEP, OUTPUT);
	pinMode(MOTOR_X_DIR, OUTPUT);
	pinMode(MOTOR_Y_DIR, OUTPUT);
	//pinMode(LOGIC_X, OUTPUT);
	pinMode(ENABLE_X, OUTPUT);
	//pinMode(LOGIC_Y, OUTPUT);
	pinMode(ENABLE_Y, OUTPUT);
	//digitalWrite(LOGIC_X, HIGH);
	digitalWrite(ENABLE_X, HIGH);
	//digitalWrite(LOGIC_Y, HIGH);
	digitalWrite(ENABLE_Y, HIGH);

	// Motor pins

	// Servo pins

	// Limit switches

}




void main_menu() {

	clear();
    printw("Welcome to microangelo's amazing artbot!\n");
    printw("Select an action from the below menu\n");
    printw("[1] - Draw art\n");
    printw("[2] - Move pen\n");
    printw("[3] - Exit\n");
	refresh();
}


void draw_menu() {
    
	clear();
    printw("Lets draw some art!\n");
    printw("Select an action from the below menu\n");
    printw("[1] - Show that we can move the stylus\n");
    printw("[2] - Draw a line\n");
    printw("[3] - Draw a border\n");
    printw("[4] - Draw the Basic Artwork\n");
	printw("[5] - Draw the Beginner Artwork\n");
    printw("[6] - Draw Apprentice Artwork\n");
    printw("[7] - Draw Journeyman Artwork\n");
    printw("[8] - Draw Master Artwork\n");
    printw("[9] - Back\n");
	refresh();
}

void pen_menu() {
    
	clear();
    printw("Pen Menu\n");
    printw("[\u2190 ] - Move Pen Left\n");
    printw("[\u2192 ] - Move Pen Right\n");
    printw("[\u2191 ] - Move Pen Forward\n");
    printw("[\u2193 ] - Move Pen Backward\n");
    printw("[5] - Back\n");
	refresh();

}


Artwork** read_artworks() {

	Artwork** artworks = malloc(sizeof(Artwork*) * 7);
	artworks[0] = filereader("artwork-files/basic.txt");
	artworks[1] = filereader("artwork-files/beginner.txt");
	artworks[2] = filereader("artwork-files/apprentice.txt");
	artworks[3] = filereader("artwork-files/journeyman.txt");
	artworks[4] = filereader("artwork-files/master.txt");
	artworks[5] = filereader("artwork-files/square.txt");
	artworks[6] = '\0';

	return artworks;

}














