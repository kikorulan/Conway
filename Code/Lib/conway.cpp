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

#include <boost/mpi.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

/*=======================================================================
====== Constructors
=========================================================================*/

// Constructor from input file stream iFile 
cubeIP newConway(std::string &iFileName){
    std::ifstream iFile;
    iFile.open(iFileName);
    if (iFile.fail()){
        std::ostringstream msg;
        msg << "Conway(): Opening file '" << iFileName
            << "' failed, it either doesn't exist or is not accessible.";
        throw std::runtime_error(msg.str());
    }
    int Nx = 0, Ny = 0, nSteps = 0;

    std::string str;
    std::stringstream ss;
    getline(iFile, str);
    ss << str;
    ss >> Nx >> Ny >> nSteps;
    ss.clear();

    // Check input values
    if (Nx < 1 || Ny < 1 )
        throw std::invalid_argument("CONWAY not created. Invalid value(s) for grid dimensions.\n");

    cubeIP domain(new cubeI(Nx, Ny, nSteps + 1));
    (*domain).fill(0);
    // Message: CONWAY created
    std::cout << "CONWAY created." << std::endl;
    getDimensions(domain);
    return domain;
}

/*=======================================================================
====== Getters for c and n
=========================================================================*/
// Get the dimensions at the standard output
void getDimensions(cubeIP &domain){
    std::cout << "Dimensions:" << std::endl;
    std::cout << "    Number of rows: " << (*domain).n_rows << std::endl;
    std::cout << "    Number of cols: " << (*domain).n_cols << std::endl;
}

/*============================================================================
==============                                            ====================
==============         Compute Conway's GoL               ====================
==============                                            ====================
==============================================================================*/

// Count alive neighbours
int countAliveNeigh(cubeIP &domain, int const& coordX, int const& coordY, int const& step){
    int alive = 0;
    int xNext = (coordX+1)%(*domain).n_rows;
    int xPrev = (coordX-1+(*domain).n_rows)%(*domain).n_rows;
    int yNext = (coordY+1)%(*domain).n_cols;
    int yPrev = (coordY-1+(*domain).n_cols)%(*domain).n_cols;
    alive = alive + (*domain)(xPrev, yPrev, step);
    alive = alive + (*domain)(coordX, yPrev, step);
    alive = alive + (*domain)(xNext, yPrev, step);
    alive = alive + (*domain)(xPrev, coordY, step);
    alive = alive + (*domain)(xNext, coordY, step);
    alive = alive + (*domain)(xPrev, yNext, step);
    alive = alive + (*domain)(coordX, yNext, step);
    alive = alive + (*domain)(xNext, yNext, step);
    return alive;
}

// Compute the new state of the given pixel
void updatePixel(cubeIP &domain, int const& coordX, int const& coordY, int const& step){
    int alive = countAliveNeigh(domain, coordX, coordY, step);
    int state = (*domain)(coordX, coordY, step);
    if (state == 1){
        if (alive < 2 || alive > 3)
            (*domain)(coordX, coordY, step+1) = 0;
        else 
            (*domain)(coordX, coordY, step+1) = 1;
    }
    else {
        if (alive == 3)
            (*domain)(coordX, coordY, step+1) = 1;
        else 
            (*domain)(coordX, coordY, step+1) = 0;
    }
}

// Compute the new state of the matrix
void updateMatrix(cubeIP &domain, int const& step){
    // Update interior points
    for (int j = 0; j < (*domain).n_rows; j++)
        for (int i = 0; i < (*domain).n_cols; i++)
            updatePixel(domain, j, i, step);
}

// Computes and writes n steps in the corresponding output files
void computeNSteps(cubeIP &domain){
    // Create the output directory
    int i = system("mkdir -p output_data");
    int nSteps = (*domain).n_slices - 1;
    for (int i = 0; i < nSteps; i++){
        updateMatrix(domain, i);
    }
    writeDomain(domain);
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
void loadDomain(cubeIP &domain, std::string &iFileName){
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
  
    // Domain matrix
    int nCol = 0, nRow = 0;
    double val;
    int Nx = (*domain).n_rows;
    int Ny = (*domain).n_cols;
    while(getline(iFile, str)){
        nCol = 0;
        ss << str;
        while(ss >> val){
            if (nCol < Ny && nRow < Nx)
                if(val == 1 || val == 0)
                    (*domain)(nRow, nCol, 0) = val;
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

    iFile.close();
}

/*=======================================================================
====== Write to output
=========================================================================*/

// Write output to given file
void writeDomain(cubeIP &domain){

    boost::mpi::environment env;
    boost::mpi::communicator world;

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
    for (int k = 0; k < (*domain).n_slices; k++){
        for (int j = 0; j < (*domain).n_rows; j++){
            for (int i = 0; i < (*domain).n_cols; i++)
                outputFile << (*domain)(j, i, k) << " ";
            outputFile << std::endl;
        }
    }
    outputFile.close();
}


