/*
 *file   : componment/command.c
 *author : haowenchao
 *mail   : haowenchao22@gmail.com
 *desc   : 
 */

#include "printf.h"
#include "string.h"
#include "componment/list.h"
#include "componment/init.h"
#include "componment/command.h"

#ifndef NULL
#define NULL (void *)0
#endif

extern unsigned char getc(void);
extern void putc(unsigned char c);

static char *buff[32];
static struct list_head command_list;

static void command_init(void)
{
	list_init(&command_list);
}
call_back1(command_init);

static int is_blank(char c)
{
	return c == ' ';
}

/*
 * make argv from string p
 * length is the largest value of argc
 * the made argv is stored in argv
 */
static int make_argv(char *p, int length, char *argv[])
{
	int argc = 0;
	char *s = p;

	while(argc < length) {
		while(is_blank(*s))
			s++;

		argv[argc++] = s;

		while(*s && !is_blank(*s))
			s++;

		if(*s == '\0')
			break;

		*s++ = '\0';
	}
	argv[argc] = NULL;

	return argc;
}

/*
 * match a command struct according name
 */
static struct cmd_desc *get_cmd_des(char *name)
{
	struct list_head *pos;
	struct cmd_desc *cmd = NULL;

	list_for_each(pos, &command_list) {
		cmd = container_of(pos, struct cmd_desc, list);

		if(!strcmp(name, cmd->name)) {
			return	cmd;
		}
	}

	return NULL;
}

/*
 * register a command
 * the command is distinguished by name
 * if the command name is already registered, -1 is returned
 */
int register_command(struct cmd_desc *command)
{
	struct list_head *pos;
	struct cmd_desc *cmd = NULL;

	if(command == NULL || command->function == NULL)
		return -1;

	//judge if command already exist
	list_for_each(pos, &command_list) {
		cmd = (struct cmd_desc *)container_of(pos, \
		       struct cmd_desc, list);
		if(!strcmp(command->name, cmd->name)) {
			return -1;
		}
	}

	//add to list
	list_add_tail(&command_list, &command->list);

	return 0;
}

/*
 * string s contains the command info
 * if not a supported command, -1 is returned
 */
int do_command(char *s)
{
	int argc = 0;

	struct cmd_desc *tmp_cmd;

	argc = make_argv(s, 32, buff);

	tmp_cmd = get_cmd_des(buff[0]);

	if(NULL != tmp_cmd) {
		tmp_cmd->function(argc, buff);

		return 0;
	}

	return -1;
}

/*
 * get command string
 */
int get_command(char *buff)
{
	int i = 0;
	unsigned char c;

	if(NULL == buff)
		return -1;

	while(1) {
		c = getc();
		putc(c);

		if(c == '\n' || c == '\r') {
			buff[i++] = '\0';
			break;
		}

		buff[i++] = c;
	}

	return i;
}

