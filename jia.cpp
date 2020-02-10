#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

std::string readFile(std::string file_name) {
    std::ifstream file_stream(file_name);
    if (!file_stream.is_open()) {
	std::cerr << "Jia cannot find " << file_name << "..." << std::endl;
	exit(EXIT_FAILURE);
    }
     std::stringstream file_string_stream;
    file_string_stream << file_stream.rdbuf();
    return file_string_stream.str();
}

bool isDigitalNumber(std::string str) {
    int dot_count = 0;
    if (!isdigit(str[0]) && str[0] != '-') return false;
    for (int i = 1; i < str.size(); ++i) {
	if(!isdigit(str[i])) {
	    if (str[i] == '.') dot_count++;
	    else return false;
	    if (dot_count > 1) return false;
	}
    }
    return true;
}

class Keywords {
public:
    Keywords() = default;
    Keywords(std::vector<std::string> set_keywords);
    void setKeywords(std::vector<std::string> set_keywords);
    std::vector<std::string> getKeywords();
    bool isKeyword(std::string word);
    int search(std::vector<std::string> expression);
private:
    std::vector<std::string> keywords_;
};

Keywords::Keywords(std::vector<std::string> set_keywords) {
    keywords_ = set_keywords;
}

void Keywords::setKeywords(std::vector<std::string> set_keywords) {
    keywords_ = set_keywords;
}

std::vector<std::string> Keywords::getKeywords() {
    return keywords_;
}

bool Keywords::isKeyword(std::string word) {
    for (int i = 0; i < keywords_.size(); ++i)
	if (word == keywords_[i]) return true;
    return false;
}

int Keywords::search(std::vector<std::string> expression) {
    for (int i = 0; i < expression.size(); ++i)
	if (isKeyword(expression[i])) return i;
    return -1;
}

class Str {
public:
    Str() = default;
    Str(std::string set_str);
    void setStr(std::string set_str);
    std::string& getStr();
    void setType(std::string set_type);
    std::string& getType();
    std::string getReverse();
    bool isDigitalNumber();
    std::string getAbsoluteValue();
private:
    std::string str_;
    std::string type_;
};

Str::Str(std::string set_str) {
    str_ = set_str;
    if (::isDigitalNumber(set_str)) type_ = "DigitalNumber";
    else type_ = "Str";
}

void Str::setStr(std::string set_str) {
    str_ = set_str;
}

std::string& Str::getStr() {
    return str_;
}

void Str::setType(std::string set_type) {
    type_ = set_type;
}

std::string& Str::getType() {
    return type_;
}

std::string Str::getReverse() {
    std::string reverse;
    for (int i = str_.size() - 1; i >= 0; --i)
	reverse.push_back(str_[i]);
    return reverse;
}

bool Str::isDigitalNumber() {
    return type_ == "DigitalNumber";
}

std::string Str::getAbsoluteValue() {
    if (this->isDigitalNumber() == false) {
	std::cerr << "This is not a digital number..." << std::endl;
	exit(EXIT_FAILURE);
    }
    if (str_[0] == '-') {
	return str_.substr(1);
    }
    return str_;
}

Str operator+(Str first, Str second) {
    if (first.isDigitalNumber() == false || second.isDigitalNumber() == false) {
	std::cerr << "Either the first or the second argument is not a digital number..." << std::endl;
	exit(EXIT_FAILURE);
    }
    Str first_reverse(first.getReverse()), second_reverse(second.getReverse());
    if (first_reverse.getStr().size() > second_reverse.getStr().size())
	std::swap(first_reverse, second_reverse);
    Str sum("0");
    for (int i = 0; i < second_reverse.getStr().size(); ++i) {
	int a = first_reverse.getStr()[i] - '0', b = second_reverse.getStr()[i] - '0';
	if (i >= first_reverse.getStr().size()) a = 0;
	if (a + b + sum.getStr()[i] - '0' < 10) {
	    sum.getStr()[i] = a + b + sum.getStr()[i];
	    sum.getStr().push_back('0');
	} else {
	    sum.getStr()[i] = a + b + sum.getStr()[i] - 10;
	    sum.getStr().push_back('1');
	}
    }
    for (int i = sum.getStr().size() - 1; i > 0; --i) {
	if (sum.getStr()[i] == '0') sum.getStr().erase(i);
	else break;
    }
    return sum.getReverse();
}

