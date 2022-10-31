#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <fstream>
#include <chrono>
#include <utility>
#include <ctime>
#include <thread>
#include <vector>
#include <sstream>
#include <algorithm>

#include "fileCheck.hpp"
#include "8051Data.hpp"

namespace m8051 {
    
    using Byte = unsigned char;     //8 bits
    using Word = unsigned short;    //16 bits

    using u32 = unsigned int;       //16 bits
	using s32 = signed int;         //16 bits

    struct ROM;
    struct CPU;

    //Bit Addressable Registers
    struct ACC;
    struct B;
    struct PSW;
    struct IE;
    struct IP;
    struct TCON;
    struct SCON;

    //Ports
    struct P0;
    struct P1;
    struct P2;
    struct P3;

}

struct m8051::ROM {
    
    Byte Data[1024][4];

    //reset the entire Program Memory 
    void initialise() {

        for (u32 i = 0 ; i < 4 ; i++){

            for(u32 j = 0 ; j < 1024 ; j++) {

                Data[i][j] = 0x00;

            }

        }  

    }
        
}; 



//Accumulator
struct m8051::ACC {

    Byte ACC_7 : 1;
    Byte ACC_6 : 1;
    Byte ACC_5 : 1;
    Byte ACC_4 : 1;
    Byte ACC_3 : 1;
    Byte ACC_2 : 1;
    Byte ACC_1 : 1;
    Byte ACC_0 : 1;

};

//Register B
struct m8051::B {

    Byte B_7 : 1;
    Byte B_6 : 1;
    Byte B_5 : 1;
    Byte B_4 : 1;
    Byte B_3 : 1;
    Byte B_2 : 1;
    Byte B_1 : 1;
    Byte B_0 : 1;

};

struct m8051::PSW {

    Byte CY : 1     ;   //Carry Flag
    Byte AC : 1     ;   //Auxillary Carry Flag
    Byte F0 : 1     ;   //Flag 0
    Byte RS1 : 1    ;   //Register select 1
    Byte RS0 : 1    ;   //Register select 0
    Byte OV : 1     ;   //Overflow Flag
    Byte UD : 1     ;   //User defined bit
    Byte P : 1      ;   //Parity Flag

};

//Interrput Enable Register 
struct m8051::IE {

    Byte EA : 1;        //if EA = 0, no interrupt is acknowledged
    Byte IE_6 : 1;      //reserved for future use
    Byte IE_5 : 1;      //reserved for future use
    Byte ES : 1;        //Enables/disables serial port interrupt
    Byte ET1 : 1;       //Enables/disables timer 1 overflow interrupt
    Byte EX1 : 1;       //Enables/disables external interrupt 1
    Byte ET0 : 1;       //Enables/disables timer 0 overflow interrup
    Byte EX0 : 1;       //Enables/disables external interrupt 0

};

//Interrupt Priority Register
struct m8051::IP {

    Byte IP_7 : 1;      //Reserved for future use
    Byte IP_6 : 1;      //Reserved for future use
    Byte IP_5 : 1;      //Reserved for future use

    Byte PS : 1;        //Defines the serial port interrupt priority level
    Byte PT1 : 1;       //Defines the timer interrupt of 1 priority
    Byte PX1 : 1;       //Defines the external interrupt 1 priority level
    Byte PT0 : 1;       //Defines the timer interrupt of 0 priority
    Byte PX0 : 1;       //Defines the external interrupt 1 priority level

};

//Timer Control Register
struct m8051::TCON {

    Byte TF1 : 1;       //Timer 1 Overflow Flag
    Byte TR1 : 1;       //Timer 1 Run Control Bit
    Byte TF0 : 1;       //Timer 0 Overflow Flag
    Byte TR0 : 1;       //Timer 0 Run Control Bit
    Byte IE1 : 1;       //External Interrupt 1 Edge Flag
    Byte IT1 : 1;       //External Interrupt 1 Trigger Type Select Bit
    Byte IE0 : 1;       //External Interrupt 0 Edge Flag
    Byte IT0 : 1;       //External Interrupt 0 Trigger Type Select Bit

};

//Serial Control Register
struct m8051::SCON {

