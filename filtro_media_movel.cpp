#include "filtro_media_movel.h"


long acc_temp = 0;
int fmm_temp[FMM_SIZE] = { 0 };
int fmm_temp_indice = 0;

int fmm_add( int valor )
{
    int i;
    i = fmm_temp_indice;
    acc_temp -= fmm_temp[i];
    fmm_temp[i] = valor;
    acc_temp += valor;
    fmm_temp_indice = (i+1) % FMM_SIZE;
    return( i );
}

int fmm_media( void )
{
    return( acc_temp / FMM_SIZE );
}
