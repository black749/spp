/*------------------------------------------------------------------------------
* rtklib.h : RTKLIB constants, types and function prototypes
*
*          Copyright (C) 2007-2020 by T.TAKASU, All rights reserved.
*
* options : -DENAGLO   enable GLONASS
*           -DENAGAL   enable Galileo
*           -DENAQZS   enable QZSS
*           -DENACMP   enable BeiDou
*           -DENAIRN   enable IRNSS
*           -DNFREQ=n  set number of obs codes/frequencies
*           -DNEXOBS=n set number of extended obs codes
*           -DMAXOBS=n set max number of obs data in an epoch
*           -DWIN32    use WIN32 API
*           -DWIN_DLL  generate library as Windows DLL
*
* version : $Revision:$ $Date:$
* history : 2007/01/13 1.0  rtklib ver.1.0.0
*           2007/03/20 1.1  rtklib ver.1.1.0
*           2008/07/15 1.2  rtklib ver.2.1.0
*           2008/10/19 1.3  rtklib ver.2.1.1
*           2009/01/31 1.4  rtklib ver.2.2.0
*           2009/04/30 1.5  rtklib ver.2.2.1
*           2009/07/30 1.6  rtklib ver.2.2.2
*           2009/12/25 1.7  rtklib ver.2.3.0
*           2010/07/29 1.8  rtklib ver.2.4.0
*           2011/05/27 1.9  rtklib ver.2.4.1
*           2013/03/28 1.10 rtklib ver.2.4.2
*           2020/11/30 1.11 rtklib ver.2.4.3 b34
*-----------------------------------------------------------------------------*/
#ifndef RTKLIB_H
#define RTKLIB_H
#define WIN32
#define TRACE
#define ENAGLO
#define ENAGAL
#define ENACMP
#define ENAQZS
#define ENAIRN
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>
#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <pthread.h>
#include <sys/select.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN_DLL
#define EXPORT __declspec(dllexport) /* for Windows DLL */
#else
#define EXPORT
#endif

/* constants -----------------------------------------------------------------*/

#define VER_RTKLIB  "demo5"             /* library version */

#define PATCH_LEVEL "gdsc_2022"               /* patch level */

#define COPYRIGHT_RTKLIB \
            "Copyright (C) 2007-2020 T.Takasu\nAll rights reserved."

#define PI          3.1415926535897932  /* pi */
#define D2R         (PI/180.0)          /* deg to rad */
#define R2D         (180.0/PI)          /* rad to deg */
#define CLIGHT      299792458.0         /* speed of light (m/s) */
#define SC2RAD      3.1415926535898     /* semi-circle to radian (IS-GPS) */
#define AU          149597870691.0      /* 1 AU (m) */
#define AS2R        (D2R/3600.0)        /* arc sec to radian */

#define OMGE        7.2921151467E-5     /* earth angular velocity (IS-GPS) (rad/s) */

#define RE_WGS84    6378137.0           /* earth semimajor axis (WGS84) (m) */
#define FE_WGS84    (1.0/298.257223563) /* earth flattening (WGS84) */

#define HION        350000.0            /* ionosphere height (m) */

#define MAXFREQ     6                   /* max NFREQ */

#define FREQL1      1.57542E9           /* L1/E1  frequency (Hz) */
#define FREQL2      1.22760E9           /* L2     frequency (Hz) */
#define FREQE5b     1.20714E9           /* E5b    frequency (Hz) */
#define FREQL5      1.17645E9           /* L5/E5a/B2a frequency (Hz) */
#define FREQL6      1.27875E9           /* E6/L6 frequency (Hz) */
#define FREQE5ab    1.191795E9          /* E5a+b  frequency (Hz) */
#define FREQs       2.492028E9           /* S      frequency (Hz) */
#define FREQ1_GLO   1.60200E9           /* GLONASS G1 base frequency (Hz) */
#define DFRQ1_GLO   0.56250E6           /* GLONASS G1 bias frequency (Hz/n) */
#define FREQ2_GLO   1.24600E9           /* GLONASS G2 base frequency (Hz) */
#define DFRQ2_GLO   0.43750E6           /* GLONASS G2 bias frequency (Hz/n) */
#define FREQ3_GLO   1.202025E9          /* GLONASS G3 frequency (Hz) */
#define FREQ1a_GLO  1.600995E9          /* GLONASS G1a frequency (Hz) */
#define FREQ2a_GLO  1.248060E9          /* GLONASS G2a frequency (Hz) */
#define FREQ1_CMP   1.561098E9          /* BDS B1I     frequency (Hz) */
#define FREQ2_CMP   1.20714E9           /* BDS B2I/B2b frequency (Hz) */
#define FREQ3_CMP   1.26852E9           /* BDS B3      frequency (Hz) */

#define EFACT_GPS   1.0                 /* error factor: GPS */
#define EFACT_GLO   0.75                /* error factor: GLONASS */
#define EFACT_GAL   1.0                 /* error factor: Galileo */
#define EFACT_QZS   1.0                 /* error factor: QZSS */
#define EFACT_CMP   1.0                 /* error factor: BeiDou */
#define EFACT_IRN   1.5                 /* error factor: IRNSS */
#define EFACT_SBS   3.0                 /* error factor: SBAS */

#define SYS_NONE    0x00                /* navigation system: none */
#define SYS_GPS     0x01                /* navigation system: GPS */
#define SYS_SBS     0x02                /* navigation system: SBAS */
#define SYS_GLO     0x04                /* navigation system: GLONASS */
#define SYS_GAL     0x08                /* navigation system: Galileo */
#define SYS_QZS     0x10                /* navigation system: QZSS */
#define SYS_CMP     0x20                /* navigation system: BeiDou */
#define SYS_IRN     0x40                /* navigation system: IRNS */
#define SYS_LEO     0x80                /* navigation system: LEO */
#define SYS_ALL     0xFF                /* navigation system: all */

#define TSYS_GPS    0                   /* time system: GPS time */
#define TSYS_UTC    1                   /* time system: UTC */
#define TSYS_GLO    2                   /* time system: GLONASS time */
#define TSYS_GAL    3                   /* time system: Galileo time */
#define TSYS_QZS    4                   /* time system: QZSS time */
#define TSYS_CMP    5                   /* time system: BeiDou time */
#define TSYS_IRN    6                   /* time system: IRNSS time */

#ifndef NFREQ
#define NFREQ       3                   /* number of carrier frequencies 载波频率的数量*/
#endif
#define NFREQGLO    2                   /* number of carrier frequencies of GLONASS */

#ifndef NEXOBS
#define NEXOBS      0                   /* number of extended obs codes */
#endif

#define SNR_UNIT    0.001               /* SNR unit (dBHz) */

#define MINPRNGPS   1                   /* min satellite PRN number of GPS */
#define MAXPRNGPS   32                  /* max satellite PRN number of GPS */
#define NSATGPS     (MAXPRNGPS-MINPRNGPS+1) /* number of GPS satellites */
#define NSYSGPS     1

#ifdef ENAGLO
#define MINPRNGLO   1                   /* min satellite slot number of GLONASS */
#define MAXPRNGLO   27                  /* max satellite slot number of GLONASS */
#define NSATGLO     (MAXPRNGLO-MINPRNGLO+1) /* number of GLONASS satellites */
#define NSYSGLO     1
#else
#define MINPRNGLO   0
#define MAXPRNGLO   0
#define NSATGLO     0
#define NSYSGLO     0
#endif
#ifdef ENAGAL
#define MINPRNGAL   1                   /* min satellite PRN number of Galileo */
#define MAXPRNGAL   36                  /* max satellite PRN number of Galileo */
#define NSATGAL    (MAXPRNGAL-MINPRNGAL+1) /* number of Galileo satellites */
#define NSYSGAL     1
#else
#define MINPRNGAL   0
#define MAXPRNGAL   0
#define NSATGAL     0
#define NSYSGAL     0
#endif
#ifdef ENAQZS
#define MINPRNQZS   193                 /* min satellite PRN number of QZSS */
#define MAXPRNQZS   202                 /* max satellite PRN number of QZSS */
#define MINPRNQZS_S 183                 /* min satellite PRN number of QZSS L1S */
#define MAXPRNQZS_S 191                 /* max satellite PRN number of QZSS L1S */
#define NSATQZS     (MAXPRNQZS-MINPRNQZS+1) /* number of QZSS satellites */
#define NSYSQZS     1
#else
#define MINPRNQZS   0
#define MAXPRNQZS   0
#define MINPRNQZS_S 0
#define MAXPRNQZS_S 0
#define NSATQZS     0
#define NSYSQZS     0
#endif
#ifdef ENACMP
#define MINPRNCMP   1                   /* min satellite sat number of BeiDou */
#define MAXPRNCMP   46                  /* max satellite sat number of BeiDou */
#define NSATCMP     (MAXPRNCMP-MINPRNCMP+1) /* number of BeiDou satellites */
#define NSYSCMP     1
#else
#define MINPRNCMP   0
#define MAXPRNCMP   0
#define NSATCMP     0
#define NSYSCMP     0
#endif
#ifdef ENAIRN
#define MINPRNIRN   1                   /* min satellite sat number of IRNSS */
#define MAXPRNIRN   14                  /* max satellite sat number of IRNSS */
#define NSATIRN     (MAXPRNIRN-MINPRNIRN+1) /* number of IRNSS satellites */
#define NSYSIRN     1
#else
#define MINPRNIRN   0
#define MAXPRNIRN   0
#define NSATIRN     0
#define NSYSIRN     0
#endif
#ifdef ENALEO
#define MINPRNLEO   1                   /* min satellite sat number of LEO */
#define MAXPRNLEO   10                  /* max satellite sat number of LEO */
#define NSATLEO     (MAXPRNLEO-MINPRNLEO+1) /* number of LEO satellites */
#define NSYSLEO     1
#else
#define MINPRNLEO   0
#define MAXPRNLEO   0
#define NSATLEO     0
#define NSYSLEO     0
#endif
#define NSYS        (NSYSGPS+NSYSGLO+NSYSGAL+NSYSQZS+NSYSCMP+NSYSIRN+NSYSLEO) /* number of systems */

#define MINPRNSBS   120                 /* min satellite PRN number of SBAS */
#define MAXPRNSBS   158                 /* max satellite PRN number of SBAS */
#define NSATSBS     (MAXPRNSBS-MINPRNSBS+1) /* number of SBAS satellites */

#define MAXSAT      (NSATGPS+NSATGLO+NSATGAL+NSATQZS+NSATCMP+NSATIRN+NSATSBS+NSATLEO)
                                        /* max satellite number (1 to MAXSAT) */
#define MAXSTA      255

#ifndef MAXOBS
#define MAXOBS      96                  /* max number of obs in an epoch */
#endif
#define MAXRCV      64                  /* max receiver number (1 to MAXRCV) */
#define MAXOBSTYPE  64                  /* max number of obs type in RINEX */
#ifdef OBS_100HZ
#define DTTOL       0.005               /* tolerance of time difference (s) */
#else
#define DTTOL       0.025               /* tolerance of time difference (s) */
#endif
/*o,n文件时间差最大不能超过的时间阈值*/
#define MAXDTOE     7200.0              /* max time difference to GPS Toe (s) */
#define MAXDTOE_QZS 7200.0              /* max time difference to QZSS Toe (s) */
#define MAXDTOE_GAL 14400.0             /* max time difference to Galileo Toe (s) */
#define MAXDTOE_CMP 21600.0             /* max time difference to BeiDou Toe (s) */
#define MAXDTOE_GLO 1800.0              /* max time difference to GLONASS Toe (s) */
#define MAXDTOE_IRN 7200.0              /* max time difference to IRNSS Toe (s) */
#define MAXDTOE_SBS 360.0               /* max time difference to SBAS Toe (s) */
#define MAXDTOE_S   86400.0             /* max time difference to ephem toe (s) for other */
#define MAXGDOP     300.0               /* max GDOP */

#define INT_SWAP_TRAC 86400.0           /* swap interval of trace file (s) */
#define INT_SWAP_STAT 86400.0           /* swap interval of solution status file (s) */

#define MAXEXFILE   1024                /* max number of expanded files */
#define MAXSBSAGEF  30.0                /* max age of SBAS fast correction (s) */
#define MAXSBSAGEL  1800.0              /* max age of SBAS long term corr (s) */
#define MAXSBSURA   8                   /* max URA of SBAS satellite */
#define MAXBAND     10                  /* max SBAS band of IGP */
#define MAXNIGP     201                 /* max number of IGP in SBAS band */
#define MAXNGEO     4                   /* max number of GEO satellites */
#define MAXCOMMENT  100                 /* max number of RINEX comments */
#define MAXSTRPATH  1024                /* max length of stream path */
#define MAXSTRMSG   1024                /* max length of stream message */
#define MAXSTRRTK   8                   /* max number of stream in RTK server */
#define MAXSBSMSG   32                  /* max number of SBAS msg in RTK server */
#define MAXSOLMSG   8191                /* max length of solution message */
#define MAXRAWLEN   16384               /* max length of receiver raw message */
#define MAXERRMSG   4096                /* max length of error/warning message */
#define MAXANT      64                  /* max length of station name/antenna type */
#define MAXSOLBUF   256                 /* max number of solution buffer */
#define MAXOBSBUF   128                 /* max number of observation data buffer */
#define MAXNRPOS    16                  /* max number of reference positions */
#define MAXLEAPS    64                  /* max number of leap seconds table */
#define MAXGISLAYER 32                  /* max number of GIS data layers */
#define MAXRCVCMD   4096                /* max length of receiver commands */

#define RNX2VER     2.10                /* RINEX ver.2 default output version */
#define RNX3VER     3.00                /* RINEX ver.3 default output version */

