#
#3AC For the Input Code File: tests/test6.c
#
   PROCENTRY        main
  BEGINFRAME           0
       ALLOC     swapped         INT           4
       ALLOC        tarr    INTARRAY           5
       ALLOC         tmp         INT           4
       ALLOC           i         INT           4
       ALLOC           a         INT           4
       ALLOC           b         INT           4
 IMMEDIATE_I       I0000           5
        ADDR        tarr       I0001
 IMMEDIATE_I       I0003           0
 IMMEDIATE_I       I0004           4
        MULT       I0003       I0004       I0005
         ADD       I0001       I0005       I0006
 IMMEDIATE_I       I0007           5
      ASSIGN       I0007       I0006
        ADDR        tarr       I0009
 IMMEDIATE_I       I0011           1
 IMMEDIATE_I       I0012           4
        MULT       I0011       I0012       I0013
         ADD       I0009       I0013       I0014
 IMMEDIATE_I       I0015           4
      ASSIGN       I0015       I0014
        ADDR        tarr       I0017
 IMMEDIATE_I       I0019           2
 IMMEDIATE_I       I0020           4
        MULT       I0019       I0020       I0021
         ADD       I0017       I0021       I0022
 IMMEDIATE_I       I0023           3
      ASSIGN       I0023       I0022
        ADDR        tarr       I0025
 IMMEDIATE_I       I0027           3
 IMMEDIATE_I       I0028           4
        MULT       I0027       I0028       I0029
         ADD       I0025       I0029       I0030
 IMMEDIATE_I       I0031           2
      ASSIGN       I0031       I0030
        ADDR        tarr       I0033
 IMMEDIATE_I       I0035           4
 IMMEDIATE_I       I0036           4
        MULT       I0035       I0036       I0037
         ADD       I0033       I0037       I0038
 IMMEDIATE_I       I0039           1
      ASSIGN       I0039       I0038
       LABEL       L0000
 IMMEDIATE_I       I0042           0
         MOV       I0042     swapped
 IMMEDIATE_I       I0045           1
         MOV       I0045           i
       LABEL       L0002
 IMMEDIATE_I       I0048           5
          LT           i       I0048       I0049
        BREQ       I0049           0       L0003
        ADDR        tarr       I0051
 IMMEDIATE_I       I0054           1
         SUB       I0054           i       I0055
 IMMEDIATE_I       I0056           4
        MULT       I0055       I0056       I0057
         ADD       I0051       I0057       I0058
       VALAT       I0059       I0058
         MOV       I0059           a
        ADDR        tarr       I0062
 IMMEDIATE_I       I0065           4
        MULT           i       I0065       I0066
         ADD       I0062       I0066       I0067
       VALAT       I0068       I0067
         MOV       I0068           b
          GT           a           b       I0072
        BREQ       I0072           0       L0004
        ADDR        tarr       I0074
 IMMEDIATE_I       I0077           1
         SUB       I0077           i       I0078
 IMMEDIATE_I       I0079           4
        MULT       I0078       I0079       I0080
         ADD       I0074       I0080       I0081
       VALAT       I0082       I0081
         MOV       I0082         tmp
        ADDR        tarr       I0084
 IMMEDIATE_I       I0087           1
         SUB       I0087           i       I0088
 IMMEDIATE_I       I0089           4
        MULT       I0088       I0089       I0090
         ADD       I0084       I0090       I0091
        ADDR        tarr       I0092
 IMMEDIATE_I       I0095           4
        MULT           i       I0095       I0096
         ADD       I0092       I0096       I0097
       VALAT       I0098       I0097
      ASSIGN       I0098       I0091
        ADDR        tarr       I0100
 IMMEDIATE_I       I0103           4
        MULT           i       I0103       I0104
         ADD       I0100       I0104       I0105
      ASSIGN         tmp       I0105
 IMMEDIATE_I       I0109           1
         MOV       I0109     swapped
       LABEL       L0004
 IMMEDIATE_I       I0112           1
         ADD       I0112           i       I0113
         MOV       I0113           i
          BR       L0002
       LABEL       L0003
 IMMEDIATE_I       I0115           1
          EQ       I0115     swapped       I0116
        BREQ       I0116           0       L0001
          BR       L0000
       LABEL       L0001
 IMMEDIATE_I       I0117           0
      RETURN       I0117
    ENDFRAME
     ENDPROC
