#!/bin/sh

echo "x" && echo "y"

echo "x" ; echo "y"

echo "x" || echo "y"

echo "x" && echo "y" || echo "z"

echo "x" && echo "y" ; echo "z"

echo "x" && echo "y" && echo "z"

echo "x" ; echo "y" || echo "z"

echo "x" ; echo "y" ; echo "z"

echo "x" ; echo "y" && echo "z"

echo "x" || echo "y" || echo "z"

echo "x" || echo "y" ; echo "z"

echo "x" || echo "y" && echo "z"