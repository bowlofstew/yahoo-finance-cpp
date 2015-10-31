include(ExternalProject)
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
externalproject_add(
        cppnetlib
        GIT_REPOSITORY https://github.com/cpp-netlib/cpp-netlib.git
        GIT_TAG 9f123b3459e23eb0cba22050b7058191b631047a
        SOURCE_DIR ../../thirdparty/cpp-netlib
        INSTALL_COMMAND ""
        BUILD_IN_SOURCE 1
)
set(CPP_NETLIB_HEADERS ../../thirdparty/cpp-netlib)
set(CPP_NETLIB_LIBS ../../thirdparty/cpp-netlib/libs/network/src)
set(SOURCE_FILES main.cpp)
include_directories(${CPP_NETLIB_HEADERS} ${GNUPLOT_HEADERS})
add_executable(downloader ${SOURCE_FILES})
add_dependencies(downloader cppnetlib)
target_link_libraries(downloader
        ${Boost_LIBRARIES}
        ${CRYPTO_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${CPP_NETLIB_LIBS}/libcppnetlib-client-connections.a
        ${CPP_NETLIB_LIBS}/libcppnetlib-server-parsers.a
        ${CPP_NETLIB_LIBS}/libcppnetlib-uri.a
)