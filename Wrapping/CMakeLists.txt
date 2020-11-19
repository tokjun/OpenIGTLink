#-----------------------------------------------------------------------------
# SWIG for Python

find_package(SWIG REQUIRED)
  
include(${SWIG_USE_FILE})

find_package(PythonLibs REQUIRED)
  
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${OpenIGTLink_SOURCE_DIR}/Source)
    
set(CMAKE SWIG OUTDIR {root})

set(CMAKE_SWIG_FLAGS "")

set_source_files_properties(OpenIGTLink.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(OpenIGTLink.i PROPERTIES SWIG_FLAGS "-cpperraswarn")

swig_add_library(openigtlink LANGUAGE python TYPE MODULE SOURCES OpenIGTLink.i)
swig_link_libraries(openigtlink ${PYTHON_LIBRARIES} OpenIGTLink)


# Files to install with Python
set(PYTHON_INSTALL_FILES
  ${CMAKE_CURRENT_BINARY_DIR}/openigtlink.py
  ${CMAKE_CURRENT_BINARY_DIR}/_openigtlink.so)

# Configure setup.py and copy to output directory
set(SETUP_PY_IN ${CMAKE_CURRENT_SOURCE_DIR}/Python/setup.py.in)
set(SETUP_PY_OUT ${CMAKE_CURRENT_BINARY_DIR}/Python/setup.py)
configure_file(${SETUP_PY_IN} ${SETUP_PY_OUT})

# Install target to call setup.py
add_custom_target(install-python
        DEPENDS _openigtlink
        COMMAND python ${SETUP_PY_OUT} install)
