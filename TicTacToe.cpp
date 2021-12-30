#include<iostream>
#include<cmath>

using namespace std;

int box[9],box1[9],pos[9],table[9][9],pos1[9],empty=0, game_state=0,mat[3][3],pos_ch[9],play=0;

void input(){
    int position,stat=0;
    while(stat==0){
        cout<<"\nEnter the position of your choice(Player 1):";
        cin>>position;
        if(position>=0 && position<9){
            if(pos_ch[position]==0){
                pos_ch[position]=1;
                //pos1[position]=1;
                box[position]=1;
                box1[position]=1;
                stat=1;
            }    
            else{
                cout<<"\nPosition Already Filled!! Try Again";
            }
        }
        else{
            cout<<"Please enter right Position. Position(0-8)";
        }    
    }
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
        for(i=0;i<empty;i++){
            stat=checkWinner(table[i]);
            if(stat==2){      
                for(j=0;j<9;j++){
                    box[j]=table[i][j];
                    box1[j]=table[i][j];}
                output();
                cout<<"\n\n\t\t\tWINNER IS AI!!";
                game_state=1;
                play=1;
                return;
            }
            else{
                game_state=0;
                //cout<<"\n No Winner :(";
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
    
   
    return b_state;
    
}

int evaluateBlockState(){
    int i,j;
    for(i=0;i<empty;i++){
        if(checkBlockState(table[i], pos[i])==1){
            pos_ch[pos[i]]=1;
            for(j=0;j<9;j++){
                box[j]=table[i][j];
                box1[j]=table[i][j];
            }
            //cout<<"\nbad";
            output();
            return 2;
        }
    }
   // cout<<"\nbad";
    return 3;
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
    
    //Looking for blocking move in future
    //If no winning move possible
    sum=mat[x][0]+mat[x][1]+mat[x][2];
    sum1=mat[0][y]+mat[1][y]+mat[2][y];
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
    
    //cout<<"\nScore:"<<score<<endl;
    return score;
    
}

void evaluateNeutralState(){
    int i,j,points=0,max=0,a=0,n=0;
    for(i=0;i<empty;i++){
        points=scoreForNeutral(table[i],pos[i]);
        //cout<<"\nPoints:"<<points<<endl;
        if(points>max){
            max=points;
            a=i;
            n=pos[i];
            //cout<<"\nMax Points:"<<max<<endl;
        }
    }
    
    for(j=0;j<9;j++){
        pos_ch[n]=1;
        box[j]=table[a][j];
        box1[j]=table[a][j];}
    output();
}


void nodeEvaluator(){
    evaluateWinner();
    int blockType=0,i;
    //cout<<game_state;
    if(game_state==1){
        play=1;
        
    }
    else{
        blockType=evaluateBlockState();
        if(blockType==3){
            evaluateNeutralState();
        }
        cout<<"\n\t\t\tPlayer 1 Turn";
    }
    
    for(i=0;i<9;i++){
        if(box[i]==0){
            pos1[i]=0;
        }
        else{
            pos1[i]=1;
        }
    }
    
}

void possibleMoveGenerator(){
    int i,j,a=0,status=0;
   for(i=0;i<empty;i++){
        for(j=0;j<9;j++){
            if(pos1[j]==0 && status==0){
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
    //cout<<"\nEmpty:"<<empty;
    cout<<"\nPossible Moves:\n";
    for(i=0;i<empty;i++){
        cout<<i+1<<" :";
        for(j=0;j<9;j++){
            cout<<table[i][j]<<" ";
        }
        cout<<endl;
    }
}

void statusGenerator(){
    int i=0,a=0;
    empty=0;
    for(i=0;i<9;i++){
        if(box1[i]==0){
            empty++;
            pos[a++]=i;
        }
        else{
            pos1[i]=1;
        }
    }
    
    //cout<<"\nPosition Status:";
    for(i=0;i<9;i++){
        cout<<pos1[i];
    }
    
    possibleMoveGenerator();    
}

int main(){
    
    int i=0,j ,player=0 ,a=0, power[9];
    for(i=0;i<9;i++){
        for(int j=0;j<=9;j++){
            table[i][j]=0;
        } 
    }
    
    for (i=0;i<9;i++){
        box[i]=0;
        pos[i]=0;
        pos1[i]=0;
        pos_ch[i]=0;
    }
    
    
    
    while(a <9 && play!=1){
       // for(i=0;i<9;i++)
         //   cout<<" pos_ch "<<i<<":"<<pos_ch[i];
        //cout<<endl;
        //system("clear");
        
        cout<<"\n\t\t###### TIC-TAC-TOE ######\n\n";
        output();
        if(a%2==0){
            input();
            
        }
        else{
            cout<<"\t\t\tAI turn\n";
            statusGenerator();
            nodeEvaluator();
            for(i=0;i<9;i++){
                for(j=0;j<9;j++){
                    table[i][j]=0;
                }
            }
            //cout<<"Box1:";
        }
        a+=1;
    }
    
    output();
    if(play!=1){
        cout<<"\n\n\t\t\tNO WINNER! TIE!!";
    }
    cout<<"\n\n\t\tGAME OVER!!";
    return 0;

}




