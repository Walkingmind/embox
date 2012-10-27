/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    25.10.2012
 */

#include <types.h>
#include <hal/context.h>

#include <asm/modes.h>

void context_init(struct context *ctx, bool privileged) {
	ctx->cpsr = ARM_MODE_SYS | I_BIT | F_BIT;
}

void context_set_stack(struct context *ctx, void *sp) {
	ctx->sp = (uint32_t) sp;
}

void context_set_entry(struct context *ctx, void(*pc)(void)) {
	ctx->lr = (uint32_t) pc;
}

void context_enter_frame(struct context *ctx, void *pc) {

}

void context_push_stack(struct context *ctx, void *arg, size_t n) {

}

