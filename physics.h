#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdbool.h>

/* Usually points are treated like coordinates on the euclidean plane
 * but sometimes we need them to behave like vectors with x and y components.
 */
typedef struct Point {
    double x;
    double y;
} Point;

extern const Point ORIGIN;

/* Traditional Euclidean vectors with direction (in radians) and a magnitude 
 * for things like velocity, etc. 
 */
typedef struct Vector {
    double d;
    double m;
} Vector;

/* A polygon's vertices are described by their position relative to its
 * center. It may be important that the center point is actually inside 
 * the polygon. We also generally assume that polygons are convex (e.g.
 * for the separating axis theorem to work.)
 */
typedef struct Polygon {
    Point center;
    double direction;
    int n_verts;
    Point* verts;
} Polygon;

void abs_pos_verts(Polygon s, Point* verts);

/* If two convex polygons aren't intersecting, then there we can draw a line
 * that separates them. The separating axis theorem says that any time this is
 * the case, one of the edges of the polygon actually is such a line. If the
 * polygons are intersecting, then the vector `penetration` is set. 
 */
bool separated(Polygon a, Polygon b, Vector* penetration);

#endif /* PHYSICS_H */
