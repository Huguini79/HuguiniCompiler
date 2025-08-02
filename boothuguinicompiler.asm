; Codigo generado por HuguiniCompiler

ORG 0x7c00
BITS 16

start:
      mov ah, 0x0E
      mov al, 'H'
      int 0x10
      mov al, 'u'
      int 0x10
      mov al, 'g'
      int 0x10
      mov al, 'u'
      int 0x10
      mov al, 'i'
      int 0x10
      mov al, 'n'
      int 0x10
      mov al, 'i'
      int 0x10
      mov al, '7'
      int 0x10
      mov al, '9'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'h'
      int 0x10
      mov al, 'a'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'c'
      int 0x10
      mov al, 'r'
      int 0x10
      mov al, 'e'
      int 0x10
      mov al, 'a'
      int 0x10
      mov al, 'd'
      int 0x10
      mov al, 'o'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'u'
      int 0x10
      mov al, 'n'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'p'
      int 0x10
      mov al, 'r'
      int 0x10
      mov al, 'o'
      int 0x10
      mov al, 'g'
      int 0x10
      mov al, 'r'
      int 0x10
      mov al, 'a'
      int 0x10
      mov al, 'm'
      int 0x10
      mov al, 'a'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'e'
      int 0x10
      mov al, 'n'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'H'
      int 0x10
      mov al, 'C'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'y'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'd'
      int 0x10
      mov al, 'e'
      int 0x10
      mov al, 's'
      int 0x10
      mov al, 'p'
      int 0x10
      mov al, 'u'
      int 0x10
      mov al, 'e'
      int 0x10
      mov al, 's'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 's'
      int 0x10
      mov al, 'e'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'c'
      int 0x10
      mov al, 'o'
      int 0x10
      mov al, 'm'
      int 0x10
      mov al, 'p'
      int 0x10
      mov al, 'i'
      int 0x10
      mov al, 'l'
      int 0x10
      mov al, 'o'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'a'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'e'
      int 0x10
      mov al, 's'
      int 0x10
      mov al, 't'
      int 0x10
      mov al, 'e'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, 'b'
      int 0x10
      mov al, 'o'
      int 0x10
      mov al, 'o'
      int 0x10
      mov al, 't'
      int 0x10
      mov al, 'l'
      int 0x10
      mov al, 'o'
      int 0x10
      mov al, 'a'
      int 0x10
      mov al, 'd'
      int 0x10
      mov al, 'e'
      int 0x10
      mov al, 'r'
      int 0x10
      mov al, ' '
      int 0x10
      mov al, ':'
      int 0x10
      mov al, ')'
      int 0x10

times 510 - ($ - $$) db 0
dw 0xAA55