#define OBSTYPE_PR  0x01                /* observation type: pseudorange */
#define OBSTYPE_CP  0x02                /* observation type: carrier-phase */
#define OBSTYPE_DOP 0x04                /* observation type: doppler-freq */
#define OBSTYPE_SNR 0x08                /* observation type: SNR */
#define OBSTYPE_ALL 0xFF                /* observation type: all */

#define FREQTYPE_L1 0x01                /* frequency type: L1/E1/B1 */
#define FREQTYPE_L2 0x02                /* frequency type: L2/E5b/B2 */
#define FREQTYPE_L3 0x04                /* frequency type: L5/E5a/L3 */
#define FREQTYPE_L4 0x08                /* frequency type: L6/E6/B3 */
#define FREQTYPE_L5 0x10                /* frequency type: E5ab */
#define FREQTYPE_ALL 0xFF               /* frequency type: all */

#define CODE_NONE   0                   /* obs code: none or unknown */
#define CODE_L1C    1                   /* obs code: L1C/A,G1C/A,E1C (GPS,GLO,GAL,QZS,SBS) */
#define CODE_L1P    2                   /* obs code: L1P,G1P,B1P (GPS,GLO,BDS) */
#define CODE_L1W    3                   /* obs code: L1 Z-track (GPS) */
#define CODE_L1Y    4                   /* obs code: L1Y        (GPS) */
#define CODE_L1M    5                   /* obs code: L1M        (GPS) */
#define CODE_L1N    6                   /* obs code: L1codeless,B1codeless (GPS,BDS) */
#define CODE_L1S    7                   /* obs code: L1C(D)     (GPS,QZS) */
#define CODE_L1L    8                   /* obs code: L1C(P)     (GPS,QZS) */
#define CODE_L1E    9                   /* (not used) */
#define CODE_L1A    10                  /* obs code: E1A,B1A    (GAL,BDS) */
#define CODE_L1B    11                  /* obs code: E1B        (GAL) */
#define CODE_L1X    12                  /* obs code: E1B+C,L1C(D+P),B1D+P (GAL,QZS,BDS) */
#define CODE_L1Z    13                  /* obs code: E1A+B+C,L1S (GAL,QZS) */
#define CODE_L2C    14                  /* obs code: L2C/A,G1C/A (GPS,GLO) */
#define CODE_L2D    15                  /* obs code: L2 L1C/A-(P2-P1) (GPS) */
#define CODE_L2S    16                  /* obs code: L2C(M)     (GPS,QZS) */
#define CODE_L2L    17                  /* obs code: L2C(L)     (GPS,QZS) */
#define CODE_L2X    18                  /* obs code: L2C(M+L),B1_2I+Q (GPS,QZS,BDS) */
#define CODE_L2P    19                  /* obs code: L2P,G2P    (GPS,GLO) */
#define CODE_L2W    20                  /* obs code: L2 Z-track (GPS) */
#define CODE_L2Y    21                  /* obs code: L2Y        (GPS) */
#define CODE_L2M    22                  /* obs code: L2M        (GPS) */
#define CODE_L2N    23                  /* obs code: L2codeless (GPS) */
#define CODE_L5I    24                  /* obs code: L5I,E5aI   (GPS,GAL,QZS,SBS) */
#define CODE_L5Q    25                  /* obs code: L5Q,E5aQ   (GPS,GAL,QZS,SBS) */
#define CODE_L5X    26                  /* obs code: L5I+Q,E5aI+Q,L5B+C,B2aD+P (GPS,GAL,QZS,IRN,SBS,BDS) */
#define CODE_L7I    27                  /* obs code: E5bI,B2bI  (GAL,BDS) */
#define CODE_L7Q    28                  /* obs code: E5bQ,B2bQ  (GAL,BDS) */
#define CODE_L7X    29                  /* obs code: E5bI+Q,B2bI+Q (GAL,BDS) */
#define CODE_L6A    30                  /* obs code: E6A,B3A    (GAL,BDS) */
#define CODE_L6B    31                  /* obs code: E6B        (GAL) */
#define CODE_L6C    32                  /* obs code: E6C        (GAL) */
#define CODE_L6X    33                  /* obs code: E6B+C,LEXS+L,B3I+Q (GAL,QZS,BDS) */
#define CODE_L6Z    34                  /* obs code: E6A+B+C,L6D+E (GAL,QZS) */
#define CODE_L6S    35                  /* obs code: L6S        (QZS) */
#define CODE_L6L    36                  /* obs code: L6L        (QZS) */
#define CODE_L8I    37                  /* obs code: E5abI      (GAL) */
#define CODE_L8Q    38                  /* obs code: E5abQ      (GAL) */
#define CODE_L8X    39                  /* obs code: E5abI+Q,B2abD+P (GAL,BDS) */
#define CODE_L2I    40                  /* obs code: B1_2I      (BDS) */
#define CODE_L2Q    41                  /* obs code: B1_2Q      (BDS) */
#define CODE_L6I    42                  /* obs code: B3I        (BDS) */
#define CODE_L6Q    43                  /* obs code: B3Q        (BDS) */
#define CODE_L3I    44                  /* obs code: G3I        (GLO) */
#define CODE_L3Q    45                  /* obs code: G3Q        (GLO) */
#define CODE_L3X    46                  /* obs code: G3I+Q      (GLO) */
#define CODE_L1I    47                  /* obs code: B1I        (BDS) (obsolute) */
#define CODE_L1Q    48                  /* obs code: B1Q        (BDS) (obsolute) */
#define CODE_L5A    49                  /* obs code: L5A SPS    (IRN) */
#define CODE_L5B    50                  /* obs code: L5B RS(D)  (IRN) */
#define CODE_L5C    51                  /* obs code: L5C RS(P)  (IRN) */
#define CODE_L9A    52                  /* obs code: SA SPS     (IRN) */
#define CODE_L9B    53                  /* obs code: SB RS(D)   (IRN) */
#define CODE_L9C    54                  /* obs code: SC RS(P)   (IRN) */
#define CODE_L9X    55                  /* obs code: SB+C       (IRN) */
#define CODE_L1D    56                  /* obs code: B1D        (BDS) */
#define CODE_L5D    57                  /* obs code: L5D(L5S),B2aD (QZS,BDS) */
#define CODE_L5P    58                  /* obs code: L5P(L5S),B2aP (QZS,BDS) */
#define CODE_L5Z    59                  /* obs code: L5D+P(L5S) (QZS) */
#define CODE_L6E    60                  /* obs code: L6E        (QZS) */
#define CODE_L7D    61                  /* obs code: B2bD       (BDS) */
#define CODE_L7P    62                  /* obs code: B2bP       (BDS) */
#define CODE_L7Z    63                  /* obs code: B2bD+P     (BDS) */
#define CODE_L8D    64                  /* obs code: B2abD      (BDS) */
#define CODE_L8P    65                  /* obs code: B2abP      (BDS) */
#define CODE_L4A    66                  /* obs code: G1aL1OCd   (GLO) */
#define CODE_L4B    67                  /* obs code: G1aL1OCd   (GLO) */
#define CODE_L4X    68                  /* obs code: G1al1OCd+p (GLO) */
#define MAXCODE     68                  /* max number of obs code */

#define PMODE_SINGLE 0                  /* positioning mode: single */
#define PMODE_DGPS   1                  /* positioning mode: DGPS/DGNSS */
#define PMODE_KINEMA 2                  /* positioning mode: kinematic */
#define PMODE_STATIC 3                  /* positioning mode: static */
#define PMODE_STATIC_START 4            /* positioning mode: static */
#define PMODE_MOVEB  5                  /* positioning mode: moving-base */
#define PMODE_FIXED  6                  /* positioning mode: fixed */
#define PMODE_PPP_KINEMA 7              /* positioning mode: PPP-kinemaric */
#define PMODE_PPP_STATIC 8              /* positioning mode: PPP-static */
#define PMODE_PPP_FIXED 9               /* positioning mode: PPP-fixed */

#define SOLF_LLH    0                   /* solution format: lat/lon/height */
#define SOLF_XYZ    1                   /* solution format: x/y/z-ecef */
#define SOLF_ENU    2                   /* so lution format: e/n/u-baseline */
#define SOLF_NMEA   3                   /* solution format: NMEA-183 */
#define SOLF_STAT   4                   /* solution format: solution status */
#define SOLF_GSIF   5                   /* solution format: GSI F1/F2 */

#define SOLQ_NONE   0                   /* solution status: no solution */
#define SOLQ_FIX    1                   /* solution status: fix */
#define SOLQ_FLOAT  2                   /* solution status: float */
#define SOLQ_SBAS   3                   /* solution status: SBAS */
#define SOLQ_DGPS   4                   /* solution status: DGPS/DGNSS */
#define SOLQ_SINGLE 5                   /* solution status: single */
#define SOLQ_PPP    6                   /* solution status: PPP */
#define SOLQ_DR     7                   /* solution status: dead reconing */
#define MAXSOLQ     7                   /* max number of solution status */

#define TIMES_GPST  0                   /* time system: gps time */
#define TIMES_UTC   1                   /* time system: utc */
#define TIMES_JST   2                   /* time system: jst */

#define IONOOPT_OFF 0                   /* ionosphere option: correction off */
#define IONOOPT_BRDC 1                  /* ionosphere option: broadcast model */
#define IONOOPT_SBAS 2                  /* ionosphere option: SBAS model */
#define IONOOPT_IFLC 3                  /* ionosphere option: L1/L2 or L1/L5 iono-free LC */
#define IONOOPT_EST 4                   /* ionosphere option: estimation */
#define IONOOPT_TEC 5                   /* ionosphere option: IONEX TEC model */
#define IONOOPT_QZS 6                   /* ionosphere option: QZSS broadcast model */
#define IONOOPT_STEC 8                  /* ionosphere option: SLANT TEC model */

#define TROPOPT_OFF 0                   /* troposphere option: correction off */
#define TROPOPT_SAAS 1                  /* troposphere option: Saastamoinen model */
#define TROPOPT_SBAS 2                  /* troposphere option: SBAS model */
#define TROPOPT_EST 3                   /* troposphere option: ZTD estimation */
#define TROPOPT_ESTG 4                  /* troposphere option: ZTD+grad estimation */
#define TROPOPT_ZTD 5                   /* troposphere option: ZTD correction */

#define EPHOPT_BRDC 0                   /* ephemeris option: broadcast ephemeris */
#define EPHOPT_PREC 1                   /* ephemeris option: precise ephemeris */
#define EPHOPT_SBAS 2                   /* ephemeris option: broadcast + SBAS */
#define EPHOPT_SSRAPC 3                 /* ephemeris option: broadcast + SSR_APC */
#define EPHOPT_SSRCOM 4                 /* ephemeris option: broadcast + SSR_COM */

#define ARMODE_OFF  0                   /* AR mode: off */
#define ARMODE_CONT 1                   /* AR mode: continuous */
#define ARMODE_INST 2                   /* AR mode: instantaneous */
#define ARMODE_FIXHOLD 3                /* AR mode: fix and hold */
#define ARMODE_WLNL 4                   /* AR mode: wide lane/narrow lane */
#define ARMODE_TCAR 5                   /* AR mode: triple carrier ar */

#define GLO_ARMODE_OFF  0               /* GLO AR mode: off */
#define GLO_ARMODE_ON 1                 /* GLO AR mode: on */
#define GLO_ARMODE_AUTOCAL 2            /* GLO AR mode: autocal */
#define GLO_ARMODE_FIXHOLD 3            /* GLO AR mode: fix and hold */

#define SBSOPT_LCORR 1                  /* SBAS option: long term correction */
#define SBSOPT_FCORR 2                  /* SBAS option: fast correction */
#define SBSOPT_ICORR 4                  /* SBAS option: ionosphere correction */
#define SBSOPT_RANGE 8                  /* SBAS option: ranging */

#define POSOPT_POS   0                  /* pos option: LLH/XYZ */
#define POSOPT_SINGLE 1                 /* pos option: average of single pos */
#define POSOPT_FILE  2                  /* pos option: read from pos file */
#define POSOPT_RINEX 3                  /* pos option: rinex header pos */
#define POSOPT_RTCM  4                  /* pos option: rtcm/raw station pos */

#define STR_NONE     0                  /* stream type: none */
#define STR_SERIAL   1                  /* stream type: serial */
#define STR_FILE     2                  /* stream type: file */
#define STR_TCPSVR   3                  /* stream type: TCP server */
#define STR_TCPCLI   4                  /* stream type: TCP client */
#define STR_NTRIPSVR 5                  /* stream type: NTRIP server */
#define STR_NTRIPCLI 6                  /* stream type: NTRIP client */
#define STR_FTP      7                  /* stream type: ftp */
#define STR_HTTP     8                  /* stream type: http */
#define STR_NTRIPCAS 9                  /* stream type: NTRIP caster */
#define STR_UDPSVR   10                 /* stream type: UDP server */
#define STR_UDPCLI   11                 /* stream type: UDP server */
#define STR_MEMBUF   12                 /* stream type: memory buffer */

#define STRFMT_RTCM2 0                  /* stream format: RTCM 2 */
#define STRFMT_RTCM3 1                  /* stream format: RTCM 3 */
#define STRFMT_OEM4  2                  /* stream format: NovAtel OEMV/4 */
#define STRFMT_CNAV  3                  /* stream format: ComNav */
#define STRFMT_UBX   4                  /* stream format: u-blox LEA-*T */
#define STRFMT_SBP   5                  /* stream format: Swift Navigation SBP */
#define STRFMT_CRES  6                  /* stream format: Hemisphere */
#define STRFMT_STQ   7                  /* stream format: SkyTraq S1315F */
#define STRFMT_JAVAD 8                  /* stream format: JAVAD GRIL/GREIS */
#define STRFMT_NVS   9                  /* stream format: NVS NVC08C */
#define STRFMT_BINEX 10                 /* stream format: BINEX */
#define STRFMT_RT17  11                 /* stream format: Trimble RT17 */
#define STRFMT_SEPT  12                 /* stream format: Septentrio */
#define STRFMT_TERSUS 13                /* stream format: TERSUS */
#define STRFMT_RINEX 14                 /* stream format: RINEX */
#define STRFMT_SP3   15                 /* stream format: SP3 */
#define STRFMT_RNXCLK 16                /* stream format: RINEX CLK */
#define STRFMT_SBAS  17                 /* stream format: SBAS messages */
#define STRFMT_NMEA  18                 /* stream format: NMEA 0183 */
#define MAXRCVFMT    13                 /* max number of receiver format */

