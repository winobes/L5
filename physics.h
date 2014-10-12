#ifndef PHISICS_H
#define PHYSICS_H

#include <stdbool.h>

typedef struct vector {
    double x;
    double y;
} vector;

typedef struct line {
    vector p1;
    vector p2;
} line;

/* A polygon's vertices are described by their position relative to its
 * center. It may be important that the center point is actually inside 
 * the polygon. We also generally assume that polygons are convex (e.g.
 * for the separating axis theorem to work.)
 */
typedef struct polygon {
    vector center;
    double direction;
    int n_verts;
    vector* verts;
} polygon;

/* If two convex polygons aren't intersecting, then there we can draw a line
 * that separates them. The separating axes theorem says that any time this is
 * the case, one of the edges of the polygon actually is such a line. If the
 * polygons are intersecting, then the vector `penetration` is set. 
 */
bool separated(polygon a, polygon b, vector* penetration);

#endif /* PHYSICS_H */
