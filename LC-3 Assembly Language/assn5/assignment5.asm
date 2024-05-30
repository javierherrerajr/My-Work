; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Javier Herrera
; Email: jherr116@ucr.edu
; 
; Assignment name: Assignment 5
; Lab section: 24
; TA: Karan Bhogal
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
ld r5, get_user_string_addr


; find size of input string
; * put your code here

; call palindrome method
; * put your code here

; determine of stirng is a palindrome
; * put your code here

; print the result to the screen
; * put your code here

; decide whether or not to print "not"
; * put your code here


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
; get_user_string - DO NOT FORGET TO REPLACE THIS HEADER WITH THE PROPER HEADER
;---------------------------------------------------------------------------------
.ORIG x3200
get_user_string
; Backup all used registers, R7 first, using proper stack discipline

; Resture all used registers, R7 last, using proper stack discipline
.END

;---------------------------------------------------------------------------------
; strlen - DO NOT FORGET TO REPLACE THIS HEADER WITH THE PROPER HEADER
;---------------------------------------------------------------------------------
.ORIG x3300
strlen
; Backup all used registers, R7 first, using proper stack discipline

; Resture all used registers, R7 last, using proper stack discipline
.END

;---------------------------------------------------------------------------------
; palindrome - DO NOT FORGET TO REPLACE THIS HEADER WITH THE PROPER HEADER
;---------------------------------------------------------------------------------
.ORIG x3400
palindrome ; Hint, do not change this label and use for recursive alls
; Backup all used registers, R7 first, using proper stack discipline

; Resture all used registers, R7 last, using proper stack discipline
.END
