#
#3AC For the Input Code File: tests/test2.c
#
   PROCENTRY        main
  BEGINFRAME           0
       ALLOC           b    INTARRAY           6
       ALLOC        temp         INT           4
       ALLOC           a    INTARRAY           3
 IMMEDIATE_I       I0000           3
 IMMEDIATE_I       I0001           2
 IMMEDIATE_I       I0002           3
        ADDR           a       I0003
 IMMEDIATE_I       I0005           0
 IMMEDIATE_I       I0006           4
        MULT       I0005       I0006       I0007
         ADD       I0003       I0007       I0008
 IMMEDIATE_I       I0009           3
      ASSIGN       I0009       I0008
        ADDR           a       I0011
 IMMEDIATE_I       I0013           1
 IMMEDIATE_I       I0014           4
        MULT       I0013       I0014       I0015
         ADD       I0011       I0015       I0016
 IMMEDIATE_I       I0017           2
      ASSIGN       I0017       I0016
        ADDR           a       I0019
 IMMEDIATE_I       I0021           2
 IMMEDIATE_I       I0022           4
        MULT       I0021       I0022       I0023
         ADD       I0019       I0023       I0024
 IMMEDIATE_I       I0025           1
      ASSIGN       I0025       I0024
        ADDR           b       I0027
 IMMEDIATE_I       I0029           0
 IMMEDIATE_I       I0030          12
        MULT       I0029       I0030       I0031
         ADD       I0027       I0031       I0032
 IMMEDIATE_I       I0033           0
 IMMEDIATE_I       I0034           4
        MULT       I0033       I0034       I0035
         ADD       I0032       I0035       I0036
 IMMEDIATE_I       I0037           4
      ASSIGN       I0037       I0036
        ADDR           b       I0039
 IMMEDIATE_I       I0041           0
 IMMEDIATE_I       I0042          12
        MULT       I0041       I0042       I0043
         ADD       I0039       I0043       I0044
 IMMEDIATE_I       I0045           1
 IMMEDIATE_I       I0046           4
        MULT       I0045       I0046       I0047
         ADD       I0044       I0047       I0048
 IMMEDIATE_I       I0049           4
      ASSIGN       I0049       I0048
        ADDR           b       I0051
 IMMEDIATE_I       I0053           0
 IMMEDIATE_I       I0054          12
        MULT       I0053       I0054       I0055
         ADD       I0051       I0055       I0056
 IMMEDIATE_I       I0057           2
 IMMEDIATE_I       I0058           4
        MULT       I0057       I0058       I0059
         ADD       I0056       I0059       I0060
 IMMEDIATE_I       I0061           4
      ASSIGN       I0061       I0060
        ADDR           b       I0063
 IMMEDIATE_I       I0065           1
 IMMEDIATE_I       I0066          12
        MULT       I0065       I0066       I0067
         ADD       I0063       I0067       I0068
 IMMEDIATE_I       I0069           0
 IMMEDIATE_I       I0070           4
        MULT       I0069       I0070       I0071
         ADD       I0068       I0071       I0072
 IMMEDIATE_I       I0073           4
      ASSIGN       I0073       I0072
        ADDR           b       I0075
 IMMEDIATE_I       I0077           1
 IMMEDIATE_I       I0078          12
        MULT       I0077       I0078       I0079
         ADD       I0075       I0079       I0080
 IMMEDIATE_I       I0081           1
 IMMEDIATE_I       I0082           4
        MULT       I0081       I0082       I0083
         ADD       I0080       I0083       I0084
 IMMEDIATE_I       I0085           4
      ASSIGN       I0085       I0084
        ADDR           b       I0087
 IMMEDIATE_I       I0089           1
 IMMEDIATE_I       I0090          12
        MULT       I0089       I0090       I0091
         ADD       I0087       I0091       I0092
 IMMEDIATE_I       I0093           2
 IMMEDIATE_I       I0094           4
        MULT       I0093       I0094       I0095
         ADD       I0092       I0095       I0096
 IMMEDIATE_I       I0097           4
      ASSIGN       I0097       I0096
 IMMEDIATE_I       I0100           3
         MOV       I0100        temp
        ADDR           a       I0102
 IMMEDIATE_I       I0105           2
         SUB       I0105        temp       I0106
 IMMEDIATE_I       I0107           4
        MULT       I0106       I0107       I0108
         ADD       I0102       I0108       I0109
 IMMEDIATE_I       I0110           3
      ASSIGN       I0110       I0109
        ADDR           a       I0112
 IMMEDIATE_I       I0115           1
         SUB       I0115        temp       I0116
 IMMEDIATE_I       I0117           4
        MULT       I0116       I0117       I0118
         ADD       I0112       I0118       I0119
 IMMEDIATE_I       I0120           3
      ASSIGN       I0120       I0119
 IMMEDIATE_I       I0123           2
         MOV       I0123        temp
        ADDR           b       I0125
 IMMEDIATE_I       I0128           1
         SUB       I0128        temp       I0129
 IMMEDIATE_I       I0130          12
        MULT       I0129       I0130       I0131
         ADD       I0125       I0131       I0132
         SUB        temp        temp       I0135
 IMMEDIATE_I       I0136           4
        MULT       I0135       I0136       I0137
         ADD       I0132       I0137       I0138
        ADDR           a       I0139
 IMMEDIATE_I       I0142           4
        MULT        temp       I0142       I0143
         ADD       I0139       I0143       I0144
       VALAT       I0145       I0144
      ASSIGN       I0145       I0138
        ADDR           b       I0147
 IMMEDIATE_I       I0150           1
         SUB       I0150        temp       I0151
 IMMEDIATE_I       I0152          12
        MULT       I0151       I0152       I0153
         ADD       I0147       I0153       I0154
 IMMEDIATE_I       I0156           1
         SUB       I0156        temp       I0157
 IMMEDIATE_I       I0158           4
        MULT       I0157       I0158       I0159
         ADD       I0154       I0159       I0160
        ADDR           a       I0161
 IMMEDIATE_I       I0164           4
        MULT        temp       I0164       I0165
         ADD       I0161       I0165       I0166
       VALAT       I0167       I0166
      ASSIGN       I0167       I0160
        ADDR           b       I0169
 IMMEDIATE_I       I0172           1
         SUB       I0172        temp       I0173
 IMMEDIATE_I       I0174          12
        MULT       I0173       I0174       I0175
         ADD       I0169       I0175       I0176
 IMMEDIATE_I       I0178           4
        MULT        temp       I0178       I0179
         ADD       I0176       I0179       I0180
        ADDR           a       I0181
 IMMEDIATE_I       I0184           4
        MULT        temp       I0184       I0185
         ADD       I0181       I0185       I0186
       VALAT       I0187       I0186
      ASSIGN       I0187       I0180
 IMMEDIATE_I       I0189           0
      RETURN       I0189
    ENDFRAME
     ENDPROC
