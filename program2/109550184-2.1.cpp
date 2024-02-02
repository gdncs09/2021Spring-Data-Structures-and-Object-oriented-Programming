#include <iostream>
#include <bits/stdc++.h>
#include <string>
#define N 26

using namespace std;

void Setup(char data[])
{
          for (int i = 0; i < N; i++)
          {
                    data[i]=char(65+i); //ASCII
          }
}

struct Node
{
          char ch;
          int value;
          struct Node *left, *right;  //child
          Node(char ch, int value)
          {
                    left = right = NULL;
                    this->ch = ch;
                    this->value = value;
          }
};

struct compare
{
          bool operator() (Node *l, Node *r)
          {
                    return (l->value >  r->value); //greater
          }
};

void Encode(struct Node *root, string encoding, string ans[], int *w)
{
          if (!root)
                    return;
          if (root->ch != '*')
          {
                    ans[int(root->ch)-65] = encoding;
                    *w+=root->value*encoding.length(); //WPL
          }

          Encode(root->left, encoding+"0",ans, &*w);
          Encode(root->right, encoding+"1",ans, &*w);
}

void HuffmanCodes(char data[], int wt[], int size, string ans[], int *w)
{
          struct Node *left, *right, *top;
          priority_queue<Node*, vector<Node*>, compare> pq; //min heap
          for (int i = 0; i < size; i++)
                    pq.push(new Node(data[i], wt[i]));
/*
          for (int i = 0; i < size; i++)
          {
                    cout << pq.top()->ch << " " << pq.top()->value << endl;
                    pq.pop();
          }

           for (int i = 0; i < size; i++)
                    pq.push(new Node(data[i], wt[i]));
*/

          while (pq.size() != 1)
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

          Encode(pq.top(), "", ans, &*w);
}

void Output(string ans[], int size, int *w)
{
          cout << "code list {" << endl;
          for (int i = 0; i < N; i++)
          {
                    cout <<  '\t' << char(65+i) << ": " << ans[i] << endl;
          }
          cout << "}" << endl;
          cout << "WPL : " << *w << endl;
}

int main()
{
          //INIT INPUT
          int wt[] = {7, 2, 2, 3, 11, 2, 2, 6, 6, 1, 1, 4, 3, 7, 9, 2, 1, 6, 6, 8, 4, 1, 2, 1, 2, 1};
          char data[N];
          string ans[N]; //encoding result
          Setup(data);

          int WPL=0; //weighted path length
          HuffmanCodes(data, wt, N, ans, &WPL);

          //OUTPUT
          Output(ans, N, &WPL);
          return 0;
}
