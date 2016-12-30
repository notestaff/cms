// functions for handling cms component(+composite) score datastructures
// last updated: 12.30.16 	vitti@broadinstitute.org

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "cms_data.h"

#define EXTRAARGS 38 // for now

int intcmp(const void *v1, const void *v2) {return (*(int *)v1 - *(int *)v2);}

/**********************/
/***COMPONENT SCORES***/
/**********************/
void get_fst_deldaf_data(fst_deldaf_data* data, char filename[]) {
	const int line_size = 15000000; 
	FILE *inf=NULL;
	char *newLine, *token, *running;
	int isnp, itoken;
		
	newLine = malloc((line_size+1) * sizeof(char));
	assert(newLine != NULL); 

	data->nsnps = 0;
	data->pos = NULL; 
	data->fst = NULL;
	data->deldaf = NULL;

	inf = fopen(filename, "r");
	if (inf == NULL) {fprintf(stderr, "Missing file: %s\n", filename);}
	assert(inf != NULL);
	while (fgets(newLine, line_size, inf) != NULL) {
			assert(strlen(newLine) < line_size);
			data->nsnps++;
		}
	fclose(inf);

	// Allocate memory; initialize
	data->pos = malloc(data->nsnps * sizeof(int*)); assert(data->pos != NULL);
	data->fst = malloc(data->nsnps * sizeof(double*)); assert(data->fst != NULL);
	data->deldaf = malloc(data->nsnps * sizeof(double*)); assert(data->deldaf != NULL);

	/*******************
	GET DATA FROM FILE
	*******************/
	inf = fopen(filename, "r");
	fgets(newLine, line_size, inf); // strip header
	isnp = 0;
	while (fgets(newLine, line_size, inf) != NULL) {
		for (running = newLine, itoken = 0; (token = strsep(&running, " \t")) != NULL; itoken++) {
			if (itoken == 0) {
				data->pos[isnp] = atoi(token);
			}	
			else if (itoken == 1) {
				data->fst[isnp] = atof(token);
			}
			else if (itoken == 2) {
				data->deldaf[isnp] = atof(token);
			}			
		} // END for running=newLine
		isnp++;
	} //END while(fgets(newLine))
	
	fclose(inf);
	free(newLine);
} //end method
void free_fst_deldaf_data(fst_deldaf_data* data) {
	if (data == NULL) {return;}
	free(data->pos);
	free(data->fst);
	free(data->deldaf);
	data->nsnps = 0;
} //end method
void get_delihh_data(delihh_data* data, char filename[]) {
	const int line_size = 15000000;	
	FILE *inf=NULL;
	char *newLine, *token, *running;
	int isnp, itoken;
		
	newLine = malloc((line_size+1) * sizeof(char));
	assert(newLine != NULL); 

	data->nsnps = 0;
	data->pos = NULL; 
	data->freq1 = NULL;
	data->ihs_unnormed = NULL;
	data->delihh_unnormed = NULL;
	data->delihh_normed = NULL;
	data->lastcol = NULL;

	inf = fopen(filename, "r");
	if (inf == NULL) {fprintf(stderr, "Missing file: %s\n", filename);}
	assert(inf != NULL);
	while (fgets(newLine, line_size, inf) != NULL) {
			assert(strlen(newLine) < line_size);
			data->nsnps++;
		}
	fclose(inf);

	// Allocate memory; initialize
	data->pos = malloc(data->nsnps * sizeof(int*)); assert(data->pos != NULL);
	data->freq1 = malloc(data->nsnps * sizeof(double*)); assert(data->freq1 != NULL);
	data->ihs_unnormed = malloc(data->nsnps * sizeof(double*)); assert(data->ihs_unnormed != NULL);
	data->delihh_unnormed = malloc(data->nsnps * sizeof(double*)); assert(data->delihh_unnormed != NULL);	
	data->delihh_normed = malloc(data->nsnps * sizeof(double*)); assert(data->delihh_normed != NULL);
	data->lastcol = malloc(data->nsnps * sizeof(int*)); assert(data->lastcol != NULL);
	/*******************
	GET DATA FROM FILE
	*******************/
	inf = fopen(filename, "r");
	isnp = 0;
	while (fgets(newLine, line_size, inf) != NULL) {
		for (running = newLine, itoken = 0; (token = strsep(&running, " \t")) != NULL; itoken++) {
			if (itoken == 1) {
				data->pos[isnp] = atoi(token);
			}	
			else if (itoken == 2) {
				data->freq1[isnp] = atof(token);
			}
			else if (itoken == 3) {
				data->ihs_unnormed[isnp] = atof(token);
			}			
			else if (itoken == 4) {
				data->delihh_unnormed[isnp] = atof(token);
			}
			//5 is duplicate!!!!
			else if (itoken == 6) {
				data->delihh_normed[isnp] = atof(token);
			}		 
			else if (itoken == 7) {
				data->lastcol[isnp] = atoi(token);
			}						
		} // END for running=newLine
		isnp++;
	} //END while(fgets(newLine))
	
	fclose(inf);
	free(newLine);
} //end method
void free_delihh_data(delihh_data* data) {
	if (data == NULL) {return;}
	free(data->pos);
	free(data->freq1);
	free(data->ihs_unnormed);
	free(data->delihh_unnormed);
	free(data->delihh_normed);	
	free(data->lastcol);
	data->nsnps = 0;
} //end method
void get_xpehh_data(xpehh_data* data, char filename[]) {
	const int line_size = 15000000; 
	FILE *inf=NULL;
	char *newLine, *token, *running;
	int	isnp, itoken;
		
	newLine = malloc((line_size+1) * sizeof(char));
	assert(newLine != NULL); 

	data->nsnps = 0;
	data->pos = NULL; 
	data->genpos = NULL;
	data->freq1 = NULL;
	data->ihh1 = NULL; 
	data->freq2 = NULL;
	data->ihh2 = NULL;
	data->xpehh_unnormed = NULL; 
	data->xpehh_normed = NULL;
	data->lastcol = NULL;

	inf = fopen(filename, "r");
	if (inf == NULL) {fprintf(stderr, "Missing file: %s\n", filename);}
	assert(inf != NULL);
	while (fgets(newLine, line_size, inf) != NULL) {
			assert(strlen(newLine) < line_size);
			data->nsnps++;
		}
	fclose(inf);

	// Allocate memory; initialize
	data->pos = malloc(data->nsnps * sizeof(int*)); assert(data->pos != NULL);
	data->genpos = malloc(data->nsnps * sizeof(double*)); assert(data->genpos != NULL);
	data->freq1 = malloc(data->nsnps * sizeof(double*)); assert(data->freq1 != NULL);
	data->ihh1 = malloc(data->nsnps * sizeof(double*)); assert(data->ihh1 != NULL);
	data->freq2 = malloc(data->nsnps * sizeof(double*)); assert(data->freq2 != NULL);
	data->ihh2 = malloc(data->nsnps * sizeof(double*)); assert(data->ihh2 != NULL);
	data->xpehh_unnormed = malloc(data->nsnps * sizeof(double*)); assert(data->xpehh_unnormed != NULL);
	data->xpehh_normed = malloc(data->nsnps * sizeof(double*)); assert(data->xpehh_normed != NULL);
	data->lastcol = malloc(data->nsnps * sizeof(int*)); assert(data->lastcol != NULL);

	/*******************
	GET DATA FROM FILE
	*******************/
	inf = fopen(filename, "r");
	fgets(newLine, line_size, inf); // strip header
	isnp = 0;
	while (fgets(newLine, line_size, inf) != NULL) {
		for (running = newLine, itoken = 0; (token = strsep(&running, " \t")) != NULL; itoken++) {
			if (itoken == 1) {
				data->pos[isnp] = atoi(token);
			}	
			else if (itoken == 2) {
				data->genpos[isnp] = atof(token);
			}
			else if (itoken == 3) {
				data->freq1[isnp] = atof(token);
			}		
			else if (itoken == 4) {
				data->ihh1[isnp] = atof(token);
			}
			else if (itoken == 5) {
				data->freq2[isnp] = atof(token);
			}		
			else if (itoken == 6) {
				data->ihh2[isnp] = atof(token);
			}
			else if (itoken == 7) {
				data->xpehh_unnormed[isnp] = atof(token);
			}		
			else if (itoken == 8) {
				data->xpehh_normed[isnp] = atof(token);
			}
			else if (itoken == 9) {
				data->lastcol[isnp] = atoi(token);
			} 
		} // END for running=newLine
		isnp++;
	} //END while(fgets(newLine))
	
	fclose(inf);
	free(newLine);
} //end method
void free_xpehh_data(xpehh_data* data) {
	if (data == NULL) {return;}
	free(data->pos);
	free(data->genpos);
	free(data->freq1);
	free(data->ihh1);
	free(data->freq2); 
	free(data->ihh2); 
	free(data->xpehh_unnormed);
	free(data->xpehh_normed);
	free(data->lastcol);
	data->nsnps = 0;
} //end method
void get_ihs_data(ihs_data* data, char filename[]) {
	const int line_size = 15000000; 
	FILE *inf=NULL;
	char *newLine, *token, *running;
	int isnp, itoken;

	newLine = malloc((line_size+1) * sizeof(char));
	assert(newLine != NULL); 

	data->nsnps = 0;
	data->pos = NULL; 
	data->freq1 = NULL;
	data->ihh0 = NULL;
	data->ihh1 = NULL;
	data->ihs_unnormed = NULL;
	data->ihs_normed = NULL;
	data->lastcol = NULL; //not sure what information this field contains, selscan documentation is sparse. 0/1

	inf = fopen(filename, "r");
	if (inf == NULL) {fprintf(stderr, "Missing file: %s\n", filename);}
	assert(inf != NULL);
	while (fgets(newLine, line_size, inf) != NULL) {
			assert(strlen(newLine) < line_size);
			data->nsnps++;
		}
	fclose(inf);

	// Allocate memory; initialize
	data->pos = malloc(data->nsnps * sizeof(int*)); assert(data->pos != NULL);
	data->freq1 = malloc(data->nsnps * sizeof(double*)); assert(data->freq1 != NULL);
	data->ihh0 = malloc(data->nsnps * sizeof(double*)); assert(data->ihh0 != NULL);
	data->ihh1 = malloc(data->nsnps * sizeof(double*)); assert(data->ihh1 != NULL);
	data->ihs_unnormed = malloc(data->nsnps * sizeof(double*)); assert(data->ihs_unnormed != NULL);
	data->ihs_normed = malloc(data->nsnps * sizeof(double*)); assert(data->ihs_normed != NULL);
	data->lastcol = malloc(data->nsnps * sizeof(int*)); assert(data->lastcol != NULL);

	/*******************
	GET DATA FROM FILE
	*******************/
	inf = fopen(filename, "r");
	isnp = 0;
	while (fgets(newLine, line_size, inf) != NULL) {
		for (running = newLine, itoken = 0; (token = strsep(&running, " \t")) != NULL; itoken++) {
			if (itoken == 1) {
				data->pos[isnp] = atoi(token);
			}	
			else if (itoken == 2) {
				data->freq1[isnp] = atof(token);
			}
			else if (itoken == 3) {
				data->ihh0[isnp] = atof(token);
			}			
			else if (itoken == 4) {
				data->ihh1[isnp] = atof(token);
			}
			else if (itoken == 9) {
				data->ihs_unnormed[isnp] = atof(token);
			}			
			else if (itoken == 10) {
				data->ihs_normed[isnp] = atof(token);
			}
			//else if (itoken == 7) {
			//	data->lastcol[isnp] = atoi(token);
			//}
		} // END for running=newLine
		isnp++;
	} //END while(fgets(newLine))
	
	fclose(inf);
	free(newLine);
} //end method
void free_ihs_data(ihs_data* data) {
	if (data == NULL) {return;}
	free(data->pos);
	free(data->freq1);
	free(data->ihh0);
	free(data->ihh1);
	free(data->ihs_unnormed);
	free(data->ihs_normed);
	free(data->lastcol);	
	data->nsnps = 0;
} //end method
void get_nsl_data(nsl_data* data, char filename[]) {
	const int line_size = 15000000; 
	FILE *inf=NULL;
	char *newLine, *token, *running;
	int isnp, itoken;

	newLine = malloc((line_size+1) * sizeof(char));
	assert(newLine != NULL); 

	data->nsnps = 0;
	data->pos = NULL; 
	data->freq1 = NULL;
	data->sl0 = NULL;
	data->sl1 = NULL;
	data->nsl_unnormed = NULL;
	data->nsl_normed = NULL;
	inf = fopen(filename, "r");
	if (inf == NULL) {fprintf(stderr, "Missing file: %s\n", filename);}
	assert(inf != NULL);
	while (fgets(newLine, line_size, inf) != NULL) {
			assert(strlen(newLine) < line_size);
			data->nsnps++;
		}
	fclose(inf);

	// Allocate memory; initialize
	data->pos = malloc(data->nsnps * sizeof(int*)); assert(data->pos != NULL);
	data->freq1 = malloc(data->nsnps * sizeof(double*)); assert(data->freq1 != NULL);
	data->sl0 = malloc(data->nsnps * sizeof(double*)); assert(data->sl0 != NULL);
	data->sl1 = malloc(data->nsnps * sizeof(double*)); assert(data->sl1 != NULL);
	data->nsl_unnormed = malloc(data->nsnps * sizeof(double*)); assert(data->nsl_unnormed != NULL);
	data->nsl_normed = malloc(data->nsnps * sizeof(double*)); assert(data->nsl_normed != NULL);

	/*******************
	GET DATA FROM FILE
	*******************/
	inf = fopen(filename, "r");
	isnp = 0;
	while (fgets(newLine, line_size, inf) != NULL) {
		for (running = newLine, itoken = 0; (token = strsep(&running, " \t")) != NULL; itoken++) {
			if (itoken == 1) {
				data->pos[isnp] = atoi(token);
			}	
			else if (itoken == 2) {
				data->freq1[isnp] = atof(token);
			}
			else if (itoken == 3) {
				data->sl0[isnp] = atof(token);
			}			
			else if (itoken == 4) {
				data->sl1[isnp] = atof(token);
			}
			else if (itoken == 5) {
				data->nsl_unnormed[isnp] = atof(token);
			}			
			else if (itoken == 6) {
				data->nsl_normed[isnp] = atof(token);
			}

		} // END for running=newLine
		isnp++;
	} //END while(fgets(newLine))
	
	fclose(inf);
	free(newLine);
} //end method
void free_nsl_data(nsl_data* data) {
	if (data == NULL) {return;}
	free(data->pos);
	free(data->freq1);
	free(data->sl0);
	free(data->sl1);
	free(data->nsl_unnormed);
	free(data->nsl_normed);
	data->nsnps = 0;
} //end method

