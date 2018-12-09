#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Node {
    public:
        Node *prev;
        Node *next;
        int value;
};

uint64_t run(const string& s) {
    int players, points;
    stringstream ss(s);
    ss >> players;
    ss.ignore(30);
    ss >> points;

    Node *current = new Node();
    current->value = 0;
    current->next = current;
    current->prev = current;
    vector<uint64_t> scores(players);
    for(int i = 1; i <= points; i++){
        Node *new_node = new Node();
        new_node->value = i;
        if(i % 23 != 0){
            current = current->next;
            Node *next_node = current->next;
            current->next = new_node;
            new_node->prev = current;
            new_node->next = next_node;
            next_node->prev = new_node;
            current = new_node;
        }
        else {
            current = current->prev->prev->prev->prev->prev->prev->prev;
            scores.at(i % players) += i + current->value;
            current->prev->next = current->next;
            current = current->next;
        }
    }
    uint64_t max = 0;
    for(int i = 0; i < scores.size(); i++){
        if(scores.at(i) > max){
            max = scores.at(i);
        }
    }
    return max;

}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    clock_t start = clock();
    auto answer = run(string(argv[1]));
    
    cout << "_duration:" << float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC << "\n";
    cout << answer << "\n";
    return 0;
}
