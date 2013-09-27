#include "glwidget.h"
#include <QDebug>

std::vector<Layer<double> > layers;
Layer<double>* selected_layer;
double rotate_y;
double rotate_x;
bool show_axis;
bool show_grid;
bool show_wave;
double cam_radius;

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
}
void GLWidget::initializeGL(){
	rotate_y=0;
	rotate_x=0;
	show_axis=true;
	show_grid=true;
	show_wave=false;
	cam_radius=2.0;

	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_DEPTH_TEST | GL_LINE_SMOOTH);
}

void GLWidget::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,0.01f,650.0f);
	gluLookAt(
		0.0, cam_radius, cam_radius,
		0.0, 0.0, 0.0,
		0.0, 0.0, 1.0);
	glViewport(0, 0, width, height);
	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 0.0, 1.0 );

	draw_layers();
	if (show_grid)
		draw_grid(-0.5,-0.5,0.1,0.1,11,11,&guide_z,&guide_col);
	if (show_axis)
		draw_axis();

	glFlush();
}

void GLWidget::resizeGL(int width_, int height_){
	width = width_; 
	height = height_;
}

void GLWidget::open_graphic(std::string file){
	std::string line;
	std::ifstream infile(file.c_str());
	while (std::getline(infile, line)){
		std::istringstream iss(line);
		std::string layer_file;
		std::getline(iss,layer_file,';');
		layer_file = file.substr(0,file.rfind("/"))+"/"+layer_file;
		std::string color_string;
		std::getline(iss,color_string,',');
		int rgb = (int)strtol(color_string.c_str(), NULL, 16);
		int r = double((rgb&0xFF0000)>>16)/255.0;
		int g = double((rgb&0x00FF00)>>8)/255.0;
		int b = double(rgb&0x0000FF)/255.0;
		open_layer(layer_file,r,g,b);
	}
}

void GLWidget::open_layer(std::string file, double r, double g, double b){
	Layer<double> layer(file, r, g, b);
	layers.push_back(layer);
	updateGL();
}

void GLWidget::draw_quad(vec a, vec b, vec c, vec d){
	glBegin(GL_POLYGON);
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);
	glVertex3f(c.x, c.y, c.z);
	glVertex3f(d.x, d.y, d.z);
	glEnd();
};

void GLWidget::draw_grid(double x,double y,double dx,double dy,int w,int h,double(*z)(const vec&),vec(*col)(const vec&)){
	for (int i=0; i<w - 1; i++){
		for (int j=0; j<h - 1; j++){
			vec color(col(vec(i,j,0)));
			glColor3f(color.x, color.y, color.z);
			int I = i+1; 
			int J = j+1;
			float pi = x+i*dx;
			float pj = y+j*dy;
			float pI = x+I*dx;
			float pJ = y+J*dy;
			draw_quad(
				vec(pi,pj,z(vec(i,j))),
				vec(pI,pj,z(vec(I,j))),
				vec(pI,pJ,z(vec(I,J))),
				vec(pi,pJ,z(vec(i,J))));
		};
	};
}

void GLWidget::draw_line(const vec & a, const vec & b){
	glBegin(GL_LINES);
	glVertex3d(a.x,a.y,a.z);
	glVertex3d(b.x,b.y,b.z);
	glEnd();
}

void GLWidget::draw_axis(){
	glColor3f(1.0,0.0,0.0); draw_line(vec(0.0,0.0,0.0),vec(1.0,0.0,0.0));
	glColor3f(0.0,1.0,0.0); draw_line(vec(0.0,0.0,0.0),vec(0.0,1.0,0.0));
	glColor3f(0.0,0.0,1.0); draw_line(vec(0.0,0.0,0.0),vec(0.0,0.0,1.0));
}

double layer_z(const vec& pos){
	return selected_layer->z(pos.x,pos.y);
}
vec layer_col(const vec & pos){
	double c=0.5+double(pos.x)*0.05 + double(int(pos.x+pos.y)%2)*0.1;
	return vec(selected_layer->r*c,selected_layer->g*c,selected_layer->b*c);
}

double guide_z(const vec & pos){ 
	return 0; 
}
vec guide_col(const vec & pos){ 
	double add=int(pos.x+pos.y)%2*0.2; 
	return vec(0.5+add,0.5+add,0.5+add); 
}

void GLWidget::draw_layers(){
	for (unsigned int i=0; i<layers.size(); ++i){
		selected_layer = &layers[i];
		draw_grid(
			layers[i].x,
			layers[i].y,
			layers[i].dx,
			layers[i].dy,
			layers[i].dimx,
			layers[i].dimy, 
			layer_z,
			layer_col);
	}
}
