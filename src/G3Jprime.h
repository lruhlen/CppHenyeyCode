#ifndef G3JPRIME_H
#define G3JPRIME_H
using namespace std;


vector<double> G3Jprime(bundle vars);
vector<double> G3Jprime(bundle vars, bundle varied_vars, int varied_param_index, int offset);

#endif
