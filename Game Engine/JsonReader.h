/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: JsonReader.h
Purpose: A set of functions for opening and reading a JSON file.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/29/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef JSON_READER_H
#define JSON_READER_H

#include <string>
#include "json.hpp"
#include "MathLibraries\Vector2D.h"

using json = nlohmann::json;

namespace AcryJson {
	//template <typename T>
	//void ParseJsonValue(const json j, T&, T, std::string);

	//template <typename T>
	//void ParseJsonValue(const json j, T&, T, std::string, std::string);

	//template <typename T>
	//void ParseJsonValue(const json j, T&, T, std::string, std::string, std::string);


	float ParseFloat(const json j, std::string, std::string);
	float ParseFloat(const json j, std::string, std::string, std::string);

	double ParseDouble(const json j, std::string, std::string);
	double ParseDouble(const json j, std::string, std::string, std::string);

	int ParseInt(const json j, std::string);
	int ParseInt(const json j, std::string, std::string);
	int ParseInt(const json j, std::string, std::string, std::string);

	std::string ParseString(const json j, std::string);
	std::string ParseString(const json j, std::string, std::string);
	std::string ParseString(const json j, std::string, std::string, std::string);

	bool ParseBool(const json j, std::string);
	bool ParseBool(const json j, std::string, std::string);
	bool ParseBool(const json j, std::string, std::string, std::string);


	bool ValueExists(const json j, std::string);
	bool ValueExists(const json j, std::string, std::string);
	bool ValueExists(const json j, std::string, std::string, std::string);

	json OpenJsonFile(std::string fileName);

	bool KeyIs(json::iterator it, std::string key);


	//#include "JsonReader.cpp"
}

#endif