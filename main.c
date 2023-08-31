#include "rtklib.h"
#define PROGNAME    "rnx2rtkp"          /* program name */
#define MAXFILE     16                  /* max number of input files */
#include <stdarg.h>

int main(int argc, char** argv)
{
    gtime_t ts = { 0 }, te = { 0 };/*开始时间结束时间*/
	prcopt_t prcopt = prcopt_default;
	solopt_t solopt = solopt_default;
	filopt_t filopt = { 0 };

	double tint = 0.0, es[] = { 2000,1,1,0,0,0 }, ee[] = { 2000,12,31,23,59,59 }, pos[3];
	int i, j, n, ret;
    char* infile[MAXFILE], * outfile = "";
    char *p;


    /*char* infile[] = {
        "E:\\2023RTKLIB\\data\\test_PPP\\data\\obs\\2022\\244\\MGEX\\daily\\abmf2440.22o",
        "E:\\2023RTKLIB\\data\\test_PPP\\data\\nav\\2022\\244\\daily\\BRDC00IGS_R_20222440000_01D_MN.rnx"
	};
	
    char* outfile = "E:\\2023RTKLIB\\data\\abmf2440.pos";*/

    /* load options from configuration file */
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-k") && i + 1 < argc) {
            resetsysopts();
            if (!loadopts(argv[++i], sysopts)) return -1;
            getsysopts(&prcopt, &solopt, &filopt);
        }
    }
    for (i = 1, n = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-o") && i + 1 < argc) outfile = argv[++i];
        else if (!strcmp(argv[i], "-ts") && i + 2 < argc) {
            sscanf(argv[++i], "%lf/%lf/%lf", es, es + 1, es + 2);
            sscanf(argv[++i], "%lf:%lf:%lf", es + 3, es + 4, es + 5);
            ts = epoch2time(es);
        }
        else if (!strcmp(argv[i], "-te") && i + 2 < argc) {
            sscanf(argv[++i], "%lf/%lf/%lf", ee, ee + 1, ee + 2);
            sscanf(argv[++i], "%lf:%lf:%lf", ee + 3, ee + 4, ee + 5);
            te = epoch2time(ee);
        }
        else if (!strcmp(argv[i], "-ti") && i + 1 < argc) tint = atof(argv[++i]);
        else if (!strcmp(argv[i], "-k") && i + 1 < argc) { ++i; continue; }
        else if (!strcmp(argv[i], "-p") && i + 1 < argc) prcopt.mode = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-f") && i + 1 < argc) prcopt.nf = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-sys") && i + 1 < argc) {
            for (p = argv[++i]; *p; p++) {
                switch (*p) {
                case 'G': prcopt.navsys |= SYS_GPS; break;
                case 'R': prcopt.navsys |= SYS_GLO; break;
                case 'E': prcopt.navsys |= SYS_GAL; break;
                case 'J': prcopt.navsys |= SYS_QZS; break;
                case 'C': prcopt.navsys |= SYS_CMP; break;
                case 'I': prcopt.navsys |= SYS_IRN; break;
                }
                if (!(p = strchr(p, ','))) break;
            }
        }
        else if (!strcmp(argv[i], "-m") && i + 1 < argc) prcopt.elmin = atof(argv[++i]) * D2R;
        else if (!strcmp(argv[i], "-v") && i + 1 < argc) prcopt.thresar[0] = atof(argv[++i]);
        else if (!strcmp(argv[i], "-s") && i + 1 < argc) strcpy(solopt.sep, argv[++i]);
        else if (!strcmp(argv[i], "-d") && i + 1 < argc) solopt.timeu = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-b")) prcopt.soltype = 1;
        else if (!strcmp(argv[i], "-c")) prcopt.soltype = 2;
        else if (!strcmp(argv[i], "-i")) prcopt.modear = 2;
        else if (!strcmp(argv[i], "-h")) prcopt.modear = 3;
        else if (!strcmp(argv[i], "-t")) solopt.timef = 1;
        else if (!strcmp(argv[i], "-u")) solopt.times = TIMES_UTC;
        else if (!strcmp(argv[i], "-e")) solopt.posf = SOLF_LLH;
        else if (!strcmp(argv[i], "-a")) solopt.posf = SOLF_ENU;
        else if (!strcmp(argv[i], "-n")) solopt.posf = SOLF_NMEA;
        else if (!strcmp(argv[i], "-g")) solopt.degf = 0;
        else if (!strcmp(argv[i], "-r") && i + 3 < argc) {
            prcopt.refpos = prcopt.rovpos = 0;
            for (j = 0; j < 3; j++) prcopt.rb[j] = atof(argv[++i]);
            matcpy(prcopt.ru, prcopt.rb, 3, 1);
        }
        else if (!strcmp(argv[i], "-l") && i + 3 < argc) {
            prcopt.refpos = prcopt.rovpos = 0;
            for (j = 0; j < 3; j++) pos[j] = atof(argv[++i]);
            for (j = 0; j < 2; j++) pos[j] *= D2R;
            pos2ecef(pos, prcopt.rb);
            matcpy(prcopt.ru, prcopt.rb, 3, 1);
        }
        else if (!strcmp(argv[i], "-y") && i + 1 < argc) solopt.sstat = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-x") && i + 1 < argc) solopt.trace = atoi(argv[++i]);
        /*else if (*argv[i] == '-') printhelp();*/
        else if (n < MAXFILE) infile[n++] = argv[i];
    }
    if (!prcopt.navsys) {
        prcopt.navsys = SYS_GPS | SYS_GLO;
    }

    prcopt.mode = PMODE_SINGLE;
    solopt.posf = SOLF_LLH;
    prcopt.refpos = 1;
    prcopt.tropopt = TROPOPT_SAAS;
    prcopt.ionoopt = IONOOPT_BRDC;
    prcopt.navsys = SYS_GPS;
	postpos(ts, te, 0.0, 0.0, &prcopt, &solopt, &filopt, infile, 2, outfile, "", "");

	return 0;
}
