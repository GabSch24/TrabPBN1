#include <stdio.h>
#include <stdlib.h>

enum Format{
    RGB,
    GREYSCALE
};

typedef struct
{
    int height;
    int width;
    int max_value;
    enum Format format; 
    unsigned char *pixeis;
} Image;

FILE* writeColorImage(Image img);

Image readImage(FILE *fp){

    Image img;

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
    if(img.format == RGB){
        unsigned char *matriz;
        matriz = (unsigned char *)malloc((linha * coluna) * sizeof(unsigned char)*3);
        for (int i = 0; i < (linha*coluna)*3; i += 3)
        {
            fscanf(fp,"%d %d %d", &matriz[i], &matriz[i+1], &matriz[i+2]);
        }
        img.pixeis = matriz;
    }
    else if(img.format == GREYSCALE){
        unsigned char *matriz;
        matriz = (unsigned char *)malloc((linha * coluna) * sizeof(unsigned char));
        for (int i = 0; i < linha*coluna; i++)
        {
            fscanf(fp,"%d", &matriz[i]);
        }
        img.pixeis = matriz;
    }
    else{
        printf("Formato inválido");
        exit(1);
    }

    return img;    
}
Image toGrayScale(Image img){
    if (img.format == GREYSCALE){
        printf("Invalid image format to convert, expect errors\n");
    }
    Image new_img;
    new_img.format = GREYSCALE;
    new_img.height = img.height;
    new_img.width = img.width;
    new_img.max_value = img.max_value;
    unsigned char *matriz;
    matriz = (unsigned char *)malloc((img.height * img.width) * sizeof(unsigned char));
    for (int i = 0; i < img.height*img.width; i++)
    {
        new_img.pixeis[i] = (img.pixeis[3*i] * 0.299 +
                                     img.pixeis[3*i+1] * 0.587 +
                                     img.pixeis[3*i+2] * 0.114);
    }
    img.pixeis = matriz;
}
FILE* writeGreyScaleImage(Image img){
    if (img.format == RGB){
        printf("Wrong write function called, switching over...\n");
        return writeColorImage(img);
    }
    FILE *new_fp;
    new_fp = fopen("new_Bugio8.ppm","w");
    fprintf(new_fp, "P2\n");
    fprintf(new_fp, "%d %d\n", img.width, img.height);
    fprintf(new_fp, "%d\n", img.max_value);

    for(int i=0; i<img.height * img.width; i++){

        fprintf(new_fp,"%d\n", (int)(img.pixeis[i]));
    }
    fclose(new_fp);

    return new_fp;

}
FILE* writeColorImage(Image img){
    if (img.format == GREYSCALE){
        printf("Wrong write function called, switching over...\n");
        return writeGreyScaleImage(img);
    }
    FILE *new_fp;
    new_fp = fopen("new_Bugio8.ppm","w");
    fprintf(new_fp, "P3\n");
    fprintf(new_fp, "%d %d\n", img.width, img.height);
    fprintf(new_fp, "%d\n", img.max_value);

    for(int i=0; i<(img.height * img.width)*3; i++){

        fprintf(new_fp,"%d\n", img.pixeis[i]);
    }
    fclose(new_fp);

    return new_fp;

}
void main(void){
    FILE *fp;
    fp = fopen("Bugio8.ppm","r");

    Image img = readImage(fp);
    writeColorImage(img);
    

    free(&img.pixeis[0]);
    
    
    fclose(fp);

}
