;=================================================
; Name: Javier Herrera 
; Email: jherr116@ucr.edu
; 
; Lab: lab 8, ex 1
; Lab section: 24
; TA: Karan Bhogal
; 
;=================================================

.orig x3000

LD R6, top_stack_addr ; stack for backing up and restoring registers

; Test harness
;-------------------------------------------------
LD R5, LOAD_FILL_VALUE_3200
JSRR R5 ; jumps to first subroutine and gets input from user

ADD R4, R4, #1 ; adds 1 to the final value gathered from input in R4

LD R5, OUTPUT_AS_DECIMAL_3400
JSRR R5 ; jumps to second subroutine and prints out the result using isolating digits algorithm

HALT

; Test harness local data
;-------------------------------------------------
top_stack_addr .fill xFE00
LOAD_FILL_VALUE_3200 .fill x3200
OUTPUT_AS_DECIMAL_3400 .fill x3400

.end

;=================================================
; Subroutine: LOAD_FILL_VALUE_3200
; Parameter: none
; Postcondition: supposed to load in a hard coded value into R4
; Return Value: R4 hard coded value
;=================================================

.orig x3200

; Backup registers
ADD R6, R6, #-1
STR R7, R6, #0

; Code
LD R4, HARD_CODED_VALUE

AND R1, R1, #0
ADD R1, R1, #1 ; sets condition for positive is true

NEGATIVE_CHECK
    ADD R4, R4, #0
    BRn NEGATIVE_TRUE
    BR FINAL
    
NEGATIVE_TRUE
    AND R1, R1, #0 ; makes condition for negative true
    
FINAL
; Restore registers
LDR R7, R6, #0
ADD R6, R6, #1

RET
; Data
HARD_CODED_VALUE .fill #105
.end

;=================================================
; Subroutine: OUTPUT_AS_DECIMAL_3400
; Parameter: R4 - holds the value needed to output
; Postcondition: outputs value in R4 with basic arithmatic algorithm of subracting the place it's at
; Return Value: none - only outputs but doesn't change anything
;=================================================

.orig x3400

; Backup registers
ADD R6, R6, #-1
STR R7, R6, #0
ADD R6, R6, #-1
STR R4, R6, #0
; Code
AND R2, R2, #0 ; counter for printing place values
AND R7, R7, #0 ; keeps track of leading 0

NEGATIVE_VALUE
    ADD R1, R1, #0
    BRz NEGATIVE_SIGN_PRINT
    
TEN_THOUSAND_CHECK
    LD R5, TEN_THOUSAND
    ADD R4, R4, R5
    BRn TEN_THOUSAND_PRINT
    ADD R7, R7, #1
    ADD R2, R2, #1
    BR TEN_THOUSAND_CHECK
    
LEADING_ZERO_TEN_THOUSAND
    ADD R7, R7, #0
    BRz THOUSAND_CHECK
    AND R0, R0, #0
    LD R0, ASCII_CONVERSION
    OUT
    BR THOUSAND_CHECK
    
TEN_THOUSAND_PRINT
    LD R5, NEGATIVE_TEN_THOUSAND
    ADD R4, R4, R5
    ADD R2, R2 #0
    BRz LEADING_ZERO_TEN_THOUSAND
    LD R5, ASCII_CONVERSION
    AND R0, R0, #0
    ADD R0, R2, #0
    ADD R0, R0, R5
    OUT
    AND R2, R2, #0
    
THOUSAND_CHECK
    LD R5, THOUSAND
    ADD R4, R4, R5
    BRn THOUSAND_PRINT
    ADD R2, R2, #1
    ADD R7, R7, #1
    BR THOUSAND_CHECK
    
LEADING_ZERO_THOUSAND
    ADD R7, R7, #0
    BRz HUNDRED_CHECK
    AND R0, R0, #0
    LD R0, ASCII_CONVERSION
    OUT
    BR HUNDRED_CHECK
    
THOUSAND_PRINT
    LD R5, NEGATIVE_THOUSAND
    ADD R4, R4, R5
    ADD R2, R2 #0
    BRz LEADING_ZERO_THOUSAND
    LD R5, ASCII_CONVERSION
    AND R0, R0, #0
    ADD R0, R2, #0
    ADD R0, R0, R5
    OUT
    AND R2, R2, #0
    
HUNDRED_CHECK
    LD R5, HUNDRED
    ADD R4, R4, R5
    BRn HUNDRED_PRINT
    ADD R2, R2, #1
    ADD R7, R7, #1
    BR HUNDRED_CHECK
    
LEADING_ZERO_HUNDRED
    ADD R7, R7, #0
    BRz TEN_CHECK
    AND R0, R0, #0
    LD R0, ASCII_CONVERSION
    OUT
    BR TEN_CHECK
    
HUNDRED_PRINT
    LD R5, NEGATIVE_HUNDRED
    ADD R4, R4, R5
    ADD R2, R2 #0
    BRz LEADING_ZERO_HUNDRED
    LD R5, ASCII_CONVERSION
    AND R0, R0, #0
    ADD R0, R2, #0
    ADD R0, R0, R5
    OUT
    AND R2, R2, #0
    
TEN_CHECK
    ADD R4, R4, #-10
    BRn TEN_PRINT
    ADD R2, R2, #1
    ADD R7, R7, #1
    BR TEN_CHECK
    
LEADING_ZERO_TEN
    ADD R7, R7, #0
    BRz ONE_CHECK
    AND R0, R0, #0
    LD R0, ASCII_CONVERSION
    OUT
    BR ONE_CHECK
    
TEN_PRINT
    ADD R4, R4, #10
    ADD R2, R2 #0
    BRz LEADING_ZERO_TEN
    LD R5, ASCII_CONVERSION
    AND R0, R0, #0
    ADD R0, R2, #0
    ADD R0, R0, R5
    OUT
    AND R2, R2, #0
    
ONE_CHECK
    ADD R4, R4, #-1
    BRn ONE_PRINT
    ADD R2, R2, #1
    ADD R7, R7, #1
    BR ONE_CHECK
    
LEADING_ZERO_ONE
    ADD R7, R7, #0
    BRz TERMINATE
    AND R0, R0, #0
    LD R0, ASCII_CONVERSION
    OUT
    BR TERMINATE
    
ONE_PRINT
    ADD R4, R4, #1
    ADD R2, R2 #0
    BRz LEADING_ZERO_ONE
    LD R5, ASCII_CONVERSION
    AND R0, R0, #0
    ADD R0, R2, #0
    ADD R0, R0, R5
    OUT
    AND R2, R2, #0
    BR TERMINATE
    
NEGATIVE_SIGN_PRINT
    LD R0, NEG_SIGN
    OUT
    NOT R4, R4
    ADD R4, R4, #1
    BR TEN_THOUSAND_CHECK
    
TERMINATE
; Restore registers
LDR R4, R6, #0
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1

RET
; Data 
TEN_THOUSAND .fill #-10000
NEGATIVE_TEN_THOUSAND .fill #10000
THOUSAND .fill #-1000
NEGATIVE_THOUSAND .fill #1000
HUNDRED .fill #-100
NEGATIVE_HUNDRED .fill #100
NEG_SIGN .fill x2D
ASCII_CONVERSION .fill #48

.end