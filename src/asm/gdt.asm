; GDT stuff
gdtr dw 0 ; for limit storage
     dd 0 ; for base storage

setGdt:
   mov   ax, [esp + 4]
   mov   [gdtr], ax
   mov   eax, [esp + 8]
   mov   [gdtr + 2], eax
   lgdt  [gdtr]
   ret
