#
#3AC For the Input Code File: tests/test2.c
#
   PROCENTRY        main
       ALLOC           a    INTARRAY           3
  BEGINFRAME           0
 IMMEDIATE_I       I0000           3
        ADDR           a       I0001
 IMMEDIATE_I       I0004           0
 IMMEDIATE_I       I0005           4
        MULT       I0004       I0005       I0006
         ADD       I0001       I0006       I0007
 IMMEDIATE_I       I0008           3
      ASSIGN       I0008       I0007
        ADDR           a       I0010
 IMMEDIATE_I       I0013           1
 IMMEDIATE_I       I0014           4
        MULT       I0013       I0014       I0015
         ADD       I0010       I0015       I0016
 IMMEDIATE_I       I0017           2
      ASSIGN       I0017       I0016
        ADDR           a       I0019
 IMMEDIATE_I       I0022           2
 IMMEDIATE_I       I0023           4
        MULT       I0022       I0023       I0024
         ADD       I0019       I0024       I0025
 IMMEDIATE_I       I0026           1
      ASSIGN       I0026       I0025
 IMMEDIATE_I       I0028           0
    ENDFRAME
     ENDPROC
