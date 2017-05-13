/*=============================================================================

  RUNCONWAY: Run Conway's Game of Life

  Copyright (C) 2017 Kiko Rul·lan

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include <conway.hpp>
#include <basicTypes.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>
#include <memory>

#include <armadillo>

using namespace std;
using namespace arma;

typedef std::unique_ptr<Conway> Conway_p;

int main(int argc, char* argv[])
{
/*=======================================================================
===================   CHECK USAGE AND INPUT FILES     =================== 
=========================================================================*/
    // Tell the user how to run the program
    if (argc != 4) {
        cerr << "USAGE: " << argv[0] << " input_file_dimensions input_file_doman number_step" << endl;
        cerr << endl;
        cerr << "    INPUT_FILE_DIMENSIONS format:" << endl;
        cerr << "        Nx Ny" << endl;
        cerr << endl;
        cerr << "    INPUT_FILE_DOMAIN format:" << endl;
        cerr << "        a_{1,1}  ... a_{1,Ny}" << endl;
        cerr << "           ...   ...  ... " << endl;
        cerr << "        a_(Nx,1} ... a_{Nx,Ny1}" << endl;
        cerr << "    where A is the matrix that defines the initial state of the matrix." << endl;
        cerr << endl;
        cerr << "    NUMBER_STEPS:" << endl;
        cerr << "    Corresponds to the number of steps to compute." << endl;
        cerr << endl;
        return 1;
    }

/*=======================================================================
===================   DEFINE GRID AND SOURCES         =================== 
=========================================================================*/
    std::string dimensionsFile;
    dimensionsFile = argv[1];
    Conway_p C(new Conway(dimensionsFile));

    std::string domainFile;
    domainFile = argv[2];
    C->loadDomain(domainFile);

/*=======================================================================
===================   COMPUTE STEPS AND WRITE OUTPUT  =================== 
=========================================================================*/    
    int nSteps;
    std::stringstream(argv[3]) >> nSteps;
    C->computeNSteps(nSteps);
    
    std::cout << -3%2 << std::endl;
    return 0;
}
