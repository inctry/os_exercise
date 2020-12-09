#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct pcb {
    string name;
    char state;
    int super; // priority
    int atime; // arrive time
    int ntime;  // need to be running time
    int rtime;  // has been running time
    struct pcb *next = NULL;
    pcb() {}
};

vector<pcb *> ready;
vector<pcb *> not_arrive;
vector<pcb *> finish;
int nowtime = 1;
void input() {
    pcb *p = new pcb();
    cout << "Please Input the name of process" << endl;
    cin >> p->name;
    cout << "Please Input the priority number of process" << endl;
    cin >> p->super;
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
    cout << p->name << " " << p->state << " " << p->super << " " << p->atime
    << " " << p->ntime << " " << p->rtime << endl;
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
}
void running() {
    cout << "Now the time is " << nowtime << endl;
    auto front = ready.begin();
    pcb *p = *front;
    ready.erase(front);
    (p)->rtime++;
    if((p)->rtime != (p)->ntime) ready.push_back(p); 
    finish.push_back(p);
    cout << "Now running process: " << endl;
    disp(p);
    cout << "The ready queue: " << endl; 
    display(ready);
    cout << "The not arrive queue: " << endl;
    display(not_arrive);
}
int main() {
    int len = 0;
    cout << "Please Input the number of Process you want to create" << endl; 
    cin >> len;

    for(int i = 0; i < len; i++) {
        input();
    }

    while(finish.size() != len) {
        check();
        running();
        nowtime++;
    }

    cout << "Running end" << endl;
    return 0;
}
