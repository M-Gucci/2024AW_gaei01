#地面判定された点群をVRML化
#delauney triangulation -> output points
import numpy as np
from scipy.spatial import Delaunay

#print("how many points?")
n_p=int(input())

pts_x=np.array([])
pts_y=np.array([])
pts_z=np.array([])
pts_x2=np.array([])
pts_y2=np.array([])
pts_z2=np.array([])
cnt=0
tmp_x=0.0
print("#VRML V2.0 utf8")
for _ in range(n_p):
    a=[float (i) for i in input().split()]
    if a[0]!=tmp_x:
        cnt+=1
    tmp_x=a[0]
    #tmp_p=(y[0],a[1])

    if cnt==3:
        #print("Delauney")
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
        print("diffuseColor 0 1 1")
        print("}")
        print("}")
        print("}")
        
        pts_x=np.array([])
        pts_y=np.array([])
        pts_z=np.array([])
        pts_x=pts_x2.copy()
        pts_y=pts_y2.copy()
        pts_z=pts_z2.copy()
        pts_x2=np.array([])
        pts_y2=np.array([])
        pts_z2=np.array([])
        cnt=0
        
    if cnt==2:
        pts_x2=np.append(pts_x2,a[0])
        pts_y2=np.append(pts_y2,a[1])
        pts_z2=np.append(pts_z2,a[2])
        
    pts_x=np.append(pts_x,a[0])
    pts_y=np.append(pts_y,a[1])
    pts_z=np.append(pts_z,a[2])
        
        
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
print("diffuseColor 0 1 1")
print("}")
print("}")
print("}")
      