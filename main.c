#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_element 20
void Split_Data(int graph[max_element][max_element],char buff[255],char delimiter[2],int* size){
    char *token;
    int tmp1, tmp2, element;
    token=strtok(buff,delimiter);
    element=atoi(token);
    token=strtok(NULL,delimiter);
    tmp1=atoi(token);
    if (tmp1 > *size) {
        *size = tmp1;
    }
    token=strtok(NULL,delimiter);
    tmp2=atoi(token);
    if (tmp2 > *size) {
        *size = tmp2;
    }
    graph[tmp1-1][tmp2-1]=element;
    graph[tmp2-1][tmp1-1]=element;
}
void File_Read(int graph[max_element][max_element],char File_Name[20],int* counter,int* size){
    FILE *fp=fopen(File_Name,"r");
    char delimiter[2] = " ";
    char buf[255];
    if(fgets(buf,255,fp)!=NULL){
        printf("%s",buf);
        Split_Data(graph,buf,delimiter,size);
        *counter = *counter +1;
    }
    while(fgets(buf,255,fp)!=NULL){
        printf("%s",buf);
        Split_Data(graph,buf,delimiter,size);
        *counter = *counter +1;
    }
    fclose(fp);
}
int Find_Path(int graph[max_element][max_element],int size,int place1,int place2,int cost,int* k,int prev_loc,int *counter,int path[max_element]){
    int i = 0;
    int tmp = cost;
    if (place1 != place2) {
        while (i<size && *k == 0) {
            if (graph[place1][i]>0 && i != prev_loc) {
                path[*counter]=i+1;
                *counter = *counter + 1;
                cost = Find_Path(graph, size, i, place2, cost+graph[place1][i], k, place1, counter,path);
                if (*k == 0) {
                    cost = tmp;
                    *counter = *counter - 1;
                }
            }
            i++;
        }
    }else{
        *k = 1;
    }
    return cost;
}
void Constract(int graph[max_element][max_element],int place1,int place2,int* counter,int path[max_element],int distance){
    int peak = distance;
    int i, j;
    j = -1;
    for (i=0; i< *counter -1; i++) {
        if (graph[path[i]-1][path[i+1]-1] > peak) {
            peak = graph[path[i]-1][path[i+1]-1];
            j=i;
        }
    }
    if (j != -1) {
        graph[place1-1][place2-1] = distance;
        graph[place2-1][place1-1] = distance;
        graph[path[j]-1][path[j+1]-1] = -1;
        graph[path[j+1]-1][path[j]-1] = -1;
        printf("\nMST guncellenmistir.");
    }else{
        printf("\nMST'nin yeniden olusturulmasina gerek yoktur.");
    }
}
void Add_Element(int graph[max_element][max_element],int* size){
    int place1, place2,cost,unique;
    int distance, counter, i;
    int path[max_element];
    printf("Eklemek istediginiz baglantinin hangi dugumler arasinda oldugunu giriniz.\n");
    printf("Birinci dugum: ");
    scanf(" %d", &place1);
    printf("Ikinci dugum: ");
    scanf(" %d", &place2);
    if (graph[place1-1][place2-1] < 0) {
        printf("\nEklemek istediginiz baglantinin degerini giriniz.");
        printf("\nUzaklik: ");
        scanf(" %d", &distance);
        unique = 0;
        counter = 1;
        path[0]=place1;
        cost = Find_Path(graph, *size, place1-1, place2-1, 0,&unique,-1,&counter,path);
        for (i=0; i<counter; i++) {
            printf("\n%d ", path[i]);
        }
        printf("\nprevious cost: %d", cost);
        if (cost <= distance) {
            printf("\nMST'nin yeniden olusturulmasina gerek yoktur.");
        }else{
            Constract(graph, place1, place2, &counter, path, distance);
        }
    }else{
        printf("\nGirdiginiz iki dugum zaten bagli!");
    }
    
}
void Print_Graph(int graph[max_element][max_element], int size){
    int i, j;
    printf("\n\n");
    for (i=0; i<size; i++) {
        printf("|");
        for (j=0; j<size; j++) {
            printf("%4d | ", graph[i][j]);
        }
        printf("\n");
    }
}
int main(int argc, const char * argv[]) {
    int graph[max_element][max_element];
    int i,j;
    int counter = 0;
    int size = 0;
    int chs = 0;
    char File_Name[20];
    for (i=0; i<max_element; i++) {
        for (j=0; j<max_element; j++) {
            graph[i][j] = -1;
            if (i == j) {
                graph[i][j] = 0;
            }
        }
    }
    printf("Lutfen bir dosya ismi giriniz.\n");
    scanf(" %s", File_Name);
    File_Read(graph, File_Name, &counter, &size);
    Print_Graph(graph, size);
    while (chs != 3) {
        printf("\nYapmak istediginiz islemi giriniz.\nBaglanti ekleme-(1)\n");
        printf("MST'yi goruntuleme-(2)\nCikis-(3)\n");
        scanf(" %d", &chs);
        if (chs == 1) {
            Add_Element(graph, &size);
        }else if (chs == 2){
            Print_Graph(graph, size);
        }else if (chs != 3){
            printf("Yanlis bir secim yaptiniz. Lutfen tekrar deneyiniz.\n\n");
        }
    }
    return 0;
}
