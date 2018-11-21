`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/08/2018 11:10:14 PM
// Design Name: 
// Module Name: counter
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


module counter(
    input clk_in,
    input reset,
    output reg [5:0] led
    );
    reg [3:0] decimal;
    reg [4:0] unit;
    initial led = 0;
    always @ (posedge clk_in or negedge reset)
            if (led >= 60 || reset == 0) led <= 0;
            else led <= led + 1;
//    always @ (posedge clk_in or negedge reset)
//        if (reset == 0)
//            unit <= 0;
//        else if (unit > 9)
//            begin
//                unit <= 0;
//                decimal <= (decimal < 5)? decimal + 1: 0;
//            end
//        else unit <= unit + 1;
endmodule
