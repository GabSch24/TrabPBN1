#include <stdio.h>
#include <stdlib.h>
enum Format{
    RGB,
    GREYSCALE
};

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef struct
{
    int height;
    int width;
    int max_value;
    enum Format format;
    Pixel *pixeis;
} Imagem;

Imagem readImage(FILE *fp){

    Imagem img;

    char formato[3];
    fscanf(fp, "%s", formato);
    //printf("%s\n", formato);
    img.format = (formato[1] == '3') ? RGB : GREYSCALE;

    int coluna,linha;
    fscanf(fp, "%d%d", &coluna, &linha);
    //printf("%d %d\n", coluna,linha);
    img.height = linha;
    img.width = coluna;

    int valor_max;
    fscanf(fp, "%d", &valor_max);
    //printf("%d\n", valor_max);
    img.max_value = valor_max;
    Pixel *matriz;
    matriz = (Pixel *)malloc((linha * coluna) * sizeof(Pixel));
    for (int i = 0; i < linha*coluna; i++)
    {
        fscanf(fp,"%d %d %d", &matriz[i].r, &matriz[i].g, &matriz[i].b);
    }
    img.pixeis = matriz;
    
}
void main(void){
    FILE *fp;
    fp = fopen("Bugio8.ppm","r");

    Imagem img = readImage(fp);

    int coluna, linha;
    Pixel Pixeis[coluna*linha];

    int i,j,count = 0;
    for(j=0; j<linha; j++){
        for (i = 0; i < coluna; i++)
        {
            fscanf(fp,"%d %d %d", &Pixeis[count].r, &Pixeis[count].g, &Pixeis[count].b);
            printf("%d %d %d\n",Pixeis[count].r,Pixeis[count].g,Pixeis[count].b);
            count++;
        }
    }
    for (int i = 0; i < img.height * img.width; i++)
    {
        free(&img.pixeis[i]);
    }
    
    fclose(fp); 

    FILE *new_fp;
    new_fp = fopen("new_Bugio8.ppm","w");
    fprintf(new_fp, "P2\n");
    fprintf(new_fp, "%d %d\n", coluna, linha);
    //fprintf(new_fp, "%d\n", valor_max);
    
    

    for(j=0; j<linha; j++){
        for (i = 0; i < coluna; i++)
        {
            fprintf(new_fp,"%d\n", (int)(Pixeis[count].r * 0.299 + Pixeis[count].g * 0.587 + Pixeis[count].b * 0.114));
            count++;
        }
    }
    fclose(new_fp);

}