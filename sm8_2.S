        .text
        .global process

process:
        movl    A, %eax
        imull   B
        movl    %eax, R
        movl    C, %eax
        imull   D
        subl    %eax, R
        ret


        .data
A:      .int    0
B:      .int    0
C:      .int    0
D:      .int    0
R:      .int    0

        .global A, B, C, D, R
