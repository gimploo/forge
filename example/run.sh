#!/usr/bin/bash

cmd.exe /c build deepclean
rm build.bat
cp ../build.bat .
cmd.exe /c build
