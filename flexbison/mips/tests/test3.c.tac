#
#3AC For the Input Code File: tests/test3.c
#
   PROCENTRY        main
  BEGINFRAME           0
       ALLOC           a         INT           4
 IMMEDIATE_I       I0001           1
         MOV       I0001           a
 IMMEDIATE_I       I0004           4
 IMMEDIATE_I       I0005           5
         ADD       I0005       I0004       I0006
 IMMEDIATE_I       I0007           2
 IMMEDIATE_I       I0008           3
         ADD       I0008       I0007       I0009
        MULT       I0009       I0006       I0011
         MOV       I0011           a
 IMMEDIATE_I       I0014           2
          EQ       I0014           a       I0015
        BREQ       I0015           0       L0000
 IMMEDIATE_I       I0017           0
         MOV       I0017           a
          BR       L0001
       LABEL       L0000
 IMMEDIATE_I       I0020           1
         NEG       I0020       I0021
         MOV       I0021           a
       LABEL       L0001
 IMMEDIATE_I       I0023           0
      RETURN       I0023
    ENDFRAME
     ENDPROC
