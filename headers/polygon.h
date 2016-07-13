#include <stdio.h>
#include "point.h"
#include "dbg.h"

typedef struct Polygon {
    Point **points;
    int num;
} Polygon;

Polygon *newPoly(int n) {
    Polygon *poly = malloc(sizeof(Polygon));
    check(poly != NULL, "Out of Memory.");
    poly->points = malloc(n * sizeof(Point *));
    check(poly->points != NULL, "Out of Memory.");
    poly->num = n;
    check(n > 2, "Invalid number of arguments.");

    return poly;
error:
    if(poly) {
        if(poly->points) free(poly->points);
        free(poly);
    }
    return NULL;
}

void freePoly(Polygon *poly) {
    check(poly != NULL && poly->points != NULL, "Null pointer.");
    int n = poly->num;
    freePts(poly->points, n);
    free(poly);
    return;
error:
    if(poly) free(poly);
    return;
}

int pushPt(Polygon *poly, Point *pt, int n) {
    check(-1 < n && n < poly->num, "Out of bounds.");
    check(poly != NULL && pt != NULL, "Null pointer.");

    poly->points[n] = pt;
    return 1;
error:
    return 0;
}

int fillPoly(Polygon *poly, Point **pts) {
    check(poly != NULL && pts != NULL, "Null pointer.");
    int size = poly->num;
    while(size--) {
        Point *pt = pts[size]; // potential OOB error
        check(pushPt(poly, pt, size), "pushPt failed.");
    }
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
