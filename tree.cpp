#include "tree.hpp"
#include <algorithm>

//reads in a file char by char and creates a list of nodes that contain the characters and frequencies
//of how often a character appears

void tree::readFile(string file)
{
    bool isFound = false;
    char ch;
    string input = "huff.txt";

    //opens connection to a file called huff.tct
    fstream fin(input, fstream::in);

    //reads file char by char, and does not skip whitespaces
    //white spaces are important for a huffman tree.
    while (fin >> noskipws >> ch)
    {
        origMessage += ch;
        //loop through each element of the vector
        for(int i = 0; i < test.size(); i++)
        {
            //check to see if the current character is already in the list
            //if yes, increase the frequency of that character, and break out.
            //if no, keep looping through the rest of the vector
            if(test[i]->data == ch)
            {
                test[i]->frequency +=1;
                isFound=true;
                break;
            }
        }

        //if the character wasn't found in the list, then we need to make a new node, fill it with data
        //and push the new node into the vector
        if(!isFound)
        {
            node *newNode;
            newNode = new node;
            newNode->data = ch;
            newNode->frequency = 1;


            test.push_back(newNode);

        }

        //reset the access granter
        isFound = false;
    }
    cout<<input <<" has been successfully read in."<<endl;



    genHuffTree(test);
}

 bool tree::cmd(const node *n1, const node *n2)
 {
     return n1->frequency < n2->frequency;


 }

void tree::genHuffTree(vector<node*> test)
{

    cout<<"Starting to generate the Huffman tree"<<endl;
    cout<<endl;

//tells the sort operator to use lambda function....whatever that is.
//third item is essentially a function that returns true/false to sort the list.
std::sort(test.begin(), test.end(), [](const node* pa, const node* pb)
    {
    return (*pa) < (*pb);
    });

    //prints out the frequencies
    //testing purposes only
    /*
    for(int i = 0; i < test.size(); i++)
        {
            cout<< test[i]->frequency<<endl;
        }
        cout<<"End of the stuff"<<endl;
    */

        //keep adding two nodes together until only one remains
        while (test.size() > 1)
        {


            node *newNode;
            newNode = new node;
            //* indicates an internal node
            newNode->data = '*';

            //combine the frequencies
            newNode->frequency = test[0]->frequency +  test[1]->frequency ;

            //the lesser of the two frequencies needs to go to the left node of the internal node
            if(test[0]->frequency < test[1]->frequency)
            {
                newNode->left = test[0];
                newNode->right = test[1];
            }
            else
            {
                newNode->left = test[1];
                newNode->right = test[0];
            }

            //add the new combined node.
            test.push_back(newNode);



            //erase the two individual nodes that made up the parent node.
            test.erase(test.begin(), test.begin()+2);


            //sort the list
            std::sort(test.begin(), test.end(), [](const node* pa, const node* pb)
            {
                return (*pa) < (*pb);
            });
        }

        cout<<"The Huffman Tree has been generated"<<endl;

        cout<<"We will now encode the following: " << origMessage<<endl;
        cout<<endl;
        encode(test[0]);
        cout<<endl;


        decode(test[0]);
}

//recursive function that traverses a proper huffman tree
//Special Instructions: All internal nodes must be denoted with a * in their data.
void tree::encode(node *head)
{

    //checks to see if the node we are at is NULL
    // A NULL node represents a dead end.
    if (head!= NULL)
    {

        //add 0 for left.
        str += "0";
        encode(head->left);

        //add 0 for right
        str+="1";
        encode(head->right);

        //if the current node is not an internal node, it means that it is a leaf node
        if (head->data != '*')
        {
            cout<<"The path to get " << head->data<<" is: "<< str<<endl;
            //strEncode += str;
            charTable.push_back(head->data);
            stringTable.push_back(str);


        }

        //quick fix to a off by one error
        //when unwinding the stack, pop_back is called one too many times.
        //this prevents the last time it is called.
        if(str.length() > 0)
        {
            str.pop_back();
        }

    }
    else // The head is NULL, so take away that 1 or 0 we just put on the string.
    {

        str.pop_back();
    }



}

//takes a well formed huffman tree and proper encoded message
void tree::decode(node *head)
{

    string tempMessage = origMessage;
    string code;

    //this block of code could be it's own method
    cout<<"Generating the encoded string"<<endl;
    while(tempMessage.length() > 0) //creates the binary code from our huffman tree.
    {
        for(int i = 0; i < charTable.size(); i++)//loops through list of characters to find a match.
        {
            if (tempMessage[0] == charTable[i])// When a letter is found, add it's binary to the code.
            {
                code += stringTable[i];
                tempMessage.erase(0,1);
                break;
            }
        }
    }

    cout<<"Encoding complete"<<endl;
    cout<<origMessage<< " has become "<< code <<endl;
    cout<<endl;
    cout<<"Starting to decode :" << code<<endl;


    //make a temporary head so we can traverse the tree without losing the head
    node *temp;
    temp = head;

    //Keep iterating until we reach the end of our encoded string.
      for ( int i = 0 ; i <= code.length(); i++)
      {
        //if the node data is * that means it is an internal node and we need to keep searching
        //if it's not *, that means we have reached a leaf node and need to record the data inside
          if (temp->data != '*')
          {
              //append the data to the final output
              strDecode += temp->data;

              //reset the temporary head back to the starting position
              temp = head;
              if(i == code.length())
                 {
                     break;
                 }
          }

            //if 0 go left, if 1 go right
             if(code[i] == '0')
             {
                 temp = temp->left;

             }
             else
             {
                 temp = temp->right;
             }


      }
    cout<<"Decoding complete"<<endl;
    cout<<code<< " has become "<< strDecode <<endl;

}



