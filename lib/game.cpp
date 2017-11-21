#include <node.h>
#include "game.h"
#include "tree.h"

void getTree(const v8::FunctionCallbackInfo<v8::Value>&args){
  Isolate* isolate = args.GetIsolate(); // Get the isolate adress
  int gamepad[3][3] = { { 0 } };
  // Get the gamepad sent
  Local<Array> gamepadSent = Local<Array>::Cast(args[0]);
  Local<Array> row = Array::New(isolate);

  int next = (int)args[1]->Int32Value();

  for(int i = 0; i < 3; i++){
		// Get row by row
		row = Local<Array>::Cast(gamepadSent->Get(i));
		for(int j = 0; j < 3; j++){
			  gamepad[i][j] = (int)row->Get(j)->Int32Value();
    }
  }
  
  Tree *tree = new Tree(gamepad);

  tree->MakeMoves(next); // Set the nodes data

  args.GetReturnValue().Set(tree->GetObject());
  // tree->Clean();
}

void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "getTree", getTree);
}

NODE_MODULE(addon, Initialize);