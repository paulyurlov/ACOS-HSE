        .text
        .global forward$args

forward$args:
        push    %ebp
        movl    %esp, %ebp
        subl    $8, %esp
        movl    12(%ebp), %eax
        movl    %eax, -8(%ebp)
        movl    16(%ebp), %eax
        movl    %eax, -4(%ebp)
        movl    8(%ebp), %eax
        cltd
        pushl   -8(%ebp)
        pushl   20(%ebp)
        pushl   %edx
        pushl   %eax
        pushl   %ecx
        call    process
        addl    $20, %esp
        negl    %eax
        leave
        ret