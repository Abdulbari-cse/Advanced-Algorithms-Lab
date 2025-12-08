/*
/*
 * Project 3: Closest Pair of Points using Divide and Conquer
 * Data Structure: Linked List
 * * Problem Description:
 *program called ClosestPair that implements the O(n log n) divide-and-conquer algorithm
for CLOSEST-PAIR. Your program should read the points from a file. The first line
of input will be an integer giving the number of points. The following lines of input will contain
the coordinates of the points, one point per line containing the x-coordinate followed by
the y-coordinate of each point, separated by whitespace; all the points will be distinct. Each
coordinate will be a decimal floating-point value.
The output of your program should be of the form
Closest pair: p1(9:00; 12:00); p2(10:00; 11:00) d = 1:414214
where each coordinate and the distance is output in the default form for printf and the first
point listed is the one with the lower x-coordinate (lower y-coordinate if the x-coordinates are
the same). If there are multiple pairs of points with the same distance then the one output
should be the first one when all such pairs are sorted in increasing order by first x-coordinate,
then first y-coordinate, then second x-coordinate, then second y-coordinate.
 * * Input Format:
 * N (number of points)
 * x1 y1
 * x2 y2
 * ...
 */

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>
//DATA STRUCTURE
typedef struct {
    double x;
    double y;
} point;

typedef struct pnode {
    point p;
    struct pnode *next;
} pnode;

typedef struct {
    pnode *head;
    int size;
} plist;
//LINKED LIST FUNCTIONS
plist* plist_create() {
    plist *l = (plist*)malloc(sizeof(plist));
    if (!l) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    l->head = NULL;
    l->size = 0;
    return l;
}
void plist_add(plist *l, point p) {
    pnode *n = (pnode*)malloc(sizeof(pnode));
    if (!n) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    n->p = p;
    n->next = l->head;
    l->head = n;
    l->size++;
}

int plist_size(const plist *l) {
    return l->size;
}

