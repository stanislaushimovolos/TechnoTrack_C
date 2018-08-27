section .data

	Buffer :times 65 db "0"				
	BufLen equ $ - Buffer 	
	elem_sz equ 8

section .text

	global MyPrintf


MyPrintf :					; better than C printf (much better)	
						; r8 - arg counter, r9 - char counter
						; rbx - string index
						; destr :r8, r9, r10, rax, rdi
	pop  rax 				; rax = retAddress
						
    	push r9					; push cdecal arguments to stack
        push r8					;
	push rcx				;
	push rdx				;
	push rsi				;
        push rdi				;				

 	push rax 				; return retAddress
						;			
	push rbp				; save rbp

	mov rbp, rsp				; set rbp on the stack top
	mov r8, 2				; set arg counter on the first argument

	push rbx				; save rbx
	push r12				; save r12

	xor rbx, rbx
	xor r12, r12				; r12 - '%' counter

	mov r9, [rbp + r8 *elem_sz]		; r9 = string adderss

.StrAnalysis :

;	xor rbx, rbx				; strPtr = 0;

	.StrCycle :
	
		cmp byte [r9 + rbx], 0		; if( sstring[i] == "\0") => Exit
		je .Exit			

		cmp byte [r9 + rbx], "%"	; if(string[i] == '%') => Begin analysis
		je .Execute

		inc rbx 			; formatStr[i++]

		jmp .StrCycle

.Execute :
	inc r8					; stack[i++]
						
	push rbx				; print symbols before '%' 
	push r9					;
						;
	call PrintStr				;
						
	pop r9					; stack aligment 
	pop rbx					;
	
	add r9, rbx				; formatStr = formatStr + i
	xor rbx, rbx				;

	inc r9					; MainStr++

	inc r12
	
	cmp byte [r9], "c"
	je .PrintC

	cmp byte [r9], "s"
	je .PrintS

	cmp byte [r9], "d"
	je .PrintDec

	cmp byte [r9], "b"
	je .PrintBin

	cmp byte [r9], "o"
	je .PrintOct
	
	cmp byte [r9], "x"
	je .PrintHex

	dec r8
	

	mov rbx, 1  
	dec r9

	dec r12

	jmp .StrAnalysis


.PrintC :

	lea rax, [rbp + r8 *elem_sz]		; rax = &(char a)
	
	push 1					; print char
	push rax				;
						;
	call PrintStr				;

	pop rax					; stack alignment	
	pop rax					;

	inc r9					; MainStr[i++]
						;

	jmp .StrAnalysis			;


.PrintS :

	cld

	mov rdi, [rbp + r8 *elem_sz]		; rdi = &(printable string) 

	mov al, 0				; rcx = strlen(print str)
	mov rcx, 0xFFFFFFFFFFFFFFFF 		;
						;
	repne scasb				;
						;
	not rcx					;

	push rcx				;

	mov rcx, [rbp + r8 *elem_sz]		;
	push rcx				;

	call PrintStr				;

	pop rdi					; stack alignment
	pop rcx					;
						
	inc r9					; formatStr[i++]

	jmp .StrAnalysis


.PrintDec :

	mov r10, 10				; r10 = radix
	mov rdi, Buffer + BufLen - 2		;

	push rdi				;
	mov rax, [rbp +r8 *elem_sz]		;


	.DecCycle :
		xor rdx, rdx			;
	
		div r10				; rax = rax/10
		mov byte [rdi], dl		; rdx = rax % 10
		add byte [rdi], "0"		; [rdi--] = al
						;
		dec rdi				;
		
		test rax, rax			;
		jz .DecFinish			;
		jmp .DecCycle			;
	
	.DecFinish :	
	
		cld				;
			
		pop rax				; print Dec number
	 	sub rax, rdi			;			
		inc rdi				;          

		push rax			;
		push rdi			;

		call PrintStr                   ;
	
	        pop rax                         ; stack alingment
	        pop rax                         ;
	 
	        inc r9                          ; formatStr[i++]
	 
	        jmp .StrAnalysis                ;
	 
	 


