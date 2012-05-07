#ifndef PRINTMATRIX_H
#define PRINTMATRIX_H
#include "global.h"
using namespace std;

void printMatrix(struct vec3d &matrix); 
void printMatrix (vector<vector<double> > &matrix);
void printMatrix (vector<vector<int> > &matrix);
void printMatrix (vector<vector<float> > &matrix);
void printMatrix (vector<vector<char> > &matrix);
void printMatrix (vector<vector<long> > &matrix);
void printMatrix (vector<vector<bool> > &matrix);

void printMatrix (vector<double>  &matrix);
void printMatrix (vector<int>  &matrix);
void printMatrix (vector<float>  &matrix);
void printMatrix (vector<char>  &matrix);
void printMatrix (vector<long> &matrix);
void printMatrix (vector<bool>  &matrix);

void printMatrix (double &matrix);
void printMatrix( int &matrix);
void printMatrix( float &matrix);
void printMatrix( char &matrix);
void printMatrix( long &matrix);
void printMatrix( bool &matrix);

#endif
