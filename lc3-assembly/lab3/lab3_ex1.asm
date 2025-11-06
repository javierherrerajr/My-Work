;=================================================
; Name: Javier Herrera
; Email: jherr116@ucr.edu
; 
; Lab: lab 2. ex 1
; Lab section:   
; TA: 
; 
;=================================================
.ORIG x3000

LD R5, DATA_PTR

LDR R3, R5, #0
LDR R4, R5, #1

ADD R3, R3, #1
ADD R4, R4, #1

STR R3, R5, #0
STR R4, R5, #1

HALT

;DATA

DATA_PTR    .FILL   x4000

.END

;Remote Data
.ORIG x4000
NEW_DEC_65  .FILL   #65
NEW_HEX_41  .FILL   x41
.END