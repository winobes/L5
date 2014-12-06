#include "physics.h" 
#include "math.h"
#include "error.h"

const Point ORIGIN = { .x = 0, .y = 0 };

Point pnt_add(Point p1, Point p2) {
    Point q = { .x = p1.x + p2.x, .y = p1.y + p2.y };
    return q;
}

Point pnt_subtract(Point p1, Point p2) {
    Point q = { .x = p1.x - p2.x, .y = p1.y - p2.y };
    return q;
}

/* Returns a Point vector perpendicular to v. */
Point pnt_perp(Point p) {
    Point q = { .x = -p.x, .y =p.y };
    return q;
}

/* Scales the x and y coordinates of Point p by m. */
Point pnt_scale(Point p, double m) {
    Point q = { .x = p.x * m, .y = p.y * m };
    return q;
}

/* Scales the magnitude of Vector v by m. */
Vector vec_scale(Vector v, double m) {
    Vector w = { .d = v.d, .m = v.m * m };
    return w;
}

/* Gives the unit normalization of p. */
Point pnt_normalize(Point p) {
    double normalizer = sqrt(p.x * p.x + p.y * p.y);
    return pnt_scale(p, 1/normalizer);
}

/* Gives the dotproduct of p1 and p2. */
double pnt_dot(Point p1, Point p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

double pnt_dist(Point p1, Point p2) {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    return sqrt(x*x + y*y);
}

/* Converts a point (considered as a vector with its tail at (0,0)
 * to its corresponding Euclinean vector.
 */
Vector pnt_to_vec(Point p) {
    double d; 
    if (p.x == 0 && p.y == 0) d = 0;
    else d = atan2(p.x, p.y);
    double m = pnt_dist(p, ORIGIN);
    Vector v = { .d = d, .m = m };
    return v;
}

/* Takes a Polygon and supplies verts with the absolute positions of its 
 * vertices (i.e. not relative to the center point. verts must be allocated
 * to the correct size (the number of vertices in the polygon).
 */
void abs_pos_verts(Polygon s, Point location, Point* verts) {
    for (int i = 0; i < s.n_verts; i++) {
        verts[i] = pnt_add(location, s.verts[i]);
    }
}

/* Checks if two ranges in the form of Points are overlapping. Assumes 
 * that .x < .y for both Points.
 */ 
double pnt_overlap(Point p1, Point p2) {
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
    double min = pnt_dot(s.verts[0], axis);
    double max = min;
    for (int i = 1; i < s.n_verts; i++) {
        double next = pnt_dot(s.verts[i], axis);
        if (next < min) min = next;
        else if (next > max) max = next;
    }
    Point projection = { .x = min, .y = max };
    return projection;
}
    

bool separated(Polygon a, Point loc_a, 
               Polygon b, Point loc_b,
               Vector* penetration) {

    double min_overlap = 10000; //TODO unmagic this
    Point min_overlap_axis;

    // check for separating axes from a's edges
    for (int i = 0; i < a.n_verts; i++) {
        int j = i + 1;
        if (j == a.n_verts) j = 0;
        Point axis = pnt_normalize(pnt_perp(pnt_subtract(
                        pnt_add(a.verts[i], loc_a), 
                        pnt_add(a.verts[j], loc_a))));
        double overlap = pnt_overlap(project(a, axis), project(b, axis));
        if (overlap == 0) return false;
        else if (overlap < min_overlap) {
            min_overlap = overlap;
            min_overlap_axis = axis;
        }
    }
    // check for separating axes from b's edges
    for (int i = 0; i < b.n_verts; i++) {
        int j = i + 1;
        if (j == b.n_verts) j = 0;
        Point axis = pnt_normalize(pnt_perp(pnt_subtract(
                        pnt_add(b.verts[i], loc_b), 
                        pnt_add(b.verts[j], loc_b))));
        double overlap = pnt_overlap(project(a, axis), project(b, axis));
        if (overlap == 0) return false;
        else if (overlap < min_overlap) {
            min_overlap = overlap;
            min_overlap_axis = axis;
        }
    }
   
    *penetration = pnt_to_vec(min_overlap_axis);
    *penetration = vec_scale(*penetration, min_overlap); 
    return penetration;
}


Polygon create_regular_polygon(int n_verts, double size) {

    if (n_verts < 3)
        error("Polygon must have at least 3 n_verts.");

    Point* verts = malloc(sizeof(Point) * n_verts);

    for (int i = 0; i < n_verts; i++) {
        verts[i].x = size *  sin(2 * i * M_PI / n_verts);
        verts[i].y = size * -cos(2 * i * M_PI / n_verts);
    }

    Polygon s;
    s.direction = 0;
    s.n_verts = n_verts;
    s.verts = verts;

    return s;

}

