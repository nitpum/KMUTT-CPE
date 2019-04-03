`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/26/2018 11:01:20 AM
// Design Name: 
// Module Name: decoder
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


module decoder(
    input [2:0] sw,
    output reg [7:0] led
    );
    always @ (sw)
        case (sw)
            3'b000 : led=8'b00000001;
            3'b001 : led=8'b00000010;
            3'b010 : led=8'b00000100;
            3'b011 : led=8'b00001000;
            3'b100 : led=8'b00010000;
            3'b101 : led=8'b00100000;
            3'b110 : led=8'b01000000;
            3'b111 : led=8'b10000000;
        endcase
endmodule
