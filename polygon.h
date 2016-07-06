#include <stdio.h>
#include <stdarg.h>
#include "point.h"
#include "dbg.h"

typedef struct Polygon {
    Point **points;
    int num;
} Polygon;

Polygon *newPoly(int n, ...) {
    check(n > 0, "Invalid arguments");
    Polygon *poly = malloc(sizeof(Polygon));
    poly->points = malloc(n * sizeof(Point *));
    poly->num = n;
    va_list ap;

    va_start(ap, n);
    int i = -1;
    while(++i < n) {
        poly->points[i] = va_arg(ap, Point *);
    }
    return poly;
error:
    return NULL;
}

void freePoly(Polygon *poly) {
    int n = poly->num;
    while(n-- > 0) {
        free(poly->points[n]);
    }
    free(poly->points);
    free(poly);
}

void printPoly(Polygon *poly) {
    int n = -1;
    printf("{\n");
    while(++n < poly->num) {
        printPt(poly->points[n]);
    }
    printf("}\n");
}
