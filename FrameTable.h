#include <iostream>
using namespace std;


// Each process should have a frame table
class FrameTable{

public:

	FrameTable() : pageNumber(0), PID(0), LRU(0) { }
	FrameTable(unsigned int pageNumber, unsigned int PID, unsigned int LRU){
		this->pageNumber = pageNumber;
		this->PID = PID;
		this->LRU = LRU;
	}

	void setPID(unsigned int PID) { this->PID = PID; }
	void setPageNumber(unsigned int pageNumber) { this->pageNumber = pageNumber; }
	void setLRU(unsigned int LRU) { this->LRU = LRU; }

	unsigned int getPageNumber(){ return pageNumber; }
	unsigned int getPID(){ return PID; }
	unsigned int getLRU(){ return LRU; }

private:
	unsigned int pageNumber;	
	unsigned int PID;
	unsigned int LRU;
};