#include "stylus.h"

typedef struct {

	double x;
	double y;

} Point;

typedef struct {
	
	Point** points;
	int numPoints;

} Segment;


typedef struct {

	Segment** segments;
	int numSegments;

} Artwork;



void sketch_artwork(Artwork* artwork, Motor* motorX, Motor* motorY, Motor* motorZ,
		Stylus* stylus, Servo* servo);


void draw_line(Motor* motorX, Motor* motorY, Point* point, Stylus* stylus);

void gcd(a, b):
	while b != 0:
		