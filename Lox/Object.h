#pragma once
#include <string>

class Object {
public:
	virtual ~Object() = default;
	virtual std::string toString() = 0;
};


class Bool : public Object {
public:
	bool value;
	Bool(bool value) : value(value) {}
	std::string toString() override {
		return value ? "true" : "false";
	}
};

class Number : public Object {
public:
	double value;
	Number(double value) : value(value) {}
	std::string toString() override {
		return std::to_string(value);
	}
};

class String : public Object {
public:
	std::string value;
	String(const std::string& value) : value(value) {}
	std::string toString() override {
		return value;
	}
};

class Nil : public Object {
public:
	Nil() = default;
	std::string toString() override {
		return "nil";
	}
};

