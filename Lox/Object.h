#pragma once
#include <string>

class Object {
public:
	virtual ~Object() = default;
	virtual std::string toString() = 0;
	virtual bool operator==(const Object& other) const = 0;
};


class Bool : public Object {
public:
	bool value;
	Bool(bool value) : value(value) {}
	std::string toString() override {
		return value ? "true" : "false";
	}
	bool operator==(const Object& other) const override {
		if (auto otherBool = dynamic_cast<const Bool*>(&other)) {
			return value == otherBool->value;
		}
		return false;
	}
};

class Number : public Object {
public:
	double value;
	Number(double value) : value(value) {}
	std::string toString() override {
		std::string text = std::to_string(value);
		if (text.substr(text.find_last_not_of('0') + 1) == ".") {
			text = text.substr(0, text.find_last_not_of('0'));
		}
		return text;
	}
	bool operator==(const Object& other) const override {
		if (auto otherNumber = dynamic_cast<const Number*>(&other)) {
			return value == otherNumber->value;
		}
		return false;
	}
};

class String : public Object {
public:
	std::string value;
	String(const std::string& value) : value(value) {}
	std::string toString() override {
		return value;
	}
	bool operator==(const Object& other) const override {
		if (auto otherString = dynamic_cast<const String*>(&other)) {
			return value == otherString->value;
		}
		return false;
	}
};

//class Nil : public Object {
//public:
//	Nil() = default;
//	std::string toString() override {
//		return "nil";
//	}
//};
//
