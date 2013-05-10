#
#3AC For the Input Code File: tests/test4.c
#
   PROCENTRY        main
       ALLOC           i         INT           4
       ALLOC           a         INT           4
  BEGINFRAME           0
 IMMEDIATE_I       I0001           1
         MOV       I0001           a
 IMMEDIATE_I       I0004           0
         MOV       I0004           i
       LABEL       L0000
 IMMEDIATE_I       I0007          10
          LT           i       I0007       I0008
        BREQ       I0008           0       L0001
  BEGINFRAME           0
 IMMEDIATE_I       I0011           2
         ADD       I0011           a       I0012
         MOV       I0012           a
    ENDFRAME
 IMMEDIATE_I       I0014           1
         ADD       I0014           i       I0015
         MOV       I0015           i
          BR       L0000
       LABEL       L0001
 IMMEDIATE_I       I0017           1
         MOV       I0017           a
       LABEL       L0002
 IMMEDIATE_I       I0020          10
          LT           a       I0020       I0021
        BREQ       I0021           0       L0003
  BEGINFRAME           0
 IMMEDIATE_I       I0024           2
         ADD       I0024           a       I0025
         MOV       I0025           a
    ENDFRAME
          BR       L0002
       LABEL       L0003
 IMMEDIATE_I       I0028           1
         MOV       I0028           a
       LABEL       L0004
  BEGINFRAME           0
 IMMEDIATE_I       I0032           2
         ADD       I0032           a       I0033
         MOV       I0033           a
    ENDFRAME
 IMMEDIATE_I       I0036          10
          LT           a       I0036       I0037
        BREQ       I0037           0       L0005
          BR       L0004
       LABEL       L0005
 IMMEDIATE_I       I0038           0
    ENDFRAME
     ENDPROC
