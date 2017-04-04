TITLE Fibonacci Numbers    (Project02.asm)

;Program to print Fibonacci numbers	

INCLUDE Irvine32.inc

.data
myName				BYTE	"Jonathan Nicolosi ", 0
programTitle		BYTE	"Fibonacci Numbers by ", 0
prompt_1			BYTE	"What is your name? ", 0
prompt_2			BYTE	"Enter the number of Fibonacci terms you would like to see. Please enter any integer between 1 and 46 ", 0
NumberOfFibToPrint	DWORD	?
prev1				DWORD	?
prev2				DWORD	?
spaces				BYTE	"     ",0
goodbye				BYTE	"Goodbye,  ", 0
firstTwo			BYTE	"1     1     ", 0
firstOne			BYTE	"1", 0
temp				DWORD	?
IntegerFive			DWORD	5
highest = 46
lowest = 1

;user's name
username			BYTE 33 DUP(0)
byteCount			DWORD	?

;greet user
greeting			BYTE	"Hello, ",0

;validation
toohighprompt		BYTE	"Too high. Enter a number less than 46 ", 0
toolowprompt		BYTE	"Too low. Enter a number above 1 ", 0


.code
 main PROC



	; INTRODUCTION
		mov		edx, OFFSET programTitle
		call	WriteString
		mov		edx, OFFSET myName
		call	WriteString
		call	CrLf

		mov		edx, OFFSET prompt_1
		call	WriteString
		call	CrLf

		; get user's name
		mov edx, OFFSET username
		mov ecx, 32
		call ReadString

		; greet the user
		mov		edx, OFFSET greeting
		call	WriteString
		mov		edx, OFFSET username
		call	WriteString
		call	CrLf

	; USER INSTRUCTIONS
topPrompt:
			mov		edx, OFFSET prompt_2
			call	WriteString
			call	CrLf

	; GET USER DATA
		call	ReadInt
		mov		NumberOfFibToPrint, eax

	; Validate user data
		cmp		eax, highest ;compare our upper bound with the given number
		jg		TooHigh ;jump if the value provided is greater than our upper bound
		cmp		eax, lowest ;compare our lower bound with the given number
		jl		TooLow ;jump if the value provided is less than
		cmp		eax, 1 
		je		OnlyOne ;if the user asks for only one number, jump immediately to printing 1
		cmp		eax, 2
		je		OnlyTwo ;if the user asks for only 2 numbers, jump immediately to printing 2
		cmp		eax, 3
		jg		GreaterThanThree
		je		OnlyThree ;To account for special case in loop where subtracting 3 causes the program to print infinitely.
		

	; DISPLAY FIBS

		; prepare loop (post-test), do the first two manually

		OnlyThree:
		mov		ecx, NumberOfFibToPrint
		sub		ecx, 2
		jmp		DisplayFibs
		
		GreaterThanThree:
		mov		ecx, NumberOfFibToPrint
		sub		ecx, 3
		jmp		DisplayFibs
		DisplayFibs:
		mov		eax, 1
		call	WriteDec
		mov		edx, OFFSET spaces
		call	WriteString
		call	WriteDec
		mov		edx, OFFSET spaces
		call	WriteString
		mov		prev2, eax
		mov		eax, 2
		call	WriteDec
		mov		edx, OFFSET spaces
		call	WriteString
		mov		prev1, eax

		fib:
			; add prev 2 to eax
			add		eax, prev2
			call	WriteDec

			mov		edx, OFFSET spaces
			call	WriteString

			mov		temp, eax
			mov		eax, prev1
			mov		prev2, eax
			mov		eax, temp
			mov		prev1, eax

			;for spacing (first time it should be % 3, rest %5)
			mov		edx, ecx
			cdq
			div		IntegerFive
			cmp		edx, 0
			jne		skip
			call	CrLf

		skip:
			; restore what was on eax
			mov		eax, temp
			; if ecx % 3 = 0 call CrLf
			loop	fib
			jmp		TheEnd

TooHigh:
			mov		edx, OFFSET toohighprompt
			call	WriteString
			call	CrLf
			jmp		TopPrompt

TooLow:
			mov		edx, OFFSET toolowprompt
			call	WriteString
			call	CrLf
			jmp		TopPrompt
;If the user asks for 1 number, no need to calculate. Just print the first number in the sequence.
OnlyOne:
			mov		edx, OFFSET firstOne
			call	WriteString
			jmp		TheEnd
;If the user asks for 2 numbers, no need to calculate. Just print the first and second numbers in the sequence.
OnlyTwo:
			mov		edx, OFFSET firstTwo
			call	WriteString
			jmp		TheEnd

	; FAREWELL
TheEnd:
			call	CrLf
			mov		edx, OFFSET goodbye
			call	WriteString
			mov		edx, OFFSET username
			call	WriteString
			call	CrLf

	exit	; exit to operating system
main ENDP

END main