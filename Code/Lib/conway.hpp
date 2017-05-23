/*=============================================================================

  CONWAY'S GAME OF LIFE

  Copyright (C) 2017 Kiko Rul·lan

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "basicTypes.hpp"
#ifndef Conway_hpp
#define Conway_hpp
#include <cstdlib>
//#include <memory>
#include <vector>

#include <armadillo>

#include <boost/mpi.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/serialization/vector.hpp>

/*=======================================================================
====== Boost serialization
=========================================================================*/

class conwaySubdomain{
/* CONWAYSUBDOMAIN 
    This class serializes a matrix of integers to be sent via boost-mpi.
    It is used to send the subdomains from the workers to the master thread.
*/
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

class conwayBoundary{
/* CONWAYSUBDOMAIN 
    This class serializes a vector of integers to be sent via boost mpi.
    It is used to send the boundaries between workers.
*/
private:
 friend class boost::serialization::access;

template<class Archive>
 void serialize(Archive &ar, const unsigned int version)
 {
    ar & col; 
 }

public:
 std::vector<int> col;

 conwayBoundary() {};
 conwayBoundary(std::vector<int> v) :col(v) {}
};

/*=======================================================================
======     Constructors
=========================================================================*/
cubeIP newConway(std::string &iFileName);
    /* NEWCONWAY opens a file under the given name and creates a CGOL object initialising it 
       from the dimensions read from the file.
        INPUTS
            iFile: input file with the following line at the given file position:
                    Nx Ny nSteps
        OUTPUTS
            CGOL object
        EXCEPTIONS
            Run time exception in the following cases:
                - Problem opening given file name
                - Incorrect format
    */


/*=======================================================================
======     Getters
=========================================================================*/

void getDimensions(cubeIP &domain);
    // GETDIMENSIONS writes in the standard output the dimensions of the grid

/*=======================================================================
======     Compute CGOL
=========================================================================*/

int countAliveNeigh(cubeIP &domain, int const& coordX, int const& coordY, int const& step);
    /* COUNTALIVENEIGHBOURS returns the number of alive neighbours for the given coordinate
        INPUTS
            domain: CGOL domain
            coordX: x coordinate of the point to compute the neighbours
            coordY: y coordinate of the point to compute the neighbours
            step: number of step to compute
        OUTPUTS
            alive: number of alive neighbours
    */

void updatePixel(cubeIP &domain, int const& coordX, int const& coordY, int const& step);
    /* UPDATEPIXEL computes the new state of Conway's Game of Life for the given pixel
        INPUTS
            domain: CGOL domain
            coordX: x coordinate of the point to update
            coordY: y coordinate of the point to update
            step: number of step to compute
        OUTPUTS
            -
    */

void updateMatrix(cubeIP &domain, int const& step);
    /* UPDATEMATRIX computes the new state of Conway's Game of Life for the domain
        INPUTS
            domain: CGOL domain
            step: number of step to compute
        OUTPUTS
            -
    */

void computeNSteps(cubeIP &domain);
    /* COMPUTENSTEPS computes and writes nSteps steps of CGOL
        INPUTS
            domain: CGOL domain
        OUTPUTS
            -
    */

/*=======================================================================
======     Load data from file stream
=========================================================================*/

void loadDomain(cubeIP &domain, std::string &iFileName);
    /* LOADDOMAIN opens a file under the given name and loads from it the data into the domain initial matrix
        INPUTS
            domain: CGOL domain
            iFileName: input file name with the initial state
                Each row contains Ny values. There should be Nx rows
        OUTPUTS
            -
        EXCEPTIONS
            Run time error in the following cases:
                - Problem opening file for given file name
                - Incorrect format
                - Invalid value for a pixel in the domain
    */

/*=======================================================================
======     Write to output
=========================================================================*/

void writeDomain(cubeIP &domain);
    /* WRITEDOMAIN opens a file under the given name and writes the current state of the domain
        INPUTS
            nStep: step number
        OUTPUTS
            File in output_data with name MatrixN.dat, where N is the number of step
        EXCEPTIONS
            Run time error in the following cases:
                - Problem opening file for given file name
    */

void writeDomain(cubeIP &domain, int nStep, std::ofstream &outputFile);

/*=======================================================================
======     MPI Communication
=========================================================================*/

void sendDimensions(cubeIP &domain);
    /* SENDDIMENSIONS sends the dimensions from the master to the other threads of the corresponding subdomains
        INPUTS
            domain: CGOL domain
        OUTPUTS
            -
    */

void sendSubdomains(cubeIP &domain);
    /* SENDSUBDOMAIN sends the corresponding initial subdomains from the master to the other threads
        INPUTS
            domain: CGOL domain
        OUTPUTS
            -
    */

void receiveSubdomain(cubeIP &domain);
    /* RECEIVESUBDOMAIN receives the corresponding initial subdomain from the master thread
        INPUTS
            domain: CGOL domain
        OUTPUTS
            -
    */

void sendSubdomainMaster(cubeIP &domain, int nStep);
    /* SENDSUBDOMAINMASTER sends the subdomain for step nStep from the worker to the master
        INPUTS
            domain: CGOL domain
        OUTPUTS
            -
    */


void receiveSubdomainsMaster(cubeIP &domain, int nStep);
    /* RECEIVESUBDOMAINMASTER receives the corresponding subdomains for step nStep from the worker threads
        INPUTS
            domain: CGOL domain
        OUTPUTS
            -
    */

void sendBoundaries(cubeIP &domain, int nStep);
    /* SENDBOUNDARIES sends the boundaries to the neighbour worker threads for step nStep
        INPUTS
            domain: CGOL domain
        OUTPUTS
            -
    */

void receiveBoundaries(cubeIP &domain, int nStep);
    /* SENDBOUNDARIES receives the boundaries from the neighbour worker threads for step nStep
        INPUTS
            domain: CGOL domain
        OUTPUTS
            -
    */

#endif
