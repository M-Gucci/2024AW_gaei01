#建物判定された点群をVRML化
#delauney triangulation -> output points
import numpy as np
from scipy.spatial import Delaunay


pts_x=np.array([])
pts_y=np.array([])
pts_z=np.array([])
cnt=0
tmp_x=0.0
print("#VRML V2.0 utf8")
while True:
    a=[float (i) for i in input().split()]
    if a[0]==-99999:
        tri=Delaunay(np.array([pts_x,pts_y]).T)
        print("Shape{")
        print("geometry IndexedFaceSet{")
        print("coord Coordinate{")
        print("point[")
        n=pts_x.size
        for i in range(n):
            print(pts_x[i],pts_y[i],pts_z[i],",")
        print("]}")
        print("coordIndex[")
        for v in tri.simplices:
            print(v[0],",",v[1],",",v[2],",",-1)
        print("]}")


        print("appearance Appearance{")
        print("material Material{")
        print("diffuseColor 1 0 1")
        print("}")
        print("}")
        print("}")
        
        pts_x=np.array([])
        pts_y=np.array([])
        pts_z=np.array([])
    elif a[0]==0:
        break
    else:
        pts_x=np.append(pts_x,a[0])
        pts_y=np.append(pts_y,a[1])
        pts_z=np.append(pts_z,a[2])
        
        
#tri=Delaunay(np.array([pts_x,pts_y]).T)
#print("Shape{")
#print("geometry IndexedFaceSet{")
#print("coord Coordinate{")
#print("point[")
#n=pts_x.size
#for i in range(n):
#    print(pts_x[i],pts_y[i],pts_z[i],",")
#print("]}")
#print("coordIndex[")
#for v in tri.simplices:
#    print(v[0],",",v[1],",",v[2],",",-1)
#print("]}")


#print("appearance Appearance{")
#print("material Material{")
#print("diffuseColor 1 0 0")
#print("}")
#print("}")
#print("}")
      