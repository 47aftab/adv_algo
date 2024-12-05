#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Suffix Tree Node structure for compressed trie
struct CompressedTrieNode {
    unordered_map<string, CompressedTrieNode*> children;
};

// Function to insert a suffix into the compressed trie
void insertCompressed(CompressedTrieNode* root, const string& suffix) {
    CompressedTrieNode* currentNode = root;
    string remaining = suffix;

    while (!remaining.empty()) {
        bool found = false;

        for (auto& child : currentNode->children) {
            string edge = child.first;
            int commonLength = 0;

            // Find the longest common prefix between edge and remaining
            while (commonLength < edge.size() && commonLength < remaining.size() &&
                   edge[commonLength] == remaining[commonLength]) {
                commonLength++;
            }

            if (commonLength > 0) {
                // Split the edge if the common prefix is less than the edge length
                if (commonLength < edge.size()) {
                    CompressedTrieNode* newNode = new CompressedTrieNode();
                    string newEdge = edge.substr(commonLength);

                    newNode->children[newEdge] = child.second;
                    currentNode->children[edge.substr(0, commonLength)] = newNode;

                    currentNode->children.erase(edge);
                    child.second = newNode;
                }

                currentNode = child.second;
                remaining = remaining.substr(commonLength);
                found = true;
                break;
            }
        }

        if (!found) {
            // Add the remaining suffix as a new child
            currentNode->children[remaining] = new CompressedTrieNode();
            break;
        }
    }
}

// Function to print the compressed trie (for debugging or visualization)
void printCompressedTrie(CompressedTrieNode* root, const string& prefix = "") {
    for (const auto& child : root->children) {
        cout << prefix << "->" << child.first << endl;
        printCompressedTrie(child.second, prefix + child.first);
    }
}

// Main function
int main() {
    CompressedTrieNode* root = new CompressedTrieNode();

    int n;
    cout << "Enter the number of suffixes to insert: ";
    cin >> n;

    cout << "Enter the suffixes:\n";
    for (int i = 0; i < n; ++i) {
        string suffix;
        cin >> suffix;
        insertCompressed(root, suffix);
    }

    cout << "\nCompressed Trie Structure:\n";
    printCompressedTrie(root);

    // Cleanup (delete dynamically allocated nodes)
    // A proper cleanup would involve recursively deleting all nodes.
    // This is left as an exercise for further memory management improvements.

    return 0;
}
