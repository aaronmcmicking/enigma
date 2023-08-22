# enigma

This is a simulation the WWII-era German Enigma Machine used to encrypt 
communications that was famously decrypted by British researchers, including 
Alan Turing.
<br><br>
This project exists because a) I thought it would be an interesting challenge 
to model Enigma and b) I wanted to learn C++.

## Sources
Details regarding Enigma, internal rotors and reflector layouts were sourced from: <br>
[Numberphile](https://youtube.com/numberphile)<br>
[Jared Owen](https://youtube.com/watch?v=ybkkiGtJmkM)<br>
[Enigma machine (Wikipedia)](https://wikipedia.org/wiki/Enigma_machine)<br>
[Enigma rotor details (Wikipedia)](https://wikipedia.org/wiki/Enigma_rotor_details)<br>

## Modelling
This simulation models rotor configurations from German M3 Army model Enigma 
machines. All reflector configurations (A - C) and Rotors 1-5 are modelled accurately 
(to my knowledge). The ability to change the turnover position of a rotor (also 
known as the "ring setting") is included.

# Build

A CMake list has been included to build with CMake. This program was written for 
C++20 and has no external dependancies.

```
clone https://github.com/aaronmcmicking/enigma
cd enigma
mkdir build
cd build
cmake ..
make
```

## Usage

**A usage example is included in `main.cpp`.**

An `EnigmaMachine` object must be instantiated with fields. For this, use the
`EnigmaConfig` object. Both an `EnigmaMachine` and `EnigmaConfig` require five
fields at instantiation: Rotors, Rotor Positions, Ring Settings, Reflector, and
Plugboard settings.

There are five `Rotors`, and each can only be used once per configuration.
Each `Rotor` can start at position including and between 1-26. As well, each `Rotor`
can have it's ring setting (ie. the position where it rotates a sequential
`Rotor`) set, again between and including 1-26. A `Reflector` may also be chosen.
The `Reflector` options are `A`, `B`, and `C`. A `Plugboard` may be assigned
using a formatted string with the desired plugboard pairs (ex. "AH KU YD WB")

After creating an `EnigmaConfig`, use it to construct an `EnigmaMachine`.

To encrypt or decrypt text using the machine, use `EnigmaMachine::encrypt_or_decrypt(...)`. This
function is overloaded, see `Enigma/Headers/EnigmaMachine.h` for more information.

To encrypt/decrypt from a file, filepaths must be specified. Defaults filepaths 
are provided which assumes that the files are stored in "../textfiles" relative
to the executable. They are `BlindDecrypt::default_plaintext_path()`, 
`BlindDecrypt::default_encrypted_path()`, and `BlindDecrypt::default_decrypted_path()`.
Place plaintext into `textfiles/plaintext.txt`. If the text needs to be formatted,
call `stdo::format_input_file(text_path)`. 

To decrypt come ciphertext, use `BlindDecrypt::decrypt(src_path, dest_path)`. 
The results will be printed. Also specify the statistical method used for 
decryption: either `BlindDecrypt::INDEX_OF_COINCIDENCE` or `BlindDecrypt::CHARACTER_FREQUENCY`
(see [Decryption Methods](#decryption-methods) for more info).

## Decryption Methods

Two statistical methods to decrypt English ciphertext have been implemented:

### Index of Coincidence (IOC)

IOC quantifies the likelyhood that two characters selected at random from a body
of text will be the same character. Random text has an IOC of ~1.00. Natural
languages have varying IOC's, with English plaintext having an IOC of ~1.74. 
Therefore, configurations which have an IOC closer to this value are generally 
considered better decryptions.

### Character Frequency (CF)

CF compares the frequency of each character in a body of text to the expected
frequency of natural English plaintext.




