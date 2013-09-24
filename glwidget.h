#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "vector3d.h"
#include "layer.h"

typedef Vector3D vec;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget(){};

    void initializeGL();
    void paintGL();
    void resizeGL();

	void draw_quad(vec a, vec b, vec c, vec d);
	void draw_grid(double x,double y,double dx,double dy,int w,int h,double(*z)(const vec&),vec(*col)(const vec&));
	void draw_line(const vec & a, const vec & b);
	void draw_axis();
	//void draw_layers();

	double rotate_y;
	double rotate_x;
	bool show_axis;
	bool show_grid;
	bool show_wave;
	double cam_radius;

	//std::vector<Layer<double> > layers;
	//Layer<double>* selected_layer;
	//double layer_z(const vec& pos);
};

//vec layer_col(const vec & pos);
//double wavy_z(const vec & pos);
//vec wavy_col(const vec & pos);
#endif // GLWIDGET_H
