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

class DigitalNumber {
public:
    DigitalNumber() = delete;
    DigitalNumber(std::string set_digital_number);
    friend std::ostream& operator<<(std::ostream &out, DigitalNumber digital_number);
    friend std::istream& operator>>(std::istream &in, DigitalNumber digital_number);
    void setDigitalNumber(std::string set_digital_number);
    std::string& getDigitalNumber();
    int size();
    std::string getReverse();
    char& operator[](int position);
    void push_back(char c);
    std::string absoluteValue();
private:
    std::string digital_number_;
};

std::ostream& operator<<(std::ostream &out, DigitalNumber digital_number) {
    std::cout << digital_number.digital_number_;
    return out;
}

std::istream& operator>>(std::istream &in, DigitalNumber digital_number) {
    std::cin >> digital_number.digital_number_;
    return in;
}

DigitalNumber::DigitalNumber(std::string set_digital_number) {
    if (!isDigitalNumber(set_digital_number)) {
	std::cerr << "\"" << set_digital_number << "\" is not a digital number..." << std::endl;
	exit(EXIT_FAILURE);
    }
    digital_number_ = set_digital_number;
}

void DigitalNumber::setDigitalNumber(std::string set_digital_number) {
    if (!isDigitalNumber(set_digital_number)) {
	std::cerr << "\"" << set_digital_number << "\" is not a digital number..." << std::endl;
	exit(EXIT_FAILURE);
    }
    digital_number_ = set_digital_number;
}

std::string& DigitalNumber::getDigitalNumber() {
    return digital_number_;
}

int DigitalNumber::size() {
    return digital_number_.size();
}

std::string DigitalNumber::getReverse() {
    std::string reverse;
    for (int i = digital_number_.size() - 1; i >= 0; --i)
	reverse.push_back(digital_number_[i]);
    return reverse;
}

char& DigitalNumber::operator[](int i) {
    return digital_number_[i];
}

void DigitalNumber::push_back(char c) {
    digital_number_.push_back(c);
}

std::string DigitalNumber::absoluteValue() {
    if (digital_number_[0] == '-') {
	return digital_number_.substr(1);
    }
    return digital_number_;
}

DigitalNumber operator+(DigitalNumber first, DigitalNumber second) {
    DigitalNumber first_reverse(first.getReverse()), second_reverse(second.getReverse());
    if (first_reverse.getDigitalNumber().size() > second_reverse.getDigitalNumber().size())
	std::swap(first_reverse, second_reverse);
    DigitalNumber sum("0");
    for (int i = 0; i < second_reverse.getDigitalNumber().size(); ++i) {
	int a = first_reverse[i] - '0', b = second_reverse[i] - '0';
	if (i >= first_reverse.getDigitalNumber().size()) a = 0;
	if (a + b + sum[i] - '0' < 10) {
	    sum[i] = a + b + sum[i];
	    sum.push_back('0');
	} else {
	    sum[i] = a + b + sum[i] - 10;
	    sum.push_back('1');
	}
    }
    if (sum[sum.size() - 1] == '0') sum.getDigitalNumber().erase(sum.size() - 1);
    return sum.getReverse();
}

DigitalNumber operator-(DigitalNumber first, DigitalNumber second) {
    DigitalNumber first_reverse(first.getReverse()), second_reverse(second.getReverse());
    bool is_negative = false;
    if (first_reverse.absoluteValue().size() < second_reverse.absoluteValue().size() || (first_reverse.absoluteValue().size() == second_reverse.absoluteValue().size() && first_reverse.absoluteValue() < second_reverse.absoluteValue())) {
	std::swap(first_reverse, second_reverse);
	is_negative = true;
    }
    DigitalNumber sum("0");
    for (int i = 0; i < first_reverse.absoluteValue().size(); ++i) {
	int a = first_reverse[i] - '0', b = second_reverse[i] - '0';
	if (i >= second_reverse.absoluteValue().size()) b = 0;
	if (a - b - (sum[i] - '0') >= 0) {
	    sum[i] = a - b - sum[i] + 2 * '0';
	    sum.push_back('0');
	} else {
	    sum[i] = 10 + a - b - sum[i] + 2 * '0';
	    sum.push_back('1');
	}
    }
    for (int i = sum.size() - 1; i >= 0; --i) {
	if (sum[i] == '0') sum.getDigitalNumber().erase(i);
	else break;
    }
    if (is_negative) sum.push_back('-');
    return sum.getReverse();
}

class Jia {
public:
    Jia();
    std::vector<std::string> translateExpression(std::vector<std::string> expression);
    int execute(std::vector<std::string> arguments);
    void loop();
private:
    Keywords jia_keywords_;
};

Jia::Jia() {
    jia_keywords_.setKeywords({"+", "-", "exit"});
}

std::vector<std::string> Jia::translateExpression(std::vector<std::string> expression) {
    std::vector<std::string> arguments;
    // for (auto i : expression) std::cout << i << std::endl;
    if (std::find(expression.begin(), expression.end(), ")") == expression.end() - 1) {
	arguments.push_back(expression[jia_keywords_.search(expression)]);
	//for (auto i : arguments) std::cout << i << std::endl;
	for (int i = 0; i < expression.size(); ++i) {
	    if (expression[i] == arguments[0] || expression[i] == "(" || expression[i] == ")") continue;
	    arguments.push_back(expression[i]);
	    //for (auto i : arguments) std::cout << i << std::endl;
	}
    } else;
    //for (auto i : arguments) std::cout << i << std::endl;
    return arguments;
}

int Jia::execute(std::vector<std::string> arguments) {
    if (arguments[0] == "+") {
	if (arguments.size() != 3){
	    std::cerr << "Number of arguments does not match Jia's \"+\"..." << std::endl;
	    return -1;
	} else {
	    DigitalNumber first(arguments[1]), second(arguments[2]);
	    std::cout << first + second << std::endl;
	}
    } else if (arguments[0] == "-") {
	if (arguments.size() != 3){
	    std::cerr << "Number of arguments does not match Jia's \"-\"..." << std::endl;
	    return -1;
	} else {
	    DigitalNumber first(arguments[1]), second(arguments[2]);
	    std::cout << first - second << std::endl;
	}
    } else if (arguments[0] == "exit") {
	exit(0);
    }
    return 0;
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
		execute(translateExpression(expression));
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
