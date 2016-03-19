#pragma once
#include<iostream>
#include<string>
class CustomExceptions
{
public:
	//error class
	class ReadError : public std::exception
	{
	public:
		const char* what() const override { return m.c_str(); };
		ReadError(const std::string message) { m = message; }
	private:
		std::string m;
	};
};

