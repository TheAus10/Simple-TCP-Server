# Simple-TCP-Server
A simple wordcount server using TCP sockets.

### Overview
A server created using TCP sockets that takes in a given sentence from the client and returns the number of letters, number of spaces, number of vowels, and a formatted version of the given sentence. The formatted sentence is returned with the first letter capitalized, and every other letter lowercase. Developed in a Linux environment using TCP sockets, string manipulation, and memory manipulation.

### To Run
There is a makefile included. Run the `make` command to compile the code. This will generate an executable for the client and the server, named `client` and `server` respectively. Run each of these with the same port number as a command line argument.
  
  *Note, server is hardcoded to run a specific server. This will likely need to be changed per usage.

### To Use
On the client side, user will be prompted for an input. Enter a sentence and the server will return the user the formatted sentence, the number of letters, the number of vowels, ad the number of spaces. It will continue to prompt in a loop until the user enters `quit`. 
