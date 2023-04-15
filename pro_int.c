#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main()
{
    char line[100],word[5],s1_num[6],atm_name[4],res_num[5],res_name[4],store_res_name[5000][4],store_atm_name[5000][4],chain_id[5000],x[9], y[9], z[9];
    int i, c1,store_atm_num[5000],flag,current_res_no[5000],c_neutral,c_pos,c_neg,c_aro,c_hydro,c_backbone,c_sidechain,c_pu,c_py, total_x, total_y, total_z;
    int  store_res_num[5000], aro_res_num[5000], resu[5000];
    float n,p,ne,a,h,b,si,pu,py, dis, store_x[5000], store_y[5000], store_z[5000], dna_x[5000], dna_y[5000], dna_z[5000];



    for(int i = 0; i < 5000; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            store_res_name[i][j] = '\0';
        }
    }

    for(int i = 0; i < 5000; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            store_atm_name[i][j] = '\0';
        }
    }

    FILE *fpt1, *fpt2;
    fpt1=fopen("2qkb.pdb", "r");
    if(fpt1 == NULL) 
    {
      perror("Error opening file");
      return(-1);
    }
    fpt2=fopen("output.pdb", "w");

    c1 = 100;
    c_neutral=c_pos=c_neg=c_aro=c_hydro=c_backbone=c_sidechain=c_pu=c_py=0;

    while (fgets(line,100,fpt1)!=NULL)
    {
        for(int i = 0; i < 4; i++)
        {
            word[i] = line[i];
        }
        word[4] = '\0';

        if (strcmp(word, "ATOM") == 0)
        {
            for(int i = 0; i < 5; i++)
            {
                s1_num[i] = line[i+6];
            }
                s1_num[5] = '\0';
                int temp = atoi(s1_num);
                store_atm_num[c1] = temp;

            for(int i = 0; i < 3; i++)
            {
                atm_name[i] = line[i+13];
            }
                atm_name[3] = '\0';
                strcpy(store_atm_name[c1], atm_name);
            for(int i = 0; i < 3; i++)
            {
                res_name[i] = line[i+17];
            }
                res_name[3] = '\0';
                strcpy(store_res_name[c1], res_name);
            chain_id[c1] = line[21];
            for(int i = 0; i < 4; i++)
            {
                res_num[i] = line[i+22];
            }
                res_num[4] = '\0';
                temp = atoi(res_num);
               store_res_num[c1] = temp;

            for(int i = 0; i < 8; i++)
            {
                x[i] = line[i+30];
            }
                x[8] = '\0';
                store_x[c1] = atof(x);
            for(int i = 0; i < 8; i++)
            {
                y[i] = line[i+38];
            }
                y[8] = '\0';
                store_y[c1] = atof(y);
            for(int i = 0; i < 46; i++)
            {
                z[i] = line[i+46];
            }
                z[8] = '\0';
                store_z[c1] = atof(z);
            c1++;

        }
    }
    for(int i = 100; i < c1; i++)
    {
        fprintf(fpt2,"ATOM %5d %s %s %c%4d %8.3f%8.3f%8.3f\n", store_atm_num[i], store_atm_name[i], store_res_name[i], chain_id[i], store_res_num[i], store_x[i], store_y[i], store_z[i]);
    }
    int j = 1;
    for(int i = 0; i < 5000; i++)
    {
        if(chain_id[i] == 'A')
        {
            if(strcmp(store_res_name[i], "PHE") == 0 || strcmp(store_res_name[i], "TRP") == 0 || strcmp(store_res_name[i], "TYR") == 0 || strcmp(store_res_name[i], "HIS") == 0)
            {  
                if(aro_res_num[j-1] != store_res_num[i]) 
                {
                    aro_res_num[j] = store_res_num[i];
                    j++;
                }
                    
            }
        }
    }
    // for(int i = 1; i < 18; i++)
    // {
    //     printf("%d ", aro_res_num[i]);
    // }
    int k = 0;
    for(int i = 0; i < 5000; i++)
    {
        if(chain_id[i] == 'D')
        {
            dna_x[k] = store_x[i];
            dna_y[k] = store_y[i];
            dna_z[k] = store_z[i];
            k++;
        }
    }
    k = 0;
    for(int i = 0; i < 5000; i++)
    {
        if(chain_id[i] == 'A')
        {
            if(strcmp(store_res_name[i], "PHE") == 0 || strcmp(store_res_name[i], "TRP") == 0 || strcmp(store_res_name[i], "TYR") == 0 || strcmp(store_res_name[i], "HIS") == 0)
            {  
                for(int j = 0; j < k; j++)
                {
                    dis = sqrt(pow((store_x[i]-dna_x[j]),2) + pow((store_y[i]-dna_y[j]),2) + pow((store_z[i]-dna_z[j]),2));
                }
                if(dis <= 10)
                {
                    resu[k] = store_res_num[i];
                    k++;
                }
            }
        }
    }
    for(int i = 0; i < 5000; i++)
    {
        printf("%d ", resu[i]);
    }
    
}




























