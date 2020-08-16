#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <unordered_map>
#include <string>
#include <unordered_set>
#include <vector>
#include "object.h"

using namespace std;

class Object;

extern vector<unordered_map<string, Object>> object_scopes;
extern unordered_set<string> keywords;
extern unordered_set<string> separators;
extern unordered_set<string> operators;

bool isIdentifier(string to_find);
bool isStart(string str);
bool isEnd(string str);
Object &findObject(string identifier);

#endif