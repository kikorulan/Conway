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

class conwaySubdomain
{
private:
 friend class boost::serialization::access;

template<class Archive>
 void serialize(Archive &ar, const unsigned int version)
 {
    for (int i = 0; i < subdomain.size(); i++)
        ar & boost::serialization::make_array(subdomain[i].data(), subdomain[i].size());
    //ar & subdomain; 
 }

public:
 std::vector< std::vector<int> > subdomain;

 conwaySubdomain() {};
 conwaySubdomain(std::vector< std::vector<int> > sd) :subdomain(sd) {}
};


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
        std::vector<long long unsigned int> dimensions(3);
        long long unsigned int nCols = ceil((float)(*domain).n_cols/(world.size()-1));
        dimensions = {(*domain).n_rows, nCols, (*domain).n_slices};
        for (int n = 1; n <= world.size()-2;  n++)
            world.send(n, 0, dimensions);            
        dimensions[1] = (*domain).n_cols - ceil((float)(*domain).n_cols/(world.size()-1))*(world.size()-2) + 2; // remaining 
        world.send(world.size()-1, 0, dimensions);
    
        // Send subdomain to other threads
        std::vector< std::vector<int> > subdomain(3, std::vector<int>(3));
        subdomain[1][1] = 10;
        subdomain[2][1] = 20;

        conwaySubdomain cSD(subdomain);
 
        for (int n = 1; n <= world.size()-1;  n++)
            world.send(n, 1, cSD);            
        // Load domain
        std::string domainFile;
        domainFile = argv[2];
        loadDomain(domain, domainFile);
    
    /*=======================================================================
    ===================   COMPUTE STEPS AND WRITE OUTPUT  =================== 
    =========================================================================*/    
        computeNSteps(domain);
        
    }

    else {
        // Receive dimensions of subdomains
        std::vector<long long unsigned int> dimensions(3);
        world.recv(0, 0, dimensions);

        std::cout << "Process " << world.rank() << " dimensions: " <<
                    dimensions[0] << " " << dimensions[1] << " " << dimensions[2] << std::endl; 


        // Receive subdomain    
        std::vector< std::vector<int> > subdomain(3, std::vector<int>(3));
        conwaySubdomain cSD(subdomain);
        world.recv(0, 1, cSD);
        std::cout << "Process " << world.rank() << " subdomain: " << std::endl;

        for (int j = 0; j <= 2; j++){
            for (int i = 0; i <= 2; i++){
                    std::cout << cSD.subdomain[i][j] << " ";
            }
            std::cout << std::endl;
        }

        
    }

    return 0;
}
