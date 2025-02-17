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

	int GetNextUnnamedIndex() { return unnamedIndex++; }

	std::string GetNextName() {
		if (name != nullptr) {
			const char* temp = name;
			name = nullptr; 
			return temp;
		}

		return "unnamedVariable_" + std::to_string(GetNextUnnamedIndex());
	}

	nlohmann::ordered_json GetNextVariable() { return document[GetNextName()]; }

	nlohmann::ordered_json GetNextArrayIndex() { return document[GetNextUnnamedIndex()]; }
};

class JSONOutputArchive : public Archive<JSONOutputArchive> {
public:
	JSONOutputArchive(std::ostream& stream) : 
		Archive<JSONOutputArchive>(this),
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
			TopStack().GetNextVariable() = data;
	}

	void SetNextName(const char* name) {
		TopStack().name = name;
	}

	void StartIndent(StackContext::Context ctx) {
		_contextStack.push(ctx);
	}

	void EndIndent() {
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


class JSONInputArchive : public Archive<JSONInputArchive> {
public:
	JSONInputArchive(std::istream& stream) :
		Archive<JSONInputArchive>(this)
	{
		_contextStack.push(StackContext::Context::Object);
		_contextStack.top().document = nlohmann::json::parse(stream);
	};

	template<typename T>
	void ProcessImpl(T&& data) {
		if (TopStack().context == StackContext::Context::Array)
			data = TopStack().GetNextArrayIndex();
		else
			data = TopStack().GetNextVariable();
	}

	void SetNextName(const char* name) {
		TopStack().name = name;
	}

	void OpenIndent(StackContext::Context ctx) {
		StackContext context = TopStack();
		_contextStack.push(ctx);
		if (context.context == StackContext::Context::Array) {
			TopStack().document = context.document[TopStack().unnamedIndex++];
		}
		else
			TopStack().document = context.GetNextVariable();
	}

	void CloseIndent() {
		_contextStack.pop();
	}

private:
	StackContext& TopStack() {
		return _contextStack.top();
	}

private:
	std::stack<StackContext> _contextStack;
};

// =======================================
// OutputArchive
// =======================================

template<typename T>
void Prologue(JSONOutputArchive& a, ArrayRef<T>&& ar) {
	std::cout << "Prologueing Array" << std::endl;
	a.StartIndent(StackContext::Context::Array);
}

template<typename T>
void Epilogue(JSONOutputArchive& a, ArrayRef<T>&& ar) {
	std::cout << "Epilogueing Array" << std::endl;
	a.EndIndent();
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
	a.StartIndent(StackContext::Context::Object);
}

template<typename T, typename std::enable_if_t<is_serializable_v<T>, int> = 0>
void Epilogue(JSONOutputArchive& a, T const&) {
	std::cout << "Epilogueing Serializable" << std::endl;
	a.EndIndent();
}

// =======================================
// InputArchive
// =======================================

template<typename T>
void Prologue(JSONInputArchive& a, ArrayRef<T>&& ar) {
	std::cout << "Prologueing Array" << std::endl;
	a.OpenIndent(StackContext::Context::Array);
}

template<typename T>
void Epilogue(JSONInputArchive& a, ArrayRef<T>&& ar) {
	std::cout << "Epilogueing Array" << std::endl;
	a.CloseIndent();
}

// =======================================

template<typename T>
void Prologue(JSONInputArchive& a, NVP<T>&& nvp) {
	std::cout << "Prologueing NVP" << std::endl;
	a.SetNextName(nvp.name);
}

template<typename T>
void Epilogue(JSONInputArchive& a, NVP<T>&& nvp) {
	std::cout << "Epilogueing NVP" << std::endl;
}

// =======================================

template<typename T, typename std::enable_if_t<!is_serializable_v<T>, int> = 0>
void Prologue(JSONInputArchive& a, T const&) {
	std::cout << "Prologueing Something" << std::endl;
}

template<typename T, typename std::enable_if_t<!is_serializable_v<T>, int> = 0>
void Epilogue(JSONInputArchive& a, T const&) {
	std::cout << "Epilogueing Something" << std::endl;
}

// =======================================

template<typename T, typename std::enable_if_t<is_serializable_v<T>, int> = 0>
void Prologue(JSONInputArchive& a, T const&) {
	std::cout << "Prologueing Serializable" << std::endl;
	a.OpenIndent(StackContext::Context::Object);
}

template<typename T, typename std::enable_if_t<is_serializable_v<T>, int> = 0>
void Epilogue(JSONInputArchive& a, T const&) {
	std::cout << "Epilogueing Serializable" << std::endl;
	a.CloseIndent();
}