# Chandy–Misra–Haas Algorithm for the OR model
This project is developed in `Windows 10 64 bit` in `Eclipse IDE for C/C++ Developers`.   
Compiler used: `MinGW's g++`  
You can install required compilers and packages in windows 10 by using this [link](http://win-builds.org/doku.php). Make sure that `Eclipse IDE for C/C++ Developers` can detect that `g++`.  
## Format of input   
Enter number of sites (Minimum value greater than 1):  
5  
Enter number of processes for site1: (Minimum value greater than 1)1  
Enter number of processes for site2: (Minimum value greater than 1)1  
Enter number of processes for site3: (Minimum value greater than 1)1  
Enter number of processes for site4: (Minimum value greater than 1)1  
Enter number of processes for site5: (Minimum value greater than 1)1  
Total number of sites = 5; Total number of processes = 5Enter the wait graph for processes; Enter 1 if the process is dependent and 0 if not.  
From Process 1 to : 1(1/0) :  
0  
From Process 1 to : 2(1/0) :  
0  
From Process 1 to : 3(1/0) :  
0  
From Process 1 to : 4(1/0) :  
0  
From Process 1 to : 5(1/0) :  
1  
From Process 2 to : 1(1/0) :  
0  
From Process 2 to : 2(1/0) :  
0  
From Process 2 to : 3(1/0) :  
0  
From Process 2 to : 4(1/0) :  
0  
From Process 2 to : 5(1/0) :  
0  
From Process 3 to : 1(1/0) :  
0  
From Process 3 to : 2(1/0) :  
0  
From Process 3 to : 3(1/0) :  
1  
From Process 3 to : 4(1/0) :  
0  
From Process 3 to : 5(1/0) :  
0  
From Process 4 to : 1(1/0) :  
0  
From Process 4 to : 2(1/0) :  
1  
From Process 4 to : 3(1/0) :  
0  
From Process 4 to : 4(1/0) :  
0  
From Process 4 to : 5(1/0) :  
1  
From Process 5 to : 1(1/0) :  
0  
From Process 5 to : 2(1/0) :  
0  
From Process 5 to : 3(1/0) :  
0  
From Process 5 to : 4(1/0) :  
0  
From Process 5 to : 5(1/0) :  
0  
  
The wait-for graph is:  
S1  S2  S3  S4  S5  
S1  0   0   0   0   1   
S2  0   0   0   0   0   
S3  0   0   1   0   0   
S4  0   1   0   0   1   
S5  0   0   0   0   0
  

Enter the process initiating the probe (Between 1 and no_of_process):   
2  

Initiating probe...  
DIRECTION   PROBE   MESSAGES  WAIT_FLAG  
S4 --> S2 (4,4,2) , 1 , 2  
S4 --> S5 (4,4,5) , 1 , 2   
Number of deadlocks detected:0  
Printing wait message array  
1  
0  
1  
2  
0  
Number of knots detected:0  
Equal number of Deadlock and Knot detected.   
 All sent messages were received.   
Hence the Chandy-Misra-Hass OR detected is validated.  

 

