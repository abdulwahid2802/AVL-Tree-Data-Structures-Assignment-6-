//
//  main.cpp
//  AVL_Tree
//
//  Created by mac on 5/27/18.
//  Copyright © 2018 mac. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <time.h>
#include <cstdlib>
#include <queue>

using namespace std;

class Tree
{
    typedef struct Node
    {
        int data;
        int height;
        int info;
        string path;
        Node* left;
        Node* right;
    }*Nptr;
    
    Nptr root;
    
    // standart tree insertion & printing methods
    void _makeNode(int);
    void _addNode(Nptr &, Nptr);
    void _print(Nptr, string)const;
    void _traverse(Nptr)const;
    
    void _tracePath(Nptr &, string, int);

    // methods to help with rotation and balance
    void _rotate_R(Nptr &);
    void _rotate_L(Nptr &);
    void _balance(Nptr &);
    void fixHeight(Nptr &);

    // helper methods for balance which will determine and adjust height
    int height(Nptr)const;
    int b_factor(Nptr)const;

public:
    Tree():root(NULL){}
    void insert(int);
    void traverse()const;
    void print()const;
};


void Tree::insert(int data)
{
    _makeNode(data);
}

void Tree::_makeNode(int data)
{
    Nptr n = new Node();
    n->data=data;
    n->left=n->right=NULL;
    n->height = 1;
    n->info = 0; // to check if the node is changed
    n->path="H";
    
    _addNode(root, n);
}

int Tree::height(Nptr Ptr)const
{
    return Ptr ? Ptr->height : 0;
}

int Tree::b_factor(Nptr Ptr)const
{
    return height(Ptr->right) - height(Ptr->left);
}

void Tree::fixHeight(Nptr &Ptr)
{
    int lh = height(Ptr->left);
    int rh = height(Ptr->right);
    
    Ptr->height = (lh > rh ? lh : rh) + 1;
}

void Tree::_rotate_R(Nptr &Ptr)
{
    Nptr temp = Ptr->left;
    Ptr->left = temp->right;
    temp->right=Ptr;
    Ptr=temp;
    
    fixHeight(Ptr->right);
    fixHeight(Ptr);
}

void Tree::_rotate_L(Nptr &Ptr)
{
    Nptr temp = Ptr->right;
    Ptr->right = temp->left;
    temp->left = Ptr;
    Ptr = temp;
    
    fixHeight(Ptr->left);
    fixHeight(Ptr);
}

void Tree::_balance(Nptr &Ptr)
{
    if(Ptr)
    {
        fixHeight(Ptr);
        if(b_factor(Ptr)==2)
        {
            if(b_factor(Ptr->right)<0)
                _rotate_R(Ptr->right);
            _rotate_L(Ptr);
        }
        else if(b_factor(Ptr)==-2)
        {
            if(b_factor(Ptr->left)>0)
                _rotate_L(Ptr->left);
            _rotate_R(Ptr);
        }
    }
}

void Tree::_addNode(Nptr &Ptr, Nptr n)
{
    if(Ptr==NULL)
        Ptr=n;
    else if(n->data < Ptr->data)
    {
        n->path+="L";
        _addNode(Ptr->left, n);
    }
    else if(n->data > Ptr->data)
    {
        n->path+="R";
        _addNode(Ptr->right, n);
    }
    
    _balance(Ptr);
    _tracePath(root, "H", 0);
}

void Tree::_tracePath(Nptr &Ptr, string nPath, int info)
{
    if(Ptr)
    {
        Ptr->info = info;
        if(Ptr->path != nPath)
        {
            cout<<Ptr->data<<" changed from "<<Ptr->path<<" to new path: "<<nPath<<endl;
            Ptr->path = nPath;
        }
        _tracePath(Ptr->left, nPath+"L", info+1);
        _tracePath(Ptr->right, nPath+"R", info+1);
        
    }
}

void Tree::print()const
{
    _print(root, "H");
    cout<<endl;
}

void Tree::_print(Nptr Ptr, string path)const
{
    if(Ptr)
    {
        _print(Ptr->left, path+"L");
        cout<<Ptr->data<<" ";
        _print(Ptr->right, path+"R");
    }
}

void Tree::traverse()const
{
    _traverse(root);
}

void Tree::_traverse(Nptr Ptr)const
{
    if(Ptr)
    {
        
        queue<Nptr> q;
        
        q.push(Ptr);
        do
        {
            Nptr temp = q.front();
            if(temp->left!=NULL)
                q.push(temp->left);
            if(temp->right!=NULL)
                q.push(temp->right);
            
            cout<<temp->data<<" level - "<<temp->info<<"   path:"<<temp->path<<endl;
            q.pop();
            
        }while(q.size()!=0);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Tree t;
    char c;
    
    do
    {
        cin >> c;
        switch(c)
        {
            case 'i':
                int temp;
                cin>>temp;
                t.insert(temp);
                break;
            case 't':
                t.traverse();
                break;
            case 'p':
                t.print();
                break;

            default: break;
        }
        
    }while(c!='e');
    
    
    return 0;
}
