#ifndef G4JPRIME_H
#define G4JPRIME_H
using namespace std;


vector<double> G4Jprime(bundle &vars);
vector<double> G4Jprime(bundle &vars, bundle &varied_vars, int varied_param_index, int offset);

#endif
