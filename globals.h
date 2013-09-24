#ifndef GLOBALS_H
#define GLOBALS_H
#include "vector3d.h"
#include <vector>
#include "layer.h"
typedef Vector3D vec;
extern double rotate_y;
extern double rotate_x;
extern bool show_axis;
extern bool show_grid;
extern bool show_wave;
extern double cam_radius;
extern std::vector<Layer<double> > layers;
extern Layer<double>* selected_layer;
#endif // GLOBALS_H
