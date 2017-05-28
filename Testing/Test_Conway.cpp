/*=============================================================================

  Copyright (c) 2017 Kiko Rul·lan
  University College London (UCL). All rights reserved.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "Conway_CatchMain.hpp"
#include "basicTypes.hpp"
#include "conway.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <armadillo>

#include <boost/mpi.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/serialization/vector.hpp>

void Test_Number(int i){
    cout << "==============================================================" << endl;
    cout << "===============" << endl;
    cout << "===============     TEST " << i << endl;
    cout << "===============" << endl;            
    cout << "==============================================================" << endl;
}

/*==============================================================
===============                                     ============
===============   TEST 1: CONSTRUCTOR AND GETTERS   ============
===============                                     ============
================================================================*/
TEST_CASE( "Constructor and getters", "1" ) {
/*===================================
Functions to test:
    - Constructors
    - Getters
        getDimensions
        getNX
        getNY
======================================*/
    Test_Number(1);
    CHECK(arg::argc == 3);
}


/*==============================================================
===============                                     ============
===============   TEST 2: SETTERS                   ============
===============                                     ============
================================================================*/
TEST_CASE( "Setters", "2" ) {
/*===================================
Functions to test:
    - Setters
        setDimensions
        setDomain
======================================*/
    Test_Number(2);
    CHECK(1 == 1);
}


/*==============================================================
===============                                     ============
===============   TEST 3: COMPUTE CONWAY'S GOL      ============
===============                                     ============
================================================================*/
TEST_CASE( "Computations", "3" ) {
/*===================================
Functions to test:
    - Compute
        countAliveNeigh
        updatePixel
        countAliveNeighBoundary
        updatePixelBoundary
        updateMatrix
======================================*/
    Test_Number(3);
    CHECK(1 == 1);
}


/*==============================================================
===============                                     ============
===============   TEST 4: LOAD AND WRITE            ============
===============                                     ============
================================================================*/
TEST_CASE( "Load and Write", "4" ) {
/*===================================
Functions to test:
    - Load data
        loadDomain
    - Write data
        writeDomain
======================================*/
    Test_Number(4);
    CHECK(1 == 1);
}

