#pragma once
#include "archives/archive.hpp"
#include "nlohmann/json.hpp"

class JSONOutputArchive : public OutputArchive<JSONOutputArchive> {
public:
	JSONOutputArchive(std::ostream& stream) : 
		OutputArchive<JSONOutputArchive>(this),
		_stream(stream) { };

	~JSONOutputArchive() {
		_stream << _json.dump(4);
	}

	template<typename T>
	void ProcessImpl(NVP<T>&& data) {
		_json[data.name] = data.value;
	}

	template<typename T>
	void ProcessImpl(T&& data) {

	}

private:
	nlohmann::ordered_json _json;
	std::ostream& _stream;
};