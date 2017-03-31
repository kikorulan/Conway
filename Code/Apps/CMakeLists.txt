
set(MYPROJECT_APPS
    runConway
)
foreach(app ${MYPROJECT_APPS})
  add_executable(${app} ${app}.cpp)
  target_link_libraries(${app} conwayGL ${ALL_THIRD_PARTY_LIBRARIES})
endforeach()