/*************************/
/***SCORE DISTRIBUTIONS***/
/*************************/
void get_likes_data(likes_data* data, char filename[]){
	const int line_size = 15000000; 
	FILE *inf=NULL;
	char *newLine, *token, *running;
	int ibin, itoken;

	newLine = malloc((line_size+1) * sizeof(char));
	assert(newLine != NULL); 

	data->nbins = 0;
	data->start_bin = NULL; 
	data->end_bin = NULL;
	data->probs = NULL;
	//fprintf(stderr, "\tloading likes tables from %s\n", filename);

	inf = fopen(filename, "r");
	assert(inf != NULL);
	fgets(newLine, line_size, inf); //strip
	while (fgets(newLine, line_size, inf) != NULL){
		data->nbins++;
	}
	data->nbins++; //one extra because 50 bins can be represented with 49 bounds

	data->start_bin = malloc(data->nbins * sizeof(double));
	data->end_bin = malloc(data->nbins * sizeof(double));
	data->probs = malloc(data->nbins * sizeof(double));
	fclose(inf);

	inf = fopen(filename, "r");
	assert(inf != NULL);
	ibin = 0;
	while (fgets(newLine, line_size, inf) != NULL){
		for (running = newLine, itoken = 0; (token = strsep(&running, "\t ")) != NULL; itoken++) {
			//fprintf(stderr, token);
		 // fprintf(stderr, "\n%d\n", itoken);
			if (itoken == 0) {
				data->start_bin[ibin] = atof(token);
			}
			else if (itoken ==1){
				 data->end_bin[ibin] = atof(token);
			}
			else if (itoken ==2){
				 data->probs[ibin] = atof(token);
				 break;
			} 
		} // end for loop
		ibin++;
		//fprintf(stderr, "ibin is now %d\n", ibin);
	} // end while loop
	fclose(inf);
	free(newLine);
} //end method
void free_likes_data(likes_data* data) {
	if (data == NULL) {return;}
	data->nbins = 0;
	free(data->start_bin);
	free(data->end_bin);
	free(data->probs);
} //end method

