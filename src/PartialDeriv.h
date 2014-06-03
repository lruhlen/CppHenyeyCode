#ifndef PARTIALDERIV_H
#define PARTIALDERIV_H


vector<double> PartialDeriv(vector<double> (*funct)(bundle &inputs), bundle vars, int OneToVary, int shift );



#endif
