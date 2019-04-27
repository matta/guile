#include "test.h"

static double data[] = { -1.0, 0.0, 0.5 };

static void
run_test(jit_state_t *j, uint8_t *arena_base, size_t arena_size)
{
  jit_begin(j, arena_base, arena_size);
  size_t align = jit_enter_jit_abi(j, 0, 0, 0);
  jit_load_args_2(j, jit_operand_gpr (JIT_OPERAND_ABI_POINTER, JIT_R0),
                  jit_operand_fpr (JIT_OPERAND_ABI_DOUBLE, JIT_F0));

  jit_str_d(j, JIT_R0, JIT_F0);
  jit_leave_jit_abi(j, 0, 0, align);
  jit_ret(j);

  void (*f)(void*, double) = jit_end(j, NULL);

  ASSERT(data[0] == -1.0);
  ASSERT(data[1] == 0.0);
  ASSERT(data[2] == 0.5);
  f(&data[1], 42.5);
  ASSERT(data[0] == -1.0);
  ASSERT(data[1] == 42.5);
  ASSERT(data[2] == 0.5);
}

int
main (int argc, char *argv[])
{
  return main_helper(argc, argv, run_test);
}
