#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

std::vector<std::string> Jia::execute() {
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
    if (expression[1] == "+") {
	double first = std::stod(expression[2]), second = std::stod(expression[3]);
	std::string str = std::to_string(first + second);
	return {str};
    } else if (expression.size() == 3) {
	return {expression[1]};
    } else if (expression.size() == 1) {
	return expression;
    }
    return {"Nothing happens..."};
}

int main() {
    Jia jia;
    jia.loop();
    return 0;
}
