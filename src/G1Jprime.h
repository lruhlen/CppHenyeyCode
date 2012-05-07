#ifndef G1JPRIME_H
#define G1JPRIME_H
using namespace std;


vector<double> G1Jprime(bundle &vars);

vector<double> G1Jprime(bundle &vars, bundle &varied_vars, int varied_param_index, int offset);

#endif
