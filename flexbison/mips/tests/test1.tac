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
         REM           i           j       I0032
         MOV       I0032           k
 IMMEDIATE_I       I0035           1
 IMMEDIATE_I       I0036           2
         ADD       I0036       I0035       I0037
 IMMEDIATE_I       I0038           3
 IMMEDIATE_I       I0039           4
         ADD       I0039       I0038       I0040
         ADD       I0040       I0037       I0041
 IMMEDIATE_I       I0042           5
 IMMEDIATE_I       I0043           6
         ADD       I0043       I0042       I0044
 IMMEDIATE_I       I0045           7
 IMMEDIATE_I       I0046           8
         ADD       I0046       I0045       I0047
         ADD       I0047       I0044       I0048
         ADD       I0048       I0041       I0049
 IMMEDIATE_I       I0050           9
 IMMEDIATE_I       I0051          10
         ADD       I0051       I0050       I0052
         ADD       I0052       I0049       I0053
         MOV       I0053           k
 IMMEDIATE_I       I0055           0
    ENDFRAME
     ENDPROC
