cmake_minimum_required(VERSION 3.25)
project(enigma)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -Werror -pedantic")

add_executable(enigma main.cpp Analysis/Ops.cpp Analysis/Ops.h Enigma/RotorBox.cpp Enigma/Headers/RotorBox.h Enigma/Rotor.cpp Enigma/Headers/Rotor.h Enigma/RotorMappingBuilder.cpp Enigma/Headers/RotorMappingBuilder.h Enigma/Reflector.cpp Enigma/Headers/Reflector.h Enigma/EMOps.cpp Enigma/Headers/EMOps.h Enigma/Plugboard.cpp Enigma/Headers/Plugboard.h Enigma/EnigmaMachine.cpp Enigma/Headers/EnigmaMachine.h Analysis/IndexOfCoincidence/IndexOfCoincidence.cpp Analysis/IndexOfCoincidence/IndexOfCoincidence.h Analysis/BlindDecrypt.cpp Analysis/BlindDecrypt.h Analysis/CharacterFrequency/CharacterFrequency.cpp Analysis/CharacterFrequency/CharacterFrequency.h Analysis/KnownPlaintextSimple/KnownPlaintextSimple.cpp Analysis/KnownPlaintextSimple/KnownPlaintextSimple.h Analysis/KnownPlaintextStack.cpp Analysis/KnownPlaintextStack.h)
