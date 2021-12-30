#include<iostream>
#include<cmath>

using namespace std;
/*
struct node{
    int boardPos[9];
    int score=0;
    struct node *father;
    struct node* next;
    struct node* child;
    int gval; 
}*head=NULL, *temp=NULL;

void createNode(struct node *dad,int score, int tab[],int isChild){
    temp=new node();
    temp->score=score;
    for(int i=0;i<9;i++)
        temp->boardPos[i]=tab[i];
    temp->father=dad;
    //temp->child=NULL;
    if(head=NULL){
        head=temp;
    }
    else{
        temp->next=head;
        head=temp;
    }

}
*/

int box[10],box1[9],pos[9],table[9][10],pos1[9],Empty=0, game_state=0,mat[3][3],pos_ch[9],play=0;
int lev1[16][10],lev2[16][10],level=0;



void input(){
    int position,stat=0;
    
    while(stat!=1){
        cout<<"\nEnter the board Position(state):";
        stat=0;
        for(int i=0;i<9;i++){
            cin>>box[i];
            box1[i]=box[i];                
        }

        for(int i=0;i<9;i++){
            if(box[i]!=0)
                if(box[i]!=4)
                if(box[i]!=1){
                    stat=2;
                    break;
                }
        }

        if(stat==0){
            stat=1;
        }
        else if(stat==2)
        {
            cout<<"\nBoard Position is wrong.\n";
        }
         
    }
    cout<<"***";
}

void output(){
    cout<<"\n\n\t\t\tX-O board\n";
    int j=0;char ch;
    for(j;j<9;j++){
        if(box[j]==1){
            ch='X';
        }
        else if(box[j]==4){
            ch='Y';
        }
        if(j%3!=0)
            cout<<"|"<<box[j]<<"|";
        else
            cout<<"\n|"<<box[j]<<"|";
    }
}

int checkWinner(int tab[]){
    int i,j,sum=0,W_status=0,sum1=0;
    for(i=0;i<9;i++){
        sum=(tab[i]+tab[i+1]+tab[i+2]);
        if(sum==3 || sum ==12){
            if(sum==3)
                W_status=1;
            else if(sum ==12)
                W_status=2;
            return W_status;
        }
        i+=2;
    }
    for(i=0;i<3;i++){
        sum1=tab[i]+tab[i+3]+tab[i+6];
        if(sum1==3 || sum1 ==12){
            if(sum1==3)
                W_status=1;
            else if(sum1==12)
                W_status=2;
            return W_status;
        }
    }
    sum=tab[0]+tab[4]+tab[8];
    sum1=tab[2]+tab[4]+tab[6];
    if(sum==3 || sum ==12){
        if(sum==3)
            W_status=1;
        else
            W_status=2;
        return W_status;
    }
    else if(sum1==3 || sum1 ==12){
        if(sum1==3)
            W_status=1;
        else
            W_status=2;
        return W_status;
    }
    
    return W_status;
    
}

void evaluateWinner(){
    int stat=0,i=0,j;
    stat=checkWinner(box);
    if(stat==1){                    
            cout<<"\n WINNER Player 1!";
            game_state=1;
    }
    else{
        if(stat==2){
            play=1;
        }
        else{
            for(i=0;i<Empty;i++){
                stat=checkWinner(table[i]);
                if(stat==1){
                    cout<<"\nInside!\n";
                    if(level==2){
                        if(table[i][9]!=0){
                            cout<<"\nFault: "<<i<<endl;
                        }
                            
                        table[i][9]=-60;
                    }
                        
                }
                else if(stat==2){       
                    for(j=0;j<9;j++){
                        box[j]=table[i][j];
                        box1[j]=table[i][j];
                    }
                    //output();
                    //if(level==0)
                    table[i][9]=60;
                    //score=50;
                    //cout<<"\n\n\t\t\tWINNER IS AI!!";
                    //game_state=1;
                    play=1;
                    //return;
                }
                stat=0;
            }
        }
        
    }
    
}

