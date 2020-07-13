/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:35:42 by marvin            #+#    #+#             */
/*   Updated: 2020/07/13 18:08:05 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void	send_to_op2(t_vm *vm, t_cursor *cur, t_arg args[])
{
	if (cur->op == 10)
	{printf("ldi\n");
		op_ldi(vm, cur, args);
		}
	else if (cur->op == 11)
	{printf("sti\n");
		op_sti(vm, cur, args);
		}
	else if (cur->op == 12)
	{printf("fork\n");
		op_fork(vm, cur, args);
		}
	else if (cur->op == 13)
	{printf("lld\n");
		op_lld(vm, cur, args);
		}
	else if (cur->op == 14)
	{printf("lldi\n");
		op_lldi(vm, cur, args);
		}
	else if (cur->op == 15)
	{printf("lfork\n");
		op_lfork(vm, cur, args);
		}
	else if (cur->op == 16)
	{printf("aff\n");
		op_aff(cur, args);
		}
}

void		send_to_op(t_vm *vm, t_cursor *cur, t_arg args[])
{
	if (cur->op == 1)
	{printf("live\n");
		op_live(vm, cur, args);
	}
	else if (cur->op == 2)
	{printf("ld\n");
		op_ld(vm, cur, args);
	}
	else if (cur->op == 3)
	{printf("st\n");
		op_st(vm, cur, args);
	}
	else if (cur->op == 4)
	{printf("add\n");
		op_add(cur, args);
	}
	else if (cur->op == 5)
	{printf("sub\n");
		op_sub(cur, args);
	}
	else if (cur->op == 6)
	{printf("and\n");
		op_and(vm, cur, args);
	}
	else if (cur->op == 7)
	{printf("or\n");
		op_or(vm, cur, args);
	}
	else if (cur->op == 8)
	{printf("xor\n");
		op_xor(vm, cur, args);
	}
	else if (cur->op == 9)
	{printf("zjmp\n");
		op_zjmp(vm, cur, args);
	}
	send_to_op2(vm, cur, args);
}
