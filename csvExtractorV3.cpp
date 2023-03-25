#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#define _GNU_SOURCE

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



vector<Record> Data;


// * TODO:  STOLL INSTEAD OF STOL
void insertData(int counter, string token){
    switch (counter)
    {
    case 0: Data.back().Direction=token; break;
    case 1: try{
        Data.back().Year=stoi(token);}
        catch(exception &err){ cout<<"ERROR  "<< token<<endl; exit(1);} break;
    case 2: Data.back().Date=token; break;
    case 3: Data.back().Weekday=token; break;
    case 4: Data.back().Country=token; break;
    case 5:{ Data.back().Commodity=token; if(token=="Logs, wood, and wood articles") cout<<Data.back().Commodity<<endl;  break;}
    case 6: Data.back().Transport_Mode=token; break;
    case 7: Data.back().Measure=token; break;
    case 8: Data.back().Value=stoll(token); break;
    case 9: Data.back().Cumulative=stoll(token); break;
    default:
        break;
    }
}


void splitstring(stringstream& ss){
    string token;
    string temp;
    int counter=0;
    
    while(getline(ss, token, ',')){
        
      
        insertData(counter, token);
        

        counter++;

        if(ss.peek()=='"'){
            ss.get();
            // temp=token;
            getline(ss, token, '"');
          //  cout<<"TEMP: "<<temp<<endl;
            // temp+=token;
            // cout<<"AFTER: " <<temp<<endl;
            // cout<<counter<<endl;
            // cout<<"NEW TOK: "<<token<<endl;
            insertData(counter, token);


            //! next comma after ",
            ss.get();
            //counter++;
        }

        
        // cout<<"COUNTER: "<<counter<<" TOKEN: "<<token<<endl;
        
       
    }
    
}

int main(){


string line="";
stringstream ss(line);
Record* temp;
//stringstream check;
ifstream file("testset.csv");
if(file.good()){
cout<<"FILE OPENED"<<endl;
file>>line;
int i=1;
   //while(file>>line){
    while(getline(file, line)){
       // cout<<"LINE: "<<i<<endl;
            //check(line);
      //  cout<<line<<endl;
        // temp=(Record*)malloc(sizeof(Record));
        temp= new Record;
        Data.push_back(*temp);
        ss<<line;
        // if(ss.peek()==' '){
        //     file>>line;
        //     ss<<ss.str()<<line;
        //     cout<<ss.str();
        //     exit(1);
        // }
       // cout << ss.str() << endl;
        splitstring(ss);
       //cout<<"\t"<< i++ <<line<<endl;
      // cout<<ss.str()<<endl;
       ss.str("");
       ss.clear();
       i++;
       //ss.str(std::string());
    }

    for (int  i = 0; i < Data.size(); i++)
    {
        if(Data[i].Commodity=="Logs, wood, and wood articles"){
            cout<<"YES"<<endl;
           // cout<<Data[i].Commodity<<endl;
    //         cout<<Data[i].Direction<<"\t"<<Data[i].Year<<"\t"<<Data[i].Date<<"\t"<<Data[i].Weekday<<"\t"<<
    // Data[i].Country<<"\t"<<Data[i].Commodity<<"\t"<<Data[i].Transport_Mode<<"\t"<<Data[i].Measure<<"\t"<<Data[i].Value<<"\t"<<
    // Data[i].Cumulative<<endl;
        }
    }
    //df
    

    cout<<Data.back().Direction<<"\t"<<Data.back().Year<<"\t"<<Data.back().Date<<"\t"<<Data.back().Weekday<<"\t"<<
    Data.back().Country<<"\t"<<Data.back().Commodity<<"\t"<<Data.back().Transport_Mode<<"\t"<<Data.back().Measure<<"\t"<<Data.back().Value<<"\t"<<
    Data.back().Cumulative<<endl;


   // cout<<sizeof(Data.back().Country)<<endl;

}

system("pause");
    return 0;
}