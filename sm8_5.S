        .text
        .global main

main:
        call    readi32
        movl    %eax, %ebx
        jc      fini
        testl   $1, %ebx
        jz      even
        jnz     odd

even:
        addl    %ebx, seven
        jmp     main

odd:
        addl    %ebx, sodd
        jmp     main

fini:
        movl    seven, %eax
        call    writei32
        call    nl
        movl    sodd, %eax
        call    writei32
        call    nl
        call    finish

        .data
sodd:   .int    0
seven:  .int    0