set(Boost_FIND_REQUIRED TRUE)
set(Boost_USE_MULTITHREADED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(openssl)
find_package(Boost REQUIRED COMPONENTS
        iostreams
        filesystem
        date_time
        system
        program_options
        atomic
        chrono
        thread
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)
add_executable(analytics ${SOURCE_FILES})
target_link_libraries(analytics
        ${Boost_LIBRARIES}
)