#define STR_MODE_R  0x1                 /* stream mode: read */
#define STR_MODE_W  0x2                 /* stream mode: write */
#define STR_MODE_RW 0x3                 /* stream mode: read/write */

#define GEOID_EMBEDDED    0             /* geoid model: embedded geoid */
#define GEOID_EGM96_M150  1             /* geoid model: EGM96 15x15" */
#define GEOID_EGM2008_M25 2             /* geoid model: EGM2008 2.5x2.5" */
#define GEOID_EGM2008_M10 3             /* geoid model: EGM2008 1.0x1.0" */
#define GEOID_GSI2000_M15 4             /* geoid model: GSI geoid 2000 1.0x1.5" */
#define GEOID_RAF09       5             /* geoid model: IGN RAF09 for France 1.5"x2" */

#define COMMENTH    "%"                 /* comment line indicator for solution */
#define MSG_DISCONN "$_DISCONNECT\r\n"  /* disconnect message */

#define DLOPT_FORCE   0x01              /* download option: force download existing */
#define DLOPT_KEEPCMP 0x02              /* download option: keep compressed file */
#define DLOPT_HOLDERR 0x04              /* download option: hold on error file */
#define DLOPT_HOLDLST 0x08              /* download option: hold on listing file */

#define LLI_SLIP    0x01                /* LLI: cycle-slip */
#define LLI_HALFC   0x02                /* LLI: half-cycle not resovled */
#define LLI_BOCTRK  0x04                /* LLI: boc tracking of mboc signal */
#define LLI_HALFA   0x40                /* LLI: half-cycle added */
#define LLI_HALFS   0x80                /* LLI: half-cycle subtracted */

#define P2_5        0.03125             /* 2^-5 */
#define P2_6        0.015625            /* 2^-6 */
#define P2_11       4.882812500000000E-04 /* 2^-11 */
#define P2_15       3.051757812500000E-05 /* 2^-15 */
#define P2_17       7.629394531250000E-06 /* 2^-17 */
#define P2_19       1.907348632812500E-06 /* 2^-19 */
#define P2_20       9.536743164062500E-07 /* 2^-20 */
#define P2_21       4.768371582031250E-07 /* 2^-21 */
#define P2_23       1.192092895507810E-07 /* 2^-23 */
#define P2_24       5.960464477539063E-08 /* 2^-24 */
#define P2_27       7.450580596923828E-09 /* 2^-27 */
#define P2_29       1.862645149230957E-09 /* 2^-29 */
#define P2_30       9.313225746154785E-10 /* 2^-30 */
#define P2_31       4.656612873077393E-10 /* 2^-31 */
#define P2_32       2.328306436538696E-10 /* 2^-32 */
#define P2_33       1.164153218269348E-10 /* 2^-33 */
#define P2_35       2.910383045673370E-11 /* 2^-35 */
#define P2_38       3.637978807091710E-12 /* 2^-38 */
#define P2_39       1.818989403545856E-12 /* 2^-39 */
#define P2_40       9.094947017729280E-13 /* 2^-40 */
#define P2_43       1.136868377216160E-13 /* 2^-43 */
#define P2_48       3.552713678800501E-15 /* 2^-48 */
#define P2_50       8.881784197001252E-16 /* 2^-50 */
#define P2_55       2.775557561562891E-17 /* 2^-55 */

#ifdef WIN32
#define thread_t    HANDLE
#define lock_t      CRITICAL_SECTION
#define initlock(f) InitializeCriticalSection(f)
#define lock(f)     EnterCriticalSection(f)
#define unlock(f)   LeaveCriticalSection(f)
#define FILEPATHSEP '\\'
#else
#define thread_t    pthread_t
#define lock_t      pthread_mutex_t
#define initlock(f) pthread_mutex_init(f,NULL)
#define lock(f)     pthread_mutex_lock(f)
#define unlock(f)   pthread_mutex_unlock(f)
#define FILEPATHSEP '/'
#endif

/* type definitions ----------------------------------------------------------*/

typedef struct {        /* time struct */
    time_t time;        /* time (s) expressed by standard time_t */
    double sec;         /* fraction of second under 1 s */
} gtime_t;

typedef struct {
    gtime_t time;            /* receiver sampling time (GPST) - 接收器采样时间 (GPST) */
    uint8_t sat, rcv;       /* satellite/receiver number - 卫星/接收器编号 */
    uint16_t SNR[NFREQ + NEXOBS];    /* signal strength (0.001 dBHz) - 信号强度 (0.001 dBHz) */
    uint8_t LLI[NFREQ + NEXOBS];    /* loss of lock indicator - 丢锁指示器 */
    uint8_t code[NFREQ + NEXOBS];   /* code indicator (CODE_???) - 码指示器 (CODE_???) */
    double L[NFREQ + NEXOBS];       /* observation data carrier-phase (cycle) - 观测数据载波相位 (周期) */
    double P[NFREQ + NEXOBS];       /* observation data pseudorange (m) - 观测数据伪距 (米) */
    float D[NFREQ + NEXOBS];        /* observation data doppler frequency (Hz) - 观测数据多普勒频率 (Hz) */

    int timevalid;           /* time is valid (Valid GNSS fix) for time mark - 时间是否有效 (用于时间标记) */
    gtime_t eventime;       /* time of event (GPST) - 事件发生的时间 (GPST) */
    uint8_t Lstd[NFREQ + NEXOBS];    /* stdev of carrier phase (0.004 cycles) - 载波相位的标准差 (0.004 周期) */
    uint8_t Pstd[NFREQ + NEXOBS];    /* stdev of pseudorange (0.01*2^(n+5) meters) - 伪距的标准差 (0.01*2^(n+5) 米) */
    uint8_t freq;           /* GLONASS frequency channel (0-13) - GLONASS 频道号 (0-13) */
} obsd_t;/*储存o文件一个历元下所选系统的所有卫星*/

typedef struct {        /* observation data  */
    int n,nmax;         /* number of obervation data/allocated 观测数据的数量,分配的观测数据的最大数量*/
    int flag;           /* epoch flag (0:ok,1:power failure,>1:event flag) 时间戳标志，0表示正常，1表示电源故障，大于1表示事件标志*/
    int rcvcount;       /* count of rcv event 接收器事件的计数*/
    int tmcount;        /* time mark count 时间标记计数*/
    obsd_t *data;       /* observation data records 指向obsd_t结构体类型的指针，表示观测数据记录*/
} obs_t;

typedef struct {        /* earth rotation parameter data type */
    double mjd;         /* mjd (days) */
    double xp,yp;       /* pole offset (rad) */
    double xpr,ypr;     /* pole offset rate (rad/day) */
    double ut1_utc;     /* ut1-utc (s) */
    double lod;         /* length of day (s/day) */
} erpd_t;

typedef struct {        /* earth rotation parameter type */
    int n,nmax;         /* number and max number of data */
    erpd_t *data;       /* earth rotation parameter data */
} erp_t;

typedef struct {        /* antenna parameter type */
    int sat;            /* satellite number (0:receiver) */
    char type[MAXANT];  /* antenna type */
    char code[MAXANT];  /* serial number or satellite code */
    gtime_t ts,te;      /* valid time start and end */
    double off[NFREQ][ 3]; /* phase center offset e/n/u or x/y/z (m) */
    double var[NFREQ][19]; /* phase center variation (m) */
                        /* el=90,85,...,0 or nadir=0,1,2,3,... (deg) */
} pcv_t;

typedef struct {        /* antenna parameters type */
    int n,nmax;         /* number of data/allocated */
    pcv_t *pcv;         /* antenna parameters data */
} pcvs_t;

typedef struct {        /* almanac type */
    int sat;            /* satellite number */
    int svh;            /* sv health (0:ok) */
    int svconf;         /* as and sv config */
    int week;           /* GPS/QZS: gps week, GAL: galileo week */
    gtime_t toa;        /* Toa */
                        /* SV orbit parameters */
    double A,e,i0,OMG0,omg,M0,OMGd;
    double toas;        /* Toa (s) in week */
    double f0,f1;       /* SV clock parameters (af0,af1) */
} alm_t;

typedef struct {        /* GPS/QZS/GAL broadcast ephemeris type GPS/QZS/GAL的广播星历*/
    int sat;            /* satellite number 数据源 */
    int iode, iodc;      /* IODE(卫星星历数据的发布号。IODE值用于区分和标识不同时间段内的卫星星历数据),IODC */
    int sva;            /* SV accuracy (URA index) 卫星准确性 (URA指数) */
    int svh;            /* SV health (0:ok) 卫星健康状态 (0表示正常) */
    int week;           /* GPS/QZS: gps week, GAL: galileo week GPS/QZS：GPS周数，GAL：伽利略周数 */
    int code;           /* GPS/QZS: code on L2, GAL: data source defined as rinex 3.03, BDS: data source (0:unknown,1:B1I,2:B1Q,3:B2I,4:B2Q,5:B3I,6:B3Q) 
                         GPS/QZS：L2码，GAL：数据源（Rinex 3.03定义），BDS：数据源（0表示未知，1表示B1I，2表示B1Q，3表示B2I，4表示B2Q，5表示B3I，6表示B3Q） */
    int flag;           /* GPS/QZS: L2 P data flag, BDS: nav type (0:unknown,1:IGSO/MEO,2:GEO) 
                           GPS/QZS：L2 P数据标志，BDS：导航类型（0表示未知，1表示IGSO/MEO，2表示GEO） */
    gtime_t toe, toc, ttr; /* Toe,Toc,T_trans */
    /* SV orbit parameters 卫星轨道参数 */
    double A, e, i0, OMG0, omg, M0, deln, OMGd, idot;
    double crc, crs, cuc, cus, cic, cis;
    double toes;        /* Toe (s) in week Toe（秒数） */
    double fit;         /* fit interval (h) 采样间隔（小时） */
    double f0, f1, f2;    /* SV clock parameters (af0,af1,af2) 卫星钟参数（af0、af1、af2） */
    double tgd[6];      /* group delay parameters 组延迟参数 */
                        /*  GPS/QZS:tgd[0]=TGD
                            GAL:tgd[0]=BGD_E1E5a,tgd[1]=BGD_E1E5b 
                            CMP:tgd[0]=TGD_B1I,tgd[1]=TGD_B2I/B2b,tgd[2]=TGD_B1Cp,tgd[3]=TGD_B2ap,tgd[4]=ISC_B1Cd,tgd[5]=ISC_B2ad */
    double Adot, ndot;   /* Adot,ndot for CNAV CNAV的Adot、ndot参数 */
} eph_t;

typedef struct {        /* GLONASS broadcast ephemeris type GLONASS广播星历类型 */
    int sat;            /* satellite number 卫星编号 */
    int iode;           /* IODE (0-6 bit of tb field) IODE（tb字段的0-6位） */
    int frq;            /* satellite frequency number 卫星频率编号 */
    int svh, sva, age;    /* satellite health, accuracy, age of operation 卫星健康状态，准确性，运行时间 */
    gtime_t toe;        /* epoch of epherides (gpst) 星历的时刻（gpst） */
    gtime_t tof;        /* message frame time (gpst) 消息帧时刻（gpst） */
    double pos[3];      /* satellite position (ecef) (m) 卫星位置（地心惯性坐标系下）（米） */
    double vel[3];      /* satellite velocity (ecef) (m/s) 卫星速度（地心惯性坐标系下）（米/秒） */
    double acc[3];      /* satellite acceleration (ecef) (m/s^2) 卫星加速度（地心惯性坐标系下）（米/秒^2） */
    double taun, gamn;   /* SV clock bias (s)/relative freq bias SV钟差（秒）/相对频率偏差 */
    double dtaun;       /* delay between L1 and L2 (s) L1和L2之间的延迟（秒） */
} geph_t;

typedef struct {        /* precise ephemeris type */
    gtime_t time;       /* time (GPST) */
    int index;          /* ephemeris index for multiple files */
    double pos[MAXSAT][4]; /* satellite position/clock (ecef) (m|s) */
    float  std[MAXSAT][4]; /* satellite position/clock std (m|s) */
    double vel[MAXSAT][4]; /* satellite velocity/clk-rate (m/s|s/s) */
    float  vst[MAXSAT][4]; /* satellite velocity/clk-rate std (m/s|s/s) */
    float  cov[MAXSAT][3]; /* satellite position covariance (m^2) */
    float  vco[MAXSAT][3]; /* satellite velocity covariance (m^2) */
} peph_t;

typedef struct {        /* precise clock type */
    gtime_t time;       /* time (GPST) */
    int index;          /* clock index for multiple files */
    double clk[MAXSAT][1]; /* satellite clock (s) */
    float  std[MAXSAT][1]; /* satellite clock std (s) */
} pclk_t;

typedef struct {        /* SBAS ephemeris type */
    int sat;            /* satellite number */
    gtime_t t0;         /* reference epoch time (GPST) */
    gtime_t tof;        /* time of message frame (GPST) */
    int sva;            /* SV accuracy (URA index) */
    int svh;            /* SV health (0:ok) */
    double pos[3];      /* satellite position (m) (ecef) */
    double vel[3];      /* satellite velocity (m/s) (ecef) */
    double acc[3];      /* satellite acceleration (m/s^2) (ecef) */
    double af0,af1;     /* satellite clock-offset/drift (s,s/s) */
} seph_t;

