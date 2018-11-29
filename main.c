%{
#include <stdio.h>
#include "zjs(1).h"
#include "zoomjoystrong.l"
#undef yywrap
#define yywrap() 1
#define debug
void yyerror (char const *s)
%}

%%

% union {
    int ival;
    float fval;
    char* sval;
}
// Tokens in our Flex file that bison needs to know
% token END
% token END_STATEMENT
% token POINT
% token LINE
% token CIRCLE
% token RECTANGLE
% token SET_COLOR
% token <ival> INT
% token <fval> FLOAT

%%
// a program has statement_list
    Program: statement_list
            ;
// A recursive valid statement followed by the end_statement token.
    statement_list: statement END_STATEMENT
                | statement statement_list END_STATEMENT
                ;
// multiple statements followed by the END token
    statement           : line INT INT INT INT   { };
                |         circle INT INT INT
                |         rectangle INT INT INT INT
                |         set_color INT INT INT
                ;
// A line command that will plot a line from x,y to u,v.
    Line x y u v        : line (x1, y1, x2, y2)
                ;
// A point command that will plot a point at x, y.
    Point x y           : point (x, y) END
                ;
// A circle command that plots a circle of radius r around the center point at x,y.

    Circle x y r        :  circle (x, y, r) END
                ;
// a rectangle command that draws a rectangle of height h and width w beginning at the top left edge x,y.
    Rectangle x y w h   : rectangle (x, y, w, h) END
                ;
// a set color command that changes the current drawing color to the r,g,b tuple.
    Set_color r g b     : set_color (r, g, b) END
                ;
// To end the setup
    END                  : finish()
                ;
%%


int main(int argc, char** argv) {
    setup();
    yyparse();// Start parsing!
    finish();
    return 0;
}
