.data
matryca byte 1,2,1,2,4,2,1,2,1,0,0,0
sepia byte 0,30,60,0
kontr byte 122,122,122,0

.code
szaryASM proc ;skala odcieni szaro�ci
mov rdi, rcx					;rdi <- wska�nik na piksel
pmovzxbd xmm1, dword ptr[rdi]	;xmm1 <- X(niebrany pod uwag�),r,g,b
movd eax, xmm1			;pobranie b
shufps xmm1, xmm1, 57	;xmm1: b,X,r,g
movd ecx, xmm1			;pobranie g
add rax, rcx			;dodanie kana�u do sumy kana��w
shufps xmm1, xmm1, 57	;xmm1: g,b,X,r
movd ecx, xmm1			;pobranie r
add rax, rcx			;dodanie kana�u do sumy kana��w
mov rdx, 0			;m�odsze bity dzielnej
mov r9, 3			;zapisanie dzielnej
div r9				;podzielenie wyniku dodawania przez 3 (obliczenie �redniej)
ret					;zwr�cenie obliczonej �redniej przy powrocie z procedury
szaryASM endp

sepiaASM proc ;sepia
mov rdi, rcx			;rdi <- wska�nik na tablic� �r�d�ow�
mov rsi, rdx			;rsi <- wska�nik na tablic� wynikow�
pmovzxbd xmm1, dword ptr[rdi]	;xmm1 <- X(niebrany pod uwag�),r,g,b
pmovzxbd xmm2, dword ptr[sepia]	;xmm2 <- maska (0,30,60,0)
paddusb xmm1, xmm2			;dodanie warto�ci do maski (ustawienie 255 w przypadku przepe�nienia)
movd r8d, xmm1				;pobranie b
mov byte ptr[rsi], r8B		;zapisanie warto�ci do tablicy wynikowej
shufps xmm1, xmm1, 57		;xmm1 <- b,X,r,g
movd r8d, xmm1				;pobranie g
mov byte ptr[rsi+1], r8B	;zapisanie obliczonej warto�ci do tablicy wynikowej
shufps xmm1, xmm1, 57		;xmm1 <- g,b,X,r
movd r8d, xmm1				;pobranie r
mov byte ptr[rsi+2], r8B	;zapisanie obliczonej warto�ci do tablicy wynikowej
ret
sepiaASM endp

kontrASM proc ;zwi�kasznie kontrastu
mov rdi, rcx	;rdi <- wska�nik na tablic� �r�d�ow�
mov rsi, rdx	;rsi <- wska�nik na tablic� wynikow�
pmovzxbd xmm1, dword ptr[rdi]	;xmm1 <- X(niebrany pod uwag�),r,g,b
pmovzxbd xmm2, dword ptr[kontr]	;xmm2 <- maska (122,122,122,0)
psubd xmm1, xmm2	;odj�cie maski od warto�ci
pslld xmm1, 1		;przesuni�cie bitowe o jeden w prawo (mno�enie x2)
paddd xmm1, xmm2	;dodanie maski do warto�ci
movd eax, xmm1		;pobranie b
cmp eax, 0			;skocz je�eli warto�� jest mniejsza ni� zero
js mniejniz0a
cmp rax, 255		;skocz je�li warto�� jest mniejsza ni� 255
js mniejniz255a
mov rax, 255		;warto�� spoza g�rnego zakresu - przypisanie 255
jmp mniejniz255a	;skok do przepisania warto�ci
mniejniz0a:
mov rax, 0			;warto�� spoza dolnego zakresu - przypisanie 0
mniejniz255a:
mov byte ptr[rsi], al	;zapisanie obliczonej warto�ci do tablicy wynikowej
shufps xmm1, xmm1, 57	;xmm1 <- b,X,r,g
movd eax, xmm1		;pobranie g
cmp eax, 0			;skocz je�eli warto�� jest mniejsza ni� zero
js mniejniz0b
cmp rax, 255		;skocz je�li warto�� jest mniejsza ni� 255
js mniejniz255b
mov rax, 255		;warto�� spoza g�rnego zakresu - przypisanie 255
jmp mniejniz255b	;skok do przepisania warto�ci
mniejniz0b:
mov rax, 0			;warto�� spoza dolnego zakresu - przypisanie 0
mniejniz255b:
mov byte ptr[rsi+1], al	;zapisanie obliczonej warto�ci do tablicy wynikowej
shufps xmm1, xmm1, 57	;xmm1 <- g,b,X,r
movd eax, xmm1		;pobranie r
cmp eax, 0			;skocz je�eli warto�� jest mniejsza ni� zero
js mniejniz0c
cmp rax, 255		;skocz je�li warto�� jest mniejsza ni� 255
js mniejniz255c
mov rax, 255		;warto�� spoza g�rnego zakresu - przypisanie 255
jmp mniejniz255c	;skok do przepisania warto�ci
mniejniz0c:
mov rax, 0			;warto�� spoza dolnego zakresu - przypisanie 0
mniejniz255c:
mov byte ptr[rsi+2], al	;zapisanie obliczonej warto�ci do tablicy wynikowej
ret
kontrASM endp

