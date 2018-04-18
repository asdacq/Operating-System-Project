#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <queue>
#include <memory>
#include <sstream>
using namespace std;

class CPU{

public:
	bool empty(){ return cpu.empty(); }

	void append(PCB aPCB){ cpu.push(aPCB); } 

	PCB getFront() { return cpu.front(); }

	unsigned int getFrontPriority() { return cpu.front().getPriority(); }

	void removeFront()  { cpu.pop(); }

	void print(){ 
		cout << "\t\t[CPU]\t\t\n";
		if(!cpu.empty()){
			cout << "PID: " << cpu.front().getPID() <<  " Priority: " << cpu.front().getPriority() << endl;
		}
	}

	void rename(const string &fileName){ cpu.front().setFileName(fileName); }

private:
	queue<PCB>cpu;
};