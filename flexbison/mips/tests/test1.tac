#
#3AC For the Input Code File: tests/test1.c
#
   PROCENTRY        main
       ALLOC           j         INT           4
       ALLOC           k         INT           4
       ALLOC           i         INT           4
  BEGINFRAME           0
 IMMEDIATE_I       I0001           1
         MOV       I0001           i
 IMMEDIATE_I       I0004           2
         MOV       I0004           j
         ADD           j           i       I0009
         MOV       I0009           k
         SUB           i           j       I0014
         MOV       I0014           k
        MULT           j           i       I0020
         MOV       I0020           k
         DIV           i           j       I0026
         MOV       I0026           k
 IMMEDIATE_I       I0029           1
 IMMEDIATE_I       I0030           2
         ADD       I0030       I0029       I0031
 IMMEDIATE_I       I0032           3
 IMMEDIATE_I       I0033           4
         ADD       I0033       I0032       I0034
         ADD       I0034       I0031       I0035
 IMMEDIATE_I       I0036           5
 IMMEDIATE_I       I0037           6
         ADD       I0037       I0036       I0038
 IMMEDIATE_I       I0039           7
 IMMEDIATE_I       I0040           8
         ADD       I0040       I0039       I0041
         ADD       I0041       I0038       I0042
         ADD       I0042       I0035       I0043
 IMMEDIATE_I       I0044           9
 IMMEDIATE_I       I0045          10
         ADD       I0045       I0044       I0046
         ADD       I0046       I0043       I0047
         MOV       I0047           k
 IMMEDIATE_I       I0049           0
    ENDFRAME
     ENDPROC
