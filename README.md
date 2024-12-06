# System Programming Lab 11 Multiprocessing
## Process
For this lab I created a new file called mandelmovie.c. In this file I knew I wanted to use a semaphore to control the process. I thought about how each image could be divided equally into the processes using the semaphore. If i set the semaphore to control the number of processes made and then just set a for loop to loop through each image and continuously make processes. After each image is made the program waits for the programs to end and then cleans up.
## Graph
![Graph of runtime vs num processes](graph.png)
## Conclusion
You would think the findings would be an exponential descrease in time as the program would run so much faster with 20 processes instead of 10 compared to 5 processes instead of 2. The time does decrease but it is not as exponential as you would think. The difference between 10 and 20 processes is very minimal.
# Systems Programming Lab 12 Multithreading
## Implementation
I realized the best way to implement this was to rewrite the compute_image function to include threads in there. I took out the main image processing and added a start row and an end row to the function parameters in order to edit what is done by each thread. I had to create a new structure in order to pass in all of the arguments and pack and unpack it at the beginning of the thread kickoff and the beginning of the thread function. Other than adding the command line argument nothing else really changed. 
## Graph
| Num Processes | 20   | 10   | 5   | 2  | 1  | Num Threads |
|---------------|-----|-----|-----|-----|-----|-------------|
| 20            | 15  | 15  | 13  | 13  | 16  |             |
| 10            | 13  | 14  | 13  | 15  | 18  |             |
| 5             | 13  | 13  | 18  | 18  | 22  |             |
| 2             | 16  | 20  | 28  | 29  | 43  |             |
| 1             | 22  | 28  | 31  |  47 |  35 |             |
## Conclusion
### Multiprocessing effect vs Multithreading
The multiprocessing had a stronger impact than multithreading. The difference between multiple processes was way faster than the difference between threads which only knocked off a few seconds. 
### Opitmal sweet spot?
The Optimal sweet spot was roughly 10 processes and between 10 and 20 threads. I experienced the fastest runtime for these times. 