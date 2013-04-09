; Quadric array file
;
Device QuadricArray		; Device name

; parallelepiped 1 (center in the origin)
Plane  P1_1
0  0 -1.5  0  0 -1
Plane  P1_2
0  0  1.5  0  0  1
Plane  P1_3
0  -1.5  0  0 -1  0      
Plane  P1_4
0   1.5  0  0  1  0
Plane  P1_5
-1.5  0  0 -1  0  0
Plane  P1_6
1.5  0  0  1  0  0

; sphere 1 (center on y axis)
Ellipsoid  E1
0  -5.0  0  1  1  1

; parallelepiped 2 (center on y axis)
Plane  P2_1
0  0 -1.0  0  0  -1
Plane  P2_2
0  0  1.0  0  0  1
Plane  P2_3
0  5  0  0  -1 0
Plane  P2_4
0  6.5   0  0  1 0
Plane  P2_5
-1.0  0  0 -1  0  0
Plane  P2_6
1.0   0  0  1  0  0

; sphere 2 (center on x axis)
Ellipsoid E2
5.0	0   0  1  1  1

; parallelepiped 3 (center on z axis)
Plane  P3_1
0  0 -6.0  0  0 -1
Plane  P3_2
0  0 -5.0  0  0  1
Plane  P3_3
0  -1.5  0  0 -1  0
Plane  P3_4
0   1.5  0  0  1  0
Plane  P3_5
-1.0  0  0 -1  0  0
Plane  P3_6
1.0  0  0  1  0  0

; cylinder 1 (along z axis)
CylinderZ C1
0  0  1  1
Plane  C1P1
0 0   7.0	0 0   1   
Plane  C1P2
0 0   5.0 	0 0  -1

; cylinder 2 (along x axis)
CylinderX C2
0  0  1  1
Plane C2P1
-7.0 0  0   -1  0 0
Plane C2P2
-5.0 0  0   1  0 0

; external spherical shell
Ellipsoid  E3
0  0  0   9  9  9					
Ellipsoid  E4
0  0  0   9.1 9.1 9.1

; Rotation of all previous quadrics:
RotateAll 0 0 0 1 0 0 20 ; x0, y0, z0, ux, uy, uz, theta (20 deg around x)
RotateAll 0 0 0 0 0 1 20 ; x0, y0, z0, ux, uy, uz, theta (30 deg around z)

End
