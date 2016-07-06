#include <stdio.h>
#include "point.h"
#include "dbg.h"

typedef struct Polygon {
    Point **points;
    int num;
} Polygon;

Polygon *newPoly(int n, Point **points) {
    check(n > 0 && points != NULL, "Invalid arguments");
    Polygon *poly = malloc(sizeof(Polygon));
    poly->points = malloc(n * sizeof(Point *));
    poly->num = n;
    while(n-- > 0) {
        poly->points[n] = points[n]; // n should work here
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
    printf("{");
    while(++n < poly->num) {
        printPt(poly->points[n]);
        printf("\b\b, ");
    }
    printf("\b\b}\n");
}
