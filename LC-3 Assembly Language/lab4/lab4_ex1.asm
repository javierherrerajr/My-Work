;=================================================
; Name: Javier Herrera 
; Email: jherr116@ucr.edu
; 
; Lab: lab 4, ex 1
; Lab section: 24
; TA: Karan Bhogal
; 
;=================================================
.orig x3000     ;Start of Program

ld r1 array_address     ;empty array in r1
ld r5 sub_fill_array_3200    ;subroutine call in r5

jsrr r5     ;calls the subroutine

ld r1, array_address    ;reverts back to the start of the array address

halt

;data
array_address   .fill   x4000     ;address for array
sub_fill_array_3200  .fill   x3200      ;subroutine address

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
dec_0_3200   .fill   #0
counter_3200    .fill   #10

.end    ;subroutine finishes

;remote data - holds hard-coded array
.orig x4000
array   .blkw   #10
.end
