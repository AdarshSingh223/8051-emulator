#pragma once

#include<string>
#include<vector>

#include "beauty.hpp"

#ifndef _8051Data_HPP_  
    #define _8051Data_HPP_

//the following function will compare the components of the string to the given arrays
//if no match is found, error is present
void checkSyntax(std::string& program) {

    //A vector containing all the instructions of 8051
    std::vector<std::string> instructions = {"ACALL","ADD","ADDC","AJMP","ANL","CJNE","CLR","CPL","DA A","DEC",
                                             "DIV","DJNZ","END""INC","JB","JBC","JC","JMP","JNB","JNC","JNZ","JZ",
                                             "LCALL","LJMP","MOV","MOVC","MOVX","MUL","NOP","ORG","ORL","POP","PUSH",
                                             "RET","RETI","RL","RLC","RR","RRC","SETB","SJMP","SUBB","SWAP","XCH",
                                             "XCHD","XRL"};

    /*
        Some registers are bit addressable, this implies to the fact that,
        their bit addressability can be used in the program, it is a part 
        of an actual and correct program and has to recognized correctly
    */
    std::vector<std::string> registers = {"A","ACC.1","ACC.2","ACC.3","ACC.4","ACC.5","ACC.6","ACC.7","B","B.0","B.1",
                                          "B.2","B.3","B.4","B.5","B.6","B.7","DPL","DPH","IE","IE.0","IE.1","IE.2",
                                          "IE.3","IE.4","IE.5","IE.6","IE.7","IP","IP.0","IP.1","IP.2","IP.2","IP.3",
                                          "IP.4","IP.5","IP.6","IP.7","P0","P0.0","P0.1","P0.2","P0.3","P0.4","P0.5",
                                          "P0.6","P0.7","P1","P1.0","P1.1","P1.2","P1.3","P1.4","P1.5","P1.6","P1.7",
                                          "P2","P2.0","P2.1","P2.2","P2.3","P2.4","P2.5","P2.6","P2.7","P3","P3.0","P3.1",
                                          "P3.2","P3.3","P3.4","P3.5","P3.6","P3.7","PCON","PSW","PSW.0","PSW.1","PSW.2",
                                          "PSW.3","PSW.4","PSW.5","PSW.6","PSW.7","SCON","SCON.0","SCON.1","SCON.2",
                                          "SCON.3","SCON.4","SCON.5","SCON.6","SCON.7","SBUF","SP","TMOD","TCON","TCON.0",
                                          "TCON.1","TCON.2","TCON.3","TCON.4","TCON.5","TCON.6","TCON.7","TL0","TH0"};

    std::string convertedProgram;
    std::vector<std::string> tokens;

    convertedProgram = beauty::convertToUpper(program);
    tokens = beauty::getTokens(convertedProgram);

    std::string temp;
    int j = 0;
    for(uint_fast64_t i = 0 ; i < program.length() ; i++) {
        if(program[i] != ' ' )
        temp[j] = program[i];
    }
                                        
}

#endif

