#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Node {
    public:
        Node *prev;
        Node *next;
        unsigned int value;
        Node(unsigned int new_value) 
        {
            this->value = new_value;
            this->prev = this;
            this->next = this;
        }
        Node(unsigned int new_value, Node* previous_node, Node* next_node) 
        {
            this->value = new_value;
            this->prev = previous_node;
            this->next = next_node;
        }
        Node* insert(unsigned int value){
            Node *new_node = new Node(value, this, this->next);
            this->next->prev = new_node;
            this->next = new_node;
            return new_node;
        }
        Node* remove() {
            this->prev->next = this->next;
            this->next->prev = this->prev;
            return this->next;
        }
};

uint64_t run(const string& s) {
    uint players, points;
    stringstream ss(s);
    ss >> players;
    ss.ignore(30);
    ss >> points;
    points = (points << 6) + (points << 5) + (points << 2);

    vector<unsigned int> scores(players);

    Node *current = new Node(0);
    unsigned int player = 0;
    unsigned int max = 0;

    for(unsigned int i = 1; i <= points; i++){
        if(i % 23 != 0){
            current = current->next->insert(i);
        }
        else {
            Node* culprit = current->prev->prev->prev->prev->prev->prev->prev;
            if((scores[player] += i + culprit->value) > max){
                max = scores[player];
            }
            current = culprit->remove();
        }
        if(player >= players - 1){
            player = 0;
        }
        else {
            player++;
        }
    }
    return max;

}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    string input = string(argv[1]);
    clock_t start = clock();
    auto answer = run(input);
    float time = float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC;
    cout << "_duration:" << time << "\n";
    cout << answer << "\n";
    return 0;
}