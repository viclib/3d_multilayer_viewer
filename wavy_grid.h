#ifndef WAVY_GRID_H
#define WAVY_GRID_H
double wavy_z(const vec & pos){
    double x=(pos.x-20)/40;
    double y=(pos.y-20)/40;
    return sin(sqrt(x*x + y*y)*24 + now()*4)*0.2;
};
vec wavy_col(const vec & pos){
    double x=(pos.x-20)/40;
    double y=(pos.y-20)/40;
    return vec((x+1)/2, (y+1)/2, 0.5);
}

#endif // WAVY_GRID_H
