#ifndef G4J_H
#define G4J_H
using namespace std;


vector<double> G4J(bundle &vars);
vector<double> G4J(bundle &vars, bundle &varied_vars, int varied_param_index, int offset);

#endif
