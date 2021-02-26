#include <stdio.h>
#include <stdlib.h>
#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

// adding a tick function for the clock without vcd code.
/*
void tick(Vcounter *tb)
{
    tb->eval();
    tb->clock = 1;
    tb->eval();
    tb->clock = 0;
    tb->eval();
}
*/

void tick( int tickcount, Vcounter *tb, VerilatedVcdC* tfp)
{
    tb->eval();
    if (tfp) // dump 2ns before the tick
        tfp->dump(tickcount * 10 -2);
    tb->clock = 1;
    tb->eval();
    if (tfp) // tick every 10ns
        tfp->dump(tickcount * 10);
    tb->clock = 0;
    tb->eval();
    if(tfp) // trailing edge dump
    {
        tfp->dump(tickcount * 10 + 5);
        tfp->flush();
    }
}

int main(int argc, char **argv) {
    int count_out;
    unsigned tickcount = 0;
    // Call commandArgs first!
    Verilated::commandArgs(argc, argv);

    // Instantiate our design
    Vcounter *tb = new Vcounter;

    // Generate a trace
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    tb->trace(tfp, 99);
    tfp->open("counter_output.vcd");

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
        //tick(tb); // calling the clock tick function.
        tick(++tickcount, tb, tfp);
        printf("Output: %d, Reset: %d\n", tb->out1, tb->reset);
    }

}

