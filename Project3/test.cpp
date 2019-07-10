#include <iostream>
#include "Search_tree.h"
#include <vector>
#include <queue>

using namespace std;

vector<string> output;
queue<Search_tree<int>::Node *> outputMine;

// recursively print the tree. <Node>: a node in search_tree.
// 							   <mark>: the marker put in front of a node
//							   <indent>: indentation space
void printTree(Search_tree<int>::Node *node, std::string mark, int indent, unsigned digitWidth) {
    // Recursion end point
    if (node == nullptr)
        return;

    // Set indent
    indent += digitWidth + 1;

    printTree(node->right_tree, "/", indent, digitWidth);

    std::string thisLine;
    // Print current node after space
    // count
    thisLine = (thisLine + std::string(indent, ' ').erase(0, digitWidth + 2));
    unsigned long long spaceAfter = digitWidth - to_string(node->node_value).length() - 1;
    string charAfter(spaceAfter, '-');
    thisLine =
            thisLine + mark + to_string(node->node_value) + ((node->is_leaf()) ? "" : charAfter + "-|") + "\n";
    output.push_back(thisLine);

    printTree(node->left_tree, "\\", indent, digitWidth);
}

// Connect the branches to make the output much easier to read. Not necessary but highly recommended.
void addTicks() {
    for (int i = 0; i < output.size(); ++i) {
        for (int j = 0; j < output[i].length(); ++j) {
            // travesal the output, if a '/' is found:
            if (output[i][j] == '/') {
                // check the number of '|' between '/' and '\'
                int k = i + 1;
                int tickCount = 0;
                bool paired = false;
                // search from the next line until the end of string vector, or until next line is shorter than this
                while ((k < output.size()) && (j < output[k].length())) {
                    if (output[k][j] == '|') {
                        ++tickCount;
                    }
                    // mark it as paired if a '\' is found
                    if (output[k][j] == '\\') {
                        paired = true;
                        break;
                    }
                    ++k;
                }
                k = i + 1;
                // if paired and there is only 1 '|' between the '/' and '\', fill the inside space with '|'
                if ((tickCount == 1)) {
                    if (paired) {
                        while (output[k][j] != '\\') {
                            output[k][j] = '|';
                            ++k;
                        }
                    }
                }
                /*
                   This function does not connect the dangling / or \:
                          / right_child
                            <== This will not be connected, if / and \ are not paired
                  parent -|
                   Because open pairing (having only / or \ and more than one line from |)  should not happen.
                   As this is an AVL tree, if the parent has only one child, the child must has no subtree
                   or the AVL balance is broken.
                   It can only be:
                          /right_child
                  parent -|                or    parent -|
                                                         \left_child
                */
            }
        }
    }
}

void printTreeMine(Search_tree<int>::Node *n) {

    outputMine.push(n);
    Search_tree<int>::Node *node;
    while (!outputMine.empty()) {
        node = outputMine.front();
        outputMine.pop();
        std::cout << to_string(node->node_value) << " ";
        if (node->left_tree != nullptr)
            outputMine.push(node->left_tree);
        if (node->right_tree != nullptr)
            outputMine.push(node->right_tree);
    }

}


int main() {
    Search_tree<int> tree;
    tree.insert(7);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    tree.insert(21);
    tree.insert(8);
    tree.insert(34);


//    for (int i = 1; i <= 30; ++i) {
//        std::cout << "      " << (83 * i) % 30 << ", ";
////        std::cout << tree.insert( (83*i) % 30 );
//        tree.insert((83 * i) % 30);
//    }

//	std::cout << std::endl;

//    for (int i = 1; i <= 30; ++i) {
////        std::cout <<  "        "<<  (97*i) % 30 <<", ";
////		std::cout << tree.insert( (97*i) % 30 );
//        tree.insert((97 * i) % 30);
//    }

    std::cout << std::endl;

    printTreeMine(tree.root_node);
//    addTicks();
//    // print the output to console
//    for (const string &i : output) {
//        cout << i;
//    }

    std::cout << "Front:   " << tree.front() << std::endl;
    std::cout << "Back:    " << tree.back() << std::endl;
    std::cout << "Height:  " << tree.height() << std::endl;

    std::cout << "--> ";

    for (Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr) {
        std::cout << *itr << " ";
    }

    std::cout << std::endl;


    tree.erase(1);
    output.clear();
    std::cout << std::endl;

    printTreeMine(tree.root_node);

//    addTicks();
    // print the output to console
//    for (const string &i : output) {
//        cout << i;
//    }

    std::cout << "Front:   " << tree.front() << std::endl;
    std::cout << "Back:    " << tree.back() << std::endl;
    std::cout << "Height:  " << tree.height() << std::endl;

    std::cout << "--> ";

    for (Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr) {
        std::cout << *itr << " ";
    }

    std::cout << std::endl;

    return 0;
}
