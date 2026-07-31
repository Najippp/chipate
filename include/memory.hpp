#pragma once

class Memory {
private:
    unsigned char ram[4096] = {0};

public: 
    bool Load_Program(const char *path);
};