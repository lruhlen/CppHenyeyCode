#include <iostream>
#include <vector>
#include "global.h"
using namespace std;


void printVector(vector<double> &vec)
{
   for ( int i = 0; i < int(vec.size()); i++ ){
     printf("%-12.5g",vec[i]);
   }
   cout << endl;

}

void printVector(vector<double> &vec, int start, int stop)
{
  if (stop < 0)
    {
      stop = int(vec.size()) + stop;
    }

   for ( int i = start; i < stop; i++ ){
     printf("%-12.5g",vec[i]);
   }
   cout << endl;

}

void printVector(vector<long> &vec)
{
   for ( int i = 0; i < int(vec.size()); i++ ){
 	 cout << vec[i] << "\t";
   }

    cout << endl;
}
void printVector(vector<int> &vec)
{
   for ( int i = 0; i < int(vec.size()); i++ ){
 	 cout << vec[i] << "\t";
   }

    cout << endl;
}

void printVector(vector<char> &vec)
{
   for ( int i = 0; i < int(vec.size()); i++ ){
 	 cout << vec[i] << "\t";
   }

    cout << endl;
}
void printVector(vector<float> &vec)
{
   for ( int i = 0; i < int(vec.size()); i++ ){
 	 cout << vec[i] << "\t";
   }
    cout << endl;
    cout << endl;
}
void printVector(vector<bool> &vec)
{
   for ( int i = 0; i < int(vec.size()); i++ ){
 	 cout << vec[i] << "\t";
   }

    cout << endl;
}
