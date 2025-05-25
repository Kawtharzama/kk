
#ifndef MINISHELL_H
#define MINISHELL_H
//include library
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include "../libft/libft.h"

typedef struct s_envp {
    char **tmp_envp;  
    int counter;   
} t_envp;

typedef enum e_types {
    WORD = 1,     
    PIPE = 2,    
    REDIR = 3,    
    HEREDOC = 4,
       
} t_types;
typedef struct s_tmptoken{
    char *value;
    int start;
    int end;
 
} t_tmptoken;

typedef struct s_token{
    char *value;
    char qouts; 
    t_types type;
    struct s_token *prev;
   struct s_token *next;
}t_token;


typedef struct s_command
{
    char **args;   // array of arguments
    char *infile;  // file to read from
    char *outfile; // file to write to
    int append;    // 0 for >, 1 for >>
    int heredoc; 
    int executable;
    struct s_command *next;
} t_command;



typedef struct s_all{
    struct s_token *token;
    struct s_tmptoken *tmp;
    struct s_command *cmd;
    struct s_envp *cp_envp;
    // char *var_value;
    int exit_status;


}t_all;



//nodes
t_token	*find_last_node(t_token *token);
int	add_node(t_token **token, char *input);
int toknize(char* input, t_all *as);
//init
t_all *init_strcuts(t_all *as);
void	init_token(t_tmptoken *tmptoken);
//split.c
int	is_parameter(char c);
int	parameter_token(char *input, int i, t_tmptoken *tmp, t_token **token);

//split.c
int split_input(char* input,t_token **token, t_tmptoken *tmp);
// int split_input(char* input,t_token **token, t_tmptoken *tmp, t_command **cmd);
void	print_list(t_token *head);
//free
void free_all(t_all *as);
void free_tokens(t_token *token);
int clean(t_all *as);
int clean_all(t_all *as);
int free_envp(t_envp *cp_envp);
void token_error(t_token *token, char *msg);
int free_token_cmd(t_all *as);
void free_args(char **args);


//qoutes
int closing_qoutes(char *input, int i);
// int find_closing_quote(char *input, int i, int flag, char quote_type);
int find_closing_quote(char *input, int i, int flag, char quote_type);

int	handle_quotes(char *input, int i, t_tmptoken *tmp, t_token **token);
void replace_qoutes(t_token *token, int i, int j, int q);
// void replace_qoutes(t_token *token);
void remove_quotes(t_token *token);

//splits 2
int closing_qoutes(char *input, int i);
int	str(char *input, int i, t_tmptoken *tmp, t_token **token);
void token_types(t_token *token);
int check_qout(char *value);


//env
void copy_envp(char **envp, t_all *as);
void print_envp(t_envp *cp_envp);
int expand_var(t_all *as, t_token *token , t_envp *cp_envp);
char *ft_getenv(const char *name,t_envp *cp_envp);

char* find_path(t_envp *cp_envp, char *cmd);
char *get_full_path(char *dir, char *cmd);

// signals
void sig_handler_prompt (int signum);
void setup_signals(void);
void restore_signals(void);
char **add_arg(char **args, char *value);
void	ignore_signals(void);

int split_cmds(t_all *as, t_token *token, t_command **cmd_list);
// void execute_commands(t_all *as,t_command *cmd_list, t_envp *env);
t_command *new_command(void);
void print_commands(t_command *cmd_list);

//built_ins
void exit_program(t_all *as, int n);
int    execute_echo(char **args);
int     if_nflag(char *str);
int     built_in(t_command *cmd_list);
void   execute_built_ins(t_command *cmd_list, t_envp *env);
void update_env_var(t_envp *env, const char *key, const char *value);
int    execute_cd(char **args, t_envp *env);
int execute_env(char **args, t_envp *env);
int execute_export(char **args, t_envp *env);
void add_or_update_env(t_envp *env, char *key, char *value);
int is_valid_key(char *key);
int execute_pwd(char **args);
int is_valid_unset_key(char *key);
void remove_env_var(t_envp *env, const char *key);
int execute_unset(char **args, t_envp *env);
char *cur_dir(t_all *as);
char *heredoc_cmd(t_all *as, char *del , int n);
void	execute_commands(t_all *as, t_command *cmd_list, t_envp *env);
int expand_var(t_all *as, t_token *token, t_envp *cp_envp);

#endif
