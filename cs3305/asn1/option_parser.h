#ifndef option_parser_h
#define option_parser_h

#define MAX 256

typedef struct {
  char *options[MAX];
  int num;
  int pipes;
} csh_cmd;

csh_cmd *get_options(char *s);
csh_cmd *make_tokenlist(char *buf);

#endif
