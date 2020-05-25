        .text
        .global main

main:
        call    readi32
        mov     %eax, %ebx
        cmp     $0, %eax
        jge     supe
        jl      fin

supe:
        mov     %ebx, %eax
        dec     %ebx
        call    writei32
        call    nl
        cmp     $0, %ebx
        jge     supe

fin:
        call    finish
