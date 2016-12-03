#!/bin/sh

cd ..

cd -

cd 

cd && cd -

cd .

cd ../../../..

cd && cd ../.. && cd -

cd && cd && cd && cd && cd && cd

(cd && cd ..) || echo "failed"

(cd . && cd ..) && echo "passed"

cd src

cd bin && ./rshell

cd Tests ; cd -

cd .. ; cd

cd ; pwd

cd - && cd -

mkdir file && cd file && cd .. && rm -r file && cd -