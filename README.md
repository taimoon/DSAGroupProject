# DSAGroupProject

## Hindsight
1. We could use makefile software, rather using custom build file

## Introduction
It is a group project for the course data structure and algorithm using C. To students, the project is aimed to practice using apporiate data structure and algorithm in solving computational problem. This project is about implementing inventory management app which is a subset of the warehouse management. We restricted the app to record the inbound and outbound requests. A request record dates, and possibly contain many items with quantities. It is nature choice to use queue to record these requests assuming the business rule is first come first served; first in first out.

We have implemented the circular linked list, singly linked list, C-styled sort and dynamic array (C++ vector).

Dynamic array is a data structure similar to C array but it automatically shrink or grow depending how much data it holds. It mimicks the functionality of vector from C++ STL. 

Conditional compilation through marco, generic pointer and function pointer are perculiarities encountered in using C that we believe we have applied some of them in our project.

The file "Sort Algorithm.h" contains binary search and quick sort functions which is a good example to understand how C implement the sort function. It is an example implementation of generic sort using C using function pointer and generic pointer.

## Challenges
- Developing serialization of linked-list data
- Making sort algorithm generic; applicable to all kind data structure

## Group 11
### Group members:
- LEONG TENG MAN
- TAN WEI QING
- NG JIE HAO
- SOON KIEN YUAN
- KHAIRUL IMRAN BIN JAMALULLAIL
# Compilation
- You may click the builder.exe to compile a file called "driver.exe". This can be fail if there is no path to gcc compiler on your pc.
- You may compile from the file "driver.c"
# Exe Files
- builder.exe : build the exe from c source codes
- driver.exe : the app
- backup.exe : back up the product list, inbound request list, outboud request list
- retrieve.exe : retrieve the backup data
Note that backup and retreive only work on window pc.
# Note for CodeBlock user
You may click the file warehousemanagement.cbp to access the project.
# Problem
- using 2018 gnu compiler might result the exe crash. Solution: use other version. 
