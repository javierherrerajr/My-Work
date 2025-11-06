;=================================================
; Name: Javier Herrera
; Email: jherr116@ucr.edu
; 
; Lab: lab 3, ex 4
; Lab section: 
; TA: 
; 
;=================================================
.orig x3000

ld r5, array_1

lea r0, prompt
puts

ld r1, checker
ld r4, counter

do_while_loop
    getc
    out
    str r0, r5, #0
    add r5, r5, #1
    add r4, r4, #1
    add r0, r0, r1
    brnp do_while_loop
end_do_while_loop

add r4, r4, #-1
ld r5, array_1
ld r0, newline
out
ldr r0, r5, #0

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

array_1     .fill   x4000
checker     .fill   #-48
counter     .fill   #0
prompt      .stringz    "Enter exactly 10 characters \n"
newline     .fill   x0a

.end