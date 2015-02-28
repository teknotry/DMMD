# DMMD
Distributed Main Memory Database

Pre-requisite
Install Unix odbc,thread libaray and GTK+-2.0 library

Command to create the main server 
cd mainserver
compile :
gcc -o mainserver *.c -lpthread -lmyodbc5 -w
Run 
./mainserver


Command to create the intermediate server :

cd subserver
gcc -o subserver *.c -w
./subserver

Create client: 
client is created with GTK+-2.0 so import the client directory in the GTK SDK and run .