typedef struct {        /* NORAL TLE data type */
    char name [32];     /* common name */
    char alias[32];     /* alias name */
    char satno[16];     /* satellilte catalog number */
    char satclass;      /* classification */
    char desig[16];     /* international designator */
    gtime_t epoch;      /* element set epoch (UTC) */
    double ndot;        /* 1st derivative of mean motion */
    double nddot;       /* 2st derivative of mean motion */
    double bstar;       /* B* drag term */
    int etype;          /* element set type */
    int eleno;          /* element number */
    double inc;         /* orbit inclination (deg) */
    double OMG;         /* right ascension of ascending node (deg) */
    double ecc;         /* eccentricity */
    double omg;         /* argument of perigee (deg) */
    double M;           /* mean anomaly (deg) */
    double n;           /* mean motion (rev/day) */
    int rev;            /* revolution number at epoch */
} tled_t;

typedef struct {        /* NORAD TLE (two line element) type */
    int n,nmax;         /* number/max number of two line element data */
    tled_t *data;       /* NORAD TLE data */
} tle_t;

typedef struct {        /* TEC grid type */
    gtime_t time;       /* epoch time (GPST) */
    int ndata[3];       /* TEC grid data size {nlat,nlon,nhgt} */
    double rb;          /* earth radius (km) */
    double lats[3];     /* latitude start/interval (deg) */
    double lons[3];     /* longitude start/interval (deg) */
    double hgts[3];     /* heights start/interval (km) */
    double *data;       /* TEC grid data (tecu) */
    float *rms;         /* RMS values (tecu) */
} tec_t;

typedef struct {        /* SBAS message type */
    int week,tow;       /* receiption time */
    uint8_t prn,rcv;    /* SBAS satellite PRN,receiver number */
    uint8_t msg[29];    /* SBAS message (226bit) padded by 0 */
} sbsmsg_t;

typedef struct {        /* SBAS messages type */
    int n,nmax;         /* number of SBAS messages/allocated */
    sbsmsg_t *msgs;     /* SBAS messages */
} sbs_t;

typedef struct {        /* SBAS fast correction type */
    gtime_t t0;         /* time of applicability (TOF) */
    double prc;         /* pseudorange correction (PRC) (m) */
    double rrc;         /* range-rate correction (RRC) (m/s) */
    double dt;          /* range-rate correction delta-time (s) */
    int iodf;           /* IODF (issue of date fast corr) */
    int16_t udre;       /* UDRE+1 */
    int16_t ai;         /* degradation factor indicator */
} sbsfcorr_t;

typedef struct {        /* SBAS long term satellite error correction type */
    gtime_t t0;         /* correction time */
    int iode;           /* IODE (issue of date ephemeris) */
    double dpos[3];     /* delta position (m) (ecef) */
    double dvel[3];     /* delta velocity (m/s) (ecef) */
    double daf0,daf1;   /* delta clock-offset/drift (s,s/s) */
} sbslcorr_t;

typedef struct {        /* SBAS satellite correction type */
    int sat;            /* satellite number */
    sbsfcorr_t fcorr;   /* fast correction */
    sbslcorr_t lcorr;   /* long term correction */
} sbssatp_t;

typedef struct {        /* SBAS satellite corrections type */
    int iodp;           /* IODP (issue of date mask) */
    int nsat;           /* number of satellites */
    int tlat;           /* system latency (s) */
    sbssatp_t sat[MAXSAT]; /* satellite correction */
} sbssat_t;

typedef struct {        /* SBAS ionospheric correction type */
    gtime_t t0;         /* correction time */
    int16_t lat,lon;    /* latitude/longitude (deg) */
    int16_t give;       /* GIVI+1 */
    float delay;        /* vertical delay estimate (m) */
} sbsigp_t;

typedef struct {        /* IGP band type */
    int16_t x;          /* longitude/latitude (deg) */
    const int16_t *y;   /* latitudes/longitudes (deg) */
    uint8_t bits;       /* IGP mask start bit */
    uint8_t bite;       /* IGP mask end bit */
} sbsigpband_t;

typedef struct {        /* SBAS ionospheric corrections type */
    int iodi;           /* IODI (issue of date ionos corr) */
    int nigp;           /* number of igps */
    sbsigp_t igp[MAXNIGP]; /* ionospheric correction */
} sbsion_t;

typedef struct {        /* DGPS/GNSS correction type */
    gtime_t t0;         /* correction time */
    double prc;         /* pseudorange correction (PRC) (m) */
    double rrc;         /* range rate correction (RRC) (m/s) */
    int iod;            /* issue of data (IOD) */
    double udre;        /* UDRE */
} dgps_t;

typedef struct {        /* SSR correction type */
    gtime_t t0[6];      /* epoch time (GPST) {eph,clk,hrclk,ura,bias,pbias} */
    double udi[6];      /* SSR update interval (s) */
    int iod[6];         /* iod ssr {eph,clk,hrclk,ura,bias,pbias} */
    int iode;           /* issue of data */
    int iodcrc;         /* issue of data crc for beidou/sbas */
    int ura;            /* URA indicator */
    int refd;           /* sat ref datum (0:ITRF,1:regional) */
    double deph [3];    /* delta orbit {radial,along,cross} (m) */
    double ddeph[3];    /* dot delta orbit {radial,along,cross} (m/s) */
    double dclk [3];    /* delta clock {c0,c1,c2} (m,m/s,m/s^2) */
    double hrclk;       /* high-rate clock corection (m) */
    float  cbias[MAXCODE]; /* code biases (m) */
    double pbias[MAXCODE]; /* phase biases (m) */
    float  stdpb[MAXCODE]; /* std-dev of phase biases (m) */
    double yaw_ang,yaw_rate; /* yaw angle and yaw rate (deg,deg/s) */
    uint8_t update;     /* update flag (0:no update,1:update) */
} ssr_t;

typedef struct {
    int n, nmax;         /* number of broadcast ephemeris - 广播星历的数量和最大数量 */
    int ng, ngmax;       /* number of GLONASS ephemeris - GLONASS星历的数量和最大数量 */
    int ns, nsmax;       /* number of SBAS ephemeris - SBAS星历的数量和最大数量 */
    int ne, nemax;       /* number of precise ephemeris - 精密星历的数量和最大数量 */
    int nc, ncmax;       /* number of precise clock - 精密钟差的数量和最大数量 */
    int na, namax;       /* number of almanac data - 星历数据的数量和最大数量 */
    int nt, ntmax;       /* number of TEC grid data - TEC（Total Electron Content）格点数据的数量和最大数量 */
    int leaps;          /* leap seconds - 闰秒信息 */
    eph_t* eph;         /* GPS/QZS/GAL/BDS/IRN ephemeris - GPS/QZS/GAL/BDS/IRN星历数据 */
    geph_t* geph;       /* GLONASS ephemeris - GLONASS星历数据 */
    seph_t* seph;       /* SBAS ephemeris - SBAS星历数据 */
    peph_t* peph;       /* precise ephemeris - 精密星历数据 */
    pclk_t* pclk;       /* precise clock - 精密钟差数据 */
    alm_t* alm;         /* almanac data - 星历数据 */
    tec_t* tec;         /* TEC grid data - TEC格点数据 */
    erp_t  erp;         /* earth rotation parameters - 地球旋转参数 */
    double utc_gps[8];  /* GPS delta-UTC parameters - GPS的delta-UTC参数 */
    double utc_glo[8];  /* GLONASS UTC time parameters - GLONASS的UTC时间参数 */
    double utc_gal[8];  /* Galileo UTC parameters - Galileo的UTC参数 */
    double utc_qzs[8];  /* QZSS UTC parameters - QZSS的UTC参数 */
    double utc_cmp[8];  /* BeiDou UTC parameters - BeiDou的UTC参数 */
    double utc_irn[9];  /* IRNSS UTC parameters - IRNSS的UTC参数 */
    double utc_sbs[4];  /* SBAS UTC parameters - SBAS的UTC参数 */
    double ion_gps[8];  /* GPS iono model parameters - GPS的电离层模型参数 */
    double ion_gal[4];  /* Galileo iono model parameters - Galileo的电离层模型参数 */
    double ion_qzs[8];  /* QZSS iono model parameters - QZSS的电离层模型参数 */
    double ion_cmp[8];  /* BeiDou iono model parameters - BeiDou的电离层模型参数 */
    double ion_irn[8];  /* IRNSS iono model parameters - IRNSS的电离层模型参数 */
    int glo_fcn[32];    /* GLONASS FCN + 8 - GLONASS FCN（频道编号） + 8 */
    double cbias[MAXSAT][3]; /* satellite DCB (0:P1-P2,1:P1-C1,2:P2-C2) (m) - 卫星的DCB（Differential Code Bias）（0:P1-P2,1:P1-C1,2:P2-C2）(米) */
    double rbias[MAXRCV][2][3]; /* receiver DCB (0:P1-P2,1:P1-C1,2:P2-C2) (m) - 接收机的DCB（Differential Code Bias）（0:P1-P2,1:P1-C1,2:P2-C2）(米) */
    pcv_t pcvs[MAXSAT]; /* satellite antenna pcv - 卫星天线PCV（Phase Center Variation） */
    sbssat_t sbssat;    /* SBAS satellite corrections - SBAS卫星的修正数据 */
    sbsion_t sbsion[MAXBAND + 1]; /* SBAS ionosphere corrections - SBAS的电离层修正数据 */
    dgps_t dgps[MAXSAT]; /* DGPS corrections - DGPS（差分GPS）修正数据 */
    ssr_t ssr[MAXSAT];  /* SSR corrections - SSR（卫星特定修正）修正数据 */
} nav_t;

typedef struct {        /* station parameter type */
    char name   [MAXANT]; /* marker name */
    char marker [MAXANT]; /* marker number */
    char antdes [MAXANT]; /* antenna descriptor */
    char antsno [MAXANT]; /* antenna serial number */
    char rectype[MAXANT]; /* receiver type descriptor */
    char recver [MAXANT]; /* receiver firmware version */
    char recsno [MAXANT]; /* receiver serial number */
    int antsetup;       /* antenna setup id */
    int itrf;           /* ITRF realization year */
    int deltype;        /* antenna delta type (0:enu,1:xyz) */
    double pos[3];      /* station position (ecef) (m) */
    double del[3];      /* antenna position delta (e/n/u or x/y/z) (m) */
    double hgt;         /* antenna height (m) */
    int glo_cp_align;   /* GLONASS code-phase alignment (0:no,1:yes) */
    double glo_cp_bias[4]; /* GLONASS code-phase biases {1C,1P,2C,2P} (m) */
} sta_t;

typedef struct {        /* solution type (解类型) */
    gtime_t time;       /* time (GPST) 时间（GPST）*/
    gtime_t eventime;   /* time of event (GPST) 事件发生时间（GPST）*/
    double rr[6];       /* position/velocity (m|m/s) 位置/速度（米或米/秒）*/
    /* {x,y,z,vx,vy,vz} or {e,n,u,ve,vn,vu} */
    float  qr[6];       /* position variance/covariance (m^2) 位置的方差/协方差（米^2）*/
    /* {c_xx,c_yy,c_zz,c_xy,c_yz,c_zx} or */
    /* {c_ee,c_nn,c_uu,c_en,c_nu,c_ue} */
    float  qv[6];       /* velocity variance/covariance (m^2/s^2) 速度的方差/协方差（米^2/秒^2）*/
    double dtr[6];      /* receiver clock bias to time systems (s) 接收机的钟差（秒）*/
    uint8_t type;       /* type (0:xyz-ecef,1:enu-baseline) 类型（0：xyz-ecef，1：enu基线）*/
    uint8_t stat;       /* solution status (SOLQ_???) 解的状态（SOLQ_???) */
    uint8_t ns;         /* number of valid satellites 有效卫星的数量*/
    float age;          /* age of differential (s) 差分的年龄（秒）*/
    float ratio;        /* AR ratio factor for valiation AR比例因子用于验证 */
    float prev_ratio1;   /* previous initial AR ratio factor for validation 先前的初始AR比例因子用于验证 */
    float prev_ratio2;   /* previous final AR ratio factor for validation 先前的最终AR比例因子用于验证 */
    float thres;        /* AR ratio threshold for valiation AR比例阈值用于验证 */
} sol_t;

typedef struct {        /* solution buffer type */
    int n,nmax;         /* number of solution/max number of buffer */
    int cyclic;         /* cyclic buffer flag */
    int start,end;      /* start/end index */
    gtime_t time;       /* current solution time */
    sol_t *data;        /* solution data */
    double rb[3];       /* reference position {x,y,z} (ecef) (m) */
    uint8_t buff[MAXSOLMSG+1]; /* message buffer */
    int nb;             /* number of byte in message buffer */
} solbuf_t;

typedef struct {        /* solution status type */
    gtime_t time;       /* time (GPST) */
    uint8_t sat;        /* satellite number */
    uint8_t frq;        /* frequency (1:L1,2:L2,...) */
    float az,el;        /* azimuth/elevation angle (rad) */
    float resp;         /* pseudorange residual (m) */
    float resc;         /* carrier-phase residual (m) */
    uint8_t flag;       /* flags: (vsat<<5)+(slip<<3)+fix */
    uint16_t snr;       /* signal strength (*SNR_UNIT dBHz) */
    uint16_t lock;      /* lock counter */
    uint16_t outc;      /* outage counter */
    uint16_t slipc;     /* slip counter */
    uint16_t rejc;      /* reject counter */
} solstat_t;

typedef struct {        /* solution status buffer type */
    int n,nmax;         /* number of solution/max number of buffer */
    solstat_t *data;    /* solution status data */
} solstatbuf_t;

