#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define INF 99999

void dijkstra(float **mat, int n, int start, int stop, int task, float *suma, char drum[4])
{
    float dist[n];
    int i, j, k, poz;

    int vector[n];
    for (i = 0; i < n; i++)
        vector[i] = -1;

    int vizitat[n];
    for (i = 0; i < n; i++)
    {
        dist[i] = INF;
        vizitat[i] = 0;
    }

    dist[start] = 0;
    for (i = 0; i < n - 1; i++)
    {
        int indice, min = INF;

        for (j = 0; j < n; j++)
            if (vizitat[j] == 0 && min >= dist[j])
            {
                min = dist[j];
                indice = j;
            }
        vizitat[indice] = 1;

        if (dist[indice] != INF)
            for (j = 0; j < n; j++)
                if (vizitat[j] == 0 && mat[indice][j] && dist[indice] + mat[indice][j] < dist[j])
                {
                    dist[j] = dist[indice] + mat[indice][j];
                    vector[j] = indice;
                }
    }
    int n_cale = 0, cale[30];
    for (i = 0; i < n; i++)
        if (i == stop)
        {
            j = i;
            cale[n_cale++] = j;
            do
            {
                j = vector[j];
                cale[n_cale++] = j;
            } while (j != start);
        }
    // task 0-->afiseaza distanta
    // task 1-->afiseaza path-ul

    if (task == 0)
    {
        if (strcmp(drum, "dus") == 0)
            printf("%.1f ", dist[stop]);
        else
            printf("%.1f", dist[stop]);
        *suma = *suma + dist[stop];
    }
    else
    {
        if (strcmp(drum, "dus") == 0)
            for (i = 1; i < n_cale; i++)
                printf("%d ", cale[n_cale - i - 1]);
        else
        {
            for (i = 1; i < n_cale - 1; i++)
                printf("%d ", cale[n_cale - i - 1]);
            printf("%d", cale[0]);
        }
    }
}

void dfs_1(float **mat, int n, int x, int *vizitat)
{ // plus
    vizitat[x] = 1;

    for (int i = 0; i < n; i++)
        if (mat[x][i] && !vizitat[i])
            dfs_1(mat, n, i, vizitat);
}
void dfs_2(float **mat, int n, int x, int *vizitat)
{ // minus
    vizitat[x] = 1;

    for (int i = 0; i < n; i++)
        if (!vizitat[i] && mat[i][x])
            dfs_2(mat, n, i, vizitat);
}
void plus_minus(float **mat, int n, int *comp, int *nrc, int nr_d, int dep[30])
{
    int i, j, viz1[30], viz2[30];
    *nrc = 0; // numarul de componente conexe
    // initializare vector de componente tare conexe
    for (i = 0; i < n; i++)
        comp[i] = 0;
    for (i = 0; i < nr_d; i++)
        comp[dep[i]] = -1; // scot depozitele

    for (i = 0; i < n; i++)
    {
        if (comp[i] == 0)
        {
            for (j = 0; j < n; j++)
                viz1[j] = viz2[j] = 0;
            (*nrc)++;

            dfs_1(mat, n, i, viz1); // dfs cu plus
            dfs_2(mat, n, i, viz2); // dfs cu minus

            for (j = 0; j < n; j++)
                if (viz1[j] == 1 && viz2[j] == 1) // cele care au atat plus, cat si minus, formeaza o componenta tare conexa
                    comp[j] = *nrc;
        }
    }
}
void dijkstra_task3(float **mat, int n, int start, int stop, float *suma)
{
    float dist[n];
    int i, j, k, poz, indice;

    int vector[n];
    for (i = 0; i < n; i++)
        vector[i] = -1;

    int vizitat[n];
    for (i = 0; i < n; i++)
    {
        dist[i] = INF;
        vizitat[i] = 0;
    }

    dist[start] = 0;
    for (i = 0; i < n - 1; i++)
    {
        int indice, min = INF;

        for (j = 0; j < n; j++)
            if (vizitat[j] == 0 && min >= dist[j])
            {
                min = dist[j];
                indice = j;
            }
        vizitat[indice] = 1;

        if (dist[indice] != INF)
            for (j = 0; j < n; j++)
                if (vizitat[j] == 0 && mat[indice][j] && dist[indice] + mat[indice][j] < dist[j])
                {
                    dist[j] = dist[indice] + mat[indice][j];
                    vector[j] = indice;
                }
    }
    *suma = *suma + dist[stop];
}
float cost = 0;
int visi[30];
void initialize(int n)
{
    for (int ind = 0; ind < n; ind++)
        visi[ind] = 0;
}
int tsp(float **mat, int n, int nod)
{
    int i, nod_apropiat = INF;
    float s_min = INF, temporar;
    for (i = 0; i < n; i++)
    {
        if ((mat[nod][i] != 0) && (visi[i] == 0))
        {
            if (mat[nod][i] + mat[i][0] < s_min)
                s_min = mat[i][0] + mat[nod][i];
            temporar = mat[nod][i];
            nod_apropiat = i;
        }
    }
    if (s_min != INF)
        cost = cost + temporar;
    return nod_apropiat;
}
void cost_minim(float **mat, int n, int nod, int dep, int *indice)
{
    int nod_apropriat;
    visi[nod] = 1;
    *indice = nod;
    //printf("%d ", nod);
    nod_apropriat = tsp(mat, n, nod);
    if (nod_apropriat == INF )
    {
        cost = cost + mat[nod][dep];
        return;
    }
    cost_minim(mat, n, nod_apropriat, dep, indice);
}

