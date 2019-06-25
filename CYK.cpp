#include <iostream>
#include <set>
#include <map>
#include <vector>
using namespace std;

typedef std:: set<int> intset;
typedef std:: map<int, intset>row;
typedef std::map<int, row> table;
table tabla;

typedef struct{
	int principal;
	int derivado;
	int derivado2;
}reglas;

std::vector<reglas> grammar;

void proyecciones(int, int, int=0);

bool CYK(string);
int buscar(char);
void imprimir();
int buscar2(int, int);
int caracter(int, int);


int main(){
	
	proyecciones((int)'S',(int)'x');
	proyecciones((int)'S',(int)'A',(int)'C');
	proyecciones((int)'C',(int)'S',(int)'R');
	proyecciones((int)'R',(int)'t');
	proyecciones((int)'R',(int)'B',(int)'C');
	proyecciones((int)'A',(int)'l');
	proyecciones((int)'B',(int)'c');
	
	for(int i=0;i<grammar.size();i++){
		printf("%c",grammar[i].principal);
		printf("->");	
		printf("%c",grammar[i].derivado);	
		printf("%c\n",grammar[i].derivado2);	
	}
	string cadena;
	cin>>cadena;
	cout<<CYK(cadena)<<endl;
	
	if(CYK(cadena)){
		cout<<"ACEPTADA"<<endl;
	}else{
		cout<<"RECHAZADA"<<endl;
	}
	
	imprimir();
	
	return 0;
}

void proyecciones(int a, int b, int c){
	reglas x;
	x.principal=a;
	x.derivado=b;
	x.derivado2=c;
	
	grammar.push_back(x);
}

bool CYK(string w){
	
	int n=w.size();
	
	for(int i=0; i<n; i++){
		tabla[i+1][1].insert(buscar(w[i]));
	}
	
	for(int j=2;j<=n;j++){
		for(int i=1;i<=n-j+1;i++){
			
			for(int k=1;k<=j-1;k++){
				int a=caracter(i,k);
				int b=caracter(i+k,j-k);
				
				if(caracter(i,k)!=32 && caracter(i+k,j-k)!=32){
						tabla[i][j].insert(buscar2(a,b));
				}
		 	}
			
		}
	}
	intset::iterator it = tabla[1][n].end();
	return tabla[1][n].find('S')!=it;
}

int buscar(char a){	//te regresa si hay una produccion por medio de un simbolo terminal
	
	for(int i=0; i<grammar.size();i++){
		
		if(grammar[i].derivado==a){
			return grammar[i].principal;
		}
		
	}
	return -1;
}

void imprimir(){
	for(int i=1; i<=tabla.size();i++){
		for(int j=1;j<=tabla.size();j++){
			intset::iterator it;
			it=tabla[i][j].begin();
			for(it;it!=tabla[i][j].end();it++){
				printf("%c ",*it);
			}
		}
		cout<<endl;
	}
}

int buscar2(int a, int b){	//te regresa si hay una produccion por medio de dos simbolos generadore
	
			
	for(int i=0;i<grammar.size();i++){
		if(grammar[i].derivado==a && grammar[i].derivado2==b){
			return grammar[i].principal;
		}
	}
	return 32;
}

int caracter(int a, int b){	//Te retorna el caracter que esta dentro de la tabla
	intset::iterator it;
			it=tabla[a][b].begin();
			for(it;it!=tabla[a][b].end();it++){
				return *it;
		}
		return 32;
}
