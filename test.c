#include "vm.h"

#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    
    VALUE inputs[16];
    inputs[0] = atof(argv[1]);
    
    // input0 * sin(pi / 4)
    inst_t code[5];
    code[0].opcode      = OP_PUSH;          code[0].operand.value = M_PI / 4;
    code[1].opcode      = OP_SIN;
    code[2].opcode      = OP_PUSH_INPUT;    code[2].operand.input_register = 0;
    code[3].opcode      = OP_MUL;
    code[4].opcode      = OP_HALT;
    
    VALUE stack[128];
    
    VALUE result = vm_eval(code, stack, 128, inputs);
    
    printf("Output: %f\n", result);
    
    return 0;
}