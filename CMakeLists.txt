cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(mdlbrt VERSION 1.0)

# Add code
aux_source_directory(src SOURCES)

set(HEADERS include/colors.h include/graph.h)

# add the executable
add_executable(mdlbrt ${SOURCES} ${HEADERS})