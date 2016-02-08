#ifndef option_parser_h
#define option_parser_h

#define MAX 256

typedef struct {
  char *options[MAX];
  int num;
} csh_cmd;

csh_cmd *get_options(char *s);
int make_tokenlist(char *buf, char *tokens[]);

#endif
