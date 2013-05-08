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
         SUB           i           j   I00000014
         MOV   I00000014           k
        MULT           j           i   I00000020
         MOV   I00000020           k
         ADD           i           j   I00000026
         MOV   I00000026           k
         ADD           j           i   I00000031
         MOV   I00000031           k
         SUB           i           j   I00000036
         MOV   I00000036           k
        MULT           j           i   I00000042
         MOV   I00000042           k
         ADD           i           j   I00000048
         MOV   I00000048           k
         ADD           j           i   I00000053
         MOV   I00000053           k
         SUB           i           j   I00000058
         MOV   I00000058           k
        MULT           j           i   I00000064
         MOV   I00000064           k
         ADD           i           j   I00000070
         MOV   I00000070           k
 IMMEDIATE_I   I00000072           0
     ENDPROC
