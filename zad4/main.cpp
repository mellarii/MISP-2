#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char** argv) {
    //ifstream fin("input.txt");
    //ofstream fout("output.txt"); 
    
    ifstream fin(argv[1]);  
    ofstream fout(argv[2]); 

    if (!fin) {
        fout << 0 << " " << 0;
        return 0;
    } // proverka nalichiya dvuh argumentov komandnoy stroki

    string line; // chitaem pervuyu stroku iz fayla (po usloviyu)
    if (!getline(fin, line)) {
        fout << 0 << " " << 0;
        return 0;
    } // esli pustoy fail to vyvodim nuli
    fin.close();

    vector<char> seq;
    for (char ch : line) { // sobiraem vse simvoly 0 i 1, ignoriruya probely i vse prochee
        if (ch == '0' or ch == '1') {
            seq.push_back(ch);
        } // vsu ostalnyu fignu prosto popuskaem
    }

    if (seq.empty()) {
        fout << 0 << " " << 0;
        return 0;
    } // esli posle fil'tracii net dannyh

    // udolaem sosednie povtory (ostavlyaem tolko nachala blokov)
    vector<char> blocks = seq;
    auto it = unique(blocks.begin(), blocks.end());
    blocks.erase(it, blocks.end());

    // schitaem skol'ko blokov '1' i skol'ko blokov '0'
    int count1 = count(blocks.begin(), blocks.end(), '1');
    int count0 = count(blocks.begin(), blocks.end(), '0');

    // zapis v vyhodnoy fayl: snachala dlya 1, potom dlya 00
    fout << count1 << " " << count0;
    fout.close();

    return 0;
}