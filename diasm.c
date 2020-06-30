#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "includes/asm.h"

int main(void) 
{
    unsigned char buf_size[1];
    int fd;
    // char *line;
    int i;

    fd = open("champ.cor", O_RDONLY);
    while ((read(fd, buf_size, 1)))
    {
        printf("%c ", buf_size[0]);
        // free(line);
    }
    return (0);
}