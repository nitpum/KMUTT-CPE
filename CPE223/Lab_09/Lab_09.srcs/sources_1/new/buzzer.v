`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/02/2018 01:51:48 AM
// Design Name: 
// Module Name: buzzer
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
module buzzer(
    input S, B, L, R,
    output F
    );
    wire w1, w2, w3, Bbar;
    or(w1, L, R);
    and(w2, w1, S);
    not(Bbar, B);
    and(w3, S, Bbar);
    or(F, w2, w3);
endmodule

//module buzzer(
//    input s, b, l, r,
//    output f
//    );
//    assign f = l and r;
//endmodule
