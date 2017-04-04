***File Transfer Server***

To compile: gcc -o ftserver ftserver.c

To run: ./ftserver <port>

To exit server: Hit CTRL-C.

Server supports multiple connections by waiting for a connection, accepting it with accept(), and then using fork() to spawn a child process to handle it.



***File Transfer Client***

To run: python ftclient.py <host> <control port> <command> <data port> <filename>

Commands supported: -l which lists files in the server's current working directory.
-g which will initiate a file transfer of the specified file.

Max filesize: 8192 bytes

