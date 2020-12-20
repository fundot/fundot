/**
 * MIT License

 * Copyright (c) 2020 Jiacheng Huang

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <fstream>

#include "fundot-eval.h"
#include "fundot-io.h"

using namespace fundot;

int main(int argc, char* argv[])
{
    if (argc == 1) {
        FunSet global;
        Evaluator eval(global);
        std::cout << ">>> ";
        for(Object to_eval; std::cin >> to_eval; std::cout << ">>> ") {
            std::cout << eval(to_eval) << "\n";
        }
        std::cout << "\n";
        return 0;
    }
    if (argc == 2) {
        std::fstream file(argv[1], std::ios_base::in | std::ios_base::app);
        if (file.is_open()) {
            file.seekg(-1, std::ios_base::end);
            char last_char;
            file >> last_char;
            if (std::isspace(last_char) == false) {
                file << "\n";
            }
            file.clear();
            file.seekg(0);
            FunSet global;
            Evaluator eval(global);
            for (Object to_eval; file >> to_eval; eval(to_eval)) {}
        }
        return 0;
    }
    return 0;
}
