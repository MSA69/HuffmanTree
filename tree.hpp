#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED
#include <iostream>
#include <vector>


using namespace std;
class tree
{

private:


     struct node
    {
        struct node *left = NULL;
        struct node *right = NULL;
        int frequency ;
        char data;

        bool operator < (const node& str) const
        {
            return (frequency < str.frequency);
        }

    };



    node *head;

public:
    string str;
    string strDecode;
    string strEncode;
    string origMessage;
    vector<node*> test;
    vector<char> charTable;
    vector<string> stringTable;


    tree()
    {
        head = NULL;
    }


    void readFile(string file);
    void genHuffTree(vector<node*> test);
    bool cmd(const node *n1, const node *s2);
    void encode(node *root);
    void decode(node *root);





};

#endif // TREE_HPP_INCLUDED
