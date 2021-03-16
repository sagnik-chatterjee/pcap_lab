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



### Strutcure of the directory:
```bash 
.
├── etc
│   ├── sample_mpi.c
│   └── saple_openmpi.c
├── opencl
│   ├── Benedict - Heterogeneous_computing_OpenCL.pdf
│   └── week5
│       ├── Class4-B.pdf
│       └── sample
│           └── vecAddn.c
├── openmpi
│   ├── runProgram.sh
│   ├── week1
│   │   ├── 180905478_Sagnik_Week1.odt
│   │   ├── 180905478_Sagnik_Week2.odt
│   │   ├── bufferSendString.c
│   │   ├── cvector.h
│   │   ├── even_hello.c
│   │   ├── power_rank.c
│   │   ├── prime2.c
│   │   ├── q1
│   │   ├── q1_addn.c
│   │   ├── q1.c
│   │   ├── q2
│   │   ├── q2.c
│   │   ├── q3
│   │   ├── q3_1
│   │   ├── q3_1.c
│   │   ├── q3.c
│   │   ├── q4
│   │   ├── q4.c
│   │   ├── q5.c
│   │   ├── q6.c
│   │   ├── reverseDigits.c
│   │   ├── simple_calc.c
│   │   ├── ss
│   │   │   ├── q1.png
│   │   │   ├── q2.png
│   │   │   ├── q3.png
│   │   │   └── q4.png
│   │   ├── standardSend.c
│   │   ├── toggle
│   │   └── toggle_character.c
│   ├── week2
│   │   └── ss
│   │       ├── q1.png
│   │       ├── q2.png
│   │       ├── q3_1.png
│   │       ├── q3.png
│   │       └── q4.png
│   ├── week3
│   │   ├── 180905478_week3_sagnik.odt
│   │   ├── hashMap.c
│   │   ├── hashMap.h
│   │   ├── q1
│   │   ├── q1.c
│   │   ├── q2
│   │   ├── q2.c
│   │   ├── q3
│   │   ├── q3.c
│   │   ├── q4
│   │   ├── q4.c
│   │   └── ss
│   │       ├── q1.png
│   │       ├── q2.png
│   │       ├── q3_1.png
│   │       ├── q3.png
│   │       └── q4.png
│   └── week4
│       ├── lib
│       │   ├── q1
│       │   ├── q1.c
│       │   ├── q2_temp
│       │   ├── q2_temp.c
│       │   ├── q3
│       │   ├── q3.c
│       │   ├── q4
│       │   ├── q4.c
│       │   └── ss
│       │       ├── q1.png
│       │       ├── q2_1.png
│       │       ├── q2.png
│       │       ├── q3.png
│       │       └── q4.png
│       ├── q1.c
│       ├── q2.c
│       ├── q3.c
│       ├── q4.c
│       └── WEEK4_Sagnik_180905478.odt
├── prac
│   ├── bufferedBSend.c
│   ├── sample_mpi.c
│   └── saple_openmpi.c
├── README.md
└── Revised_Parallel Programming Lab Manual 2020_CSE_3263.pdf

15 directories, 79 files
```