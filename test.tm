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
* TOFF set: -2
* Compound Body
* EXPRESSION
* CALL outputb
 40:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param 1
 41:    LDC  3,1(6)	Load integer constantkkk 
 42:    RND  3,3,6	Op ? 
 43:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
 44:    TEQ  3,4,3	Op == 
 45:     ST  3,-5(1)	Push parameter 
* TOFF dec: -6
* Param end outputb
 46:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 47:    LDA  3,1(7)	Return address in ac 
 48:    JMP  7,-32(7)	CALL outputb
 49:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -2
* EXPRESSION
* CALL outnl
 50:     ST  1,-2(1)	Store fp in ghost frame for outnl
* TOFF dec: -3
* TOFF dec: -4
* Param end outnl
 51:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 52:    LDA  3,1(7)	Return address in ac 
 53:    JMP  7,-20(7)	CALL outnl
 54:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* EXPRESSION
* CALL outputb
 55:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param 1
 56:    LDC  3,100000(6)	Load integer constantkkk 
 57:    RND  3,3,6	Op ? 
* TOFF inc: -3
 58:     LD  4,-3(1)	Pop left into ac1 
 59:     ST  3,-3(1)	Push parameter 
* TOFF dec: -4
* Param end outputb
 60:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 61:    LDA  3,1(7)	Return address in ac 
 62:    JMP  7,-46(7)	CALL outputb
 63:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -2
* EXPRESSION
* CALL outputb
 64:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param 1
 65:    LDC  3,3(6)	Load integer constantkkk 
 66:    RND  3,3,6	Op ? 
 67:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
 68:    LDC  3,3(6)	Load integer constantkkk 
 69:    RND  3,3,6	Op ? 
* TOFF inc: -4
 70:     LD  4,-4(1)	Pop left into ac1 
 71:    AND  3,4,3	Op AND 
 72:    LDC  3,3(6)	Load integer constantkkk 
 73:    RND  3,3,6	Op ? 
 74:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
 75:    AND  3,4,3	Op AND 
 76:    LDC  3,3(6)	Load integer constantkkk 
 77:    RND  3,3,6	Op ? 
* TOFF inc: -4
 78:     LD  4,-4(1)	Pop left into ac1 
 79:    AND  3,4,3	Op AND 
 80:    LDC  3,3(6)	Load integer constantkkk 
 81:    RND  3,3,6	Op ? 
 82:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
 83:    AND  3,4,3	Op AND 
 84:    LDC  3,3(6)	Load integer constantkkk 
 85:    RND  3,3,6	Op ? 
* TOFF inc: -4
 86:     LD  4,-4(1)	Pop left into ac1 
 87:    AND  3,4,3	Op AND 
 88:    LDC  3,3(6)	Load integer constantkkk 
 89:    RND  3,3,6	Op ? 
 90:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
 91:    AND  3,4,3	Op AND 
 92:    LDC  3,3(6)	Load integer constantkkk 
 93:    RND  3,3,6	Op ? 
* TOFF inc: -4
 94:     LD  4,-4(1)	Pop left into ac1 
 95:    AND  3,4,3	Op AND 
 96:    LDC  3,3(6)	Load integer constantkkk 
 97:    RND  3,3,6	Op ? 
 98:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
 99:    AND  3,4,3	Op AND 
