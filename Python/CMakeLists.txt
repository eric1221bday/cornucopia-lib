find_package(pybind11 REQUIRED)

include_directories(${Cornucopia_SOURCE_DIR}/Cornucopia)
pybind11_add_module(CornucopiaPy CornucopiaPy.cpp)

target_link_libraries(CornucopiaPy PUBLIC Cornucopia)