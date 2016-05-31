#include"matrix_generator.h"

#include"Colsamm.h"
using namespace ::_COLSAMM_;

Matrix_Generator::Matrix_Generator(){;}


double k_func(double x, double y)
{
    double delta=0.01;
    real a=(100 + delta);
    real k;
    k=  a*exp(-50*((x*x) + (y*y)))-100;
    return k;
}

void Matrix_Generator::local_stiffness_matrix(face f)
{
    static int face_num =0;
    ELEMENTS::Triangle my_element;
    corners.resize(6,0);

    corners[0] = i.V[f.v1].x; corners[1] = i.V[f.v1].y;
    corners[2] = i.V[f.v2].x; corners[3] = i.V[f.v2].y;
    corners[4] = i.V[f.v3].x; corners[5] = i.V[f.v3].y;


    cout<< "Vertices " << endl;
    cout << face_num << '\t'<< f.v1 << '\t' << f.v2 << '\t' << f.v3 << endl;

    cout<< "vertix co-ordinates" <<endl;
    for(int i=0 ; i<5 ;i+=2)
        cout<< corners[i] << '\t' << corners[i+1] << endl;

   my_element(corners);


   Laplacian_Stencil = my_element.integrate(grad(v_()) * grad(w_()));

   Helmholtz_Stencil = my_element.integrate(func<double>(k_func) *v_() * w_());

   my_local_matrix.resize(3);

   for(auto i = my_local_matrix.begin(); i < my_local_matrix.end(); ++i)
       i->resize(3);

   for(size_t i = 0; i < 3; ++i)
   {
        for(size_t j = 0; j < 3; ++j)
        {
        my_local_matrix[i][j] = Laplacian_Stencil[i][j] - Helmholtz_Stencil[i][j];
        }
   }

   cout<< "Local stiffness Matrix" << endl;
   for(auto i = my_local_matrix.begin(); i < my_local_matrix.end(); ++i)
   {
       for(auto j = i->begin(); j< i->end() ; ++j)
           cout<< *j << '\t';
   cout<<endl;
   }

   face_num++;

}

void Matrix_Generator::generate()
{
    i.process();
    int count =0;
        for(auto iter=i.F.begin();iter<i.F.end();++iter)
        {

            if(count<1)
            {
            local_stiffness_matrix(*iter); ++count;
            }
            else
                break;
        }

}
