section .text
    global procesar_gini_asm

procesar_gini_asm:
    ; El float viene en xmm0 (convención x86_64)
    
    ; convertir float a int
    cvttss2si eax, xmm0
    
    ; sumar 1
    add eax, 1
    
    ; devolver resultado en eax
    ret
