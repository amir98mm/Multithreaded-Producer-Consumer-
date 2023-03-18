# Multithreaded Producer-Consumer Queue

This is a simple multithreaded C++ program that demonstrates the producer-consumer problem.
The program allows the user to specify the number of producers, number of consumers, and queue size, and then starts the specified number of producer and consumer threads. The producers generate random numbers and add them to a shared buffer, while the consumers retrieve numbers from the buffer and print them to the console.

This program was created as a learning project. The code demonstrates the use of mutexes, condition variables, and thread synchronization techniques to ensure correct operation of the producer-consumer system.

## How to Run
To run the program, simply compile the source code using a C++ compiler (such as g++ or clang++) and execute the resulting binary. Upon running the program, the user will be prompted to enter the number of producers, number of consumers, and queue size.

Alternatively, you can run the program by executing the 'MultiThread.exe' file located in the folder.

To stop the program, you can either press the Enter key or use the Ctrl+C signal handler. The program will stop once all the threads have finished their execution.

## Examples
### First : 
![image](https://user-images.githubusercontent.com/75622732/226123558-0d14b51e-3f6a-4e38-90c3-5a8e1a336c86.png)

### Second :
#### queue of size 1, so can't add until we consume the data
![image](https://user-images.githubusercontent.com/75622732/226123963-28ea399f-a76c-49bd-8ba0-d5e26f0a3881.png)


# License & Credits
This program was created by Amir Mahamid as a learning project.
This project is licensed under the MIT License. See the LICENSE file for details.


