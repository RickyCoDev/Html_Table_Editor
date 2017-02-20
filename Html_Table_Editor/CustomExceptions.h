/*
Html_Table_Editor
https://github.com/rickycorte/Html_Table_Editor

Copyright (c) 2016 Ricky Corte

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#pragma once
#include<iostream>
#include<string>
class CustomExceptions
{
public:
	//error class



	//error class
	class ReadError : public std::exception
	{
	public:
		const char* what() const noexcept override { return m.c_str(); };
		ReadError(const std::string message) { m = message; }
	private:
		std::string m;
	};

	class FileError : public std::exception
	{
	public:
		const char* what() const noexcept override { return m.c_str(); };
		FileError(const std::string message) { m = message; }
	private:
		std::string m;
	};

	class CmdError : public std::exception
	{
	public:
		const char* what() const noexcept override { return m.c_str(); };
		CmdError(const std::string message) { m = message; }
	private:
		std::string m;
	};
};

