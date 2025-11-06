; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Javier Herrera
; Email: jherr116@ucr.edu
; 
; Assignment name: Assignment 5
; Lab section: 
; TA: 
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
; PUT ALL YOUR CODE AFTER THE main LABEL
;=================================================================================

;---------------------------------------------------------------------------------
;  Initialize program by setting stack pointer and calling main subroutine
;---------------------------------------------------------------------------------
.ORIG x3000

; initialize the stack
ld r6, stack_addr

; call main subroutine
lea r5, main
jsrr r5

;---------------------------------------------------------------------------------
; Main Subroutine
;---------------------------------------------------------------------------------
main
; get a string from the user
; * put your code here

lea r1, user_prompt
lea r2, user_string

ld r5, get_user_string_addr ; second subroutine
jsrr r5

; find size of input string
; * put your code here

and r1, r1, #0
lea r1, user_string

ld r5, strlen_addr
jsrr r5

; call palindrome method
; * put your code here

add r2, r2, #-1
and r4, r4, #0
add r4, r3, #0

ld r5, palindrome_addr
jsrr r5

; determine of stirng is a palindrome
; * put your code here

lea r0, result_string
puts

add r4, r4, #0
brp finish_sentence

; decide whether or not to print "not"
; * put your code here

lea r0, not_string
puts

; print the result to the screen
; * put your code here

finish_sentence
    lea r0, final_string
    puts

HALT

;---------------------------------------------------------------------------------
; Required labels/addresses
;---------------------------------------------------------------------------------

; Stack address ** DO NOT CHANGE **
stack_addr           .FILL    xFE00

; Addresses of subroutines, other than main
get_user_string_addr .FILL    x3200
strlen_addr          .FILL    x3300
palindrome_addr      .FILL	  x3400


; Reserve memory for strings in the progrtam
user_prompt          .STRINGZ "Enter a string: "
result_string        .STRINGZ "The string is "
not_string           .STRINGZ "not "
final_string         .STRINGZ	"a palindrome\n"

; Reserve memory for user input string
user_string          .BLKW	  #100

.END

;---------------------------------------------------------------------------------
; get_user_string - get the user's input string and store it
; parameter: R1 - user_prompt string address
; parameter: R2 - address where the user string should be stored
;
; returns: nothing
;---------------------------------------------------------------------------------
.ORIG x3200
get_user_string
; Backup all used registers, R7 first, using proper stack discipline
add r6, r6, #-1
str r7 r6, #0

add r0, r0, r1
puts

and r1, r1, #0
add r1, r1, #-10 ; newline check

user_input
    getc
    out
    str r0, r2, #0
    add r3, r0, r1
    brz done
    add r2, r2, #1
    br user_input
    
done
; Resture all used registers, R7 last, using proper stack discipline
ldr r7, r6, #0
add r6, r6, #1

ret

.END

;---------------------------------------------------------------------------------
; strlen - compute the length of a zero terminated string
;
; parameter: R1 - the address of a zero terminated string
;
; returns: r3 - the length of the string
;---------------------------------------------------------------------------------
.ORIG x3300
strlen
; Backup all used registers, R7 first, using proper stack discipline
add r6, r6, #-1
str r7, r6, #0
add r6, r6, #-1
str r2, r6, #0
add r6, r6, #-1
str r1, r6, #0

and r3, r3, #0
and r2, r2, #0

string_size
    ldr r2, r1, #0
    add r2, r2, #-10
    brz terminate
    add r3, r3, #1
    add r1, r1, #1
    br string_size
    
terminate
; Resture all used registers, R7 last, using proper stack discipline
ldr r1, r6, #0
add r6, r6, #1
ldr r2, r6, #0
add r6, r6, #1
ldr r7, r6, #0
add r6, r6, #1

ret

.END

;---------------------------------------------------------------------------------
; palindrome - check if the string is parameter
; parameter: R1 - the address of the first letter in the string
;            R2 - the address of the last letter in the string
;            R6 - the address of stack    
; returns: R4 - if r4 is 1 then true, else false
;---------------------------------------------------------------------------------
.ORIG x3400

add r6, r6, #-1
str r7, r6, #0

palindrome ; Hint, do not change this label and use for recursive alls
; Backup all used registers, R7 first, using proper stack discipline
; Cases to test for
;   - zero string is true
;   - one character string is true
;   - don't account for spaces or capitals

add r3, r3, #0
brz true ; checks for empty string base case

and r0, r0, #0
add r0, r3, #-1
brz true ; checks for one character strings

and r0, r0, #0
and r7, r7, #0

ldr r0, r1, #0
ldr r7, r2, #0

not r0, r0
add r0, r0, #1

and r5, r5, #0
add r5, r0, r7

brnp false ; different characters is false

add r1, r1, #1 ; shift to the right from the front of the string
add r2, r2, #-1 ; shift to the left from the end of the string

add r4, r4, #-1 ; counter to traverse through the string
brz true ; cycled through all letters and found no difference, meaning all are the same and true

jsr palindrome

false
    and r4, r4, #0
    br restore
    
true
    and r4, r4, #0
    add r4, r4, #1
    
restore
; Resture all used registers, R7 last, using proper stack discipline
ldr r7, r6, #0
add r6, r6, #1

ret

.END
