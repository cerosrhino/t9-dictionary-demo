#pragma once

#include "Digit.h"
#include "Deque.h"
#include <cctype>
#include <string>

class T9Tree {
private:
    struct Node {
        char data;
        bool isEndOfWord = false;
        Node* left = nullptr;
        Node* equal = nullptr;
        Node* right = nullptr;
        
        Node(char data) : data(data) {}
    };

    Node* root = nullptr;

    Node* insert(Node* node, const std::string& word, int pos)
    {
        if (node == nullptr) {
            node = new Node(word[pos]);
        }

        if (word[pos] < node->data) {
            node->left = insert(node->left, word, pos);
        } else if (word[pos] > node->data) {
            node->right = insert(node->right, word, pos);
        } else {
            if (pos + 1 < word.length()) {
                node->equal = insert(node->equal, word, pos + 1);
            } else {
                node->isEndOfWord = true;
            }
        }

        return node;
    }

    void getT9(Node* node,
               Deque<std::string>& results, std::string& word,
               const std::string& input, int pos)
    {
        if (node == nullptr) {
            return;
        }

        Digit& digit = digits[input[pos] - NUMERIC_ASCII_OFFSET];
        if (digit.contains(node->data)) {
            getT9(node->left, results, word, input, pos);
            getT9(node->right, results, word, input, pos);

            word.push_back(node->data);

            pos++;

            getT9(node->equal, results, word, input, pos);

            if (pos == input.length()) {
                if (node->isEndOfWord) {
                    results.push_front(word);
                } else {
                    results.push_back(word);
                }
            }

            if (word.length() > 0) {
                word.pop_back();
            }
        } else {
            if (digit.isLessThan(node->data)) {
                getT9(node->left, results, word, input, pos);
            } else if (digit.isGreaterThan(node->data)) {
                getT9(node->right, results, word, input, pos);
            }
        }
    }

public:
    static const char NUMERIC_ASCII_OFFSET;

    static Digit digits[10];

    void insert(std::string word)
    {
        Node* node = insert(root, word, 0);
        if (root == nullptr) {
            root = node;
        }
    }

    Deque<std::string> findWords(std::string input)
    {
        Deque<std::string> results;

        std::string word;
        getT9(root, results, word, input, 0);

        return results;
    }

    static int findDigit(char c)
    {
        for (int i = 2; i <= 9; i++) {
            if (digits[i].contains(c)) {
                return i;
            }
        }
        return -1;
    }
    
    static std::string digitize(std::string input)
    {
        for (std::string::iterator it = input.begin(); 
             it != input.end(); it++) {
            int digit = findDigit(std::tolower(*it));
            if (digit == -1) {
                throw std::invalid_argument("Illegal character");
            }
            *it = digit + NUMERIC_ASCII_OFFSET;
        }
        return input;
    }
};
