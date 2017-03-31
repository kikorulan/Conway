/*=============================================================================

  CONWAY'S GAME OF LIFE

  Copyright (C) 2017 Kiko Rul·lan

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "conway.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <memory>
#include <armadillo>


using namespace arma;

/*=======================================================================
====== Constructors
=========================================================================*/

// Constructor for given dimensions 
Conway::Conway(int const& Nx, int const& Ny) {
    // Check input values
    if (Nx < 1 || Ny < 1)
        throw std::invalid_argument("CONWAY object not created. Invalid value(s) for grid dimensions.\n");
    setDimensions(Nx, Ny);
    // Message: CONWAY created
    std::cout << "CONWAY created." << std::endl;
    getDimensions();
}

// Constructor from input file stream iFile 
Conway::Conway(std::string &iFileName){
    std::ifstream iFile;
    iFile.open(iFileName);
    if (iFile.fail()){
        std::ostringstream msg;
        msg << "Conway(): Opening file '" << iFileName
            << "' failed, it either doesn't exist or is not accessible.";
        throw std::runtime_error(msg.str());
    }
    int Nx = 0, Ny = 0;

    std::string str;
    std::stringstream ss;
    getline(iFile, str);
    ss << str;
    ss >> Nx >> Ny;
    ss.clear();

    // Check input values
    if (Nx < 1 || Ny < 1 )
        throw std::invalid_argument("CONWAY not created. Invalid value(s) for grid dimensions.\n");

    setDimensions(Nx, Ny);
    // Message: CONWAY created
    std::cout << "CONWAY created." << std::endl;
    getDimensions();
}

/*=======================================================================
====== Setters
=========================================================================*/
// Set the dimensions of the CONWAY domain
void Conway::setDimensions(int const& Nx, int const& Ny){
    // Assign values
    Conway::Nx = Nx; // Assign Nx points at the x axis
    Conway::Ny = Ny; // Assign Ny points at the y axis
    domain.reset(new mat(Nx, Ny)); // Create domain matrix 
    (*domain).fill(datum::nan);
}

// Set domain equal to the given matrix
void Conway::setDomain(matP &M){
    domain.reset(M.release());
}

/*=======================================================================
====== Getters for c and n
=========================================================================*/
// Get the dimensions at the standard output
void Conway::getDimensions(void){
    std::cout << "Dimensions:" << std::endl;
    std::cout << "    Nx: " << Nx << std::endl;
    std::cout << "    Ny: " << Ny << std::endl;
}

// Get Nx
int Conway::getNX(void) { return Nx; }

// Get Ny
int Conway::getNY(void) { return Ny; }

/*============================================================================
==============                                            ====================
==============         Load and write data                ====================
==============                                            ====================
==============================================================================*/

/*=======================================================================
====== Load data from file stream
=========================================================================*/
/* Load C matrix from input file */
void Conway::loadDomain(std::string &iFileName){
    // Open input file
    std::ifstream iFile;
    iFile.open(iFileName);
    if (iFile.fail()){
        std::ostringstream msg;
        msg << "loadDomain(): Opening file '" << iFileName
            << "' failed, it either doesn't exist or is not accessible.";
        throw std::runtime_error(msg.str());
    }

    std::string str;
    std::stringstream ss;
    matP domain; 
  
    // C matrix
    int nCol = 0, nRow = 0;
    double val;
    domain.reset(new mat(Nx, Ny));
    domain->fill(datum::nan);
    while(getline(iFile, str)){
        nCol = 0;
        ss << str;
        while(ss >> val){
            if (nCol < Ny && nRow < Nx)
                if(val == 1 || val == 0)
                    (*domain)(nRow, nCol) = val;
                else
                    throw std::invalid_argument(std::string("Error: Wrong value for domain matrix.\n"));
            else
                throw std::invalid_argument(std::string("Error: Wrong dimension for domain matrix.\n"));
            nCol++;
        }
        ss.clear();
        nRow++;
    }
    
    if (nCol < Ny || nRow < Nx)
        throw std::invalid_argument(std::string("Error: Wrong dimension for domain matrix.\n"));

    setDomain(domain);
    iFile.close();
}

/*=======================================================================
====== Write to output
=========================================================================*/

