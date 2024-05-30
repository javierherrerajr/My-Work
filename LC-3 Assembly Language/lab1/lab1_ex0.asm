;=================================================
; Name: Javier Herrera Jr  
; Email: jherr116@ucr.edu
; 
; Lab: lab 1, ex 0
; Lab section: 24
; TA: Karan Bhogal
; 
;=================================================
.ORIG x3000

    LEA R0, MSG_TO_PRINT
    PUTS
    
    HALT
    
    MSG_TO_PRINT    .STRINGZ    "Hello world!!!\n"
    
    
.END