`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/15/2018 08:45:16 PM
// Design Name: 
// Module Name: ALU
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


module ALU(
    input [3:0] ALU_control, Ain, Bin,
    output [3:0] ACC_out,
    output V, Z, C, clk
    );
    wire [5:0] Carry;
    wire [4:0] tmp;
    reg [3:0] ALU_out;
    assign tmp = {1'b0, Ain} + {1'b0, Bin};
    assign Carry = {2'b00, Ain} + {2'b00, Bin};
    assign V = (Carry[4] ^ Carry[5])? 1: 0; // Overflow
    assign C = (ALU_control != 4)? tmp[4]: 0; // Carry out
    assign Z = (ALU_out == 0)? 1 : 0; // Is zero  
    assign ACC_out = ALU_out;
    always @ (*) begin
        case (ALU_control)
            4'b0000 : ALU_out = Bin;
            4'b0001 : ALU_out = Ain + Bin;
            4'b0010 : ALU_out = Ain - Bin;
            4'b0011 : ALU_out = Ain;
            4'b0100 : ALU_out = 0;
            4'b0101 : ALU_out = Ain & Bin;
            4'b0110 : ALU_out = Ain | Bin;
            4'b0111 : ALU_out = ~Ain;
            4'd8: ALU_out = Ain<<2;
            4'd9: ALU_out = Ain<<2;
            4'd10: ALU_out = Ain<<2;
            4'd11: ALU_out = Ain>>2;
            4'd12: ALU_out = Ain>>2;
            4'd13: ALU_out = Ain>>2;
            4'd14: ALU_out = Ain>>2;
            4'd15: ALU_out = Ain>>2; 
        endcase
    end
    
endmodule
