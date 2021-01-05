#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <string.h>
#include<locale.h>

typedef struct linkedList
{
    char nodeKelime[50];
    int nodeKelimeSayi;
    struct linkedList *nextNode;
} linkedList;
void arayaNodeEkle(linkedList**headNode,char nodeKelime[],int nodeKelimeSayi,int eklemeKonum)
{
    linkedList *newNode=(linkedList*)malloc(sizeof (linkedList));
    newNode->nodeKelimeSayi=nodeKelimeSayi;
    strcpy(newNode->nodeKelime,nodeKelime);

    if(*headNode==NULL)
    {
        newNode->nextNode=NULL;
        *headNode = newNode;
        return;
    }
    else
    {
        linkedList *findNode = *headNode;
        int counter=1;
        while (counter != eklemeKonum)
        {
            findNode = findNode->nextNode;
            counter++;
        }
        linkedList *tempNode2;
        tempNode2=findNode->nextNode;
        findNode->nextNode=newNode;
        newNode->nextNode=tempNode2;
    }
}
void basaNodeEkle(linkedList**headNode,char nodeKelime[],int nodeKelimeSayi)
{

    linkedList *newNode=(linkedList*)malloc(sizeof (linkedList));
    newNode->nodeKelimeSayi=nodeKelimeSayi;
    strcpy(newNode->nodeKelime,nodeKelime);

    if(*headNode==NULL)
    {
        newNode->nextNode=NULL;
        *headNode = newNode;
        return;
    }
    else
    {
        newNode->nextNode=(*headNode);
        (*headNode)=newNode;
    }
}
void sonaNodeEkle(linkedList**headNode,char nodeKelime[],int nodeKelimeSayi)
{
    linkedList *newNode=(linkedList*)malloc(sizeof (linkedList));
    newNode->nodeKelimeSayi=nodeKelimeSayi;
    strcpy(newNode->nodeKelime,nodeKelime);
    newNode->nextNode=NULL;

    if(*headNode==NULL)
    {
        newNode->nextNode=NULL;
        *headNode = newNode;
        return;
    }
    else
    {
        linkedList *lastNode = *headNode;
        while (lastNode->nextNode != NULL)
        {
            lastNode = lastNode->nextNode;
        }
        lastNode->nextNode = newNode;
    }
}

int listedeVarMi(linkedList*headNode,char nodeKelime[])
{
    while (headNode != NULL)
    {
        if( strcmp(headNode->nodeKelime,nodeKelime)==0 )
            return 1;
        else
            headNode = headNode->nextNode;
    }
    return -1;
}
int siraBul(linkedList*headNode,int nodeKelimeSayi)
{
    int sira=0;
    while (headNode != NULL)
    {
        if( nodeKelimeSayi > headNode->nodeKelimeSayi )
        {
            return sira;
        }
        else
        {
            headNode = headNode->nextNode;
            sira++;
        }

    }
    return sira;
}
int dugumSayisi(linkedList*headNode)
{
    int sira=0;
    while (headNode != NULL)
    {
        headNode = headNode->nextNode;
        sira++;
    }
    return sira;
}

int nodeKelimeSayiBul(char*dosyaYolu,char *kelime)
{
    int nodeKelimeSayi =0;
    char metindeBak[30];

    FILE *dosya = fopen(dosyaYolu, "r");
    while ( fscanf(dosya,"%s", metindeBak)!=-1)
    {
        if(strcmp(metindeBak, kelime)==0)
            nodeKelimeSayi++;
    }
    fclose(dosya);
    return nodeKelimeSayi;
}
void okuKelime (FILE *f,linkedList**headNode)
{
    char kelime[1024];
    while (fscanf(f, " %1023s", kelime) == 1)
    {
        switch( listedeVarMi(*headNode,kelime) )
        {
        case 1:
            break;
        case -1:
        {
            int kelimeAdetSayisi=nodeKelimeSayiBul("metin.txt",kelime);
            if(*headNode==NULL)
                basaNodeEkle(headNode,kelime,kelimeAdetSayisi);

            else
            {
                //printf("adet : %d\n",kelimeAdetSayisi);
                int sira=siraBul(*headNode,kelimeAdetSayisi);
                //printf("%d\n",sira);
                if(sira==0)
                    basaNodeEkle(headNode,kelime,kelimeAdetSayisi);
                else if(sira==dugumSayisi(*headNode))
                    sonaNodeEkle(headNode,kelime,kelimeAdetSayisi);
                else
                    arayaNodeEkle(headNode,kelime,kelimeAdetSayisi,sira);
               // listeBastir(*headNode);
            }
            break;
        }
        }
    }
}
void listeBastir(linkedList *node)
{
    int sira=0;
    while (node != NULL)
    {
        printf("%d -> %s:%d\n",sira,node->nodeKelime,node->nodeKelimeSayi);
        node = node->nextNode;
        sira=sira+1;
    }
    printf("***********\n");
}
int main()
{
    setlocale(LC_ALL ,"Turkish" );
    linkedList *head = NULL;
    FILE * dosya = fopen("metin.txt", "r");
    okuKelime(dosya,&head);
    listeBastir(head);
    fclose(dosya);
    return 0;
}
