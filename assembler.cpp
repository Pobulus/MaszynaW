#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <vector>

bool readParameters ( int& argc, char** argv, std::string& in, std::string& out, int &inst, int &data ) {
    bool errors = false;
    for ( int i = 1; i < argc - 1; i++ ) {
        if ( not strcmp ( argv[i], "-i" ) ) { //input file
            in = argv[i + 1];
        } else if ( not strcmp ( argv[i], "-o" ) ) { //output file
            out = argv[i + 1];
        } else if ( not strcmp ( argv[i], "-d" ) ) { //data bits
            data = std::stoi(argv[i + 1]);
        } else if ( not strcmp ( argv[i], "-c" ) ) { //command bits
                inst = std::stoi(argv[i + 1]);
        } else if ( not strcmp ( argv[i], "-h" ) ) { //help
            errors = true;
        }
    }
    if ( not strcmp ( argv[argc - 1], "-h" ) ) 
            errors = true; //help
    return errors;
    
}

int main(int argc, char **argv) {
    using namespace std;
    int data_bits = 5;
    int inst_bits = 3;
    string input_file_name;
    string output_file_name;
    if(readParameters(argc, argv, input_file_name, output_file_name, inst_bits, data_bits)){
        cout << "You can use parameters:" << endl;
        cout << "-i \t input file name" << endl;
        cout << "-o \t output file name" << endl;
        cout << "-d \t number of data bits (5)" << endl;
        cout << "-c \t number of instruction bits (3)" << endl;
        cout << "-h \t this help message" << endl;
        return 0;
    }
    if(input_file_name==""){
        cout << "Input file name:"<<endl;
        cin >> input_file_name;
    }
    if(output_file_name==""){
        cout << "Output file name:"<<endl;
        cin >> output_file_name;
    }
    ifstream  input(input_file_name);
    ofstream  output(output_file_name);
    vector<pair<string, string>> lines;
    map<string, int> insts;
    map<string, int> labels;
    insts["RST"] = 0<<data_bits;
    insts["RPA"] = 0<<data_bits;
    insts["STP"] = 0<<data_bits;
    insts["DOD"] = 1<<data_bits;
    insts["ODE"] = 2<<data_bits;
    insts["POB"] = 3<<data_bits;
    insts["ŁAD"] = 4<<data_bits;
    insts["SOB"] = 5<<data_bits;
    insts["SOM"] = 6<<data_bits;
    insts["SOZ"] = 7<<data_bits;
    if(input){
        int lc = 0;
        
        string token;
        while(input >> token){
            int pos = token.find(":");
            if(pos!=string::npos){ //token is a label
                cout << "LABEL:"<<token<<endl;
                labels[token.substr(0, pos)]=lc;
            }else{
                for(auto &l : token){//ignore lowercase
                    l = toupper(l);
                }
                if( insts.count(token)){ //token is an instruction
                    string attr;
                    if(token == "RPA" or token == "STP") {
                        attr = "0";
                    }else{
                        if(!(input >> attr)){
                            cerr << "Attribute error on "<<lc<<endl;
                            attr = "0";
                        }
                    }
                    lines.push_back({token, attr});
                    cout << "INST: "<<token << " ATTR: "<<attr<<endl;
                    ++lc;
                }else{
                    cerr << "Instruction not found on line "<< lc<<endl;
                }
            }
        }
        std::cout << "Labels:"<<endl;
        for(auto l : labels){
            std::cout << l.first<< " -> " << l.second<<endl;
        }
        for(auto &line : lines){
            if(labels.count(line.second)){
                line.second = to_string(labels[line.second]);
            }
            cout << (insts[line.first])+stoi(line.second) <<endl;
        }
        if(output){
            output << "v2.0 raw"<<endl;
            output << hex;
            for(auto line : lines){
                output << (insts[line.first])+stoi(line.second) << " ";
            }
            output << endl;
        }
        
    }
    return 0;
}
