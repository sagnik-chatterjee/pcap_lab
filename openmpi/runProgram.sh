#!/bin/bash 
## running mpi programs 
echo "Ensure that mpi is installed and in path 
and include mpi.h in your c file."
# compile the program 
mpicc $1.c -o $1 -lm ## to link with math library if present 

# ask user for the number of processes 
echo "Enter the number of processes"
read varname 
#execute 
mpirun -np varname $1  
