#-----------------------------------------------------------------------------
# SWIG for Python

find_package(SWIG REQUIRED)
  
include(${SWIG_USE_FILE})

find_package(PythonLibs REQUIRED)
  
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${OpenIGTLink_SOURCE_DIR}/Source)
include_directories(${OpenIGTLink_SOURCE_DIR}/Source/igtlutil)
include_directories(${OpenIGTLink_BINARY_DIR})
include_directories(${penIGTLink_BINARY_DIR}/igtlutil)
    
set(CMAKE SWIG OUTDIR {root})

set(CMAKE_SWIG_FLAGS "")

set_source_files_properties(OpenIGTLink.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(OpenIGTLink.i PROPERTIES SWIG_FLAGS "-cpperraswarn")

swig_add_library(OpenIGTLink LANGUAGE python TYPE MODULE SOURCES OpenIGTLink.i)

swig_link_libraries(OpenIGTLink ${PYTHON_LIBRARIES} OpenIGTLink)


