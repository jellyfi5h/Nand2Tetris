// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.


@bitCheck
M=1         //init bit checker (check if bit is 0 or 1)
@sum
M=0         //init sum (total of each bit multiplications)
@R2
M=0

(ABSR0)
    @R0
    D=M
    @absR0
    M=D
    @isR0Neg
    D;JLT

    @ABSR1
    0;JMP

(isR0Neg)
    @absR0
    M=-M

(ABSR1)
    @R1
    D=M
    @absR1
    M=D
    @isR1Neg
    D;JLT

    @MULTIPLIER
    0;JMP

(isR1Neg)
    @absR1
    M=-M




(MULTIPLIER)
    @absR0
    D=M
    @absR1
    D=D-M
    @STORE
    D;JGT

    @R1
    D=M
    @multiplicand
    M=D
    @absR0
    D=M
    @multiplier
    M=D
    @R0
    D=M
    @multiplierVal
    M=D
    @LOOP
    0;JMP

(STORE)
    @R0
    D=M
    @multiplicand
    M=D
    @absR1
    D=M
    @multiplier
    M=D
    @R1
    D=M
    @multiplierVal
    M=D

//LOOP
(LOOP)
    @multiplier
    D=M
    @bitCheck
    D=D-M
    @STOP
    D;JLT // if exceed nbr of bits to the multiplier -> STOP
    
    @multiplier
    D=M
    @bitCheck
    D=D&M;

    @GRADE
    D;JNE   //check the selected bit if is on or off
    
    @ACCUMULATE
    0;JMP

(GRADE)
    @multiplicand
    D=M
    @sum
    M=D+M   //sum the shifted multiplicant by n(index of bits)

(ACCUMULATE)
    @multiplicand 
    D=M
    M=D+M   //multiplicant * 2
    @bitCheck
    D=M
    M=D+M   //bitCheck * 2
            //ex:
            //    2nd bit -> (10) = 2
            //    3rd bit -> (100) = 4
    @LOOP
    0;JMP

(STOP)
    @multiplierVal
    D=M
    @ToNegative
    D;JLT

    @ENDVALUE
    0;JMP

(ToNegative)
    @sum
    M=-M

(ENDVALUE)
    @sum
    D=M
    @R2
    M=D

(END)

    @END
    0;JMP 
