#include "vm.h"

#include <math.h>
#include <stdio.h>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

// remove the `##f` to swap to double-precision
#define MATH_OP(name) name##f

#define COS(x)      (MATH_OP(cos)(x))
#define SIN(x)      (MATH_OP(sin)(x))
#define TAN(x)      (MATH_OP(tan)(x))
#define ACOS(x)     (MATH_OP(acos)(x))
#define ASIN(x)     (MATH_OP(asin)(x))
#define ATAN(x)     (MATH_OP(atan)(x))
#define ATAN2(y, x) (MATH_OP(atan2)(y, x))
#define POW(x, y)   (MATH_OP(pow)(x, y))
#define SQRT(x)     (MATH_OP(sqrt)(x))
#define FLOOR(x)    (MATH_OP(floor)(x))
#define CEIL(x)     (MATH_OP(ceil)(x))
#define LOGE(x)     (MATH_OP(log)(x))
#define LOG10(x)    (MATH_OP(log10)(x))

#define POP() \
    (stack[stack_pos--])

#define PUSH(v) \
    if (stack_pos == stack_max) { \
        /* stack overflow, abort! (use longjmp if supported, methinks) */ \
    } \
    stack[++stack_pos] = v
    
#define CURR \
    stack[stack_pos]
    
#define NEXT() \
    ++code; \
    goto *jump_table[code->opcode]
    
VALUE vm_eval(inst_t *code, VALUE *stack, size_t stack_sz, VALUE *inputs) {
    
    /* must be in the same order as opcodes */
    static void* jump_table[] = {
        &&LBL_HALT,
        &&LBL_PUSH,
        &&LBL_PUSH_INPUT,
        &&LBL_NEGATE,
        &&LBL_ADD,
        &&LBL_SUB,
        &&LBL_MUL,
        &&LBL_DIV,
        &&LBL_COS,
        &&LBL_SIN,
        &&LBL_TAN,
        &&LBL_ACOS,
        &&LBL_ASIN,
        &&LBL_ATAN,
        &&LBL_ATAN2,
        &&LBL_POW,
        &&LBL_SQRT,
        &&LBL_LOGE,
        &&LBL_LOG10,
        &&LBL_CLAMP,
        &&LBL_FLOOR,
        &&LBL_CEIL,
        &&LBL_MIN2,
        &&LBL_MAX2,
    };
    
    int stack_pos = -1;
    int stack_max = stack_sz - 1;
    
    goto *jump_table[code->opcode];
    
    LBL_PUSH:
    {
        PUSH(code->operand.value);
        NEXT();
    }
    LBL_PUSH_INPUT:
    {
        PUSH(inputs[code->operand.input_register]);
        NEXT();
    }
    LBL_NEGATE:
    {
        CURR = -CURR;
        NEXT();
    }
    LBL_ADD:
    {
        VALUE v1 = POP();
        CURR = CURR + v1;
        NEXT();
    }
    LBL_SUB:
    {
        VALUE v1 = POP();
        CURR = v1 - CURR;
        NEXT();
    }
    LBL_MUL:
    {
        VALUE v1 = POP();
        CURR = v1 * CURR;
        NEXT();
    }
    LBL_DIV:
    {
        VALUE v1 = POP();
        CURR = v1 / CURR;
        NEXT();
    }
    LBL_COS:
    {
        CURR = COS(CURR);
        NEXT();
    }
    LBL_SIN:
    {
        CURR = SIN(CURR);
        NEXT();
    }
    LBL_TAN:
    {
        CURR = TAN(CURR);
        NEXT();
    }
    LBL_ACOS:
    {
        CURR = ACOS(CURR);
        NEXT();
    }
    LBL_ASIN:
    {
        CURR = ASIN(CURR);
        NEXT();
    }
    LBL_ATAN:
    {
        CURR = ATAN(CURR);
        NEXT();
    }
    LBL_ATAN2:
    {
        VALUE y = POP();
        CURR = ATAN2(y, CURR);
        NEXT();
    }
    LBL_POW:
    {
        VALUE x = POP();
        CURR = POW(x, CURR);
        NEXT();
    }
    LBL_SQRT:
    {
        CURR = SQRT(CURR);
        NEXT();
    }
    LBL_LOGE:
    {
        CURR = LOGE(CURR);
        NEXT();
    }
    LBL_LOG10:
    {
        CURR = LOG10(CURR);
        NEXT();
    }
    LBL_CLAMP:
    {
        VALUE v   = POP();
        VALUE min = POP();
        VALUE max = POP();
        if (v < min) v = min;
        if (v > max) v = max;
        PUSH(v);
        NEXT();
    }
    LBL_FLOOR:
    {
        CURR = FLOOR(CURR);
        NEXT();
    }
    LBL_CEIL:
    {
        CURR = CEIL(CURR);
        NEXT();
    }
    LBL_MIN2:
    {
        VALUE v1 = POP();
        CURR = MIN(v1, CURR);
        NEXT();
    }
    LBL_MAX2:
    {
        VALUE v1 = POP();
        CURR= MAX(v1, CURR);
        NEXT();
    }
    LBL_HALT:
    {
        goto done;
    }
    
    done:
    ;
    
    return POP();
}