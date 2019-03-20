cmake_minimum_required(VERSION 3.10)
project(compiler_generator)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(models)

add_executable(compiler_generator
        models/ArithmeticOperators.cpp
        models/ArithmeticOperators.h
        models/Keywords.cpp
        models/Keywords.h
        models/Punctuations.cpp
        models/Punctuations.h
        models/RegularDefinitions.cpp
        models/RegularDefinitions.h
        models/RegularExpressions.cpp
        models/RegularExpressions.h
        models/RelationalOperators.cpp
        models/RelationalOperators.h
        models/TokenStateNode.cpp
        models/TokenStateNode.h
        main.cpp
        NFABuilder.cpp
        NFABuilder.h models/RulesParser.cpp models/RulesParser.h models/Types.h
        NFABuilder.h utils/StringUtils.cpp utils/StringUtils.h)