/****************/
/***POP PAIR****/
/***************/

int get_num_completeData(char ihs_filename[], char delihh_filename[], char nsl_filename[], char xpehh_filename[], char freqs_filename[]){
	ihs_data ihs1;
	delihh_data delihh1;
	nsl_data nsl1;
	xpehh_data xp;
	fst_deldaf_data fst_deldaf;
	int nsnps;
	//char *locus;
	int isnp;
	int ihs1_index, delihh1_index, nsl1_index, xp_index, fst_deldaf_index;
	int ihs1pos, delihh1pos, nsl1pos, xppos, fst_deldafpos, minimum;
	double thisDeldaf, thisXp;

	get_ihs_data(&ihs1, ihs_filename);
	get_delihh_data(&delihh1, delihh_filename);
	get_nsl_data(&nsl1, nsl_filename);
	get_xpehh_data(&xp, xpehh_filename);
	get_fst_deldaf_data(&fst_deldaf, freqs_filename);

	ihs1_index=0;
	nsl1_index=0;
	delihh1_index=0;
	xp_index=0;
	fst_deldaf_index=0;
	nsnps = 0;
	while (ihs1_index < ihs1.nsnps && delihh1_index < delihh1.nsnps && xp_index < xp.nsnps && fst_deldaf_index < fst_deldaf.nsnps)
	{
		ihs1pos = ihs1.pos[ihs1_index];
		nsl1pos = nsl1.pos[nsl1_index];
		delihh1pos = delihh1.pos[delihh1_index];
		xppos = xp.pos[xp_index];
		fst_deldafpos = fst_deldaf.pos[fst_deldaf_index];
		if (ihs1pos == delihh1pos && delihh1pos == xppos && xppos == fst_deldafpos && nsl1pos == fst_deldafpos){
			nsnps++;
		}
		//If not at the same point, find out which position is lowest and advance its pointer.
		minimum = 2147483647;
		if (ihs1pos < minimum){minimum = ihs1pos;}
		if (nsl1pos < minimum){minimum = nsl1pos;}
		if (delihh1pos < minimum){minimum = delihh1pos;}
		if (xppos < minimum){minimum = xppos;}		
		if (fst_deldafpos < minimum){minimum = fst_deldafpos;}

		if (ihs1pos == minimum){ihs1_index++;}
		if (nsl1pos == minimum){nsl1_index++;}
		if (delihh1pos == minimum){delihh1_index++;}
		if (xppos == minimum){xp_index++;}		
		if (fst_deldafpos == minimum){fst_deldaf_index++;}
	} // end while loop
	//fprintf(stderr, "\tfound complete data for %d SNPs\n", data->nsnps);
return nsnps;
} // end function


