TITLE Program 1    (Prog01.asm)

; Author: Jonathan Nicolosi
; Course / Project ID                 Date: 04/10/2016
; Description: This program will get the sum, difference, quotient, and remainder of two numbers.

INCLUDE Irvine32.inc
; (insert constant definitions here)

.data
; (insert variable definitions here)

intro BYTE "Elementary Arithmetic by Jonathan Nicolosi",0
userprompt BYTE "Enter 2 numbers, and I'll show you the sum, difference, product, quotient, and remainder.", 0
prompt_1 BYTE "First number: ", 0
prompt_2 BYTE "Second number: ", 0
sum_statement BYTE "The sum is: ", 0
difference_statement BYTE "The difference is: ", 0
product_statement BYTE "The product is: ", 0
quotient_statement BYTE "The quotient is: ", 0
remainder_statement BYTE "The remainder is: ", 0
number_1 DWORD ?
number_2 DWORD ?
sum_result DWORD ?
difference_result DWORD ?
product_result DWORD ?
quotient_result DWORD ?
remainder_result DWORD ?

.code
main PROC
; (insert executable instructions here)

;Print intro
	mov edx, OFFSET intro
	call WriteString
	call CrLf

;Print userprompt
	mov edx, OFFSET userprompt
	call WriteString
	call CrLf

;Ask for first number
	mov edx, OFFSET prompt_1
	call WriteString

;Get first number
	call ReadInt
	mov number_1, eax
	
;Ask for second number
	mov edx, OFFSET prompt_2
	call WriteString

;Get second number
	call ReadInt
	mov number_2, eax
	
;Add number_1 and number_2
	mov	eax, number_1
	add	eax, number_2
	mov	sum_result, eax

;Display sum
	mov edx, OFFSET sum_statement
	call WriteString
	mov	eax, sum_result
	call WriteDec
	call CrLf

;Subtract number_1 and number_2
	mov eax, number_1
	sub eax, number_2
	mov difference_result, eax
	
;Display difference
	mov edx, OFFSET difference_statement
	call WriteString
	mov eax, difference_result
	call WriteDec
	call CrLf

;Multiply number_1 and number_2
	mov eax, number_1
	mov ebx, number_2
	mul ebx
	mov product_result, eax

;Display product
	mov edx, OFFSET product_statement
	call WriteString
	mov eax, product_result
	call WriteDec
	call CrLf

;Divide number_1 by number_2
	mov edx, 0
	mov eax, number_1
	cdq
	mov ebx, number_2
	cdq
	div ebx
	mov quotient_result, eax
	mov remainder_result, edx

;Display quotient
	mov edx, OFFSET quotient_statement
	call WriteString
	mov eax, quotient_result
	call WriteDec
	call CrLf

;Display remainder
	mov edx, OFFSET remainder_statement
	call WriteString
	mov eax, remainder_result
	call WriteDec
	call CrLf

	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
