/**
@file   hw5.cpp

@author Danny Brown (dmb0057)
@version 03-16-2018 22:35

@section DESCRIPTION

The program first allows players to create their trivia questions and answers.
Multiple questions are organized and managed using a linked data structure.
Then, the program asks a question to the player, input the player’s answer,
and checks if the player’s answer matches the actual answer.
If so, the player is awarded points for that question.If the player enters the
wrong answer, the program displays the correct answer. When all questions have
been asked, the program displays the total points that the player has won.

Limited outside resources were used and are documented where relevant as line
comments.

To compile, you will need to use g++ in a Linux terminal with C++11.
i.e. "g++ -o hw4 hw4.cpp -std=c++0x" or "g++ -o hw4 hw4.cpp -std=c++11".
note: I used the former to compile my source code and it worked as desired.

*/

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

static const int PAGE_TABLE_SIZE = 256;
static const int NUM_TLB_ENTRIES = 16;
static const int PAGE_SIZE = 256;
static const int FRAME_SIZE = 256;
static const int NUM_FRAMES = 256;
static const int PHYSICAL_MEMORY_SIZE = 256;

void system(void) {
  std::cout << "Welcome to Danny's VM Simulator Version 1.0\n" << '\n';
}
int read(/* arguments */) { /* code */
}
