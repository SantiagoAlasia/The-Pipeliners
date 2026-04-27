[org 0x7C00]
bits 16

start:
    cli

    ; cargar GDT
    lgdt [gdt_descriptor]

    ; activar modo protegido (bit PE en CR0)
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; salto largo para limpiar pipeline
    jmp 0x08:protected_mode

; ---------------------
; GDT
; ---------------------

gdt_start:
    dq 0x0000000000000000     ; null

    ; code segment
    dq 0x00CF9A000000FFFF

    ; data segment
    dq 0x00CF92000000FFFF

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

; ---------------------
; MODO PROTEGIDO
; ---------------------

bits 32
protected_mode:

    mov ax, 0x10   ; selector de datos
    mov ds, ax
    mov es, ax
    mov ss, ax

    mov esp, 0x90000

hang:
    hlt
    jmp hang

; ---------------------
; BOOT SIGNATURE
; ---------------------

times 510-($-$$) db 0
dw 0xAA55