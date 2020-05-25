        .text
        .global process

process:
        pushl   %ebp
        movl    %esp, %ebp        
        movl    %edx, %ecx
        movl    A, %eax
        mull    %ecx
        mull    %ecx
        pushl   %eax
        movl    $5, %eax
        mull    %ecx
        mull    B
        pushl   %eax
        movl    $2, %eax
        mull    C
        movl    -4(%ebp), %edx
        subl    -8(%ebp), %edx
        addl    %eax, %edx
        addl    $8, %esp
        popl    %ebp
        ret

        .data
A:      .int    1
B:      .int    2
C:      .int    3

        .global A, B, C