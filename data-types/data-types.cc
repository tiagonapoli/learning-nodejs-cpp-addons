#include <node.h>
#include <string>
#include <algorithm>
#include <iostream>
using namespace v8;

void IncNumber(const FunctionCallbackInfo<Value> &args) {
	Isolate *isolate = args.GetIsolate();
	if (args.Length() < 1 || !args[0]->IsNumber()) {
		return;
	}

	double value = args[0]->NumberValue(isolate->GetCurrentContext()).ToChecked();
	value += 42;
	Local<Number> ret = Number::New(isolate, value);
	args.GetReturnValue().Set(ret);
}

void IncInteger(const FunctionCallbackInfo<Value> &args) {
	Isolate *isolate = args.GetIsolate();
	int32_t value = args[0]->Int32Value(isolate->GetCurrentContext()).ToChecked();
	value += 42;
	Local<Number> ret = Int32::New(isolate, value);
	args.GetReturnValue().Set(ret);
}

void NegateBoolean(const FunctionCallbackInfo<Value> &args) {
	Isolate *isolate = args.GetIsolate();
	bool val = args[0]->BooleanValue(isolate);
	Local<Boolean> ret = Boolean::New(isolate, !val);
	args.GetReturnValue().Set(ret);
}

void ReverseString(const FunctionCallbackInfo<Value> &args) {
	Isolate *isolate = args.GetIsolate();
	String::Utf8Value s(isolate, args[0]);
	char *p = *s;
	std::reverse(p, p + s.length());
	Local<String> ret = String::NewFromUtf8(isolate, p, NewStringType::kNormal).ToLocalChecked();
	args.GetReturnValue().Set(ret);
}

void ModifyObject(const FunctionCallbackInfo<Value> &args) {
	Isolate *isolate = args.GetIsolate();
	Local<Object> obj = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
	obj->Set(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "y", NewStringType::kNormal).ToLocalChecked(), Number::New(isolate, 10)).Check();
	args.GetReturnValue().Set(obj);
}

void MathOpsObject(const FunctionCallbackInfo<Value> &args) {
	Isolate *isolate = args.GetIsolate();
	Local<Context> ctx = isolate->GetCurrentContext();
	Local<String> x_prop = String::NewFromUtf8(isolate, "x", NewStringType::kNormal).ToLocalChecked();
	Local<String> y_prop = String::NewFromUtf8(isolate, "y", NewStringType::kNormal).ToLocalChecked();

	Local<Object> obj = args[0]->ToObject(ctx).ToLocalChecked();
	if (!obj->Get(ctx, x_prop).ToLocalChecked()->IsNumber() || !obj->Get(ctx, y_prop).ToLocalChecked()->IsNumber()) {
		return;
	}

	Local<String> sum_prop = String::NewFromUtf8(isolate, "sum", NewStringType::kNormal).ToLocalChecked();
	Local<String> product_prop = String::NewFromUtf8(isolate, "product", NewStringType::kNormal).ToLocalChecked();

	double x = obj->Get(ctx, x_prop).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
	double y = obj->Get(ctx, y_prop).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();

	obj->Set(ctx, sum_prop, Number::New(isolate, x + y)).Check();
	obj->Set(ctx, product_prop, Number::New(isolate, x * y)).Check();
	args.GetReturnValue().Set(obj);
}

void incrementArray(const FunctionCallbackInfo<Value> &args) {
	Isolate *isolate = args.GetIsolate();
	Local<Context> ctx = isolate->GetCurrentContext();
	Local<Array> arr = Local<Array>::Cast(args[0]);

	for (uint32_t i = 0; i < arr->Length(); i++) {
		if (arr->Has(ctx, i).ToChecked()) {
			double value = arr->Get(ctx, i).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).ToChecked();
			arr->Set(ctx, i, Number::New(isolate, value + 1)).ToChecked();
		}
	}
}

void Init(Local<Object> exports) {
	NODE_SET_METHOD(exports, "incNumber", IncNumber);
	NODE_SET_METHOD(exports, "incInteger", IncInteger);
	NODE_SET_METHOD(exports, "incArray", incrementArray);
	NODE_SET_METHOD(exports, "negateBool", NegateBoolean);
	NODE_SET_METHOD(exports, "reverseString", ReverseString);
	NODE_SET_METHOD(exports, "modifyObject", ModifyObject);
	NODE_SET_METHOD(exports, "mathOpsObject", MathOpsObject);
}

NODE_MODULE(type_conversions_addon, Init)