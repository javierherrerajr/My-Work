;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Javier Herrera
; Email: jherr116@ucr.edu
; 
; Assignment name: Assignment 4
; Lab section: 24
; TA: Karan Bhogal
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
;THE BINARY REPRESENTATION OF THE USER-ENTERED DECIMAL NUMBER MUST BE STORED IN R4
;=================================================================================

.ORIG x3000		
;-------------
;Instructions
;-------------

; output intro prompt
prompt ; recursive call label for if invalid input is entered
    and r0, r0, #0 ; r0 cannot be changed
	ld r0, introPromptPtr ; gets prompt
	puts ; outputs prompts
	
; Set up flags, counters, accumulators as needed
    and r1, r1, #0
    
    ; ld r1, newlineCheck ; checker for newline entered - cannot be changed
    and r2, r2, #0 ; register that holds checking values - can be changed
    and r3, r3, #0
    add r3, r3, #1 ; holds flag for if the number is negative or positive - 0=negative, 1=positive. default is negative is true - cannot be changed
    and r4, r4, #0 ; holds value entered by user in converted decimal form - cannot be changed
    and r5, r5, #0
    add r5, r5, #5 ; holds the max digits allowed in a single entry - cannot be changed
    and r6, r6, #0 ; sign tracker
    ld r6, asciiConversion
    and r7, r7, #0 ; determines if loop is handling the first or other digits - can be changed
    
; Get first character, test for '\n', '+', '-', digit/non-digit 
fiveIntegers ; Now get remaining digits from user in a loop (max 5), testing each to see if it is a digit, and build up number in accumulator
	getc
	out

newlineTest
    and r2, r2, #0
    add r2, r0, #-10
    brz negativeConversion ; is very first character = '\n'? if so, just quit (no message)!

positiveTest
    and r2, r2, #0
    add r2, r2, #-10
    add r2, r2, #-10
    add r2, r2, #-12
    add r2, r2, #-11
    add r2, r0, r2
    brn error
    brz positiveTrue ; is it = '+'? if so, ignore it, go get digits
    
negativeTest
    and r2, r2, #0
    add r2, r2, #-10
    add r2, r2, #-10
    add r2, r2, #-12
    add r2, r2, #-13
    add r2, r0, r2
    brn error
    brz negativeTrue ; is it = '-'? if so, set neg flag, go get digits

inputTestOne
    and r2, r2, #0
    add r2, r2, #-10
    add r2, r2, #-10
    add r2, r2, #-15
    add r2, r2, #-13
    add r2, r0, r2
    brn error
    ; brz isInteger ; is it < '0'? if so, it is not a digit	- o/p error message, start over
    
inputTestTwo
    and r2, r2, #0
    add r2, r2, #-16
    add r2, r2, #-16
    add r2, r2, #-16
    add r2, r2, #-9
    add r2, r2, r0
    brp error ; is it > '9'? if so, it is not a digit	- o/p error message, start over
    br isInteger
    

positiveTrue

    ADD R1, R1, #0
    BRp PROMPT
    add R1, R1, #1
    
    add r3, r3, #0 ; sets condition to true for positive number
    brnzp fiveIntegers
	    
negativeTrue
    ADD R1, R1, #0
    BRp PROMPT
    add R1, R1, #1
    add r3, r3, #-1 ; is it = '-'? if so, set neg flag, go get digits
    brnzp fiveIntegers
    
error
    ld r0, newline
    out
    ld r0, errorMessagePtr
    puts
    add r0, r0, #0
    brnzp prompt
    
loader
    ld r7, multiplierCounter
    add r2, r4, #0
    
multipleNumberBuncher
    add r4, r4, r2
    add r7, r7, #-1
    brp multipleNumberBuncher
    brnzp traverse
    
isInteger
    add r0, r0, r6
    and r7, r7, #0
    add r7, r5, #-5
    brn loader
    
traverse
    add r4, r4, r0
	add r5, r5, #-1
	brp fiveIntegers
	
negativeConversion
    add r3, r3, #0
    brp terminate
    not r4, r4
    add r4, r4, #1

terminate

    add r3, r3, #0
    ; brp rip
    ; not r4, r4
    ; add r4, r4, #1
    ; rip
    ld r0, newline
    out ; remember to end with a newline!
    
HALT

;---------------	
; Program Data
;---------------

introPromptPtr  .FILL xB000
errorMessagePtr .FILL xB200
newlineCheck .FILL #-32
newline .FILL x0A
asciiConversion .FILL #-48
multiplierCounter .FILL #9

.END

;------------
; Remote data
;------------
.ORIG xB000	 ; intro prompt
.STRINGZ	 "Input a positive or negative decimal number (max 5 digits), followed by ENTER\n"

.END					
					
.ORIG xB200	 ; error message
.STRINGZ	 "ERROR: invalid input\n"

;---------------
; END of PROGRAM
;---------------
.END

;-------------------
; PURPOSE of PROGRAM
;-------------------
; Convert a sequence of up to 5 user-entered ascii numeric digits into a 16-bit two's complement binary representation of the number.
; if the input sequence is less than 5 digits, it will be user-terminated with a newline (ENTER).
; Otherwise, the program will emit its own newline after 5 input digits.
; The program must end with a *single* newline, entered either by the user (< 5 digits), or by the program (5 digits)
; Input validation is performed on the individual characters as they are input, but not on the magnitude of the number.
