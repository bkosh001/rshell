#!/bin/sh

(echo "x" && echo "y") || (echo "z" && echo "t")

(echo "x" && (echo "y" || echo "g")) #check

(echo "t"; echo "")

echo x && echo y || (echo f && echo g)

echo x && echo y || echo f && echo g

(echo l && echo z) || echo s && echo u

echo l && (echo t || echo r) && echo v

pwd && ((ls -al || clear) || touch README.md)

(pwd && (ls -al) || clear || touch README.md)

clear ; (echo t && (echo c ; touch README.md)) #check

echo l || (echo g && echo t) # && echo hello || echo r) && echo v

echo "8" ; (echo g && echo p && (echo s && echo t ; echo n) && echo "bonfire")

echo "8" ; (echo g && echo p && ((echo s && echo t)|| echo n) && echo "bonfire")