solarASM proc ;solaryzacja
mov rdi, rcx	;rdi <- wska�nik na tablic� �r�d�ow�
mov rsi, rdx	;rsi <- wska�nik na tablic� wynikow�
pmovzxbd xmm1, dword ptr[rdi]	;xmm1 <- X(niebrany pod uwag�),r,g,b
movd eax, xmm1	;pobranie b
cmp rax, 127	;skok je�eli warto�� jest mniejsza ni� 127
js mn1
not al			;negacja wczytanej warto�ci
sub rax, 255	;odj�cie 255 od warto�ci
mn1:
mov byte ptr[rsi], al	;zapisanie obliczonej warto�ci do tablicy wynikowej
shufps xmm1, xmm1, 57	;xmm1 <- b,X,r,g
movd eax, xmm1	;pobranie g
cmp rax, 127	;skok je�eli warto�� jest mniejsza ni� 127
js mn2
not al			;negacja wczytanej warto�ci
sub rax, 255	;odj�cie 255 od warto�ci
mn2:
mov byte ptr[rsi+1], al	;zapisanie obliczonej warto�ci do tablicy wynikowej
shufps xmm1, xmm1, 57	;xmm1 <- g,b,X,r
movd eax, xmm1	;pobranie r
cmp rax, 127	;skok je�eli warto�� jest mniejsza ni� 127
js mn3
not al			;negacja wczytanej warto�ci
sub rax, 255	;odj�cie 255 od warto�ci
mn3:
mov byte ptr[rsi+2], al	;zapisanie obliczonej warto�ci do tablicy wynikowej
ret
solarASM endp

gaussASM proc ;filtr Gaussa
mov rdi, rcx	;rdi <- wska�nik punkt
mov rsi, rdx		;rsi <- wska�nik na obraz docelowy
mov r9, 16		;r11 <- suma wag
mov rax, 0		;wyzerowanie sumy
pmovzxbd xmm1, dword ptr[rdi]		;xmm1 <- (x-3,y-1),(x,y-1),(x+3,y-1),(x-3,y)
pmovzxbd xmm2, dword ptr[matryca]	;xmm2 <- maska (1,2,1,2)
pmulld xmm1, xmm2		;pomno�enie warto�ci przez mask�
movd ecx, xmm1			;pobranie warto�ci (x-3,y)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
shufps xmm1, xmm1, 57	;xmm1 <- (x-3,y),(x-3,y-1),(x,y-1),(x+3,y-1)
movd ecx, xmm1			;pobranie warto�ci (x+3,y-1)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
shufps xmm1, xmm1, 57	;xmm1 <- (x+3,y-1),(x-3,y),(x-3,y-1),(x,y-1)
movd ecx, xmm1			;pobranie warto�ci (x,y-1)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
shufps xmm1, xmm1, 57	;xmm1 <- (x,y-1),(x+3,y-1),(x-3,y),(x-3,y-1)
movd ecx, xmm1			;pobranie warto�ci (x-3,y-1)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
pmovzxbd xmm1, dword ptr[rdi+4]		;xmm1 <- (x,y),(x+3,y),(x-3,y+1),(x,y+1)
pmovzxbd xmm2, dword ptr[matryca+4] ;xmm2 <- maska (4,2,1,2)
pmulld xmm1, xmm2		;pomno�enie warto�ci przez mask�
movd ecx, xmm1			;pobranie warto�ci (x-3,y)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
shufps xmm1, xmm1, 57	;xmm1 <- (x-3,y),(x-3,y-1),(x,y-1),(x+3,y-1)
movd ecx, xmm1			;pobranie warto�ci (x+3,y-1)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
shufps xmm1, xmm1, 57	;xmm1 <- (x+3,y-1),(x-3,y),(x-3,y-1),(x,y-1)
movd ecx, xmm1			;pobranie warto�ci (x,y-1)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
shufps xmm1, xmm1, 57	;xmm1 <- (x,y-1),(x+3,y-1),(x-3,y),(x-3,y-1)
movd ecx, xmm1			;pobranie warto�ci (x-3,y-1)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
pmovzxbd xmm1, dword ptr[rdi+8]		;xmm1 <- (x+3,y+1),0,0,0
pmovzxbd xmm2, dword ptr[matryca+8] ;xmm2 <- maska (1,0,0,0)
pmulld xmm1, xmm2		;pomno�enie warto�ci przez mask�
movd ecx, xmm1			;pobranie warto�ci (x-3,y)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
shufps xmm1, xmm1, 57	;xmm1 <- (x-3,y),(x-3,y-1),(x,y-1),(x+3,y-1)
movd ecx, xmm1			;pobranie warto�ci (x+3,y-1)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
shufps xmm1, xmm1, 57	;xmm1 <- (x+3,y-1),(x-3,y),(x-3,y-1),(x,y-1)
movd ecx, xmm1			;pobranie warto�ci (x,y-1)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
shufps xmm1, xmm1, 57	;xmm1 <- (x,y-1),(x+3,y-1),(x-3,y),(x-3,y-1)
movd ecx, xmm1			;pobranie warto�ci (x-3,y-1)*maska
add rax, rcx			;dodanie warto�ci do sumy wa�onej
mov rdx, 0				;wyzerowanie m�odszych bit�w iloczynu
div r9					;obliczenie �redniej wa�onej
mov byte ptr[rsi], al	;zapisanie obliczonej warto�ci do tablicy
ret
gaussASM endp

end