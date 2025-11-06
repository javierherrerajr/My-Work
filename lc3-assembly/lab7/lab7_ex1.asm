;=================================================
; Name: Javier Herrera 
; Email: jherr116@ucr.edu
; 
; Lab: lab 7, ex 1
; Lab section: 
; TA: 
; 
;=================================================
.orig x3000
; Initialize the stack. Don't worry about what that means for now.
ld r6, top_stack_addr ; DO NOT MODIFY, AND DON'T USE R6, OTHER THAN FOR BACKUP/RESTORE
ld r1, array_address ; fills r1 with array
and r5, r5, #0 ; sets r5 to 0 for later counter of characters in array for size

ld r2, sub_get_string ; loads subroutine to be called
jsrr r2 ; subroutine call

ld r0, array_address 
puts ; prints string in array

ld r2, sub_is_palindrome ; loads subroutine to be called
jsrr r2 ; subroutine call

and r0, r0, #0
lea r0, sentence_starter
puts ; prints the beginning of the statement

add r4, r4, #0
brz not_palindrome ; checks if r4 is 1 or 0

palindrome
    lea r0, is_palindrome
    puts
    brnzp done

not_palindrome
    lea r0, is_not_palindrome
    puts

done

halt

; your local data goes here

top_stack_addr .fill xFE00 ; DO NOT MODIFY THIS LINE OF CODE
array_address   .fill   x4000 ; array address that has reserved space for palindrome
sub_get_string  .fill   x3200 ; subroutine pointer for inputting a string
sub_is_palindrome   .fill   x3400 ; subroutine pointer for palindrome checker
sentence_starter   .stringz    ". The string "
is_palindrome   .stringz    " IS a palindrome\n"
is_not_palindrome   .stringz    "IS NOT a palindrome\n"
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

;-------------------------------------------------------------------------
; Subroutine: SUB_IS_PALINDROME
; Parameter (R1): The starting address of a null-terminated string
; Parameter (R5): The number of characters in the array.
; Postcondition: The subroutine has determined whether the string at (R1)
;		 is a palindrome or not, and returned a flag to that effect.
; Return Value: R4 {1 if the string is a palindrome, 0 otherwise}
;-------------------------------------------------------------------------
.orig x3400
;backup registers
add r6, r6, #-1
str r7, r6, #0
add r6, r6, #-1
str r1, r6, #0
add r6, r6, #-1
str r5, r6, #0

ld r0, sub_to_upper
jsrr r0 ; changes the whole array to uppercase before checking for palindrome

; start of array in register 1

and r0, r0, #0
add r0, r1, r5 
add r0, r0, #-1 ; end of array

and r2, r2, #0
and r3, r3, #0 ; empties registers from sub_to_upper call

is_palindrome_check
    ldr r2, r1, #0
    ldr r3, r0, #0
    not r3, r3
    add r3, r3, #1
    add r4, r2, r3 ; if r0=0, the characters are the same
    brnp palindrome_fail
    add r1, r1, #1 ; shifts up to the next character
    add r0, r0, #-1 ; shifts down to the next character
    add r5, r5, #-1 ; counter for whole string
    brp is_palindrome_check

palindrome_success
    and r4, r4, #0
    add r4, r4, #1 ; sets r4=1 since it's a palindrome
    brnzp finished
    
palindrome_fail
    and r4, r4, #0 ; sets r4=0 sinc it's not a palindrome
    
finished
;restore registers
ldr r5, r6, #0
add r6, r6, #1
ldr r1, r6, #0
add r6, r6, #1
ldr r7, r6, #0

ret
;data
sub_to_upper    .fill   x3600 ; conversion to uppercase subroutine
.end

;-------------------------------------------------------------------------
; Subroutine: SUB_TO_UPPER
; Parameter (R1): Starting address of a null-terminated string
; Postcondition: The subroutine has converted the string to upper-case
;     in-place i.e. the upper-case string has replaced the original string
; No return value, no output, but R1 still contains the array address, unchanged
;-------------------------------------------------------------------------
.orig x3600
;backup registers
add r6, r6, #-1
str r7, r6, #0
add r6, r6, #-1
str r1, r6, #0
add r6, r6, #-1
str r5, r6, #0

and r2, r2, #0 
and r3, r3, #0

ld r3, lower_conversion

lower_to_upper
    ldr r0, r1, #0 ; gets value of character in array
    and r2, r0, r3 ; converts lower to upper using bit masking to clear bit 5
    str r2, r1, #0 ; stores the converted letter into the array
    add r1, r1, #1 ; traverses the array
    add r5, r5, #-1 ; counter
    brp lower_to_upper
    
restore_registers
;restore registers
ldr r5, r6, #0
add r6, r6, #1
ldr r1, r6, #0
add r6, r6, #1
ldr r7, r6, #0
add r6, r6, #1

ret
;data
lower_conversion    .fill   xDF
.end

;remote array
.orig x4000
array   .blkw   #30     ;saves space for words that realistically shouldn't be bigger than this
.end