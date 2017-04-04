TITLE Programming Assignment #3 Accumulator    (Project03.asm)

; Author: Jonathan Nicolosi
; Description:
;1. Display the program title and programmer’s name.
;2. Get the user’s name, and greet the user.
;3. Display instructions for the user.
;4. Repeatedly prompt the user to enter a number. Validate the user input to be in [-100, -1] (inclusive).
;		Count and accumulate the valid user numbers until a non-negative number is entered. (The non-
;		negative number is discarded.)
;5. Calculate the (rounded integer) average of the negative numbers. 6. Display:
;	i. the number of negative numbers entered (Note: if no negative numbers were entered, display a special message and skip to iv.)
;	ii. the sum of negative numbers entered
;	iii. the average, rounded to the nearest integer (e.g. -20.5 rounds to -20)
;	iv. a parting message (with the user’s name)

INCLUDE Irvine32.inc

.data

greeting			BYTE	"Welcome to the Integer Accumulator by Jonathan Nicolosi", 0
prompt1				BYTE	"Please enter numbers between [-100, -1].", 0
prompt2				BYTE	"Enter a non-negative number when you are finished to see results. ", 0
prompt3				BYTE	" Enter a number: ", 0
getName				BYTE	"What's your name?", 0
hello				BYTE	"Hi, ", 0
goodbye			    BYTE	"Thank you for playing Integer Accumulator! It's been a pleasure to meet you, ", 0
number			    DWORD  ?
userName			BYTE   32 DUP(0)
getUsername			DWORD	?
count				DWORD	1
accumulator			DWORD	0
total					    BYTE	"The total is:                  ", 0
numberOFnumbers 		BYTE	"Amount of numbers you entered:  ", 0
roundedAvgPrompt			BYTE	"The Rounded Average is:        ", 0
roundedAvg				    DWORD  0


;constraints
LOWERLIMIT		=		 -100
UPPERLIMIT		=		 -1



.code
 main PROC


	; Programmer name and title of assignment
  	call	 CrLf
  	mov		 edx, OFFSET greeting
  	call	 WriteString
  	call	 CrLf

	; get user name
  	mov		edx, OFFSET getName
  	call	WriteString
  	call	CrLf
  	mov		edx, OFFSET userName
  	mov		ecx, 32
  	call	ReadString


	;test username
  	mov		edx, OFFSET hello
  	call	WriteString
  	mov		edx, OFFSET userName
  	call	WriteString
  	call	CrLF

	; assignment instructions
  	mov		edx, OFFSET prompt1
  	call	WriteString
  	call	CrLf
  	mov		edx, OFFSET prompt2
  	call	WriteString
  	call	CrLf
  	mov		ecx, 0


	; loop to allow user to continue entering negative numbers
	userNumbers:	;read user number
			mov		eax, count
			call	WriteDec
			add		eax, 1
			mov		count, eax
			mov	  edx, OFFSET prompt3
			call	WriteString
			call  ReadInt
			mov   number, eax
			cmp		eax,LOWERLIMIT
			jb		addNumbers;
			cmp		eax, UPPERLIMIT
			jg		addNumbers
			add		eax, accumulator
			mov		accumulator, eax
			loop	userNumbers


	; do the accumulation
	addNumbers:
			;If no valid numbers entered, jump to goodbyePrompt
			mov		eax, count
			sub		eax, 2
			jz		goodbyePrompt
			mov		eax, accumulator
			call	CrLF

			; accumulated total
			mov		edx, OFFSET  total
			call	WriteString
			mov		eax, accumulator
			call	WriteInt
			call	CrLF

			; total numbers accumulated
			mov		edx, OFFSET numberOFnumbers
			call	WriteString
			mov		eax, count
			sub		eax, 2
			call	WriteDec
			call	CrLf

			; integer rounded average
			mov		edx, OFFSET roundedAvgPrompt
			call	WriteString
			mov		eax, 0
			mov		eax, accumulator
			cdq
			mov		ebx, count
			sub		ebx, 2
			idiv	ebx
			mov		roundedAvg, eax
			call	WriteInt
			call	CrLf



	; say goodbye
	goodbyePrompt:
			call	CrLf
			mov		edx, OFFSET goodbye
			call	WriteString
			mov		edx, OFFSET userName
			call	WriteString
			call	CrLf

exit	; exit to operating system
main ENDP

END main