int checkBlockState(int tab[], int change_pos){
    int score=0,a=0,x=0,y=0;
    int i,j,sum=0,b_state=0,sum1=0;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            mat[i][j]=tab[a++];
        }
    }
    y=change_pos%3;
    x=change_pos/3;
    sum=mat[x][0]+mat[x][1]+mat[x][2];
    sum1=mat[0][y]+mat[1][y]+mat[2][y];
    
    //Looking for winning move (in future)
    if(level==0){
        if(sum==6 || sum1==6){
            b_state=1;
            return b_state;
        }
        if((x==0 || x==2) && (y==0 || y==2)){
            sum=mat[x][y]+mat[1][1]+mat[2-x][2-y];
            if(sum==6){
                b_state=1;
                return b_state;
            }
        }
        if(x==1 && y==1){
            sum=mat[0][0]+mat[1][1]+mat[2][2];
            sum1=mat[0][2]+mat[1][1]+mat[2][0];
            if(sum==6){
                b_state=1;
                return b_state;
            }
            if(sum1==6){
                b_state=1;
                return b_state;
            }
        }

    }
    else if(level==2){
        if(sum==9 || sum1==9){
            b_state=2;
            return b_state;
        }
        if((x==0 || x==2) && (y==0 || y==2)){
            sum=mat[x][y]+mat[1][1]+mat[2-x][2-y];
            if(sum==9){
                b_state=2;
                return b_state;
            }
        }
        if(x==1 && y==1){
            sum=mat[0][0]+mat[1][1]+mat[2][2];
            sum1=mat[0][2]+mat[1][1]+mat[2][0];
            if(sum==9){
                b_state=2;
                return b_state;
            }
            if(sum1==9){
                b_state=2;
                return b_state;
            }
        }

    }
        
    return b_state;
    
}

void evaluateBlockState(){
    int i,j;
    for(i=0;i<Empty;i++){
        
        if(checkBlockState(table[i], pos[i])==1 && level==0){
            pos_ch[pos[i]]=1;
            
            table[i][9]+=30;
           
        }
        else if(checkBlockState(table[i], pos[i])==2 && level==2){
            pos_ch[pos[i]]=1;
            
            table[i][9]-=30;
           
        }
    }
}

int scoreForNeutral(int tab[], int change_pos){
    int score=0,a=0,x=0,y=0;
    int i,j,sum=0,B_status=0,sum1=0;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            mat[i][j]=tab[a++];
        }
    }
    y=change_pos%3;
    x=change_pos/3;
    sum=mat[x][0]+mat[x][1]+mat[x][2];
    sum1=mat[0][y]+mat[1][y]+mat[2][y];
    
    //Looking for winning move (in future)
    /*
    if(sum>6){
        score+=20;
    }
    else if(sum1>6)
        score+=20;
    if((x==0 || x==2) && (y==0 || y==2)){
        sum=mat[x][y]+mat[1][1]+mat[2-x][2-y];
        if(sum>6)
            score+=20;
    }
    if(x==1 && y==1){
        sum=mat[0][0]+mat[1][1]+mat[2][2];
        sum1=mat[0][2]+mat[1][1]+mat[2][0];
        if(sum>6)
            score+=20;
        if(sum1>6)
            score+=20;
    }
    */
    //Looking for blocking move in future
    //If no winning move possible
    sum=mat[x][0]+mat[x][1]+mat[x][2];
    sum1=mat[0][y]+mat[1][y]+mat[2][y];
    if(level==0){
        if(sum<6 && sum!=0){
            score+=1;
        }
        if(sum1<6 && sum1!=0)
            score+=1;
        if((x==0 || x==2) && (y==0 || y==2)){
            sum=mat[x][y]+mat[1][1]+mat[2-x][2-y];
            if(sum<6 && sum!=0)
                score+=1;
        }
        if(x==1 && y==1){
            sum=mat[0][0]+mat[1][1]+mat[2][2];
            sum1=mat[0][2]+mat[1][1]+mat[2][0];
            if(sum<6 && sum!=0)
                score+=1;
            if(sum1<6 && sum1!=0)
                score+=1;
        }
    }
    else if(level==2){
        if(sum<7 && sum!=0){
            score-=1;
        }
        if(sum1<7 && sum1!=0)
            score-=1;
        if((x==0 || x==2) && (y==0 || y==2)){
            sum=mat[x][y]+mat[1][1]+mat[2-x][2-y];
            if(sum<7 && sum!=0)
                score-=1;
        }
        if(x==1 && y==1){
            sum=mat[0][0]+mat[1][1]+mat[2][2];
            sum1=mat[0][2]+mat[1][1]+mat[2][0];
            if(sum<7 && sum!=0)
                score-=1;
            if(sum1<7 && sum1!=0)
                score-=1;
        }
    }
    
    //cout<<"\nScore:"<<score<<endl;
    return score;
    
}

