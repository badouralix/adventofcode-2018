#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>

#define ALPHABET_SIZE 26

using namespace std;

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;

    // index of line in original list
    int index;
};
typedef struct TrieNode TrieNode;

// Returns new trie node (initialized to NULLs)
TrieNode *getNode()
{
    TrieNode *pNode = new TrieNode;

    pNode->isEndOfWord = false;
    pNode->index = -1;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(TrieNode *root, string key, int index)
{
    TrieNode *pCrawl = root;

    for (int i = 0; i < key.size(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
    pCrawl->index = index;
}

// Returns index value if key presents in trie,
// does a fuzzy lookup allowing up to one character mismatch
int search(TrieNode *root, string key)
{
    TrieNode *pCrawl = root;
    for (int i = 0; i < key.size(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return -1;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord) ? pCrawl->index : -1;
}

string copyExcept(string s, int index)
{
    string r;

    for (int i = 0; i < s.size(); i++)
    {
        if (i == index)
            continue;
        r.push_back(s[i]);
    }

    return r;
}

string run(string s)
{
    istringstream stream(s);
    string stripped, line;
    int k = -1;
    TrieNode *trie[ALPHABET_SIZE];

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        trie[i] = getNode();
    }

    while (getline(stream, line))
    {
        k++;
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            stripped = copyExcept(line, i);
            int j = search(trie[i], stripped);
            if (j > -1)
                return stripped;
            insert(trie[i], stripped, k);
        }
    }

    return "";
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Missing one argument" << endl;
        exit(1);
    }
    cout << run(string(argv[1])) << "\n";
    return 0;
}
