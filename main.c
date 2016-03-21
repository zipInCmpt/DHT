//
//  main.c
//  DHT
//
//  Created by Ziyue Lu on 15/10/25.
//  Name: Ziyue Lu
//  ID: 301295780
//  language: C

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *in,*out;
int succTable[10][3];

int FindSucc(int key, int* Node, int nodeNumber){
    int i;
    
    while(key>=8){
        key=key-8;
    }
    
    for(i=0;i<nodeNumber;i++){
        if(Node[i]==key)
            return Node[i];
        if(Node[i]>key)
            return Node[i];
    }
    
    return Node[0];
}

int PathLength(int key,int NodeID, int *Node, int nodeNumber){
    int count;
    int Des;
    int j;
    
    count=0;
    Des=FindSucc(key, Node, nodeNumber);
    
    while(1){
        if(NodeID==Des)
            return count;
        count++;
        for(j=0;j<3;j++){
            if(succTable[NodeID][j]==Des){
                NodeID=Des;
                break;
            }
            if(succTable[NodeID][j]>key){
                NodeID=succTable[NodeID][j-1];
                break;
            }
        }
        if(j==3){
            NodeID=succTable[NodeID][2];
        }
    }
}

int main(int argc, const char * argv[]) {
    
    int hashSpace;
    int nodeNumber;
    int keyNumber;
    char nodeids[10];
    char keys[10];
    int Node[10];
    int Key[10];
    char Query[5];
    int queryKey;
    int queryNode;
    
    
    int i,j,min,t;
    int Length;
    
    in=fopen("DHT.in","r");
    out = fopen("DHTout.out","w+");
    
    if(in==NULL){
        printf("Open Failure!");
        exit(1);
    }
    else{
        fscanf(in,"%d",&hashSpace);
        fscanf(in,"%d",&nodeNumber);
        fscanf(in,"%d",&keyNumber);
        fscanf(in,"%s",nodeids);
        fscanf(in,"%s",keys);
        
        //Depart Node
        j=0;
        for(i=0;nodeids[i]!=0;i++){
            if(nodeids[i]<='9' && nodeids[i]>='0'){
                Node[j]=nodeids[i]-'0';
                j++;
            }
            else if(nodeids[i]==',') continue;
        }
        
        //Sort Node
        for(i=0;i<nodeNumber-1;i++)
        {
            min=i;
            for(j=i+1;j<nodeNumber;j++)
                if(Node[min]>Node[j])
                    min=j;
            if(min!=i)
            {
                t=Node[min];
                Node[min]=Node[i];
                Node[i]=t;
            }
        }
        
        //Make SuccTable
        for(i=0;i<nodeNumber;i++){
            for(j=0;j<3;j++){
                succTable[Node[i]][j]=FindSucc(Node[i]+pow(2,j), Node, nodeNumber);
            }
        }
        
        //Depart Key
        j=0;
        for(i=0;keys[i]!='0';i++){
            if(keys[i]<='9' && keys[i]>='0'){
                Key[j]=keys[i]-'0';
                j++;
            }
            else if(keys[i]==',') continue;
        }
        
        fscanf(in,"%s",Query);
        while(Query[0]!='-'){
            queryKey=Query[0]-'0';
            queryNode=Query[2]-'0';
            
            Length=PathLength(queryKey, queryNode, Node, nodeNumber);
            printf("%d\n",Length);
            fprintf(out,"%d\n",Length);
            fscanf(in,"%s",Query);
        }
        
    }
    fclose(in);
    fclose(out);
    return 0;
}
