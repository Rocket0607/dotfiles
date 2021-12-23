global _start

section .data
old_message db "You are old", 0x0a
old_message_len equ $ - old_message

not_old_message db "You are not old", 0x0a
not_old_message_len equ $ - not_old_message

section .text
_start:
mov ecx, 30
cmp ecx, 60
jg old

mov eax, 4
mov ebx, 1
mov ecx, not_old_message
mov edx, not_old_message_len
int 0x80

mov eax, 1
mov ebx, 0
int 0x80

old:
mov eax, 4
mov ebx, 1
mov ecx, old_message
mov edx, old_message_len
int 0x80
mov eax, 1
mov ebx, 0
int 0x80
