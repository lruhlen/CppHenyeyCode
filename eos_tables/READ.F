      PROGRAM READTAB
C  THIS SHORT PROGRAM SHOWS HOW TO READ THE ASCII EOS TABLES IN
C  THE PROPER FORMAT.  THE PARAMETERS 'NT' AND 'NP' ARE DIFFERENT
C  FOR EACH FILE.  THE FOLLOWING TABLE GIVES THE VALUES TO USE:
C    FILE NAME           NT      NP
C
C    H_tab_I.a           63      76
C    He_tab_I.a          63      76
C    H_tab_P1.a          17      41
C    H_tab_P2.a          17      51
C
C  DESCRIPTION OF THE ARRAYS:
C     TLOG            LOG T (K) OF EACH ISOTHERM IN THE TABLE
C     NPOINT          NUMBER OF POINTS INOPRESSURE FOR EACH ISOTHERM
C     TABLE           EOS TABLE (SEE THE 'README' FILE FOR A DETAILED
C                     DESCRIPTION OF CONTENTS)

      PARAMETER(NT=63, NP=76)
      DIMENSION TLOG(NT),NPOINT(NT),TABLE(NT,NP,11)
      OPEN(UNIT=1,FILE='H_tab_I.a')
      DO 10 I=1,NT
      READ(1,1) TLOG(I),NPOINT(I)
      WRITE(2,1) TLOG(I),NPOINT(I)
      READ(1,2) ((TABLE(I,J,K),J=1,NPOINT(I)),K=1,11)
      WRITE(2,2) ((TABLE(I,J,K),J=1,NPOINT(I)),K=1,11)
   10 CONTINUE
      WRITE(2,*) NPOINT
      WRITE(2,3) TLOG
    1 FORMAT(F5.2,I4)
    2 FORMAT(F6.2,1P2E13.5,0P,8F9.4)
    3 FORMAT(15F5.2)
      STOP
      END
      
