#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct pcb {
    string name;
    int super; // priority
    int atime; // arrive time
    int ntime;  // need to be running time
    int rtime;  // has been running time
    int srtime,ftime;
    double cirtime,valcirtime;
    struct pcb *next = NULL;
    pcb() {}
};

vector<pcb *> ready;
vector<pcb *> not_arrive;
vector<pcb *> finish;
int nowtime = 0;
int opt = 0;
bool cmp1(pcb *a, pcb *b) {
	return a->ntime < b->ntime;
}
bool cmp2(pcb *a, pcb *b) {
	if(a->atime == b->atime) return a->ntime < b->ntime;
	return a->atime < b->atime;
}
void input() {
    pcb *p = new pcb();
    cout << "Please Input the name of process" << endl;
    cin >> p->name;
    cout << "Please Input the arrival time of process" << endl;
    cin >> p->atime;
    cout << "Please Input the running time of process" << endl;
    cin >> p->ntime;

    p->rtime = 0;
    if(p->atime == 0) {
        ready.push_back(p);
    } else {
        not_arrive.push_back(p);
    }
}
void disp(pcb *p) {
    cout << p->name << endl;
}
void display(vector<pcb *> que) {
    for(auto it = que.begin(); it != que.end(); it++) {
        disp(*it);
    }
    return;
}
void check() {
    for(auto it = not_arrive.begin(); it != not_arrive.end();) {
        if((*it)->atime <= nowtime) {
            ready.push_back(*it);
            it = not_arrive.erase(it);
        } else {
            it++;
        }
    }
    if(ready.size() == 0) {
    	sort(not_arrive.begin(), not_arrive.end(), cmp2);
    	auto front = not_arrive.begin();
    	pcb *p = *front;
    	not_arrive.erase(front);
    	ready.push_back(p);
	}
}
void running() {
	if(opt == 1) sort(ready.begin(), ready.end(), cmp1);
    else sort(ready.begin(), ready.end(), cmp2);
    auto front = ready.begin();
    pcb *p = *front;
    ready.erase(front);
	nowtime = max(nowtime, p->atime);
	    cout << "Now the time is " << nowtime << endl;
    cout << "Now running process: " << endl;
    disp(p);
    cout << "The ready queue: " << endl; 
    display(ready);
    
    nowtime += p->ntime;
    p->srtime = nowtime - p->ntime; 
    p->ftime = nowtime;
    p->cirtime = nowtime-p->atime;
    p->valcirtime = p->cirtime / p->ntime;
    
    finish.push_back(p);
    
    cout << "The not arrive queue: " << endl;
    display(not_arrive); 
}
int main() {
    int len = 0;
    freopen("test.txt", "r", stdin);
    cout << "Please Input the number of Process you want to create" << endl; 
    cin >> len;
    cout << "Please choose FIFO or SJF, FIFO 0, SJF 1" << endl;
    cin >> opt;
    for(int i = 0; i < len; i++) {
        input();
    }
	
    while(finish.size() != len) {
        check();
        running();
    }
    auto totcir = 0.0, totvalcircle = 0.0;
	for(auto &x : finish) {
		cout << x->name << " " << x->atime << " " << x->ntime << " " << x->srtime << " " << x->ftime << " " << x->cirtime << " " <<x->valcirtime << endl;
		totcir += x->cirtime;
		totvalcircle += x -> valcirtime;
	}
	cout << totcir / finish.size() << "  " << totvalcircle  / finish.size() << endl;
    cout << "Running end" << endl;
    return 0;
}
