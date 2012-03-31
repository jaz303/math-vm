#include "vm.h"

#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    
    // 5 * sin(pi / 4)
    inst_t code[] = {
        { OP_PUSH, M_PI / 4 },
        { OP_SIN },
        { OP_PUSH, 5.0f },
        { OP_MUL },
        { OP_HALT }
    };
    
    VALUE stack[128];
    
    VALUE result = vm_eval(code, stack, 128);
    
    printf("Output: %f\n", result);
    
    return 0;
}