void evaluateNeutralState(){
    int i,j,points=0,max=0,a=0,n=0;
    for(i=0;i<Empty;i++){
        //if(table[i][9]>-60)
        points=scoreForNeutral(table[i],pos[i]);
        //cout<<"\nPoints:"<<points<<endl;
        //if(level==2)
            table[i][9]+=points;    
        // else
        //     table[i][9]+=points;
        //createNode(NULL,0,box,0);
        //cout<<"check1:"<<table[i][9];
        //createNode();
        points=0;
    }
    
    
}


void nodeEvaluator(){
    //int score=0;
    evaluateWinner();
    //
    int blockType=0,i;
    //cout<<game_state;
    if(play==1){
        //cout<<"AI Winner";
        //return;   
        //break; 
    }
    else{
            //createNode(NULL,0,box,0);
            evaluateBlockState();
            //if(blockType==3){
                //cout<<"IUJABj";
            evaluateNeutralState();
            //}
            //cout<<"\n\t\t\tPlayer 1 Turn";
    }
    
    
}

void possibleMoveGenerator(){
    int i,j,a=0,status=0;
    for(i=0;i<Empty;i++){
        for(j=0;j<9;j++){
            if(pos1[j]==0 && status==0){
                if(level==2){
                    box1[j]=1;
                }
                else
                    box1[j]=4;
                pos1[j]=1;
                status=1;
                table[a][j]=box1[j];
                box1[j]=0;
            }
            else
                table[a][j]=box1[j];
        }
        status=0;
        a+=1;
        
    }
    //cout<<"\nEmpty:"<<Empty;
    if(level==0){
        cout<<"\nPossible Moves:";
        cout<<"\nLevel [1]\n";
        for(i=0;i<Empty;i++){
            cout<<i+1<<" :";
            for(j=0;j<9;j++){
                cout<<table[i][j]<<" ";
            }
            cout<<endl;
        }
    }
}

void statusGenerator(){
    int i=0,a=0;
    Empty=0;
    for(i=0;i<9;i++){
        if(box[i]==0){
            Empty++;
            pos[a++]=i;
        }
        else{
            pos1[i]=1;
        }
    }
    
    // cout<<"\nPosition Status:";
    // for(i=0;i<9;i++){
    //     cout<<pos1[i];
    // }
    
    possibleMoveGenerator();    
}

void resetTable(){
    int i,j;
     for(i=0;i<9;i++){
        for(int j=0;j<10;j++){
            table[i][j]=0;
            if(j!=9){
                pos1[i]=0;
            }
        } 
    }
}
void resetPosition(){
    int i,j;
     for(i=0;i<9;i++){
        pos1[i]=0;
    }
}


void level1Output(){
    int i=0,j=0;
    //lev1[i][0]!='\0'
    cout<<"\n\nLevel1:\n";
    for(i=0;i<Empty+1;i++){
        for(j=0;j<10;j++){
            if(j==9){
                cout<<" | Score:"<<lev1[i][j];
            }
            else
            cout<<lev1[i][j]<<" ";
        }
        cout<<endl;
    }
}

