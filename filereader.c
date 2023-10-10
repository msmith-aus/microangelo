#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filereader.h"
#include <ctype.h>


Point* getPoints(char* line) {
	
	Point* point = malloc(sizeof(Point));
	double x;
	double y;
	char* tokens = strtok(line, ",");
	x = atof(tokens);
	tokens = strtok(NULL, ",");
	y = atof(tokens);
	point->x = x;
	point->y = y;

	return point;
	
}


Artwork* filereader(char* path) {

	char line[BUFFER];
	FILE* artfile = fopen(path, "r");
	Artwork* artwork = malloc(sizeof(Artwork));
	artwork->segments = malloc(sizeof(Segment*));
	artwork->numSegments = 0;
	Segment* segment;
	Point* point;
	int pointCount = 0;
	int segmentCount = 0;

	while ((fgets(line, BUFFER, artfile)) != NULL) {
		if (strncmp(line, "STA", 3) == 0) {
			pointCount = 0;
			segment = malloc(sizeof(Segment));
			segment->points = malloc(sizeof(Point*));
			segment->points[pointCount] = '\0';
			segment->numPoints = 0;
		} else if (strncmp(line, "STO", 3) == 0) {
			artwork->segments = realloc(artwork->segments, 
					sizeof(Segment*) * (segmentCount + 2));
			artwork->segments[segmentCount] = segment;
			artwork->segments[segmentCount + 1] = '\0';
			artwork->numSegments++;
			segmentCount++;
		} else if (isdigit(line[0])) {
			segment->points = realloc(segment->points, sizeof(Point*) * (pointCount + 2));
			point = getPoints(line);
			segment->points[pointCount] = point;
			segment->points[pointCount + 1] = '\0';
			segment->numPoints++;
			pointCount++;
		}
	}

	fclose(artfile);
	return artwork;
}





