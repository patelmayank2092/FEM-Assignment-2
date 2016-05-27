#include"matrix_generator.h"


Matrix_Generator::Matrix_Generator(){;}

void Matrix_Generator::local_stiffness_matrix(face f)
{
    corners.resize(6,0);

    corners[0] = i.V[f.v1].x; corners[1] = i.V[f.v1].y;
    corners[2] = i.V[f.v2].x; corners[3] = i.V[f.v2].y;
    corners[4] = i.V[f.v3].x; corners[5] = i.V[f.v3].y;

    /*cout << f.v1 << '/t' << f.v2 << '/t' << f.v3 << endl;
    for(int i=0 ; i<5 ;i+=2)
        cout<< corners[i] << '\t' << corners[i+1] << endl;*/

    //my_element(corners);

   // my_local_matrix = my_element.integrate(grad(v_()) * grad(w_()));
}

void Matrix_Generator::generate()
{
    cout<< "I am in generate" << endl;
    i.process();
    int count =0;
        for(auto iter=i.F.begin();iter<i.F.end();++iter)
        {
            cout<< "I am in for loop" << endl;
            if(count<1)
            {
            local_stiffness_matrix(*iter); ++count;
            }
            else
                break;
        }

}
