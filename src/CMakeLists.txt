link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(photoimport
    main.cpp
    photoimport.cpp
    photoimport.h)

target_link_libraries(photoimport
    ${GTKMM_LIBRARIES}  )