void printare_mat(float **mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%.1f ", mat[i][j]);
        printf("\n");
    }
}
int main()
{
    int n, m, d;
    int depozit[30];
    // n-->nr noduri
    // m-->nr muchii/arce
    // d-->nr depozite
    scanf("%d%d%d", &n, &m, &d);

    int i, j, u, v;
    float w;

    float **mat = malloc(sizeof(float *) * n);
    for (int i = 0; i < n; i++)
        mat[i] = calloc(n, sizeof(float));

    for (i = 0; i < m; i++)
    {
        scanf("%d%d%f", &u, &v, &w);
        mat[u][v] = w;
    }

    // citire depozite
    for (i = 0; i < d; i++)
        scanf("%d", &depozit[i]);

    int nr_cerinte, count;
    scanf("%d", &nr_cerinte);

    char cerinta[3];
    for (count = 0; count < nr_cerinte; count++)
    {
        scanf("%s", cerinta);
        ////TASK 1////
        if (strcmp(cerinta, "e1") == 0)
        {
            float s = 0;

            int dep, nr_magazine, magazin, contor;
            scanf("%d", &dep);
            scanf("%d", &nr_magazine);

            for (contor = 0; contor < nr_magazine; contor++)
            {
                scanf("%d", &magazin);
                printf("%d\n", magazin);
                // afisare distanta
                dijkstra(mat, n, dep, magazin, 0, &s, "dus");
                dijkstra(mat, n, magazin, dep, 0, &s, "intors");
                printf("\n");
                printf("%d ", dep);
                // afisare cale
                dijkstra(mat, n, dep, magazin, 1, &s, "dus");
                dijkstra(mat, n, magazin, dep, 1, &s, "intors");
                printf("\n");
            }

            printf("%.1f", s);
        }
        ////TASK 2////
        if (strcmp(cerinta, "e2") == 0)
        {
            // scoatere depozite
            for (i = 0; i < d; i++)
            {
                for (j = 0; j < n; j++)
                {
                    mat[j][depozit[i]] = 0;
                    mat[depozit[i]][j] = 0;
                }
            }
            int componente[30]; // fiecare nod va contine nr-ul componentei din care face parte
            int nr_componente = 0;

            plus_minus(mat, n, componente, &nr_componente, d, depozit);

            int indice_comp = 1;
            printf("%d\n", nr_componente);

            while (indice_comp <= nr_componente)
            {
                // calculez numarul de noduri ale unei componente
                int nr_pe_indice = 0;
                for (i = 0; i < n; i++)
                    if (componente[i] == indice_comp)
                        nr_pe_indice++;

                for (i = 0; i < n; i++)
                {
                    if (componente[i] == indice_comp)
                    {
                        printf("%d", i);
                        nr_pe_indice--;
                        if (nr_pe_indice > 0) // afisare corespunzatoare a spatiilor
                            printf(" ");
                    }
                }
                if (indice_comp < nr_componente)
                    printf("\n");
                indice_comp++;
            }
        }
        ////TASK 3////
        if (strcmp(cerinta, "e3") == 0)
        {
            float **mat_nou = malloc(sizeof(float *) * n);
            for (int i = 0; i < n; i++)
                mat_nou[i] = calloc(n, sizeof(float));

            float sume_finale[30];
            int k, nr_zone, zone[30];
            scanf("%d", &nr_zone);

            int x, y, id;
            for (i = 0; i < nr_zone; i++)
                sume_finale[i] = INF;

            for (i = 0; i < nr_zone; i++)
            {
                scanf("%d", &k);
                for (j = 0; j < k; j++)
                    scanf("%d", &zone[j]);
                
                for (x = 0; x < n; x++)
                    for (y = 0; y < n; y++)
                        mat_nou[x][y] = 0;

                // transfer intr-o matrice noua doar nodurile vizate din ruta
                for (j = 0; j < k; j++)
                {
                    for (x = 0; x < n; x++)
                    {
                        for (y = 0; y < n; y++)
                            if ((x == zone[j]) || (y == zone[j]))
                                mat_nou[x][y] = mat[x][y];
                    }
                }
                
                int indice;
                for (id = 0; id < d; id++)
                {
                    for (j = 0; j < n; j++)
                        visi[j] = 0;
                    cost = 0;
                    cost_minim(mat_nou, n, depozit[id], depozit[id], &indice);
                    //printf("%d", indice);
                    if(mat_nou[indice][depozit[id]] == 0)
                        dijkstra_task3(mat_nou, n, indice, depozit[id], &cost);
                
                    if (cost < sume_finale[i])
                        sume_finale[i] = cost;
                }
            }
            for (i = 0; i < nr_zone - 1; i++)
                printf("%.1f\n", sume_finale[i]);
            printf("%.1f", sume_finale[nr_zone - 1]);

            for (i = 0; i < n; i++)
                free(mat_nou[i]);
            free(mat_nou);
        }

        if (count < nr_cerinte - 1)
            printf("\n");
    }
    // printare_mat(mat, n);
    for (i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
    return 0;
}
