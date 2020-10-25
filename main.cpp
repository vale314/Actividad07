#include<iostream>
 
#include <map>
 
#define n 5

using namespace std;

 
int compltedPhilo = 0,i;
 
struct fork{
	int taken;
}ForkAvil[n];
 
struct philosp{
	int left;
	int right;
	int comido;
}Philostatus[n];
 

map<int,int> mymap;

void goForDinner(int philID){ 
    
    if(Philostatus[philID].comido==6){
            return;
    }
        
	if(Philostatus[philID].left==10 && Philostatus[philID].right==10){
	    Philostatus[philID].comido++;
        cout<<"Philosopher "<<philID+1<<" Ya Ha Comido" << Philostatus[philID].comido << "\n";
	//if already completed dinner
	}else if(Philostatus[philID].left==1 && Philostatus[philID].right==1 ){
	    	Philostatus[philID].comido++;

            //if just taken two forks
            cout<<"Philosopher "<<philID+1<<" Ya Ha Comido" << Philostatus[philID].comido << "\n";
 
            Philostatus[philID].left = Philostatus[philID].right = 10; //remembering that he completed dinner by assigning value 10
            int otherFork = philID-1;
 
            if(otherFork== -1)
                otherFork=(n-1);
 
            ForkAvil[philID].taken = ForkAvil[otherFork].taken = 0; //releasing forks
            cout<<"Philosopher "<<philID+1<<" Liberado Tenedor "<<philID+1<<" Y Tenedor "<<otherFork+1<<"\n";
            
        }
        else if(Philostatus[philID].left==1 && Philostatus[philID].right==0){ //left already taken, trying for right fork
                if(philID==(n-1)){
                    if(ForkAvil[philID].taken==0){ //KEY POINT OF THIS PROBLEM, THAT LAST PHILOSOPHER TRYING IN reverse DIRECTION
                        ForkAvil[philID].taken = Philostatus[philID].right = 1;
                        cout<<"Tenedor "<<philID+1<<" Tomado Por philosopher "<<philID+1<<"\n";
                    }else{
                        cout<<"Philosopher "<<philID+1<<" Esta Esperando Tenedor "<<philID+1<<"\n";
                    }
                }else{ //except last philosopher case
                    int dupphilID = philID;
                    philID-=1;
 
                    if(philID== -1)
                        philID=(n-1);
 
                    if(ForkAvil[philID].taken == 0){
                        ForkAvil[philID].taken = Philostatus[dupphilID].right = 1;
                        cout<<"Tenedor "<<philID+1<<" Tomado Por Philosopher "<<dupphilID+1<<"\n";
                    }else{
                        cout<<"Philosopher "<<dupphilID+1<<" Esta Esperando Tenedor "<<philID+1<<"\n";
                    }
                }
            }
            else if(Philostatus[philID].left==0){ //nothing taken yet
                    if(philID==(n-1)){
                        if(ForkAvil[philID-1].taken==0){ //KEY POINT OF THIS PROBLEM, THAT LAST PHILOSOPHER TRYING IN reverse DIRECTION
                            ForkAvil[philID-1].taken = Philostatus[philID].left = 1;
                            cout<<"Tenedor "<<philID<<" Tomado Por philosopher "<<philID+1<<"\n";
                        }else{
                            cout<<"Philosopher "<<philID+1<<" Esta Esperando Tenedor  "<<philID<<"\n";
                        }
                    }else{ //except last philosopher case
                        if(ForkAvil[philID].taken == 0){
                            ForkAvil[philID].taken = Philostatus[philID].left = 1;
                            cout<<"Tenedor "<<philID+1<<" Tomado Por Philosopher "<<philID+1<<"\n";
                        }else{
                            cout<<"Philosopher "<<philID+1<<" Esta Esperando Por Tenedor "<<philID+1<<"\n";
                        }
                    }
        }else{}
}

void comer (){
    
		    for(i=0;i<n;i++){
                goForDinner(i);
    		}
    		
    		for(i=0;i<n;i++){
                if(Philostatus[i].comido == 6){
                    mymap[i]=1;
                    cout<<"Sr. Filosofo " << i << " Ya se Ha Comido sus 6" << endl;
                }
            }

		cout<<"\nEste Es El Numero De Filisofos Que Ya Comieron:  "<<mymap.size()<<"\n\n";
	}

 
int main(){
    for(i=0;i<n;i++)
        ForkAvil[i].taken=Philostatus[i].comido=Philostatus[i].left=Philostatus[i].right=0;
	
	do {
	    comer();
	}while(mymap.size()<5);


	return 0;
}
