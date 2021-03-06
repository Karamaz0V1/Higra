############################################################################
# Copyright ESIEE Paris (2018)                                             #
#                                                                          #
# Contributor(s) : Benjamin Perret                                         #
#                                                                          #
# Distributed under the terms of the CECILL-B License.                     #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/lib/include ${PYTHON_INCLUDE_DIR} ${NUMPY_INCLUDE_DIRS})

set(PY_FILES
        __init__.py
        concept.py
        data_cache.py
        hg_utils.py)

REGISTER_PYTHON_MODULE_FILES("${PY_FILES}")

set(PYMODULE_COMPONENTS
        pymodule.cpp)

add_subdirectory(accumulator)
add_subdirectory(algo)
add_subdirectory(assessment)
add_subdirectory(attribute)
add_subdirectory(detail)
add_subdirectory(hierarchy)
add_subdirectory(image)
add_subdirectory(interop)
add_subdirectory(io_utils)
add_subdirectory(plot)
add_subdirectory(structure)

pybind11_add_module(higram ${PYMODULE_COMPONENTS})
get_target_property(_higram_file_name higram OUTPUT_NAME)
set(HIGRA_CPP_MODULE_NAME $<TARGET_FILE:${higram}> PARENT_SCOPE)
set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} higram CACHE INTERNAL "" FORCE)
