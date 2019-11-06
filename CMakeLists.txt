cmake_minimum_required(VERSION 2.6.4)
project(naoKin)
find_package(qibuild)

include_directories(".")

qi_create_bin(naoKin main.cpp src/external/Kofinas/NAOKinematics.cpp src/external/Kofinas/NAOKinematicsJacobian.cpp src/NAOKin.cpp src/Timer.cpp)
qi_use_lib(naoKin ALCOMMON ALPROXIES)
