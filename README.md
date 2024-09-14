# get_next_line
This project has proved extremely useful in later projects. Its function is to read from a file descriptor every 'line', defined as the string before a '\n'. This function must return every line (including the '\n'), and with the bonus, it must handle several fd's at the same time.

## About the restrictions
Moreover, we had some restrictions which made this project even more interesting. We couldn't use the libft, and we were limited to a maximum of 2 '.c' files with up to 5 functions per file, and 25 lines per function. This shouldn't be a huge limitation honestly, however the approach I followed (lists) made it a big barrier.

## About my approach
I decided to follow the 'lists' approach. This means that every fd to be read was stored as a node of a linked list. Other information, such as the actual buffer with the content read from the file, or the amount of bytes read is stored as well in the node.

This approach is certainly less efficient as others used out there, like having a 'map' of fds, with their respective buffers. However, I like to face these challenges in my own ways and do not usually like to follow strategies that I already know. In addition, I wanted to master linked lists before starting the next project: psuh_swap.
