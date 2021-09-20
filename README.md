# Flight-Gear-Interpreter
An Interpreter project for a FlightGear flight simulator. The program connects to the simulator and flys the aircraft based on text file contains code of the language that Dr. Eliahu Khalastchi has invented.
The project acts as both server (in order to send data to the flightgear simulator) and client (in order to receive data from the flightgear simulator).


# how to Run the program
first , you will need Linux environment to run the code.<br>
you can freely downlod the [Flightgear](https://www.flightgear.org/) simulator.you need this simulator for running the program.

Add the generic_small.xml file to the /data/Protocol directory where you installed the simulator (file of the flight simulator values)
Config the following settings in the 'Settings' tab in the simulator:

`--telnet=socket,in,10,127.0.0.1,5402,tcp` 

`--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small` 

This will open two communication sockets - 'in' where you send commands to the simulator, and 'out' where you receive data from it.


In order to run the project you need to clone it and use the following command in terminal:
```
 g++ -std=c++14 */*.cpp */*/*.cpp  *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
 ```
 Then, run:<br>
```
./a.out fly.txt 
```
**note:** you can use any file you want that is not the fly.txt that this project provided , but it need to be written according to the invented language and you need to use it properly. In your cusotmized script you must first open the client and server connection:<br>
openDataServer(5400)<br>
connectControlClient("127.0.0.1",5402)<br>
Then, you will start intializing your variables, loops and commands:<br>
 
The program will wait for a connection from the simulator.<br>
Click the 'Fly!' icon in the simulator in the bottom left corner, and wait for the simulator to load. It will connect to the interpreter in the meantime.<br>

When the text file is correctly written (as the fly.txt provided) you will see the plane takeoff and fly.<br>
 
