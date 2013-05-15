#
#3AC For the Input Code File: tests/test7.c
#
   PROCENTRY        swap
  BEGINFRAME           0
       ALLOC         tmp         INT           4
       PARAM           y         INT           4
       PARAM           x         INT           4
       VALAT       I0002           x
         MOV       I0002         tmp
       VALAT       I0007           y
      ASSIGN       I0007           x
      ASSIGN         tmp           y
    ENDFRAME
     ENDPROC
   PROCENTRY        main
  BEGINFRAME           0
       ALLOC        tarr    INTARRAY           5
       ALLOC         tmp         INT           4
       ALLOC     swapped         INT           4
       ALLOC           i         INT           4
       ALLOC           a         INT           4
       ALLOC           b         INT           4
 IMMEDIATE_I       I0013           5
        ADDR        tarr       I0014
 IMMEDIATE_I       I0016           0
 IMMEDIATE_I       I0017           4
        MULT       I0016       I0017       I0018
         ADD       I0014       I0018       I0019
 IMMEDIATE_I       I0020           5
      ASSIGN       I0020       I0019
        ADDR        tarr       I0022
 IMMEDIATE_I       I0024           1
 IMMEDIATE_I       I0025           4
        MULT       I0024       I0025       I0026
         ADD       I0022       I0026       I0027
 IMMEDIATE_I       I0028           4
      ASSIGN       I0028       I0027
        ADDR        tarr       I0030
 IMMEDIATE_I       I0032           2
 IMMEDIATE_I       I0033           4
        MULT       I0032       I0033       I0034
         ADD       I0030       I0034       I0035
 IMMEDIATE_I       I0036           3
      ASSIGN       I0036       I0035
        ADDR        tarr       I0038
 IMMEDIATE_I       I0040           3
 IMMEDIATE_I       I0041           4
        MULT       I0040       I0041       I0042
         ADD       I0038       I0042       I0043
 IMMEDIATE_I       I0044           2
      ASSIGN       I0044       I0043
        ADDR        tarr       I0046
 IMMEDIATE_I       I0048           4
 IMMEDIATE_I       I0049           4
        MULT       I0048       I0049       I0050
         ADD       I0046       I0050       I0051
 IMMEDIATE_I       I0052           1
      ASSIGN       I0052       I0051
       LABEL       L0000
 IMMEDIATE_I       I0055           0
         MOV       I0055     swapped
 IMMEDIATE_I       I0058           1
         MOV       I0058           i
       LABEL       L0002
 IMMEDIATE_I       I0061           5
          LT           i       I0061       I0062
        BREQ       I0062           0       L0003
        ADDR        tarr       I0064
 IMMEDIATE_I       I0067           1
         SUB       I0067           i       I0068
 IMMEDIATE_I       I0069           4
        MULT       I0068       I0069       I0070
         ADD       I0064       I0070       I0071
       VALAT       I0072       I0071
         MOV       I0072           a
        ADDR        tarr       I0075
 IMMEDIATE_I       I0078           4
        MULT           i       I0078       I0079
         ADD       I0075       I0079       I0080
       VALAT       I0081       I0080
         MOV       I0081           b
          GT           a           b       I0085
        BREQ       I0085           0       L0004
        ADDR        tarr       I0087
 IMMEDIATE_I       I0090           1
         SUB       I0090           i       I0091
 IMMEDIATE_I       I0092           4
        MULT       I0091       I0092       I0093
         ADD       I0087       I0093       I0094
        ADDR        tarr       I0095
 IMMEDIATE_I       I0098           4
        MULT           i       I0098       I0099
         ADD       I0095       I0099       I0100
        FPAR       I0100
        FPAR       I0094
        CALL        swap
 IMMEDIATE_I       I0102           1
         MOV       I0102     swapped
       LABEL       L0004
 IMMEDIATE_I       I0105           1
         ADD       I0105           i       I0106
         MOV       I0106           i
          BR       L0002
       LABEL       L0003
        BREQ     swapped           0       L0001
          BR       L0000
       LABEL       L0001
 IMMEDIATE_I       I0108           0
      RETURN       I0108
    ENDFRAME
     ENDPROC
