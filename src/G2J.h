#ifndef G2J_H
#define G2J_H
using namespace std;


vector<double> G2J(bundle &vars);
vector<double> G2J(bundle &vars, bundle &varied_vars, int varied_param_index, int offset);

#endif
