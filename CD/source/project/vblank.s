   .align   2 
   .global   WaitVblank 
   .type   WaitVblank,function 
WaitVblank: 
   @ args = 0, pretend = 0, frame = 0 
   @ frame_needed = 1, current_function_anonymous_args = 0 
   mov   ip, sp 
   stmfd   sp!, {fp, ip, lr, pc} 
   sub   fp, ip, #4 
   mov   r0, r0   @ nop 
.L3: 
   mov   r3, #67108864 
   add   r3, r3, #6 
   ldrh   r3, [r3, #0]   @ movhi 
   mov   r3, r3, asl #16 
   mov   r3, r3, lsr #16 
   cmp   r3, #159 
   bls   .L3 
   ldmea   fp, {fp, sp, pc} 
.Lfe2: 
   .size   WaitVblank,.Lfe2-WaitVblank 
