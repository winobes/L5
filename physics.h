#ifndef PHISICS_H
#define PHYSICS_H

#include <stdbool.h>

typedef struct Point {
    double x;
    double y;
} Point;

typedef struct Vector {
    double direction;
    double magnitude;
} Vector;

typedef struct Line {
    Point p1;
    Point p2;
} Line;

/* A polygon's vertices are described by their position relative to its
 * center. It may be important that the center point is actually inside 
 * the polygon. We also generally assume that polygons are convex (e.g.
 * for the separating axis theorem to work.)
 */
typedef struct polygon {
    Point center;
    double direction;
    int n_verts;
    Point* verts;
} polygon;

/* If two convex polygons aren't intersecting, then there we can draw a line
 * that separates them. The separating axes theorem says that any time this is
 * the case, one of the edges of the polygon actually is such a line. If the
 * polygons are intersecting, then the vector `penetration` is set. 
 */
bool separated(polygon a, polygon b, Vector* penetration);

#endif /* PHYSICS_H */
