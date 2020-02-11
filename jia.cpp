#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

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
    std::vector<std::string> movingSplit(int &i);
    std::vector<std::string> split(int i);
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
	int front_parenthesis_count = 0, back_parenthesis_count = 0;
	while(std::cin >> input) {
	    if (input == "(") ++front_parenthesis_count;
	    if (input == ")") ++back_parenthesis_count;
	    expression_.push_back(input);
	    if (front_parenthesis_count == back_parenthesis_count) {
		for (auto str : execute()) std::cout << str << std::endl;
		break;
	    }
	}
	expression_.clear();
    }
}

std::vector<std::string> Jia::movingSplit(int &i) {
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

std::vector<std::string> Jia::split(int i) {
    return movingSplit(i);
}

std::vector<std::string> Jia::execute() {
    if (expression_[1] == "def") {
	int p = 4;
	Definition definition;
	std::vector<std::string> parameters;
        while (expression_[p] != ")") parameters.push_back(expression_[p++]);
	definition.parameters = parameters;
	std::vector<std::string> body;
	for (int i = p + 1; i < expression_.size() - 1; ++i) body.push_back(expression_[i]);
	definition.body = body;
	definitions.insert(std::pair<std::string, Definition>(expression_[2], definition));
	return {expression_[2]};
    }
    std::vector<std::string> expression;
    if (std::find(expression_.begin(), expression_.end(), ")") != expression_.end() - 1) {
	expression.push_back(expression_[0]);
	expression.push_back(expression_[1]);
	for (int i = 2; i < expression_.size() - 1; ++i) {
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
    if (expression[1] == "exit") exit(0);
    if (definitions.find(expression[1]) != definitions.end()) {
	std::string replaced = expression[1];
	std::map<std::string, std::string> arguments;
	for (int i = 0; i < definitions[replaced].parameters.size(); ++i) {
	    arguments.insert(std::pair<std::string, std::string>(definitions[replaced].parameters[i], expression[2]));
	    expression.erase(expression.begin() + 2);
	}
        for (int j = 0; j < definitions[replaced].body.size(); ++j) {
	    std::string to_insert = definitions[replaced].body[j];
	    if (std::find(definitions[replaced].parameters.begin(), definitions[replaced].parameters.end(), to_insert) != definitions[replaced].parameters.end())
		to_insert = arguments[to_insert];
	    if (j == 0) {
		expression[1] = to_insert;
		continue;
	    }
	    expression.insert(expression.begin() + 1 + j, to_insert);
	}
	Jia jia_recursion(expression);
	return jia_recursion.execute();
    }
    if (expression[1] == "+") {
	double first = std::stod(expression[2]), second = std::stod(expression[3]);
	std::string str = std::to_string(first + second);
	return {str};
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
