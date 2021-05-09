* C- Compiler Spring 2021
* Author: Jacob Friedberg
* File Compiled:  test.c-
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION input
  1:     ST  3,-1(1)	Store return address 
  2:     IN  2,2,2	Grab int input 
  3:     LD  3,-1(1)	Load return address 
  4:     LD  1,0(1)	Adjust fp 
  5:    JMP  7,0(3)	Return 
* END FUNCTION input
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION output
  6:     ST  3,-1(1)	Store return address 
  7:     LD  3,-2(1)	Load parameter 
  8:    OUT  3,3,3	Output integer 
  9:     LD  3,-1(1)	Load return address 
 10:     LD  1,0(1)	Adjust fp 
 11:    JMP  7,0(3)	Return 
* END FUNCTION output
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputb
 12:     ST  3,-1(1)	Store return address 
 13:    INB  2,2,2	Grab bool input 
 14:     LD  3,-1(1)	Load return address 
 15:     LD  1,0(1)	Adjust fp 
 16:    JMP  7,0(3)	Return 
* END FUNCTION inputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputb
 17:     ST  3,-1(1)	Store return address 
 18:     LD  3,-2(1)	Load parameter 
 19:   OUTB  3,3,3	Output bool 
 20:     LD  3,-1(1)	Load return address 
 21:     LD  1,0(1)	Adjust fp 
 22:    JMP  7,0(3)	Return 
* END FUNCTION outputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputc
 23:     ST  3,-1(1)	Store return address 
 24:    INC  2,2,2	Grab char input 
 25:     LD  3,-1(1)	Load return address 
 26:     LD  1,0(1)	Adjust fp 
 27:    JMP  7,0(3)	Return 
* END FUNCTION inputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputc
 28:     ST  3,-1(1)	Store return address 
 29:     LD  3,-2(1)	Load parameter 
 30:   OUTC  3,3,3	Output char 
 31:     LD  3,-1(1)	Load return address 
 32:     LD  1,0(1)	Adjust fp 
 33:    JMP  7,0(3)	Return 
* END FUNCTION outputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outnl
 34:     ST  3,-1(1)	Store return address 
 35:  OUTNL  3,3,3	Output a newline 
 36:     LD  3,-1(1)	Load return address 
 37:     LD  1,0(1)	Adjust fp 
 38:    JMP  7,0(3)	Return 
* END FUNCTION outnl
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION dog
* TOFF set: -4
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -4
* Compound Body
* EXPRESSION
* EXPRESSION
 40:    LDC  3,444(6)	Load integer constant 
* EXPRESSION
 41:    LDC  3,9(6)	Load integer constant 
 42:     ST  3,-4(1)	Push index 
* TOFF dec: -5
 43:    LDC  3,555(6)	Load integer constant 
* TOFF inc: -4
 44:     LD  4,-4(1)	Pop index 
 45:     LD  5,-3(1)	Load address of base of array b
 46:    SUB  5,5,4	Compute offset of value 
 47:     ST  3,0(5)	Store variable b
* RETURN
 48:     LD  3,-1(1)	Load return address 
 49:     LD  1,0(1)	Adjust fp 
 50:    JMP  7,0(3)	Return 
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
 51:    LDC  2,0(6)	Set return value to 0 
 52:     LD  3,-1(1)	Load return address 
 53:     LD  1,0(1)	Adjust fp 
 54:    JMP  7,0(3)	Return 
* END FUNCTION dog
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
* TOFF set: -2
 55:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -14
 56:    LDC  3,10(6)	load size of array y
 57:     ST  3,-3(1)	save size of array y
* Compound Body
* EXPRESSION
* EXPRESSION
 58:    LDC  3,1(6)	Load Boolean constant 
 59:     ST  3,0(0)	Store variable g
* EXPRESSION
 60:    LDC  3,9(6)	Load integer constant 
 61:     ST  3,-14(1)	Push index 
* TOFF dec: -15
 62:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -14
 63:     LD  4,-14(1)	Pop index 
 64:    LDA  5,-2(0)	Load address of base of array h
 65:    SUB  5,5,4	Compute offset of value 
 66:     ST  3,0(5)	Store variable h
* EXPRESSION
* EXPRESSION
 67:    LDC  3,111(6)	Load integer constant 
 68:     ST  3,-2(1)	Store variable x
* EXPRESSION
 69:    LDC  3,9(6)	Load integer constant 
 70:     ST  3,-14(1)	Push index 
* TOFF dec: -15
 71:    LDC  3,222(6)	Load integer constant 
* TOFF inc: -14
 72:     LD  4,-14(1)	Pop index 
 73:    LDA  5,-4(1)	Load address of base of array y
 74:    SUB  5,5,4	Compute offset of value 
 75:     ST  3,0(5)	Store variable y
* EXPRESSION
* CALL output
 76:     ST  1,-14(1)	Store fp in ghost frame for output
* TOFF dec: -15
* TOFF dec: -16
* Param 1
 77:    LDC  3,333(6)	Load integer constant 
 78:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
* EXPRESSION
* CALL dog
 79:     ST  1,-17(1)	Store fp in ghost frame for dog
* TOFF dec: -18
* TOFF dec: -19
* Param 1
 80:     LD  3,-2(1)	Load variable x
 81:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param 2
 82:     LD  3,-2(1)	Load variable x
 83:     ST  3,-20(1)	Push parameter 
* TOFF dec: -21
* Param end dog
 84:    LDA  1,-17(1)	Ghost frame becomes new active frame 
 85:    LDA  3,1(7)	Return address in ac 
 86:    JMP  7,-48(7)	CALL dog
 87:    LDA  3,0(2)	Save the result in ac 
* Call end dog
* TOFF set: -17
 88:    ADD  3,4,3	Op + 
 89:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end output
 90:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 91:    LDA  3,1(7)	Return address in ac 
 92:    JMP  7,-87(7)	CALL output
 93:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -14
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
 94:    LDC  2,0(6)	Set return value to 0 
 95:     LD  3,-1(1)	Load return address 
 96:     LD  1,0(1)	Adjust fp 
 97:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,97(7)	Jump to init [backpatch] 
* INIT
 98:    LDA  1,-12(0)	set first frame at end of globals 
 99:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
100:    LDC  3,10(6)	load size of array h
101:     ST  3,-1(0)	save size of array h
* END INIT GLOBALS AND STATICS
102:    LDA  3,1(7)	Return address in ac 
103:    JMP  7,-49(7)	Jump to main 
104:   HALT  0,0,0	DONE! 
* END INIT
