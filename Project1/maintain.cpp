#pragma once
/*
 * This file is part of Connect4 Game Solver <http://connect4.gamesolver.org>
 * Copyright (C) 2007 Pascal Pons <contact@gamesolver.org>
 *
 * Connect4 Game Solver is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Connect4 Game Solver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Connect4 Game Solver. If not, see <http://www.gnu.org/licenses/>.
 */


#include "maintain.h"

//#include "solver.hpp"
//#include <iostream>
//#include <chrono>


//using namespace GameSolver::Connect4;


/*
 * Main function.
 * Reads Connect 4 positions, line by line, from standard input
 * and writes one line per position to standard output containing:
 *  - score of the position
 *  - number of nodes explored
 *  - time spent in microsecond to solve the position.
 *
 *  Any invalid position (invalid sequence of move, or already won game)
 *  will generate an error message to standard error and an empty line to standard output.
 */



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
      //std::chrono::steady_clock::time_point This = std::chrono::steady_clock::now();
      int score = solver.solve(P, weak);
      //std::chrono::steady_clock::time_point That = std::chrono::steady_clock::now();
      //std::chrono::nanoseconds now = This - That;
      std::cout << line << " " << score << " " << solver.getNodeCount() << " " ; //<< now.count();
      std::cout << std::endl;
      return score;
  }
}