typedef struct {        /* RTCM control struct type */
    int staid;          /* station id */
    int stah;           /* station health */
    int seqno;          /* sequence number for rtcm 2 or iods msm */
    int outtype;        /* output message type */
    gtime_t time;       /* message time */
    gtime_t time_s;     /* message start time */
    obs_t obs;          /* observation data (uncorrected) */
    nav_t nav;          /* satellite ephemerides */
    sta_t sta;          /* station parameters */
    dgps_t *dgps;       /* output of dgps corrections */
    ssr_t ssr[MAXSAT];  /* output of ssr corrections */
    char msg[128];      /* special message */
    char msgtype[256];  /* last message type */
    char msmtype[7][128]; /* msm signal types */
    int obsflag;        /* obs data complete flag (1:ok,0:not complete) */
    int ephsat;         /* input ephemeris satellite number */
    int ephset;         /* input ephemeris set (0-1) */
    double cp[MAXSAT][NFREQ+NEXOBS]; /* carrier-phase measurement */
    uint16_t lock[MAXSAT][NFREQ+NEXOBS]; /* lock time */
    uint16_t loss[MAXSAT][NFREQ+NEXOBS]; /* loss of lock count */
    gtime_t lltime[MAXSAT][NFREQ+NEXOBS]; /* last lock time */
    int nbyte;          /* number of bytes in message buffer */ 
    int nbit;           /* number of bits in word buffer */ 
    int len;            /* message length (bytes) */
    uint8_t buff[1200]; /* message buffer */
    uint32_t word;      /* word buffer for rtcm 2 */
    uint32_t nmsg2[100]; /* message count of RTCM 2 (1-99:1-99,0:other) */
    uint32_t nmsg3[400]; /* message count of RTCM 3 (1-299:1001-1299,300-329:4070-4099,0:ohter) */
    char opt[256];      /* RTCM dependent options */
} rtcm_t;

typedef struct {        /* RINEX control struct type */
    gtime_t time;       /* message time */
    double ver;         /* RINEX version */
    char   type;        /* RINEX file type ('O','N',...) */
    int    sys;         /* navigation system */
    int    tsys;        /* time system */
    char   tobs[8][MAXOBSTYPE][4]; /* rinex obs types */
    obs_t  obs;         /* observation data */
    nav_t  nav;         /* navigation data */
    sta_t  sta;         /* station info */
    int    ephsat;      /* input ephemeris satellite number */
    int    ephset;      /* input ephemeris set (0-1) */
    char   opt[256];    /* rinex dependent options */
} rnxctr_t;

typedef struct {        /* download URL type */
    char type[32];      /* data type */
    char path[1024];    /* URL path */
    char dir [1024];    /* local directory */
    double tint;        /* time interval (s) */
} url_t;

typedef struct {        /* option type */
    const char *name;   /* option name */
    int format;         /* option format (0:int,1:double,2:string,3:enum) */
    void *var;          /* pointer to option variable */
    const char *comment; /* option comment/enum labels/unit */
} opt_t;

typedef struct {        /* SNR mask type */
    int ena[2];         /* enable flag {rover,base} */
    double mask[NFREQ][9]; /* mask (dBHz) at 5,10,...85 deg */
} snrmask_t;

typedef struct {        /* 处理选项类型 */
    int mode;           /* 定位模式（PMODE_???) */
    int soltype;        /* 解算类型（0：前向解算，1：后向解算，2：组合解算） */
    int nf;             /* 频率数量 （1：L1，2：L1+L2，3：L1+L2+L5） */
    int navsys;         /* 导航系统 */
    double elmin;       /* 最小仰角（弧度） */
    snrmask_t snrmask;  /* 信噪比掩模 */
    int sateph;         /* 卫星星历/钟差数据（EPHOPT_???) */
    int modear;         /* 宽巷模糊度模式（0：关闭，1：连续，2：瞬时，3：固定和保持，4：ppp-ar） */
    int glomodear;      /* GLONASS宽巷模糊度模式（0：关闭，1：开启，2：自动校准，3：外部校准） */
    int gpsmodear;      /* GPS宽巷模糊度模式，仅用于调试/学习目的（0：关闭，1：开启） */
    int bdsmodear;      /* BeiDou宽巷模糊度模式（0：关闭，1：开启） */
    int arfilter;       /* 使用AR滤波器来拒绝坏卫星（0：关闭，1：开启） */
    int maxout;         /* 观测数据中断计数以重置偏差 */
    int minlock;        /* 最小锁定计数以固定模糊度 */
    int minfixsats;     /* 最小卫星数以固定整数模糊度 */
    int minholdsats;    /* 最小卫星数以保持整数模糊度 */
    int mindropsats;    /* 最小卫星数以在AR中丢弃卫星 */
    int minfix;         /* 最小固定计数以保持模糊度 */
    int armaxiter;      /* 解算模糊度的最大迭代次数 */
    int ionoopt;        /* 电离层选项（IONOOPT_???) */
    int tropopt;        /* 对流层选项（TROPOPT_???) */
    int dynamics;       /* 动力学模型（0：无，1：速度，2：加速度） */
    int tidecorr;       /* 地球潮汐修正（0：关闭，1：仅固体潮，2：固体潮+海洋潮汐+极移） */
    int niter;          /* 滤波器迭代次数 */
    int codesmooth;     /* 代码平滑窗口大小（0：无） */
    int intpref;        /* 插值参考观测（用于事后处理） */
    int sbascorr;       /* SBAS校正选项 */
    int sbassatsel;     /* SBAS卫星选择（0：全部） */
    int rovpos;         /* 固定模式下的流动站位置 */
    int refpos;         /* 相对模式下的基准站位置 */
    /* （0：来自prcopt中的位置，1：单一位置的平均值， */
    /*  2：从文件中读取，3：rinex的头文件，4：rtcm的位置） */
    double eratio[NFREQ]; /* 代码/相位误差比 */
    double err[8];      /* 观测误差项 */
    /* [保留,常数,仰角,基线,多普勒,信噪比最大值,信噪比, 接收机标准差] */
    double std[3];      /* 初始状态标准差 [0]偏差,[1]电离层 [2]对流层 */
    double prn[6];      /* 过程噪声标准差 [0]偏差,[1]电离层 [2]对流层 [3]加速度组合因子 */
    /* [4]速度组合因子 [5]位置组合因子 */
    double sclkstab;    /* 卫星钟稳定性（秒/秒） */
    double thresar[8];  /* AR验证阈值 */
    double elmaskar;    /* AR的仰角遮挡角（度） */
    double elmaskhold;  /* 保持模糊度的仰角遮挡角（度） */
    double thresslip;   /* 零几何相位滑动阈值（米） */
    double thresdop;    /* 多普勒滑动阈值（米） */
    double varholdamb;  /* 固定和保持伪测量的方差（载波周期^2） */
    double gainholdamb; /* 用于调整模糊度的GLO和SBAS卫星的增益 */
    double maxtdiff;    /* 时间的最大差异（秒） */
    double maxinno[2];  /* 用于代码和相位创新的拒绝阈值（米） */
    double baseline[2]; /* 基线长度约束 {const,sigma} （米） */
    double ru[3];       /* 固定模式下的流动站位置 {x,y,z} （ECEF）（米） */
    double rb[3];       /* 相对模式下的基准站位置 {x,y,z} （ECEF）（米） */
    char anttype[2][MAXANT]; /* 天线类型 {流动站,基准站} */
    double antdel[2][3]; /* 天线delta {{流动站_e,流动站_n,流动站_u},{基准站_e,基准站_n,基准站_u}} */
    pcv_t pcvr[2];      /* 接收机天线参数 {流动站,基准站} */
    uint8_t exsats[MAXSAT]; /* 排除的卫星（1：排除，2：包含） */
    int  maxaveep;      /* 最大平均纪元 */
    int  initrst;       /* 通过重启来初始化 */
    int  outsingle;     /* 通过dgps/浮点解/固定解/ppp中断输出单点解 */
    char rnxopt[2][256]; /* rinex选项 {流动站,基准站} */
    int  posopt[6];     /* 定位选项 */
    int  syncsol;       /* 解算同步模式（0：关闭，1：开启） */
    double odisp[2][6 * 11]; /* 海洋潮汐加载参数 {流动站,基准站} */
    int freqopt;        /* 禁用L2-AR */
    char pppopt[256];   /* ppp选项 */
} prcopt_t;

typedef struct {        /* 解算选项类型 */
    int posf;           /* 解的格式（SOLF_???）解的输出格式，例如经纬度和高程等*/
    int times;          /* 时间系统（TIMES_???）时间系统，例如GPS时间*/
    int timef;          /* 时间格式（0:sssss.s,1:yyyy/mm/dd hh:mm:ss.s）时间的格式，可以是秒或者年月日时分秒等*/
    int timeu;          /* 时间小数位数时间小数点后的位数 */
    int degf;           /* 纬度/经度格式（0:ddd.ddd,1:ddd mm ss）纬度和经度的输出格式，可以是度和度分秒表示*/
    int outhead;        /* 输出头部（0:关闭,1:开启）是否输出头部信息*/
    int outopt;         /* 输出定位选项（0:关闭,1:开启）是否输出定位选项*/
    int outvel;         /* 输出速度选项（0:关闭,1:开启）是否输出速度选项*/
    int datum;          /* 大地基准改正（0:WGS84,1:Tokyo）使用的大地基准改正类型*/
    int height;         /* 高程类型（0:椭球面,1:大地测量）输出高程的类型，可以是椭球面高程或大地测量高程*/
    int geoid;          /* 大地高模型（0:EGM96,1:JGD2000）使用的大地高模型类型*/
    int solstatic;      /* 静态模式解（0:全部,1:单点）静态模式下的解类型，可以是全部卫星或单个卫星*/
    int sstat;          /* 解统计信息级别（0:关闭,1:状态,2:残差）解的统计信息的级别，可以是关闭、状态或残差*/
    int trace;          /* 调试追踪级别（0:关闭,1-5:调试）调试追踪的级别，可以是关闭或不同的调试级别*/
    double nmeaintv[2]; /* NMEA输出间隔时间（s）(<0:关闭,0:全部) NMEA输出的间隔时间，可以是关闭或不同的时间间隔*/
    /* nmeaintv[0]:gprmc,gpgga,nmeaintv[1]:gpgsv */
    char sep[64];       /* 字段分隔符 字段之间的分隔符*/
    char prog[64];      /* 程序名称 程序的名称*/
    double maxsolstd;   /* 解输出的最大标准差（m）(0:全部) 解输出的最大标准差，可以是全部或不同的值*/
} solopt_t;

typedef struct {        /* 文件设置file options type */
    char satantp[MAXSTRPATH];  /* 卫星天线参数文件路径 */
    char rcvantp[MAXSTRPATH];  /* 接收机天线参数文件路径 */
    char stapos[MAXSTRPATH];   /* 测站位置文件路径 */
    char geoid[MAXSTRPATH];    /* 外部大地高数据文件路径 */
    char iono[MAXSTRPATH];     /* 电离层数据文件路径 */
    char dcb[MAXSTRPATH];      /* DCB数据文件路径 */
    char eop[MAXSTRPATH];      /* EOP数据文件路径 */
    char blq[MAXSTRPATH];      /* 海洋潮汐负载BLQ文件路径 */
    char tempdir[MAXSTRPATH];  /* 临时目录路径，用于FTP/HTTP传输 */
    char geexe[MAXSTRPATH];    /* Google Earth执行文件路径 */
    char solstat[MAXSTRPATH];  /* 解统计文件路径 */
    char trace[MAXSTRPATH];    /* 调试追踪文件路径 */
} filopt_t;

typedef struct {        /* RINEX options type */
    gtime_t ts,te;      /* time start/end */
    double tint;        /* time interval (s) */
    double ttol;        /* time tolerance (s) */
    double tunit;       /* time unit for multiple-session (s) */
    int rnxver;         /* RINEX version (x100) */
    int navsys;         /* navigation system */
    int obstype;        /* observation type */
    int freqtype;       /* frequency type */
    char mask[7][64];   /* code mask {GPS,GLO,GAL,QZS,SBS,CMP,IRN} */
    char staid [32];    /* station id for rinex file name */
    char prog  [32];    /* program */
    char runby [32];    /* run-by */
    char marker[64];    /* marker name */
    char markerno[32];  /* marker number */
    char markertype[32]; /* marker type (ver.3) */
    char name[2][32];   /* observer/agency */
    char rec [3][32];   /* receiver #/type/vers */
    char ant [3][32];   /* antenna #/type */
    double apppos[3];   /* approx position x/y/z */
    double antdel[3];   /* antenna delta h/e/n */
    double glo_cp_bias[4]; /* GLONASS code-phase biases (m) */
    char comment[MAXCOMMENT][64]; /* comments */
    char rcvopt[256];   /* receiver dependent options */
    uint8_t exsats[MAXSAT]; /* excluded satellites */
    int glofcn[32];     /* glonass fcn+8 */
    int outiono;        /* output iono correction */
    int outtime;        /* output time system correction */
    int outleaps;       /* output leap seconds */
    int autopos;        /* auto approx position */
    int phshift;        /* phase shift correction */
    int halfcyc;        /* half cycle correction */
    int sep_nav;        /* separated nav files */
    gtime_t tstart;     /* first obs time */
    gtime_t tend;       /* last obs time */
    gtime_t trtcm;      /* approx log start time for rtcm */
    char tobs[7][MAXOBSTYPE][4]; /* obs types {GPS,GLO,GAL,QZS,SBS,CMP,IRN} */
    double shift[7][MAXOBSTYPE]; /* phase shift (cyc) {GPS,GLO,GAL,QZS,SBS,CMP,IRN} */
    int nobs[7];        /* number of obs types {GPS,GLO,GAL,QZS,SBS,CMP,IRN} */
} rnxopt_t;

