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

open('win32_trampoline_vc.asm', 'w') do |fd|

  fd.write <<EOS
TITLE win32_trampoline_masm.asm
.686P
.model flat

extern	_ocidump_is_initialized:dword
extern  _ocidump_init:near
extern  _ocidump_unresolved_symbol:near
EOS

  trampoline_funcs.each do |name|
    fd.write <<EOS
extern	_ocidump_#{name}:dword
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
_#{name} proc near
	cmp	_ocidump_is_initialized, 0
	jne	initialized
	call	_ocidump_init
initialized:
	cmp	_ocidump_#{name}, 0
	jne	symbol_is_resolved
	push	offset #{name}_name
	call	_ocidump_unresolved_symbol
symbol_is_resolved:
	jmp	_ocidump_#{name}
_#{name} endp
;
EOS
  end
  fd.write <<EOS
_TEXT	ENDS
END
EOS
end