void get_popComp_data(popComp_data* data, char ihs_filename[], char delihh_filename[], char nsl_filename[], char xpehh_filename[], char freqs_filename[]){
	ihs_data ihs1;
	delihh_data delihh1;
	nsl_data nsl1;
	xpehh_data xp;
	fst_deldaf_data fst_deldaf;
	char *locus, *token;
	int isnp;
	int ihs1_index, delihh1_index, nsl1_index, xp_index, fst_deldaf_index;
	int ihs1pos, delihh1pos, nsl1pos, xppos, fst_deldafpos, minimum;
	double thisDeldaf, thisXp;

	/////////////////
	// INITIALIZE ///
	/////////////////
	data->nsnps = 0;
	data->locus_id = NULL;
	data->physpos = NULL;
	data->genpos = NULL;
	data->daf_selpop = NULL;
	data->delDAF = NULL;
	data->fst = NULL;
	data->xp_normed = NULL;
	data->ihs_normed = NULL;
	data->delihh_normed = NULL;
	data->nsl_normed = NULL;

	////////////////////////////////
	// LOAD EACH COMPONENT SCORE ///
	////////////////////////////////
	fprintf(stderr, "\tloading component score data from: %s\n", ihs_filename);
	get_ihs_data(&ihs1, ihs_filename);
	fprintf(stderr, "\t\t found values for %d SNPs\n", ihs1.nsnps);

	fprintf(stderr, "\tloading component score data from: %s\n", delihh_filename);
	get_delihh_data(&delihh1, delihh_filename);
	fprintf(stderr, "\t\t found values for %d SNPs\n",  delihh1.nsnps);

	fprintf(stderr, "\tloading component score data from: %s\n", nsl_filename);
	get_nsl_data(&nsl1, nsl_filename);
	fprintf(stderr, "\t\t found values for %d SNPs\n",  nsl1.nsnps);

	fprintf(stderr, "\tloading component score data from: %s\n", xpehh_filename);
	get_xpehh_data(&xp, xpehh_filename);
	fprintf(stderr, "\t\t found values for %d SNPs\n",  xp.nsnps);

	fprintf(stderr, "\tloading component score data from: %s\n", freqs_filename);
	get_fst_deldaf_data(&fst_deldaf, freqs_filename);
	fprintf(stderr, "\t\t found values for %d SNPs\n",  fst_deldaf.nsnps);

	///////////////////
	// COLLATE SNPS ///
	///////////////////
	ihs1_index=0;
	nsl1_index=0;
	delihh1_index=0;
	xp_index=0;
	fst_deldaf_index=0;

	while (ihs1_index < ihs1.nsnps && delihh1_index < delihh1.nsnps && xp_index < xp.nsnps && fst_deldaf_index < fst_deldaf.nsnps)
	{
		ihs1pos = ihs1.pos[ihs1_index];
		nsl1pos = nsl1.pos[nsl1_index];
		delihh1pos = delihh1.pos[delihh1_index];
		xppos = xp.pos[xp_index];
		fst_deldafpos = fst_deldaf.pos[fst_deldaf_index];
		if (ihs1pos == delihh1pos && delihh1pos == xppos && xppos == fst_deldafpos && nsl1pos == fst_deldafpos){
			data->nsnps++;
		}
		//If not at the same point, find out which position is lowest and advance its pointer.
		minimum = 2147483647;
		if (ihs1pos < minimum){minimum = ihs1pos;}
		if (nsl1pos < minimum){minimum = nsl1pos;}
		if (delihh1pos < minimum){minimum = delihh1pos;}
		if (xppos < minimum){minimum = xppos;}		
		if (fst_deldafpos < minimum){minimum = fst_deldafpos;}

		if (ihs1pos == minimum){ihs1_index++;}
		if (nsl1pos == minimum){nsl1_index++;}
		if (delihh1pos == minimum){delihh1_index++;}
		if (xppos == minimum){xp_index++;}		
		if (fst_deldafpos == minimum){fst_deldaf_index++;}
	} // end while loop
	fprintf(stderr, "\tfound complete data for %d SNPs\n", data->nsnps);

	/////////////////////
	// RESERVE MEMORY ///
	/////////////////////
	data->locus_id = malloc(data->nsnps * sizeof(char*));
	for (isnp = 0; isnp < data->nsnps; isnp++){
		data->locus_id[isnp] = malloc(256*sizeof(char));
		assert(data->locus_id[isnp] != NULL);
	}
	data->physpos = malloc(data->nsnps * sizeof(int));
	data->genpos = malloc(data->nsnps * sizeof(double));
	data->daf_selpop = malloc(data->nsnps * sizeof(double));
	data->delDAF = malloc(data->nsnps * sizeof(double));
	data->fst = malloc(data->nsnps * sizeof(double));
	data->xp_normed = malloc(data->nsnps * sizeof(double));
	data->ihs_normed = malloc(data->nsnps * sizeof(double));
	data->delihh_normed = malloc(data->nsnps * sizeof(double));
	data->nsl_normed = malloc(data->nsnps * sizeof(double));
	assert(data->physpos != NULL);
	assert(data->genpos != NULL);
	assert(data->daf_selpop != NULL);
	assert(data->delDAF != NULL);
	assert(data->fst != NULL);
	assert(data->xp_normed != NULL);
	assert(data->ihs_normed != NULL);
	assert(data->delihh_normed != NULL);
	assert(data->nsl_normed != NULL);
	//fprintf(stderr, "reserved\n"); //debug

	/////////////////////////
	// LOAD COLLATED DATA ///
	/////////////////////////
	ihs1_index=0;
	nsl1_index=0;
	delihh1_index=0;
	xp_index=0;
	fst_deldaf_index=0;

	isnp = -1;
	while (ihs1_index < ihs1.nsnps && delihh1_index < delihh1.nsnps && xp_index < xp.nsnps && fst_deldaf_index < fst_deldaf.nsnps)
	{
		ihs1pos = ihs1.pos[ihs1_index];
		nsl1pos = nsl1.pos[nsl1_index];
		delihh1pos = delihh1.pos[delihh1_index];
		xppos = xp.pos[xp_index];
		fst_deldafpos = fst_deldaf.pos[fst_deldaf_index];

		if (ihs1pos == delihh1pos && delihh1pos == xppos && xppos == fst_deldafpos && nsl1pos == fst_deldafpos){
			thisXp=xp.xpehh_normed[xp_index];
			thisDeldaf=fst_deldaf.deldaf[fst_deldaf_index];
			//fprintf(stderr, "found match\n"); //debug
			sprintf(locus, "%d", ihs1pos); //leaving this for now; issues with copying string/pointer-to-char
			//data->locus_id[isnp] = locus;

			token = strsep(&locus, "\t")
			strcpy(data->locus_id[isnp], token); //token was given by strsep (here=locus)
			isnp +=1;
			//fprintf(stderr, "isnp is%d\n", isnp); //debug
			data->physpos[isnp] = ihs1pos;
			data->genpos[isnp] = xp.genpos[xp_index];
			data->daf_selpop[isnp] = (1. - ihs1.freq1[ihs1_index]);
			data->delDAF[isnp] = thisDeldaf;
			data->fst[isnp] = fst_deldaf.fst[fst_deldaf_index];
			data->xp_normed[isnp] = thisXp;			
			data->ihs_normed[isnp] = ihs1.ihs_normed[ihs1_index];
			data->nsl_normed[isnp] = nsl1.nsl_normed[nsl1_index];
			data->delihh_normed[isnp] = delihh1.delihh_normed[delihh1_index];
			//fprintf(stderr, "finished data entry\n");
		}
		//If not at the same point, find out which position is lowest and advance its pointer.
		minimum = 2147483647;
		if (ihs1pos < minimum){minimum = ihs1pos;}
		if (nsl1pos < minimum){minimum = nsl1pos;}
		if (delihh1pos < minimum){minimum = delihh1pos;}
		if (xppos < minimum){minimum = xppos;}		
		if (fst_deldafpos < minimum){minimum = fst_deldafpos;}
		//fprintf(stderr, "advancing\n"); //debug
		if (ihs1pos == minimum){ihs1_index++;}
		if (nsl1pos == minimum){nsl1_index++;}
		if (delihh1pos == minimum){delihh1_index++;}
		if (xppos == minimum){xp_index++;}		
		if (fst_deldafpos == minimum){fst_deldaf_index++;}
			
	} //end while
	free_ihs_data(&ihs1);
	free_nsl_data(&nsl1);
	free_delihh_data(&delihh1);
	free_xpehh_data(&xp);
	free_fst_deldaf_data(&fst_deldaf);
	//fprintf(stderr, "loaded all data to object\n");
} //end method
void free_popComp_data(popComp_data* data){
	int isnp;
	fprintf(stderr, "702\n");
	if (data == NULL) {return;}
	for (isnp = 0; isnp < data->nsnps; isnp++){
		free(data->locus_id[isnp]);
	}
	fprintf(stderr, "707\n");
	free(data->locus_id); // THIS IS CREATING ISSUES; need to track down
	fprintf(stderr, "709\n");
	free(data->physpos);
	free(data->genpos);
	free(data->daf_selpop);
	free(data->delDAF);
	free(data->fst);
	free(data->xp_normed);
	free(data->ihs_normed);
	free(data->delihh_normed);
	free(data->nsl_normed);
	data->nsnps = 0;	fprintf(stderr, "719\n");
} //end method