Str operator-(Str first, Str second) {
    Str first_reverse(first.getReverse()), second_reverse(second.getReverse());
    bool is_negative = false;
    if (first_reverse.getAbsoluteValue().size() < second_reverse.getAbsoluteValue().size() || (first_reverse.getAbsoluteValue().size() == second_reverse.getAbsoluteValue().size() && first_reverse.getAbsoluteValue() < second_reverse.getAbsoluteValue())) {
	std::swap(first_reverse, second_reverse);
	is_negative = true;
    }
    Str sum("0");
    for (int i = 0; i < first_reverse.getAbsoluteValue().size(); ++i) {
	int a = first_reverse.getStr()[i] - '0', b = second_reverse.getStr()[i] - '0';
	if (i >= second_reverse.getAbsoluteValue().size()) b = 0;
	if (a - b - (sum.getStr()[i] - '0') >= 0) {
	    sum.getStr()[i] = a - b - sum.getStr()[i] + 2 * '0';
	    sum.getStr().push_back('0');
	} else {
	    sum.getStr()[i] = 10 + a - b - sum.getStr()[i] + 2 * '0';
	    sum.getStr().push_back('1');
	}
    }
    for (int i = sum.getStr().size() - 1; i > 0; --i) {
	if (sum.getStr()[i] == '0') sum.getStr().erase(i);
	else break;
    }
    if (is_negative) sum.getStr().push_back('-');
    return sum.getReverse();
}

class Jia {
public:
    Jia();
    std::vector<std::string> split(std::string str);
    std::vector<std::string> translateExpression(std::vector<std::string> expression);
    std::string execute(std::vector<std::string> arguments);
    std::string recurse(std::vector<std::string> expression);
    void loop();
private:
    Keywords jia_keywords_;
};

Jia::Jia() {
    jia_keywords_.setKeywords({"+", "-", "exit"});
}

std::vector<std::string> Jia::split(std::string str) {
    std::vector<std::string> str_vector;
    for (int i = 0; i < str.size(); ++i)
	if (str[i] != ' ') {
	    std::string s;
	    while (str[i] != ' ')
		s.push_back(str[i++]);
	    str_vector.push_back(s);
	}
    return str_vector;
}

std::vector<std::string> Jia::translateExpression(std::vector<std::string> expression) {
    std::vector<std::string> arguments;
    arguments.push_back(expression[jia_keywords_.search(expression)]);
    for (int i = 0; i < expression.size(); ++i) {
	if (expression[i] == arguments[0] || expression[i] == "(" || expression[i] == ")") continue;
	arguments.push_back(expression[i]);
    }
    return arguments;
}

std::string Jia::execute(std::vector<std::string> arguments) {
    if (arguments[0] == "+") {
	if (arguments.size() != 3){
	    std::cerr << "Number of arguments does not match Jia's \"+\"..." << std::endl;
	    exit(EXIT_FAILURE);
	} else {
	    Str first(arguments[1]), second(arguments[2]);
	    if (arguments[1][1] == '(')
		first = recurse(split(arguments[1]));
	    if (arguments[2][1] == '(')
		second = recurse(split(arguments[2]));
	    return (first + second).getStr();
	}
    } else if (arguments[0] == "-") {
	if (arguments.size() != 3){
	    std::cerr << "Number of arguments does not match Jia's \"-\"..." << std::endl;
	    exit(EXIT_FAILURE);
	} else {
	    Str first(arguments[1]), second(arguments[2]);
	    if (arguments[1][1] == '(')
		first = recurse(split(arguments[1]));
	    if (arguments[2][1] == '(')
		second = recurse(split(arguments[2]));
	    return (first - second).getStr();
	}
    } else if (arguments[0] == "exit") {
	exit(0);
    }
    return "0";
}

std::string Jia::recurse(std::vector<std::string> expression) {
    if ((std::find(expression.begin(), expression.end(), ")") == expression.end() - 1))
	return execute(translateExpression(expression));
    int i = 1;
    std::vector<std::string> arguments;
    while (i < expression.size() - 1) {
	std::string argument;
	int front_parenthesis_count = 0, back_parenthesis_count = 0;
	while (front_parenthesis_count == 0 || front_parenthesis_count != back_parenthesis_count) {
	    if (front_parenthesis_count == 0 && expression[i] != "(") {
		argument = expression[i++];
		break;
	    }
	    if (expression[i] == "(") front_parenthesis_count++;
	    if (expression[i] == ")") back_parenthesis_count++;
	    argument = argument + " " + expression[i++];
	}
	arguments.push_back(argument);
    }
    return execute(translateExpression(arguments));
}

void Jia::loop() {
    for (;;) {
	std::string input;
	std::vector<std::string> expression;
	int front_parenthesis_count = 0, back_parenthesis_count = 0;
	while(std::cin >> input) {
	    if (input == "(") front_parenthesis_count++;
	    if (input == ")") back_parenthesis_count++;
	    expression.push_back(input);
	    if (front_parenthesis_count == back_parenthesis_count) {
		std::cout << recurse(expression) << std::endl;
		break;
	    }
	}
    }
}

int main(int argc, char **argv) {
    Jia jia;
    jia.loop();
    return 0;
}
