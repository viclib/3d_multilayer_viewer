void draw_quad(vec a, vec b, vec c, vec d){
	glBegin(GL_POLYGON);
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);
	glVertex3f(c.x, c.y, c.z);
	glVertex3f(d.x, d.y, d.z);
	glEnd();
};

void draw_grid(double x,double y,double dx,double dy,int w,int h,double(*z)(const vec&),vec(*col)(const vec&)){
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

void draw_line(const vec & a, const vec & b){
	glBegin(GL_LINES);
	glVertex3d(a.x,a.y,a.z);
	glVertex3d(b.x,b.y,b.z);
	glEnd();
}

void draw_axis(){
	glColor3f(1.0,0.0,0.0); draw_line(vec(0.0,0.0,0.0),vec(1.0,0.0,0.0));
	glColor3f(0.0,1.0,0.0); draw_line(vec(0.0,0.0,0.0),vec(0.0,1.0,0.0));
	glColor3f(0.0,0.0,1.0); draw_line(vec(0.0,0.0,0.0),vec(0.0,0.0,1.0));
}

void draw_layers(){
	for (int i=0; i<layers.size(); ++i){
		selected_layer = &layers[i];
		draw_grid(
			layers[i].x,
			layers[i].y,
			layers[i].dx,
			layers[i].dy,
			layers[i].dimx,
			layers[i].dimy, 
			[](const vec & pos) -> double {return selected_layer->z(pos.x,pos.y);},
			[](const vec & pos){double c=0.5+double(pos.x)*0.05 + double(int(pos.x+pos.y)%2)*0.1;return vec(selected_layer->r*c,selected_layer->g*c,selected_layer->b*c);});
	}
}
