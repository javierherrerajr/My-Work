;=================================================
; Name: Javier Herrera
; Email: jherr116@ucr.edu
; 
; Lab: lab 2. ex 1
; Lab section: 24  
; TA: Karan Bhogal
; 
;=================================================
.ORIG x3000

LD R3, DEC_65
LD R4, HEX_41

HALT

;DATA

DEC_65  .FILL   #65
HEX_41  .FILL   x41

.END