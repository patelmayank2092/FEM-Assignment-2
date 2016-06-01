#ifndef MATRIX_GENERATOR_H
#define MATRIX_GENERATOR_H

#include<iostream>
using std::cout;using std::cin;using std::endl;

#include<vector>
using std::vector;

#include <cmath>

#include<string>
using std::string;

#include<map>
using std::map;

#include<fstream>
using std::ifstream;using std::ofstream;

#include"Vertex.h"
#include"initialisation.h"

class Matrix_Generator
{
   public:
    Matrix_Generator();

    vector<vector<double>> Laplacian_Stencil ;
    vector<vector<double>> Helmholtz_Stencil ;

    vector<vector<double>> my_local_stiffness_matrix;
    vector<vector<double>> my_local_mass_matrix;

    vector<map<int,double>> global_stiffness_matrix;
    vector<map<int,double>> global_mass_matrix;

    vector<double> corners;

    Initialisation i;
    void local_stiffness_matrix(face f);

    void print_stiffness_matrix();

     void print_mass_matrix();

    void generate();
};


#endif // MATRIX_GENERATOR_H

