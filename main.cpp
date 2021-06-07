#include <iostream>
#include "command.h"
// Copyright (C) 2021 Remy van Elst
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <http://www.gnu.org/licenses/>.

int main() {
    using namespace raymii;

    std::cout << "Example:" << std::endl;
    std::cout << Command::exec("echo 'Hello you absolute legends!'") << std::endl;


    std::string expectedOutput("test\000abc\n", 9); //NOLINT We want to test for nullbytes...
    CommandResult nullbyteCommand = Command::exec("/usr/bin/printf 'test\\000abc\\n'"); // NOLINT(bugprone-string-literal-with-embedded-nul)
    CommandResult fgetsNullbyteCommand = Command::execFgets("/usr/bin/printf 'test\\000abc\\n'"); // NOLINT(bugprone-string-literal-with-embedded-nul)

    std::cout << "Nullbyte example expected output: " << expectedOutput << std::endl;
    std::cout << "Output using fread:  " << nullbyteCommand << std::endl;
    std::cout << "Output using fgets: " << fgetsNullbyteCommand << std::endl;

    std::cout << "Redirect stdout to stderr" << std::endl;
    std::cout << Command::exec("/bin/bash --invalid  1>&2") << std::endl;

#ifdef _WIN32
    std::cout << "Windows example:" << std::endl;
    std::cout << Command::exec("dir * /on /p") << std::endl;
#endif

    return 0;
}
