#pragma once

#include "maintain.h"

//#include "solver.hpp"
//#include <iostream>
//#include <chrono>


//using namespace GameSolver::Connect4;



int maintain(std::string line) {

    GameSolver::Connect4::Solver solver;

  bool weak = false;
  
  GameSolver::Connect4::Position P;
    if(P.play(line) != line.size())
    {
        std::cout << "error aayo hai" << std::endl;
    }
    else
    {
      solver.reset();
      int score = solver.solve(P, weak);
      std::cout << line << " " << score << " " << solver.getNodeCount() << " " ; //<< now.count();
      std::cout << std::endl;
      return score;
  }
}


