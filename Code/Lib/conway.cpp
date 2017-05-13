/*=============================================================================

  CONWAY'S GAME OF LIFE

  Copyright (C) 2017 Kiko Rul·lan

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "basicTypes.hpp"
#include "conway.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <memory>

#define ARMA_USE_CXX11
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
    domain.reset(new matI(Nx, Ny)); // Create domain matrix 
    (*domain).fill(0);
    domainNext.reset(new matI(Nx, Ny));
}

// Set domain equal to the given matrix
void Conway::setDomain(matIP &M){
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
==============         Compute Conway's GoL               ====================
==============                                            ====================
==============================================================================*/

// Count alive neighbours
int Conway::countAliveNeigh(int const& coordX, int const& coordY){
    int alive = 0;
    int xNext = (coordX+1)%Nx;
    int xPrev = (coordX-1+Nx)%Nx;
    int yNext = (coordY+1)%Ny;
    int yPrev = (coordY-1+Ny)%Ny;
    alive = alive + (*domain)(xPrev, yPrev);
    alive = alive + (*domain)(coordX, yPrev);
    alive = alive + (*domain)(xNext, yPrev);
    alive = alive + (*domain)(xPrev, coordY);
    alive = alive + (*domain)(xNext, coordY);
    alive = alive + (*domain)(xPrev, yNext);
    alive = alive + (*domain)(coordX, yNext);
    alive = alive + (*domain)(xNext, yNext);
    return alive;
}

// Compute the new state of the given pixel
void Conway::updatePixel(int const& coordX, int const& coordY){
    int alive = countAliveNeigh(coordX, coordY);
    int state = (*domain)(coordX, coordY);
    if (state == 1){
        if (alive < 2 || alive > 3)
            (*domainNext)(coordX, coordY) = 0;
        else 
            (*domainNext)(coordX, coordY) = 1;
    }
    else {
        if (alive == 3)
            (*domainNext)(coordX, coordY) = 1;
        else 
            (*domainNext)(coordX, coordY) = 0;
    }
}

// Compute the new state of the matrix
void Conway::updateMatrix(void){
    // Update interior points
    for (int i = 0; i < Ny; i++)
        for (int j = 0; j < Nx; j++)
            updatePixel(j, i);
        
    domain.reset(domainNext.release());
    domainNext.reset(new matI(Nx, Ny));
}

// Computes and writes n steps in the corresponding output files
void Conway::computeNSteps(int const& nSteps){
    // Create the output directory
    int i = system("mkdir -p output_data");
    for (int i = 1; i <= nSteps; i++){
        updateMatrix();
        writeDomain(i);
    }
}

/*============================================================================
==============                                            ====================
==============         Load and write data                ====================
==============                                            ====================
==============================================================================*/

/*=======================================================================
====== Load data from file stream
=========================================================================*/
/* Load domain matrix from input file */
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
    matIP domain; 
  
    // Domain matrix
    int nCol = 0, nRow = 0;
    double val;
    domain.reset(new matI(Nx, Ny));
    domain->fill(0);
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
    
    if (nCol < Ny-1 || nRow < Nx-1)
        throw std::invalid_argument(std::string("Error: Given matrix exceeds dimensions of domain.\n"));

    setDomain(domain);
    iFile.close();
}

/*=======================================================================
====== Write to output
=========================================================================*/

// Write output to given file
void Conway::writeDomain(int const& nStep){
    // Save the data
    std::ofstream outputFile;
    std::string str = "output_data/Matrix" + std::to_string(nStep) + ".dat";

    outputFile.open(str);
    if (outputFile.fail()){
        std::ostringstream msg;
        msg << "writeDomain(): Opening file '" << str
            << "' failed, could not be created.";
        throw std::runtime_error(msg.str());
    }
    

    for (int j = 0; j < Nx; j++){
        for (int i = 0; i < Ny; i++)
            outputFile << (*domain)(j, i) << " ";
        outputFile << std::endl;
    }
    outputFile.close();
}

// Write output in the standard output
void Conway::writeDomain(void){

    for (int j = 0; j < Nx; j++){
        for (int i = 0; i < Ny; i++)
            std::cout << (*domain)(j, i) << " ";
        std::cout << std::endl;
    }
}


