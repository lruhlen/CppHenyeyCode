#include <iostream>
#include <vector>
#include "global.h"
using namespace std;

double dotProduct(vector<double> &vec1, vector<double> &vec2){
  
  double result=0;
  int n_elements = vec1.size();
  int m_elements = vec2.size();
  
  if ( n_elements != m_elements )
    {
      cout<<"ERROR: These vectors are not the same length.\n";
      result = -1;
    }
  else if ( (n_elements < 1) || (m_elements < 1) ) {
    cout<<"ERROR: One of these vectors has zero lenght!\n";
    result = -1;
  }
  else{

    for(int i=0; i<n_elements; i++){
      result += (vec1[i]*vec2[i]);
    }

  }

 return result;
}
