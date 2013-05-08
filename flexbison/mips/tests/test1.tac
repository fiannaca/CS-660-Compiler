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
         DIV           i           j   I00000026
         MOV   I00000026           k
 IMMEDIATE_I   I00000029           1
 IMMEDIATE_I   I00000030           2
         ADD   I00000030   I00000029   I00000031
 IMMEDIATE_I   I00000032           3
 IMMEDIATE_I   I00000033           4
         ADD   I00000033   I00000032   I00000034
         ADD   I00000034   I00000031   I00000035
 IMMEDIATE_I   I00000036           5
 IMMEDIATE_I   I00000037           6
         ADD   I00000037   I00000036   I00000038
         ADD   I00000038   I00000035   I00000039
 IMMEDIATE_I   I00000040           7
 IMMEDIATE_I   I00000041           8
         ADD   I00000041   I00000040   I00000042
         ADD   I00000042   I00000039   I00000043
 IMMEDIATE_I   I00000044           9
 IMMEDIATE_I   I00000045          10
         ADD   I00000045   I00000044   I00000046
         ADD   I00000046   I00000043   I00000047
         MOV   I00000047           k
 IMMEDIATE_I   I00000049           0
     ENDPROC
