#
#3AC For the Input Code File: tests/test4.c
#
   PROCENTRY        main
       ALLOC           i         INT           4
       ALLOC           a         INT           4
  BEGINFRAME           0
 IMMEDIATE_I   I00000001           1
         MOV   I00000001           a
 IMMEDIATE_I   I00000004           0
         MOV   I00000004           i
       LABEL   L00000000
 IMMEDIATE_I   I00000007          10
          LT           i   I00000007   I00000008
        BREQ   I00000008           0   L00000001
  BEGINFRAME           0
 IMMEDIATE_I   I00000011           2
         ADD   I00000011           a   I00000012
         MOV   I00000012           a
    ENDFRAME
 IMMEDIATE_I   I00000014           1
         ADD   I00000014           i   I00000015
         MOV   I00000015           i
          BR   L00000000
       LABEL   L00000001
 IMMEDIATE_I   I00000017           1
         MOV   I00000017           a
       LABEL   L00000002
 IMMEDIATE_I   I00000020          10
          LT           a   I00000020   I00000021
        BREQ   I00000021           0   L00000003
  BEGINFRAME           0
 IMMEDIATE_I   I00000024           2
         ADD   I00000024           a   I00000025
         MOV   I00000025           a
    ENDFRAME
          BR   L00000002
       LABEL   L00000003
 IMMEDIATE_I   I00000028           1
         MOV   I00000028           a
       LABEL   L00000004
  BEGINFRAME           0
 IMMEDIATE_I   I00000032           2
         ADD   I00000032           a   I00000033
         MOV   I00000033           a
    ENDFRAME
 IMMEDIATE_I   I00000036          10
          LT           a   I00000036   I00000037
        BREQ   I00000037           0   L00000005
          BR   L00000004
       LABEL   L00000005
 IMMEDIATE_I   I00000038           0
    ENDFRAME
     ENDPROC
