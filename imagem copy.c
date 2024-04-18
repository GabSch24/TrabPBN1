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
    unsigned char a;
} Pixel;
typedef struct
{
    int height;
    int width;
    int max_value;
    enum Format format; 
    Pixel **pixeis;
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
        Pixel** matriz;
        matriz = (Pixel**)malloc(linha * sizeof(Pixel*));
        for (int i = 0; i < linha; i++) {
            matriz[i] = (Pixel*)malloc(coluna * sizeof(Pixel));
        }
        for (int i = 0; i < linha; i++)
        {
            for (int j = 0; j < coluna; j++)
            {
                fscanf(fp,"%d %d %d", &matriz[i][j].r, &matriz[i][j].g, &matriz[i][j].b);
            }
        }
        img.pixeis = matriz;
    }
    else if(img.format == GREYSCALE){
        Pixel** matriz;
        matriz = (Pixel**)malloc(linha * sizeof(Pixel*));
        for (int i = 0; i < linha; i++) {
            matriz[i] = (Pixel*)malloc(coluna * sizeof(Pixel));
        }
        for (int i = 0; i < linha; i++)
        {
            for (int j = 0; j < coluna; j++)
            {
                fscanf(fp,"%d", &matriz[i][j].a);
            }
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
    Pixel** matriz;
    matriz = (Pixel**)malloc(img.height * sizeof(Pixel*));
    for (int i = 0; i < img.height; i++) {
        matriz[i] = (Pixel*)malloc(img.width * sizeof(Pixel));
    }
    for (int i = 0; i < img.height; i++)
    {
        for (int j = 0; j < img.width; j++)
        {
            matriz[i][j].a = (img.pixeis[i][j].r * 0.299 +
                              img.pixeis[i][j].g * 0.587 +
                              img.pixeis[i][j].b * 0.114);
        }
    }
    new_img.pixeis = matriz;
    return new_img;
}
Image toNegative(Image img){
    Image new_img;
    new_img.height = img.height;
    new_img.width = img.width;
    new_img.max_value = img.max_value;
    Pixel **matriz;
    matriz = (Pixel**)malloc(img.height * sizeof(Pixel*));
    for (int i = 0; i < img.height; i++) {
        matriz[i] = (Pixel*)malloc(img.width * sizeof(Pixel));
    }
    if (img.format == RGB){
        new_img.format = RGB;
        for (int i = 0; i < img.height; i++)
        {
            for (int j = 0; j < img.width; j++)
            {
                matriz[i][j].r = img.max_value - img.pixeis[i][j].r;
                matriz[i][j].g = img.max_value - img.pixeis[i][j].g;
                matriz[i][j].b = img.max_value - img.pixeis[i][j].b;
            }
        }
        new_img.pixeis = matriz;
        return new_img;
    }
    else if (img.format == GREYSCALE){
        new_img.format = GREYSCALE;
        for (int i = 0; i < img.height; i++)
        {
            for (int j = 0; j < img.width; j++)
            {
                matriz[i][j].a = img.max_value - img.pixeis[i][j].a;
            }
        }
        new_img.pixeis = matriz;
        return new_img;
    }
}
Image toBrighter(Image img){
    Image new_img;
    new_img.height = img.height;
    new_img.width = img.width;
    new_img.max_value = img.max_value;
    Pixel **matriz;
    matriz = (Pixel**)malloc(img.height * sizeof(Pixel*));
    for (int i = 0; i < img.height; i++) {
        matriz[i] = (Pixel*)malloc(img.width * sizeof(Pixel));
    }
    if (img.format == RGB){
        new_img.format = RGB;
        for (int i = 0; i < img.height; i++)
        {
            for (int j = 0; j < img.width; j++)
            {
                matriz[i][j].r = img.pixeis[i][j].r + 100 > new_img.max_value ? 
                                                new_img.max_value:img.pixeis[i][j].r + 20;
                matriz[i][j].g = img.pixeis[i][j].g + 100 > new_img.max_value ? 
                                                new_img.max_value:img.pixeis[i][j].g + 20;
                matriz[i][j].b = img.pixeis[i][j].b + 100 > new_img.max_value ? 
                                                new_img.max_value:img.pixeis[i][j].b + 20;
            }
        }
        new_img.pixeis = matriz;
        return new_img;
    }
    else if(img.format == GREYSCALE){
        new_img.format = GREYSCALE;
        for (int i = 0; i < img.height; i++)
        {
            for (int j = 0; j < img.width; j++)
            {
                matriz[i][j].a = img.pixeis[i][j].a + 100 > new_img.max_value ? 
                                                new_img.max_value:img.pixeis[i][j].a + 20;
            }
        }
        new_img.pixeis = matriz;
        return new_img;
    }
}
Image to90graus(Image img){
    Image new_img;
    new_img.height = img.width;
    new_img.width = img.height;
    new_img.max_value = img.max_value;
    Pixel **matriz;
    matriz = (Pixel**)malloc(new_img.height * sizeof(Pixel*));
    for (int i = 0; i < new_img.height; i++) {
        matriz[i] = (Pixel*)malloc(img.width * sizeof(Pixel));
    }
    if (img.format == RGB){
        new_img.format = RGB;
        for (int i = 0; i < new_img.height; i++)
        {
            for (int j = 0; j < new_img.width; j++)
            {
                matriz[i][j].r = img.pixeis[j][i].r;
                matriz[i][j].g = img.pixeis[j][i].g;
                matriz[i][j].b = img.pixeis[j][i].b;
            }
        }
        new_img.pixeis = matriz;
        return new_img;
    }
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

    for(int i=0; i<img.height; i++){
        for (int j = 0; j < img.width; j++)
        {
            fprintf(new_fp,"%d\n", img.pixeis[i][j].a);
        }
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

    for(int i=0; i<img.height; i++){
        for (int j = 0; j < img.width; j++)
        {
            fprintf(new_fp,"%d\n%d\n%d\n", 
                    img.pixeis[i][j].r, 
                    img.pixeis[i][j].g, 
                    img.pixeis[i][j].b);
        }
    }
    fclose(new_fp);

    return new_fp;

}
void main(void){
    FILE *fp;
    fp = fopen("Bugio8.ppm","r");
    Image img = readImage(fp);
    Image new_img = toGrayScale(img);
    new_img = toBrighter(new_img);
    writeColorImage(new_img);
    

    free(&img.pixeis[0]);
    

    fclose(fp);

}
