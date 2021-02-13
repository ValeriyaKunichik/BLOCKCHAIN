#include "header.h"
void quit_and_save(struct nodes *masternode, const char *save_file)
{
    if (save_file == NULL)
    {
        my_write_string(1, "Save backup file is not provided\n");
        return;
    }
    const int fd = open(save_file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    struct nodes *current = masternode;
    struct blocks *current_block;
    while (current != NULL)
    {
        my_write_string(fd, "nid\n");
        my_write_integer(fd, current->nid);
        my_write_string(fd, "\n");
        current_block = current->bidlist->head;
        while (current_block != NULL)
        {
            if (current_block == current->bidlist->head)
            {
                my_write_string(fd, "bid\n");
            }
            my_write_string(fd, current_block->bid);
            my_write_string(fd, "\n");          
            current_block = current_block->next;
        }

        current = current->next;
    }

    close(fd);
}
