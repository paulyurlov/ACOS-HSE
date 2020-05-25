        .text
        .global mystrcmp

mystrcmp:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $16, %esp
        movl    8(%ebp), %eax
        movl    %eax, -4(%ebp)
        movl    12(%ebp), %eax
        movl    %eax, -8(%ebp)
while:
        movl    -4(%ebp), %eax
        movzbl  (%eax), %edx
        movl    -8(%ebp), %eax
        movzbl  (%eax), %eax
        cmpb    %al, %dl
        jne     fin

endcheck:
        movl    -4(%ebp), %eax
        movzbl  (%eax), %eax
        testb   %al, %al
        jne     add
        jmp     fin
add:
        addl    $1, -4(%ebp)
        addl    $1, -8(%ebp)
        jmp     while
fin:
        movl    -4(%ebp), %eax
        movzbl  (%eax), %eax
        movzbl  %al, %edx
        movl    -8(%ebp), %eax
        movzbl  (%eax), %eax
        movzbl  %al, %eax
        subl    %eax, %edx
        movl    %edx, %eax
        leave
        ret