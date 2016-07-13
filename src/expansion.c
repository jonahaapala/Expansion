#include <stdio.h>
#include <stdbool.h>
#include "polygon.h"
#include "vector.h"
#include "parse.h"

static Polygon *expand(Polygon *poly, bool directIsOut, double len);
static Point *move(Polygon *poly, int pos, bool directIsOut, double len);
static bool isFacingCorrectDirection(Polygon *poly, Point *cur,
        Point *direction, bool directIsOut);
static bool isInternalPt(Polygon *poly, Point *test);
static int mod(int a, int b);

int main(int argc, char *argv[]) {
    bool directIsOut; double width; int chkpt = 0;
    int valid = validArgs(--argc, ++argv, &width, &directIsOut);
    if(!valid) goto error;

    Point **points = NULL;
    Polygon *poly = newPoly(argc-2);
    check(poly, "newPoly failed.");
    points = parseArgs(argc-2, argv+2);
    check(points != NULL, "parseArgs failed.");
    check(fillPoly(poly, points), "fillPoly failed.");
    free(points);

    chkpt = 1;
    Polygon *border = expand(poly, directIsOut, width);
    check(border != NULL, "expand failed.");

    printPoly(poly);
    freePoly(poly);
    printPoly(border);
    freePoly(border);
    return 0;
error:
    if(valid) {
        freePoly(poly);
        free(points);
    }
    if(chkpt) freePoly(border);
    else printf("USAGE: %s\n", USAGE);
    return 1;
}

static Polygon *expand(Polygon *poly, bool directIsOut, double len) {
    check(poly != NULL, "Null pointer.");

    int size = poly->num;
    Polygon *border = newPoly(size);
    check(border, "newPoly failed.");

    while(size-- > 0) {
        Point *new = move(poly, size, directIsOut, len);
        if(!pushPt(border, new, size)) {
            log_err("pushPt failed.");
        }
    }

    return border;
error:
    return NULL;
}

static Point *move(Polygon *poly, int pos, bool directIsOut, double len) {
    int size = poly->num;
    Point **ptSet = poly->points;
    Point *cur = ptSet[pos];
    Vector *v1 = newVec(cur, ptSet[mod(pos-1, size)]);
    Vector *v2 = newVec(cur, ptSet[mod(pos+1, size)]);

    double angleBtwn = fabs(v1->theta - v2->theta) / 2;
    double magnitude = fabs(len/sin(angleBtwn));
    double angBisect = (v1->theta + v2->theta) / 2;
    Point *direction = newPt(cos(angBisect), sin(angBisect)); // unit 'vector'

    Point *ret;
    if(isFacingCorrectDirection(poly, cur, direction, directIsOut)) {
        ret = sumPt(cur, scalePt(direction, magnitude)); // ret = cur + m * unit
    } else {
        ret = diffPt(cur, scalePt(direction, magnitude)); // ret = cur - m * unit
    }

    freeVec(v1);
    freeVec(v2);
    freePt(direction);
    return ret;
}

static bool isFacingCorrectDirection(Polygon *poly, Point *cur,
        Point *direction, bool directIsOut) {
    double epsilon = 0.001;
    Point *directionCpy = newPt(direction->x, direction->y);
    Point *test = sumPt(cur, scalePt(directionCpy, epsilon));
    freePt(directionCpy);

    bool ptIsIn = isInternalPt(poly, test);
    freePt(test);

    if(ptIsIn == directIsOut) {
        return false;
    }

    return true;
}

static bool isInternalPt(Polygon *poly, Point *test) {
    Point **ptSet = poly->points;
    int size = poly->num;
    double total = 0;
    int i = -1;
    while(++i < size) {
        Vector *v1 = newVec(test, ptSet[i]);
        Vector *v2 = newVec(test, ptSet[mod(i+1, size)]);
        total += atan2(crossMag(v1, v2), dot(v1, v2));
        freeVec(v1);
        freeVec(v2);
    }

    if(fabs(total) < PI) {
        return false;
    }

    return true;
}

static int mod(int a, int b) {
    int ret = a % b;
    return ret < 0 ? ret + b : ret;
}
