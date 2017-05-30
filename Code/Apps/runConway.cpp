/*=============================================================================

  RUNCONWAY: Run Conway's Game of Life

  Copyright (C) 2017 Kiko Rul·lan

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#define N 512

#include <conway.hpp>
//#include <basicTypes.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>

int main(int argc, char* argv[])
{
/*=======================================================================
===================   CHECK USAGE AND INPUT FILES     =================== 
=========================================================================*/
    // Tell the user how to run the program
    if (argc != 3) {
        std::cerr << "USAGE: " << argv[0] << " input_file_dimensions input_file_doman" << std::endl;
        std::cerr << std::endl;
        std::cerr << "    INPUT_FILE_DIMENSIONS format:" << std::endl;
        std::cerr << "        Nx Ny nSteps" << std::endl;
        std::cerr << std::endl;
        std::cerr << "    INPUT_FILE_DOMAIN format:" << std::endl;
        std::cerr << "        a_{1,1}  ... a_{1,Ny}" << std::endl;
        std::cerr << "           ...   ...  ... " << std::endl;
        std::cerr << "        a_(Nx,1} ... a_{Nx,Ny1}" << std::endl;
        std::cerr << "    where A is the matrix that defines the initial state of the matrix." << std::endl;
        std::cerr << std::endl;
        return 1;
    }

/*=======================================================================
===================   DEFINE DOMAIN                   =================== 
=========================================================================*/
    // Create initial matrix
    std::string dimensionsFile;
    dimensionsFile = argv[1];
    int *domain = newConway(dimensionsFile);
    
    // Load initial domain
    std::string domainFile;
    domainFile = argv[2];
    loadDomain(domain, domainFile);

/*=======================================================================
===================   COMPUTE STEPS AND WRITE OUTPUT  =================== 
=========================================================================*/    
    // Compute CGOL
    computeNSteps(domain);
    // Write to file
    writeDomain(domain);
   
    // Free memory
    free(domain);
    return 0;
}
