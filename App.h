#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <queue>
#include <memory>
#include <sstream>
#include <exception>
#include "Driver.h"
using namespace std;

class App{

public:
	void run(){
		driverObj.generateSystem();
		cin.ignore();
		string command;
		unsigned int counter = 0;
		while(true){
			cout << "Enter a command" << endl;
			getline(cin, command);
			if(command.substr(0,1) == "A"){
				if(command.find(" ") == -1){
					cout << "Invalid command\n";
					continue;
				}
				PCB newPCB(++counter);
				newPCB.setTableSize(driverObj.section);
				command = command.substr(command.find(" ")+1, command.length()-2);
				try{
					stoi(command);
				}
				catch(exception e){
					cout << "Input is not an integer\n";
					continue; 
				}
				newPCB.setPriority(stoi(command));
				driverObj.addPCB(newPCB);
				driverObj.addEntry(newPCB);
			}
			else if(command == "t"){
				driverObj.terminate();
			}
			else if(command.substr(0,1) == "d"){
				if(command.find(" ") == -1){
					cout << "Invalid command\n";
					continue;
				}
				command = command.substr(command.find(" ")+1, command.length()-2);
				if(command.find(" ") == -1){
					cout << "Invalid command\n";
					continue;
				}
				try{
					stoi(command.substr(0, command.find(" ")));
				}
				catch(exception e){
					cout << "Input is not an integer\n";
					continue; 
				}
				unsigned int diskNumber = stoi(command.substr(0, command.find(" ")));
				if(driverObj.cpuEmpty()){
					cout << "CPU is empty\n";
					continue;
				}
				if(diskNumber >= driverObj.dqSize()){
					cout << "Invalid hard disk number.\n";
					continue;
				}
				command = command.substr(command.find(" ")+1);
				driverObj.dCommand(diskNumber, command);
			}
			else if(command.substr(0,1) == "D"){
				if(command.find(" ") == -1){
					cout << "Invalid command\n";
					continue;
				}
				command = command.substr(command.find(" ")+1, command.length()-2);
				try{
					stoi(command);
				}
				catch(exception e){
					cout << "Input is not an integer\n";
					continue; 
				}
				int number = stoi(command);
				if(number >= driverObj.dqSize()){
					cout << "Invalid hard disk number.\n";
					continue;
				}
				driverObj.removeFromDisk(number);
			}
			else if(command.substr(0,1) == "m"){
				if(command.find(" ") == -1){
					cout << "Invalid command\n";
					continue;
				}
				command = command.substr(command.find(" ")+1, command.length()-2);
				try{
					stoi(command.substr(0, command.find(" ")));
				}
				catch(exception e){
					cout << "Input is not an integer\n";
					continue; 
				}
				int memoryAddress = stoi(command.substr(0, command.find(" ")));
				driverObj.addEntry(memoryAddress);
			}
			else if(command.substr(0,1) == "S"){
				if(command.find(" ") == -1){
					cout << "Invalid command\n";
					continue;
				}
				command = command.substr(command.find(" ")+1, command.length()-2);
				if(command == "r"){
					driverObj.printCPU();
					driverObj.printRQ();
				}
				else if(command == "i"){
					driverObj.printDisks();
					driverObj.printDQ();
				}
				else if(command == "m"){
					driverObj.printFrame();
				}
				else{
					cout << "Invalid S command\n";
				}
			}
			else{
				cout << "Invalid command!" << endl;
			}
		}
	}
private:
	Driver driverObj;

};