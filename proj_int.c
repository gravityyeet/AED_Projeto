#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main () {

    FILE *fp;
    //char tab_c[2] = {"0"}, tab_l[2] = {"0"}, tes_l[2] = {"0"}, tes_c[2] = {"0"}, tipo_int[2] = {"0"}, num_pretas[3] = {"0"};
    int tab_c = 0, tab_l = 0, tes_l = 0, tes_c = 0, num_pretas = 0;
    char tipo_int[2] = {"0"};
    int parede = 0;

    char ch = '0', ch_next = '0';
    char temp_string[4] = {"0"};
    int cont = 0;
    int cont_n = 0, t = 0;



    fp = fopen("enunciado202.in1", "r");

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







        /*
        // Contar o numero de algarismos do numero 
        
        while  (1) {
            ch = fgetc(fp);

            if (ch != ' ' && ch != '\n') {
                cont_n++;
            } else {
                break;
            }    
        }
        t = -cont_n - 1;

        fseek(fp, t, SEEK_CUR);

        // Voltar atras n espaços e carrega los para malloc

        // Passar o numero para uma string

        for (int j = 0; j < cont_n; j++) {
            ch = fgetc(fp);

            temp_string[j] = ch;    
        }


        switch (i) {
            case 0:
                tab_c = atoi(temp_string);
                break;
            case 1:
                tab_l = atoi(temp_string);
                break; 
            default:
                break;
        }    

        


        cont_n = 0;~
        */


        /*
        for (int j = 0; ch != ' ' && ch != '\n'; j++) {

            ch = fgetc(fp);
            
            //fseek(fp, 1, SEEK_CUR);
            ch_next = fgetc(fp);

            temp_string[j] = ch;

            if (ch_next == ' ' || ch_next == '\n') break;   

        }
        printf("%c %c %c %c\n", temp_string[0], temp_string[1], temp_string[2], temp_string[3]);

        fseek(fp, 1, SEEK_CUR);/*



        /*
        ch = fgetc(fp);

        if (ch != ' ' && ch != '\n') {
            temp_string[cont] = ch;
            printf("%c ", temp_string[cont]);
            cont++;
        } else {
            cont = 0;
        }*/

        //printf("%c %c %c %c\n", temp_string[0], temp_string[1], temp_string[2], temp_string[3]);


    }

    fclose(fp);

}