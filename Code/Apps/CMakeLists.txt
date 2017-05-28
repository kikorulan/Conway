
if(PARALLEL_OMP)
    set(APP runConwayOMP)
else()
    set(APP runConway)
endif()    
add_executable(${APP} runConway.cpp)
target_link_libraries(${APP} conwayGL ${ALL_THIRD_PARTY_LIBRARIES})
