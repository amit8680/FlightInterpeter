cmake_minimum_required(VERSION 3.15)
project(ex3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(ex3 main.cpp Lexer.cpp Lexer.h Parser.cpp Parser.h Command.h var.cpp var.h OpenDataServer.cpp OpenDataServer.h VarInfo.h VarManager.cpp VarManager.h Print.cpp Print.h Sleep.cpp Sleep.h ConnectCommand.cpp ConnectCommand.h LoopCommand.cpp LoopCommand.h ex1.cpp ex1.h Expression.h IfCommand.cpp IfCommand.h ConditionParser.h ConditionParser.cpp)