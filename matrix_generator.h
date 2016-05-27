#ifndef MATRIX_GENERATOR_H
#define MATRIX_GENERATOR_H

#include<iostream>
using std::cout;using std::cin;using std::endl;

#include<vector>
using std::vector;

//#include"Colsamm.h"
//using namespace ::_COLSAMM_;

#include"Vertex.h"
#include"initialisation.h"

class Matrix_Generator
{
   public:
    Matrix_Generator();

    //ELEMENTS::Triangle my_element;
    vector< std::vector< double > > my_local_matrix;
    vector<double> corners;

    Initialisation i;
    void local_stiffness_matrix(face f);

    void generate();
};


#endif // MATRIX_GENERATOR_H

