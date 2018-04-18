#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <queue>
#include <memory>
#include <sstream>
using namespace std;

class ReadyQueue{

public:

	bool empty(){ return readyQueue.empty(); }

	void bubblesort(){
		bool swapped = true;
		for( int i = 0; i < readyQueue.size() && swapped; i++){
			swapped = false;
			for( int j = 0; j < readyQueue.size()-1; j++){
				// Sort ascending order
				if(readyQueue[j].getPriority() < readyQueue[j+1].getPriority()){
					PCB temp = readyQueue[j];
					readyQueue[j] = readyQueue[j+1];
					readyQueue[j+1] = temp;
					swapped = true;
				}
			}
		}
	}

	void append(PCB aPCB){ 
		readyQueue.push_back(aPCB); 
		// Don't need to sort one element
		if(!empty()){
			bubblesort();
		}
	}

	unsigned int getFrontPriority(){ return readyQueue[0].getPriority(); }
	PCB getFront(){ return readyQueue.front(); }
	void removeFront(){ readyQueue.erase(readyQueue.begin()); }


	void print(){
		cout << "\t\t[Ready Queue]\t\t\n";
		if(!readyQueue.empty())
			for(auto i : readyQueue){
				cout << "PID: " << i.getPID() << "  Priority: " << i.getPriority() << endl;
			}
	}
private:
	vector<PCB>readyQueue;
};