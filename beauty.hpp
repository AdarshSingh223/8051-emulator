#include <string>
#include <regex>
#include <iostream>
#include <sstream>
#include <fstream>

std::string convertToUpper(std::string& program) {

    for(uint_fast64_t i = 0 ; i < program.length() ; i++) {
        program[i] = toupper(program[i]);
    }

    return program;
}

std::vector<std::string> tokenizeLines(std::string& convertedProgram){
	
	std::vector<std::string> tokenizedLines;
    std::string intermediate;
	std::stringstream check(convertedProgram);
	
	while(std::getline(check, intermediate, '\n'))
	{
		tokenizedLines.push_back(intermediate);
	}

    return tokenizedLines;
}

std::string removeComments(std::vector<std::string> programLines) {

    std::string properProgram;

    
    for(std::vector<std::string>::iterator i = programLines.begin() ;
        i != programLines.end() ; i++) {

            std::string str = *i;
            if(str[0] == '/' && str[1] == '/') {
                programLines.erase(i);
            } 
            properProgram = properProgram + (*i) + '\n';
    }

    while(1) {

        bool commentStart = false;
        bool commentEnd = false;

        uint_fast64_t commentStartPosition;
        uint_fast64_t commentEndPosition;

        for(uint_fast64_t i = 0 ; i < properProgram.length() ; i++) {

            if(properProgram[i] == '/' && properProgram[i+1] == '*') {
                commentStart = true;
                commentStartPosition = i;
            } else if(properProgram[i] == '*' && properProgram[i+1] == '/') {
                commentEnd = true;
                commentEndPosition = i+1;
            }

            if(commentStart && commentEnd) {
                properProgram.erase(commentStartPosition,commentEndPosition - commentStartPosition + 1);
                break;
            }
        }

        if(!commentStart && !commentEnd) {
            break;
        }
    }
    return properProgram;

}

std::vector<std::string> getTokens(std::string program) {

    std::vector<std::string> tokens;
    
    std::regex regexRules("[^\\s.,\\n;!?]+");
    auto regexBegin = std::sregex_iterator(program.begin(), program.end(), regexRules);
    auto regexEnd = std::sregex_iterator();

    for (std::sregex_iterator i = regexBegin ; i != regexEnd; ++i) {
        std::string str = (*i).str();
        tokens.push_back(str);
    }

    return tokens;
}
