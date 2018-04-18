#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class RAM{

public:

	RAM() {}
	void setMemory( unsigned long long int memory ) { this->memory = memory; }
	unsigned int getMemory(){ return memory; }

	void setTableSize(unsigned int size) { frameTable.resize(size); }
	unsigned int getTableSize(){ return frameTable.size(); }

	int findEmptyEntry(){
		for(int i = 0; i < frameTable.size(); i++){
			if(frameTable[i].getPID() == 0){
				return i;
			}
		}
		return -1;
	}

	bool doesEntryExist(size_t pageNumber, size_t PID){
		for(auto &i :frameTable){
			if(i.getPageNumber() == pageNumber && i.getPID() == PID){
				return true;
			}
		}
		return false;
	}

	bool renewLRU(size_t pageNumber, size_t PID, size_t &counter){
		for(auto &i :frameTable){
			if(i.getPageNumber() == pageNumber && i.getPID() == PID){
				i.setLRU(counter++);
				return true;
			}
		}
		return false;
	}

	bool replaceEntry(size_t pageNumber, size_t PID, size_t &counter){
		size_t index = 0;
		size_t min = numeric_limits<size_t>::max();
		if(findEmptyEntry() == -1){
			FrameTable replacement(pageNumber, PID, counter++);
			for(size_t i = 0; i < frameTable.size(); i++){
				if(frameTable[i].getLRU() < min ){
					min = frameTable[i].getLRU();
					index = i;
				}
			}
			frameTable[index] = replacement;
			return true;
		}
		return false;
	}

	bool addEntry(size_t memoryAddress, size_t pageSize, size_t PID, size_t &counter){
		size_t pageNumber = memoryAddress / pageSize;	
		if(findEmptyEntry() != -1){
			FrameTable entry(pageNumber, PID, counter++);
			frameTable[findEmptyEntry()] = entry;
			return true;
		}
		return false;
	}

	bool addEntry(size_t pageNumber, size_t PID, size_t &counter){
		if(findEmptyEntry() != -1){
			FrameTable entry(pageNumber, PID, counter++);
			frameTable[findEmptyEntry()] = entry;
			return true;
		}
		return false;
	}

	void print(){
		cout << "\t\t[Frame Table]\t\t\n";
		cout << "Frame\tPage Number\tPID\tLRU\n";
		int index = 0;
		for(auto &i : frameTable){
			cout << index++ <<"\t"<< i.getPageNumber() << "\t\t" << i.getPID() << "\t" << i.getLRU() << endl; 
		}
	}

	void removeFromTable(size_t findPID){
		for(int i = 0; i < frameTable.size(); i++){
			if(frameTable[i].getPID() == findPID){
				frameTable[i].setPageNumber(0);
				frameTable[i].setPID(0);
				frameTable[i].setLRU(0);
			}
		}
	}
private:
	unsigned long long int memory;
	vector<FrameTable>frameTable;
};
