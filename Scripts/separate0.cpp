//地面建物判定されたファイル->地面判定された点群を抽出

#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include<array>
#include<map>
#include<utility>
#include<cmath>

using position=std::array<double,3>;

int main(){
    std::string filename;
    std::cout << "filename?: ";
    std::cin >> filename;

    std::ifstream file_in{filename};
    if(!file_in){
        std::cerr << "cannot open the file: " << filename << "\n";
        std::exit(1);
    }

    std::string line;
    std::vector<position> judged_points_0;
    std::vector<position> judged_points_1;
    while(std::getline(file_in,line)){
        std::istringstream string_in{line};
        double x,y,z;
        int jug;
        string_in >> x >> y >> z >> jug;
        if(jug==0){
            judged_points_0.push_back({x,y,z});
        }if(jug==1){
            break;
        }
    }
    
    for(auto pts : judged_points_0){
        std::cout << pts[0] << " " << pts[1] << " " << pts[2] << "\n";
    }


}