#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

#define READLINE_READ_SIZE 11
struct blocks
{
    char *bid;
    struct blocks *next;
};

struct list_of_blocks
{
    struct blocks *head;
    struct blocks *tail;
};

struct nodes
{
    int nid;
    int bidlist_size;
    struct list_of_blocks *bidlist;
    bool sync;
    struct nodes *next;
};

char* my_strchr(char* param_1, int c);
char* my_strcpy(char* param_1, char* param_2);
char* my_strncpy(char* param_1, char* param_2, int i);
char* my_strcat(char* param_1, char* param_2);
int my_strlen(const char *str);
int my_write_string(const int fd, const char *str);
int my_write_integer(const int fd, const int input);
bool my_strcmp(const char *left, const char *right);
bool my_strncmp(const char *left, const char *right, const int start_ind, const int len);
char *my_strcpy1(const char *str);
int my_atoi2(const char *str);
void my_blockchain(struct nodes **masternode);
int display_prompt(const bool is_sync, const int node_size);
int prompt_action(const int fd, struct nodes **masternode);
int my_blockchain_command(const char *str, struct nodes **masternode);
int read_command(const int fd, char *buff);
void add_node(const char *buff, struct nodes **masternode);
void add_block(const char *buff, struct nodes **masternode);
void rm_node(const char *buff, struct nodes **masternode);
void rm_block(const char *buff, struct nodes **masternode);
bool ls_l(const char *buff);
int my_atoi(const char *str, const int start_ind);
char *my_trunc_string(const char *str, const int start_ind);
void read_backup_file(struct nodes **masternode, const char *backup_file);
int add_new_block(struct nodes *node, int nid_numb, char *bid);
void rm_found_block(struct nodes *node, char *bid);
bool find_block(struct nodes *node, char *bid);
void free_blockchain_node(struct nodes *node);
char **find_blocks_to_sync(struct nodes *node, int *block_numb);
void sync_blockchain(struct nodes *node);
bool is_synced(struct nodes *node);
char* my_readline(int fd);
void quit_and_save(struct nodes *masternode, const char *save_file);
struct nodes *create_node(int nid_numb);
void add_new_node(struct nodes *node, int nid);
struct nodes *rm_found_node(struct nodes *node, int nid_numb);
void rm_all_nodes(struct nodes *fisrt_node);
void ls(struct nodes *node, const bool is_l);
struct nodes *find_node(struct nodes *node, int nid_numb);
int blockchain_size(struct nodes *node);
struct blocks *create_block(char *data);
