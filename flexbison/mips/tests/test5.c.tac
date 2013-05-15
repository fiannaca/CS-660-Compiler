#
#3AC For the Input Code File: tests/test5.c
#
   PROCENTRY         add
  BEGINFRAME           0
       ALLOC        temp         INT           4
       PARAM           b         INT           4
       PARAM           a         INT           4
         ADD           b           a       I0003
         MOV       I0003        temp
    ENDFRAME
     ENDPROC
   PROCENTRY        main
  BEGINFRAME           0
       ALLOC           x         INT           4
       ALLOC           y         INT           4
       ALLOC        temp         INT           4
 IMMEDIATE_I       I0006           1
         MOV       I0006           x
 IMMEDIATE_I       I0009           2
         MOV       I0009           y
        FPAR           y
        FPAR           x
        CALL         add
 IMMEDIATE_I       I0014           0
      RETURN       I0014
    ENDFRAME
     ENDPROC
