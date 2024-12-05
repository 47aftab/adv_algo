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

// Function to print the compressed trie
void printCompressedTrie(CompressedTrieNode* node, const string& prefix) {
    for (const auto& child : node->children) {
        cout << prefix + child.first << endl;
        printCompressedTrie(child.second, prefix + child.first);
    }
}

int main() {
    string text = "minimize";
    vector<string> suffixes;

    // Generate all suffixes
    for (int i = 0; i < text.length(); ++i) {
        suffixes.push_back(text.substr(i));
    }

    // Sort the suffixes in dictionary order
    sort(suffixes.begin(), suffixes.end());

    // Build the compressed trie
    CompressedTrieNode* root = new CompressedTrieNode();
    for (const string& suffix : suffixes) {
        insertCompressed(root, suffix);
    }

    // Print the compressed trie
    cout << "Compressed Trie for the word \"" << text << "\":" << endl;
    printCompressedTrie(root, "");

    // Cleanup (delete dynamically allocated nodes)
    // This is left as an exercise for memory management.

    return 0;
}
