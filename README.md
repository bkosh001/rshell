rshell
======

Known bugs
----------

1. When using the ; connector in the command line with multiple arguments, our 
last command either gets an incorrect pointer error, or some unknown error. We 
believe that this is from when we parse the user string or extracting the 
tokenized c strings from the parsed line of the userinput.

2. We also have possible bugs with white space when combining commands. This
can come from the parsing algorithm as well.

3. Pound is not implemented. Inputing a sharp '#' will not result in a comment, 
but will result in it not executing