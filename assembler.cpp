#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

int main(int argc, char **argv) {
    using namespace std;
    const int data_bits = 5;
    const int inst_bits = 3;
    string input_file_name;
    string output_file_name;
    cout << "Input file name:"<<endl;;
    cin >> input_file_name;
    cout << "Output file name:"<<endl;
    cin >> output_file_name;
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
