/*=============================================================================
  CONWAY'S GAME OF LIFE
  Copyright (C) 2017 Kiko Rul·lan
  See LICENSE.txt in the top level directory for details.
=============================================================================*/

#ifndef Conway_hpp
#define Conway_hpp
#include <cstdlib>
//#include <memory>
#include <vector>
#include <string>

/*=======================================================================
======     Constructors
=========================================================================*/
int * newConway(std::string &iFileName);
    /* NEWCONWAY opens a file under the given name and creates a CGOL matrix initialising it 
       from the data read from the file.
        INPUTS
            iFile: input file with the following line at the given file position:
                    Nx Ny
        OUTPUTS
            CGOL matrix
        EXCEPTIONS
            Run time exception in the following cases:
                - Problem opening given file name
                - Incorrect format
            Invalid argument exception when:
                - Nx or Ny are lower than 1
    */

/*=======================================================================
======     Getters
=========================================================================*/

void getDimensions(int *domain);
    // GETDIMENSIONS writes in the standard output the dimensions of the grid

/*=======================================================================
======     Compute CGOL
=========================================================================*/

__global__ void updateMatrix(int *domain, int *neigh);
    /* UPDATEMATRIX computes the new state of Conway's Game of Life for the domain
        INPUTS
            coordX: x coordinate of the point to update
            coordY: y coordinate of the point to update
            step: number of step to compute
        OUTPUTS
            -
    */

__global__ void countAliveNeigh(int *domain, int *neigh, int nRows, int nCols);
    /* COUNTALIVENEIGH returns the number of alive neighbours for the given coordinate
        INPUTS
            domain: CGOL matrix
            coordX: x coordinate of the point to compute the neighbours
            coordY: y coordinate of the point to compute the neighbours
            step: number of step to compute
        OUTPUTS
            alive: number of alive neighbours
    */

void computeNSteps(int *domain);
    /* COMPUTENSTEPS computes and writes nSteps steps of CGOL
        INPUTS
            - 
        OUTPUTS
            -
    */

/*=======================================================================
======     Load data from file stream
=========================================================================*/

void loadDomain(int *domain, std::string &iFileName);
    /* LOADDOMAIN opens a file under the given name and loads from it the data into the CGOL matrix
        INPUTS
            iFileName: input file name with the C matrix
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

void writeDomain(int *domain);
    /* WRITEDOMAIN saves the domain in the folder "output_data" under the name "CGOL.dat"
        INPUTS
            domain: CGOL matrix
        OUTPUTS
            -
    */

void writeDomain(int *domain, int step);
    /* WRITEDOMAIN writes the domain step in the standard output
        INPUTS
            domain: CGOL matrix
            step: step to write output
        OUTPUTS
            -
    */

#endif
