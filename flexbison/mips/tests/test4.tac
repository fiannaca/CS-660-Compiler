#
#3AC For the Input Code File: tests/test4.c
#
   PROCENTRY        main
       ALLOC           i         INT           4
       ALLOC           a         INT           4
 IMMEDIATE_I   I00000001           1
         MOV   I00000001           a
 IMMEDIATE_I   I00000004           0
         MOV   I00000004           i
       LABEL   L00000000
 IMMEDIATE_I   I00000007          10
          LT   I00000007           i   I00000008
         ADD           1           i   I00000010
         MOV           i   I00000010
        BREQ           i           0   L00000001
 IMMEDIATE_I   I00000013           2
         ADD   I00000013           a   I00000014
         MOV   I00000014           a
          BR   L00000000
       LABEL   L00000001
 IMMEDIATE_I   I00000017           1
         MOV   I00000017           a
       LABEL   L00000002
 IMMEDIATE_I   I00000020          10
          LT   I00000020           a   I00000021
        BREQ   I00000021           0   L00000003
 IMMEDIATE_I   I00000024           2
         ADD   I00000024           a   I00000025
         MOV   I00000025           a
          BR   L00000002
       LABEL   L00000003
 IMMEDIATE_I   I00000028           1
         MOV   I00000028           a
       LABEL   L00000004
 IMMEDIATE_I   I00000032           2
         ADD   I00000032           a   I00000033
         MOV   I00000033           a
 IMMEDIATE_I   I00000036          10
          LT   I00000036           a   I00000037
        BREQ   I00000037           0   L00000005
          BR   L00000004
       LABEL   L00000005
 IMMEDIATE_I   I00000038           0
     ENDPROC
