/*=============================================================================

  CONWAY'S GAME OF LIFE

  Copyright (C) 2017 Kiko Rul·lan

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "basicTypes.hpp"
#ifndef Conway_hpp
#define Conway_hpp
#include <cstdlib>
#include <memory>
#include <vector>

#include <armadillo>

using namespace arma;

/*=======================================================================
======     Constructors
=========================================================================*/
matIP newConway(std::string &iFileName);
    /* GRIDRT opens a file under the given name and creates a GRIDRT object initialising it 
       from the data read from the file. Calls the previous GridRT constructor after reading data.
        INPUTS
            iFile: input file with the following line at the given file position:
                    Nx Ny
        OUTPUTS
            GRIDRT object
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

void getDimensions(matIP &domain);
    // GETDIMENSIONS writes in the standard output the dimensions of the grid

/*=======================================================================
======     Compute CGOL
=========================================================================*/

int countAliveNeigh(matIP &domain, int const& coordX, int const& coordY);
    /* COUNTALIVENEIGHBOURS returns the number of alive neighbours for the given coordinate
        INPUTS
            coordX: x coordinate of the point to compute the neighbours
            coordY: y coordinate of the point to compute the neighbours
        OUTPUTS
            alive: number of alive neighbours
    */

void updatePixel(matIP &domain, matIP &domainNext, int const& coordX, int const& coordY);
    /* UPDATEPIXEL computes the new state of Conway's Game of Life for the given pixel
        INPUTS
            coordX: x coordinate of the point to update
            coordY: y coordinate of the point to update
        OUTPUTS
            -
    */

void updateMatrix(matIP &domain, matIP &domainNext);
    /* UPDATEMATRIX computes the new state of Conway's Game of Life for the domain
        INPUTS
            coordX: x coordinate of the point to update
            coordY: y coordinate of the point to update
        OUTPUTS
            -
    */
void computeNSteps(matIP &domain, int const& nSteps);
    /* COMPUTENSTEPS computes and writes nSteps steps of CGOL
        INPUTS
            nSteps: number of steps to compute
        OUTPUTS
            -
    */

/*=======================================================================
======     Load data from file stream
=========================================================================*/

void loadDomain(matIP &domain, std::string &iFileName);
    /* LOADDOMAIN opens a file under the given name and loads from it the data into the C matrix
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

void writeDomain(matIP &domain, int const& nStep);
    /* WRITEDOMAIN opens a file under the given name and writes the current state of the domain
        INPUTS
            nStep: step number
        OUTPUTS
            File in output_data with name MatrixN.dat, where N is the number of step
        EXCEPTIONS
            Run time error in the following cases:
                - Problem opening file for given file name
    */
void writeDomain(matIP &domain);
    /* WRITEDOMAIN writes the domain in the standard output
        INPUTS
            -
        OUTPUTS
            -

*/

#endif