    Byte SM0 : 1;       //Serial port mode 0 
    Byte SM1 : 1;       //Serial port mode 1
    Byte SM2 : 1;       //Enable multiprocessor communication in mode 2/3
    Byte REN : 1;       //set/ clear by software to enable/disable reception
    Byte TB8 : 1;       //the 9th bit that will be transmitted in mode 2/3
    Byte RB8 : 1;       //In mode 2/3 it is the 9th bit that was received in mode 1, if SM2 =0, RB8 is the stop bit that was received in mode it is not used
    Byte TI : 1;        //Transmit interrupt flag
    Byte RI : 1;        //Receive interrupt flag

};

//Port 0
struct m8051::P0 {

    Byte P0_7 : 1;
    Byte P0_6 : 1;
    Byte P0_5 : 1;
    Byte P0_4 : 1;
    Byte P0_3 : 1;
    Byte P0_2 : 1;
    Byte P0_1 : 1;

};

//Port 1
struct m8051::P1 {

    Byte P1_7 : 1;
    Byte P1_6 : 1;
    Byte P1_5 : 1;
    Byte P1_4 : 1;
    Byte P1_3 : 1;
    Byte P1_2 : 1;
    Byte P1_1 : 1;
    Byte P1_0 : 1;

};

//Port 2
struct m8051::P2 {

    Byte P2_7 : 1;
    Byte P2_6 : 1;
    Byte P2_5 : 1;
    Byte P2_4 : 1;
    Byte P2_3 : 1;
    Byte P2_2 : 1;
    Byte P2_1 : 1;
    Byte P2_0 : 1;

};

//Port 3
struct m8051::P3 {

    Byte P3_7 : 1;
    Byte P3_6 : 1;
    Byte P3_5 : 1;
    Byte P3_4 : 1;
    Byte P3_3 : 1;
    Byte P3_2 : 1;
    Byte P3_1 : 1;
    Byte P3_0 : 1;

};
struct m8051::CPU {

        ACC accumulator;
        B b;
        PSW programStatusWord;
        IE interruptEnable;
        IP interruptPriority;
        TCON timerControl;
        SCON serialControl;

        P0 portZero;
        P1 portOne;
        P2 portTwo;
        P3 portThree;


        Byte DPH;
        Byte DPL;

        Byte TL0;
        Byte TH0;
        Byte TL1;
        Byte TH1;
        
        Byte TMOD;  //Timer mode

        Byte PCON;  //Power Control

        Byte SP;    //Stack pointer

        Word PC;    //Program Counter
        Word DPTR;  //Data Pointer

        ROM readOnlyMemory; //ROM

        void reset() {

            //Reset the Byte Addressable Registers
            SP = 0x07;
            TMOD = 0x00;
            DPH = 0x00;
            DPL = 0x00;
            PCON = 0x00;
            DPTR = 0x0000;
            
            TL0 = 0x00;
            TH0 = 0x00;
            TL1 = 0x00;
            TH1 = 0x00;

            //reset the Bit Addressable Registers
            resetAccumulator();
            resetRegisterB();
            resetProgramStatusWordRegister();
            resetInterruptEnableRegister();
            resetInterruptPriorityRegister();
            resetTimerControlRegister();
            resetSerialControlRegister();

            //set all the Ports
            setPort0();
            setPort1();
            setPort2();
            setPort3();

        }

        inline void resetAccumulator() {

            accumulator.ACC_1 = 0;
            accumulator.ACC_2 = 0;
            accumulator.ACC_3 = 0;
            accumulator.ACC_4 = 0;
            accumulator.ACC_5 = 0;
            accumulator.ACC_6 = 0;
            accumulator.ACC_7 = 0;

        }

        inline void resetRegisterB() {

            b.B_0 = 0;
            b.B_1 = 0;
            b.B_2 = 0;
            b.B_3 = 0;
            b.B_4 = 0;
            b.B_5 = 0;
            b.B_6 = 0;
            b.B_7 = 0;

        }

        inline void resetProgramStatusWordRegister() {

            programStatusWord.P = 0;
            programStatusWord.UD = 0;
            programStatusWord.OV = 0;
            programStatusWord.RS0 = 0;
            programStatusWord.RS1 = 0;
            programStatusWord.F0 = 0;
            programStatusWord.AC = 0;
            programStatusWord.CY = 0;

        }

        inline void resetInterruptEnableRegister() {
            
            interruptEnable.EX0 = 0;
            interruptEnable.ET0 = 0;
            interruptEnable.EX1 = 0;
            interruptEnable.ET1 = 0;
            interruptEnable.ES = 0;
            interruptEnable.IE_5 = 0;
            interruptEnable.IE_6 = 0;
            interruptEnable.EA = 0;

        }

