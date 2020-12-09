#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct block {
    int state;
    int size;
    int start;
    int jobid;
    struct block *pre = NULL;
    struct block *next = NULL;
};
struct job {
    int jobid;
    int size;
};
int size = 0;
int opt;
block *list = new block();
void change(block *i, block *j) {
	swap(i->state, j->state);
	swap(i->size, j->size);
	swap(i->start, j->start);
	swap(i->jobid, j->jobid);
	
}
void sort_firstFit() {

	for(block *i = list; i != NULL; i = i->next) {
		block *j = i->next;
		for(; j != NULL; j = j->next) {
			if(i->start > j->start) {
				change(i, j);
			}
		}
	}
}
void sort_bestfit() {
	for(block *i = list; i != NULL; i = i->next) {
		block *j = i->next;
		for(; j != NULL; j = j->next) {
			if(i->size > j->size) {
				change(i, j);
			}
		}
	}
}
bool deliver(job *b) {
    block *now = list;
    if(opt == 1) sort_bestfit();
    while(now != NULL) {
        if(now->size >= b->size && now->state == 0) {
            block *p = new block();
            p->state = 1;
            p->start = now->start;
            p->size = b->size;
            p->jobid = b->jobid;
            if(now->size - b->size > 0) {
                now->size = now->size - b->size;
                now->start = p->start + p->size;
                p->next = now;
                p->pre = now->pre;
                now->pre = p;
                if(p->pre != NULL) p->pre->next = p;
                else list = p;
            } else {
                p->next = now->next;
                p->pre = now->pre;
                if(p->pre != NULL)  p->pre->next = p;
                else list = p;
                delete now;
            }
            return true;
        }
        now = now->next;
    }
    return false;
}
void merge(block *p) {

	while(p != NULL && p->next != NULL) {
		
		if(p->start + p->size == p->next->start && p->state == 0 && p->next->state == 0) {
			p->size = p->size + p->next->size;
			block *temp = p->next;
			p->next = p->next->next;
			if(p->next != NULL) p->next->pre = p;
			
			delete temp;
//break;
		} else break;
	}
}
bool del(job *p) {
    block *now = list;
    if(opt == 1) sort_firstFit();
    while(now != NULL) {
        if(now->jobid == p->jobid && now->state == 1) {
            now->state = 0;
            merge(now);
            merge(now->pre);
            // delete now;
            return true;
        }
        now = now->next;
    }
    return false;
}
job *input() {
    int opt;
    job *b = new job();
    cout << "Please choose the malloc or delete if choose malloc input 0, else Input 1" << endl;
    cin >> opt;
    cout << "Please Input the job ID" << endl;
    cin >> b->jobid;
    cout << "Please Input the job size " << endl;
    cin >> b->size;
    if(opt == 0) {
    	if(deliver(b)) {
    		cout << "malloc successfully" << endl;
		}
		else cout << "malloc failed" << endl;
    }
    else {
    	if(del(b)) {
    		cout << "free successfully" << endl;
		} else
		cout << "free failed" << endl;
	}
}
void display() {
    if(opt == 1) sort_bestfit();
    block *p = list;
    while(p != NULL) {
        cout << p->start << "   " << p->size << "   " << p->state;
        if(p->state == 1) cout << "   " << p->jobid;
        cout << endl;
        p = p->next;
    }
}

int main() {
	cout << "Please Input the size you want have" << endl;
    cin >> size;
    cout << "Please choose the firstfit or bestfit, firstfit  0, else 1" << endl;
    cin >> opt;
    list->state = 0;
    list->start = 0;
    list->size = size;
    int n;
    cout << "Please Input then commands you have" << endl;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        input();
        display();
    }

    cout << "Running end" << endl;
    return 0;
}
