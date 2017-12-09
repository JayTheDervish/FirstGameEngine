#ifndef JSON_READER_CPP
#define JSON_READER_CPP

#include "JsonReader.h"
#include <fstream>

namespace AcryJson {
	//template <typename T>
	//void ParseJsonValue(const json j, T& result, T defaultValue, std::string first)
	//{
	//	if (j.find(first) != j.end())
	//		result = j[first];
	//	result = defaultValue;
	//}

	//template <typename T>
	//void ParseJsonValue(const json j, T& result, T defaultValue, std::string first, std::string second)
	//{
	//	if (j.find(first) != j.end()) {
	//		if (j[first].find(second) != j[first].end())
	//			result = j[first][second];
	//	}6
	//	result = defaultValue;
	//}

	//template <typename T>
	//void ParseJsonValue(const json j, T& result, T defaultValue, std::string first, std::string second, std::string third)
	//{
	//	if (j.find(first) != j.end()) {
	//		if (j[first].find(second) != j[first].end()) {
	//			if (j[first][second].find(third) != j[first][second].end())
	//				result = j[first][second][third];
	//		}
	//	}
	//	result = defaultValue;
	//}

	float ParseFloat(const json j, std::string first, std::string second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end())
				return j[first][second];
		}
		return 0.0f;
	}

	float ParseFloat(const json j, std::string first, std::string second, std::string third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return j[first][second][third];
			}
		}
		return 0.0f;
	}

	double ParseDouble(const json j, std::string first, std::string second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end())
				return j[first][second];
		}
		return 0.0;
	}

	double ParseDouble(const json j, std::string first, std::string second, std::string third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return j[first][second][third];
			}
		}
		return 0.0;
	}

	int ParseInt(const json j, std::string first)
	{
		if (j.find(first) != j.end())
			return j[first];
		return 0;
	}

	int ParseInt(const json j, std::string first, std::string second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end())
				return j[first][second];
		}
		return 0;
	}

	int ParseInt(const json j, std::string first, std::string second, std::string third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return j[first][second][third];
			}
		}
		return 0;
	}

	std::string ParseString(const json j, std::string first)
	{
		if (j.find(first) != j.end())
			return j[first];
		return "";
	}

	std::string ParseString(const json j, std::string first, std::string second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end())
				return j[first][second];
		}
		return "";
	}

	std::string ParseString(const json j, std::string first, std::string second, std::string third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return j[first][second][third];
			}
		}
		return "";
	}

	bool ParseBool(const json j, std::string first)
	{
		if (j.find(first) != j.end())
			return j[first];
		return false;
	}

	bool ParseBool(const json j, std::string first, std::string second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end())
				return j[first][second];
		}
		return false;
	}

	bool ParseBool(const json j, std::string first, std::string second, std::string third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return j[first][second][third];
			}
		}
		return false;
	}

	Vector2D ParseVector2D(const json j, std::string first, std::string second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				Vector2D vector2d;
					vector2d.x = ParseFloat(j, first, second, "x");
					vector2d.y = ParseFloat(j, first, second, "y");
					return vector2d;
			}
		}
		return Vector2D();
	}

	bool ValueExists(const json j, std::string first)
	{
		return (j.find(first) != j.end());
	}

	bool ValueExists(const json j, std::string first, std::string second)
	{
		if (j.find(first) != j.end()) {
			return j[first].find(second) != j[first].end();
		}
		return false;
	}

	bool ValueExists(const json j, std::string first, std::string second, std::string third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return true;
			}
		}
		return false;
	}

	json OpenJsonFile(std::string fileName)
	{
		std::ifstream i(fileName);
		json j;
		i >> j;
		i.close();
		return j;
	}

	bool KeyIs(json::iterator it, std::string key)
	{
		return it.key().compare(key) == 0;
	}

}

#endif