void plist_destroy(plist *l) {
    if (!l) return;
    pnode *curr = l->head;
    while (curr) {
        pnode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(l);
}

//SORTING UTILITIES
point* plist_to_array(const plist *l) {
    point *arr = (point*)malloc(l->size * sizeof(point));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    pnode *curr = l->head;
    int i = l->size - 1;
    while (curr) {
        arr[i--] = curr->p;
        curr = curr->next;
    }
    return arr;
}
void plist_from_array(plist *l, point *arr, int n) {
    pnode *curr = l->head;
    while (curr) {
        pnode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    l->head = NULL;
    l->size = 0;

    for (int i = n - 1; i >= 0; i--) {
        plist_add(l, arr[i]);
    }
}

int point_compare_x(const void *a, const void *b) {
    point *p1 = (point*)a;
    point *p2 = (point*)b;
    if (p1->x < p2->x) return -1;
    if (p1->x > p2->x) return 1;
    if (p1->y < p2->y) return -1;
    if (p1->y > p2->y) return 1;
    return 0;
}

int point_compare_y(const void *a, const void *b) {
    point *p1 = (point*)a;
    point *p2 = (point*)b;
    if (p1->y < p2->y) return -1;
    if (p1->y > p2->y) return 1;
    if (p1->x < p2->x) return -1;
    if (p1->x > p2->x) return 1;
    return 0;
}

void plist_sort(plist *l, int (*cmp)(const void*, const void*)) {
    if (l->size <= 1) return;
    point *arr = plist_to_array(l);
    qsort(arr, l->size, sizeof(point), cmp);
    plist_from_array(l, arr, l->size);
    free(arr);
}
//MATH FUNCTIONS
double distance(point p1, point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}
int pair_compare(point a1, point a2, point b1, point b2) {
    if (point_compare_x(&a1, &a2) > 0) {
        point temp = a1; a1 = a2; a2 = temp;
    }
    if (point_compare_x(&b1, &b2) > 0) {
        point temp = b1; b1 = b2; b2 = temp;
    }
    int cmp = point_compare_x(&a1, &b1);
    if (cmp != 0) return cmp;
    return point_compare_x(&a2, &b2);
}

//INPUT FUNCTION

void read_points(FILE *stream, plist *l, int n) {
    for (int i = 0; i < n; i++) {
        point p;
        if (fscanf(stream, "%lf %lf", &p.x, &p.y) != 2) {
            fprintf(stderr, "Error: Failed to read point %d\n", i + 1);
            exit(1);
        }
        plist_add(l, p);
    }
}
//BRUTE FORCE (BASE CASE)
void closest_pair_bruteforce(const plist *l, point *p1, point *p2, double *d) {
    *d = DBL_MAX;

    for (pnode *a = l->head; a; a = a->next) {
        for (pnode *b = a->next; b; b = b->next) {
            double dist = distance(a->p, b->p);
            if (dist < *d || (fabs(dist - *d) < 1e-10 &&
                pair_compare(a->p, b->p, *p1, *p2) < 0)) {
                *d = dist;
                *p1 = a->p;
                *p2 = b->p;
            }
        }
    }
}

//REQUIRED SPLIT FUNCTIONS
void split_list_x(const plist *l, plist *left, plist *right) {
    pnode *curr = l->head;
    int mid = l->size / 2;
    int i = 0;

    while (curr) {
        if (i < mid)
            plist_add(left, curr->p);
        else
            plist_add(right, curr->p);
        curr = curr->next;
        i++;
    }
}

void split_list_y(const plist *l, const plist *x_left, const plist *x_right,
                  plist *y_left, plist *y_right) {
    pnode *curr = l->head;

    while (curr) {
        // Check if point exists in x_left
        int in_left = 0;
        pnode *check = x_left->head;
        while (check) {
            if (fabs(check->p.x - curr->p.x) < 1e-10 &&
                fabs(check->p.y - curr->p.y) < 1e-10) {
                in_left = 1;
                break;
            }
            check = check->next;
        }

        if (in_left)
            plist_add(y_left, curr->p);
        else
            plist_add(y_right, curr->p);

        curr = curr->next;
    }
}

// SLAB CREATION FUNCTIONS
void make_slab_l(const plist *list_y, plist *slab_l, double x_mid, double delta) {
    pnode *curr = list_y->head;
    while (curr) {
        if (curr->p.x >= x_mid - delta && curr->p.x <= x_mid) {
            plist_add(slab_l, curr->p);
        }
        curr = curr->next;
    }
}
void make_slab_r(const plist *list_y, plist *slab_r, double x_mid, double delta) {
    pnode *curr = list_y->head;
    while (curr) {
        if (curr->p.x > x_mid && curr->p.x <= x_mid + delta) {
            plist_add(slab_r, curr->p);
        }
        curr = curr->next;
    }
}

//CROSS-DIVIDE SEARCH
void across_pair(const plist *slab_l, const plist *slab_r,
                 point *p1, point *p2, double *d) {
    pnode *curr_l = slab_l->head;

    while (curr_l) {
        pnode *curr_r = slab_r->head;
        int checked = 0;

        while (curr_r && checked < 8) {
            double dy = fabs(curr_r->p.y - curr_l->p.y);

            if (dy < *d) {
                double dist = distance(curr_l->p, curr_r->p);

                if (dist < *d || (fabs(dist - *d) < 1e-10 &&
                    pair_compare(curr_l->p, curr_r->p, *p1, *p2) < 0)) {
                    *d = dist;
                    *p1 = curr_l->p;
                    *p2 = curr_r->p;
                }
                checked++;
            } else if (curr_r->p.y > curr_l->p.y + *d) {
                // Points too far in y, stop checking
                break;
            }

            curr_r = curr_r->next;
        }
        curr_l = curr_l->next;
    }
}

// ========== MAIN DIVIDE & CONQUER ALGORITHM ==========

void closest_pair(const plist *list_x, const plist *list_y,
                  point *p1, point *p2, double *d) {
    int n = plist_size(list_x);

    if (n <= 3) {
        closest_pair_bruteforce(list_x, p1, p2, d);
        return;
    }

    plist *x_left = plist_create();
    plist *x_right = plist_create();
    plist *y_left = plist_create();
    plist *y_right = plist_create();

    split_list_x(list_x, x_left, x_right);
    split_list_y(list_y, x_left, x_right, y_left, y_right);

    double x_mid = 0.0;
    pnode *curr = x_left->head;
    while (curr) {
        x_mid = curr->p.x;
        curr = curr->next;
    }

    point p1_left, p2_left;
    double d_left;
    closest_pair(x_left, y_left, &p1_left, &p2_left, &d_left);

    point p1_right, p2_right;
    double d_right;
    closest_pair(x_right, y_right, &p1_right, &p2_right, &d_right);
    if (d_left < d_right || (fabs(d_left - d_right) < 1e-10 &&
        pair_compare(p1_left, p2_left, p1_right, p2_right) < 0)) {
        *p1 = p1_left;
        *p2 = p2_left;
        *d = d_left;
    } else {
        *p1 = p1_right;
        *p2 = p2_right;
        *d = d_right;
    }

    double delta = *d;

    plist *slab_l = plist_create();
    plist *slab_r = plist_create();
    make_slab_l(y_left, slab_l, x_mid, delta);
    make_slab_r(y_right, slab_r, x_mid, delta);

    across_pair(slab_l, slab_r, p1, p2, d);

    plist_destroy(x_left);
    plist_destroy(x_right);
    plist_destroy(y_left);
    plist_destroy(y_right);
    plist_destroy(slab_l);
    plist_destroy(slab_r);
}

// ========== MAIN FUNCTION ==========

int main(int argc, char **argv) {
    FILE *input = stdin;
    int n;
    if (argc == 2) {
        input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "Error: Cannot open file '%s'\n", argv[1]);
            return 1;
        }
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s [input_file]\n", argv[0]);
        fprintf(stderr, "       If no file specified, reads from stdin\n");
        return 1;
    }
    if (fscanf(input, "%d", &n) != 1 || n < 2) {
        fprintf(stderr, "Error: Invalid number of points (need at least 2)\n");
        if (input != stdin) fclose(input);
        return 1;
    }

    plist *list_x = plist_create();
    plist *list_y = plist_create();

    read_points(input, list_x, n);
    if (input != stdin) fclose(input);

    plist_sort(list_x, point_compare_x);

    pnode *curr = list_x->head;
    while (curr) {
        plist_add(list_y, curr->p);
        curr = curr->next;
    }
    plist_sort(list_y, point_compare_y);
    point p1, p2;
    double d;
    closest_pair(list_x, list_y, &p1, &p2, &d);
    if (point_compare_x(&p1, &p2) > 0) {
        point temp = p1;
        p1 = p2;
        p2 = temp;
    }
    printf("Closest pair: p1(%.2f, %.2f), p2(%.2f, %.2f) d = %f\n",
           p1.x, p1.y, p2.x, p2.y, d);

    // Cleanup
    plist_destroy(list_x);
    plist_destroy(list_y);

    return 0;
}