/***********************/
/***POP COMPARISONS****/
/***********************/
void get_popComp_data_multiple(popComp_data_multiple* data, int nComparisons, int argc, char *argv[]){
	/*
	argv is all files for pop-pairs (each of which points to further component score files)
	*/
	const int line_size = 15000000; 
	popComp_data data_sing;
	FILE *inf=NULL;
	char *newLine;//, *token, *running;
	char infilename[512];
	int	isnp, jsnp, iComp, totNsnp, nunique; //thisPhysPos, itoken
	int *allSnps, *allUniqueSnps;
	char ihs_filename[528], delihh_filename[528], nsl_filename[528], xpehh_filename[528], freqs_filename[528];
	int numExtraArgs, ivar;
		
	newLine = malloc((line_size+1) * sizeof(char));
	assert(newLine != NULL); 

	//////////////////
	/// INITIALIZE ///
	//////////////////
	newLine = malloc((line_size+1) * sizeof(char));
	assert(newLine != NULL); 
	data->nsnps = 0;
	data->physpos = NULL;
	data->genpos = NULL;
	data->daf_selpop = NULL;
	data->delDAF = NULL;
	data->fst = NULL;
	data->xp_normed = NULL;
	data->ihs_normed = NULL;
	data->delihh_normed = NULL;
	data->nsl_normed = NULL;

	////////////////////
	/// COLLATE LOCI ///
	////////////////////
	totNsnp = 0; //pass over first argument (run params)
	numExtraArgs = argc - nComparisons;
	for (iComp = 0; iComp < nComparisons; iComp++){
		sprintf(infilename, "%s", argv[iComp + numExtraArgs]);
		fprintf(stderr, "loading pop-pair from file: ");
		fprintf(stderr, infilename);
		fprintf(stderr, "\n");
		inf = fopen(infilename, "r");
		fgets(ihs_filename, line_size, inf);
		strtok(ihs_filename, "\n");
		fgets(delihh_filename, line_size, inf);
		strtok(delihh_filename, "\n");
		fgets(nsl_filename, line_size, inf);
		strtok(nsl_filename, "\n");
		fgets(xpehh_filename, line_size, inf);
		strtok(xpehh_filename, "\n");
		fgets(freqs_filename, line_size, inf);
		strtok(freqs_filename, "\n");
		fclose(inf);
		totNsnp += get_num_completeData(ihs_filename, delihh_filename, nsl_filename, xpehh_filename, freqs_filename);
	} // end iComp
	fprintf(stderr, "found a total of %d complete-info snps present in any of %d comparisons\n.", totNsnp,  nComparisons);

	//then get array for all of them
	allSnps = malloc(totNsnp * sizeof(int));
	isnp = 0;
	for (iComp = 0; iComp < nComparisons; iComp++){
		//get each infilename
		sprintf(infilename, "%s", argv[iComp + numExtraArgs]);
		fprintf(stderr, "loading pop-pair from file: ");
		fprintf(stderr, infilename);
		fprintf(stderr, "\n");
		inf = fopen(infilename, "r");
		fgets(ihs_filename, line_size, inf);
		strtok(ihs_filename, "\n");
		fgets(delihh_filename, line_size, inf);
		strtok(delihh_filename, "\n");
		fgets(nsl_filename, line_size, inf);
		strtok(nsl_filename, "\n");
		fgets(xpehh_filename, line_size, inf);
		strtok(xpehh_filename, "\n");
		fgets(freqs_filename, line_size, inf);
		strtok(freqs_filename, "\n");
		fclose(inf);
		get_popComp_data(&data_sing, ihs_filename, delihh_filename, nsl_filename, xpehh_filename, freqs_filename);
	
		//something wonky here.
		for (jsnp = 0; jsnp < data_sing.nsnps; jsnp++){
			fprintf(stderr, "isnp: %d; jsnp: %d\n", isnp, jsnp);
			allSnps[isnp + jsnp] = data_sing.physpos[jsnp];
			isnp +=1;
		}
		fprintf(stderr, "be free\n");
		free_popComp_data(&data_sing); 
		fprintf(stderr, "freed\n");
	}//end icomp
	fprintf(stderr, "loaded all positions!\n");

	for (ivar = 0; ivar <= totNsnp; ivar++){
		fprintf(stderr, " %d ", allSnps[ivar]);
	}



	//////////////////////////
	/// COLLATE LOCI: SORT ///
	/////////////////////////
	fprintf(stderr, "now sorting:\n");
	qsort(allSnps, totNsnp, sizeof(int), intcmp);
	fprintf(stderr, "Sorted SNPs from pos %d to %d\n", allSnps[0], allSnps[totNsnp-1]);
	nunique = 0;
	for (isnp = 0; isnp <= totNsnp-2; isnp++){
		//fprintf(stderr, "%d\t", allSnps[isnp]);
		if (allSnps[isnp] == allSnps[isnp+1]){continue;}
		else{nunique++;}
	} // end for isnp
	fprintf(stderr, "Found %d SNPs with values for at least one pop comparison...\n", nunique);

	allUniqueSnps	= malloc(nunique * sizeof(int));
	jsnp = 0;
	for (isnp = 0; isnp <= totNsnp-2; isnp++){
		//fprintf(stderr, "%d\t", allSnps[isnp]);
		if (allSnps[isnp] == allSnps[isnp+1]){continue;}
		else{allUniqueSnps[jsnp] = allSnps[isnp]; jsnp++;}
	} // end for isnp

	///////////////////////
	/// ALLOCATE MEMORY ///
	//////////////////////

	fprintf(stderr, "Allocating memory...\n");
	data->nsnps = nunique;
	data->ncomp =nComparisons;
	data->physpos = malloc(nComparisons * sizeof(int*));
	data->genpos = malloc(nComparisons * sizeof(double*));
	data->daf_selpop = malloc(nComparisons * sizeof(double*));
	data->delDAF = malloc(nComparisons * sizeof(double*));
	data->fst = malloc(nComparisons * sizeof(double*));
	data->xp_normed = malloc(nComparisons * sizeof(double*));
	data->ihs_normed = malloc(nComparisons * sizeof(double*));
	data->delihh_normed = malloc(nComparisons * sizeof(double*));
	data->nsl_normed = malloc(nComparisons * sizeof(double*));

	assert(data->physpos != NULL);
	assert(data->genpos != NULL);
	assert(data->daf_selpop != NULL);
	assert(data->delDAF != NULL);
	assert(data->fst != NULL);
	assert(data->xp_normed != NULL);
	assert(data->ihs_normed != NULL);
	assert(data->delihh_normed != NULL);
	assert(data->nsl_normed != NULL);


	for (iComp = 0; iComp < nComparisons; iComp++){
		data->physpos[iComp] = calloc(nunique, sizeof(int));
		data->genpos[iComp] = calloc(nunique, sizeof(double));
		data->daf_selpop[iComp] = calloc(nunique, sizeof(double));
		data->delDAF[iComp] = calloc(nunique, sizeof(double));
		data->fst[iComp] = calloc(nunique, sizeof(double));
		data->xp_normed[iComp] = calloc(nunique, sizeof(double));		
		data->ihs_normed[iComp] = calloc(nunique, sizeof(double));
		data->delihh_normed[iComp] = calloc(nunique, sizeof(double));	
		data->nsl_normed[iComp] = calloc(nunique, sizeof(double));	
			
		assert(data->physpos[iComp] != NULL);
		assert(data->genpos[iComp] != NULL);
		assert(data->daf_selpop[iComp] != NULL);
		assert(data->delDAF[iComp] != NULL);
		assert(data->fst[iComp] != NULL);
		assert(data->xp_normed[iComp] != NULL);
		assert(data->ihs_normed[iComp] != NULL);
		assert(data->delihh_normed[iComp] != NULL);
		assert(data->nsl_normed[iComp] != NULL);		
	} // end for icomp

	/////////////////////////////////////////////
	// LOAD ALL COMPARISONS TO ONE DATA OBJECT //
	/////////////////////////////////////////////

	fprintf(stderr, "Loading all component scores...\n");
	for (iComp = 0; iComp < nComparisons; iComp++){
		sprintf(infilename, "%s", argv[iComp + numExtraArgs]);
		fprintf(stderr, "loading pop-pair from file: ");
		fprintf(stderr, infilename);
		fprintf(stderr, "\n");

		inf = fopen(infilename, "r");
		fgets(ihs_filename, line_size, inf);
		strtok(ihs_filename, "\n");
		fgets(delihh_filename, line_size, inf);
		strtok(delihh_filename, "\n");
		fgets(nsl_filename, line_size, inf);
		strtok(nsl_filename, "\n");
		fgets(xpehh_filename, line_size, inf);
		strtok(xpehh_filename, "\n");
		fgets(freqs_filename, line_size, inf);
		strtok(freqs_filename, "\n");
		fclose(inf);

		get_popComp_data(&data_sing, ihs_filename, delihh_filename, nsl_filename, xpehh_filename, freqs_filename);
		jsnp = 0; //isnp iterates (0, nunique) over allUnique Snps; // jsnp runs (0, data_sing.nsnp) over data_sing.physpos, smaller range.
		for (isnp = 0; isnp < nunique; isnp++){
			//fprintf(stderr, "%d\t%d\t%d\t%d\n", isnp, jsnp, allUniqueSnps[isnp], data_sing.physpos[jsnp]);
			if (allUniqueSnps[isnp] == data_sing.physpos[jsnp]){ // the snp matches; load all data
				data->physpos[iComp][isnp] = data_sing.physpos[jsnp];	
				data->genpos[iComp][isnp] = data_sing.genpos[jsnp];	 
				data->daf_selpop[iComp][isnp] = data_sing.daf_selpop[jsnp];	 
				data->delDAF[iComp][isnp] = data_sing.delDAF[jsnp];	
				data->fst[iComp][isnp] = data_sing.fst[jsnp];	 
				data->xp_normed[iComp][isnp] = data_sing.xp_normed[jsnp];							 
				data->ihs_normed[iComp][isnp] = data_sing.ihs_normed[jsnp];	 
				data->delihh_normed[iComp][isnp] = data_sing.delihh_normed[jsnp];	
				data->nsl_normed[iComp][isnp] = data_sing.nsl_normed[jsnp];		 
				jsnp++; //assert(jsnp<=data_sing.nsnps);
				if (jsnp >= data_sing.nsnps){break;}
			}
			else if (allUniqueSnps[isnp] > data_sing.physpos[jsnp]){jsnp++; if (jsnp >= data_sing.nsnps){break;}}//assert(jsnp<=data_sing.nsnps);}
			//else if (allUniqueSnps[isnp] < data_sing.physpos[jsnp]){pass;}
		}// end for isnp loop
		
		free_popComp_data(&data_sing); 
	} // end for icomp
fprintf(stderr, "loaded multiple pop-pair comparisons to data object.\n");
} //end method
void free_popComp_data_multiple(popComp_data_multiple* data){
	int iComp;
	if (data == NULL) {return;}
	for (iComp = 0; iComp < data->ncomp; iComp++){
		free(data->physpos[iComp]);
		free(data->genpos[iComp]);
		free(data->daf_selpop[iComp]);
		free(data->delDAF[iComp]);
		free(data->fst[iComp]);
		free(data->xp_normed[iComp]);
		free(data->ihs_normed[iComp]);
		free(data->delihh_normed[iComp]);
	}
	free(data->physpos);
	free(data->genpos);
	free(data->daf_selpop);
	free(data->delDAF);
	free(data->fst);
	free(data->xp_normed);
	free(data->ihs_normed);
	free(data->delihh_normed);
	data->nsnps = 0;
	data->ncomp = 0;
} //end method

