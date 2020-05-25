        .text
        .global main

main:
        call    readi32
        jc      fini
        add     %eax, sum
        jno     main

overflow:
        adcl    $0, max_t
        movl    max_t, %eax
        call    writei32
        call    nl
        call    finish

fini:
        mov     sum, %eax
        call    writei32
        call    nl
        call    finish

        .data
sum:    .int    0
max_t:  .int    2147483647