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

#include <boost/mpi.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/serialization/vector.hpp>


int main(int argc, char* argv[])
{

    boost::mpi::environment env;
    boost::mpi::communicator world;

    if (world.rank() == 0){
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
            cerr << "        a_(Nx,1} ... a_{Nx,Ny}" << endl;
            cerr << "    where A is the matrix that defines the initial state of the matrix." << endl;
            cerr << endl;
            return 1;
        }
    
    /*=======================================================================
    ===================   DEFINE GRID AND SOURCES         =================== 
    =========================================================================*/
        // Load dimensions
        std::string dimensionsFile;
        dimensionsFile = argv[1];
        cubeIP domain(newConway(dimensionsFile).release());

        // Send dimensions to other threads
        sendDimensions(domain);

        // Load domain
        std::string domainFile;
        domainFile = argv[2];
        loadDomain(domain, domainFile);

        // Send subdomains to the other threads
        sendSubdomains(domain);
    
    /*=======================================================================
    ===================   COMPUTE STEPS AND WRITE OUTPUT  =================== 
    =========================================================================*/    
        
        // Save the data
        std::ofstream outputFile;
        std::string str = "output_data/CGOL.dat";
        //std::string str = "output_data/Source" + std::to_string(world.rank()) + ".dat";
    
        outputFile.open(str);
        if (outputFile.fail()){
            std::ostringstream msg;
            msg << "writeDomain(): Opening file '" << str
                << "' failed, could not be created.";
            throw std::runtime_error(msg.str());
        }

        writeDomain(domain, 0, outputFile);
        for (int n = 1; n < (*domain).n_slices; n++){
            receiveSubdomainsMaster(domain, n);
            writeDomain(domain, n, outputFile);
        }
        
        outputFile.close();
    }

    else {
        // Receive dimensions of subdomains
        std::vector<long long unsigned int> dimensions(3);
        world.recv(0, 0, dimensions);

        // Create subdomain for this thread
        cubeIP subdomain(new cubeI(dimensions[0], dimensions[1], dimensions[2]));
        // Receive subdomain    
        receiveSubdomain(subdomain);

        // Compute steps
        for (int n = 0; n < dimensions[2]-1; n++){
            sendBoundaries(subdomain, n);   // Send boundaries
            receiveBoundaries(subdomain, n);// Receive boundaries
            updateMatrix(subdomain, n);     // Compute step
            sendSubdomainMaster(subdomain, n+1); // Send subdomain to master
        }


    }

    return 0;
}
