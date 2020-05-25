        .text
        .global satsum

satsum:
        pushl   %ebp
        movl    %esp, %ebp
        movl    8(%ebp), %edx
        addl    12(%ebp), %edx
        jc      overflow
        jnc     fin

fin:    
        movl    %edx, %eax
        popl    %ebp
        ret

overflow:
        movl    max,  %eax
        popl    %ebp
        ret
  
        .section        .rodata

max:    .int    4294967295