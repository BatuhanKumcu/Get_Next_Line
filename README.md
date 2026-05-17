*This project has been created as part of the 42 curriculum by bakumcu.*

# GET_NEXT_LINE

## Description

In short, **get_next_line** is a 42 curriculum project that focuses on reading text from a file descriptor one line at a time.

The goal of this project is to write a function that returns the next available line from a file descriptor each time it is called. This includes reading from regular files, standard input, and other valid file descriptors while correctly handling memory allocation, buffer management, and end-of-file behavior.

This project introduces one of the most important concepts in C programming: **static variables**. By using a static variable, the function can preserve unread data between multiple calls and continue reading from where it stopped.

## Project Overview

### Mandatory Function

| Function | Prototype | Description |
|----------|-----------|-------------|
| `get_next_line` | `char *get_next_line(int fd);` | Returns the next line read from a file descriptor |

The function returns:

| Return Value | Description |
|--------------|-------------|
| A line | The next line read from the file descriptor |
| `NULL` | Nothing else to read or an error occurred |

The returned line includes the terminating newline character `\n`, except when the end of the file is reached and the file does not end with a newline.

## Submitted Files

The mandatory part of the project contains the following files:

| File | Description |
|------|-------------|
| `get_next_line.c` | Contains the main `get_next_line` logic and static stash management |
| `get_next_line_utils.c` | Contains helper functions used by `get_next_line` |
| `get_next_line.h` | Contains function prototypes, required includes, and `BUFFER_SIZE` handling |

## Function Overview

### Main Logic

| Function | Description |
|----------|-------------|
| `get_next_line` | Checks the file descriptor, reads data, extracts a line, and updates the leftover stash |
| `ft_read_store_line` | Reads from the file descriptor until a newline is found or the end of file is reached |
| `ft_write_line` | Extracts the current line from the stored data |
| `ft_make_leftover` | Saves the remaining characters after the newline for the next function call |
| `ft_join_and_free` | Joins the stash with the new buffer and frees the old stash |

### Utility Functions

| Function | Description |
|----------|-------------|
| `ft_strlen` | Calculates the length of a string |
| `ft_strchr` | Locates the first occurrence of a character in a string |
| `ft_strjoin` | Joins two strings into a newly allocated string |
| `ft_strdup` | Duplicates a string into newly allocated memory |
| `ft_substr` | Extracts a substring from a string |

## Algorithm Explanation

The selected algorithm is based on keeping a persistent storage area called a **stash**.

Since `read()` does not necessarily stop at the end of a line, one call may read more data than needed. For example, the buffer may contain the current line and part of the next line. The extra data must not be lost. To solve this, the project uses a static variable that remains available between calls to `get_next_line`.

The algorithm works in four main steps:

1. **Validate input**

   The function first checks whether the file descriptor is valid and whether `BUFFER_SIZE` is greater than zero. If not, it returns `NULL`.

2. **Read and store**

   Data is read from the file descriptor into a temporary buffer. The buffer is joined to the existing stash. Reading continues until a newline character is found or until `read()` reaches the end of the file.

3. **Extract the line**

   Once the stash contains either a newline or the remaining end-of-file content, the function extracts the line that must be returned. If a newline exists, the returned string includes it.

4. **Update the stash**

   After extracting the line, the function keeps only the characters that appear after the newline. This leftover content is saved in the static stash and will be used during the next call. If there is no leftover content, the stash is freed and set to `NULL`.

This approach is appropriate because it avoids reading the entire file at once. Instead, it reads only as much as necessary to return the next line, while preserving unused data for future calls.

## Instructions

### Requirements

- GCC or CC compiler
- Unix-based operating system such as Linux or macOS
- Standard C library
- 42 Norm compatibility

### Allowed External Functions

| Function | Purpose |
|----------|---------|
| `read` | Reads data from a file descriptor |
| `malloc` | Allocates memory dynamically |
| `free` | Frees dynamically allocated memory |

### Forbidden

| Forbidden Element | Reason |
|-------------------|--------|
| `libft` | The project must be implemented without using your libft |
| `lseek` | The reading position must not be manually changed |
| Global variables | The project must rely on static storage, not global variables |

## Compilation

The project must be compiled with the following flags:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` can be changed during compilation:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c
```

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 get_next_line.c get_next_line_utils.c
```

The project should also compile without explicitly defining `BUFFER_SIZE`, because a default value is provided in the header file.

## Usage

Example test program:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```

Compile example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl_test
```

Run:

```bash
./gnl_test
```

## Testing

Recommended test cases:

| Test Case | Expected Behavior |
|-----------|-------------------|
| Empty file | Returns `NULL` |
| File with one line ending in `\n` | Returns the line including `\n`, then `NULL` |
| File with one line without `\n` | Returns the line, then `NULL` |
| Multiple lines | Returns one line per call |
| Very long line | Correctly joins multiple reads |
| `BUFFER_SIZE=1` | Still reads correctly, one character at a time |
| Large `BUFFER_SIZE` | Still reads correctly without reading invalid memory |
| Invalid file descriptor | Returns `NULL` |
| Standard input | Reads from `stdin` correctly |

Example compilation for testing different buffer sizes:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 main.c get_next_line.c get_next_line_utils.c -o gnl_test
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl_test
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 main.c get_next_line.c get_next_line_utils.c -o gnl_test
```

## Bonus

The bonus part of the project requires `get_next_line` to manage multiple file descriptors at the same time.

Bonus files must use the `_bonus` suffix:

| File | Description |
|------|-------------|
| `get_next_line_bonus.c` | Bonus version of the main function |
| `get_next_line_bonus.h` | Bonus header file |
| `get_next_line_utils_bonus.c` | Bonus utility functions |

The bonus part is evaluated only if the mandatory part works perfectly.

## Project Notes

- The function must not cause segmentation faults, double frees, or memory leaks.
- Every allocated line returned by `get_next_line` must be freed by the caller.
- The implementation should work with different `BUFFER_SIZE` values.
- The project should be tested with both files and standard input.
- Binary file behavior is considered undefined by the subject.

## Resources

### Documentation & References

- 42 Cursus Get Next Line Subject - official project requirements
- [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language) - classic C reference book
- [man7.org - read(2)](https://man7.org/linux/man-pages/man2/read.2.html) - Linux manual page for `read`
- [man7.org - open(2)](https://man7.org/linux/man-pages/man2/open.2.html) - Linux manual page for `open`
- [man7.org - malloc(3)](https://man7.org/linux/man-pages/man3/malloc.3.html) - Linux manual page for dynamic memory allocation
- [cppreference.com - C File Input/Output](https://en.cppreference.com/w/c/io) - C input/output reference
- [cppreference.com - Static Storage Duration](https://en.cppreference.com/w/c/language/storage_duration) - explanation of static variables and storage duration

### AI Usage

AI tools were used as a supplemental learning and documentation resource while preparing this README.

Specifically, AI was used to:

* Organize the project explanation into a clear README format.
* Explain the algorithm in a readable way.
* Summarize the role of static variables, buffers, and leftover data.
* Prepare testing suggestions and usage examples.
* Ensure that the README includes the required 42 sections: description, instructions, resources, and algorithm explanation.

The project code itself should be understood, tested, and defended by the student. AI was not used as a replacement for learning the logic of the project.

---

**Author:** bakumcu@student.42istanbul.com.tr

**Note:** This README file was written with the assistance of AI.
