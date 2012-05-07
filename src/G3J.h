#ifndef G3J_H
#define G3J_H
using namespace std;


vector<double> G3J(bundle &vars);
vector<double> G3J(bundle &vars, bundle &varied_vars, int varied_param_index, int offset);

#endif
