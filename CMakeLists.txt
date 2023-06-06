cmake_minimum_required(VERSION 3.25)
project(enigma)

set(CMAKE_CXX_STANDARD 20)

add_executable(enigma main.cpp Enigma/RotorBox.cpp Enigma/Headers/RotorBox.h Enigma/Rotor.cpp Enigma/Headers/Rotor.h Enigma/RotorMappingBuilder.cpp Enigma/Headers/RotorMappingBuilder.h Enigma/Reflector.cpp Enigma/Headers/Reflector.h Enigma/EMOps.cpp Enigma/Headers/EMOps.h Enigma/Plugboard.cpp Enigma/Headers/Plugboard.h Enigma/EnigmaMachine.cpp Enigma/Headers/EnigmaMachine.h IndexOfCoincidence/IndexOfCoincidence.cpp IndexOfCoincidence/IndexOfCoincidence.h)