        inline void resetInterruptPriorityRegister() {

            interruptPriority.PX0 = 0;
            interruptPriority.PT0 = 0;
            interruptPriority.PX1 = 0;
            interruptPriority.PT1 = 0;
            interruptPriority.PS = 0;
            interruptPriority.IP_5 = 0;
            interruptPriority.IP_6 = 0;
            interruptPriority.IP_7 = 0;

        }

        inline void resetTimerControlRegister() {

            timerControl.IT0 = 0;
            timerControl.IE0 = 0;
            timerControl.IT1 = 0;
            timerControl.IE1 = 0;
            timerControl.TR0 = 0;
            timerControl.TF0 = 0;
            timerControl.TR1 = 0;
            timerControl.TF1 = 0;

        }

        inline void resetSerialControlRegister() {

            serialControl.RI = 0;
            serialControl.TI = 0;
            serialControl.RB8 = 0;
            serialControl.TB8 = 0;
            serialControl.REN = 0;
            serialControl.SM2 = 0;
            serialControl.SM1 = 0;
            serialControl.SM0 = 0;

        }

        inline void setPort0() {

            portZero.P0_1 = 1;
            portZero.P0_2 = 1;
            portZero.P0_3 = 1;
            portZero.P0_3 = 1;
            portZero.P0_4 = 1;
            portZero.P0_5 = 1;
            portZero.P0_5 = 1;
            portZero.P0_6 = 1;
            portZero.P0_7 = 1;

        }
        
        inline void setPort1() {

            portOne.P1_0 = 1;
            portOne.P1_1 = 1;
            portOne.P1_2 = 1;
            portOne.P1_3 = 1;
            portOne.P1_4 = 1;
            portOne.P1_5 = 1;
            portOne.P1_6 = 1;
            portOne.P1_7 = 1;

        }
        
        inline void setPort2() {

            portTwo.P2_0 = 1;
            portTwo.P2_2 = 1;
            portTwo.P2_3 = 1;
            portTwo.P2_3 = 1;
            portTwo.P2_4 = 1;
            portTwo.P2_5 = 1;
            portTwo.P2_6 = 1;
            portTwo.P2_7 = 1;

        }
            
        inline void setPort3() {

            portThree.P3_1 = 1;
            portThree.P3_2 = 1;
            portThree.P3_3 = 1;
            portThree.P3_4 = 1;
            portThree.P3_5 = 1;
            portThree.P3_6 = 1;
            portThree.P3_7 = 1;

        }

        //read the program from the file
        std::string fetchProgram() {

            std::string programName = "fileName";
            std::cin >> programName;

            bool perfectionStatus = true;
            int attempts = 0;

            /*
                Try to open the file, if unsuccesful, try 10 times, then quit
            */
            while (perfectionStatus != true || attempts <= 10) {

                perfectionStatus = fileIsPerfect(programName);
                if(!perfectionStatus) {
                    std::cout << "\n\nFAILED TO OPEN THE FILE!\n";
                    std::cout << "RETRYING...";
                    attempts++;
                    generateDelay(1);
                } else { //if file is opened succesfully, make attempts > 10
                         //so it doesn't enter the loop again
                    attempts = 11;
                }
            } 

            if(!perfectionStatus) {

                std::cout << "\n\nFAILED TO OPEN THE FILE.\nPLEASE CHECK THE FILE NAME PROPERLY!";

            }
            
            /*
                Reading from file and storing it in a string
            */

            std::ifstream file(programName);
            std::string str;
            if(file) {
                std::ostringstream ss;
                ss << file.rdbuf();
                str = ss.str();
            }

            file.close();

            return str;
        }

        void generateDelay(m8051::u32 time) {

            clock_t now = clock();
            while(clock() < now + 10000);

        }

        void complation(std::string& str) {
            std::cout << "bruh";
        }

     
};

int main(int argc, char *argv[]) {

    m8051::CPU centralProcessingUnit;
    centralProcessingUnit.reset();
    centralProcessingUnit.readOnlyMemory.initialise();
    std::string program = centralProcessingUnit.fetchProgram();

    //convert the string to upper case 
    centralProcessingUnit.complation(program);


    return 0;
}

