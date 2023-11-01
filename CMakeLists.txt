cmake_minimum_required(VERSION 3.22)
project(calbebr)

set(SOURCES 
  ./src/utils/io.c 
  ./src/utils/vec.c 
  ./src/domain/parser/parser.c 
  ./src/domain/expr/expr.c 
  ./src/domain/eval/eval.c
)

add_executable(calbebr ./src/main.c ${SOURCES})
target_link_libraries(calbebr m)


