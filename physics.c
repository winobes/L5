#include "physics.h" 
#include "math.h"

Point pnt_add(Point v1, Point v2) {
    Point w = { .x = v1.x + v2.x, .y = v1.y + v2.y };
    return w;
}

Point pnt_subtract(Point v1, Point v2) {
    Point w = { .x = v1.x - v2.x, .y = v1.y - v2.y };
    return w;
}

/* Returns a Point vector perpendicular to v. */
Point pnt_perp(Point v) {
    Point w = { .x = -v.x, .y =v.y };
    return w;
}

/* Scales the Pint vector v by m. */
Point pnt_scale(Point v, double m) {
    Point w = { .x = v.x * m, .y = v.y * m };
    return w ;
}

/* Gives the unit normalization of v. */
Point pnt_normalize(Point v) {
    double normalizer = sqrt(v.x * v.x + v.y * v.y);
    return pnt_scale(v, 1/normalizer);
}

/* Gives the dotproduct of v1 and v2. */
double pnt_dot(Point v1, Point v2) {
    return v1.x * v2.x + v1.y * v2.y;
}


/* Checks if two ranges in the form of Points are overlapping. Assumes 
 * that .x < .y for both Points.
 */ 
double pnt_overlap(Point v1, Point v2) {
    if ((v1.y < v2.x) || (v2.y < v1.x)) 
        return 0;
    else if (v1.x < v2.x) {
        if (v1.y < v2.y) return v1.y - v2.x;
        else return v2.y - v2.x;
    }
    else { // v2.x < v1.x
        if (v2.y < v1.y) return v2.y - v1.x;
        else return v1.y - v1.x;
    }
}


/* Gives the projection of v onto the provided axis. */
Point project(polygon s, Point axis) {
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
    

bool separated(polygon a, polygon b, Vector* penetration) {

    double min_overlap = 10000; //TODO unmagic this
    Point min_overlap_axis;

    // check for separating axes from a's edges
    for (int i = 0; i < a.n_verts; i++) {
        int j = i + 1;
        if (j == a.n_verts) j = 0;
        Point axis = pnt_normalize(pnt_perp(pnt_subtract(
                        pnt_add(a.verts[i], a.center), 
                        pnt_add(a.verts[j], a.center))));
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
                        pnt_add(b.verts[i], b.center), 
                        pnt_add(b.verts[j], b.center))));
        double overlap = pnt_overlap(project(a, axis), project(b, axis));
        if (overlap == 0) return false;
        else if (overlap < min_overlap) {
            min_overlap = overlap;
            min_overlap_axis = axis;
        }
    }
   
    //TODO need to convert to a direction vector 
    //*penetration = pnt_scale(min_overlap_axis, min_overlap);
    penetration->direction = min_overlap_axis.x; 
    penetration->magnitude = min_overlap;
    return true;
}


