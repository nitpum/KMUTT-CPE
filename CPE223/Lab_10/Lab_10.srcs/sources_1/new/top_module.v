`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/08/2018 11:20:12 PM
// Design Name: 
// Module Name: top_module
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


module top_module(
    input clk, clear,
    output [6:0] seg
    );
    wire clk_2;
    wire [3:0] led;
    divide(clk, clk_2);
    counter(clk_2, clear, led);
    bcdto7seg(led, seg);
endmodule
