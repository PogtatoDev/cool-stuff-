.intel_syntax noprefix
.global _start
.text
_start:
  mov rax, 1
  mov rdi, 1
  lea rsi, helloguyswhatsup
  mov rdx, 14
  syscall

  mov rax, 60
  xor rdi, rdi
  syscall

.data
helloguyswhatsup:
		.asciz  "yeah"
