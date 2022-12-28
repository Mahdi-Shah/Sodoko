# include <stdio.h>
# include <math.h>
# include <stdbool.h>

/*
4 5
2 2 3 - 1
2 7 11 % 3
2 0 4 % 3
2 13 14 % 3
1 15 = 3
*/
/*
4 12
2 0 2 / 2
2 0 7 / 2
2 0 8 / 2
2 0 13 / 2
2 2 3 / 2
2 2 5 / 2
2 2 10 / 2
2 2 12 / 2
2 1 6 - 2
2 6 4 - 2
2 6 11 - 2
2 6 14 - 2

4 7
4 0 1 4 5 * 36
2 2 3 - 1
3 6 9 10 * 12
2 7 11 / 2
2 8 12 - 2
2 13 14 + 3
1 15 = 3
*/

void sefrer();
void get_input();
void print_jadval();
void mosavi_yab();
bool check(int i, int j);
void sefrer2(int array[]);
int plus_corectivity();
int multiple_corectivity();
int row_coloumn();
bool dfs(int i);
bool divide_dfs(int i);
bool minus_dfs(int i);
bool mod_dfs(int i);

int abaad, tedad_shart;
int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0;
//reste_anything[i][0] = tool(whitout javab)       reshte_anything = [i][1] = javab
int jadval[25][25], reshte[27], reshte_plus[225][225], reshte_minus[225][4], reshte_mod[225][4], reshte_divide[225][4], reshte_equality[225][3], reshte_multiple[225][225];
int divide[225], minoos[225], mod[225], mod2[225];
bool a, b;
char alamat[225];

int main(){

    get_input();
    mosavi_yab();
    divide[0] = 1;
    minoos[0] = 1;
    mod2[0] = 0;
    mod[0] = 0;
    a = dfs(0);
    if (a)
        print_jadval();

    return 0;
}

bool dfs(int i){
    int x, y;
    if (i < a4){
        //printf("%d\n", i);
        divide[i + 1] = 1;
        return divide_dfs(i);
    }
    else if (i < a3 + a4){
        minoos[i + 1 - a4] = 1;
        return minus_dfs(i);
    }
    else if (i < a5 + a3 + a4){
        mod[i + 1 - a4 - a3] = 0;
        mod2[i + 1 - a4 - a3] = 0;
        return mod_dfs(i);
    }
    for (int j = 0; j < abaad * abaad; j++){
        x = j / abaad;
        y = j % abaad;
        if (!jadval[x][y]){
            for (int n = 1; n <= abaad; n++){
                jadval[x][y] = n;
                if (check(x, y)){
                    a = dfs(i + 1);
                    if (a)
                        return true;
                }
                jadval[x][y] = 0;
            }
            return false;
        }
    }
    return true;
}

