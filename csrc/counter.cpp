#include <stdio.h>
#include <stdlib.h>
#include "Vcounter.h"
#include "verilated.h"


int main(int argc, char **argv) {
	int count_out;
    // Call commandArgs first!
	Verilated::commandArgs(argc, argv);    

	// Instantiate our design
	Vcounter *tb = new Vcounter;

	// Need a clock pulse
    
    count_out = tb->out1 ;
    // Reset the counter
    tb->reset = 1; 
    tb->eval(); // Evaluate the model.
    tb->reset = 0;
    tb->eval();// Evaluate the model.
    
    // Simple loop which toggles the clock and prints the 
    // value of out1 in the RTL. 
    for (int x=0; x < 100; x++)
    {        
        tb->clock = 1;
        tb->eval();// Evaluate the model.
        tb->clock = 0;
        tb->eval();// Evaluate the model.
        printf("Output: %d, Reset: %d\n", tb->out1, tb->reset);        
    }

}

