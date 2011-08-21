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

EOS

  trampoline_funcs.each do |name|
    fd.write <<EOS
FARPROC ocidump_#{name};
EOS
  end

  fd.write <<EOS

void ocidump_init_win32_trampoline(HMODULE hMod)
{
EOS
  trampoline_funcs.each do |name|
    fd.write <<EOS
    ocidump_#{name} = GetProcAddress(hMod, "#{name}");
EOS
  end
  fd.write <<EOS
}
EOS
end

open("win32_trampoline_vc32.asm", 'w') do |fd|

  fd.write <<EOS
TITLE win32_trampoline_masm.asm
.686P
.model flat

EXTERN	_ocidump_is_initialized:DWORD
EXTERN	_ocidump_init:PROC
EXTERN	_ocidump_unresolved_symbol:PROC
EOS

  trampoline_funcs.each do |name|
    fd.write <<EOS
EXTERN	_ocidump_#{name}:DWORD
EOS
  end

  fd.write <<EOS

.CONST
EOS
  trampoline_funcs.each do |name|
    fd.write <<EOS
#{name}_name	DB	'#{name}', 00H
EOS
  end

  fd.write <<EOS

.CODE
EOS
  trampoline_funcs.each do |name|
    fd.write <<EOS
_#{name} PROC
	cmp	_ocidump_is_initialized, 0
	jne	initialized
	call	_ocidump_init
initialized:
	cmp	_ocidump_#{name}, 0
	jne	symbol_is_resolved
	push	OFFSET #{name}_name
	call	_ocidump_unresolved_symbol
symbol_is_resolved:
	jmp	_ocidump_#{name}
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
TITLE win32_trampoline_masm.asm
EXTERN	ocidump_is_initialized:DWORD
EXTERN	ocidump_init:PROC
EXTERN	ocidump_unresolved_symbol:PROC
EOS

  trampoline_funcs.each do |name|
    fd.write <<EOS
EXTERN	ocidump_#{name}:QWORD
EOS
  end

  fd.write <<EOS

.CONST
EOS
  trampoline_funcs.each do |name|
    fd.write <<EOS
#{name}_name	DB	'#{name}', 00H
EOS
  end

  fd.write <<EOS
.CODE

; Save registers which may be used for function arguments,
; call ocidump_init, and restore them.
call_ocidump_init PROC
	sub	rsp, 128
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
	add	rsp, 128
	ret	0
call_ocidump_init ENDP
;
EOS

  trampoline_funcs.each do |name|
    fd.write <<EOS
#{name} PROC
	cmp	ocidump_is_initialized, 0
	jne	initialized
	call	call_ocidump_init
initialized:
	cmp	ocidump_#{name}, 0
	jne	symbol_is_resolved
	sub	rsp, 40
	lea	rcx, OFFSET #{name}_name
	call	ocidump_unresolved_symbol ; noreturn
symbol_is_resolved:
	jmp	ocidump_#{name}
#{name} ENDP
;
EOS
  end
  fd.write <<EOS
END
EOS
end
