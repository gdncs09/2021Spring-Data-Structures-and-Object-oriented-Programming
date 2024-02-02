#include <iostream>
#include <bits/stdc++.h>
#include <string.h>

using namespace std;

map <char, int> wt; //character - weight
map <char, string> codelist; //character-code

void Input(string *str)
{
          cout << "Enter character: ";
          cin >> *str;
}

void CalcWT(string str)
{
          for (auto c: str)
          {
                    wt[c]++;
          }
}

struct Node
{
          char ch; //character
          int value; //weight
          struct Node *left, *right; //child
          Node (char ch, int value)
          {
                    left = right = NULL;
                    this->ch = ch;
                    this->value = value;
          }
};

struct compare
{
          bool operator()(Node *l, Node *r)
          {
                    return (l->value > r->value);
          }
};

void CodeList(struct Node *root, string encoding, int *w)
{
          if (!root)
                    return;
          if (root->ch != '*')
          {
                    codelist[root->ch] = encoding;
                    *w += root->value*encoding.length();
          }

          CodeList(root->left, encoding+"0", &*w);
          CodeList(root->right, encoding+"1", &*w);
}

 priority_queue <Node*, vector<Node*>, compare> pq; //minHeap

void HuffmanCodes(int *w)
{
          struct Node *left, *right, *top;

          for (map<char, int>::iterator i = wt.begin(); i != wt.end(); i++) //map
          {
                    pq.push(new Node(i->first, i->second));
                    cout << i->first << " " << i->second << endl;
          }
          while (pq.size()!=1)
          {
                    left = pq.top();
                    pq.pop();
                    right = pq.top();
                    pq.pop();

                    top = new Node('*', left->value + right->value);
                    top->left = left;
                    top->right = right;
                    pq.push(top);
          }
          CodeList(pq.top(), "", &*w);
}

string Encode(string str)
{
          string res="";
          for (auto c: str)
          {
                    res += codelist[c];
          }
          return(res);
}

string Decode(struct Node *root, string enstr)
{
          string res = "";
          struct Node *now = root;
          for (auto c: enstr)
          {
                    if (c == '0')
                    {
                              now = now->left;
                    }
                    else if (c=='1')
                    {
                              now = now->right;
                    }
                    if (now->left == NULL && now->right == NULL)
                    {
                              res+=now->ch;
                              now = root;
                    }
          }
          return res;
}

int main()
{
          //INPUT
          string str;
          Input(&str);

          CalcWT(str);

          int  WPL = 0;
          HuffmanCodes(&WPL);

          //ENCODE
          string enstr = Encode(str);
          cout << "encoding result: " << enstr << endl;

          //CODE LIST
          cout << "code list{" << endl;
          for (auto i = codelist.begin(); i != codelist.end(); i++) //maps
          {
                    cout << '\t' << i->first << ": " << i->second << endl;
          }
          cout << "}" << endl;

          //WPL
          cout << "WPL = " << WPL << endl;

          //DECODE
          string destr = Decode(pq.top(), enstr);
          cout << "decoding result: " << destr << endl;
          return 0;
}
