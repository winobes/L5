#include "physics.h" 
#include "math.h"
#include "error.h"
#include "log.h"

const Point ORIGIN = { .x = 0, .y = 0 };

Point point_add(Point p1, Point p2) {
    return (Point) { p1.x + p2.x, p1.y + p2.y };
}

Point point_subtract(Point p1, Point p2) {
    return (Point) { p1.x - p2.x, p1.y - p2.y };
}

/* Returns a Point vector perpendicular to v. */
Point point_perp(Point p) {
    return (Point) { -p.y, p.x };
}

/* Scales the x and y coordinates of Point p by m. */
Point point_scale(Point p, double m) {
    return (Point) { p.x * m, p.y * m };
}

/* Converts a polar vector (Vector) to a euclidean (Point) vector. */ 
Point vector_to_point(Vector v) {
    Point p;
    p.x = v.m *  sin(v.d);
    p.y = v.m * -cos(v.d);
    return p;
}

/* Gives the distance between two points */
double point_dist(Point p1, Point p2) {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    return sqrt(x*x + y*y);
}

/* Converts a euclidean (Point) vector to a polar vector (Vector). */
Vector point_to_vector(Point p) {
    Vector v;
    if (p.x == 0 && p.y == 0) 
        v.d = 0;
    else 
        v.d = atan2(p.y, p.x) + M_PI/2;
    v.m = point_dist(p, ORIGIN);
    return v;
}

void vector_add_to(Vector *v1, Vector v2) {
    Point p1 = vector_to_point(*v1);
    Point p2 = vector_to_point(v2);
    *v1 = point_to_vector(point_add(p1,p2));
}

void move_by(Point *p, Vector v) {
    p->x += v.m *  sin(v.d);
    p->y += v.m * -cos(v.d);
}

/* Rotates the point around the origin. */
Point point_rotate(Point p, double r) {
    return (Point) { p.x * cos(r) - p.y * sin(r) , p.x * sin(r) + p.y * cos(r) };
}

Point point_rotate_around(Point p, Point q, double r) {
    return point_add(point_rotate(point_subtract(p, q), r), q);
}

/* Gives the unit normalization of p. */
Point point_normalize(Point p) {
    double normalizer = sqrt(p.x * p.x + p.y * p.y);
    return point_scale(p, 1/normalizer);
}

/* Gives the dotproduct of p1 and p2. */
double point_dot(Point p1, Point p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

/* Checks if two ranges in the form of Points are overlapping. Assumes 
 * that .x < .y for both Points.
 */ 
double point_overlap(Point p1, Point p2) {
    if ((p1.y < p2.x) || (p2.y < p1.x)) 
        return 0;
    else if (p1.x < p2.x) {
        if (p1.y < p2.y) return p1.y - p2.x;
        else return p2.y - p2.x;
    }
    else { // p2.x < p1.x
        if (p2.y < p1.y) return p2.y - p1.x;
        else return p1.y - p1.x;
    }
}


/* Gives the projection of v onto the provided axis. */
Point project(Polygon s, Point axis) {
    double min = point_dot(s.verts[0], axis);
    double max = min;
    for (int i = 1; i < s.n_verts; i++) {
        double next = point_dot(s.verts[i], axis);
        if (next < min) min = next;
        else if (next > max) max = next;
    }
    Point projection = { .x = min, .y = max };
    return projection;
}
   

void polygon_translate(Polygon *s, double r, Point pos) {
    for (int i = 0; i < s->n_verts; i++)
        s->verts[i] = point_add(point_rotate(s->verts[i], r), pos);
}


bool polygon_intersect(Polygon a, Polygon b, Vector* penetration) {

    double min_overlap = 10000; //TODO unmagic this
    Point min_overlap_axis;

    // check for separating axes from a's edges
    for (int i = 0; i < a.n_verts; i++) {
        int j = i + 1;
        if (j == a.n_verts) 
            j = 0;
        Point axis = point_normalize(point_perp(point_subtract(
                        a.verts[i], a.verts[j])));
        /*printf("axis %d x = %f y = %f\n", i, axis.x, axis.y);*/
        double overlap = point_overlap(project(a, axis), project(b, axis));
        if (overlap == 0) {
            penetration = NULL;
            return false;
        }
        else if (overlap < min_overlap) {
            min_overlap = overlap;
            min_overlap_axis = axis;
        }
    }
    // check for separating axes from b's edges
    for (int i = 0; i < b.n_verts; i++) {
        int j = i + 1;
        if (j == b.n_verts) j = 0;
        Point axis = point_normalize(point_perp(point_subtract(
                        b.verts[i], b.verts[j])));
        double overlap = point_overlap(project(a, axis), project(b, axis));
        if (overlap == 0) {
            penetration = NULL;
            return false;
        }
        else if (overlap < min_overlap) {
            min_overlap = overlap;
            min_overlap_axis = axis;
        }
    }
   
    *penetration = point_to_vector(point_scale(min_overlap_axis, min_overlap));
    return true;
}


Polygon create_regular_polygon(int n_verts, double size) {

    if (n_verts < 3)
        error("Polygon must have at least 3 vertices.");

    Point* verts = malloc(sizeof(Point) * n_verts);

    for (int i = 0; i < n_verts; i++) {
        verts[i].x = size *  sin(2 * i * M_PI / n_verts);
        verts[i].y = size * -cos(2 * i * M_PI / n_verts);
    }

    Polygon s;
    s.n_verts = n_verts;
    s.verts = verts;

    return s;

}

