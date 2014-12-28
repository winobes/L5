#include "physics.h" 
#include "math.h"
#include "error.h"
#include "log.h"

const Vector ORIGIN = { .x = 0, .y = 0 };

Vector vec_add(Vector v1, Vector v2) {
    return (Vector) { v1.x + v2.x, v1.y + v2.y };
}

Vector vec_subtract(Vector v1, Vector v2) {
    return (Vector) { v1.x - v2.x, v1.y - v2.y };
}

/* Returns a Vector vector perpendicular to v. */
Vector vec_perp(Vector v) {
    return (Vector) { -v.y, v.x };
}

/* Scales the x and y coordinates of Vector v by m. */
Vector vec_scale(Vector v, double m) {
    return (Vector) { v.x * m, v.y * m };
}

/* Gives the distance between two points */
double vec_dist(Vector p1, Vector p2) {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    return sqrt(x*x + y*y);
}


Vector vec_reflect(Vector v, Vector ax) {
    double c = (ax.x*v.x + ax.y*v.y) / (ax.x*ax.x + ax.y*ax.y);
    return (Vector) { v.x - 2*ax.x*c, v.y - 2*ax.y*c };
}

/* Rotates the point around the origin. */
Vector vec_rotate(Vector p, double r) {
    return (Vector) { p.x * cos(r) - p.y * sin(r) , p.x * sin(r) + p.y * cos(r) };
}

Vector vec_rotate_around(Vector p, Vector q, double r) {
    return vec_add(vec_rotate(vec_subtract(p, q), r), q);
}

/* Converts a polar vector to a euclidean `Vector`. */ 
Vector polar_to_vec(double d, double m) {
    return (Vector) { m * sin(d), m * -cos(d) };
}


/* Gives the unit normalization of v. */
Vector vec_normalize(Vector v) {
    double normalizer = sqrt(v.x * v.x + v.y * v.y);
    return vec_scale(v, 1/normalizer);
}

/* Gives the dotproduct of v1 and v2. */
double vec_dot(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

/* Checks if two ranges in the form of Vectors are overlapping. Assumes 
 * that .x < .y for both Vectors.
 */ 
double vec_overlap(Vector v1, Vector v2) {
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
Vector project(Polygon s, Vector axis) {
    double min = vec_dot(s.verts[0], axis);
    double max = min;
    for (int i = 1; i < s.n_verts; i++) {
        double next = vec_dot(s.verts[i], axis);
        if (next < min) min = next;
        else if (next > max) max = next;
    }
    Vector projection = { .x = min, .y = max };
    return projection;
}
   

void polygon_translate(Polygon *s, double r, Vector pos) {
    for (int i = 0; i < s->n_verts; i++)
        s->verts[i] = vec_add(vec_rotate(s->verts[i], r), pos);
}


bool polygon_intersect(Polygon a, Polygon b, Vector *collision_vec) {

    double min_overlap = 10000; //TODO unmagic this
    Vector min_overlap_axis;

    // check for separating axes from a's edges
    for (int i = 0; i < a.n_verts; i++) {
        int j = i + 1;
        if (j == a.n_verts) 
            j = 0;
        Vector axis = vec_normalize(vec_perp(vec_subtract(
                        a.verts[i], a.verts[j])));
        /*printf("axis %d x = %f y = %f\n", i, axis.x, axis.y);*/
        double overlap = vec_overlap(project(a, axis), project(b, axis));
        if (overlap == 0) {
            collision_vec = NULL;
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
        Vector axis = vec_normalize(vec_perp(vec_subtract(
                        b.verts[i], b.verts[j])));
        double overlap = vec_overlap(project(a, axis), project(b, axis));
        if (overlap == 0) {
            collision_vec = NULL;
            return false;
        }
        else if (overlap < min_overlap) {
            min_overlap = overlap;
            min_overlap_axis = axis;
        }
    }
   
    *collision_vec = vec_scale(min_overlap_axis, min_overlap);
    return true;
}


Polygon create_regular_polygon(int n_verts, double size) {

    if (n_verts < 3)
        error("Polygon must have at least 3 vertices.");

    Vector* verts = malloc(sizeof(Vector) * n_verts);

    for (int i = 0; i < n_verts; i++) {
        verts[i].x = size *  sin(2 * i * M_PI / n_verts);
        verts[i].y = size * -cos(2 * i * M_PI / n_verts);
    }

    Polygon s;
    s.n_verts = n_verts;
    s.verts = verts;

    return s;

}

