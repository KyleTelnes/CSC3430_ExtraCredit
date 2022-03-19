# CSC3430_ExtraCredit - Kyle Telnes
Implementing Dynamic Programming Weighted Interval Scheduling

# Information
This program, written in C++, implements a dynamic programming solution to the weighted interval scheduling problem. It takes a csv file of requests
in the format of: startTime,finishTime,weight -- and produces the requests that are mutually compatible and yield the maximum weight. This uses the 
C++ vector library to store the requests extracted from the file and the C++ algorithm library to sort those requests by finish time. The sorting
algorithm runs in O(nlogn) time, as stated on the C++ reference website. There is also some processing done to find p(j), or the mutually compatible 
request closest to request j looking backwards. That processing takes O(n^2) time in its worst case. This makes the whole algorithm run in O(n^2) in its
worst case.

# Running the program
To run this program, you must first clone this repository. After that, in command line, change to the directory where this repository is cloned to on
your computer. As long as you have a C++ compiler, you will be able to run this command: 
<div><b>g++ -Wall main.cpp -o intSchedule</b></div>
To compile the program. This will create an executable called intSchedule, and running the command:
<div><b>./intSchedule</b></div>
in command line will execute the program. You can also change the data in the requests.csv file in a text editor, in order to test the program with 
different inputs, just make sure to save the file after you have made changes to it.
