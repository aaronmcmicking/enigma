# enigma

This is a simulation the WWII-era German Enigma Machine used to encrypt communications that was famously decrypted 
by British researchers, including Alan Turing.
<br><br>
This project exists because a) I thought it would be an interesting challenge to model Enigma and 
b) I wanted to learn C++.

## Sources
Details regarding Enigma, internal rotors and reflector layouts were sourced from: <br>
[Numberphile](https://youtube.com/numberphile)<br>
[Jared Owen](https://youtube.com/watch?v=ybkkiGtJmkM)<br>
[Enigma machine (Wikipedia)](https://wikipedia.org/wiki/Enigma_machine)<br>
[Enigma rotor details (Wikipedia)](https://wikipedia.org/wiki/Enigma_rotor_details)<br>

## Modelling
This simulation models rotor configurations from German M3 Army model Enigma machines, as recorded in 1938. 
Rotors 6-8 (introduced in 1939) have their substitution maps included, but will not behave accurately to their 
real-world counterparts as their designs different from earlier models.
<br>
All reflector configurations (A - C) and Rotors 1-5 are modelled accurately (to my knowledge). The ability to change
the turnover position of a rotor (also known as the "ring setting") is included, but is not emphasized.

## Usage
I/O reads and writes to text files during encryption/decryption. In EnigmaMachine, encrypt_or_decrypt_arr(string, string)
reads plaintext from an input file and writes its encrypted form into an output file. Decryption uses the identical
mechanism (since encryption and decryption processes are identical) to write plaintext into the output file.

Enigma Machine configurations can be set using an EnigmaConfig struct (defined in EnigmaMachine.h). To decrypt an
encrypted message, the machine must have config settings identical to those used to encrypt the plaintext.