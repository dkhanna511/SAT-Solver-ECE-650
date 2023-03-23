#include<iostream>
#include<memory>
#include "satSolver.h"

#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // your code starts here
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
  
  std::vector<Minisat::Lit> minisatObjectList;
  
  for(int i = 0; i < numVar-1; i++)
  {
    minisatObjectList.push_back(Minisat::mkLit(solver->newVar()));
  }
  
  
  for (int i = 0; i < cnf.size(); i++)
  {
    Minisat::vec<Minisat::Lit> clauseVec; // to store each clause

    for(int j = 0; j < cnf[i].size(); j++)
    {
      
      if (cnf[i][j] < 0){
        // minisatObject[i-1] = miniSatObject[i-1];
        clauseVec.push(~minisatObjectList[-cnf[i][j]-1]);
      }
      else {
        clauseVec.push(minisatObjectList[cnf[i][j]-1]);
      }
    }
    solver->addClause(clauseVec);
  }
  bool res = solver->solve();

  solver.reset (new Minisat::Solver());

  return res;
}
