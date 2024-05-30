;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Javier Herrera 
; Email: jherr116@ucr.edu
; 
; Assignment name: Assignment 2
; Lab section: 24
; TA: Kangan Bhogal
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=========================================================================

.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------

;----------------------------------------------
;output prompt
;----------------------------------------------	
LEA R0, intro			; get starting address of prompt string
PUTS			    	; Invokes BIOS routine to output string

;-------------------------------
;INSERT YOUR CODE here
;--------------------------------

ld r5, adjustment

getc
add r1, r0, #0  ;first input taken and echo

getc
add r2, r0, #0  ;second input taken and echo

add r0, r1, #0  ;ouput first number
out

ld r0, newline
out

add r0, r2, #0  ;output second number
out

ld r0, newline
out

not r3, r2
add r3, r3, #1
add r4, r1, r3  ;subtraction comparison

brn NEG_CASE    ;incase result is negative
brnzp  REG_CASE ;incase result is positive

NEG_CASE    ;switches position of numbers and takes inverse of final result to convert into negative
    not r3, r1
    add r3, r3, #1
    add r4, r2, r3
    add r4, r4, r5 ;48 from ascii conversion rate
    brnzp neg_output

REG_CASE
    add r4, r4, r5
    brnzp reg_output
    
neg_output
    add r0, r1, #0
    out
    
    lea r0, subraction  ;output operation
    puts
    
    add r0, r2, #0
    out

    lea r0, equal   ;output equal sign
    puts
    
    ld r0, subtraction_2
    out
    
    add r0, r4, #0
    out
    brnzp newline_termination
    
reg_output
    add r0, r1, #0
    out
    
    lea r0, subraction  ;output operation
    puts
    
    add r0, r2, #0
    out

    lea r0, equal   ;output equal sign
    puts
    
    add r0, r4, #0
    out

newline_termination
    ld r0, newline
    out
    
HALT				; Stop execution of program
;------	
;Data
;------
; String to prompt user. Note: already includes terminating newline!
intro 	.STRINGZ	"ENTER two numbers (i.e '0'....'9')\n" 		; prompt string - use with LEA, followed by PUTS.
newline .FILL x0A	; newline character - use with LD followed by OUT
subraction   .STRINGZ " - "
subtraction_2   .stringz    "-"
equal   .stringz    " = "
adjustment  .fill   #48

;---------------	
;END of PROGRAM
;---------------	
.END