100:    LDC  3,3(6)	Load integer constantkkk 
101:    RND  3,3,6	Op ? 
* TOFF inc: -4
102:     LD  4,-4(1)	Pop left into ac1 
103:    AND  3,4,3	Op AND 
104:    LDC  3,3(6)	Load integer constantkkk 
105:    RND  3,3,6	Op ? 
106:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
107:    AND  3,4,3	Op AND 
108:    LDC  3,3(6)	Load integer constantkkk 
109:    RND  3,3,6	Op ? 
* TOFF inc: -4
110:     LD  4,-4(1)	Pop left into ac1 
111:    AND  3,4,3	Op AND 
112:    LDC  3,3(6)	Load integer constantkkk 
113:    RND  3,3,6	Op ? 
114:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
115:    AND  3,4,3	Op AND 
116:     ST  3,-5(1)	Push parameter 
* TOFF dec: -6
* Param end outputb
117:    LDA  1,-2(1)	Ghost frame becomes new active frame 
118:    LDA  3,1(7)	Return address in ac 
119:    JMP  7,-103(7)	CALL outputb
120:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -2
* EXPRESSION
* CALL outputb
121:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param 1
122:    LDC  3,3(6)	Load integer constantkkk 
123:    RND  3,3,6	Op ? 
* TOFF inc: -3
124:     LD  4,-3(1)	Pop left into ac1 
125:    LDC  3,3(6)	Load integer constantkkk 
126:    RND  3,3,6	Op ? 
127:     ST  3,-3(1)	Push left side 
* TOFF dec: -4
128:     OR  3,4,3	Op OR 
129:    LDC  3,3(6)	Load integer constantkkk 
130:    RND  3,3,6	Op ? 
* TOFF inc: -3
131:     LD  4,-3(1)	Pop left into ac1 
132:     OR  3,4,3	Op OR 
133:    LDC  3,3(6)	Load integer constantkkk 
134:    RND  3,3,6	Op ? 
135:     ST  3,-3(1)	Push left side 
* TOFF dec: -4
136:     OR  3,4,3	Op OR 
137:    LDC  3,3(6)	Load integer constantkkk 
138:    RND  3,3,6	Op ? 
* TOFF inc: -3
139:     LD  4,-3(1)	Pop left into ac1 
140:     OR  3,4,3	Op OR 
141:    LDC  3,3(6)	Load integer constantkkk 
142:    RND  3,3,6	Op ? 
143:     ST  3,-3(1)	Push left side 
* TOFF dec: -4
144:     OR  3,4,3	Op OR 
145:    LDC  3,3(6)	Load integer constantkkk 
146:    RND  3,3,6	Op ? 
* TOFF inc: -3
147:     LD  4,-3(1)	Pop left into ac1 
148:     OR  3,4,3	Op OR 
149:    LDC  3,3(6)	Load integer constantkkk 
150:    RND  3,3,6	Op ? 
151:     ST  3,-3(1)	Push left side 
* TOFF dec: -4
152:     OR  3,4,3	Op OR 
153:    LDC  3,3(6)	Load integer constantkkk 
154:    RND  3,3,6	Op ? 
* TOFF inc: -3
155:     LD  4,-3(1)	Pop left into ac1 
156:     OR  3,4,3	Op OR 
157:    LDC  3,3(6)	Load integer constantkkk 
158:    RND  3,3,6	Op ? 
159:     ST  3,-3(1)	Push left side 
* TOFF dec: -4
160:     OR  3,4,3	Op OR 
161:    LDC  3,3(6)	Load integer constantkkk 
162:    RND  3,3,6	Op ? 
* TOFF inc: -3
163:     LD  4,-3(1)	Pop left into ac1 
164:     OR  3,4,3	Op OR 
165:    LDC  3,3(6)	Load integer constantkkk 
166:    RND  3,3,6	Op ? 
167:     ST  3,-3(1)	Push left side 
* TOFF dec: -4
168:     OR  3,4,3	Op OR 
169:    LDC  3,3(6)	Load integer constantkkk 
170:    RND  3,3,6	Op ? 
* TOFF inc: -3
171:     LD  4,-3(1)	Pop left into ac1 
172:     OR  3,4,3	Op OR 
173:     ST  3,-3(1)	Push parameter 
* TOFF dec: -4
* Param end outputb
174:    LDA  1,-2(1)	Ghost frame becomes new active frame 
175:    LDA  3,1(7)	Return address in ac 
176:    JMP  7,-160(7)	CALL outputb
177:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -2
* EXPRESSION
* CALL outnl
178:     ST  1,-2(1)	Store fp in ghost frame for outnl
* TOFF dec: -3
* TOFF dec: -4
* Param end outnl
179:    LDA  1,-2(1)	Ghost frame becomes new active frame 
180:    LDA  3,1(7)	Return address in ac 
181:    JMP  7,-148(7)	CALL outnl
182:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
183:    LDC  2,0(6)	Set return value to 0 
184:     LD  3,-1(1)	Load return address 
185:     LD  1,0(1)	Adjust fp 
186:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,186(7)	Jump to init [backpatch] 
* INIT
187:    LDA  1,0(0)	set first frame at end of globals 
188:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
189:    LDA  3,1(7)	Return address in ac 
190:    JMP  7,-152(7)	Jump to main 
191:   HALT  0,0,0	DONE! 
* END INIT
