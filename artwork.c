#include "artwork.h"
#include <math.h>


void draw_line(Motor* motorX, Motor* motorY, Point* point, Stylus* stylus) {

	double deltaX = 0;
	double deltaY = 0;
	double angle = 0;
	double numStepsX = 0;
	double numStepsY = 0;
	int stepsTakenX = 0;
	int stepsTakenY = 0;



	if (point->x != stylus->currentX || point->y != stylus->currentY) {

		current_steps_x = floor(stylus->currentX / LINEAR_STEP);
		current_steps_y = floor(stylus->currentY / LINEAR_STEP);

		next_point_steps_x = floor(point->x / LINEAR_STEP)
		next_point_steps_y = floor(point->y / LINEAR_STEP)

		deltaX = current_steps_x - next_point_steps_x;
		deltaY = current_steps_y - next_point_steps_y;

		// adjust for negative direction
		if deltaX < 0:
			deltaX = -deltaX;
			x_dir = 1 // anticlockwise
		else:
			x_dir = 0 // clockwise
		
		if deltaY < 0:
			deltaY = -deltaY;
			y_dir = 1 // anticlockwise
		else:	
			y_dir = 0 // clockwise
		
		gcd = 

		angle = atan(deltaY / deltaX);
		numStepsX = floor(deltaX / LINEAR_STEP);
		numStepsY = floor(deltaY / LINEAR_STEP);


		printw("Ratio: %lf\n", 2 * angle / M_PI);
		printw("Pi: %lf\n", M_PI);
	}

}


void sketch_artwork(Artwork* artwork, Motor* motorX, Motor* motorY, 
		Stylus* stylus, Servo* servo) {

	Segment* segment;
	Point* point;
	stylus->currentX = 0;
	stylus->currentY = 0;
	printw("Stylus: (%f, %f)\n", stylus->currentX, stylus->currentY);
	int numPoints;
	int segments = artwork->numSegments;
	for (int i = 0; i < segments; ++i) {
		segment = artwork->segments[i];
		numPoints = segment->numPoints;
		for (int j = 0; j < numPoints; ++j) {
			// Calculate ratios of the lines
			point = segment->points[j];
			draw_line(motorX, motorY, point, stylus);

	
		}
		printw("\n");


	}

		





}
