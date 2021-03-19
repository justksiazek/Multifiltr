.data
matryca byte 1,2,1,2,4,2,1,2,1,0,0,0
sepia byte 0,30,60,0
kontr byte 122,122,122,0

.code
szaryASM proc ;skala odcieni szaroœci
mov rdi, rcx					;rdi <- wskaŸnik na piksel
pmovzxbd xmm1, dword ptr[rdi]	;xmm1 <- X(niebrany pod uwagê),r,g,b
movd eax, xmm1			;pobranie b
shufps xmm1, xmm1, 57	;xmm1: b,X,r,g
movd ecx, xmm1			;pobranie g
add rax, rcx			;dodanie kana³u do sumy kana³ów
shufps xmm1, xmm1, 57	;xmm1: g,b,X,r
movd ecx, xmm1			;pobranie r
add rax, rcx			;dodanie kana³u do sumy kana³ów
mov rdx, 0			;m³odsze bity dzielnej
mov r9, 3			;zapisanie dzielnej
div r9				;podzielenie wyniku dodawania przez 3 (obliczenie œredniej)
ret					;zwrócenie obliczonej œredniej przy powrocie z procedury
szaryASM endp

sepiaASM proc ;sepia
mov rdi, rcx			;rdi <- wskaŸnik na tablicê Ÿród³ow¹
mov rsi, rdx			;rsi <- wskaŸnik na tablicê wynikow¹
pmovzxbd xmm1, dword ptr[rdi]	;xmm1 <- X(niebrany pod uwagê),r,g,b
pmovzxbd xmm2, dword ptr[sepia]	;xmm2 <- maska (0,30,60,0)
paddusb xmm1, xmm2			;dodanie wartoœci do maski (ustawienie 255 w przypadku przepe³nienia)
movd r8d, xmm1				;pobranie b
mov byte ptr[rsi], r8B		;zapisanie wartoœci do tablicy wynikowej
shufps xmm1, xmm1, 57		;xmm1 <- b,X,r,g
movd r8d, xmm1				;pobranie g
mov byte ptr[rsi+1], r8B	;zapisanie obliczonej wartoœci do tablicy wynikowej
shufps xmm1, xmm1, 57		;xmm1 <- g,b,X,r
movd r8d, xmm1				;pobranie r
mov byte ptr[rsi+2], r8B	;zapisanie obliczonej wartoœci do tablicy wynikowej
ret
sepiaASM endp

kontrASM proc ;zwiêkasznie kontrastu
mov rdi, rcx	;rdi <- wskaŸnik na tablicê Ÿród³ow¹
mov rsi, rdx	;rsi <- wskaŸnik na tablicê wynikow¹
pmovzxbd xmm1, dword ptr[rdi]	;xmm1 <- X(niebrany pod uwagê),r,g,b
pmovzxbd xmm2, dword ptr[kontr]	;xmm2 <- maska (122,122,122,0)
psubd xmm1, xmm2	;odjêcie maski od wartoœci
pslld xmm1, 1		;przesuniêcie bitowe o jeden w prawo (mno¿enie x2)
paddd xmm1, xmm2	;dodanie maski do wartoœci
movd eax, xmm1		;pobranie b
cmp eax, 0			;skocz je¿eli wartoœæ jest mniejsza ni¿ zero
js mniejniz0a
cmp rax, 255		;skocz jeœli wartoœæ jest mniejsza ni¿ 255
js mniejniz255a
mov rax, 255		;wartoœæ spoza górnego zakresu - przypisanie 255
jmp mniejniz255a	;skok do przepisania wartoœci
mniejniz0a:
mov rax, 0			;wartoœæ spoza dolnego zakresu - przypisanie 0
mniejniz255a:
mov byte ptr[rsi], al	;zapisanie obliczonej wartoœci do tablicy wynikowej
shufps xmm1, xmm1, 57	;xmm1 <- b,X,r,g
movd eax, xmm1		;pobranie g
cmp eax, 0			;skocz je¿eli wartoœæ jest mniejsza ni¿ zero
js mniejniz0b
cmp rax, 255		;skocz jeœli wartoœæ jest mniejsza ni¿ 255
js mniejniz255b
mov rax, 255		;wartoœæ spoza górnego zakresu - przypisanie 255
jmp mniejniz255b	;skok do przepisania wartoœci
mniejniz0b:
mov rax, 0			;wartoœæ spoza dolnego zakresu - przypisanie 0
mniejniz255b:
mov byte ptr[rsi+1], al	;zapisanie obliczonej wartoœci do tablicy wynikowej
shufps xmm1, xmm1, 57	;xmm1 <- g,b,X,r
movd eax, xmm1		;pobranie r
cmp eax, 0			;skocz je¿eli wartoœæ jest mniejsza ni¿ zero
js mniejniz0c
cmp rax, 255		;skocz jeœli wartoœæ jest mniejsza ni¿ 255
js mniejniz255c
mov rax, 255		;wartoœæ spoza górnego zakresu - przypisanie 255
jmp mniejniz255c	;skok do przepisania wartoœci
mniejniz0c:
mov rax, 0			;wartoœæ spoza dolnego zakresu - przypisanie 0
mniejniz255c:
mov byte ptr[rsi+2], al	;zapisanie obliczonej wartoœci do tablicy wynikowej
ret
kontrASM endp

