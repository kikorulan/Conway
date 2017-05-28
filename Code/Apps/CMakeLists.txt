set(APP runConwayMPI)
add_executable(${APP} runConway.cpp)
target_link_libraries(${APP} conwayGL ${ALL_THIRD_PARTY_LIBRARIES})
