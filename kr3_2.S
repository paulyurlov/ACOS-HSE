процесс:
        push    %ebp
        mov     %esp, %ebp
        mov     %edi, -24(%ebp)
        movl    %esi, -28(%ebp)
        mov     %edx, -40(%ebp)
        movl    -28(%ebp), %eax
        movl    %eax, -4(%ebp)
        movl    -4(%ebp), %edx
        movl    %edx, %eax
        addl    %eax, %eax
        addl    %edx, %eax
        movl    %eax, -4(%ebp)
        movl    -28(%ebp), %edx
        movl    %edx, %eax
        addl    %eax, %eax
        addl    %edx, %eax
        cmpl    %eax, -4(%ebp)
        je      .L2
        movl    $1, %eax
        jmp     .L3
.L2:
        mov     -24(%ebp), %eax
        movzbl  (%eax), %eax
        movb    %al, -5(%ebp)
        salb    -5(%ebp)
        movzbl  -5(%ebp), %edx
        mov     -24(%ebp), %eax
        movzbl  (%eax), %eax
        movsbl  %al, %eax
        addl    %eax, %eax
        cmpl    %eax, %edx
        je      .L4
        movl    $2, %eax
        jmp     .L3
.L4:
        movzbl  -5(%ebp), %eax
        movl    -4(%ebp), %edx
        movl    %edx, %ecx
        subl    %eax, %ecx
        movl    -28(%ebp), %edx
        movl    %edx, %eax
        addl    %eax, %eax
        addl    %eax, %edx
        mov     -24(%ebp), %eax
        movzbl  (%eax), %eax
        movsbl  %al, %eax
        addl    %eax, %eax
        subl    %eax, %edx
        movl    %edx, %eax
        cmpl    %eax, %ecx
        je      .L5
        movl    $3, %eax
        jmp     .L3
.L5:
        movl    -28(%ebp), %eax
        movl    %eax, %edx
        movl    %edx, %eax
        addl    %eax, %eax
        addl    %eax, %edx
        mov     -24(%ebp), %eax
        movzbl  (%eax), %eax
        addl    %eax, %eax
        subl    %eax, %edx
        movl    %edx, %eax
        movl    %eax, %edx
        mov    -40(%ebp), %eax
        movb    %dl, (%eax)
        movl    $0, %eax
.L3:
        pop     %ebp
        ret