solarASM proc ;solaryzacja
mov rdi, rcx	;rdi <- wskaŸnik na tablicê Ÿród³ow¹
mov rsi, rdx	;rsi <- wskaŸnik na tablicê wynikow¹
pmovzxbd xmm1, dword ptr[rdi]	;xmm1 <- X(niebrany pod uwagê),r,g,b
movd eax, xmm1	;pobranie b
cmp rax, 127	;skok je¿eli wartoœæ jest mniejsza ni¿ 127
js mn1
not al			;negacja wczytanej wartoœci
sub rax, 255	;odjêcie 255 od wartoœci
mn1:
mov byte ptr[rsi], al	;zapisanie obliczonej wartoœci do tablicy wynikowej
shufps xmm1, xmm1, 57	;xmm1 <- b,X,r,g
movd eax, xmm1	;pobranie g
cmp rax, 127	;skok je¿eli wartoœæ jest mniejsza ni¿ 127
js mn2
not al			;negacja wczytanej wartoœci
sub rax, 255	;odjêcie 255 od wartoœci
mn2:
mov byte ptr[rsi+1], al	;zapisanie obliczonej wartoœci do tablicy wynikowej
shufps xmm1, xmm1, 57	;xmm1 <- g,b,X,r
movd eax, xmm1	;pobranie r
cmp rax, 127	;skok je¿eli wartoœæ jest mniejsza ni¿ 127
js mn3
not al			;negacja wczytanej wartoœci
sub rax, 255	;odjêcie 255 od wartoœci
mn3:
mov byte ptr[rsi+2], al	;zapisanie obliczonej wartoœci do tablicy wynikowej
ret
solarASM endp

gaussASM proc ;filtr Gaussa
mov rdi, rcx	;rdi <- wskaŸnik punkt
mov rsi, rdx		;rsi <- wskaŸnik na obraz docelowy
mov r9, 16		;r11 <- suma wag
mov rax, 0		;wyzerowanie sumy
pmovzxbd xmm1, dword ptr[rdi]		;xmm1 <- (x-3,y-1),(x,y-1),(x+3,y-1),(x-3,y)
pmovzxbd xmm2, dword ptr[matryca]	;xmm2 <- maska (1,2,1,2)
pmulld xmm1, xmm2		;pomno¿enie wartoœci przez maskê
movd ecx, xmm1			;pobranie wartoœci (x-3,y)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
shufps xmm1, xmm1, 57	;xmm1 <- (x-3,y),(x-3,y-1),(x,y-1),(x+3,y-1)
movd ecx, xmm1			;pobranie wartoœci (x+3,y-1)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
shufps xmm1, xmm1, 57	;xmm1 <- (x+3,y-1),(x-3,y),(x-3,y-1),(x,y-1)
movd ecx, xmm1			;pobranie wartoœci (x,y-1)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
shufps xmm1, xmm1, 57	;xmm1 <- (x,y-1),(x+3,y-1),(x-3,y),(x-3,y-1)
movd ecx, xmm1			;pobranie wartoœci (x-3,y-1)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
pmovzxbd xmm1, dword ptr[rdi+4]		;xmm1 <- (x,y),(x+3,y),(x-3,y+1),(x,y+1)
pmovzxbd xmm2, dword ptr[matryca+4] ;xmm2 <- maska (4,2,1,2)
pmulld xmm1, xmm2		;pomno¿enie wartoœci przez maskê
movd ecx, xmm1			;pobranie wartoœci (x-3,y)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
shufps xmm1, xmm1, 57	;xmm1 <- (x-3,y),(x-3,y-1),(x,y-1),(x+3,y-1)
movd ecx, xmm1			;pobranie wartoœci (x+3,y-1)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
shufps xmm1, xmm1, 57	;xmm1 <- (x+3,y-1),(x-3,y),(x-3,y-1),(x,y-1)
movd ecx, xmm1			;pobranie wartoœci (x,y-1)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
shufps xmm1, xmm1, 57	;xmm1 <- (x,y-1),(x+3,y-1),(x-3,y),(x-3,y-1)
movd ecx, xmm1			;pobranie wartoœci (x-3,y-1)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
pmovzxbd xmm1, dword ptr[rdi+8]		;xmm1 <- (x+3,y+1),0,0,0
pmovzxbd xmm2, dword ptr[matryca+8] ;xmm2 <- maska (1,0,0,0)
pmulld xmm1, xmm2		;pomno¿enie wartoœci przez maskê
movd ecx, xmm1			;pobranie wartoœci (x-3,y)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
shufps xmm1, xmm1, 57	;xmm1 <- (x-3,y),(x-3,y-1),(x,y-1),(x+3,y-1)
movd ecx, xmm1			;pobranie wartoœci (x+3,y-1)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
shufps xmm1, xmm1, 57	;xmm1 <- (x+3,y-1),(x-3,y),(x-3,y-1),(x,y-1)
movd ecx, xmm1			;pobranie wartoœci (x,y-1)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
shufps xmm1, xmm1, 57	;xmm1 <- (x,y-1),(x+3,y-1),(x-3,y),(x-3,y-1)
movd ecx, xmm1			;pobranie wartoœci (x-3,y-1)*maska
add rax, rcx			;dodanie wartoœci do sumy wa¿onej
mov rdx, 0				;wyzerowanie m³odszych bitów iloczynu
div r9					;obliczenie œredniej wa¿onej
mov byte ptr[rsi], al	;zapisanie obliczonej wartoœci do tablicy
ret
gaussASM endp

end