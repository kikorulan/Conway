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

#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char* argv[])
{
/*=======================================================================
===================   CHECK USAGE AND INPUT FILES     =================== 
=========================================================================*/
    // Tell the user how to run the program
    if (argc != 3) {
        cerr << "USAGE: " << argv[0] << " input_file_dimensions input_file_doman" << endl;
        cerr << endl;
        cerr << "    INPUT_FILE_DIMENSIONS format:" << endl;
        cerr << "        Nx Ny nSteps" << endl;
        cerr << endl;
        cerr << "    INPUT_FILE_DOMAIN format:" << endl;
        cerr << "        a_{1,1}  ... a_{1,Ny}" << endl;
        cerr << "           ...   ...  ... " << endl;
        cerr << "        a_(Nx,1} ... a_{Nx,Ny1}" << endl;
        cerr << "    where A is the matrix that defines the initial state of the matrix." << endl;
        cerr << endl;
        return 1;
    }

/*=======================================================================
===================   DEFINE GRID AND SOURCES         =================== 
=========================================================================*/
    std::string dimensionsFile;
    dimensionsFile = argv[1];
    cubeIP domain(newConway(dimensionsFile).release());

    std::string domainFile;
    domainFile = argv[2];
    loadDomain(domain, domainFile);

/*=======================================================================
===================   COMPUTE STEPS AND WRITE OUTPUT  =================== 
=========================================================================*/    
    computeNSteps(domain);
    
    return 0;
}
