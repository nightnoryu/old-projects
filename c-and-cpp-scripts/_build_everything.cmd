@echo off

rem Build C programs
forfiles /m *.c /c "cmd /c gcc @file -o @fname"
rem Build C++ programs
forfiles /m *.cpp /c "cmd /c g++ @file -o @fname"

rem Move the executables
mkdir dist
move /y *.exe dist\
