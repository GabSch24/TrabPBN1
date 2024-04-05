#include <stdio.h>
typedef struct pixel
{
    int r;
    int g;
    int b;
} pixel;

void main(void){
    FILE *fp;
    fp = fopen("Bugio8.ppm","r");

    char formato[3];
    fscanf(fp, "%s", formato);
    printf("%s\n", formato);

    int coluna,linha;
    fscanf(fp, "%d%d", &coluna, &linha);
    printf("%d %d\n", coluna,linha);

    int valor_max;
    fscanf(fp, "%d", &valor_max);
    printf("%d\n", valor_max);

    pixel Pixeis[coluna*linha];

    int i,j,count = 0;
    for(j=0; j<linha; j++){
        for (i = 0; i < coluna; i++)
        {
            fscanf(fp,"%d %d %d", &Pixeis[count].r, &Pixeis[count].g, &Pixeis[count].b);
            printf("%d %d %d\n",Pixeis[count].r,Pixeis[count].g,Pixeis[count].b);
            count++;
        }
    }
    fclose(fp); 

    FILE *new_fp;
    new_fp = fopen("new_Bugio8.ppm","w");
    fprintf(new_fp, "P2\n");
    fprintf(new_fp, "%d %d\n", coluna, linha);
    fprintf(new_fp, "%d\n", valor_max);
    count = 0;
    for(j=0; j<linha; j++){
        for (i = 0; i < coluna; i++)
        {
            fprintf(new_fp,"%d\n", (int)(Pixeis[count].r * 0.299 + Pixeis[count].g * 0.587 + Pixeis[count].b * 0.114));
            count++;
        }
    }
    fclose(new_fp);

}