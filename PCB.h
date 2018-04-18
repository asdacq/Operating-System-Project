#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <queue>
#include <memory>
#include <sstream>
#include "FrameTable.h"
using namespace std;


class PCB{

public:

	PCB() {};
	PCB(int num) :  priority(0), fileName(""), PID(num) {  }
	unsigned int getPID(){ return PID; }
	void setPriority(const unsigned int &priority){ this->priority = priority; }
	unsigned int getPriority() { return priority; } 
	void setFileName(const string &fileName){ this->fileName = fileName; }
	string getFileName(){ return fileName; }
	void setTableSize(unsigned int size) { pageTable.resize(size); }
	unsigned int getTableSize(){ return pageTable.size(); }

private:
	unsigned int PID;
	unsigned int priority;
	string fileName;
	// Stores the index where the process is being stored inside the Frame Table
	vector<int>pageTable;
};