#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

typedef struct Definition {
    std::vector<std::string> parameters;
    std::vector<std::string> body;
} Definition;

std::map<std::string, Definition> definitions;

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

class Jia {
public:
    Jia() = default;
    Jia(std::vector<std::string> set_expression);
    void loop();
    void rewriteArguments();
    std::vector<std::string> rewriteExpression(std::vector<std::string> expression);
    std::vector<std::string> movingSplit(size_t &i);
    std::vector<std::string> split(size_t i);
    std::vector<std::string> recurse();
    std::vector<std::string> execute();
private:
    std::vector<std::string> expression_;
};

Jia::Jia(std::vector<std::string> set_expression) {
    expression_ = set_expression;
}

void Jia::loop() {
    for (;;) {
	std::string input;
	std::getline(std::cin, input);
	std::stringstream input_string_stream(input);
	expression_.push_back("(");
	std::string input_string;
	while (input_string_stream >> input_string) expression_.push_back(input_string);
	expression_.push_back(")");
	for (auto str : execute()) std::cout << str << std::endl;
	expression_.clear();
    }
}

void Jia::rewriteArguments() {
    for (size_t i = 0; i < expression_.size(); ++i)
	if (definitions.find(expression_[i]) != definitions.end() && definitions[expression_[i]].parameters.size() == 0)
	    if (i - 1 < 0 || i + 1 > expression_.size() || expression_[i - 1] != "(" || expression_[i + 1] != ")") {
		expression_.insert(expression_.begin() + i + 1, ")");
	        expression_.insert(expression_.begin() + i, "(");
	        i += 2;
	    }
}

std::vector<std::string> Jia::rewriteExpression(std::vector<std::string> expression) {
    std::string replaced = expression[1];
    std::map<std::string, std::string> arguments;
    for (size_t i = 0; i < definitions[replaced].parameters.size(); ++i) {
	arguments.insert(std::pair<std::string, std::string>(definitions[replaced].parameters[i], expression[2]));
        expression.erase(expression.begin() + 2);
    }
    for (size_t j = 0; j < definitions[replaced].body.size(); ++j) {
	std::string to_insert = definitions[replaced].body[j];
        if (std::find(definitions[replaced].parameters.begin(), definitions[replaced].parameters.end(), to_insert) != definitions[replaced].parameters.end())
	    to_insert = arguments[to_insert];
	if (j == 0) {
	    expression[1] = to_insert;
	    continue;
	}
	expression.insert(expression.begin() + 1 + j, to_insert);
    }
    return expression;
}

std::vector<std::string> Jia::movingSplit(size_t &i) {
    std::vector<std::string> splited;
    int front_parenthesis_count = 0, back_parenthesis_count = 0;
    while (i < expression_.size() - 1) {
	if (expression_[i] == "(") ++front_parenthesis_count;
	if (expression_[i] == ")") ++back_parenthesis_count;
	if (front_parenthesis_count == back_parenthesis_count) {
	    splited.push_back(")");
	    break;
	}
	splited.push_back(expression_[i++]);
    }
    return splited;
}

std::vector<std::string> Jia::split(size_t i) {
    return movingSplit(i);
}

std::vector<std::string> Jia::recurse() {
    std::vector<std::string> expression;
    if (std::find(expression_.begin(), expression_.end(), ")") != expression_.end() - 1) {
	expression.push_back(expression_[0]);
	expression.push_back(expression_[1]);
	for (size_t i = 2; i < expression_.size() - 1; ++i) {
	    std::vector<std::string> before_recursion;
	    if (expression_[i] != "(") expression.insert(expression.end(), expression_[i]);
	    else {
		Jia jia_recursion(movingSplit(i));
		std::vector<std::string> after_recursion = jia_recursion.execute();
		expression.insert(expression.end(), after_recursion.begin(), after_recursion.end());
	    }
	}
	expression.push_back(")");
    } else expression = expression_;
    return expression;
}

std::vector<std::string> Jia::execute() {
    rewriteArguments();
    if (expression_[1] == "def") {
	int p = 4;
	Definition definition;
	std::vector<std::string> parameters;
        while (expression_[p] != ")") parameters.push_back(expression_[p++]);
	definition.parameters = parameters;
	std::vector<std::string> body;
	for (size_t i = p + 1; i < expression_.size() - 1; ++i) body.push_back(expression_[i]);
	definition.body = body;
	definitions.insert(std::pair<std::string, Definition>(expression_[2], definition));
	return {expression_[2]};
    }
    
    std::vector<std::string> expression = recurse();
    if (expression[1] == "exit") exit(0);
    if (definitions.find(expression[1]) != definitions.end()) {
	Jia jia_recursion(rewriteExpression(expression));
	return jia_recursion.execute();
    }
    if (expression[1] == "if") {
	if (expression[2] == "true") {
	    Jia jia_true(split(3));
	    return jia_true.execute();
	} else {
	    Jia jia_false(split(3));
	    return jia_false.execute();
	}
    }
    if (expression[1] == "while") {
	while (expression[2] == "true") {
	    Jia jia_true(split(0));
	    return jia_true.execute();
	}
    }
    if (expression[1] == "+") {
	double sum = std::stod(expression[2]);
        for (size_t i = 3; i < expression.size() - 1; ++i) {
	    decltype(sum) next = std::stod(expression[i]);
	    sum += next;
	}
	std::string str = std::to_string(sum);
	return {str};
    } else if (expression[1] == "-") {
	double sum = std::stod(expression[2]);
        for (size_t i = 3; i < expression.size() - 1; ++i) {
	    decltype(sum) next = std::stod(expression[i]);
	    sum -= next;
	}
	std::string str = std::to_string(sum);
	return {str};
    } else if (expression[1] == "*") {
	double sum = std::stod(expression[2]);
        for (size_t i = 3; i < expression.size() - 1; ++i) {
	    decltype(sum) next = std::stod(expression[i]);
	    sum *= next;
	}
	std::string str = std::to_string(sum);
	return {str};
    } else if (expression[1] == "/") {
	double sum = std::stod(expression[2]);
        for (size_t i = 3; i < expression.size() - 1; ++i) {
	    decltype(sum) next = std::stod(expression[i]);
	    sum /= next;
	}
	std::string str = std::to_string(sum);
	return {str};
    } else if (expression[1] == "==") {
	double first = std::stod(expression[2]);
        for (size_t i = 3; i < expression.size() - 1; ++i) {
	    decltype(first) next = std::stod(expression[i]);
	    if (first != next) return {"false"};
	}
	return {"true"};
    } else if (expression[1] == "<") {
	double first = std::stod(expression[2]);
        for (size_t i = 3; i < expression.size() - 1; ++i) {
	    decltype(first) next = std::stod(expression[i]);
	    if (first >= next) return {"false"};
	}
        return {"true"};
    } else if (expression[1] == ">") {
	double first = std::stod(expression[2]);
        for (size_t i = 3; i < expression.size() - 1; ++i) {
	    decltype(first) next = std::stod(expression[i]);
	    if (first <= next) return {"false"};
	}
	return {"true"};
    } else if (expression.size() == 3) {
	return {expression[1]};
    } else if (expression.size() == 1) {
	return expression;
    } else if (expression.size() > 2 && expression[0] == "(" && expression[expression.size() - 1] == ")") {
	Jia jia_recursion(split(1));
	return jia_recursion.execute();
    }
    return {"Nothing happens..."};
}

int main() {
    Jia jia;
    jia.loop();
    return 0;
}
