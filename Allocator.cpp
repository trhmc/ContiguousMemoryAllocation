#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class process {
public:
    size_t size;
    string pid;
};

vector<process> pop(vector<process> processes, process p) {
    vector<process> result;
    for (int i = 0; i < processes.size(); i++) {
        if (p.pid != processes.at(i).pid) {
            result.push_back(processes.at(i));
        }
    }
    return result;
}

class memory {
public:
    size_t size;
    pid_t mid;
    vector<process> space_occupied;

    void push(const process p) {
        if (p.size <= size) {
            space_occupied.push_back(p);
            size -= p.size;
        }
    }

    void pop(const process p) {
        vector<process> temp;
        int i;
        if (!space_occupied.empty()) {
            for (i = 0; i < space_occupied.size(); i++) {
                if (space_occupied.at(i).pid != p.pid) {
                    temp.push_back(space_occupied.at(i));
                }
            }
            if (!temp.empty()) {
                size += p.size;
            }
            space_occupied = temp;
            // return p;
        }
    }

    bool empty() {
        return space_occupied.empty();
    }
};

// Implementing strategies
vector<memory> first_fit(vector<memory> memory_blocks, process p) {
    // Finding the first memory block that fits the process
    int i;
    for (i = 0; i < memory_blocks.size(); i++) {
        if (memory_blocks.at(i).size >= p.size) {
            memory_blocks.at(i).push(p);
            break;
        }
    }
    return memory_blocks;
}

vector<memory> best_fit(vector<memory> memory_blocks, process p) {
    // Finding the memory block with least size different from the process
    int i, index;
    int min = 0;
    for (i = 0; i < memory_blocks.size(); i++) {
        if (memory_blocks.at(i).size >= p.size && (min == 0 || memory_blocks.at(i).size < min)) {
            min = memory_blocks.at(i).size;
            index = i;
        }
    }
    if (min != 0) {
        memory_blocks.at(index).push(p);
    }
    else {
        cout << "Cannot fit process into memory";
    }
    return memory_blocks;
}

vector<memory> worst_fit(vector<memory> memory_blocks, process p) {
    // Finding largest memory block to fit the process
    int i, index;
    int max = 0;
    for (i = 0; i < memory_blocks.size(); i++) {
        if (memory_blocks.at(i).size >= p.size && memory_blocks.at(i).size > max) {
            max = memory_blocks.at(i).size;
            index = i;
        }
    }
    if (max != 0) {
        memory_blocks.at(index).push(p);
    }
    else {
        cout << "Cannot fit process into memory";
    }
    return memory_blocks;
}
// Implementing functions
vector<memory> request(vector<memory> memory_blocks, process p, char option) {
    // allocate memory according to option strategy
    switch(option) {
        case 'B':
            cout << "Implementing Best fit strategy" << endl;
            memory_blocks = best_fit(memory_blocks, p);
            break;
        case 'W':
            cout << "Implementing Worst fit strategy" << endl;
            memory_blocks = worst_fit(memory_blocks, p);
            break;
        case 'F':
            cout << "Implementing First fit strategy" << endl;
            memory_blocks = first_fit(memory_blocks, p);
            break;
        default:
            cout << "Invalid option" << endl;
    }
    return memory_blocks;
}

vector<memory> release(vector<memory> memory_blocks, process p) {
    // release process
    int i;
    // process d;
    for (i = 0; i < memory_blocks.size(); i++) {
        memory_blocks.at(i).pop(p);
    }
    cout << "Process " << p.pid << " is released from memory" << endl;
    return memory_blocks;
}

vector<memory> compact(vector<memory> memory_blocks) {
    // compacting free memory blocks into one big chunk
    memory chunk_block;
    chunk_block.size = 0;
    vector<memory> result;
    for (int i = 0; i < memory_blocks.size(); i++) {
        // do something if it is not empty and size is != 0
        if ((!memory_blocks.at(i).empty()) && (memory_blocks.at(i).size != 0)) {
            chunk_block.size += memory_blocks.at(i).size;
            memory_blocks.at(i).size = 0;
            result.push_back(memory_blocks.at(i));
        }
    }
    for (int i = 0; i < memory_blocks.size(); i++) {
        // do something if the memory block is empty
        if (memory_blocks.at(i).empty()) {
            chunk_block.size += memory_blocks.at(i).size;
        }
    }
    // adding the 'chunk to the new memory block
    chunk_block.mid = result.size() - 1;
    result.push_back(chunk_block);
    return result;
}

