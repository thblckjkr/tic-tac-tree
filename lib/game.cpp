#include <nan.h>

using namespace v8;

void set(const Nan::FunctionCallbackInfo<Value>& info) {

  /* if (gamepad.Length() != 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  } */

  // Local<Object> pad = Nan::New(gamepad);
  Local<Number> num = Nan::New(15 + 16);
  info.GetReturnValue().Set(num);
}

void Init(Local<Object> exports) {
  exports->Set(Nan::New("set").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(set)->GetFunction());
}

NODE_MODULE(addon, Init)