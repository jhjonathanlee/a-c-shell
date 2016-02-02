#ifndef option_parser_h
#define option_parser_h

typedef struct {
  char *cmd;
  char **options;
  int num;
} csh_cmd;

csh_cmd *get_options(char *s);

#endif