.PrintHex :
						; ;123456789ABCDEF поменять!!!!!!!!!!!!!!1
	mov rbx, [rbp + r8 *elem_sz]		; rbx = stack[i]
	mov rdi, Buffer + BufLen - 2		; set rdi on the end of string

	push rdi				; save string ending

	std					; 

	.HexCycle :
		
		mov rax, rbx			; rax = rbx % 16 
		and rax, 1111b			; rbx = rbx\16
		shr rbx, 4			; 

		cmp al, 9			; if (al > 9) => al += 7
		jle .LessThanNine 		;
		add al, 7			;
				
	.LessThanNine :

		add al, "0"			; [rdi --] = al
		stosb				;

		test rbx, rbx			; if(rbx == 0) => finish
		jz .HexFinish			;	else continue cycle
						;
		jmp .HexCycle			;

	.HexFinish :
		
		cld				; 
						
		pop rax				; rax = strlen(string)
		sub rax, rdi			;
						
		inc rdi				; print Hex number
						;
		push rax			;
		push rdi			;
						;
		call PrintStr			;

		pop rax				; stack alignment
		pop rax				;

		inc r9				; stack[i++]

		jmp .StrAnalysis		;



.PrintOct :
	
	mov rbx, [rbp + r8 *elem_sz]		; rbx = stack[i]
	mov rdi, Buffer + BufLen - 2		; set rdi on the end of string

	push rdi				; save str ending

	std					;

	.OctCycle :
		

		mov rax, rbx			; rax = rbx % 8
		and rax, 111b 			; rbx = rbx/8
		shr rbx, 3			;
	
		add al, "0"			; [rdi--] = al
		stosb				;

		test rbx, rbx			; if( rbx == 0) => finish
		jz .OctFinish			;	else continue cycle
						;
		jmp .OctCycle			; 

	.OctFinish :

		cld				;
						
		pop rax				; rax = strlen(string)
		sub rax, rdi			;
						;
		inc rdi				; print Oct number

		push rax			;
		push rdi			;
						;
		call PrintStr			;

		pop rax				; stack alingment
		pop rax				;

		inc r9				; sring[i++]

		jmp .StrAnalysis		;


.PrintBin :

	mov rbx, [rbp +r8 *elem_sz]		; rbx = stack[i] 
	mov rdi, Buffer + BufLen - 2		; set rdi on the end of str

	push rdi				; save str ending

	std					; set DF

	.BinCycle :

		shr rbx, 1			; if(last digit = 0)=-> jump 
		jc .putOne			;						

		.putZero :
			mov al, "0"		; s[i++] = "0"
			stosb			;
			test rbx, rbx		;
			jz .BinFinish		;
			jmp .BinCycle		;

		.putOne :
			mov al, "1"		; s[i++] = "1"
			stosb			;
			test rbx, rbx		;
			jz .BinFinish		;
			jmp .BinCycle		;

	.BinFinish :
		
		cld				; print Bin number
						;
		pop rax				;
		sub rax, rdi			;
						;
		inc rdi				;

		push rax			;
		push rdi			;

		call PrintStr			;

		pop rax				;
		pop rax				;

		inc r9				;

		jmp .StrAnalysis


.Exit :

	push rbx				; print symbols after last '%'	
	push r9					; 
						;
	call PrintStr				;
						;
	pop rbx					;
	pop r9 					;
	
	mov rax, r12				; rax = % counter

	pop r12					; restore r12 
	pop rbx					; restore rbx
	pop rbp					; restore rbp
									;
	ret					; ret rax


PrintStr :					; print a string 
						; parametres 	: 
	push rbp				;		string pointer
	mov rbp, rsp				;		string length
						;
	mov rdi, 2				; Destr : rdi, rsi, rax
	
	mov rsi,[rbp + rdi *elem_sz]
	inc rdi

	mov rdx, [rbp + rdi *elem_sz] 
	inc rdi

	mov rax, 1
	mov rdi, 1

	syscall

	pop rbp
 
	ret  
