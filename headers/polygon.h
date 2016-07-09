#include <stdio.h>
#include <stdarg.h>
#include "point.h"
#include "dbg.h"

typedef struct Polygon {
    Point **points;
    int num;
} Polygon;

Polygon *newPoly(int n, ...) {
    Polygon *poly = malloc(sizeof(Polygon));
    check_mem(poly);
    poly->points = malloc(n * sizeof(Point *));
    check_mem(poly->points);
    poly->num = n;
    check(n > 2, "Invalid number of arguments");

    va_list ap;
    va_start(ap, n);
    int i = -1;
    while(++i < n) {
        poly->points[i] = va_arg(ap, Point *);
    }

    return poly;
error:
    if(poly) free(poly);
    return NULL;
}

void freePoly(Polygon *poly) {
    check(poly != NULL && poly->points != NULL, "Null pointer");
    int n = poly->num;
    while(n-- > 0) {
        freePt(poly->points[n]);
    }
    free(poly->points);
    free(poly);
error:
    return;
}

int addPt(Polygon *poly, Point *pt, int n) {
    check(-1 < n && n < poly->num, "Out of bounds");
    check(poly != NULL && pt != NULL, "Null pointer");

    poly->points[n] = pt;

    return 1;
error:
    return 0;
}

void printPoly(Polygon *poly) {
    int n = -1;
    printf("{\n");
    while(++n < poly->num) {
        printPt(poly->points[n]);
    }
    printf("}\n");
}
