#include "layer.h"

template <class T>
Layer<T>::Layer(){};

template <class T>
Layer<T>::Layer(std::string file, T r_, T g_, T b_){
    r = r_; g = g_; b = b_;
	x = 0; y = 0; dx = 0; dy = 0;
	r = 0; g = 0; b = 0;
	dimx = 0; dimy = 0;
    read_file(file);
};

template <class T>
Layer<T>::~Layer(){};

template <class T>
T Layer<T>::z(int x, int y) const{
    unsigned int idx = y*dimx+x;
    assert (idx < dimx*dimy);
    return zs[idx];
};

template <class T>
void Layer<T>::read_file(std::string file){
    dimx = 0; dimy = 0;
    std::string line;
    std::ifstream infile(file.c_str());

    std::getline(infile, line);
    std::istringstream first_line(line);
    first_line >> x;
    first_line >> y;
    first_line >> dx;
    first_line >> dy;

    while (std::getline(infile, line)){
        T n;
        std::istringstream iss(line);

        while (iss >> n)
            zs.push_back(n);

        if (dimx == 0)
            dimx = zs.size();
        dimy++;
    }
}

