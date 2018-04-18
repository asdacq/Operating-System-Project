#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <queue>
#include <cmath>
#include <memory>
#include <sstream>
#include "PCB.h"
#include "ReadyQueue.h"
#include "Disk.h"
#include "CPU.h"
#include "RAM.h"
#include "DiskQueue.h"
using namespace std;

// Global Variable to keep track of LRU
size_t counter = 1;

class Driver{

public:

	// Public variable to keep track of the the number of pages / frames
	unsigned int section = 0;
	// Public variable to keep track of number of bytes of each section
	unsigned long long int size = 0;

	void generateSystem(){
		long long int ramSize, pageSize;
		unsigned int numberOfDisks;
		cout << "How much RAM memory is there on the simulated computer? ";
		cin >> ramSize;
		while(ramSize  > 4000000000){
			cout << "Please enter a number up to 4 billion: ";
			cin >> ramSize;
		}
		cout << "What's the size of the frame / page? ";
		cin >> pageSize;
		while((pageSize <= 0)){
				cout << "Enter a number that's not less than 1: ";
			cin >> pageSize;
		}
		size = pageSize;
		cout << "How many hard disks does the simulated computer have? ";
		cin >> numberOfDisks;
		while(numberOfDisks < 1){
			cout << "Please enter a number greater than 0" << endl;
			cin >> numberOfDisks;
		}
		dq.resize(numberOfDisks);
		disk.resize(numberOfDisks);
		section = ramSize/pageSize;
		ram.setTableSize(section);
	}

	void addPCB(PCB aPCB){
		// If empty place PCB into CPU
		if(cpu.empty()){
			cpu.append(aPCB);
			return;
		}
		// Checks priority of the incoming PCB & PCB in the CPU
		// If incoming PCB has higher priority, preempt the PCB
		if(cpu.getFrontPriority() < aPCB.getPriority()){
			PCB cpuPCB = cpu.getFront();
			PCB tempPCB = aPCB;
			cpu.removeFront();
			cpu.append(tempPCB);
			rq.append(cpuPCB);
			return;
		}
		rq.append(aPCB);
	}

	void terminate(){
		if(cpu.empty()){
			cout << "CPU is empty!\n";
			return;
		} 
		ram.removeFromTable(cpu.getFront().getPID());
		cpu.removeFront();
		if(!rq.empty()){
			cpu.append(rq.getFront());
			rq.removeFront(); 
		}
	}

	void printRQ(){ rq.print(); }
	void printCPU(){ cpu.print(); }
	void printDQ(){ dq.print(); }
	void printDisks(){
		cout << "\t\t[I/O Devices]\t\t\n";
		unsigned int index = 0;
		/*
		for(auto i : disk){
			if(!i.empty()){
				cout << "I/O Device " << index++ <<":  ";  
				i.print();
			}
		}
		*/
		for(int i = 0; i < disk.size(); i++){
			if(!disk[i].empty()){
				cout << "I/O Device " << i <<":  ";  
				disk[i].print();
			}
		}
	}
	void printFrame(){ ram.print(); }

	unsigned int dqSize(){ return dq.size(); }
	bool cpuEmpty() { return cpu.empty(); }
	bool rqEmpty(){ return rq.empty(); }

	void dCommand(const unsigned int &diskNumber, const string &fileName){
 		if(cpu.empty()){
			cout << "There's processes running in the CPU.\n";
			return;
		}
		cpu.rename(fileName);
		dq.append(diskNumber, cpu.getFront());
		cpu.removeFront();
		// Append the next PCB into the empty CPU
		if(!rq.empty()){
			cpu.append(rq.getFront());
			rq.removeFront();
		}
		if(disk[diskNumber].empty()){
			disk[diskNumber].append(dq.getFront(diskNumber));
			dq.removeFront(diskNumber);
		}
	}

	void removeFromDisk(const int &diskNumber){

		if(disk[diskNumber].empty()) { 
			cout << "Driver is empty\n";
			return; 
		}
		if(cpuEmpty()){
			cpu.append(disk[diskNumber].getFront());
			disk[diskNumber].removeFront();
			dqToDisk(diskNumber);
			return;
		}
		if(disk[diskNumber].getFront().getPriority() > cpu.getFront().getPriority()){
			PCB temp = cpu.getFront();
			cpu.removeFront();
			rq.append(temp);
			PCB temp2 = disk[diskNumber].getFront();
			cpu.append(temp2);
			disk[diskNumber].removeFront();
			dqToDisk(diskNumber);
			return;
		}
		// Adds the PCB in the Ready Queue
		rq.append(disk[diskNumber].getFront());
		disk[diskNumber].removeFront();
		dqToDisk(diskNumber);
	}

	bool dqToDisk(const unsigned int &diskNumber){
		if(dq.emptyIndex(diskNumber)) { return false; }
		// Automatically adds PCB from the Device Queue into Disk
		disk[diskNumber].append(dq.getFront(diskNumber));
		dq.removeFront(diskNumber);
		return true;
	}

	size_t getTableSize(PCB temp){ return temp.getTableSize(); }
	size_t getFrameSize() { return ram.getTableSize(); }

	bool addEntry(size_t memoryAddress){
		size_t page = 0;
		page = memoryAddress / size;
		if(page >= section){
				cout << "Memory address greater than the number of pages / frames" << endl;
				return false;
			}
		if(!cpuEmpty()){
			if(ram.renewLRU(page, cpu.getFront().getPID(), counter)){
				return true;
			}
			if(ram.findEmptyEntry() == -1){
				ram.replaceEntry(page, cpu.getFront().getPID(), counter);
				return true;
			}
			ram.addEntry(memoryAddress, size, cpu.getFront().getPID(), counter);
			return true;
		}
		cout << "Cannot perform operation.\n";
		return false;
	}

	bool addEntry(PCB newProcess){
		if(ram.addEntry(0, newProcess.getPID(), counter)){
			return true;
		}
		if(!(ram.addEntry(0, newProcess.getPID(), counter))){
			if(ram.findEmptyEntry() == -1){
				ram.replaceEntry(0, newProcess.getPID(), counter);
				return true;
			}
		}
		cout << "Cannot perform operation.\n";
		return false;
	}

private:
	ReadyQueue rq;
	CPU cpu;
	DiskQueue dq;
	vector<Disk>disk;
	RAM ram;
};