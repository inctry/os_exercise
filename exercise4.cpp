#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 1e3;
const int M = 1e3;
int availble[M] = {3, 3, 2};
int Max[N][M] = { {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
int allocation[N][M] = { {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2} };
int need[N][M];
int vis[N];
int work[M];
int request[M];
int n,m,r;
vector<int> v;
void init() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            need[i][j] = Max[i][j] - allocation[i][j];
    }
}
void reset() {
        for(int i = 0; i < m; i++) {
            work[i] = availble[i]; 
            // cout << work[i] << " ";
        }
        // cout << endl;
}
bool judge(int index) {
    for(int j = 0; j < m; j++) {
        if(need[index][j] <= work[j]) continue;
        else return false;
    }
    return true;
}
void add(int index, int opt) {
    for(int j = 0; j < m; j++) {
        work[j] += allocation[index][j] * opt;
    }
}
bool isSafe(int now) {
    bool state = false;
    if(now == n) {
        state = true;
        for(auto &x : v) {
            cout << x << " ";
        }
        cout << endl; 
        return state;
    }
    for(int i = 0; i < n; i++) {
        if(!vis[i] && judge(i)) {
            vis[i] = 1;
            add(i, 1);
            v.push_back(i);
            state = isSafe(now + 1);
            v.pop_back();
            vis[i] = 0;
            add(i, -1);
            if(state == true) return true;
        }
    }
    return state;
}
void trytodeliver(int index, int opt) {
    for(int j = 0; j < m; j++) {
        availble[j] = availble[j] - request[j] * opt;
        allocation[index][j] = allocation[index][j] + request[j] * opt;
        need[index][j] = need[index][j] - request[j] * opt;
    }
}

int main() {
    // cout << "Please Input the"
	n = 5, m = 3;
    init();
    // input();
    cout << "Please Input the Number of Requests" << endl;
    cin >> r;
    bool error = false;
    for(int i = 1; i <= r; i++) {
        cout << "Please Input the ID of process" << endl;
        int id;
        error = false;
        cin >> id;
        cout << "Please Input the Request vector of that process" << endl;
        for(int j = 0; j < m; j++) {
            cin >> request[j];
        }
        for(int j = 0; j < m; j++) {
            if(request[j] <= need[id][j] && request[j] <= availble[j]) continue;
            else {
                error = true; break;
            }
        }
        if(error) {
            cout << "Error please retry" << endl; continue;
        }
        trytodeliver(id, 1);
        reset();
        bool state = isSafe(0);
        cout << state << endl;
        if(!state) trytodeliver(id, -1);
    }

    return 0;
}
