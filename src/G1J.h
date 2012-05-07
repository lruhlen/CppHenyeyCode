#ifndef G1J_H
#define G1J_H
using namespace std;


vector<double> G1J(bundle &vars);

vector<double> G1J(bundle &vars, bundle &varied_vars, int varied_param_index, int offset);

#endif
