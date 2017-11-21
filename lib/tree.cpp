#include <node.h>
#include "tree.h"

Node::Node(){
}

Node::Node(Local<Array> data){
	// Local<Array> _data = Array::New(isolate);
	_data = data;
}

Node::Node(int init[3][3]){
	for(int i=0; i <3; i++){
		for(int j=0; j <3; j++){
			this->data[i][j] = init[i][j];
		}
	}
}

Local<Array> Node::GetData(){
	Local<Array> gamepad = Array::New(isolate,3);

	for(int i = 0; i < 3; i++){
		Local<Array> row = Array::New(isolate,3);
		for(int j = 0; j < 3; j++){
			row->Set(j, Integer::New(isolate, data[i][j]));
		}
		gamepad->Set(i, row);
	}

	return gamepad;
}

Local<Object> Node::GetObject(){
	Local<Object> node = Object::New(isolate);

	node->Set( String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "node") );

	node->Set( String::NewFromUtf8(isolate, "gamepad"), this->GetData() );
	// node->Set( String::NewFromUtf8(isolate, "parent"), String::NewFromUtf8(isolate, "node") );
	if(childs[0] != NULL){
		Local<Array> children = Array::New(isolate);
		for(int i = 0; i < MAXNODES - 1; i++){
			if( childs[i] != NULL ){
				children->Set(i, childs[i]->GetObject());
			}
		}

		node->Set( String::NewFromUtf8(isolate, "children"), children );
	}
	
	return node;
}

void Node::MakeMoves(int next){
	int counter = -1;
	int gamepad[3][3] = { { 0 } };
	int nextMove = ( next == 1 ) ? 2 : 1;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){

			// A lot of unneficient, i know. But i am short of time
			for(int xi = 0; xi < 3; xi++){
				for(int xj = 0; xj < 3; xj++){
					gamepad[xi][xj] = data[xi][xj];
				}
			}

			if(data[i][j] == 0){
				counter ++;

				gamepad[i][j] = next;

				this->childs[counter] = new Node(gamepad);
				this->childs[counter]->MakeMoves(nextMove);
			}

		}
	}
}

void Node::Destroy(){
	if(childs[0] != NULL){
		for(int i = 0; i < MAXNODES - 1; i++){
			if( childs[i] != NULL ){
				childs[i]->Destroy();
				free(childs[i]);
			}
		}
	}
}

Tree::Tree(Local<Array> data){
	root = new Node(data);
}

Tree::Tree(int data[3][3]){
	root = new Node(data);
}

Local<Object> Tree::GetObject(){
	Local<Object> tree = Object::New(isolate);
	tree->Set( String::NewFromUtf8(isolate, "tree"), root->GetObject());
	return tree;
}

void Tree::Clean(){
	root->Destroy();
	free(root);
}

void Tree::MakeMoves(int next){
	root->MakeMoves(next);
}