bool mod_dfs(int i){
    int x, y, z, t, r;
    x = reshte_mod[i - a4 - a3][2] / abaad;
    y = reshte_mod[i - a4 - a3][2] % abaad;
    z = reshte_mod[i - a4 - a3][3] / abaad;
    t = reshte_mod[i - a4 - a3][3] % abaad;
    if (jadval[x][y] && jadval[z][t]){
            if (!((jadval[x][y] - jadval[z][t]) % reshte_mod[i - a4 - a3][1]))
                return dfs(i + 1);
            return false;
    }
    else{
        for (; mod[i - a4 - a3] < abaad; mod[i - a4 - a3]++){
            if (jadval[x][y] && !jadval[z][t]){
                jadval[z][t] = jadval[x][y] + (reshte_mod[i - a4 - a3][1]) * mod[i - a4 - a3];
                a = check(z, t);
                if (a){
                    b = dfs(i + 1);
                    if (b)
                        return true;
                }
                jadval[z][t] = jadval[x][y] - (reshte_mod[i - a4 - a3][1]) * mod[i - a4 - a3];
                a = check(z, t);
                if (a){
                    b = dfs(i + 1);
                    if (b)
                        return true;
                }
                jadval[z][t] = 0;
            }
            else if (!jadval[x][y] && jadval[z][t]){
                jadval[x][y] = jadval[z][t] + reshte_mod[i - a4 - a3][1] * mod[i - a4 - a3];
                a = check(x, y);
                if (a){
                    b = dfs(i + 1);
                    if (b)
                        return true;
                }
                jadval[x][y] = jadval[z][t] - reshte_mod[i - a4 - a3][1] * mod[i - a4 - a3];
                a = check(z, t);
                if (a){
                    b = dfs(i + 1);
                    if (b)
                        return true;
                }
                jadval[x][y] = 0;
            }
            else if (!jadval[x][y] && !jadval[z][t]){
                //printf("!!\n");
                for (; mod2[i - a4 - a3] < abaad; ++mod2[i - a4 - a3]){
                    jadval[x][y] = mod[i - a4 - a3];
                    jadval[z][t] = mod[i - a4 - a3] + reshte_mod[i - a4 - a3][1] * (mod2[i - a4 - a3]);
                    a = check(x, y) & check(z, t);
                    //printf("%d %d*\n", jadval[x][y], jadval[z][t]);
                    if (a){
                        //printf("^^");
                        b = dfs(i + 1);
                        if (b)
                            return true;
                        //printf("&&");
                    }
                    /*x = reshte_mod[i - a4 - a3][2] / abaad;
                    y = reshte_mod[i - a4 - a3][2] % abaad;
                    z = reshte_mod[i - a4 - a3][3] / abaad;
                    t = reshte_mod[i - a4 - a3][3] % abaad;*/
                    jadval[x][y] = mod[i - a4 - a3] + reshte_mod[i - a4 - a3][1] * mod2[i - a4 - a3];
                    jadval[z][t] = mod[i - a4 - a3];
                    a = check(x, y) & check(z, t);
                    //printf("%d %d*\n", jadval[x][y], jadval[z][t]);
                    if (a){
                        //printf("qw");
                        b = dfs(i + 1);
                        if (b)
                            return true;
                    }
                }
                mod2[i - a4 - a3] = 0;
                /*x = reshte_mod[i - a4 - a3][2] / abaad;
                y = reshte_mod[i - a4 - a3][2] % abaad;
                z = reshte_mod[i - a4 - a3][3] / abaad;
                t = reshte_mod[i - a4 - a3][3] % abaad;*/
                jadval[x][y] = 0;
                jadval[z][t] = 0;
            }
        }
        mod[i - a4 - a3] = 0;
        return false;
    }
}

bool minus_dfs(int i){
    int x, y, z, t, r;
    x = reshte_minus[i - a4][2] / abaad;
    y = reshte_minus[i - a4][2] % abaad;
    z = reshte_minus[i - a4][3] / abaad;
    t = reshte_minus[i - a4][3] % abaad;
    if (jadval[x][y] && !jadval[z][t]){
        jadval[z][t] = jadval[x][y] + reshte_minus[i - a4][1];
        a = check(z, t);
        if (a){
            b = dfs(i + 1);
            if (b)
                return true;
        }
        jadval[z][t] = jadval[x][y] - reshte_minus[i - a4][1];
        a = check(z, t);
        if (a){
            b = dfs(i + 1);
            if (b)
                return true;
        }
        jadval[z][t] = 0;
        return false;
    }
    else if (!jadval[x][y] && jadval[z][t]){
        jadval[x][y] = jadval[z][t] + reshte_minus[i - a4][1];
        a = check(x, y);
        if (a){
            b = dfs(i + 1);
            if (b)
                return true;
        }
        jadval[x][y] = jadval[z][t] - reshte_minus[i - a4][1];
        a = check(z, t);
        if (a){
            b = dfs(i + 1);
            if (b)
                return true;
        }
        jadval[x][y] = 0;
        return false;
    }
    else if (!jadval[x][y] && !jadval[z][t]){
        for (; minoos[i - a4] <= abaad; ++minoos[i - a4]){
                //printf("!!");
                jadval[x][y] = minoos[i - a4];
                jadval[z][t] = minoos[i - a4] + reshte_minus[i - a4][1];
                a = check(x, y) & check(z, t);
                //printf("%d %d*\n", jadval[x][y], jadval[z][t]);
                if (a){
                    //printf("^^");
                    b = dfs(i + 1);
                    if (b)
                        return true;
                }
                jadval[x][y] = minoos[i - a4] + reshte_minus[i - a4][1];
                jadval[z][t] = minoos[i - a4];
                a = check(x, y) & check(z, t);
                //printf("%d %d*\n", jadval[x][y], jadval[z][t]);
                if (a){
                    //printf("qw");
                    b = dfs(i + 1);
                    if (b)
                        return true;
                }
        }
        minoos[i - a4] = 1;
        jadval[x][y] = 0;
        jadval[z][t] = 0;
        return false;
    }
        else{
            if (abs(jadval[x][y] - jadval[z][t]) == reshte_minus[i - a4][1])
                return dfs(i + 1);
            return false;
        }
        jadval[x][y] = 0;
        jadval[z][t] = 0;
        return false;
}

