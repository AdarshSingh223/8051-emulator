#include<string>

namespace beauty
{
    std::string convertToUpper(std::string& program);
    std::vector<std::string> getTokens(std::string );
} // namespace beauty

std::string convertToUpper(std::string& program) {

    for(uint_fast64_t i = 0 ; i < program.length() ; i++) {
        program[i] = toupper(program[i]);
    }

    return program;
}

std::vector<std::string> getTokens(std::string program) {
    

    uint_fast64_t len = program.length();
    for(auto i = 0 ; i < len ; i++) {
        if(program[i] == '\n') {
            program[i] = ' ';
        }
    }
    //while()

}