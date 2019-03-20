cmake_minimum_required(VERSION 3.13)
project(Lexical_Analyzer)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Lexical_Analyzer
        main.cpp
        models/RegularDefinitions.cpp
        models/RegularDefinitions.h
        models/RegularExpressions.cpp
        models/RegularExpressions.h
        models/Keywords.cpp
        models/Keywords.h
        models/Punctuations.cpp
        models/Punctuations.h
        models/RelationalOperators.cpp
        models/RelationalOperators.h
        models/ArithmeticOperators.cpp
        models/ArithmeticOperators.h
        models/TokenStateNode.cpp
        models/TokenStateNode.h
        NFABuilder.cpp
        NFABuilder.h utils/StringUtils.cpp utils/StringUtils.h)