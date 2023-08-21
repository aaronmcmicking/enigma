cmake_minimum_required(VERSION 3.25)
project(enigma)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -Werror -pedantic")

add_executable(enigma main.cpp Enigma/RotorBox.cpp Enigma/Headers/RotorBox.h Enigma/Rotor.cpp Enigma/Headers/Rotor.h Enigma/RotorMappingBuilder.cpp Enigma/Headers/RotorMappingBuilder.h Enigma/Reflector.cpp Enigma/Headers/Reflector.h Enigma/Headers/stdeo.h Enigma/Plugboard.cpp Enigma/Headers/Plugboard.h Enigma/EnigmaMachine.cpp Enigma/Headers/EnigmaMachine.h Analysis/stdo.h Analysis/IndexOfCoincidence/IndexOfCoincidence.cpp Analysis/IndexOfCoincidence/IndexOfCoincidence.h Analysis/BlindDecrypt.cpp Analysis/BlindDecrypt.h Analysis/CharacterFrequency/CharacterFrequency.cpp Analysis/CharacterFrequency/CharacterFrequency.h Analysis/DecryptionReturnables/RotorDecryptInfo.cpp Analysis/DecryptionReturnables/RotorDecryptInfo.h Analysis/DecryptionReturnables/RingDecryptInfo.cpp Analysis/DecryptionReturnables/RingDecryptInfo.h Analysis/DecryptionReturnables/PlugboardDecryptInfo.cpp Analysis/DecryptionReturnables/PlugboardDecryptInfo.h Analysis/DecryptionReturnables/DecryptInfo.h Enigma/EnigmaConfig.cpp Enigma/Headers/EnigmaConfig.h)
