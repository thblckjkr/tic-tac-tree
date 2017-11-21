#include <node.h>
#include "tree.h"

Node::Node(){

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

bool Node::IsWinner(){
/*
To not overload tree
check if is winner the node

Data winners
X X X <- Winner by row (i to 3)
0 0 0
0 0 0
-----
X 0 0 <- Winner by col (i to 3)
X 0 0
X 0 0
-----
0 0 X <- Winner by diag x2
0 X 0
X 0 0

X 0 0
0 X 0
0 0 X
*/

	// Winner by row
	for(int i = 0; i < 3; i++ ){
		if( data[i][0] != 0 && data[i][0] == data[i][1] && data[i][1] == data[i][2] ){
			winner = data[i][0];
			return true;
		}
	}

	// Winner by col
	for(int i = 0; i < 3; i++ ){
		if( data[0][i] != 0 &&  data[0][i] == data[1][i] && data[1][i] == data[2][i] ){
			winner = data[0][i];
			return true;
		}
	}

	if( data[0][0] != 0 && data[0][0] == data[1][1] && data[1][1] == data[2][2]){
		winner = data[0][0];
		return true;
	}

	if(data[2][0] != 0 && data[0][2] == data[1][1] && data[1][1] == data[2][0]){
		winner = data[2][0];
		return true;
	}

	return false;

}

Local<Object> Node::GetObject(){
	Local<Object> node = Object::New(isolate);

	node->Set( String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "node") );

	node->Set( String::NewFromUtf8(isolate, "gamepad"), this->GetData() );

	Local<Integer> win = Integer::New(isolate, winner);

	node->Set( String::NewFromUtf8(isolate, "winner"), win );
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

	if(this->IsWinner()){
		// Do not continue because is a dead end
		return ;
	}

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