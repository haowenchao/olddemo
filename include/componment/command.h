#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "componment/list.h"
#include "componment/init.h"

struct cmd_desc {
	char *name;
	void (*function)(int argc, char **argv);
	struct list_head list;
};

int register_command(struct cmd_desc *command);
int get_command(char *);
int do_command(char *s);

#define DEFINE_COMMAND(cname, cmd_func) \
void cmd_func(int, char **); \
static struct cmd_desc cmd_##cname; \
static void init_##cname(void) \
{ \
	cmd_##cname.name = #cname; \
	cmd_##cname.function = cmd_func; \
	if(-1 == register_command(&cmd_##cname)) \
	{ \
		return; \
	} \
} \
call_back2(init_##cname); \
void cmd_func(int argc, char **argv)

#endif

