#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common\plist.h"


typedef struct _stu_info {
	Uint8 *name;
	Uint16 id;
}st_stu_info;

typedef void(*func)(void *);

typedef struct _func {
	Uint8* code;
	func p_func;
}st_func;

struct list_head stu_info_list;
struct list_head func_list;

void func1(void)
{
	printf("func1\n");
}

void func2(void)
{
	printf("func2\n");
}

void func3(void)
{
	printf("func3\n");
}

int main(int argc, char **agrv)
{
	int16 ret = 0;
	st_stu_info stu1;
	stu1.name = "张三";
	stu1.id = 1;
	init_list(&stu_info_list);
	add_list_node(&stu1, sizeof(st_stu_info), &stu_info_list);

	st_stu_info stu2;
	stu2.name = "李四";
	stu2.id = 2;
	add_list_node(&stu2, sizeof(st_stu_info), &stu_info_list);

	st_stu_info stu3;
	stu3.name = "王老五";
	stu3.id = 3;
	add_list_node(&stu3, sizeof(st_stu_info), &stu_info_list);

	st_stu_info stu4;
	stu3.name = "张小七";
	stu3.id = 4;
	add_list_node(&stu3, sizeof(st_stu_info), &stu_info_list);

	stu3.name = "王老五";
	stu3.id = 3;
	add_list_node(&stu3, sizeof(st_stu_info), &stu_info_list);

	struct list_head *pos = NULL;
	struct list_head *n = NULL;
	st_list *_node = NULL;
	list_for_each_safe(pos, n, &stu_info_list)
	{
		_node = (st_list *)list_entry(pos, st_list, list);
		printf("name = %s,id = %d\n", ((st_stu_info *)(_node->p_data))->name, ((st_stu_info *)(_node->p_data))->id);
	}

	delete_list_node(&stu2, sizeof(st_stu_info), &stu_info_list);
	list_for_each_safe(pos, n, &stu_info_list)
	{
		_node = (st_list *)list_entry(pos, st_list, list);
		printf("name = %s,id = %d\n", ((st_stu_info *)(_node->p_data))->name, ((st_stu_info *)(_node->p_data))->id);
	}

	delete_list_node(&stu1, sizeof(st_stu_info), &stu_info_list);
	list_for_each_safe(pos, n, &stu_info_list)
	{
		_node = (st_list *)list_entry(pos, st_list, list);
		printf("name = %s,id = %d\n", ((st_stu_info *)(_node->p_data))->name, ((st_stu_info *)(_node->p_data))->id);
	}

	free_list(&stu_info_list);


	st_func _func1;
	_func1.code = "func1";
	_func1.p_func = func1;
	init_list(&func_list);
	add_list_node(&_func1, sizeof(_func1), &func_list);

	st_func _func2;
	_func2.code = "func2";
	_func2.p_func = func2;
	add_list_node(&_func2, sizeof(_func2), &func_list);

	st_func _func3;
	_func3.code = "func3";
	_func3.p_func = func3;
	add_list_node(&_func3, sizeof(_func3), &func_list);

	list_for_each_safe(pos, n, &func_list)
	{
		_node = (st_list *)list_entry(pos, st_list, list);
		((st_func *)_node->p_data)->p_func((void*) 0);
	}
	return 0;
}