void status(vector<memory> memory_blocks, vector<process> processes) {
    // status report of memory blocks
    int i, j;
    int temp;
    cout << "+-------------+--------------+--------------+"
            << endl;
    cout << "| Process no. | Process size | Memory block |"
            << endl;
    cout << "+-------------+--------------+--------------+"
            << endl;
    for (i = 0; i < processes.size(); i++) {
        process p = processes.at(i);
        string p_mem;
        bool p_in_mem = false;
        // find the process in the memory blocks
        for (j = 0; j < memory_blocks.size(); j++) {
            vector<process> block = memory_blocks.at(j).space_occupied;
            for (int k = 0; k < block.size(); k++) {
                if (block.at(k).pid == p.pid) {
                    p_mem = to_string(memory_blocks.at(j).mid);
                    p_in_mem = true;
                }

            }
        }
        temp = p.pid.length();
        cout << "|" << string(7 - temp / 2 - temp % 2, ' ')
             << p.pid << string(6 - temp / 2, ' ');

        temp = to_string(p.size).length();
        cout << "|" << string(7 - temp / 2 - temp % 2, ' ')
             << p.size << string(7 - temp / 2, ' ');
        if (!p_in_mem) {
            p_mem = "N/A";
        }
        temp = p_mem.length();
        cout << "|" << string(7 - temp / 2 - temp % 2, ' ')
             << p_mem << string(7 - temp / 2, ' ') << "|" << endl;

    }
    cout << "+-------------+--------------+--------------+"
            << endl;
}

vector<string> split(string s, string delimiter) {
    size_t start = 0, end, delim_len = delimiter.length();
    string token;
    vector<string> result;

    while ((end = s.find(delimiter, start)) != string::npos) {
        token = s.substr(start, end - start);
        start = end + delim_len;
        result.push_back(token);
    }
    result.push_back(s.substr(start));
    return result;
}

int main(int argc, char *argv[]) {
    // argv should have size 2:
    // argv[0]: name of program
    // argv[1]: MAX memory blocks array size
    // argv[2]: total memory size of memory blocks
    int i;
    if (argc != 2) {
        cout << "Argument Invalid" << endl;
        return 0;
    }
    int max = atoi(argv[1]);
    vector<memory> memory_blocks(max);
    vector<process> processes;
    
    for (i =  0; i < max; i++) {
        int mem_size;
        cout << "Memory size of block " << i << " :";
        cin >> mem_size;
        memory_blocks[i].mid = i;
        memory_blocks[i].size = mem_size;
    }
    string input;
    while (getline(cin, input)) {
        vector<string> inputs;
        inputs = split(input, " ");
        if (inputs[0] == "RQ") {
            process p;
            p.pid = inputs[1];
            p.size = stoi(inputs[2]);
            char opt = inputs[3][0];
            memory_blocks = request(memory_blocks, p, opt);
            processes.push_back(p);
            // cout << processes.size();
            // cout << "This is a request" << endl;
        }
        else if (inputs[0] == "RL") {
            process p;
            bool p_exist = false;
            string temp_pid = inputs[1];
            for (int i = 0; i < processes.size(); i++) {
                if (temp_pid == processes.at(i).pid) {
                    p = processes.at(i);
                    p_exist = true;
                }
            }
            if (p_exist) {
                memory_blocks = release(memory_blocks, p);
                processes = pop(processes, p);
            }
            // cout << "This is a release" << endl;
        }
        else if (inputs[0] == "C") {
            memory_blocks = compact(memory_blocks);
            // cout << "This is a compaction" << endl;
        }
        else if (inputs[0] == "STAT") {
            status(memory_blocks, processes);
            // cout << "This is a status report" << endl;
        }
        else if (inputs[0] == "Exit") {
            cout << "Exiting program..." << endl;
            break;
        }
        cout << ">";
    }
    return 0;


}