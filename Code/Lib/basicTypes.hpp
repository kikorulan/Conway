/*=============================================================================

  MYPROJECT: A software package for whatever.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef basicTypes_hpp
#define basicTypes_hpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <memory>
#include <limits>

#include <armadillo>

using namespace arma;

// Limits
typedef std::numeric_limits<double> lim;

// Vector 
typedef std::vector<double> vec_old;
typedef std::vector<int> vecI;
typedef std::unique_ptr<vecI> vecIP;

// Matrix 
typedef std::vector<vec_old> Matrix;
typedef std::unique_ptr<Matrix> MatrixP;


// Armadillo
typedef std::unique_ptr<rowvec> rowvecP;
typedef std::unique_ptr<vec> vecP;
typedef std::unique_ptr<mat> matP;
typedef std::unique_ptr<cube> cubeP;

typedef Row<int> rowvecI;
typedef std::unique_ptr<rowvecI> rowvecIP;
typedef Mat<int> matI;
typedef std::unique_ptr<matI> matIP;
typedef Cube<int> cubeI;
typedef std::unique_ptr<cubeI> cubeIP;
#endif
