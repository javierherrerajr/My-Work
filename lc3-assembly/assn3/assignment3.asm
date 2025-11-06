;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Javier Herrera
; Email: jherr116@ucr.edu
; 
; Assignment name: Assignment 3
; Lab section: 
; TA: 
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=========================================================================

.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------
LD R6, Value_ptr		; R6 <-- pointer to value to be displayed as binary
LDR R1, R6, #0			; R1 <-- value to be displayed as binary 
;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------
LD R2, DEC_15
LD R3, DEC_4
LD R4, DEC_0

DO_WHILE
	ADD R1, R1, R4

	BRzp POS
	BRn END_POS
POS
	LD R0, ASCII_0
	OUT
END_POS

	BRn NEG
	BRzp END_NEG
NEG
	LD R0, ASCII_1
	OUT
END_NEG

	ADD R3, R3, #-1
	BRnp NO_SPACE

	LD R0, SPACE
	OUT
	LD R3, DEC_4
NO_SPACE

	ADD R4, R1, #0
	ADD R2, R2, #-1
	BRnp DO_WHILE

ADD R1, R1, R4
BRzp POST
BRn END_POST
POST
	LD R0, ASCII_0
	OUT
END_POST

BRn NEGA
BRzp END_NEGA
NEGA
	LD R0, ASCII_1
	OUT
END_NEGA

	LEA R0, NEWLINE
	PUTS

HALT
;---------------	
;Data
;---------------
Value_ptr	.FILL xCA01	; The address where value to be displayed is stored
DEC_15 .FILL #15
DEC_4 .FILL #4
DEC_0 .FILL #0
ASCII_0 .FILL #48
ASCII_1 .FILL #49
SPACE .FILL #32
NEWLINE .STRINGZ "\n"

.END

.ORIG xCA01					; Remote data
Value .FILL xABCD			; <----!!!NUMBER TO BE DISPLAYED AS BINARY!!! Note: label is redundant.
;---------------	
;END of PROGRAM
;---------------	
.END
