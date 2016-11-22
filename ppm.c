# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <math.h>


#define MAX 500
#define NORM 2*3.1415/255

int main(int argc, char** argv) {
    char *entrada;
    char *saida;
    char formato[2];
    char c;

    int largura;
    int altura;
    int maximo;

    int iteracoes;
    int processadores;

    int i, j;

    int **red;
    int **grn;
    int **blu;

    double angulo_1, angulo_2;

    FILE *imagem, *nova_imagem; 

    entrada = argv[1];
    saida = argv[2];
    iteracoes = atoi (argv[3]);
    processadores = atoi (argv[4]);

    imagem = fopen (entrada, "r");
    nova_imagem = fopen (saida, "w");

    fscanf (imagem, "%s", formato);
    printf("\n%s\n", formato);

    c = getc (imagem);
    c = getc (imagem);
    while (!isdigit(c)) {
        while (getc (imagem) != '\n') ;
        c = getc(imagem);
    }
    ungetc (c, imagem);
    

    fscanf (imagem, "%d %d %d", &largura, &altura, &maximo);

    printf("%s %d %d %d %d %d %s\n", formato, largura, altura, maximo, iteracoes, processadores, saida);


    red = malloc (altura * sizeof (int *));
        for (i = 0; i < altura; i++)
            red[i] = malloc (largura *sizeof (int));
    grn = malloc (altura * sizeof (int *));
        for (i = 0; i < altura; i++)
            grn[i] = malloc (largura *sizeof (int));        
    blu = malloc (altura * sizeof (int *));
        for (i = 0; i < altura; i++)
            blu[i] = malloc (largura *sizeof (int));

    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            fscanf (imagem, "%d", &red[i][j]);
            fscanf (imagem, "%d", &grn[i][j]);
            fscanf (imagem, "%d", &blu[i][j]);

        }
    }

    for (i = 1; i < altura - 1; i++) {
        for (j = 1; j < largura - 1; j++) {

            angulo_1 = grn[i][j]*NORM;

            if (angulo_1 < 0.5*3.14159265) {

                red[i - 1][j] = (int) 63.75*((1 - (double) red[i - 1][j]/255) * red[i][j]/255);
                red[i][j + 1] = (int) 63.75*((1 - (double) red[i][j + 1]/255) * red[i][j]/255);
                blu[i + 1][j] = (int) 63.75*((1 - (double) blu[i + 1][j]/255) * blu[i][j]/255);
                blu[i][j - 1] = (int) 63.75*((1 - (double) blu[i][j - 1]/255) * blu[i][j]/255);

            }
            else if (angulo_1 < 3.14159265) {

                red[i + 1][j] = (int) 63.75*((1 - (double) red[i + 1][j]/255) * red[i][j]/255);
                red[i][j + 1] = (int) 63.75*((1 - (double) red[i][j + 1]/255) * red[i][j]/255);
                blu[i - 1][j] = (int) 63.75*((1 - (double) blu[i - 1][j]/255) * blu[i][j]/255);
                blu[i][j - 1] = (int) 63.75*((1 - (double) blu[i][j - 1]/255) * blu[i][j]/255);

            }
            else if (angulo_1 < 1.5*3.14159265) {

                red[i + 1][j] = (int) 63.75*((1 - (double) red[i + 1][j]/255) * red[i][j]/255);
                red[i][j - 1] = (int) 63.75*((1 - (double) red[i][j - 1]/255) * red[i][j]/255);
                blu[i - 1][j] = (int) 63.75*((1 - (double) blu[i - 1][j]/255) * blu[i][j]/255);
                blu[i][j + 1] = (int) 63.75*((1 - (double) blu[i][j + 1]/255) * blu[i][j]/255);

            }
            else { /* (angulo_1 < 2*3.14159265) */

                red[i - 1][j] = (int) 63.75*((1 - (double) red[i - 1][j]/255) * red[i][j]/255);
                red[i][j - 1] = (int) 63.75*((1 - (double) red[i][j - 1]/255) * red[i][j]/255);
                blu[i + 1][j] = (int) 63.75*((1 - (double) blu[i + 1][j]/255) * blu[i][j]/255);
                blu[i][j + 1] = (int) 63.75*((1 - (double) blu[i][j + 1]/255) * blu[i][j]/255);
            }
        }
    }

    for (i = 1; i < altura - 1; i++) {
        for (j = 1; j < largura - 1; j++) {
            angulo_1 = grn[i][j]*NORM;
            angulo_2 = atan2 ((double) blu[i][j], (double) red[i][j]);
            grn[i][j] = (int) ((angulo_1 + angulo_2)*255/2)%255;
        }
    }
   
    fprintf (nova_imagem, "%s\n", formato);
    fprintf (nova_imagem, "%d %d\n", largura, altura);
    fprintf (nova_imagem, "%d\n", maximo);

    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++)
            fprintf (nova_imagem, "%d %d %d\n", red[i][j], grn[i][j], blu[i][j]);
    }

    return 0;
}



