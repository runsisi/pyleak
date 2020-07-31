cmake_minimum_required(VERSION 2.8.12)
project(x)

add_subdirectory(pybind11)

pybind11_add_module(x src/x.cc)
