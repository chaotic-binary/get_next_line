A function which returns the next line from a file descriptor each time the function is called, without losing the reading thread.
Bonus is handling multiple file descriptors without losing thread of reading on any.

From subject:
Calling your function get_next_line in a loop will then allow you to read the text available on a file descriptor one line at a time until the EOF.
Your program must compile with the flag -D BUFFER_SIZE=xx. which will be used as the buffer size for the read calls in your get_next_line. This value will be modified by your evaluators and by moulinette.
Compilation will be done this way : gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c
Your read must use the BUFFER_SIZE defined during compilation to read from a file or from stdin.

int main()
{
    int fd, ret;
    char *str;
    fd = open("test.txt", O_RDONLY);
    while ((ret = get_next_line(fd, &str)) > 0)
    {
        printf("%s\n", str);
        free(str);
    }
    if (ret == 0)
    {
         printf("%s", str);
         free(str);
    }
    if (ret == -1)
        printf("%d", ret);
	close(fd);
    return (0);
}

Bonus part
To be able to manage multiple file descriptor with your get_next_line. For example, if the file descriptors 3, 4 and 5 are accessible for reading, then you can call get_next_line once on 3, once on 4, once again on 3 then once on 5 etc. without losing the reading thread on each of the descriptors.


int main()
{
    int fd1, fd2,ret;
    char *str;
    fd2 = open("test.txt", O_RDONLY);
    fd1 = open("test1.txt", O_RDONLY);

    if ((ret = get_next_line(fd1, &str)) != -1 )
    {
        printf("%s\n", str);
        free(str);
    }

    if (ret == -1)
        printf("%d", ret);

    if ((ret = get_next_line(fd2, &str)) != -1 )
    {
        printf("%s\n", str);
        free(str);
    }

    if (ret == -1)
        printf("%d", ret);

    if ((ret = get_next_line(fd1, &str)) != -1 )
    {
        printf("%s\n", str);
        free(str);
    }

    if (ret == -1)
        printf("%d", ret);

	close(fd);
    close(fd1);
    return (0);
}

