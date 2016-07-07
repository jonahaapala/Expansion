#include <stdio.h>
#include <stdbool.h>
#include "polygon.h"
#include "vector.h"

static Polygon *expand(Polygon *poly, bool out, double len);
static Point *move(Polygon *poly, int pos, bool out, double len);
static bool isFacingCorrectDirection(Point *cur, Point *unit, bool out);
static int mod(int a, int b);

int main(int argc, char *argv[]) {
    Polygon *poly = newPoly(4, newPt(0,0), newPt(0,1), newPt(1, 1), newPt(1,0));
    check(poly != NULL, "newPoly failed");
    Polygon *border = expand(poly, true, 1);

    printPoly(poly);
    printPoly(border);
    freePoly(border);
    freePoly(poly);
    return 0;
error:
    return 1;
}

static Polygon *expand(Polygon *poly, bool out, double len) {
    check(poly != NULL, "Null pointer");

    int size = poly->num;
    Polygon *border = newPoly(size);

    while(size-- > 0) {
        Point *new = move(poly, size, out, len);
        if(!addPt(border, new, size)) {
            log_err("addPt failed");
        }
    }

    return border;
error:
    return NULL;
}

static Point *move(Polygon *poly, int pos, bool out, double len) {
    int size = poly->num;
    Point **ptSet = poly->points;
    Point *cur = ptSet[pos];
    Vector *v1 = newVec(cur, ptSet[mod(pos-1, size)]);
    Vector *v2 = newVec(cur, ptSet[mod(pos+1, size)]);

    double angleBtwn = fabs(v1->theta - v2->theta) / 2;
    double magnitude = fabs(len/sin(angleBtwn));
    double angBisect = (v1->theta + v2->theta) / 2;
    Point *unit = newPt(cos(angBisect), sin(angBisect));

    Point *ret;
    if(isFacingCorrectDirection(cur, unit, out)) {
        ret = sumPt(cur, scalePt(unit, magnitude)); // ret = cur + m * unit
    } else {
        ret = diffPt(cur, scalePt(unit, magnitude)); // ret = cur - m * unit
    }

    freeVec(v1);
    freeVec(v2);
    freePt(unit);
    return ret;
}

static bool isFacingCorrectDirection(Point *cur, Point *unit, bool out) {
    double epsilon = 0.001;
    Point *unitCpy = newPt(unit->x, unit->y);
    Point *test = sumPt(cur, scalePt(unitCpy, epsilon));

    freePt(unitCpy);
    return false;
}

static int mod(int a, int b) {
    int ret = a % b;
    return ret < 0 ? ret + b : ret;
}
