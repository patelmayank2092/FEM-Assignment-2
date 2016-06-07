#include"matrix_generator.h"

#define tri_elem 1039
#define numPoint 1039


#include"Colsamm.h"
using namespace ::_COLSAMM_;

Matrix_Generator::Matrix_Generator(){
    init_vec.resize(1039,1);
}


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


    /*cout<< "Vertices " << endl;
    cout << face_num << '\t'<< f.v1 << '\t' << f.v2 << '\t' << f.v3 << endl;

    cout<< "vertix co-ordinates" <<endl;
    for(int i=0 ; i<5 ;i+=2)
        cout<< corners[i] << '\t' << corners[i+1] << endl;*/

   my_element(corners);


   Laplacian_Stencil = my_element.integrate(grad(v_()) * grad(w_()));

   Helmholtz_Stencil = my_element.integrate(func<double>(k_func) *v_() * w_());

   my_local_stiffness_matrix.resize(3);

   for(auto i = my_local_stiffness_matrix.begin(); i < my_local_stiffness_matrix.end(); ++i)
       i->resize(3);

   for(size_t i = 0; i < 3; ++i)
   {
        for(size_t j = 0; j < 3; ++j)
        {
        my_local_stiffness_matrix[i][j] = Laplacian_Stencil[i][j] - Helmholtz_Stencil[i][j];
        }
   }

   /*cout<< "Local stiffness Matrix" << endl;
   for(auto i = my_local_stiffness_matrix.begin(); i < my_local_stiffness_matrix.end(); ++i)
   {
       for(auto j = i->begin(); j< i->end() ; ++j)
           cout<< *j << '\t';
   cout<<endl;
   }*/

   my_local_mass_matrix = my_element.integrate(v_() * w_());

   face_num++;


   global_stiffness_matrix.resize(1039);

   global_stiffness_matrix[f.v1][f.v1] += my_local_stiffness_matrix[0][0];
   global_stiffness_matrix[f.v2][f.v2] += my_local_stiffness_matrix[1][1];
   global_stiffness_matrix[f.v3][f.v3] += my_local_stiffness_matrix[2][2];

   global_stiffness_matrix[f.v1][f.v2] += my_local_stiffness_matrix[0][1];
   global_stiffness_matrix[f.v2][f.v1] += my_local_stiffness_matrix[1][0];
   global_stiffness_matrix[f.v1][f.v3] += my_local_stiffness_matrix[0][2];
   global_stiffness_matrix[f.v3][f.v1] += my_local_stiffness_matrix[2][0];
   global_stiffness_matrix[f.v2][f.v3] += my_local_stiffness_matrix[1][2];
   global_stiffness_matrix[f.v3][f.v2] += my_local_stiffness_matrix[2][1];

   /*
   cout<< "\nGlobal stiffness matrix" << endl;
   cout<< "row " << f.v1 << " columns " << endl;
   cout << f.v1 << '\t' << '\t' << f.v2 << '\t'<< '\t' << f.v3 << endl;
   cout << global_stiffness_matrix[f.v1][f.v1] << '\t' <<  global_stiffness_matrix[f.v1][f.v2] << '\t' << global_stiffness_matrix[f.v1][f.v3] <<endl;
   */

   global_mass_matrix.resize(1039);

   global_mass_matrix[f.v1][f.v1] +=  my_local_mass_matrix[0][0];
   global_mass_matrix[f.v2][f.v2] +=  my_local_mass_matrix[1][1];
   global_mass_matrix[f.v3][f.v3] +=  my_local_mass_matrix[2][2];

   global_mass_matrix[f.v1][f.v2] +=  my_local_mass_matrix[0][1];
   global_mass_matrix[f.v2][f.v1] +=  my_local_mass_matrix[1][0];
   global_mass_matrix[f.v1][f.v3] +=  my_local_mass_matrix[0][2];
   global_mass_matrix[f.v3][f.v1] +=  my_local_mass_matrix[2][0];
   global_mass_matrix[f.v2][f.v3] +=  my_local_mass_matrix[1][2];
   global_mass_matrix[f.v3][f.v2] +=  my_local_mass_matrix[2][1];

   /*cout<< "\nGlobal mass matrix" << endl;
   cout<< "row " << f.v1 << " columns " << endl;
   cout << f.v1 << '\t' << '\t' << f.v2 << '\t'<< '\t' << f.v3 << endl;
   cout << global_mass_matrix[f.v1][f.v1] << '\t' <<  global_mass_matrix[f.v1][f.v2] << '\t' << global_mass_matrix[f.v1][f.v3] <<endl;
   */
}

