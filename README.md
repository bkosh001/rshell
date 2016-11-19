rshell
======

Known bugs
----------

1. There is a case when exit does not work as intended. Upon executing an 
   "incorrect" input, the exit command must be executed multiple times. We 
   believe that this an issue with executing the commands themselves.
2. We have possible memory leaks.