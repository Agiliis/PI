cmake_minimum_required(VERSION 3.31)

project(EmprestimoDeSalas
   VERSION 1.0
   LANGUAGES C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

add_subdirectory(include)
add_subdirectory(src)
