/*
* Title: 8 bit counter.
* Active high (synchonous) reset  
* When the counter is not in reset, the count will be increased.
* Out1 is assigned to the 8th bit of the counter.
*/
module counter(
    clock,
    reset,
    out1
);

input clock;
input reset;
output out1;

reg [7:0] count;

always@(posedge clock)
    begin       
        if (reset)
            begin
                count <= 8'b0;
            end
        else
            begin
                count <= count + 1'b1;
            end
    end

assign out1 = count[2];

endmodule