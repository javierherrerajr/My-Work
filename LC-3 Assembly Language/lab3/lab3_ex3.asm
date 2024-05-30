;=================================================
; Name: Javier Herrera
; Email: jherr116@ucr.edu
; 
; Lab: lab 3, ex 3
; Lab section: 24
; TA: Karan Bhogal
; 
;=================================================
.orig x3000

lea r5, array_1

lea r0, prompt
puts

ld r4, counter_10

do_while_loop
    getc
    str r0, r5, #0
    add r5, r5, #1
    add r4, r4, #-1
    brp do_while_loop
end_do_while_loop

lea r5, array_1
ldr r0, r5, #0
add r4, r4, #10

second_do_while_loop
    out
    ld r0, newline
    out
    add r5, r5, #1
    ldr r0, r5, #0
    add r4, r4, #-1
    brp second_do_while_loop
end_second_do_while_loop

halt

;===========
;data
;===========

array_1     .blkw   #10
prompt      .stringz    "Enter exactly 10 characters \n"
counter_10  .fill   #10
newline     .fill   x0a

.end