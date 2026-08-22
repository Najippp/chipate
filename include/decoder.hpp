#pragma once

#define INSTRUCTION_CLEAR 1
#define INSTRUCTION_JUMP 2
#define INSTRUCTION_SETREG 3
#define INSTRUCTION_ADDREG 4
#define INSTRUCTION_SETINDEX 5
#define INSTRUCTION_DRAW 6
#define INSTRUCTION_SKIPIFREGEQUAL 7
#define INSTRUCTION_SKIPIFREGNEQUAL 8
#define INSTRUCTION_SKIPIFEQUAL 9
#define INSTRUCTION_SKIPIFNEQUAL 10
#define INSTRUCTION_UNKNOWN -1

namespace Decoder {
    // Returns the first nibble (first four bits) of a byte
    char First_Nibble(unsigned char byte);

    // Returns the second nibble (last four bits) of a byte
    char Second_Nibble(unsigned char byte);

    // Returns the macro identifier of an instruction based on the argument  
    char Decode(unsigned char instruction[2]);
};