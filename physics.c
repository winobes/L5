#include "physics.h" 
#include "math.h"

vector vec_add(vector v1, vector v2) {
    vector w = { .x = v1.x + v2.x, .y = v1.y + v2.y };
    return w;
}

vector vec_subtract(vector v1, vector v2) {
    vector w = { .x = v1.x - v2.x, .y = v1.y - v2.y };
    return w;
}

/* Returns a vector perpendicular to v. */
vector vec_perp(vector v) {
    vector w = { .x = -v.x, .y =v.y };
    return w;
}

/* Scales the vector v by m. */
vector vec_scale(vector v, double m) {
    vector w = { .x = v.x * m, .y = v.y * m };
    return w ;
}

/* Gives the unit normalization of v. */
vector vec_normalize(vector v) {
    double normalizer = sqrt(v.x * v.x + v.y * v.y);
    return vec_scale(v, 1/normalizer);
}

/* Gives the dotproduct of v1 and v2. */
double vec_dot(vector v1, vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}


/* Checks if two ranges in the form of vectors are overlapping. Assumes 
 * that .x < .y for both vectors.
 */ 
double vec_overlap(vector v1, vector v2) {
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
vector project(polygon s, vector axis) {
    double min = vec_dot(s.verts[0], axis);
    double max = min;
    for (int i = 1; i < s.n_verts; i++) {
        double next = vec_dot(s.verts[i], axis);
        if (next < min) min = next;
        else if (next > max) max = next;
    }
    vector projection = { .x = min, .y = max };
    return projection;
}
    

bool separated(polygon a, polygon b, vector* penetration) {

    double min_overlap = 10000; //TODO unmagic this
    vector min_overlap_axis;

    // check for separating axes from a's edges
    for (int i = 0; i < a.n_verts; i++) {
        int j = i + 1;
        if (j == a.n_verts) j = 0;
        vector axis = vec_normalize(vec_perp(vec_subtract(
                        vec_add(a.verts[i], a.center), 
                        vec_add(a.verts[j], a.center))));
        double overlap = vec_overlap(project(a, axis), project(b, axis));
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
        vector axis = vec_normalize(vec_perp(vec_subtract(
                        vec_add(b.verts[i], b.center), 
                        vec_add(b.verts[j], b.center))));
        double overlap = vec_overlap(project(a, axis), project(b, axis));
        if (overlap == 0) return false;
        else if (overlap < min_overlap) {
            min_overlap = overlap;
            min_overlap_axis = axis;
        }
    }
    
    *penetration = vec_scale(min_overlap_axis, min_overlap);
    return true;
}


