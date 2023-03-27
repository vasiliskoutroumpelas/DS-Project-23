#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;




typedef struct record{
    /* 
    direction 10
    date 11
    weekday 10
    */
    string Direction;
    string Date;
    string Weekday;
    string Country;
    string Commodity;
    string Transport_Mode;
    string Measure;
    long int Value;
    long int Cumulative;
    int Year;
    
}Record;






// * TODO:  STOLL INSTEAD OF STOL
void insertData(int counter, string token, vector<Record>& Data){
    switch (counter)
    {
    case 0: Data.back().Direction=token; break;
    case 1: try{
        Data.back().Year=stoi(token);}
        catch(exception &err){ cout<<"ERROR  "<< token<<endl; exit(1);} break;
    case 2: Data.back().Date=token; break;
    case 3: Data.back().Weekday=token; break;
    case 4: Data.back().Country=token; break;
    case 5: {Data.back().Commodity=token; 
            if(token=="Milk powder, butter, and cheese") 
            cout<<Data.back().Commodity<<endl;  break;}
    case 6: Data.back().Transport_Mode=token; break;
    case 7: Data.back().Measure=token; break;
    case 8: Data.back().Value=stoll(token); break;
    case 9: Data.back().Cumulative=stoll(token); break;
    default:
        break;
    }
}


void splitstring(stringstream& ss, vector<Record>& Data){
    string token;
    string temp;
    int counter=0;
    
    while(getline(ss, token, ',')){
        
      
        insertData(counter, token, Data);
        

        counter++;

        if(ss.peek()=='"'){
            ss.get();
            getline(ss, token, '"');
            insertData(counter, token, Data);


            //! next comma after ",
            ss.get();
         
        }
    }
    
}


void InitiateFile(ifstream& file, vector<Record>& Data){
string line;
stringstream ss(line);
Record* temp;

//? Remove the first line of the file
file>>line;
// int lineNum=1;
   
    while(getline(file, line)){
       
        temp= new Record;
        Data.push_back(*temp);
        ss<<line;
        
        splitstring(ss, Data);
      
       ss.str("");
       ss.clear();
    // lineNum++;
       
    }
}

int main(){

    ifstream file("testset.csv");
    if(file.good()){
    cout<<"FILE OPENED"<<endl;
    vector<Record> Data;
    InitiateFile(file, Data);

       
        
        for (int  i = 0; i < Data.size(); i++)
        {
            // if(Data[i].Commodity=="Milk powder, butter, and cheese") cout<<"True"<<endl;
            if(Data[i].Commodity=="Milk powder, butter, and cheese")
           cout<<Data[i].Commodity<<endl;
        }
        


        // cout<<Data.back().Direction<<"\t"<<Data.back().Year<<"\t"<<Data.back().Date<<"\t"<<Data.back().Weekday<<"\t"<<
        // Data.back().Country<<"\t"<<Data.back().Commodity<<"\t"<<Data.back().Transport_Mode<<"\t"<<Data.back().Measure<<"\t"<<Data.back().Value<<"\t"<<
        // Data.back().Cumulative<<endl;


    

}

system("pause");
    return 0;
}