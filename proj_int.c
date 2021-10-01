#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main () {

    FILE *fp;
    //char tab_c[2] = {"0"}, tab_l[2] = {"0"}, tes_l[2] = {"0"}, tes_c[2] = {"0"}, tipo_int[2] = {"0"}, num_pretas[3] = {"0"};
    int tab_c = 0, tab_l = 0, tes_l = 0, tes_c = 0, num_pretas = 0;
    char tipo_int[2] = {"0"};
    int parede_1 = 0, parede_2 = 0, parede_v = 0;

    char ch = '0', ch_next = '0';
    char temp_string[4] = {"0"};
    int cont = 0;
    int cont_n = 0, t = 0;

    int t_counter = 0;



    fp = fopen("enunciado202.in1", "r");

    // Calcula a quantidade de informação da tabela + paredes

    for (int i = 0; i < 100; i++) {
        fscanf(fp, " ");
        fscanf(fp, "\n");

        if(feof(fp) != 0) break; 

        if (i > 5 /* && tipo_jogo != A6 */) {    // Ler Paredes para apenas 1 int

            if (t_counter == 0) {
                fscanf(fp, "%d", &parede_1);
                t_counter++; 
            }
            if (t_counter == 1) {
                fscanf(fp, "%d", &parede_2);
                t_counter++;
            }
            if (t_counter == 2) {
                fscanf(fp, "%d", &parede_v);
                t_counter = 0;
                printf("%d %d %d\n", parede_1, parede_2, parede_v);
            }
        } else {
            fscanf(fp, "%s", temp_string);
            printf("%s\n", temp_string);
        }
    }




    /*
    cont = 0;

    for (int i = 0; i < 10; i++) {  // i indica qual é o numero da "palavra" em que vou

        while (1) {

            ch = fgetc(fp);

            if (ch == ' ' && ch != '\n' && cont == 0) continue;

            if (ch != ' ' && ch != '\n') {
                temp_string[cont] = ch;
                cont++;
            } else {
                switch (i) {
                    case 0:
                        tab_c = atoi(temp_string);
                        break;
                    case 1:
                        tab_l = atoi(temp_string);
                        break; 
                    case 2:
                        tes_c = atoi(temp_string);
                        break;
                    case 3:
                        tes_l = atoi(temp_string);
                        break;
                    case 4:
                        tipo_int[0] = temp_string [0];
                        tipo_int[1] = temp_string [1];
                        break;
                    case 5:
                        num_pretas = atoi(temp_string);
                        break;
                    default:
                        parede = atoi(temp_string);
                        break;
                }   
                cont = 0;
                break;
            }
        }
        memset(temp_string, 0, sizeof(temp_string));
        

        // Resolver o problema para ler as linhas das paredes e o seu valor
    }*/

    fclose(fp);

}