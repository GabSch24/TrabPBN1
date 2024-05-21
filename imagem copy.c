#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char file_name[25];
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

Image reduceBrightness(Image img, char value){
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
                matriz[i][j].r = img.pixeis[i][j].r + value < 0 ? 
                                                0:img.pixeis[i][j].r + value;
                matriz[i][j].g = img.pixeis[i][j].g + value < 0 ? 
                                                0:img.pixeis[i][j].g + value;
                matriz[i][j].b = img.pixeis[i][j].b + value < 0 ? 
                                                0:img.pixeis[i][j].b + value;
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
                matriz[i][j].a = img.pixeis[i][j].a + value < 0? 
                                                0:img.pixeis[i][j].a + value;
            }
        }
        new_img.pixeis = matriz;
        return new_img;
    }
}
Image increaseBrightness(Image img, char value){
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
                matriz[i][j].r = img.pixeis[i][j].r + value > new_img.max_value ? 
                                                new_img.max_value:img.pixeis[i][j].r + value;
                matriz[i][j].g = img.pixeis[i][j].g + value > new_img.max_value ? 
                                                new_img.max_value:img.pixeis[i][j].g + value;
                matriz[i][j].b = img.pixeis[i][j].b + value > new_img.max_value ? 
                                                new_img.max_value:img.pixeis[i][j].b + value;
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
                matriz[i][j].a = img.pixeis[i][j].a + value > new_img.max_value ? 
                                                new_img.max_value:img.pixeis[i][j].a + value;
            }
        }
        new_img.pixeis = matriz;
        return new_img;
    }
}
Image brightnessAjust(Image img, char value){
    if (value < 0) return reduceBrightness(img, value);
    else return increaseBrightness(img, value);
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
Image toOlder(Image old_img){
    Image new_img;
    new_img.height = old_img.height;
    new_img.width = old_img.width;
    new_img.max_value = old_img.max_value;
    Pixel **matriz;
    matriz = (Pixel**)malloc(old_img.height * sizeof(Pixel*));
    for (int i = 0; i < old_img.height; i++) {
        matriz[i] = (Pixel*)malloc(old_img.width * sizeof(Pixel));
    }
    if (old_img.format == RGB){
        new_img.format = RGB;
        for (int i = 0; i < old_img.height; i++)
        {
            for (int j = 0; j < old_img.width; j++)
            {
                int newR =  0.393 * old_img.pixeis[i][j].r +
                            0.769 * old_img.pixeis[i][j].g +
                            0.189 * old_img.pixeis[i][j].b;
                matriz[i][j].r = newR > 255 ? 255:newR;
                int newG =  0.349 * old_img.pixeis[i][j].r +
                            0.686 * old_img.pixeis[i][j].g + 
                            0.168 * old_img.pixeis[i][j].b;
                matriz[i][j].g = newG > 255 ? 255:newG;
                int newB =  0.272 * old_img.pixeis[i][j].r + 
                            0.534 * old_img.pixeis[i][j].g + 
                            0.131 * old_img.pixeis[i][j].b;
                matriz[i][j].b = newB > 255 ? 255:newB;
            }
        }
        new_img.pixeis = matriz;
        return new_img;
    }
}
FILE* writeGreyScaleImage(Image img){
    char new_file_name[30] = "new_";
    strcat(new_file_name,file_name);
    FILE *new_fp;
    new_fp = fopen(new_file_name,"w+");
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
    char new_file_name[30] = "new_";
    strcat(new_file_name,file_name);
    FILE *new_fp;
    new_fp = fopen(new_file_name,"w+");
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
FILE* writeImage(Image img){
    if (img.format == GREYSCALE){
        return writeGreyScaleImage(img);
    }
    if (img.format == RGB){
        return writeColorImage(img);
    }
}
void main(void){
    
    unsigned char image_modification_choice;
    printf("Digite o nome do arquivo: ");
    scanf("%s",file_name);
    printf("Digite:\n0 - Gerar imagem em tons de cinza\n1 - Imagem em tons de cinza - gerar imagem negativa\n2 - Imagem tons de cinza - aumentar o brilho\n");
    printf("3 - Imagem tons de cinza - diminuir o brilho\n4 - Rotacionar imagem colorida -90 graus\n5 - Imagem colorida - envelhecimento da imagem");
    printf("Escolha: ");
    FILE *fp;
    fp = fopen(file_name,"r");
    Image img = readImage(fp);
    //printf("%s",file_name);
    while(1) {
        scanf("%d",&image_modification_choice);
        if(image_modification_choice < 6) {
            break;
        }
    }
    if(image_modification_choice == 0) {
        Image gray_img = toGrayScale(img);
        writeGreyScaleImage(gray_img);
        free(&gray_img.pixeis[0]);
    }
    else if(image_modification_choice == 1) {
        Image gray_img = toGrayScale(img);
        Image negative_img = toNegative(gray_img);
        writeGreyScaleImage(negative_img);
        free(&gray_img.pixeis[0]);
        free(&negative_img.pixeis[0]);
    }
    else if(image_modification_choice == 2) {
        Image gray_img = toGrayScale(img);
        Image increase_img_brightness = brightnessAjust(gray_img,100);
        writeGreyScaleImage(increase_img_brightness);
        free(&gray_img.pixeis[0]);
        free(&increase_img_brightness.pixeis[0]);
    }
    else if(image_modification_choice == 3) {
        Image gray_img = toGrayScale(img);
        Image decrease_img_brightness = brightnessAjust(gray_img,-100);
        writeGreyScaleImage(decrease_img_brightness);
        free(&gray_img.pixeis[0]);
        free(&decrease_img_brightness.pixeis[0]);
    }
    else if(image_modification_choice == 4) {
        Image rotate_img = to90graus(img);
        writeColorImage(rotate_img);
        free(&rotate_img.pixeis[0]);
    }
    else {
        Image age_img = toOlder(img);
        writeColorImage(age_img);
        free(&age_img.pixeis[0]);
    }
    free(&img.pixeis[0]);
    fclose(fp);
}
