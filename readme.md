A function which returns the next line from a file descriptor each time the function is called, without losing the reading thread.</br>
Bonus is handling multiple file descriptors without losing thread of reading on any.</br>
Calling <code>get_next_line</code> in a loop will then allow you to read the text available on a file descriptor one line at a time until the EOF.</br>
Function uses the BUFFER_SIZE defined during compilation to read from a file or from stdin.


Example compilation: <code>gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c</code>
