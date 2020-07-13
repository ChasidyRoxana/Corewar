
#include "../includes/vm.h"

// возвращает значение регистра/дира/значение по инд(%IDX_MOD)
int			set_arg(t_vm *vm, t_cursor *cur, t_arg args[], int i)
{
	if (args[i].type == T_REG)
		return (cur->regs[args[i].arg - 1]);
	else if (args[0].type == T_DIR)
		return (args[i].arg);
	else
		return (get_arg(vm, cur->i + (args[i].arg % IDX_MOD), 4));
}

void 		op_and(t_vm *vm, t_cursor *cur, t_arg args[])
{
	int		result;
	int		first_arg;
	int		second_arg;

	first_arg = set_arg(vm, cur, args, 0);
	second_arg = set_arg(vm, cur, args, 1);
	result = first_arg & second_arg;
	cur->regs[args[2].arg - 1] = result;
	cur->carry = (result == 0 ? 1 : 0);
}

void		op_or(t_vm *vm, t_cursor *cur, t_arg args[])
{
	int		result;
	int		first_arg;
	int		second_arg;

	first_arg = set_arg(vm, cur, args, 0);
	second_arg = set_arg(vm, cur, args, 1);
	result = first_arg | second_arg;
	cur->regs[args[2].arg - 1] = result;
	cur->carry = (result == 0 ? 1 : 0);
}

void		op_xor(t_vm *vm, t_cursor *cur, t_arg args[])
{
	int		result;
	int		first_arg;
	int		second_arg;

	first_arg = set_arg(vm, cur, args, 0);
	second_arg = set_arg(vm, cur, args, 1);
	result = first_arg ^ second_arg;
	cur->regs[args[2].arg - 1] = result;
	cur->carry = (result == 0 ? 1 : 0);
}

void		op_zjmp(t_vm *vm, t_cursor *cur, t_arg args[])
{
	if (cur->carry)
		cur->i = (cur->i + (set_arg(vm, cur, args, 0) % IDX_MOD)) % MEM_SIZE;
}
