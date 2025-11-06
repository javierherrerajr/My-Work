;=================================================
; Name: Javier Herrera 
; Email: jherr116@ucr.edu
; 
; Lab: lab 4, ex 3
; Lab section: 
; TA: 
; 
;=================================================
.orig x3000     ;Start of Program

ld r1 array_address     ;empty array in r1
ld r5 sub_fill_array_3200    ;subroutine call in r5

jsrr r5     ;calls the subroutine

ld r1, array_address    ;reverts back to the start of the array address

ld r5 sub_convert_array_3400    ;subroutine call in r5

jsrr r5     ;calls the subroutine

ld r1, array_address    ;reverts back to the start of the array

ld r5 sub_print_array_3600  ;subroutine call in r5

jsrr r5     ;calls the subroutine

ld r1, array_address    ;reverts back to the start of the array

halt

;data
array_address   .fill   x4000     ;address for array
sub_fill_array_3200  .fill   x3200      ;subroutine address
sub_convert_array_3400  .fill   x3400   ;subroutine address 
sub_print_array_3600    .fill   x3600   ;subroutine address

.end    ;the program is terminated

;------------------------------------------------------------------------------------------------------------
; Subroutine: sub_fill_array_3200
; Parameter (r1): The starting address of the array. This should be unchanged at the end of the subroutine!
; Postcondition: The array has decimal values from 0-9
; Return Value (None)
;------------------------------------------------------------------------------------------------------------
.orig x3200     ;Start of subroutine

ld r2 dec_0_3200    ;hard-coded value of decimal 0
ld r3, counter_3200 ;counter for loop

array_filler_3200   ;loop for filling up the array
    str r2, r1, #0      ;storing of the array
    add r1, r1, #1      ;moves to next open space in array
    add r2, r2, #1      ;increments decimal by 1
    add r3, r3, #-1 
    brp array_filler_3200
end_array_filler_3200

ret
;3200 data
dec_0_3200   .fill   #0     ;hard-coded decimal 0
counter_3200    .fill   #10     ; loop counter

.end    ;subroutine finishes

;------------------------------------------------------------------------------------------------------------
; Subroutine: sub_convert_array_3400
; Parameter (r1): The starting address of the array. This should be unchanged at the end of the subroutine!
; Postcondition: The array has character values from 0-9
; Return Value (None)
;------------------------------------------------------------------------------------------------------------
.orig x3400

ld r2 ascii_conversion_3400     ;converter for decimal to ascii characters
ld r3 counter_3400      ;loop counter

ldr r4, r1, #0      ;holds value of r1
add r4, r4, r2      ;converts to ascii

conversion_loop
    str r4, r1, #0  ;stores new value into array
    add r4, r4, #1  ;converts to the next ascii value
    add r1, r1, #1  ;moves to the next array place
    add r3, r3, #-1 ;counts to 10 for array
    brp conversion_loop
end_conversion_loop

ret
;3400 data
counter_3400    .fill   #10     ;counter for loop
ascii_conversion_3400   .fill   #48     ;converts decimals to ascii characters

.end    ;subroutine finishes

;------------------------------------------------------------------------------------------------------------
; Subroutine: sub_print_array_3600
; Parameter (r1): The starting address of the array. This should be unchanged at the end of the subroutine!
; Postcondition: The array has character values from 0-9 that print out to the console
; Return Value (None)
;------------------------------------------------------------------------------------------------------------
.orig x3600     ;Starts the subroutine

ld r3 counter_3600  ;counter for loop

print_loop  ;prints out each character of the array
    ldr r0, r1, #0  ;gets the value of r1 and loads it into r0 for printing later
    out
    add r1, r1, #1  ;moves to the next value
    add r3, r3, #-1
    brp print_loop
end_print_loop

ret
;data
counter_3600    .fill   #10

.end    ;subroutine finishes

;remote data - holds hard-coded array
.orig x4000
array   .blkw   #10
.end
