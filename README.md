# enigma

This is a simulation the WWII-era German Enigma Machine, used for cryptography in "secure" communications,
that was famously decrypted by British researchers, including Alan Turing.
<br><br>
This project exists because a) I thought it would be an interesting challenge to model Enigma and 
b) I am using it to learn C++.

## Sources
Details regarding Enigma, internal rotors and reflector layouts were sourced from: <br>
[Numberphile](https://youtube.com/numberphile)<br>
[Jared Owen](https://youtube.com/watch?v=ybkkiGtJmkM)<br>
[Enigma machine (Wikipedia)](https://wikipedia.org/wiki/Enigma_machine)<br>
[Enigma rotor details (Wikipedia)](https://wikipedia.org/wiki/Enigma_rotor_details)<br>

## Basic Design of Enigma
Enigma is a substitution cipher machine. It takes one character as input, and outputs a different
character. However, the same character is unlikely to yield the same output twice in a row. This is 
achieved with three rotors which form a circuit to determine the substitution. Eight distinct rotors (with 
standardized inputs-outputs) were created by 1939. Each rotor contains crossed wiring that maps each letter to 
another letter. The output from a given rotor is used as input for the subsequent rotor. On each keypress, the 
first rotor turns, changing the input point on the wheel. For every full rotation of the first rotor, the second 
rotor turns, and so on for the third rotor.
<br><br>
After the third rotor, a reflection changes the current character and then sends the signal back through the rotors, although
they do not turn this time. This effectively makes the Enigma machine reversible. As long as the starting position of the components
are the same, an input will always give the same output and entering a previous output will give the input value it used. 
Therefore, encryption and decryption are mechanically identical.
<br><br>
As well, Military Enigma machines included a "plugboard" on the front of the machine that allow two letters to be "swapped."
ie. if `A` and `Q` are paired together on the plugboard, then pressing `A` will behave as though `Q` had been pressed
and vice versa. Conversely, if `H` and `K` are paired, then a `K` that is output will be changed to an `H`.
This further substitution is made before and after the signal passes through the rotors. Ten such
pairs can be made at any time. The reversible properties explained earlier are unaffected by this mechanism.


## Modelling
This simulation models rotor configurations from German M3 Army model Enigma machines, as recorded in 1938. 
Rotors 6-8 (introduced in 1939) have their substitution maps included, but will not behave accurately to their 
real-world counterparts as their designs different from earlier models.
<br>
All reflector configurations (A - C) and Rotors 1-5 are modelled accurately.