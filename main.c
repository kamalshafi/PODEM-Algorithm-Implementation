#include "input.h"
/***************************************************************************************************
Command Instructions
***************************************************************************************************/
//To Compile: make
//To Run: ./project c17.isc 
/***************************************************************************************************
 Main Function
***************************************************************************************************/
int main(int argc,char **argv)
{
FILE *Isc,*Pat,*Res;                  //File pointers used for .isc, .pattern, and .res files
int Npi,Npo,Tgat;                     //Tot no of PIs,Pos,Maxid,Tot no of patterns in.vec,.fau
GATE *Node;                           //Structure to store the ckt given in .isc file 
clock_t Start,End;                    //Clock variables to calculate the Cputime
double Cpu;                           //Total cpu time
int i,j;                              //Temporary variables
int Tpat;                             //Total No of Patterns 
PATTERN Patterns[Mpt];                //Defining Memory structure for patterns
BACKTRACE input;


/****************PART 1.-Read the .isc file and store the information in Node structure***********/
Npi=Npo=Tgat=0;                                //Intialize values of all variables
Isc=fopen(argv[1],"r");                        //File pointer to open .isc file 
Node=(GATE *) malloc(Mnod * sizeof(GATE));     //Dynamic memory allocation for Node structure
Tgat=ReadIsc(Isc,Node);                        //Read .isc file and return index of last node
fclose(Isc);                                   //Close file pointer for .isc file
//PrintGats(Node,Tgat);                          //Print the information of each active gate in Node structure after reading .isc file
CountPri(Node,Tgat,&Npi,&Npo);                 //Count the No of Pis and Pos
//printf("\n\nNpi: %d Npo: %d\n",Npi,Npo);       //Print the no of primary inputs and outputs
/***************************************************************************************************/
//Pat=fopen(argv[2],"r");                        //File pointer to open .isc file 
//Tpat=ReadPat(Pat,Patterns);                    //Read .isc file and return index of last node
//fclose(Pat);                                   //Close pattern file
//Res=fopen(argv[3],"w");                        //Generating Response File
//LogicSim(Node, Patterns, Tgat, Tpat, Res);     //Run Logic Simulation
//fclose(Res);
Incertx(Node, Tgat);
//LogicSimImply(Node, 1, 0);
//PrintGats(Node,Tgat); 
Backtrace(Node,22,0,input);
PrintGats(Node,Tgat); 
/***************************************************************************************************/

ClearGat(Node,Tgat);  free(Node);                                      //Clear memeory for all members of Node
return 0;
}//end of main
/****************************************************************************************************************************/

