#
#3AC For the Input Code File: tests/test4.c
#
   PROCENTRY        main
  BEGINFRAME           0
       ALLOC           i         INT           4
       ALLOC           a         INT           4
 IMMEDIATE_I       I0001           1
         MOV       I0001           a
 IMMEDIATE_I       I0004           0
         MOV       I0004           i
       LABEL       L0000
 IMMEDIATE_I       I0007          10
          LT           i       I0007       I0008
        BREQ       I0008           0       L0001
 IMMEDIATE_I       I0011           2
         ADD       I0011           a       I0012
         MOV       I0012           a
 IMMEDIATE_I       I0015           1
         ADD       I0015           i       I0016
         MOV       I0016           i
          BR       L0000
       LABEL       L0001
 IMMEDIATE_I       I0018           1
         MOV       I0018           a
       LABEL       L0002
 IMMEDIATE_I       I0021          10
          LT           a       I0021       I0022
        BREQ       I0022           0       L0003
 IMMEDIATE_I       I0025           2
         ADD       I0025           a       I0026
         MOV       I0026           a
          BR       L0002
       LABEL       L0003
 IMMEDIATE_I       I0029           1
         MOV       I0029           a
       LABEL       L0004
 IMMEDIATE_I       I0033           2
         ADD       I0033           a       I0034
         MOV       I0034           a
 IMMEDIATE_I       I0037          10
          LT           a       I0037       I0038
        BREQ       I0038           0       L0005
          BR       L0004
       LABEL       L0005
 IMMEDIATE_I       I0039           0
      RETURN       I0039
    ENDFRAME
     ENDPROC