typedef struct {        /* satellite status type (卫星状态类型) */
    uint8_t sys;        /* navigation system (导航系统) */
    uint8_t vs;         /* valid satellite flag single (单个卫星的有效标志) */
    double azel[2];     /* azimuth/elevation angles {az,el} (rad)
                           方位角/仰角（弧度）{az, el} */
    double resp[NFREQ]; /* residuals of pseudorange (m)
                           伪距残差（米） */
    double resc[NFREQ]; /* residuals of carrier-phase (m)
                           载波相位残差（米） */
    double icbias[NFREQ];  /* glonass IC bias (cycles)
                              GLONASS IC偏差（周） */
    uint8_t vsat[NFREQ]; /* valid satellite flag
                           卫星有效标志 */
    uint16_t snr_rover[NFREQ]; /* rover signal strength (0.25 dBHz)
                                   移动站信号强度（0.25 dBHz） */
    uint16_t snr_base[NFREQ]; /* base signal strength (0.25 dBHz)
                                   基站信号强度（0.25 dBHz） */
    uint8_t fix[NFREQ]; /* ambiguity fix flag (1:fix,2:float,3:hold)
                           模糊度解标志（1:固定，2:浮点，3:保持） */
    uint8_t slip[NFREQ]; /* cycle-slip flag
                           周跳标志 */
    uint8_t half[NFREQ]; /* half-cycle valid flag
                           半周有效标志 */
    int lock[NFREQ];   /* lock counter of phase
                           相位锁定计数器 */
    uint32_t outc[NFREQ]; /* obs outage counter of phase
                             相位观测缺失计数器 */
    uint32_t slipc[NFREQ]; /* cycle-slip counter
                             周跳计数器 */
    uint32_t rejc[NFREQ]; /* reject counter
                             拒绝计数器 */
    double gf[NFREQ - 1]; /* geometry-free phase (m)
                          几何无关相位（米） */
    double mw[NFREQ - 1]; /* MW-LC (m)
                          MW-LC（米） */
    double  phw;        /* phase windup (cycle)
                           相位回绕（周） */
    gtime_t pt[2][NFREQ]; /* previous carrier-phase time
                            前一次载波相位时间 */
    double  ph[2][NFREQ]; /* previous carrier-phase observable (cycle)
                            前一次载波相位观测量（周） */
} ssat_t;

typedef struct {        /* ambiguity control type */
    gtime_t epoch[4];   /* last epoch */
    int n[4];           /* number of epochs */
    double LC [4];      /* linear combination average */
    double LCv[4];      /* linear combination variance */
    int fixcnt;         /* fix count */
    char flags[MAXSAT]; /* fix flags */
} ambc_t;

typedef struct {        /* RTK control/result type (RTK 控制/结果类型)包含sol_t与prcopt_t结构体 */
    sol_t  sol;         /* RTK solution (RTK 解) */
    double rb[6];       /* base position/velocity (ecef) (m|m/s)
                           基准位置/速度（ECEF坐标系）（以米或米/秒表示）*/
    int nx, na;          /* number of float states/fixed states
                           浮点状态数/固定状态数 */
    double tt;          /* time difference between current and previous (s)
                           当前时刻与上一时刻的时间差（秒） */
    double* x, * P;      /* float states and their covariance EKF的x阵与p阵 
                           浮点状态及其协方差 x阵:xyz+若干dtr*+对流层+若干卫星的模糊度*/
    double* xa, * Pa;     /* fixed states and their covariance
                           固定状态及其协方差 */
    int nfix;           /* number of continuous fixes of ambiguity
                           模糊度的连续固定次数 */
    int excsat;         /* index of next satellite to be excluded for partial ambiguity resolution
                           下一个被排除的卫星索引, 用于部分模糊度解 */
    int nb_ar;          /* number of ambiguities used for AR last epoch
                           用于周跳修复的模糊度数量 */
    char holdamb;       /* set if fix-and-hold has occurred at least once
                           如果至少发生过一次固定和保持，则设置为 true */
    ambc_t ambc[MAXSAT]; /* ambiguity control
                           模糊度控制数组 */
    ssat_t ssat[MAXSAT]; /* satellite status
                           卫星状态数组 */
    int neb;            /* bytes in error message buffer
                           错误消息缓冲区中的字节数 */
    char errbuf[MAXERRMSG]; /* error message buffer
                               错误消息缓冲区 */
    prcopt_t opt;       /* processing options
                           处理选项 */
    int initial_mode;   /* initial positioning mode
                           初始定位模式 */
} rtk_t;

typedef struct {        /* receiver raw data control type */
    gtime_t time;       /* message time */
    gtime_t tobs[MAXSAT][NFREQ+NEXOBS]; /* observation data time */
    obs_t obs;          /* observation data */
    obs_t obuf;         /* observation data buffer */
    nav_t nav;          /* satellite ephemerides */
    sta_t sta;          /* station parameters */
    int ephsat;         /* update satelle of ephemeris (0:no satellite) */
    int ephset;         /* update set of ephemeris (0-1) */
    sbsmsg_t sbsmsg;    /* SBAS message */
    char msgtype[256];  /* last message type */
    uint8_t subfrm[MAXSAT][380]; /* subframe buffer */
    double lockt[MAXSAT][NFREQ+NEXOBS]; /* lock time (s) */
    unsigned char lockflag[MAXSAT][NFREQ+NEXOBS]; /* used for carrying forward cycle slip */
    double icpp[MAXSAT],off[MAXSAT],icpc; /* carrier params for ss2 */
    double prCA[MAXSAT],dpCA[MAXSAT]; /* L1/CA pseudrange/doppler for javad */
    uint8_t halfc[MAXSAT][NFREQ+NEXOBS]; /* half-cycle add flag */
    char freqn[MAXOBS]; /* frequency number for javad */
    int nbyte;          /* number of bytes in message buffer */ 
    int len;            /* message length (bytes) */
    int iod;            /* issue of data */
    int tod;            /* time of day (ms) */
    int tbase;          /* time base (0:gpst,1:utc(usno),2:glonass,3:utc(su) */
    int flag;           /* general purpose flag */
    int outtype;        /* output message type */
    uint8_t buff[MAXRAWLEN]; /* message buffer */
    char opt[256];      /* receiver dependent options */
    int format;         /* receiver stream format */
    int rcvtype;        /* receiver type within format */
    void *rcv_data;     /* receiver dependent data */
} raw_t;

typedef struct {        /* stream type */
    int type;           /* type (STR_???) */
    int mode;           /* mode (STR_MODE_?) */
    int state;          /* state (-1:error,0:close,1:open) */
    uint32_t inb,inr;   /* input bytes/rate */
    uint32_t outb,outr; /* output bytes/rate */
    uint32_t tick_i;    /* input tick tick */
    uint32_t tick_o;    /* output tick */
    uint32_t tact;      /* active tick */
    uint32_t inbt,outbt; /* input/output bytes at tick */
    lock_t lock;        /* lock flag */
    void *port;         /* type dependent port control struct */
    char path[MAXSTRPATH]; /* stream path */
    char msg [MAXSTRMSG];  /* stream message */
} stream_t;

typedef struct {        /* stream converter type */
    int itype,otype;    /* input and output stream type */
    int nmsg;           /* number of output messages */
    int msgs[32];       /* output message types */
    double tint[32];    /* output message intervals (s) */
    uint32_t tick[32];  /* cycle tick of output message */
    int ephsat[32];     /* satellites of output ephemeris */
    int stasel;         /* station info selection (0:remote,1:local) */
    rtcm_t rtcm;        /* rtcm input data buffer */
    raw_t raw;          /* raw  input data buffer */
    rtcm_t out;         /* rtcm output data buffer */
} strconv_t;

typedef struct {        /* stream server type */
    int state;          /* server state (0:stop,1:running) */
    int cycle;          /* server cycle (ms) */
    int buffsize;       /* input/monitor buffer size (bytes) */
    int nmeacycle;      /* NMEA request cycle (ms) (0:no) */
    int relayback;      /* relay back of output streams (0:no) */
    int nstr;           /* number of streams (1 input + (nstr-1) outputs */
    int npb;            /* data length in peek buffer (bytes) */
    char cmds_periodic[16][MAXRCVCMD]; /* periodic commands */
    double nmeapos[3];  /* NMEA request position (ecef) (m) */
    uint8_t *buff;      /* input buffers */
    uint8_t *pbuf;      /* peek buffer */
    uint32_t tick;      /* start tick */
    stream_t stream[16]; /* input/output streams */
    stream_t strlog[16]; /* return log streams */
    strconv_t *conv[16]; /* stream converter */
    thread_t thread;    /* server thread */
    lock_t lock;        /* lock flag */
} strsvr_t;

typedef struct {        /* RTK server type */
    int state;          /* server state (0:stop,1:running) */
    int cycle;          /* processing cycle (ms) */
    int nmeacycle;      /* NMEA request cycle (ms) (0:no req) */
    int nmeareq;        /* NMEA request (0:no,1:nmeapos,2:single sol) */
    double nmeapos[3];  /* NMEA request position (ecef) (m) */
    int buffsize;       /* input buffer size (bytes) */
    int format[3];      /* input format {rov,base,corr} */
    solopt_t solopt[2]; /* output solution options {sol1,sol2} */
    int navsel;         /* ephemeris select (0:all,1:rover,2:base,3:corr) */
    int nsbs;           /* number of sbas message */
    int nsol;           /* number of solution buffer */
    rtk_t rtk;          /* RTK control/result struct */
    int nb [3];         /* bytes in input buffers {rov,base} */
    int nsb[2];         /* bytes in soulution buffers */
    int npb[3];         /* bytes in input peek buffers */
    uint8_t *buff[3];   /* input buffers {rov,base,corr} */
    uint8_t *sbuf[2];   /* output buffers {sol1,sol2} */
    uint8_t *pbuf[3];   /* peek buffers {rov,base,corr} */
    sol_t solbuf[MAXSOLBUF]; /* solution buffer */
    uint32_t nmsg[3][10]; /* input message counts */
    raw_t  raw [3];     /* receiver raw control {rov,base,corr} */
    rtcm_t rtcm[3];     /* RTCM control {rov,base,corr} */
    gtime_t ftime[3];   /* download time {rov,base,corr} */
    char files[3][MAXSTRPATH]; /* download paths {rov,base,corr} */
    obs_t obs[3][MAXOBSBUF]; /* observation data {rov,base,corr} */
    nav_t nav;          /* navigation data */
    sbsmsg_t sbsmsg[MAXSBSMSG]; /* SBAS message buffer */
    stream_t stream[8]; /* streams {rov,base,corr,sol1,sol2,logr,logb,logc} */
    stream_t *moni;     /* monitor stream */
    uint32_t tick;      /* start tick */
    thread_t thread;    /* server thread */
    int cputime;        /* CPU time (ms) for a processing cycle */
    int prcout;         /* missing observation data count */
    int nave;           /* number of averaging base pos */
    double rb_ave[3];   /* averaging base pos */
    char cmds_periodic[3][MAXRCVCMD]; /* periodic commands */
    char cmd_reset[MAXRCVCMD]; /* reset command */
    double bl_reset;    /* baseline length to reset (km) */
    lock_t lock;        /* lock flag */
} rtksvr_t;

typedef struct {        /* GIS data point type */
    double pos[3];      /* point data {lat,lon,height} (rad,m) */
} gis_pnt_t;

typedef struct {        /* GIS data polyline type */
    int npnt;           /* number of points */
    double bound[4];    /* boundary {lat0,lat1,lon0,lon1} */
    double *pos;        /* position data (3 x npnt) */
} gis_poly_t;

typedef struct {        /* GIS data polygon type */
    int npnt;           /* number of points */
    double bound[4];    /* boundary {lat0,lat1,lon0,lon1} */
    double *pos;        /* position data (3 x npnt) */
} gis_polygon_t;

typedef struct gisd_tag { /* GIS data list type */
    int type;           /* data type (1:point,2:polyline,3:polygon) */
    void *data;         /* data body */
    struct gisd_tag *next; /* pointer to next */
} gisd_t;

typedef struct {        /* GIS type */
    char name[MAXGISLAYER][256]; /* name */
    int flag[MAXGISLAYER];     /* flag */
    gisd_t *data[MAXGISLAYER]; /* gis data list */
    double bound[4];    /* boundary {lat0,lat1,lon0,lon1} */
} gis_t;

typedef void fatalfunc_t(const char *); /* fatal callback function type */

/* global variables ----------------------------------------------------------*/
extern const double chisqr[];        /* chi-sqr(n) table (alpha=0.001) */
extern const prcopt_t prcopt_default; /* default positioning options */
extern const solopt_t solopt_default; /* default solution output options */
extern const sbsigpband_t igpband1[9][8]; /* SBAS IGP band 0-8 */
extern const sbsigpband_t igpband2[2][5]; /* SBAS IGP band 9-10 */
extern const char *formatstrs[];     /* stream format strings */
extern opt_t sysopts[];              /* system options table */

/* satellites, systems, codes functions --------------------------------------*/
EXPORT int  satno   (int sys, int prn);
EXPORT int  satsys  (int sat, int *prn);
EXPORT int  satid2no(const char *id);
EXPORT void satno2id(int sat, char *id);
EXPORT uint8_t obs2code(const char *obs);
EXPORT char *code2obs(uint8_t code);
EXPORT double code2freq(int sys, uint8_t code, int fcn);
EXPORT double sat2freq(int sat, uint8_t code, const nav_t *nav);
EXPORT int  code2idx(int sys, uint8_t code);
EXPORT int  satexclude(int sat, double var, int svh, const prcopt_t *opt);
EXPORT int  testsnr(int base, int freq, double el, double snr,
                    const snrmask_t *mask);
EXPORT void setcodepri(int sys, int idx, const char *pri);
EXPORT int  getcodepri(int sys, uint8_t code, const char *opt);

