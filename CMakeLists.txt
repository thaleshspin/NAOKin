cmake_minimum_required(VERSION 2.6.4)
project(nao)
find_package(qibuild)

include_directories(".")

qi_create_bin(nao main.cpp src/NAO.cpp src/Timer.cpp)
qi_use_lib(nao ALCOMMON ALPROXIES)
