#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#define STRV_MAX 1024
#define EPSILON 0.000001

bool isFunStart(std::string str);
bool isFunEnd(std::string str);
bool isFullExpr(std::vector<std::string> strv);
bool isFullExpr(std::vector<std::string> strv, size_t p, size_t q);
std::vector<std::string> getExpr(std::vector<std::string> strv, size_t p);
bool isStartSymbol(char c);
bool isEndSymbol(char c);
void symbolSplit(std::vector<std::string> &strv, size_t p);
std::vector<std::string> readStream(std::istream &in);
std::vector<std::string> readFile(std::string file_name);
std::vector<std::string> readShell();
std::string numToStr(double num);
std::ostream &operator<<(std::ostream &out, std::vector<std::string> strv);

#endif