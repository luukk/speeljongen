#include <iostream>
#include "src/registers.h"
#include "src/flags.h"

int main() {
    cpu::registers registerList;
    cpu::flags flags(registerList);
 
    flags.setCarry();
}