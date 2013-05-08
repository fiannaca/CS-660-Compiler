#
#3AC For the Input Code File: tests/test3.c
#
   PROCENTRY        main
       ALLOC           a         INT           4
 IMMEDIATE_I   I00000001           1
         MOV   I00000001           a
 IMMEDIATE_I   I00000004           2
          EQ   I00000004           a   I00000005
        BREQ   I00000005           0   L00000000
 IMMEDIATE_I   I00000007           0
         MOV   I00000007           a
          BR   L00000001
       LABEL   L00000000
 IMMEDIATE_I   I00000010           1
         MOV   I00000010           a
       LABEL   L00000001
 IMMEDIATE_I   I00000012           0
     ENDPROC
