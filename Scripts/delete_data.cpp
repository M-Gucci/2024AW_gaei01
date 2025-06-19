//データ削減用プログラム

#include<iostream>
#include<map>
#include<vector>
#include<array>
#include<cmath>
#include<string>
#include<sstream>
#include<fstream>

using position=std::array<double,3>;
int ran=0;

void del(std::map<std::pair<double,double>,double>& pts,double t_x,double t_y){
    //std::cout << "delete" << std::endl;
    double sumx=0;
    double sumy=0;
    double sumz=0;
    int cnt=0;
    for(int i=t_x-1.0;i<=t_x+1.0;i+=1.0){
        for(int j=t_y-1.0;j<=t_y+1.0;j+=1.0){
            sumx+=i;
            sumy+=j;
            sumz+=pts[{i,j}];
            cnt++;
            //std::cout << "tmp" << std::endl;
            if(i==t_x && j==t_y){
                continue;
            }
            pts.erase({i,j});
            //std::cout << "pass";
            
        }
    }
    //std::cout << "tmp2" << std::endl;
    double avgx=sumx/(double)cnt;
    double avgy=sumy/(double)cnt;
    double avgz=sumz/(double)cnt;

    pts[{avgx,avgy}]=avgz;
    //std::cout << "tmp3" << std::endl;
    ran++;
}

void search(std::map<std::pair<double,double>,double>& pts){
    //std::cout << "search" << std::endl;
    for(auto p : pts){
        //std::cout << (p.first).first << " " << (p.first).second << " " << p.second << std::endl;
        int t_x=(p.first).first;
        int t_y=(p.first).second;
        //std::cout << "t_x:" << t_x << " t_y:" << t_y << std::endl;
        int flag=1;
        for(double i=t_x-1.0;i<=t_x+1.0;i+=1.0){
            for(double j=t_y-1.0;j<=t_y+1.0;j+=1.0){
                if(t_x==i && t_y==j){
                    continue;
                }
                auto iter=pts.find({i,j});
                //std::cout << "(" << i << "," << j << ")" << std::endl;
                if(iter==pts.end()){
                    flag=0;
                }
            }
        }
        //std::cout << "pass";
        //std::cout << "flag:" << flag << std::endl;
        if(flag==1){
            del(pts,t_x,t_y);
        }
    }
}

int main(){
    std::string filename;
    std::cout << "filename?: ";
    std::cin >> filename;

    std::ifstream file_in{filename};
    if(!file_in){
        std::cerr << "cannot open the file:" << filename << "\n";
        std::exit(1);
    }
    std::string line;

    std::map<std::pair<double,double>,double> pts;
    //std::map<std::pair<double,double>,double> inf_pts;
    while(std::getline(file_in,line)){
        std::istringstream string_in{line};
        double x,y,z;
        //int n;
        //std::cout << "pass";
        string_in >> x >> y >> z;
        //std::cout << x << " " << y << " " << z << "\n";
        if(x==-99999){
            search(pts);
            //std::cout << "pass";
            pts.clear();
        }else{
            pts[{x,y}]=z;
            //inf_pts[{x,y}]=z;
        }
    }

    search(pts);
    

    for(auto p : pts){
        //std::cout << "pass";
        std::cout << (p.first).first << " " << (p.first).second << " " << p.second << "\n";
    }
}