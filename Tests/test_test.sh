#!/bin/sh

test rshell
test -e rshell
test -d rshell
test -f rshell

[ rshell ]
[ -e rshell ]
[ -d rshell ]
[ -f rshell ]

mkdir Folder
test Folder
test -e Folder
test -d Folder
test -f Folder

[ Folder ]
[ -e Folder ]
[ -d Folder ]
[ -f Folder ]