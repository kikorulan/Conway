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


/*=======================================================================
====== Constructors
=========================================================================*/

// Constructor from input file stream iFile 
int * newConway(std::string &iFileName){
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

    int *domain;
    int sizeMatrix = Nx * Ny * (nSteps + 1) * sizeof(int) + 3;
    domain = (int*) malloc(sizeMatrix);
    // Save dimensions
    domain[0] = Nx;
    domain[1] = Ny;
    domain[2] = nSteps + 1;
    
    for (int k = 0; k<=nSteps; k++)
        for (int j = 0; j<Ny; j++)
            for (int i = 0; i<Nx; i++)
                domain[k*Nx*Ny + j*Nx + i + 3] = 0;

    // Message: CONWAY created
    std::cout << "CONWAY created." << std::endl;
    getDimensions(domain);
    return domain;
}

/*=======================================================================
====== Getters for c and n
=========================================================================*/
// Get the dimensions at the standard output
void getDimensions(int *domain){
    std::cout << "Dimensions:" << std::endl;
    std::cout << "    Number of rows: " << domain[0] << std::endl;
    std::cout << "    Number of cols: " << domain[1] << std::endl;
    std::cout << "    Number of steps: " << domain[2] << std::endl;
}

/*============================================================================
==============                                            ====================
==============         Compute Conway's GoL               ====================
==============                                            ====================
==============================================================================*/

// Compute the new state of the matrix
__global__ void updateMatrix(int *domain, int *neigh){
    int index = blockIdx.x*blockDim.x + threadIdx.x;
    bool alive3 = (3 == neigh[index]);
    bool alive2 = (2 == neigh[index]);
    domain[index] = alive3 + domain[index]*alive2;
}

__global__ void countAliveNeigh(int *domain, int *neigh, int nRows, int nCols){
    int index = blockIdx.x*blockDim.x + threadIdx.x;
    //===========================================================
    // Compute number of neighbours by shifting columns and rows
    //===========================================================
    // Row shift
    int i_row_pos = index - (index%nRows) + (nRows + index  - 1)%nRows;
    int i_row_neg = index - (index%nRows) + ((index  + 1)%nRows);
    // Column shift
    int i_col_pos = (index  - nRows + nRows*nCols)%(nRows*nCols);
    int i_col_neg = (index  + nRows)%(nRows*nCols);
    // Row - Column shift
    int i_row_pos_col_pos = (i_row_pos  - nRows + nRows*nCols)%(nRows*nCols);
    int i_row_pos_col_neg = (i_row_pos  + nRows)%(nRows*nCols);
    int i_row_neg_col_pos = (i_row_neg  - nRows + nRows*nCols)%(nRows*nCols);
    int i_row_neg_col_neg = (i_row_neg  + nRows)%(nRows*nCols);
    neigh[index] = domain[i_row_pos] + domain[i_row_neg] + 
                   domain[i_col_pos] + domain[i_col_neg] + 
                   domain[i_row_pos_col_pos] + domain[i_row_pos_col_neg] + 
                   domain[i_row_neg_col_pos] + domain[i_row_neg_col_neg];
}

// Computes and writes n steps in the corresponding output files
void computeNSteps(int *domain){
    // Create the output directory
    int i = system("mkdir -p output_data");
    int nSteps = domain[2] - 1;
    int nRows = domain[0], nCols = domain[1];
    int sizeMatrix = nRows * nCols * sizeof(int);

    // Save space in the GPU
    int *device_domain, *device_neighbours;
    cudaMalloc((void **) &device_domain, sizeMatrix);
    cudaMalloc((void **) &device_neighbours, sizeMatrix);

    cudaMemcpy(device_domain, domain + 3, sizeMatrix, cudaMemcpyHostToDevice);
    for (int i = 1; i<=nSteps; i++){
        countAliveNeigh<<<nRows, nCols>>>(device_domain, device_neighbours, nRows, nCols);    
        cudaDeviceSynchronize();
        updateMatrix<<<nRows, nCols>>>(device_domain, device_neighbours);
        cudaMemcpy(domain + 3 + i * nRows * nCols, device_domain, sizeMatrix, cudaMemcpyDeviceToHost);
    }
    cudaFree(device_domain);
    cudaFree(device_neighbours);
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
void loadDomain(int *domain, std::string &iFileName){
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
    int Nx = domain[0];
    int Ny = domain[1];
    while(getline(iFile, str)){
        nCol = 0;
        ss << str;
        while(ss >> val){
            if (nCol < Ny && nRow < Nx)
                if(val == 1 || val == 0)
                    domain[nCol*Nx + nRow + 3] = val;
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
void writeDomain(int *domain){
    // Save the data
    std::ofstream outputFile;
    std::string str = "output_data/CGOL.dat";

    outputFile.open(str);
    if (outputFile.fail()){
        std::ostringstream msg;
        msg << "writeDomain(): Opening file '" << str
            << "' failed, could not be created.";
        throw std::runtime_error(msg.str());
    }

    int nSteps = domain[2], nCols = domain[1], nRows = domain[0];
    for (int k = 0; k < nSteps; k++){
        for (int j = 0; j < nRows; j++){
            for (int i = 0; i < nCols; i++)
                outputFile << domain[k*nRows*nCols + i*nRows + j + 3] << " ";
            outputFile << std::endl;
        }
    }
    outputFile.close();

    // Save the data
    str = "output_data/dimensions.dat";
    outputFile.open(str);
    if (outputFile.fail()){
        std::ostringstream msg;
        msg << "writeDomain(): Opening file '" << str
            << "' failed, could not be created.";
        throw std::runtime_error(msg.str());
    }

    outputFile << nRows << " " << nCols << " " << nSteps-1;
    outputFile.close();
}

// Write CGOL step to standard output
void writeDomain(int *domain, int step){
    int nCols = domain[1], nRows = domain[0];
    std::cout << "Host Matrix for step " << step << ": " << std::endl;
    for (int j = 0; j < nRows; j++){
        for (int i = 0; i < nCols; i++)
            std::cout << domain[step*nRows*nCols + i*nRows + j + 3] << " ";
        std::cout << std::endl;
    }
}


