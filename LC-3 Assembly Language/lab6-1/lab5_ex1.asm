;=================================================
; Name: Javier Herrera 
; Email: jherr116@ucr.edu
; 
; Lab: lab 6, ex 1
; Lab section: 24
; TA: Karan Bhogal
; 
;=================================================
.orig x3000
; Initialize the stack. Don't worry about what that means for now.
ld r6, top_stack_addr ; DO NOT MODIFY, AND DON'T USE R6, OTHER THAN FOR BACKUP/RESTORE
ld r1, array_address ; fills r1 with array
and r5, r5, #0 ; sets r5 to 0 for later counter of characters in array for size

ld r2, sub_get_string ; loads subroutine
jsrr r2 ; subroutine call

ld r0, array_address 
puts ; prints string in array

halt

; your local data goes here

top_stack_addr .fill xFE00 ; DO NOT MODIFY THIS LINE OF CODE
array_address   .fill   x4000 ; array address that has reserved space for palindrome
sub_get_string  .fill   x3200 ; subroutine pointer for inputting a string
.end

; your subroutines go below here
;------------------------------------------------------------------------
; Subroutine: SUB_GET_STRING
; Parameter (R1): The starting address of the character array
; Postcondition: The subroutine has prompted the user to input a string,
;	terminated by the [ENTER] key (the "sentinel"), and has stored 
;	the received characters in an array of characters starting at (R1).
;	the array is NULL-terminated; the sentinel character is NOT stored.
; Return Value (R5): The number of non-sentinel chars read from the user.
;	R1 contains the starting address of the array unchanged.
;-------------------------------------------------------------------------
.orig x3200
;backup registers
add r6, r6, #-1
str r7, r6, #0
add r6, r6, #-1
str r1, r6, #0

get_string_loop ; loops until ENTER is inputted
    getc
    out
    add r3, r0, #-10
    brz end_get_string_loop ; base case for null-terminated and doesn't store null-terminated
    str r0, r1, #0
    add r1, r1, #1
    add r5, r5, #1
    brnzp get_string_loop ; keeps looping
end_get_string_loop

;restore registers
ldr r1, r6, #0
add r6, r6, #1
ldr r7, r6, #0
add r6, r6, #1

ret
;data

.end

;remote array
.orig x4000
array   .blkw   #30     ;saves space for words that realistically shouldn't be bigger than this
.end