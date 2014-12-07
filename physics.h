#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdlib.h>
#include <stdbool.h>

#define M_PI 3.14159265358979323846264338327

/* Usually vectors are treated like component vectors 
 * but sometimes we need them to  like Euclidean points. 
 */
typedef struct Vector {
    double x;
    double y;
} Vector;

extern const Vector ORIGIN;

/* A polygon's vertices are described by their position relative to its
 * center. It may be important that the center point is actually inside 
 * the polygon. We also generally assume that polygons are convex (e.g.
 * for the separating axis theorem to work.)
 */
typedef struct Polygon {
    size_t n_verts;
    Vector* verts;
} Polygon;

Vector vec_add(Vector p1, Vector p2);
Vector polar_to_vec(double d, double m);

/* Moves a polygon by `pos` and rotates it by `r` */
void polygon_translate(Polygon *s, double r, Vector pos);

/* If two convex polygons aren't intersecting, then there we can draw a line
 * that separates them. The separating axis theorem says that any time this is
 * the case, one of the edges of the polygon actually is such a line. If the
 * polygons are intersecting, then the vector `penetration` is set. 
 */
bool polygon_intersect(Polygon a, Polygon b, Vector *collision_vec);

/* n_verts is the number of vertices (or equivallently sides)
 * size is the distance (in pixles) of each vertex from the center
 */
Polygon create_regular_polygon(int n_verts, double size);

#endif /* PHYSICS_H */
