cmake_minimum_required(VERSION 3.10)
project(compiler_generator_master)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(models)
include_directories(utils)

add_executable(compiler_generator_master
        input/rules.txt
        input/test.txt
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
        models/RulesParser.cpp
        models/RulesParser.h
        models/TokenStateNode.cpp
        models/TokenStateNode.h
        models/Types.h
        utils/StringUtils.cpp
        utils/StringUtils.h
        DFAmini.cpp
        DFAmini.h
        main.cpp
        NFABuilder.cpp
        NFABuilder.h models/FiniteStateTable.cpp models/FiniteStateTable.h DFABuilder.cpp DFABuilder.h models/DFAState.cpp models/DFAState.h)
