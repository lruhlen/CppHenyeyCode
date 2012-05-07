#ifndef G2JPRIME_H
#define G2JPRIME_H
using namespace std;


vector<double> G2Jprime(bundle &vars);
vector<double> G2Jprime(bundle &vars, bundle &varied_vars, int varied_param_index, int offset);

#endif
