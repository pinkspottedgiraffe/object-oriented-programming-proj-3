#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

enum movement{impressionism,expressionism,naturalism};
enum condition{bad,good,excellent};
enum technique{oil,aquarelle,tempera};
enum material{iron,stone,wood};

class artifacts{
	int index;
	int creator;
	int year;
	public:
		artifacts(int,int,int);
		virtual void getInfo();
		void getIndex();
		virtual ~artifacts();
		virtual int evaluate(movement,condition)=0;
};

class masterpiece:public artifacts{
	protected:
	movement m;
	condition c;
	public:
		masterpiece(movement,condition,int,int,int);
		void getInfo();	
		~masterpiece();		
};

class paintings:public masterpiece{
	int length;
	int width;
	technique t;
	public:
		paintings(movement,condition,int,int,int,int,int,technique);
		void getInfo();
		virtual int evaluate(movement,condition=good);
		~paintings();
		
};

class sculptures:public masterpiece{
	int volume;
	material mater;
	public:
		sculptures(movement,condition,int,int,int,int,material);
		void getInfo();
		virtual int evaluate(movement,condition=excellent);
		~sculptures();
};


void auction(artifacts** ar,movement mov,condition cond,int arsize){		//prints each artifacts information and evaluates it with the given
	for(int i=0;i<arsize;i++){												//movement and condition
		ar[i]->getInfo();
		int k=ar[i]->evaluate(mov,cond);
		if(k==1){
			cout << "the artifact is accepted " << endl;
		}
		else if(k==0){
			cout << "the artifact is rejected " << endl;
		}
	}
}

string getmovement(movement mov){						//functions to print out string not numbers
	switch(mov){
		case impressionism: return "impressionism";
		case expressionism: return "expressionism";
		case naturalism: return "naturalism";
	}
}

string getcondition(condition cond){
	switch(cond){
		case bad: return "bad";
		case good: return "good";
		case excellent: return "excellent";
	}
}

string gettechnique(technique tech){
	switch(tech){
		case oil: return "oil";
		case aquarelle: return "aquarelle";
		case tempera: return "tempera";
	}
}

string getmaterial(material mat){
	switch(mat){
		case iron: return "iron";
		case stone: return "stone";
		case wood: return "wood";
	}
}


int main(int argc,char* argv[]){
	
	int N=atoi(argv[1]);			//number of artifacts
	string value1=argv[2];			//movement value
	string value2=argv[3];			//condition value
	
	movement movvalue;
	condition condvalue;
	
	if(value1=="impressionism"){
		movvalue=impressionism;
	}
	else if(value1=="expressionism"){
		movvalue=expressionism;
	}
	else{
		movvalue=naturalism;
	}
	string temp=getmovement(movvalue);
	cout << "the movement value is " << temp << endl;
	
	if(value2=="bad"){
		condvalue=bad;
	}
	else if(value2=="good"){
		condvalue=good;
	}
	else{
		condvalue=excellent;
	}
	
	string temp2=getcondition(condvalue);
	cout << "the value of the condition is " << temp2 << endl;
	
	int array_size=N;
	srand(time(NULL));
	
	artifacts** array;
	array=new artifacts*[array_size];
	for(int i=0;i<array_size;i++){
		array[i]=NULL;
	}
	
	for(int j=0;j<array_size;j++){
		int randomnum=rand()%2;							//randomly chooses if the artifact is going to be a painting or a sculpture
		if(randomnum==0){
			movement mov=movement(rand()%3);
			condition cond=condition(rand()%3);
			int creat=rand()%100;
			int y=rand()%(2018-1800+1)+1800;
			int le=rand()%(200-10+1)+10;
			int wi=rand()%(200-10+1)+10;
			technique tec=technique(rand()%3);
			
			array[j]=new paintings(mov,cond,creat,y,j,le,wi,tec);
		}
		else{
			movement move=movement(rand()%3);
			condition condi=condition(rand()%3);
			int crea=rand()%100;
			int ye=rand()%(2018-1800+1)+1800;
			int volu=rand()%(200-10+1)+10;
			material mat=material(rand()%3);
			array[j]=new sculptures(move,condi,crea,ye,j,volu,mat);
		}
	}
	
	auction(array,movvalue,condvalue,array_size);
	
	
	
	for(int k=0;k<array_size;k++){
		delete array[k];
		array[k]=NULL;
	}
	delete array;
	
}

artifacts::artifacts(int creat,int y,int i):index(i),creator(creat),year(y)
{
	cout << "Creating an instance of artifacts " << endl;
}

void artifacts::getInfo(){
	cout << "the artifact was created in " << year << " by the creator Creator" << creator << endl;
}

void artifacts::getIndex(){
	cout << "the index of the artifact is " << index << endl;
}

artifacts::~artifacts(){
	cout << "Destroying an instance of artifacts " << endl;
}

masterpiece::masterpiece(movement mov,condition cond,int creat,int y,int i):m(mov),c(cond),artifacts(creat,y,i)
{
	cout << "Creating an instance of masterpieces" << endl;
}

void masterpiece::getInfo(){
	artifacts::getIndex();
	artifacts::getInfo();
	string mov=getmovement(m);
	string cond=getcondition(c);
	cout << "the masterpiece belongs in the " << mov << " movement " << endl;
	cout << "the masterpiece is in " << cond << " condition " << endl;
}

masterpiece::~masterpiece(){
	cout << "Destroying an instance of masterpiece " << endl;
}

paintings::paintings(movement mov,condition cond,int creat,int y,int i,int le,int wi,technique tec):masterpiece(mov,cond,creat,y,i),length(le),width(wi),t(tec)
{
	cout << "Creating an instance of paintings " << endl;
}

paintings::~paintings(){
	cout << "Destroying an instance of paintings " << endl;
}

void paintings::getInfo(){
	masterpiece::getInfo();
	string techni=gettechnique(t);
	cout << "the painting is " << length << " cm in length " << endl;
	cout << "the painting is " << width << " cm in width " << endl;
	cout << "the painting has " << length*width << " cm^2 surface area " << endl;
	cout << "the painting is made using the " << techni << " technique " << endl;
}

int paintings::evaluate(movement mo,condition con){						//it will accept an artifact if it is the exact movement that we specified 
	if(mo==m && con<=c){												//and the condition is the same or in better condition
		cout << "the movement and condition are correct " << endl;
		return 1;
	}
	else{
		cout << "the movement or the condition are incorrect " << endl;
		return 0;
	}
}

int sculptures::evaluate(movement mo,condition con){					//it will accept an artifact if it is the exact movement and  
	if(mo==m && con==c){												//condition we specified
		cout << "the movement and the condition are correct " << endl;
		return 1;
	}
	else{
		cout << "the movement or the condition are incorrect " << endl;
		return 0;
	}
}

sculptures::sculptures(movement mov,condition cond,int creat,int y,int i,int vol,material ma):masterpiece(mov,cond,creat,y,i),volume(vol),mater(ma)
{
	cout << "Creating an instance of sculptures " << endl;
}

void sculptures::getInfo(){
	masterpiece::getInfo();
	string mate=getmaterial(mater);
	cout << "the sculpture has " << volume << " cm^3 volume " << endl;
	cout << "the sculpture is made from " << mate << endl;
}

sculptures::~sculptures(){
	cout << "Destroying an instance of sculptures " << endl;
}
