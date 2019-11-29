#include "execution.h"
#include "../main/42sh.h"

void command_apply_redirections(struct command *command, void *bundle_ptr)
{
    command->save_in = dup(STDIN_FILENO);
    command->save_out = dup(STDOUT_FILENO);
    command->save_err = dup(STDERR_FILENO);
    for (size_t i = 0; i < command->n_redirections; i++)
    {
        redirection_execute(command, *(command->redirections + i), bundle_ptr);
    }
}

void command_restore_flux(struct command *command)
{
/*
    printf("fd_in: %d || save_in: %d\n", command->fd_in, command->save_in);
    printf("fd_out: %d || save_out: %d\n", command->fd_out, command->save_out);
    printf("fd_err: %d || save_err: %d\n", command->fd_err, command->save_err);
*/
    if (command->fd_in > 2)
    {
        //close(command->fd_in);
    }
    if (command->fd_out > 2)
    {
        close(command->fd_out);
    }
    if (command->fd_err > 2)
    {
        close(command->fd_err);
    }
    dup2(command->save_in, STDIN_FILENO);
    dup2(command->save_out, STDOUT_FILENO);
    dup2(command->save_err, STDERR_FILENO);
    close(command->save_in);
    close(command->save_out);
    close(command->save_err);
}
