#include <iostream>
// #include <queue>
#include <vector>
using namespace std;

class process {
public:
    size_t size;
    pid_t no;
};

class memory {
public:
    size_t size;
    pid_t no;
    vector<process> space_occupied;

    void push(const process p) {
        if (p.size <= size) {
            space_occupied.push_back(p);
            size -= p.size;
        }
    }

    process pop(const process p) {
        if (!space_occupied.empty()) {
            space_occupied.erase(find(space_occupied.begin(), space_occupied.end(), p));
            return p;
        }
    }

    bool empty() {
        return space_occupied.empty();
    }
};

// Implementing strategies
vector<memory> first_fit(vector<memory> memory_blocks, process p) {

}

vector<memory> best_fit(vector<memory> memory_blocks, process p) {
    
}

vector<memory> worst_fit(vector<memory> memory_blocks, process p) {
    
}
// Implementing functions
void request(vector<memory> memory_blocks, process p) {

}

void release(vector<memory> memory_blocks, process p) {

}

void compact(vector<memory> memory_blocks) {

}

void status(vector<memory> memory_blocks) {

}

int main(int argc, char *argv[]) {
    // argv should have size 3:
    // argv[0]: name of program
    // argv[1]: MAX memory blocks array size
    // argv[2]: total memory size of memory blocks
}