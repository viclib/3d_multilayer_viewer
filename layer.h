#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

// OBSERVAÇÂO: Usando C++ devido a especificação
template <class T>
class Layer {
    public:
	Layer();
	Layer(std::string file, T r, T g, T b);

	T z(int x, int y) const;
	void read_file(std::string file);

	T x, y;
	T dx, dy;
	unsigned int dimx, dimy;
	T r, g, b;

    private:
	std::vector<T> zs;
};

template <class T>
Layer<T>::Layer(){};

template <class T>
Layer<T>::Layer(std::string file, T r_, T g_, T b_){
	r = r_; g = g_; b = b_;
	read_file(file);
};

template <class T>
T Layer<T>::z(int x, int y) const{
	unsigned int idx = y*dimx+x;
	assert (idx < dimx*dimy);
	return zs[idx];
};

//template <class T>
//int Layer<T>::width(){
	//return dimx;
//}
//template <class T>
//int Layer<T>::height(){
	//return dimy;
//}

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

// Alimenta instância a partir de um arquivo de dados.
// Semanticamente equivalente ao seguinte programa em Scheme: 
// (λ(fname)(map (λ(line)(split " " line)) (split "\n" (fload fname)))
// Que é mais muito eficiente, por ser automaticamente paralelizável.
// (:

