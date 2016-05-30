#ifndef MATRIX_GENERATOR_H
#define MATRIX_GENERATOR_H

#include<iostream>
using std::cout;using std::cin;using std::endl;

#include<vector>
using std::vector;

#include <cmath>

#include<string>
using std::string;

#include"Vertex.h"
#include"initialisation.h"

class Matrix_Generator
{
   public:
    Matrix_Generator();

    std::vector<std::vector<double> > Laplacian_Stencil ;
    std::vector<std::vector<double> > Helmholtz_Stencil ;

    vector< std::vector< double > > my_local_matrix;
    vector<double> corners;

    Initialisation i;
    void local_stiffness_matrix(face f);

    void generate();
};


#endif // MATRIX_GENERATOR_H

