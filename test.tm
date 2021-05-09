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
* FUNCTION main
* TOFF set: -2
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -10
 40:    LDC  3,7(6)	load size of array x
 41:     ST  3,-2(1)	save size of array x
* Compound Body
* EXPRESSION
 42:    LDC  3,3(6)	Load integer constant 
 43:     ST  3,-10(1)	Push index 
* TOFF dec: -11
 44:    LDC  3,1023(6)	Load integer constant 
* TOFF inc: -10
 45:     LD  4,-10(1)	Pop index 
 46:    LDA  5,-3(1)	Load address of base of array x
 47:    SUB  5,5,4	Compute offset of value 
 48:     ST  3,0(5)	Store variable x
* EXPRESSION
* CALL output
 49:     ST  1,-10(1)	Store fp in ghost frame for output
* TOFF dec: -11
* TOFF dec: -12
* Param 1
* EXPRESSION
 50:    LDA  3,-3(1)	Load address of base of array x
 51:     ST  3,-12(1)	Push left side 
* TOFF dec: -13
 52:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -12
 53:     LD  4,-12(1)	Pop left into ac1 
 54:    SUB  3,4,3	compute location from index 
 55:     LD  3,0(3)	Load array element 
 56:    LDA  5,-3(1)	Load address of base of array x
 57:    SUB  5,5,3	Compute offset of value 
 58:     LD  3,0(5)	Load lhs variable of x
 59:    LDA  3,1(3)	increment value of [
 60:     ST  3,0(5)	Store variable x
 61:     ST  3,-12(1)	Push parameter 
* TOFF dec: -13
* Param end output
 62:    LDA  1,-10(1)	Ghost frame becomes new active frame 
 63:    LDA  3,1(7)	Return address in ac 
 64:    JMP  7,-59(7)	CALL output
 65:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -10
* EXPRESSION
* CALL outnl
 66:     ST  1,-10(1)	Store fp in ghost frame for outnl
* TOFF dec: -11
* TOFF dec: -12
* Param end outnl
 67:    LDA  1,-10(1)	Ghost frame becomes new active frame 
 68:    LDA  3,1(7)	Return address in ac 
 69:    JMP  7,-36(7)	CALL outnl
 70:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -10
* EXPRESSION
* CALL output
 71:     ST  1,-10(1)	Store fp in ghost frame for output
* TOFF dec: -11
* TOFF dec: -12
* Param 1
 72:    LDA  3,-3(1)	Load address of base of array x
 73:     ST  3,-12(1)	Push left side 
* TOFF dec: -13
 74:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -12
 75:     LD  4,-12(1)	Pop left into ac1 
 76:    SUB  3,4,3	compute location from index 
 77:     LD  3,0(3)	Load array element 
 78:     ST  3,-12(1)	Push parameter 
* TOFF dec: -13
* Param end output
 79:    LDA  1,-10(1)	Ghost frame becomes new active frame 
 80:    LDA  3,1(7)	Return address in ac 
 81:    JMP  7,-76(7)	CALL output
 82:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -10
* EXPRESSION
* CALL outnl
 83:     ST  1,-10(1)	Store fp in ghost frame for outnl
* TOFF dec: -11
* TOFF dec: -12
* Param end outnl
 84:    LDA  1,-10(1)	Ghost frame becomes new active frame 
 85:    LDA  3,1(7)	Return address in ac 
 86:    JMP  7,-53(7)	CALL outnl
 87:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -10
* EXPRESSION
* CALL output
 88:     ST  1,-10(1)	Store fp in ghost frame for output
* TOFF dec: -11
* TOFF dec: -12
* Param 1
* EXPRESSION
 89:    LDA  3,-3(1)	Load address of base of array x
 90:     ST  3,-12(1)	Push left side 
* TOFF dec: -13
 91:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -12
 92:     LD  4,-12(1)	Pop left into ac1 
 93:    SUB  3,4,3	compute location from index 
 94:     LD  3,0(3)	Load array element 
 95:    LDA  5,-3(1)	Load address of base of array x
 96:    SUB  5,5,3	Compute offset of value 
 97:     LD  3,0(5)	Load lhs variable of x
 98:    LDA  3,-1(3)	decrement value of [
 99:     ST  3,0(5)	Store variable x
100:     ST  3,-12(1)	Push parameter 
* TOFF dec: -13
* Param end output
101:    LDA  1,-10(1)	Ghost frame becomes new active frame 
102:    LDA  3,1(7)	Return address in ac 
103:    JMP  7,-98(7)	CALL output
104:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -10
* EXPRESSION
* CALL outnl
105:     ST  1,-10(1)	Store fp in ghost frame for outnl
* TOFF dec: -11
* TOFF dec: -12
* Param end outnl
106:    LDA  1,-10(1)	Ghost frame becomes new active frame 
107:    LDA  3,1(7)	Return address in ac 
108:    JMP  7,-75(7)	CALL outnl
109:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -10
* EXPRESSION
* CALL output
110:     ST  1,-10(1)	Store fp in ghost frame for output
* TOFF dec: -11
* TOFF dec: -12
* Param 1
111:    LDA  3,-3(1)	Load address of base of array x
112:     ST  3,-12(1)	Push left side 
* TOFF dec: -13
113:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -12
114:     LD  4,-12(1)	Pop left into ac1 
115:    SUB  3,4,3	compute location from index 
116:     LD  3,0(3)	Load array element 
117:     ST  3,-12(1)	Push parameter 
* TOFF dec: -13
* Param end output
118:    LDA  1,-10(1)	Ghost frame becomes new active frame 
119:    LDA  3,1(7)	Return address in ac 
120:    JMP  7,-115(7)	CALL output
121:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -10
* EXPRESSION
* CALL outnl
122:     ST  1,-10(1)	Store fp in ghost frame for outnl
* TOFF dec: -11
* TOFF dec: -12
* Param end outnl
123:    LDA  1,-10(1)	Ghost frame becomes new active frame 
124:    LDA  3,1(7)	Return address in ac 
125:    JMP  7,-92(7)	CALL outnl
126:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -10
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
127:    LDC  2,0(6)	Set return value to 0 
128:     LD  3,-1(1)	Load return address 
129:     LD  1,0(1)	Adjust fp 
130:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,130(7)	Jump to init [backpatch] 
* INIT
131:    LDA  1,0(0)	set first frame at end of globals 
132:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
133:    LDA  3,1(7)	Return address in ac 
134:    JMP  7,-96(7)	Jump to main 
135:   HALT  0,0,0	DONE! 
* END INIT