void level2Output(){
    int i=0,j=0;
    //lev1[i][0]!='\0'
    cout<<"\n\nLevel2:\n";
    for(i=0;i<Empty*(Empty+1);i++){
        for(j=0;j<10;j++){
            if(j==9){
                cout<<" | Score:"<<lev2[i][j];
            }
            else
            cout<<lev2[i][j]<<" ";
        }
        cout<<endl;
    }
}

void MinMax(){  //Code to for minimax function
    int min=100,i,j,totalNode,a=0,posi=0;
    totalNode=Empty*(Empty+1);
    for(i=0;i<totalNode;i++){
        for(j=0;j<Empty;j++){
            if(lev2[j+i][9]<min){
                min=lev2[j+i][9];
            }
        }
        a=i/Empty;
        lev1[a][9]=min;
        i-=1;
        i+=Empty;
        min=100;
    }

    int max=-200;
    for(i=0;i<Empty+1;i++){
        if(lev1[i][9]>max){
            max=lev1[i][9];
            posi=i;
        }
    }
    box[9]=max;
    level1Output();
    // cout<<"\nRoot: ";
    // for(i=0;i<10;i++){
    //     cout<<box[i]<<" ";
    // }
    cout<<"\nNext Turn: ";
    for(i=0;i<10;i++){
        if(i==9){
            cout<<" | Score:"<<lev1[posi][i];
        }
        else
        cout<<lev1[posi][i]<<" ";
    }
        
}

int main(){
    
    int i=0,j ,player=0 ,a=0, power[9],end=0;
   int checkend=0,posit=0,big=0;
    for (i=0;i<9;i++){
        box[i]=0;
        pos[i]=0;
        pos1[i]=0;
        pos_ch[i]=0;
    }
    
    cout<<"\n\t\t###### TIC-TAC-TOE ######\n\n";
    output();
    input();      
    evaluateWinner();
    if(play==1){
        cout<<"Player 1 winner";
    }
    else{
        //-------------------Level1
        statusGenerator();
        
        nodeEvaluator();
        // cout<<"\n\nOUTPUT level1:\n";
        // for(i=0;i<Empty;i++){
        //     for(j=0;j<10;j++){
        //         cout<<table[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
        
        for(i=0;i<Empty;i++){
            for(j=0;j<10;j++){
                lev1[i][j]=table[i][j];
            }
        }
        
        for(i=0;i<Empty;i++){
             if(big<lev1[i][9]){
                 big=lev1[i][9];
                 posit=i;
             }        
        }
         if(big>=30){
             end=1;
        }
        //-----------------------------------Level 2
        Empty-=1;int k=0;
        resetTable();
        level=2;
        if(end!=1){
        //for(i=0;i<Empty;i++){
            for(j=0;j<Empty+1;j++){
                for(k=0;k<9;k++){
                    box[k]=lev1[j][k];
                    box1[k]=box[k];
                }
                statusGenerator();
                nodeEvaluator();
                resetPosition();
                
                cout<<"Level [2]["<<j<<"] :\n";
                for(int m=0;m<Empty;m++){
                    cout<<m+1<<" :";
                    for(int n=0;n<10;n++){
                        if(n==9){
                            cout<<" | Score:"<<table[m][n];
                        }
                        else
                        cout<<table[m][n]<<" ";
                    }
                    cout<<endl;
                }
                
                for(int z=0;z<Empty;z++){
                    
                    for(k=0;k<10;k++){
                        //cout<<" ";
                        lev2[z+a][k]=table[z][k];
                    }
                    cout<<endl;
                }
                resetTable();
                a+=Empty;
            }
        }
    
    }  
    if(end!=1){
        level2Output();
        MinMax();
    }
    else{
         
        //  for(i=0;i<10;i++){
        //      cout<<lev1[posit][i]<<" ";
        //  }
       level1Output(); 
       cout<<"\n\nNext Turn: ";
       for(i=0;i<10;i++){
           if(i==9){
                cout<<" | Score:"<<lev1[posit][i];
            }
            else
              cout<<lev1[posit][i]<<" ";
       }
    }
    return 0;

}




