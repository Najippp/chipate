#pragma once

#define INSTRUCTION_CLEAR 1
#define INSTRUCTION_JUMP 2
#define INSTRUCTION_SETREG 3
#define INSTRUCTION_ADDREG 4
#define INSTRUCTION_SETINDEX 5
#define INSTRUCTION_DRAW 6
#define INSTRUCTION_UNKNOWN -1

namespace Decoder {
    char Decode (unsigned char instruction[2]);
};