void Matrix_Generator::print_stiffness_matrix()
{

      ofstream file_A("A.txt");
      if(file_A.is_open())
      {
      for(size_t i=0;i<1039;i++)
        for(size_t j=0;j<1039;j++)
        {
        if(global_stiffness_matrix[i][j]!=0)
            file_A<<i<<"\t"<< j<<"\t"<<global_stiffness_matrix[i][j]<<"\n";
        }
      }
    else {cout<<"unable to open file"<<endl;}

file_A.close();
}

void Matrix_Generator::print_mass_matrix()
{

      ofstream file_M("M.txt");
      if(file_M.is_open())
      {
      for(size_t i=0;i<1039;i++)
        for(size_t j=0;j<1039;j++)
        {
        if(global_mass_matrix[i][j]!=0)
        file_M<<i<<"\t"<< j<<"\t"<<global_mass_matrix[i][j]<<"\n";
        }
      }
    else {cout<<"unable to open file"<<endl;}

file_M.close();
}


void Matrix_Generator::generate()
{
    i.process();
    //int count =0;
    for(auto iter=i.F.begin();iter<i.F.end();++iter)
        {

            //if(count<2)
           // {
            local_stiffness_matrix(*iter); //++count;
           // }
           // else
             //   break;
        }
    print_stiffness_matrix();
    print_mass_matrix();

    fillMassVector();
    fillStiffnessVector();
   // printVector();

}
/*
    colM_ stores nonezero column of perticular row
    valueM_ stores nonzero value of respected colM_
    rowM_ stores number of nonzero element in one row

*/
void Matrix_Generator::fillMassVector(void){

real val=0.0,val1=0.0;
intg nzcount=0;
rowM_.push_back(nzcount);

    for(int i=0;i<1039;i++){
        val = global_mass_matrix[i][0];
      for(int j=0;j<1039;j++){

          val1 = global_mass_matrix[i][j+1];

         if(val!=0){
                colM_.push_back(j);
                valueM_.push_back(val);
                nzcount++;
        }
        val = val1;
        }
      rowM_.push_back(nzcount);
    }
}

/*
    colM_ stores nonezero column of perticular row
    valueM_ stores nonzero value of respected colM_
    rowM_ stores number of nonzero element in one row

*/


void Matrix_Generator::fillStiffnessVector(void){

real val=0.0,val1=0.0;
intg nzcount=0;
rowA_.push_back(nzcount);

    for(int i=0;i<1039;i++){
        val = global_stiffness_matrix[i][0];
      for(int j=0;j<1039;j++){

          val1 = global_stiffness_matrix[i][j+1];

         if(val!=0){
                colA_.push_back(j);
                valueA_.push_back(val);
                nzcount++;
        }
        val = val1;
        }
      rowA_.push_back(nzcount);
    }
}



void Matrix_Generator::printVector(void){
/*
    for(auto it=colA_.begin();it!=colA_.end();it++){
        cout<<"col of stiffness matrix is..."<<*it<<endl;
    }
*//*
    for(auto it=rowA_.begin();it!=rowA_.end();it++){
        cout<<"row of stiffness matrix is..."<<*it<<endl;
    }*/
/*
    for(auto it=valueA_.begin();it!=valueA_.end();it++){
        cout<<"value of stiffness matrix is..."<<*it<<endl;
    }
*/


    for(int i=0;i<10;i++){
        cout<<"row of mass matrix is..."<<rowM_[i]<<endl;//"\t value is..."<<valueM_[i]<<endl;
    }

   //cout<<"row first element is..."<<rowM_[j]<<endl;

}


