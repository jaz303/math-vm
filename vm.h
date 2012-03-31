#ifndef VM_H
#define VM_H

#include <stdlib.h>

typedef enum opcode {
    
    OP_HALT,
    
    OP_PUSH,
    
    OP_NEGATE,
    
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    
    OP_COS,
    OP_SIN,
    OP_TAN,
    
    OP_ACOS,
    OP_ASIN,
    OP_ATAN,
    OP_ATAN2,
    
    OP_POW,
    OP_SQRT,
    OP_LOGE,
    OP_LOG10,
    
    OP_CLAMP,
    OP_FLOOR,
    OP_CEIL,
    
    OP_MIN2,
    OP_MAX2,
    
    OP_OPCODE_MAX
    
} opcode_t;

typedef float VALUE;

// TODO: use packing to store opcode inside a VALUE
// sizeof(inst_t) should be 4 or 8 bytes, depending on precision
typedef struct {
    char        opcode;
    VALUE       value;
} inst_t;

/**
 * Evaluate code on the supplied stack.
 *
 * @param code array of instructions to evaluate.
 *             must be non-empty and terminated with OP_HALT
 * @param stack stack to be used for evaluation
 * @param stack_sz number of VALUEs the stack can hold
 */
VALUE vm_eval(inst_t *code, VALUE *stack, size_t stack_sz);

#endif