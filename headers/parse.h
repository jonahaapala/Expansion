#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "point.h"
#include "dbg.h"

static void toUpper(char *string);
#define USAGE "\tSet WIDTH='value' and IN_OUT='IN or OUT'\n\tSet POINTS='\"(x1,y1)\" ... \"(xN,yN)\"'\n\tThen type: make run"

Point **parseArgs(int argc, char **args) {
    Point **points = malloc(argc * sizeof(Point));
    char *cur; double x; double y;
    
    int i = -1;
    while(++i < argc) {
        cur = args[i];
        check(*cur == '(', "Invalid format. Must start with '('");
        x = strtod(++cur, &cur);
        check(*cur == ',', "Invalid format. Must be comma delimited");
        y = strtod(++cur, &cur);
        check(*cur == ')', "Invalid format. Must end with ')'");
        points[i] = newPt(x,y);
    }

    return points;
error:
    freePts(points, argc);
    return NULL;
}

int validArgs(int argc, char **args, double *width, bool *out) {
    check(argc > 4, "Invalid number of arguments.");
    *width = strtod(args[0], NULL);
    check(*width > 0, "Invalid WIDTH. Must be greater than 0.");
    toUpper(args[1]);
    check(!strcmp(args[1], "IN") || !strcmp(args[1], "OUT"), "Invalid IN_OUT.");
    *out = strcmp(args[1], "IN") ? true : false; 

    return 1;
error:
    return 0;
}

static void toUpper(char *string) {
    while(*string != '\0') {
        *string = toupper((unsigned char)*string);
        string++;
    }
}