void Matrix_Generator::CGprocess(long double &eph){

   // real eph=0.0;
//step:1   Input
    setLoad();
    setStiffness();

//step:2 Compute residual and direction vector

    residualandDirection();

//step:3 find new u

   real resNorm = normResidual();
   real ro=0.0,tk=0.0,beta=0.0;

  while(resNorm<eph){

        ro = setRo();
        tk = stepSize(ro);
        init_new(tk);
        res_new(tk);
        beta=setBeta(ro);
        setNewdirection(beta);
        resNorm = normResidual();
    }


}


void Matrix_Generator::setLoad(void){
real fval=0.0;
intg end=0,start=0;

    for(int row = 0;row < 1039;row++){
        start = rowM_[row];
        end = rowM_[row+1];

        for(int j=start ; j<end;j++){

            fval += init_vec[colM_[j]]*valueM_[j];

        }
        load_vec.push_back(fval);
        fval = 0.0;
}
}

void Matrix_Generator::setStiffness(void){

real fval=0.0;
intg end=0,start=0;

 for(int row = 0;row < 1039;row++){
       start = rowA_[row];
       end = rowA_[row+1];
          for(int j=start ; j<end;j++){
                fval += init_vec[colA_[j]]*valueA_[j];
                }
            stiff_vec.push_back(fval);
            fval = 0.0;
 }
}

void Matrix_Generator::residualandDirection(void){

 real val=0.0;

    for(int i=0;i<numPoint;i++){
        val=stiff_vec[i]-load_vec[i];
        res_vec.push_back(val);
        dir_vec.push_back(val*(-1));
        val=0.0;
        }
}

real Matrix_Generator::normResidual(void){

    real norm=0.0;
    real resultNorm=0.0;

        for(int i=0;i<numPoint;i++){
            norm+= res_vec[i]*res_vec[i];
        }
            resultNorm = sqrt(norm/res_vec.size());

return resultNorm;
}

real Matrix_Generator::setRo(void){
 //--------------------------- Adk ------------------------
    real fval=0.0;
    intg end=0,start=0;
    real ro=0.0;

        for(int row = 0;row < numPoint;row++){
            start = rowA_[row];
            end = rowA_[row+1];

            for(int j=start ; j<end;j++){

                fval += dir_vec[colA_[j]]*valueA_[j];

            }
            Adk.push_back(fval);
            fval = 0.0;
        }
  //----------------------------ro-------------------------

        for(intg i=0;i<numPoint;i++){
            ro += dir_vec[i]* Adk[i];
        }

return ro;
}

real Matrix_Generator::stepSize(real &ro){

    real val=0.0;

    for(intg i=0;i<numPoint;i++){
        val += res_vec[i]*dir_vec[i];
      }
    tk = (-1)*(val/ro);

return tk;
}

void Matrix_Generator::init_new(real &tk){

 real val=0.0;

    for(int i=0;i<numPoint;i++){

        val = init_vec[i] +  tk*dir_vec[i];
        xk_new.push_back(val);
    }



}

void Matrix_Generator::res_new(real &tk){
    real val=0.0;

       for(int i=0;i<numPoint;i++){

           val = res_vec[i] +  tk*Adk[i];
           rk_new.push_back(val);
       }
}

real Matrix_Generator::setBeta(real &ro){
    real val=0.0;
    real beta=0.0;

    for(int i=0;i<numPoint;i++){
        val+= rk_new[i]*Adk[i];
    }

    beta = val / ro;

return beta;
}

void Matrix_Generator::setNewdirection(real &beta){

    real val=0.0;
       for(int i=0;i<numPoint;i++){

           val = (-1.0)*rk_new[i] +  beta*dir_vec[i];
           dir_new.push_back(val);
       }
}

void Matrix_Generator::CGprint(void){    

    for(int i=0;i<numPoint;i++){
        cout<<stiff_vec[i]<<endl;
    }

}






