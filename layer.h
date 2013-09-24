#ifndef LAYER_H
#define LAYER_H
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

template <class T>
class Layer {
    public:
    Layer();
    Layer(std::string file, T r, T g, T b);
	~Layer();

    T z(int x, int y) const;
    void read_file(std::string file);

    T x, y;
    T dx, dy;
    unsigned int dimx, dimy;
    T r, g, b;

    private:
    std::vector<T> zs;
};
#endif // LAYER_H
