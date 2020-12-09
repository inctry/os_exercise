#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
//segmentNumber 3, pageNumber 3, offset 2
int segTable[5] = {2, 10, 20, 30, 40};
int pageTable[5] = {55, 56, 57, 58, 59}; // every segtable has a pagetable which contain one page; 2^6
int phyaddress[1005];
int addr[1005];
	int n;
void init() {
	for(int i = 55; i <= 59; i++) phyaddress[i] = i;
	for(int i = 1; i <= 5; i++) {
		phyaddress[ segTable[i] ] = pageTable[i];
	}
}
void virtual_to_phycialaddress() {
	for(int i = 1; i <= n; i++) {
		int adr = addr[i];
		int seg = adr >> 5;
		int pageNumber = (adr >> 2) & 7;
		int offset = adr & 3;
		
		if(offset > 0 || seg > 4 || pageNumber > 4) {
			cout << "Out of index" << endl; continue;
		} else {
			cout << "virtual address: "<< adr <<endl;
			cout << "physical address: " <<  phyaddress[ phyaddress[ segTable[i] ] + offset] << endl;
		}
	}
}
int main() {
	init();
	
	cout << "Please Input the address you want" << endl;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> addr[i];
	
	
	virtual_to_phycialaddress();
	
    return 0;
}
