#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <queue>
#include <memory>
#include <sstream>
using namespace std;

class Disk{

public:

	Disk(){ diskNumber++; }
	unsigned int getDiskNumber() { return diskNumber; }

	bool empty(){ return disk.empty(); }

	void append(PCB aPCB){ disk.push(aPCB); } 

	PCB getFront() { return disk.front(); }

	unsigned int getFrontPriority() { return disk.front().getPriority(); }

	void removeFront(){ disk.pop(); }
	void print(){ 
		if(!disk.empty()){
			cout << "PID: " << disk.front().getPID() <<  " File Name: " << disk.front().getFileName() << endl;
		}
		else{
			cout << "There's no processes running in this I/O device\n";
		}
	}

private:
	queue<PCB>disk;
	unsigned int diskNumber;
};