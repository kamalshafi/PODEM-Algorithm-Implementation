#include "input.h"
/***************************************************************************************************************************
Truth Table
****************************************************************************************************************************/
int NOTG[5] = {1,0,Db,D,DC};
int ANDG[5][5]={{0,0,0,0,0},{0,1,D,Db,DC},{0,D,D,0,DC},{0,Db,0,Db,DC},{0,DC,DC,DC,DC}};
int ORG[5][5]={{0,1,D,Db,DC},{1,1,1,1,1},{D,1,D,1,DC},{Db,1,1,Db,DC},{DC,1,DC,DC,DC}};
int NOC[10]={0,0,0,0,1,1,0,0,0,0};

int ReadPat(FILE *Pat, PATTERN *Patterns){   // Function for reading patterns
	char line[Mlin];//Local Variable having a array of size of Mlin
	int i=0,n;
	// read line by line
	while(!feof(Pat)){
		if(fgets(line,Mlin,Pat)!=NULL){
			// printf("%s",line);
			for(n=0;n<strlen(line);n++){
				if(line[n]=='1')
					Patterns[i].Pat[n]=1;
				else if(line[n]=='0')
					Patterns[i].Pat[n]=0;
				else if(line[n]=='x'||line[n]=='X')
					Patterns[i].Pat[n]=DC;
			}
			i++;
		}
	}

	// for(n=0;n<5;n++){
	//	for(i=0;i<5;i++)	printf("%d",Patterns[n].Pat[i]);
	//	printf("\n");
	// }
	return i;
}

void LogicSim(GATE *Node, PATTERN *Patterns, int Tgat, int Tpat, FILE *Res) //Function for running Logic Simulation
{
	int i,j,k;

	for(i=0;i<Tpat;i++){
		k=0;
		for(j=0;j<=Tgat;j++){
			if(Node[j].Type !=0){
				if(Node[j].Type==INPT){
					Node[j].Val = Patterns[i].Pat[k];
					k++;
				}
				else{
					Gout(Node, j);
				}
				if(Node[j].Po) {
					printf("%d",Node[j].Val);
					fputc(Node[j].Val+'0' , Res);
				}
			}
		}//PrintGats(Node,Tgat); 
		printf(" %d\n", i); // Printing output corresponding Number
		fputc('\n' , Res);
		
	}
}

void Gout(GATE *Node, int a) //Function for gate outputs
{
	LIST *lfin;
	int val; // local variable
	if(Node[a].Type==FROM){
		lfin=Node[a].Fin;
		while(lfin!=NULL){
			Node[a].Val=Node[lfin->Id].Val; 
			lfin=lfin->Next;
		}
	}
	else if(Node[a].Type==BUFF){
		lfin=Node[a].Fin;
		while(lfin!=NULL){
			Node[a].Val=Node[lfin->Id].Val; 
			lfin=lfin->Next;
		}
	}
	else if(Node[a].Type==NOT){
		lfin=Node[a].Fin;
		while(lfin!=NULL){
			Node[a].Val=NOTG[Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		}
	}
	else if(Node[a].Type==AND){
		lfin=Node[a].Fin;
		val=1;// non control for AND gate
		while(lfin!=NULL){
			val=ANDG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		}
		Node[a].Val=val;
	}
	else if(Node[a].Type==NAND){
		lfin=Node[a].Fin;
		val=1;// non control for AND gate
		while(lfin!=NULL){
			val=ANDG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		}
		Node[a].Val=NOTG[val]; //Inverting AND Operation
	}
	else if(Node[a].Type==OR){
		lfin=Node[a].Fin;
		val=0;//NOTG non control for OR gate
		while(lfin!=NULL){
			val=ORG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		 }
		Node[a].Val=val;
	}
	else if(Node[a].Type==NOR){
		lfin=Node[a].Fin;
		val=0;// non control for OR gate
		while(lfin!=NULL){
			val=ORG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		 }
		Node[a].Val=NOTG[val];//Inverting OR Operation
	}
	else if(Node[a].Type==XOR) {printf("ERROR: XOR GATE FOUND\n");exit(0);}
	else if(Node[a].Type==XNOR){printf("ERROR: XNOR GATE FOUND\n");exit(0);}
}

/***************************************************************************************************/

void Incertx(GATE * Node, int Tgat){ //Function for Reset
	int j;
	for(j=0;j<=Tgat;j++){
		if(Node[j].Type !=0){
			Node[j].Val = DC;
		}
	}
}
void LogicSimImply(GATE * Node, int G, int Val,LIST **Dfront) {
	LIST * lFot, *Nodenxt;
	int g, Preval;
	Nodenxt=NULL;
	Node[G].Val=Val;
	lFot=Node[G].Fot;// Adding Fanout value to the list
	if(lFot!=NULL){
		InsertEle(&Nodenxt,lFot->Id);//insert element in Nodenxt list
		lFot=lFot->Next;//Updating List 
	}
	while(Nodenxt!=NULL){
		g = Nodenxt->Id;
		Preval=Node[g].Val;
		Gout(Node,g);
		if(Check_DF(Node, g)) InsertEle(Dfront,g);//Incerting into D-Frontier
		if(Node[g].Val!=Preval){
			lFot=Node[Nodenxt->Id].Fot;
		}
		while(lFot!=NULL){
			InsertEle(&Nodenxt,lFot->Id);
			lFot=lFot->Next;
		}
		Nodenxt=Nodenxt->Next;
	}
}

void Backtrace(GATE *Node, int G, int Val, BACKTRACE input){ //Function for Backtrace
	int Tinversion=0;
	LIST *Temp;
	while(Node[G].Type!=INPT){
		if(Node[G].Type==NAND || Node[G].Type==NOR || Node[G].Type==NOT)
			Tinversion++;
		Temp=Node[G].Fin;
		while(Temp!=NULL){
			if(Node[Temp->Id].Val==DC){
				G = Temp->Id;
				break;
			}
			Temp=Temp->Next;
		}
		
	}
	if(Tinversion%2 != 0){
		Val=NOTG[Val];
	}
	
	input.Gate=G;
	input.Value=Val;
	printf("gatevalue=%d, gate_number=%d", input.Gate, input.Value);
}

int Check_Dfront(GATE *Node, int i){
	LIST *lFin;
	lFin=Node[i].Fin;//Putting fanin values and saving to the list
	if(Node[i].Val==DC){
		while(lFin!=NULL){
			if(Node[lfin->Id]==D||Node[lFin->Id]==Db)
				return Sucess;
			lFin=lFin->Next;
		}
	}
	Return Failure;
}

int Get_object(GATE *Node, int G, int V){
	//LIST *Temp
	//Temp=Node[G].Fin;
		if(Node[G].Val==DC){
	
		}
		Node[Temp->Id].Val=NOC[Node[Temp->Id].Type];
		return      	
	}
	
		



}


int Podem_Recursion(GATE *Node, int G, int V, LIST **Dfront){
	if(Node[G].Val=)

}