float getMaxBf(likes_data* data_miss, likes_data* data_hit){
	int ibin;
	float thisBf;
	float maxBf = 0.;

	for (ibin = 0; ibin < data_hit->nbins; ibin++){
		if(data_hit->probs[ibin] > 1e-10 && data_miss->probs[ibin] > 1e-10){
			thisBf = data_hit->probs[ibin] / data_miss->probs[ibin];
			if (thisBf > maxBf){maxBf = thisBf;}
		}
	}//end ibin
	//fprintf(stderr, "found max bf: %f\n", maxBf);
	return maxBf;
}//end function
float getMinBf(likes_data* data_miss, likes_data* data_hit){
	int ibin;
	float thisBf;
	float minBf = 1.;

	for (ibin = 0; ibin < data_hit->nbins; ibin++){
		if(data_hit->probs[ibin] > 1e-10 && data_miss->probs[ibin] > 1e-10){
			thisBf = data_hit->probs[ibin] / data_miss->probs[ibin];
			if (thisBf < minBf){minBf = thisBf;}
		}
	}//end ibin

	//fprintf(stderr, "found min bf: %f\n", minBf);	
	return minBf;
}//end function
float getProb(likes_data* data, double value){
	int ibin;
	for (ibin = 0; ibin < data->nbins; ibin++){
		if (value >= data->start_bin[ibin] && value <= data->end_bin[ibin]){return data->probs[ibin];}
	}
	if (value < data->start_bin[0]){return data->probs[0];}
	if (value > data->end_bin[data->nbins - 1]){return data->probs[data->nbins - 1];}

	return 0;
} //end function
float compareXp(popComp_data_multiple* data, int isnp){//currently: takes max val
	double xp;
	int iComp;
	xp = data->xp_normed[0][isnp];
	for (iComp = 0; iComp < data->ncomp; iComp++){
		if (data->xp_normed[iComp][isnp] > xp){xp = data->xp_normed[iComp][isnp];}
	}
	return xp;
} //end function
float compareFst(popComp_data_multiple* data, int isnp){ //currently: takes average
	//takes LSBL? or PBS? I would need to include outgroup-pairs-Fst. 
	//previously: takes max val
	double fst;
	double ave;
	int iComp;
	int theseComp=0;
	fst =	0.;
	for (iComp = 0; iComp < data->ncomp; iComp++){
		if (data->fst[iComp][isnp] != 0){
		fst += data->fst[iComp][isnp];
		theseComp ++;}
	}
	ave = fst / (double)theseComp;
	return ave;
} //end function
float comparedelDaf(popComp_data_multiple* data, int isnp){//currently: takes average
	//previously: takes max val
	double deldaf;
	int iComp;
	double ave;
	int theseComp=0;
	deldaf = 0;//-100;
	for (iComp = 0; iComp < data->ncomp; iComp++){
		if (data->delDAF[iComp][isnp] !=0){
		deldaf += data->delDAF[iComp][isnp];
		theseComp++;}
		//if (data->delDAF[iComp][isnp] > deldaf){deldaf = data->delDAF[iComp][isnp];}

	}
	ave = deldaf / (double)theseComp;
	return ave;
} //end function

