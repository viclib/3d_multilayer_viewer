#ifndef DRAW_H
#define DRAW_H
#include <QGLWidget>
#include "globals.h"
void draw_quad(vec a, vec b, vec c, vec d);
void draw_grid(double x,double y,double dx,double dy,int w,int h,double(*z)(const vec&),vec(*col)(const vec&));
void draw_line(const vec & a, const vec & b);
void draw_axis();
double layer_z(const vec& pos);
vec layer_col(const vec & pos);
void draw_layers();
#endif // DRAW_H
