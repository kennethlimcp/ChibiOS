#ifndef __EINK_SHELL_H__
#define __EINK_SHELL_H__

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "shell.h"

void einkShellInit(void);
void einkShellRestart(void);

#define eink_command_start() \
({ \
  static char start[0] __attribute__((unused,  \
    aligned(16), section(".chibi_list_cmd_1")));        \
  (const ShellCommand *)&start;            \
})

#define eink_command(_name, _func) \
  const ShellCommand _eink_cmd_list_##_func \
  __attribute__((unused, aligned(16), section(".chibi_list_cmd_2_" _name))) = \
     { _name, _func }

#define eink_command_end() \
  const ShellCommand _eink_cmd_list_##_func \
  __attribute__((unused, aligned(16), section(".chibi_list_cmd_3_end"))) = \
     { NULL, NULL }

#endif /* __EINK_SHELL_H__ */
