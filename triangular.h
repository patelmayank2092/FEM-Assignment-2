
#ifndef TRIANGULAR_H
#define TRIANGULAR_H

#include "type.h"

#include<iostream>
using std::cout;using std::cin;using std::endl;

#include<fstream>
using std::ifstream;using std::ofstream;

#include<string>
using std::string;

#include <vector>
using std::vector;

#include "Vertex.h"

#include <cmath>

typedef double real;
typedef int intg;

class Initialisation{

  private:
    vector<real> corners;

  public:
    vector<vertex> V;
    vector<face> F;
    vector<real> K;
    vertex v;
    face f;


    Initialisation();
    void process(void);
    void readFile(void);
    void k_waveNumber(void);
};

#endif  // TRIANGULAR_H
