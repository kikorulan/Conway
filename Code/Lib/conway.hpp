/*=============================================================================

  CONWAY'S GAME OF LIFE

  Copyright (C) 2017 Kiko Rul·lan

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef gridRT_hpp
#define gridRT_hpp
#include <cstdlib>
#include <memory>
#include <vector>

#include <armadillo>

using namespace arma;

class Conway {
    /*=======================================================================
    ===================                          ============================
    ===================           DATA           ============================ 
    ===================                          ============================
    =========================================================================*/
    private:
        // Domain definition
        int Nx, Ny; // Number of points for the grid in the x and y axis, respectively
        matP domain; // Domain definition

    /*=======================================================================
    ===================                          ============================
    ===================         FUNCTIONS        ============================ 
    ===================                          ============================
    =========================================================================*/
    public:
        /*=======================================================================
        ======     Constructors
        =========================================================================*/
        Conway(int const& Nx, int const& Ny);
            /* CONWAY creates a CONWAY object initialising it with the given Nx, Ny
                INPUTS
                    Nx: number of points in the x axis
                    Ny: number of points in the y axis
                OUTPUTS
                    CONWAY object
                EXCEPTIONS
                    Invalid argument exception when:
                        - Nx or Ny are lower than 1
            */
        Conway(std::string &iFileName);
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
        ======     Setters
        =========================================================================*/
    protected:
        void setDimensions(int const& Nx, double const& dx, int const& Ny, double const& dy);
            /* SETDIMENSIONS assigns the dimensions to the CONWAY object. Creates the domain matrix
                 INPUTS
                    Nx: number of points in the x axis
                    Ny: number of points in the y axis
                OUTPUTS
                    -
                EXCEPTIONS
                    Not safe
            */
    public:
        void setDomain(matP &M);
            /* SETC assigns the matrix pointer M to the domain matrix 
                INPUTS
                    M: matrix pointer 
                OUTPUTS
                    -
                EXCEPTIONS
                    Not save
            */

        /*=======================================================================
        ======     Getters
        =========================================================================*/
    public:
        void getDimensions(void);
            // GETDIMENSIONS writes in the standard output the dimensions of the grid
        int getNX(void);
            /* GETNX returns the value of the member Nx
                INPUTS
                    -
                OUTPUTS
                    Nx: number of points along the x coordinate
            */
        int getNY(void);
            /* GETNY returns the value of the member Ny
                INPUTS
                    -
                OUTPUTS
                    Ny: number of points along the y coordinate
            */

        /*=======================================================================
        ======     Load data from file stream
        =========================================================================*/
    public:
        void loadDomain(std::string &iFileName);
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

};

} 

#endif
