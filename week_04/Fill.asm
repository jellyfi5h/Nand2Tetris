// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

@lastState
M=0
@screenState // screen state black or white
M=0


@8192 //number of registers holding SCRENN pixels
D=A
@n
M=D

(LOOP)
    @KBD
    D=M
    @ISPRESSED
    D;JNE

    @screenState
    M=0
    @lastState
    D=M
    @CHANGESTATE
    D;JNE

    @LOOP
    0;JMP

(ISPRESSED)
    @screenState
    M=1
    @lastState
    D=M
    @CHANGESTATE
    D;JEQ

    @LOOP
    0;JMP

(CHANGESTATE) // change screen either to white or black depends on if the keyboard is pressed or not
    @screenState
    D=M
    @lastState
    M=D

    @index
    M=0
(UPDATESCREEN)
    @index
    D=M
    @n
    D=M-D
    @LOOP
    D;JEQ

    @SCREEN
    D=A
    @index
    A=M+D
    M=!M

    @index
    M=M+1

    @UPDATESCREEN
    0;JMP
