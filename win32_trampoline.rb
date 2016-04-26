require 'yaml'

if defined? YAML::ENGINE
  YAML::ENGINE.yamler = 'syck'
end

hooked_funcs = []
YAML.load(open(File.dirname(__FILE__) + '/ocifunc.yml')).each do |key, val|
  hooked_funcs << key
end

trampoline_funcs = []
IO.foreach(File.dirname(__FILE__) + '/ocidump.def') do |line|
  line.chomp!
  trampoline_funcs << line if line != 'EXPORTS'
end

trampoline_funcs -= hooked_funcs

open('win32_trampoline.c', 'w') do |fd|
  fd.write <<EOS
/* This file was generaed by #{__FILE__} */
#include <windows.h>
#include "ocidump.h"

trampoline_func_t trampoline_funcs[] = {
EOS

  trampoline_funcs.each do |name|
    fd.write <<EOS
    {NULL, "#{name}"},
EOS
  end

  fd.write <<EOS
    {NULL, NULL},
};
EOS
end

open("win32_trampoline_vc32.asm", 'w') do |fd|

  fd.write <<EOS
TITLE win32_trampoline_vc32.asm
.686P
.model flat

EXTERN	_ocidump_unresolved_symbol:PROC
EXTERN	_ocidump_init:PROC
EXTERN	_trampoline_funcs:DWORD

.CODE

_call_unresolved_symbol PROC
	sub	esp, 4
	call	_ocidump_unresolved_symbol ; noreturn
_call_unresolved_symbol ENDP

_call_ocidump_init PROC
	sub	esp, 4
	push	ecx
	push	edx
	call	_ocidump_init
	pop	edx
	pop	ecx
	pop	eax
	jmp	DWORD PTR [_trampoline_funcs+eax*8]
_call_ocidump_init ENDP

EOS

  trampoline_funcs.each_with_index do |name, index|
    fd.write <<EOS
_#{name} PROC
	mov	DWORD PTR [esp-4], #{index}
	jmp	DWORD PTR [_trampoline_funcs+#{index*8}]
_#{name} ENDP
;
EOS
  end

  fd.write <<EOS
END
EOS
end


open("win32_trampoline_vc64.asm", 'w') do |fd|

  fd.write <<EOS
TITLE win32_trampoline_vc64.asm
EXTERN	ocidump_unresolved_symbol:PROC
EXTERN	ocidump_init:PROC
EXTERN	trampoline_funcs:QWORD

.CODE

call_unresolved_symbol PROC
	mov	rcx, QWORD PTR [rsp-8]
	jmp	ocidump_unresolved_symbol ; noreturn
call_unresolved_symbol ENDP

; Save registers which may be used for function arguments,
; call ocidump_init, and restore them.
call_ocidump_init PROC
	sub	rsp, 136
	mov	QWORD PTR [rsp+32], rcx
	mov	QWORD PTR [rsp+40], rdx
	mov	QWORD PTR [rsp+48], r8
	mov	QWORD PTR [rsp+56], r9
	movaps	XMMWORD PTR [rsp+64], xmm0
	movaps	XMMWORD PTR [rsp+80], xmm1
	movaps	XMMWORD PTR [rsp+96], xmm2
	movaps	XMMWORD PTR [rsp+112], xmm3
	call	ocidump_init
	mov	rcx, QWORD PTR [rsp+32]
	mov	rdx, QWORD PTR [rsp+40]
	mov	r8, QWORD PTR [rsp+48]
	mov	r9, QWORD PTR [rsp+56]
	movaps	xmm0, XMMWORD PTR [rsp+64]
	movaps	xmm1, XMMWORD PTR [rsp+80]
	movaps	xmm2, XMMWORD PTR [rsp+96]
	movaps	xmm3, XMMWORD PTR [rsp+112]
	add	rsp, 136
	mov	rax, QWORD PTR [rsp-8]
	add	rax, rax
	lea	r10, [trampoline_funcs]
	jmp	QWORD PTR [r10+rax*8]
call_ocidump_init ENDP
;

EOS

  trampoline_funcs.each_with_index do |name, index|
    fd.write <<EOS
#{name} PROC
	mov	QWORD PTR [rsp-8], #{index}
	lea	rax, [trampoline_funcs]
	jmp	QWORD PTR [rax+#{index*16}]
#{name} ENDP
;
EOS
  end
  fd.write <<EOS
END
EOS
end