/* matrix and vector functions -----------------------------------------------*/
EXPORT double *mat  (int n, int m);
EXPORT int    *imat (int n, int m);
EXPORT double *zeros(int n, int m);
EXPORT double *eye  (int n);
EXPORT double dot (const double *a, const double *b, int n);
EXPORT double norm(const double *a, int n);
EXPORT void cross3(const double *a, const double *b, double *c);
EXPORT int  normv3(const double *a, double *b);
EXPORT void matcpy(double *A, const double *B, int n, int m);
EXPORT void matmul(const char *tr, int n, int k, int m, double alpha,
                   const double *A, const double *B, double beta, double *C);
EXPORT int  matinv(double *A, int n);
EXPORT int  solve (const char *tr, const double *A, const double *Y, int n,
                   int m, double *X);
EXPORT int  lsq   (const double *A, const double *y, int n, int m, double *x,
                   double *Q);
EXPORT int  filter(double *x, double *P, const double *H, const double *v,
                   const double *R, int n, int m);
EXPORT int  smoother(const double *xf, const double *Qf, const double *xb,
                     const double *Qb, int n, double *xs, double *Qs);
EXPORT void matprint (const double *A, int n, int m, int p, int q);
EXPORT void matfprint(const double *A, int n, int m, int p, int q, FILE *fp);

EXPORT void add_fatal(fatalfunc_t *func);

/* time and string functions -------------------------------------------------*/
EXPORT double  str2num(const char *s, int i, int n);
EXPORT int     str2time(const char *s, int i, int n, gtime_t *t);
EXPORT void    time2str(gtime_t t, char *str, int n);
EXPORT gtime_t epoch2time(const double *ep);
EXPORT void    time2epoch(gtime_t t, double *ep);
EXPORT void    time2epoch_n(gtime_t t, double *ep, int n);
EXPORT gtime_t gpst2time(int week, double sec);
EXPORT double  time2gpst(gtime_t t, int *week);
EXPORT gtime_t gst2time(int week, double sec);
EXPORT double  time2gst(gtime_t t, int *week);
EXPORT gtime_t bdt2time(int week, double sec);
EXPORT double  time2bdt(gtime_t t, int *week);
EXPORT char    *time_str(gtime_t t, int n);

EXPORT gtime_t timeadd  (gtime_t t, double sec);
EXPORT double  timediff (gtime_t t1, gtime_t t2);
EXPORT gtime_t gpst2utc (gtime_t t);
EXPORT gtime_t utc2gpst (gtime_t t);
EXPORT gtime_t gpst2bdt (gtime_t t);
EXPORT gtime_t bdt2gpst (gtime_t t);
EXPORT gtime_t timeget  (void);
EXPORT void    timeset  (gtime_t t);
EXPORT void    timereset(void);
EXPORT double  time2doy (gtime_t t);
EXPORT double  utc2gmst (gtime_t t, double ut1_utc);
EXPORT int read_leaps(const char *file);

EXPORT int adjgpsweek(int week);
EXPORT uint32_t tickget(void);
EXPORT void sleepms(int ms);

EXPORT int reppath(const char *path, char *rpath, gtime_t time, const char *rov,
                   const char *base);
EXPORT int reppaths(const char *path, char *rpaths[], int nmax, gtime_t ts,
                    gtime_t te, const char *rov, const char *base);

/* coordinates transformation ------------------------------------------------*/
EXPORT void ecef2pos(const double *r, double *pos);
EXPORT void pos2ecef(const double *pos, double *r);
EXPORT void ecef2enu(const double *pos, const double *r, double *e);
EXPORT void enu2ecef(const double *pos, const double *e, double *r);
EXPORT void covenu  (const double *pos, const double *P, double *Q);
EXPORT void covecef (const double *pos, const double *Q, double *P);
EXPORT void xyz2enu (const double *pos, double *E);
EXPORT void eci2ecef(gtime_t tutc, const double *erpv, double *U, double *gmst);
EXPORT void deg2dms (double deg, double *dms, int ndec);
EXPORT double dms2deg(const double *dms);

/* input and output functions ------------------------------------------------*/
EXPORT void readpos(const char *file, const char *rcv, double *pos);
EXPORT int  sortobs(obs_t *obs);
EXPORT void uniqnav(nav_t *nav);
EXPORT int  screent(gtime_t time, gtime_t ts, gtime_t te, double tint);
EXPORT int  readnav(const char *file, nav_t *nav);
EXPORT int  savenav(const char *file, const nav_t *nav);
EXPORT void freeobs(obs_t *obs);
EXPORT void freenav(nav_t *nav, int opt);
EXPORT int  readblq(const char *file, const char *sta, double *odisp);
EXPORT int  readerp(const char *file, erp_t *erp);
EXPORT int  geterp (const erp_t *erp, gtime_t time, double *val);

/* debug trace functions -----------------------------------------------------*/
EXPORT void traceopen(const char *file);
EXPORT void traceclose(void);
EXPORT void tracelevel(int level);
EXPORT void trace    (int level, const char *format, ...);
EXPORT void tracet   (int level, const char *format, ...);
EXPORT void tracemat (int level, const double *A, int n, int m, int p, int q);
EXPORT void traceobs (int level, const obsd_t *obs, int n);
EXPORT void tracenav (int level, const nav_t *nav);
EXPORT void tracegnav(int level, const nav_t *nav);
EXPORT void tracehnav(int level, const nav_t *nav);
EXPORT void tracepeph(int level, const nav_t *nav);
EXPORT void tracepclk(int level, const nav_t *nav);
EXPORT void traceb   (int level, const uint8_t *p, int n);
EXPORT int gettracelevel(void);

/* platform dependent functions ----------------------------------------------*/
EXPORT int execcmd(const char *cmd);
EXPORT int expath (const char *path, char *paths[], int nmax);
EXPORT void createdir(const char *path);

/* positioning models --------------------------------------------------------*/
EXPORT double satazel(const double *pos, const double *e, double *azel);
EXPORT double geodist(const double *rs, const double *rr, double *e);
EXPORT void dops(int ns, const double *azel, double elmin, double *dop);

/* atmosphere models ---------------------------------------------------------*/
EXPORT double ionmodel(gtime_t t, const double *ion, const double *pos,
                       const double *azel);
EXPORT double ionmapf(const double *pos, const double *azel);
EXPORT double ionppp(const double *pos, const double *azel, double re,
                     double hion, double *pppos);
EXPORT double tropmodel(gtime_t time, const double *pos, const double *azel,
                        double humi);
EXPORT double tropmapf(gtime_t time, const double *pos, const double *azel,
                       double *mapfw);
EXPORT int iontec(gtime_t time, const nav_t *nav, const double *pos,
                  const double *azel, int opt, double *delay, double *var);
EXPORT void readtec(const char *file, nav_t *nav, int opt);
EXPORT int ionocorr(gtime_t time, const nav_t *nav, int sat, const double *pos,
                    const double *azel, int ionoopt, double *ion, double *var);
EXPORT int tropcorr(gtime_t time, const nav_t *nav, const double *pos,
                    const double *azel, int tropopt, double *trp, double *var);
EXPORT int seliflc(int optnf, int sys);

/* antenna models ------------------------------------------------------------*/
EXPORT int  readpcv(const char *file, pcvs_t *pcvs);
EXPORT pcv_t *searchpcv(int sat, const char *type, gtime_t time,
                        const pcvs_t *pcvs);
EXPORT void antmodel(const pcv_t *pcv, const double *del, const double *azel,
                     int opt, double *dant);
EXPORT void antmodel_s(const pcv_t *pcv, double nadir, double *dant);

/* earth tide models ---------------------------------------------------------*/
EXPORT void sunmoonpos(gtime_t tutc, const double *erpv, double *rsun,
                       double *rmoon, double *gmst);
EXPORT void tidedisp(gtime_t tutc, const double *rr, int opt, const erp_t *erp,
                     const double *odisp, double *dr);

/* geiod models --------------------------------------------------------------*/
EXPORT int opengeoid(int model, const char *file);
EXPORT void closegeoid(void);
EXPORT double geoidh(const double *pos);

/* datum transformation ------------------------------------------------------*/
EXPORT int loaddatump(const char *file);
EXPORT int tokyo2jgd(double *pos);
EXPORT int jgd2tokyo(double *pos);

/* rinex functions -----------------------------------------------------------*/
EXPORT int readrnx (const char *file, int rcv, const char *opt, obs_t *obs,
                    nav_t *nav, sta_t *sta);
EXPORT int readrnxt(const char *file, int rcv, gtime_t ts, gtime_t te,
                    double tint, const char *opt, obs_t *obs, nav_t *nav,
                    sta_t *sta);
EXPORT int readrnxc(const char *file, nav_t *nav);
EXPORT int outrnxobsh(FILE *fp, const rnxopt_t *opt, const nav_t *nav);
EXPORT int outrnxobsb(FILE *fp, const rnxopt_t *opt, const obsd_t *obs, int n,
                      int epflag);
EXPORT int outrnxnavh (FILE *fp, const rnxopt_t *opt, const nav_t *nav);
EXPORT int outrnxgnavh(FILE *fp, const rnxopt_t *opt, const nav_t *nav);
EXPORT int outrnxhnavh(FILE *fp, const rnxopt_t *opt, const nav_t *nav);
EXPORT int outrnxlnavh(FILE *fp, const rnxopt_t *opt, const nav_t *nav);
EXPORT int outrnxqnavh(FILE *fp, const rnxopt_t *opt, const nav_t *nav);
EXPORT int outrnxcnavh(FILE *fp, const rnxopt_t *opt, const nav_t *nav);
EXPORT int outrnxinavh(FILE *fp, const rnxopt_t *opt, const nav_t *nav);
EXPORT int outrnxnavb (FILE *fp, const rnxopt_t *opt, const eph_t *eph);
EXPORT int outrnxgnavb(FILE *fp, const rnxopt_t *opt, const geph_t *geph);
EXPORT int outrnxhnavb(FILE *fp, const rnxopt_t *opt, const seph_t *seph);
EXPORT int rtk_uncompress(const char *file, char *uncfile);
EXPORT int convrnx(int format, rnxopt_t *opt, const char *file, char **ofile);
EXPORT int  init_rnxctr (rnxctr_t *rnx);
EXPORT void free_rnxctr (rnxctr_t *rnx);
EXPORT int  open_rnxctr (rnxctr_t *rnx, FILE *fp);
EXPORT int  input_rnxctr(rnxctr_t *rnx, FILE *fp);

/* ephemeris and clock functions ---------------------------------------------*/
EXPORT double eph2clk (gtime_t time, const eph_t  *eph);
EXPORT double geph2clk(gtime_t time, const geph_t *geph);
EXPORT double seph2clk(gtime_t time, const seph_t *seph);
EXPORT void eph2pos (gtime_t time, const eph_t  *eph,  double *rs, double *dts,
                     double *var);
EXPORT void geph2pos(gtime_t time, const geph_t *geph, double *rs, double *dts,
                     double *var);
EXPORT void seph2pos(gtime_t time, const seph_t *seph, double *rs, double *dts,
                     double *var);
EXPORT int  peph2pos(gtime_t time, int sat, const nav_t *nav, int opt,
                     double *rs, double *dts, double *var);
EXPORT void satantoff(gtime_t time, const double *rs, int sat, const nav_t *nav,
                      double *dant);
EXPORT int  satpos(gtime_t time, gtime_t teph, int sat, int ephopt,
                   const nav_t *nav, double *rs, double *dts, double *var,
                   int *svh);
EXPORT void satposs(gtime_t time, const obsd_t *obs, int n, const nav_t *nav,
                    int sateph, double *rs, double *dts, double *var, int *svh);
EXPORT void setseleph(int sys, int sel);
EXPORT int  getseleph(int sys);
EXPORT void readsp3(const char *file, nav_t *nav, int opt);
EXPORT int  readsap(const char *file, gtime_t time, nav_t *nav);
EXPORT int  readdcb(const char *file, nav_t *nav, const sta_t *sta);
EXPORT int  readfcb(const char *file, nav_t *nav);
EXPORT void alm2pos(gtime_t time, const alm_t *alm, double *rs, double *dts);

EXPORT int tle_read(const char *file, tle_t *tle);
EXPORT int tle_name_read(const char *file, tle_t *tle);
EXPORT int tle_pos(gtime_t time, const char *name, const char *satno,
                   const char *desig, const tle_t *tle, const erp_t *erp,
                   double *rs);

/* receiver raw data functions -----------------------------------------------*/
EXPORT uint32_t getbitu(const uint8_t *buff, int pos, int len);
EXPORT int32_t  getbits(const uint8_t *buff, int pos, int len);
EXPORT void setbitu(uint8_t *buff, int pos, int len, uint32_t data);
EXPORT void setbits(uint8_t *buff, int pos, int len, int32_t  data);
EXPORT uint32_t rtk_crc32 (const uint8_t *buff, int len);
EXPORT uint32_t rtk_crc24q(const uint8_t *buff, int len);
EXPORT uint16_t rtk_crc16 (const uint8_t *buff, int len);
EXPORT int decode_word (uint32_t word, uint8_t *data);
EXPORT int decode_frame(const uint8_t *buff, eph_t *eph, alm_t *alm,
                        double *ion, double *utc);
EXPORT int test_glostr(const uint8_t *buff);
EXPORT int decode_glostr(const uint8_t *buff, geph_t *geph, double *utc);
EXPORT int decode_bds_d1(const uint8_t *buff, eph_t *eph, double *ion,
                         double *utc);
EXPORT int decode_bds_d2(const uint8_t *buff, eph_t *eph, double *utc);
EXPORT int decode_gal_inav(const uint8_t *buff, eph_t *eph, double *ion,
                           double *utc);
EXPORT int decode_gal_fnav(const uint8_t *buff, eph_t *eph, double *ion,
                           double *utc);
EXPORT int decode_irn_nav(const uint8_t *buff, eph_t *eph, double *ion,
                          double *utc);

