# get_next_line
#### This is the get next line project done @ 42 Paris
[125/100][Subject] (https://github.com/ablin42/getnextline/blob/master/get_next_line.pdf) 

Whether it's from a file, the standard input, or even from a network connection later on, you'll need a way to read data one line at a time. Now is the time to write such a function, essential for several of your next projects.

#### The prototype is get_next_line(int fd, char **line);
The functions returns -1 if an error occured, 1 if it successfully read a line, and 0 if it reached the end of the file being read.

### Objectives
> - File descriptors 
> - Buffering 
> - Basic parsing 
> - Memory allocation (stack/heap)
> - Static Vars

### Skills
> - Imperative programming
> - Algorithms & AI
> - Rigor

### Instructions
> - Write a function that returns a line read from a file descriptor
> - Return result without the "\n"
> - Loop calls must read a file line by line
> - Read from file/STDIN/redirection

### Restrictions
> - Only two files allowed (get_next_line.c/get_next_line.h)
> - Libft allowed
> - No main function
> - No Makefile
> - Error handling, no errors allowed
> - Memory allocated MUST be freed
> - Global vars are FORBIDDEN

### Bonuses
> - Use a single static var
> - Can handle multiple file descriptors at once and alternatively
