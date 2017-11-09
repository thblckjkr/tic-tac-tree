#include <nan.h>

using namespace Nan;
using namespace v8;
using namespace std;

class Game : public ObjectWrap {
public:
  static void Init(Local<Object> exports);
  static void Set(const Nan::FunctionCallbackInfo<Value>& info);

private:
  int gamepad[3];
};

void Game::Set(const Nan::FunctionCallbackInfo<Value>& info) {
  Local<Function> callback = info[0].As<Function>(); // For make callbacks
  const unsigned argc = 1;

  Local<Array> gamepad = New<v8::Array>(4);

  for(int i = 0; i < 3; i++){
      Nan::Set(gamepad, i, New<Number>(*((int *) 2)));
  }
  
  v8::Local<v8::Value> argv[argc] = gamepad;
  
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, argc, argv );
}

void Game::Init(Local<Object> exports) {
  exports->Set(Nan::New("set").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(Game::Set)->GetFunction());
}

NODE_MODULE(addon, Game::Init)