//地面建物判定プログラム

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
double B=2.0;
int repe=5000;
double x_min,y_min,z_min,z_max,y_max,x_max;
double x_z_min,y_z_min;
int cnt1=0,cnt2=0;
std::vector<position> pts_1;

void tem_border(std::map<position,int>& pts_tjug, double mx, double my, double mz, std::map<std::pair<double,double>,double>& pts){
    
    std::vector<position> t_pts;
    t_pts.push_back({mx,my,mz});

    pts_tjug.erase({mx,my,mz});
    
    while(true){
        if(t_pts.size()==0){
            break;
        }
        position p=*t_pts.begin();
        pts_1.push_back(p);    
        //std::cout << p[0] << " " << p[1] << " " << p[2] << " " << 1 << "\n";
        t_pts.erase(t_pts.begin());
        for(double i=p[0]-1;i<=p[0]+1;i++){
            for(double j=p[1]-1;j<=p[1];j++){
                if(p[0]==i && p[1]==j){
                    continue;
                }
                if(pts_tjug.find({i,j,pts[{i,j}]})==pts_tjug.end()){
                    continue;
                }
                if(std::fabs(mz-pts[{i,j}])<=B){
                    cnt1++;
                    t_pts.push_back({i,j,pts[{i,j}]});
                    //std::cout << "erase: " << i << " " << j << " " << pts[{i,j}] << "\n";
                    pts_tjug.erase({i,j,pts[{i,j}]});
                }
            }
        }
    }
}

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
    std::map<position,int> t_jug;
    std::map<std::pair<double,double>,double> pts;
    std::vector<position> min_pts;
    double z_min=10000.0;
    double x_z_min,y_z_min;
    while(std::getline(file_in,line)){
        std::istringstream string_in{line};
        double x,y,z;
        string_in >> x >> y >> z;
        if(z_min>z){
            z_min=z;
            x_z_min=x;
            y_z_min=y;
        }
        pts[{x,y}]=z;
        t_jug[{x,y,z}]=-1;
    }
    //std::cout << "min " << x_z_min << " " << y_z_min << " " << z_min << "\n";
    tem_border(t_jug,x_z_min,y_z_min,z_min,pts);
    for(int i=1;i<repe;i++){
        double t_z=10000.0;
        double t_x,t_y;
        for(auto pts : t_jug){
            if(t_z>(pts.first)[2]){
                t_z=(pts.first)[2];
                t_x=(pts.first)[0];
                t_y=(pts.first)[1];
            }
        }
        //std::cout << "i " << t_x << " " << t_y << " " << t_z << "\n";
        tem_border(t_jug,t_x,t_y,t_z,pts);
    }
    for(auto p : pts_1){
        //ground
        std::cout << p[0] << " " << p[1] << " " << p[2] << " " << 0 << "\n";
    }

    for(auto k_v : t_jug){
        //building
        std::cout << (k_v.first)[0]<< " " << (k_v.first)[1] << " " << (k_v.first)[2] << " " << 1 << "\n";
    }
    //std::cout << cnt1 << "\n";
}