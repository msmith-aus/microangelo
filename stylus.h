#include "motors.h"


typedef struct {


	double currentX;
	double currentY;
	int state;

} Stylus;

void pen_up(Stylus *stylus, Motor *motor);

void pen_down(Stylus *stylus, Motor *motor);

void pen_forward(Stylus *stylus, Motor *motor);

void pen_back(Stylus *stylus, Motor *motor);

void pen_left(Stylus *stylus, Motor *motor);

void pen_right(Stylus *stylus, Motor *motor);