bool divide_dfs(int i){
    int x, y, z, t, r;
    x = reshte_divide[i][2] / abaad;
    y = reshte_divide[i][2] % abaad;
    z = reshte_divide[i][3] / abaad;
    t = reshte_divide[i][3] % abaad;
    if (jadval[x][y] && !jadval[z][t]){
        jadval[z][t] = jadval[x][y] * reshte_divide[i][1];
        a = check(z, t);
        if (a){
            b = dfs(i + 1);
            if (b)
                return true;
        }
        if (!(jadval[x][y] % reshte_divide[i][1])){
            jadval[z][t] = jadval[x][y] / reshte_divide[i][1];
            a = check(z, t);
            if (a){
                b = dfs(i + 1);
                if (b)
                    return true;
            }
        }
        jadval[z][t] = 0;
        return false;
    }
    else if (!jadval[x][y] && jadval[z][t]){
        jadval[x][y] = jadval[z][t] * reshte_divide[i][1];
        a = check(x, y);
        if (a){
            b = dfs(i + 1);
            if (b)
                return true;
        }
        if (!(jadval[z][t] % reshte_divide[i][1])){
            jadval[x][y] = jadval[z][t] / reshte_divide[i][1];
            a = check(z, t);
            if (a){
                b = dfs(i + 1);
                if (b)
                    return true;
            }
        }
        jadval[x][y] = 0;
        return false;
    }
    else if (!jadval[x][y] && !jadval[z][t]){
        for (; divide[i] <= abaad; ++divide[i]){
                //printf("!!");
                jadval[x][y] = divide[i];
                jadval[z][t] = divide[i] * reshte_divide[i][1];
                a = check(x, y) & check(z, t);
                //printf("%d*", a);
                if (a){
                    //printf("^^");
                    b = dfs(i + 1);
                    if (b)
                        return true;
                }
                jadval[x][y] = divide[i] * reshte_divide[i][1];
                jadval[z][t] = divide[i];
                a = check(x, y) & check(z, t);
                if (a){
                    //printf("qw");
                    b = dfs(i + 1);
                    if (b)
                        return true;
                }
        }
        divide[i] = 1;
        jadval[x][y] = 0;
        jadval[z][t] = 0;
        return false;
    }
        else{
            if (jadval[x][y] == jadval[z][t])
                r = 1;
            else
                r = jadval[x][y] / jadval[z][t] + jadval[z][t] / jadval[x][y];
            if (r != reshte_divide[i][1])
                return false;
            return true;
        }

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

bool check(int i, int j){
    //printf("\n#jadval[%d][%d] = %d\n",i ,j , jadval[i][j]);
    if (jadval[i][j] > 0 && jadval[i][j] <= abaad){
        //printf("a");
        if (row_coloumn(i, j)){
            //printf("b");
            if (multiple_corectivity()){
                //printf("c");
                if (plus_corectivity()){
                    //printf("d");
                    return true;
                }
            }
        }
    }
    return false;
}

int row_coloumn(int i, int j){
    int counter = 0;
    for (int k = 0; k < abaad; k++){
        if (jadval[i][k] == jadval[i][j])
            counter++;
        if (jadval[k][j] == jadval[i][j])
            counter++;
    }
    if (counter > 2)
        return 0;
    return 1;
}

void sefrer2(int array[]){
    for (int i = 0; i < 225; i++){
        array[i] = 0;
    }
}

int plus_corectivity(){
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
            return 0;
        else if (r == 0 && jam != reshte_plus[i][1])
            return 0;
        jam = 0;
    }
    return 1;
}

int multiple_corectivity(){
    int zarb = 1, k, t, r = 0;
    for (int s = 0; s < a2; s++){
        //printf("\n$$ ");
        for (int j = 2; j < reshte_multiple[s][0] + 2; j++){
            k = reshte_multiple[s][j] / abaad;
            t = reshte_multiple[s][j] % abaad;
            //printf("jadval[%d][%d] * ", k, t);
            if (!jadval[k][t]){
                zarb *= (jadval[k][t] + 1);
                r++;
            }
            else
                zarb *= jadval[k][t];
        }
        //printf("= %d", zarb);
        if (zarb > reshte_multiple[s][1])
            return 0;
        else if (r == 0 && zarb != reshte_multiple[s][1])
            return 0;
        zarb = 1;
    }
    return 1;
}

