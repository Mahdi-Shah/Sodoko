# include <stdio.h>

void sefrer();
void get_input();
void print_jadval();
void mosavi_yab();
void satr_checker(int i);
void sotoon_checker(int j);
void check(int i, int j);
void farakhan(int i, int j);
void satr_o_sotoon_checker(int i, int j);
void sefrer2(int array[]);
void corect_jadval();
void plus_corectivity();
void multiple_corectivity();


int abaad, tedad_shart;
int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0;
//reste_anything[i][0] = tool(whitout javab)       reshte_anything = [i][1] = javab
int jadval[25][25], reshte[27], reshte_plus[225][27], reshte_minus[225][27], reshte_mod[225][27], reshte_divide[225][27], reshte_equality[225][27], reshte_multiple[225][27];
char alamat[225];

int main(){

    get_input();
    sefrer();
    mosavi_yab();
    //printf("%d %d %d&&\n", reshte_equality[0][0][1], reshte[0], reshte_equality[0][0][2]);
    print_jadval();


    return 0;
}

void print_jadval(){
    for (int i = 0; i < abaad; i++){
        for (int j = 0; j < abaad; j++){
            printf("%d ", jadval[i][j]);
        }
        printf("\n");
    }
}

void sefrer(){
    for (int i = 0; i < abaad; i++){
        for (int j = 0; j < abaad; j++){
            jadval[i][j] = 0;
        }
    }
}

void get_input(){
    scanf("%d %d", &abaad, &tedad_shart);
    for (int i = 0; i < tedad_shart; i++){
        scanf("%d", &reshte[0]);
        for (int j = 2; j < reshte[0] + 2; j++){
            scanf("%d", &reshte[j]);
            //printf("%d ", reshte[i]);
        }
        //printf("\n");
        scanf(" %c %d", &alamat[i], &reshte[1]);
        if (alamat[i] == '+'){
            for (int j = 0; j < reshte[0] + 2; j++){
                reshte_plus[a1][j] = reshte[j];
            }
        a1++;
        }
        else if (alamat[i] == '*'){
            for (int j = 0; j < reshte[0] + 2; j++){
                reshte_multiple[a2][j] = reshte[j];
            }
        a2++;
        }
        else if (alamat[i] == '-'){
            for (int j = 0; j < reshte[0] + 2; j++){
                reshte_minus[a3][j] = reshte[j];
            }
        a3++;
        }
        else if (alamat[i] == '/'){
            for (int j = 0; j < reshte[0] + 2; j++){
                reshte_divide[a4][j] = reshte[j];
            }
        a4++;
        }
        else if (alamat[i] == '%'){
            for (int j = 0; j < reshte[0] + 2; j++){
                reshte_mod[a5][j] = reshte[j];
            }
        a5++;
        }
        else if (alamat[i] == '='){
            for (int j = 0; j < reshte[0] + 2; j++){
                reshte_equality[a6][j] = reshte[j];
            }
        a6++;
        }
    }
}

void mosavi_yab(){
    int k, t;
    for (int i = 0; i < a6; i++){
        k = reshte_equality[i][2] / abaad;
        t = reshte_equality[i][2] % abaad;
        //printf("*%d %d %d*", k, t, reshte_equality[i][0][1]);
        jadval[k][t] = reshte_equality[i][1];
        //printf("||%d||\n", jadval[k][t][0]);
    }
}

void check(int i, int j){
    int counter = 0;
    for (int k = 0; k < abaad; k++){
        if (jadval[i][k] == jadval[i][j])
            counter++;
        if (jadval[k][j] == jadval[i][j])
            counter++;
    }
    if(counter > 2)
        jadval[i][j] = 0;
    plus_corectivity();
    multiple_corectivity();
    corect_jadval();
}

void satr_checker(int i){
    int kontor = 0, akharin, majmoo = 0;
    for (int k = 0; k < abaad; k++){
        if (jadval[i][k]){
            kontor++;
            majmoo += jadval[i][k];
        }
        if (!jadval[i][k])
            akharin = k;
    }
    if (kontor == abaad - 1){
        jadval[i][akharin] = (((abaad + 1) * (abaad)) / 2) - majmoo;
        //check() //mohem
    }
    else
        return ;
}

void sotoon_checker(int j){
    int kontor = 0, akharin, majmoo = 0;
    for (int k = 0; k < abaad; k++){
        if (jadval[k][j]){
            kontor++;
            majmoo += jadval[k][j];
        }
        if (!jadval[k][j])
            akharin = k;
    }
    if (kontor == abaad - 1){
        jadval[akharin][j] = (((abaad + 1) * (abaad)) / 2) - majmoo;
        //check() //mohem
    }
    else
        return ;
}

void farakhan(int i, int j){
    for (int k = 0; k < abaad; k++){
        if (!jadval[i][k]){
            satr_o_sotoon_checker(i, k);
        }
        if (!jadval[k][j]){
            satr_o_sotoon_checker(k, j);
        }
    }
}

void satr_o_sotoon_checker(int i, int j){
    int marja[abaad], error = 0, majmoo = (((abaad + 1) * (abaad)) / 2);
    sefrer2(marja);
    for (int k = 0; k < abaad; k++){
        if (!marja[jadval[i][k]] && jadval[i][k]){
            marja[jadval[i][k]] = 1;
            majmoo -= jadval[i][k];
            error++;
        }
        if (!marja[jadval[k][j]] && jadval[i][k]){
            marja[jadval[k][j]] = 1;
            majmoo -= jadval[k][j];
            error++;
        }
    }
    if (abaad - 1 == error){
        jadval[i][j] = majmoo;
        //check() //mohem
    }
}

void sefrer2(int array[]){
    for (int i = 0; i < abaad; i++){
        array[i] = 0;
    }
}

void corect_jadval(){
    for (int i = 0; i < abaad; i++){
        for (int j = 0; j < abaad; j++){
            if (!jadval[i][j])
                return;
        }
    }
    for (int i = 0; i < abaad; i++){
        for (int j = 0; j < abaad; j++){
            printf("%d ", jadval[i][j]);
        }
        printf("\n");
    }
}

void plus_corectivity(){
    int jam = 0, k, t, r = 0;
    for (int i = 0; i < a1; i++){
        for (int j = 2; j < reshte_plus[i][0] + 2; j++){
            k = reshte_plus[i][j] / abaad;
            t = reshte_plus[i][j] % abaad;
            jam += jadval[k][t];
            if (!jadval[k][t]){
                jam++;
                r++;
            }
        }
        if (jam > reshte_plus[i][1])
            return;
        else if (r == 0 && jam != reshte_plus[i][1])
            return;
    }
}

void multiple_corectivity(){
    int zarb = 1, k, t, r = 0;
    for (int i = 0; i < a2; i++){
        for (int j = 2; j < reshte_multiple[i][0] + 2; j++){
            k = reshte_plus[i][j] / abaad;
            t = reshte_plus[i][j] % abaad;
            if (!jadval[k][t]){
                zarb *= (jadval[k][t] + 1);
                r++;
            }
            else
                zarb *= jadval[k][t];
        }
        if (zarb > reshte_multiple[i][1])
            return;
        else if (r == 0 && zarb != reshte_multiple[i][1])
            return;
    }
}

