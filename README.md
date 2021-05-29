## pcap_lab 

Parallel Programming Lab 2021.
MIT-Manipal-6th Semester CSE.


### OpenMPI 
To compile the OpenMPI programs :

Here the filename.c is the input filename 

```bash 
    mpicc filename.c -o executablename
```

To run the program :- 

Assuming taking 4 processers(we can change that by passing in the args)

``` bash 
   mpirun -np 4 executablename
```

To check for synchronization status of all processes and messages we can use 
``` bash 
    mpitask 

```
Note : For using mpitask , you also need to install lamruntime in your system 





