#
#3AC For the Input Code File: tests/test3.c
#
   PROCENTRY        main
       ALLOC           a         INT           4
  BEGINFRAME           0
 IMMEDIATE_I       I0001           1
         MOV       I0001           a
 IMMEDIATE_I       I0004           2
          EQ       I0004           a       I0005
        BREQ       I0005           0       L0000
  BEGINFRAME           0
 IMMEDIATE_I       I0007           0
         MOV       I0007           a
    ENDFRAME
          BR       L0001
       LABEL       L0000
  BEGINFRAME           0
 IMMEDIATE_I       I0010           3
         MOV       I0010           a
    ENDFRAME
       LABEL       L0001
 IMMEDIATE_I       I0012           0
    ENDFRAME
     ENDPROC
