cmake_minimum_required(VERSION 3.12)
project(compiler_generator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(input)
include_directories(models)
include_directories(utils)

add_executable(compiler_generator
        input/rules.txt
        input/test.txt
        input/try.txt
        models/ArithmeticOperators.cpp
        models/ArithmeticOperators.h
        models/DFAminiState.cpp
        models/DFAminiState.h
        models/DFAState.cpp
        models/DFAState.h
        models/FiniteStateTable.cpp
        models/FiniteStateTable.h
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
        Controller.cpp
        Controller.h
        DFABuilder.cpp
        DFABuilder.h
        DFAmini.cpp
        DFAmini.h
        main.cpp
        NFABuilder.cpp
        NFABuilder.h
        TokenGenerator.cpp
        TokenGenerator.h)
