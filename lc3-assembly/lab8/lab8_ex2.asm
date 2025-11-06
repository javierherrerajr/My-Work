;=================================================
; Name: Javier Herrera Jr
; Email: jherr116@ucr.edu
; 
; Lab: lab 8, ex 2
; Lab section: 
; TA: 
; 
;=================================================

.orig x3000

LD R6, top_stack_addr

GETC
OUT

ADD R1, R0, #0 ; parameter for subroutine

AND R0, R0, #0
LD R0, newline
OUT
; Test harness
;-------------------------------------------------
LD R5, sub_parity_check_3600
JSRR R5

LEA R0, first_sentence
PUTS

AND R0, R0, #0
ADD R0, R0, R1
OUT

AND R0, R0, #0
LEA R0, second_sentence
PUTS

AND R0, R0, #0
AND R4, R4, #0
LD R4, ascii_conversion
ADD R0, R0, R3
ADD R0, R0, R4
OUT 

AND R0, R0, #0
LD R0, newline
OUT

HALT

; Test harness local data
;-------------------------------------------------
top_stack_addr .fill xFE00
sub_parity_check_3600 .fill x3600
first_sentence .stringz "After conducting the parity check, the number of 1's in the character '"
second_sentence .stringz "' came out to: "
newline .fill x0A
ascii_conversion .fill #48

.end

;=================================================
; Subroutine: PARITY_CHECK_3600
; Parameter: R1 - holds the character inputted from the user (Should not be changed or altered)
; Postcondition: Should be able to count the number of binary 1's in a single character and store it in a return value register
; Return Value (R3): The number of binary 1's in a single character
;=================================================

.orig x3600

; Backup registers
ADD R6, R6, #-1
STR R7, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0
; Code
AND R3, R3, #0 ; counter for binary 1's
ADD R2, R1, #0 ; checker for binary
ADD R4, R4, #15 ; counter for 16 bit binary

BINARY_ONE_COUNTER
    ADD R2, R2, #0
    BRzp BINARY_ZERO
    
    ADD R3, R3, #1
    ADD R2, R2, R2
    ADD R4, R4, #-1
    BRzp BINARY_ONE_COUNTER
    BRn RESTORE_REGISTERS
    
BINARY_ZERO
    ADD R2, R2, R2
    ADD R4, R4, #-1
    BRp BINARY_ONE_COUNTER
    
RESTORE_REGISTERS
; Restore registers
LDR R1, R6, #0
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1

RET

.end