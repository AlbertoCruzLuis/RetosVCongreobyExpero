//Nombre: Alberto
//Apellidos: Cruz Luis
//Correo: alu0101217734@ull.edu.es

#include<iostream>
#include<vector>
#include<string>
#include<limits.h>

using namespace std;

string emuladorBonito(vector<string>);

int main()
{
    vector<string> cod(6);
    cod = {"DEC R42", 
 "INC R01", 
 "ADD R02,R01", 
 "ADD R00,R02", 
 "ADD R00,R42", 
 "JZ 1"};

    string resultado;

    resultado = emuladorBonito(cod);
    cout << "Resultado: " << resultado << endl;
}

string emuladorBonito(vector<string> subrutina) {
    
    vector<unsigned int> R(43);     //Registers
    
    //Recognize Instructions
    for(int i = 0; i < subrutina.size(); i++)
    {
        //Assign Each Instruction - (8 types of instructions)
        if(subrutina[i].substr(0,5) == "MOV R")
        {
            //Instruction MOV R(Rxx = Ryy)
            R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))] = R[stoi(subrutina[i].substr(5,2))];
        
        }else if(subrutina[i].substr(0,3) == "MOV")
        {
            //Instruction MOV(Rxx = d)
            R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))] = stoul(subrutina[i].substr(4,subrutina[i].size()-8));
        }else if(subrutina[i].substr(0,3) == "ADD")
        {
            //Instruction ADD(Rxx = Rxx + Ryy)
            if(R[stoi(subrutina[i].substr(5,2))] + R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))] > UINT_MAX)
            {
                R[stoi(subrutina[i].substr(5,2))] = 0;
            }else
            {
                R[stoi(subrutina[i].substr(5,2))] += R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))];
            }
            
        }else if(subrutina[i].substr(0,3) == "DEC")
        {
            //Instruction DEC(Rxx = Rxx - 1) Especial Case: if Rxx = 0 -> Rxx = (2^32)-1
            if(R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))] != 0)
            {
                R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))]--;
            }else
            {
                R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))] = UINT_MAX;
            }
            
        }else if(subrutina[i].substr(0,3) == "INC")
        {
            //Instruction INC(Rxx = Rxx + 1) Especial Case: if Rxx = (2^32)-1 -> Rxx = 0
            if(R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))] != UINT_MAX)
            {
                R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))]++;
            }else
            {
                R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))] = 0;
            }
            
        }else if(subrutina[i].substr(0,3) == "INV")
        {
            //Instruction INV(Rxx = ~Rxx) Example: 11001 -> 00110
            R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))] = ~R[stoi(subrutina[i].substr(subrutina[i].size()-2,2))];
            
        }else if(subrutina[i].substr(0,3) == "JMP")
        {
            //Instruction JMP (Jump to line d)
            i = stoi(subrutina[i].substr(4,subrutina[i].size()-4))-2;
            
        }else if(subrutina[i].substr(0,3) == "JZ ")
        {
            //Instruction JZ(if R00 = 0 -> Jump to line d)
            if(R[0] == 0)
            {
                i = stoi(subrutina[i].substr(3,subrutina[i].size()-3))-2;
            }
            
        }
        //NOP Does Nothing
    }
    
    return to_string(R[42]);
}
