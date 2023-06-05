cmake_minimum_required(VERSION 3.25)
project(enigma)

set(CMAKE_CXX_STANDARD 20)

add_executable(enigma main.cpp RotorBox.cpp RotorBox.h Rotor.cpp Rotor.h RotorMappingBuilder.cpp RotorMappingBuilder.h Reflector.cpp Reflector.h EMOps.cpp EMOps.h Plugboard.cpp Plugboard.h EnigmaMachine.cpp EnigmaMachine.h)
