#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <queue>
#include <memory>
#include <sstream>
using namespace std;

class DiskQueue{

public:
	void resize(const int &size){ diskQueue.resize(size); }
	unsigned int size() { return diskQueue.size(); }
	void append(const int &number, PCB aPCB){ diskQueue[number].push_back(aPCB); }
	bool emptyIndex(const int &index){ return diskQueue[index].empty(); }

	void print(){
		/*int index = 0;
		if(!diskQueue[index].empty()){
			for(auto i : diskQueue){
				if( !i.empty()){
					cout << "\t\t[I/O Queue " << index++ << "]" << endl;
					for(auto j: i){
						cout << "PID: " << j.getPID() << " File name: " << j.getFileName() << endl;
					}
				}
			}
		}*/
		for(int i  = 0; i < diskQueue.size(); i++){
			if(!diskQueue[i].empty()){
				cout << "\t\t[I/O Queue " << i << "]" << endl;
				for(int j  = 0; j <diskQueue[i].size(); j++){
					cout << "PID: " << diskQueue[i][j].getPID() << " File name: " << diskQueue[i][j].getFileName() << endl;
				}
			}
		}
	}

	unsigned int getFrontPriority(unsigned int diskNumber){ return diskQueue.at(diskNumber)[0].getPriority(); }
	PCB getFront(unsigned int diskNumber){ return diskQueue[diskNumber].front(); }
	void removeFront(unsigned int diskNumber){ diskQueue[diskNumber].erase(diskQueue[diskNumber].begin()); }

private:
	vector<vector<PCB> >diskQueue;

};