EXPORT int init_raw   (raw_t *raw, int format);
EXPORT void free_raw  (raw_t *raw);
EXPORT int input_raw  (raw_t *raw, int format, uint8_t data);
EXPORT int input_rawf (raw_t *raw, int format, FILE *fp);

EXPORT int init_rt17  (raw_t *raw);
EXPORT int init_cmr   (raw_t *raw);
EXPORT void free_rt17 (raw_t *raw);
EXPORT void free_cmr  (raw_t *raw);
EXPORT int update_cmr (raw_t *raw, rtksvr_t *svr, obs_t *obs);

EXPORT int input_oem4  (raw_t *raw, uint8_t data);
EXPORT int input_cnav  (raw_t *raw, uint8_t data);
EXPORT int input_ubx   (raw_t *raw, uint8_t data);
EXPORT int input_sbp   (raw_t *raw, uint8_t data);
EXPORT int input_cres  (raw_t *raw, uint8_t data);
EXPORT int input_stq   (raw_t *raw, uint8_t data);
EXPORT int input_javad (raw_t *raw, uint8_t data);
EXPORT int input_nvs   (raw_t *raw, uint8_t data);
EXPORT int input_bnx   (raw_t *raw, uint8_t data);
EXPORT int input_rt17  (raw_t *raw, uint8_t data);
EXPORT int input_sbf   (raw_t *raw, uint8_t data);
EXPORT int input_tersus(raw_t *raw, uint8_t data);
EXPORT int input_oem4f (raw_t *raw, FILE *fp);
EXPORT int input_cnavf (raw_t *raw, FILE *fp);
EXPORT int input_ubxf  (raw_t *raw, FILE *fp);
EXPORT int input_sbpf  (raw_t *raw, FILE *fp);
EXPORT int input_cresf (raw_t *raw, FILE *fp);
EXPORT int input_stqf  (raw_t *raw, FILE *fp);
EXPORT int input_javadf(raw_t *raw, FILE *fp);
EXPORT int input_nvsf  (raw_t *raw, FILE *fp);
EXPORT int input_bnxf  (raw_t *raw, FILE *fp);
EXPORT int input_rt17f (raw_t *raw, FILE *fp);
EXPORT int input_sbff  (raw_t *raw, FILE *fp);
EXPORT int input_tersusf(raw_t *raw, FILE *fp);

EXPORT int gen_ubx (const char *msg, uint8_t *buff);
EXPORT int gen_stq (const char *msg, uint8_t *buff);
EXPORT int gen_nvs (const char *msg, uint8_t *buff);

/* rtcm functions ------------------------------------------------------------*/
EXPORT int init_rtcm   (rtcm_t *rtcm);
EXPORT void free_rtcm  (rtcm_t *rtcm);
EXPORT int input_rtcm2 (rtcm_t *rtcm, uint8_t data);
EXPORT int input_rtcm3 (rtcm_t *rtcm, uint8_t data);
EXPORT int input_rtcm2f(rtcm_t *rtcm, FILE *fp);
EXPORT int input_rtcm3f(rtcm_t *rtcm, FILE *fp);
EXPORT int gen_rtcm2   (rtcm_t *rtcm, int type, int sync);
EXPORT int gen_rtcm3   (rtcm_t *rtcm, int type, int subtype, int sync);

/* solution functions --------------------------------------------------------*/
EXPORT void initsolbuf(solbuf_t *solbuf, int cyclic, int nmax);
EXPORT void freesolbuf(solbuf_t *solbuf);
EXPORT void freesolstatbuf(solstatbuf_t *solstatbuf);
EXPORT sol_t *getsol(solbuf_t *solbuf, int index);
EXPORT int addsol(solbuf_t *solbuf, const sol_t *sol);
EXPORT int readsol (char *files[], int nfile, solbuf_t *sol);
EXPORT int readsolt(char *files[], int nfile, gtime_t ts, gtime_t te,
                    double tint, int qflag, solbuf_t *sol);
EXPORT int readsolstat(char *files[], int nfile, solstatbuf_t *statbuf);
EXPORT int readsolstatt(char *files[], int nfile, gtime_t ts, gtime_t te,
                        double tint, solstatbuf_t *statbuf);
EXPORT int inputsol(uint8_t data, gtime_t ts, gtime_t te, double tint,
                    int qflag, const solopt_t *opt, solbuf_t *solbuf);

EXPORT int outprcopts(uint8_t *buff, const prcopt_t *opt);
EXPORT int outsolheads(uint8_t *buff, const solopt_t *opt);
EXPORT int outsols  (uint8_t *buff, const sol_t *sol, const double *rb,
                     const solopt_t *opt);
EXPORT int outsolexs(uint8_t *buff, const sol_t *sol, const ssat_t *ssat,
                     const solopt_t *opt);
EXPORT void outprcopt(FILE *fp, const prcopt_t *opt);
EXPORT void outsolhead(FILE *fp, const solopt_t *opt);
EXPORT void outsol  (FILE *fp, const sol_t *sol, const double *rb,
                     const solopt_t *opt);
EXPORT void outsolex(FILE *fp, const sol_t *sol, const ssat_t *ssat,
                     const solopt_t *opt);
EXPORT int outnmea_rmc(uint8_t *buff, const sol_t *sol);
EXPORT int outnmea_gga(uint8_t *buff, const sol_t *sol);
EXPORT int outnmea_gsa(uint8_t *buff, const sol_t *sol,
                       const ssat_t *ssat);
EXPORT int outnmea_gsv(uint8_t *buff, const sol_t *sol,
                       const ssat_t *ssat);

/* google earth kml converter ------------------------------------------------*/
EXPORT int convkml(const char *infile, const char *outfile, gtime_t ts,
                   gtime_t te, double tint, int qflg, double *offset,
                   int tcolor, int pcolor, int outalt, int outtime);

/* gpx converter -------------------------------------------------------------*/
EXPORT int convgpx(const char *infile, const char *outfile, gtime_t ts,
                   gtime_t te, double tint, int qflg, double *offset,
                   int outtrk, int outpnt, int outalt, int outtime);

/* sbas functions ------------------------------------------------------------*/
EXPORT int  sbsreadmsg (const char *file, int sel, sbs_t *sbs);
EXPORT int  sbsreadmsgt(const char *file, int sel, gtime_t ts, gtime_t te,
                        sbs_t *sbs);
EXPORT void sbsoutmsg(FILE *fp, sbsmsg_t *sbsmsg);
EXPORT int  sbsdecodemsg(gtime_t time, int prn, const uint32_t *words,
                         sbsmsg_t *sbsmsg);
EXPORT int sbsupdatecorr(const sbsmsg_t *msg, nav_t *nav);
EXPORT int sbssatcorr(gtime_t time, int sat, const nav_t *nav, double *rs,
                      double *dts, double *var);
EXPORT int sbsioncorr(gtime_t time, const nav_t *nav, const double *pos,
                      const double *azel, double *delay, double *var);
EXPORT double sbstropcorr(gtime_t time, const double *pos, const double *azel,
                          double *var);

/* options functions ---------------------------------------------------------*/
EXPORT opt_t *searchopt(const char *name, const opt_t *opts);
EXPORT int str2opt(opt_t *opt, const char *str);
EXPORT int opt2str(const opt_t *opt, char *str);
EXPORT int opt2buf(const opt_t *opt, char *buff);
EXPORT int loadopts(const char *file, opt_t *opts);
EXPORT int saveopts(const char *file, const char *mode, const char *comment,
                    const opt_t *opts);
EXPORT void resetsysopts(void);
EXPORT void getsysopts(prcopt_t *popt, solopt_t *sopt, filopt_t *fopt);
EXPORT void setsysopts(const prcopt_t *popt, const solopt_t *sopt,
                       const filopt_t *fopt);

/* stream data input and output functions ------------------------------------*/
EXPORT void strinitcom(void);
EXPORT void strinit  (stream_t *stream);
EXPORT void strlock  (stream_t *stream);
EXPORT void strunlock(stream_t *stream);
EXPORT int  stropen  (stream_t *stream, int type, int mode, const char *path);
EXPORT void strclose (stream_t *stream);
EXPORT int  strread  (stream_t *stream, uint8_t *buff, int n);
EXPORT int  strwrite (stream_t *stream, uint8_t *buff, int n);
EXPORT void strsync  (stream_t *stream1, stream_t *stream2);
EXPORT int  strstat  (stream_t *stream, char *msg);
EXPORT int  strstatx (stream_t *stream, char *msg);
EXPORT void strsum   (stream_t *stream, int *inb, int *inr, int *outb, int *outr);
EXPORT void strsetopt(const int *opt);
EXPORT gtime_t strgettime(stream_t *stream);
EXPORT void strsendnmea(stream_t *stream, const sol_t *sol);
EXPORT void strsendcmd(stream_t *stream, const char *cmd);
EXPORT void strsettimeout(stream_t *stream, int toinact, int tirecon);
EXPORT void strsetdir(const char *dir);
EXPORT void strsetproxy(const char *addr);

/* integer ambiguity resolution ----------------------------------------------*/
EXPORT int lambda(int n, int m, const double *a, const double *Q, double *F,
                  double *s);
EXPORT int lambda_reduction(int n, const double *Q, double *Z);
EXPORT int lambda_search(int n, int m, const double *a, const double *Q,
                         double *F, double *s);

/* standard positioning ------------------------------------------------------*/
EXPORT int pntpos(const obsd_t *obs, int n, const nav_t *nav,
                  const prcopt_t *opt, sol_t *sol, double *azel,
                  ssat_t *ssat, char *msg);

/* precise positioning -------------------------------------------------------*/
EXPORT void rtkinit(rtk_t *rtk, const prcopt_t *opt);
EXPORT void rtkfree(rtk_t *rtk);
EXPORT int  rtkpos (rtk_t *rtk, const obsd_t *obs, int nobs, const nav_t *nav);
EXPORT int  rtkopenstat(const char *file, int level);
EXPORT void rtkclosestat(void);
EXPORT int  rtkoutstat(rtk_t *rtk, char *buff);

/* precise point positioning -------------------------------------------------*/
EXPORT void pppos(rtk_t *rtk, const obsd_t *obs, int n, const nav_t *nav);
EXPORT int pppnx(const prcopt_t *opt);
EXPORT int pppoutstat(rtk_t *rtk, char *buff);

EXPORT int ppp_ar(rtk_t *rtk, const obsd_t *obs, int n, int *exc,
                  const nav_t *nav, const double *azel, double *x, double *P);

/* post-processing positioning -----------------------------------------------*/
EXPORT int postpos(gtime_t ts, gtime_t te, double ti, double tu,
                   const prcopt_t *popt, const solopt_t *sopt,
                   const filopt_t *fopt, char **infile, int n, char *outfile,
                   const char *rov, const char *base);

/* stream server functions ---------------------------------------------------*/
EXPORT void strsvrinit (strsvr_t *svr, int nout);
EXPORT int  strsvrstart(strsvr_t *svr, int *opts, int *strs, char **paths,
                        char **logs, strconv_t **conv, char **cmds,
                        char **cmds_priodic, const double *nmeapos);
EXPORT void strsvrstop (strsvr_t *svr, char **cmds);
EXPORT void strsvrstat (strsvr_t *svr, int *stat, int *log_stat, int *byte,
                        int *bps, char *msg);
EXPORT strconv_t *strconvnew(int itype, int otype, const char *msgs, int staid,
                             int stasel, const char *opt);
EXPORT void strconvfree(strconv_t *conv);

/* rtk server functions ------------------------------------------------------*/
EXPORT int  rtksvrinit  (rtksvr_t *svr);
EXPORT void rtksvrfree  (rtksvr_t *svr);
EXPORT int  rtksvrstart (rtksvr_t *svr, int cycle, int buffsize, int *strs,
                         char **paths, int *formats, int navsel, char **cmds,
                         char **cmds_periodic, char **rcvopts, int nmeacycle,
                         int nmeareq, const double *nmeapos, prcopt_t *prcopt,
                         solopt_t *solopt, stream_t *moni, char *errmsg);
EXPORT void rtksvrstop  (rtksvr_t *svr, char **cmds);
EXPORT int  rtksvropenstr(rtksvr_t *svr, int index, int str, const char *path,
                          const solopt_t *solopt);
EXPORT void rtksvrclosestr(rtksvr_t *svr, int index);
EXPORT void rtksvrlock  (rtksvr_t *svr);
EXPORT void rtksvrunlock(rtksvr_t *svr);
EXPORT int  rtksvrostat (rtksvr_t *svr, int type, gtime_t *time, int *sat,
                         double *az, double *el, int **snr, int *vsat);
EXPORT void rtksvrsstat (rtksvr_t *svr, int *sstat, char *msg);
EXPORT int  rtksvrmark(rtksvr_t *svr, const char *name, const char *comment);

/* downloader functions ------------------------------------------------------*/
EXPORT int dl_readurls(const char *file, char **types, int ntype, url_t *urls,
                       int nmax);
EXPORT int dl_readstas(const char *file, char **stas, int nmax);
EXPORT int dl_exec(gtime_t ts, gtime_t te, double ti, int seqnos, int seqnoe,
                   const url_t *urls, int nurl, char **stas, int nsta,
                   const char *dir, const char *usr, const char *pwd,
                   const char *proxy, int opts, char *msg, FILE *fp);
EXPORT void dl_test(gtime_t ts, gtime_t te, double ti, const url_t *urls,
                    int nurl, char **stas, int nsta, const char *dir,
                    int ncol, int datefmt, FILE *fp);

/* GIS data functions --------------------------------------------------------*/
EXPORT int gis_read(const char *file, gis_t *gis, int layer);
EXPORT void gis_free(gis_t *gis);

/* application defined functions ---------------------------------------------*/
extern int showmsg(const char *format,...);
extern void settspan(gtime_t ts, gtime_t te);
extern void settime(gtime_t time);

#ifdef __cplusplus
}
#endif
#endif /* RTKLIB_H */
