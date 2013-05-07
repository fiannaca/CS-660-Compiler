#
#3AC For the Input Code File: tests/test1.c
#
   PROCENTRY        main
       ALLOC           j         INT           4
       ALLOC           k         INT           4
       ALLOC           i         INT           4
 IMMEDIATE_I   I00000001           1
         MOV   I00000001           i
 IMMEDIATE_I   I00000004           2
         MOV   I00000004           j
         ADD           j           i   I00000009
         MOV   I00000009           k
 IMMEDIATE_I   I00000011           0
     ENDPROC
