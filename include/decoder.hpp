#pragma once

#define INSTRUCTION_00E0 1
#define INSTRUCTION_1NNN 2
#define INSTRUCTION_6XNN 3
#define INSTRUCTION_7XNN 4
#define INSTRUCTION_ANNN 5
#define INSTRUCTION_DXYN 6
#define INSTRUCTION_5XY0 7
#define INSTRUCTION_9XY0 8
#define INSTRUCTION_3XNN 9
#define INSTRUCTION_4XNN 10
#define INSTRUCTION_UNKNOWN -1

namespace Decoder {
    // Returns the first nibble (first four bits) of a byte
    char First_Nibble(unsigned char byte);

    // Returns the second nibble (last four bits) of a byte
    char Second_Nibble(unsigned char byte);

    // Returns the macro identifier of an instruction based on the argument  
    char Decode(unsigned char instruction[2]);
};