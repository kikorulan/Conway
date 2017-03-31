#/*============================================================================
#
#  MYPROJECT: A software package for whatever.
#
#  Copyright (c) University College London (UCL). All rights reserved.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
#  See LICENSE.txt in the top level directory for details.
#
#============================================================================*/

set(MYPROJECT_SRCS
  basicTypes.cpp
  conway.cpp
)

add_library(conwayGL ${MYPROJECT_SRCS})

target_link_libraries(gridrt PRIVATE ${ALL_THIRD_PARTY_LIBRARIES})
