//rahat choudery
#include <iostream>
using namespace std;
#include <fstream>
#include <list>
#include <iterator>
#include <string.h>

class Node //represents Node in tree
{
public:
  string word;
  int count; //tracks # of times word occurs in the string of text
  Node *left, *right;
  
  Node (string file_word) 
  { 
    word = file_word;
    count = 1; 
    left = NULL; 
    right = NULL;
  }

  //getters and setters
  void setWord (string w)
  {
    word = w;
  }

  void setCount (int c)
  {
    count = c;
  }

  string getWord ()
  {
    return word;
  }

  int getCount ()
  {
    return count;
  }

  int getWordLength ()
  {
    return word.length();
  }
};

//preOrder
string longest;
int length;

void preOrder (Node *p)
{
  if (p != NULL)
    {
      preOrder (p->left);
      preOrder (p->right);

      if (p->getWordLength() > length)
	{
	  longest = p->getWord();
	  length = p->getWordLength();
	}
    }
}

//inOrder
string most_freq;
int most_count;

void inOrder (Node *p)
{
  if (p != NULL)
    {
      inOrder (p->left);
      inOrder (p->right);

      if (p->getCount() > most_count)
	{
	  most_freq = p->getWord();
	  most_count = p->getCount();
	} 
    }
}

//postOrder
string least_freq ="";
int least_count = 10000;

void leastFrequent (Node *p)
{
  if (p != NULL)
    {
      leastFrequent (p->left);
      leastFrequent (p->right);

      if (p->getCount() < least_count)
	{
	  least_freq = p->getWord();
	  least_count = p->getCount();
	}
    }
}

//build tree
void bInsert(string c, Node **t)
{
  if ((*t) == NULL)
    {
      *t = new Node (c);
    }
 
 else if ((*t)->word > c )     
    {
      bInsert(c, &((*t)->left)); // Insert in left subtree
    }

  else if ((*t)->word == c ) //increment count if it's already there
    {
      int total = (*t)->getCount();
      total = total + 1;
      (*t)->setCount (total);
    }

  else if ((*t)->word < c) 
    {
      bInsert(c, &((*t)->right));  // Insert in right subtree
    }
}

//main starts here
int main () 
{
  ifstream fin;
  string c;
  Node *T = NULL;

  fin.open("test_text.txt"); //open the file
  
  if (fin.fail())
    {
      cout << "Error!";
    } //return an error if the file does not open

  fin >> c;
  while (!fin.eof())
    {
      bInsert(c, &T);
      fin >> c;
    }
  
  //print longest word
  preOrder(T);
  cout << "LONGEST WORD" << endl;
  cout << "Longest word: " << longest << " | Length: " << length << endl;
  cout << endl;

  //print most frequently occuring word
  inOrder(T);
  cout << "MOST FREQUENT WORD" << endl; 
  cout << "Most frequent word: " << most_freq << " | Most Count: " << most_count << endl;
  cout << endl;

  //print least frequently occuring word
  leastFrequent(T);
  cout << "LEAST FREQUENT WORD" << endl;
  cout << "Least frequent word: " << least_freq << " | Least count: " << least_count << endl;
  cout << endl;
}
