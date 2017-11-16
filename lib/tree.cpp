#include <node.h>
#include "tree.h"

Node::Node(){

}

Node::Node(Local<Array> data){
	_data = Local<Array>::Cast(data);
}

Node::Node(vector<Node> children, Local<Array> data){
	this->childs = &children;
	_data = Local<Array>::Cast(data);
}

void Node::SetChildren(vector<Node> children){
	this->childs = &children;
}

vector<Node>* Node::GetChildren(){
	return this->childs;
}

Local<Array> Node::GetData(){
	return this->_data;
}

Tree::Tree(Local<Array> data){
	Node *temp;
	temp = new Node(data);
	root = temp;
}

void Tree::SetRoot(Local<Array> data){
	//Node temp* = new Node(data);
	//root = temp;
}

Local<Array> Tree::GetData(){
	return root->GetData();
}