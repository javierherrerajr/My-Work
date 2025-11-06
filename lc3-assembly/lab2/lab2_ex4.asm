;=================================================
; Name: Javier Herrera
; Email: jherr116@ucr.edu
; 
; Lab: lab 2. ex 4
; Lab section: 
; TA: 
; 
;=================================================
.ORIG x3000

LD R0, HEX_61
LD R1, HEX_1A

DO_WHILE 
    Trap x21
    ADD R0, R0, x1
    ADD R1, R1, #-1
    BRp DO_WHILE
END_DO_WHILE

HALT

;DATA

HEX_61      .FILL   x61
HEX_1A      .FILL   x1A

.END