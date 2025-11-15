#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional> 
using namespace std;

int main(int argc, char** argv) {
  //proverka kolichestva argumentov stroki
  if(argc!=3) return 0;

  /*ifstream File("input.txt");
  ofstream File2("output.txt");*/

  //otkruvaem faili dlya chtenia 
  fstream File(argv[1]);
  fstream File2(argv[2]);

  //esli ne otkrilsya to grustno
  if (!File) {
        File2 << 0 << " " << 0;
        return 0;
  } 
  
  //chitaem kilichestvo chisel
  int N;
  File >> N;
  vector<int> v;

  //chitaem N chisel i pihaem v vector
  for(int i=0; i < N; i++) {
    int temp;
    File >> temp;
    v.push_back(temp);
  }
    
  File.close();
  sort(v.begin(), v.end(), std::greater<int>()); //sortiruem bol->men
  int first = 0, second = 0;

  for(int i = 0; i < v.size()/2; i++) {
    first += v[i]; //summa 1 polovini vectora (bolshie chisla)
    second += v[v.size()/2+i]; //summa 2 polovini vectora (minshie chisla)
  }

  if(!File2) return 0; 
  File2 << max(first, second) - min(first, second);
  return 0;
  
}