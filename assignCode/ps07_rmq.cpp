#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

vector<long long> segmentTree;
vector<long long> A;

void initSegmentTree(int n) {
    long long treeSize = 1;
    while (treeSize < n) {
        treeSize *= 2;
    }
    segmentTree.assign(2 * treeSize, LLONG_MAX);
}

void buildSegmentTree(int node, int start, int end) {
    if (start == end) {
        segmentTree[node] = start;
    }
    else {
        int mid = (start + end) / 2;
        buildSegmentTree(2 * node, start, mid);
        buildSegmentTree(2 * node + 1, mid + 1, end);
        segmentTree[node] = (A[segmentTree[2 * node]] <= A[segmentTree[2 * node + 1]]) ? segmentTree[2 * node] : segmentTree[2 * node + 1];
    }
}

long long querySegmentTree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) {
        return -1;
    }
    if (left <= start && end <= right) {
        return segmentTree[node];
    }

    int mid = (start + end) / 2;
    long long leftIdx = querySegmentTree(2 * node, start, mid, left, right);
    long long rightIdx = querySegmentTree(2 * node + 1, mid + 1, end, left, right);

    if (leftIdx == -1) return rightIdx;
    if (rightIdx == -1) return leftIdx;
    return (A[leftIdx] <= A[rightIdx]) ? leftIdx : rightIdx;
}

void updateSegmentTree(int node, int start, int end, int index, int newValue) {
    if (start == end) {
        A[index] = newValue;
        segmentTree[node] = index;
    }
    else {
        int mid = (start + end) / 2;
        if (start <= index && index <= mid) {
            updateSegmentTree(2 * node, start, mid, index, newValue);
        }
        else {
            updateSegmentTree(2 * node + 1, mid + 1, end, index, newValue);
        }
        segmentTree[node] = (A[segmentTree[2 * node]] <= A[segmentTree[2 * node + 1]]) ? segmentTree[2 * node] : segmentTree[2 * node + 1];
    }
}

int main() {
    ifstream ifp("rmq.inp");
    ofstream ofp("rmq.out");

    long long N, n, a, b, sum = 0;
    char cmd;

    ifp >> N;

    for (long long i = 0; i < N; i++) {
        ifp >> n;
        A.emplace_back(n);
    }

    initSegmentTree(N);
    buildSegmentTree(1, 0, N - 1);

    while (true) {
        ifp >> cmd;

        if (cmd == 's') break;

        ifp >> a >> b;

        if (cmd == 'q') {
            sum += querySegmentTree(1, 0, N - 1, a, b);
        }
        else if (cmd == 'c') {
            A[a] = b;
            updateSegmentTree(1, 0, N - 1, a, b);
        }
    }

    ofp << sum % 100000 << endl;

    ifp.close();
    ofp.close();
}
