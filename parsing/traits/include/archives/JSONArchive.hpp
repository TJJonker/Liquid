#pragma once
#include "archives/archive.hpp"
#include "nlohmann/json.hpp"
#include <stack>

struct StackContext {
	enum class Context {
		Array,
		Object
	};

	Context context;
	int unnamedIndex;
	nlohmann::ordered_json document;
	const char* name;

	StackContext(Context context) : context(context), unnamedIndex(0), name(nullptr) { }

	std::string GetNextName() {
		if (name != nullptr) {
			const char* temp = name;
			name = nullptr; 
			return temp;
		}

		return "unnamedVariable_" + std::to_string(unnamedIndex++);
	}
};

class JSONOutputArchive : public OutputArchive<JSONOutputArchive> {
public:
	JSONOutputArchive(std::ostream& stream) : 
		OutputArchive<JSONOutputArchive>(this),
		_stream(stream) 
	{ 
		_contextStack.push(StackContext::Context::Object);
	};

	~JSONOutputArchive() {
		_stream << TopStack().document.dump(4);
	}

	template<typename T>
	void ProcessImpl(T&& data) {
		if (TopStack().context == StackContext::Context::Array)
			TopStack().document.push_back(data);
		else
			TopStack().document[TopStack().GetNextName()] = data;
	}

	void SetNextName(const char* name) {
		TopStack().name = name;
	}

	void StartArray() {
		_contextStack.push(StackContext::Context::Array);
	}

	void EndArray() {
		StackContext context = TopStack();
		_contextStack.pop();
		ProcessImpl(context.document);
	}

	void StartObject() {
		_contextStack.push(StackContext::Context::Object);
	}

	void EndObject() {
		StackContext context = TopStack();
		_contextStack.pop();
		ProcessImpl(context.document);
	}

private:
	StackContext& TopStack() {
		return _contextStack.top();
	}

private:
	std::ostream& _stream;
	std::stack<StackContext> _contextStack;
};


// =======================================

template<typename T>
void Prologue(JSONOutputArchive& a, ArrayRef<T>&& ar) {
	std::cout << "Prologueing Array" << std::endl;
	a.StartArray();
}

template<typename T>
void Epilogue(JSONOutputArchive& a, ArrayRef<T>&& ar) {
	std::cout << "Epilogueing Array" << std::endl;
	a.EndArray();
}

// =======================================

template<typename T>
void Prologue(JSONOutputArchive& a, NVP<T>&& nvp) {
	std::cout << "Prologueing NVP" << std::endl;
	a.SetNextName(nvp.name);
}

template<typename T>
void Epilogue(JSONOutputArchive& a, NVP<T>&& nvp) {
	std::cout << "Epilogueing NVP" << std::endl;
}

// =======================================

template<typename T, typename std::enable_if_t<!is_serializable_v<T>, int> = 0>
void Prologue(JSONOutputArchive& a, T const&) {
	std::cout << "Prologueing Something" << std::endl;
}

template<typename T, typename std::enable_if_t<!is_serializable_v<T>, int> = 0>
void Epilogue(JSONOutputArchive& a, T const&) {
	std::cout << "Epilogueing Something" << std::endl;
}

// =======================================

template<typename T, typename std::enable_if_t<is_serializable_v<T>, int> = 0>
void Prologue(JSONOutputArchive& a, T const&) {
	std::cout << "Prologueing Serializable" << std::endl;
	a.StartObject();
}

template<typename T, typename std::enable_if_t<is_serializable_v<T>, int> = 0>
void Epilogue(JSONOutputArchive& a, T const&) {
	std::cout << "Epilogueing Serializable" << std::endl;
	a.EndObject();
}