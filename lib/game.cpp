#include <node.h>
#include "game.h"
#include "tree.h"

void getTree(const v8::FunctionCallbackInfo<v8::Value>&args){
  // Isolate* isolate = args.GetIsolate(); // Get the isolate adress

  // Get the gamepad sent
  Local<Array> gamepad = Local<Array>::Cast(args[0]);

  Tree* tree = new Tree(gamepad);

  tree->MakeMoves(1); // Set the nodes data

  args.GetReturnValue().Set(tree->GetObject());
}

void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "getTree", getTree);
}

NODE_MODULE(addon, Initialize);