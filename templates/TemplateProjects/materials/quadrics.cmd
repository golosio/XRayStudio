; Quadric array file
;
Device QuadricArray			; Device name

; External parallelepiped
Plane PZm
0 0 -5 0 0 -1
Plane PZp
0 0 5 0 0 1
Plane PXp
5 0 0 1 0 0
Plane PXm
-5 0 0 -1 0 0
Plane PYp
0 0.5 0 0 1 0
Plane PYm
0 -0.5 0 0 -1 0

; Inner planes
Plane PZ1
0 0 -4.001 0 0 1
Plane PZ2
0 0 -4 0 0 -1
Plane PZ3
0 0 4 0 0 1
Plane PZ4
0 0 4.001 0 0 -1
Plane PX1
-4 0 0 1 0 0
Plane PX2
4 0 0 -1 0 0


;1st cylinder
CylinderZ C1
-3 0 0.5 0.5

;2nd cylinder
CylinderZ C2
-1 0 0.5 0.5

;3rd cylinder
CylinderZ C3
1 0 0.5 0.5

;4th cylinder
CylinderZ C4
3 0 0.5 0.5

; Rotation of all previous quadrics:
RotateAll 0 0 0 0 0 1 -20 ; x0, y0, z0, ux, uy, uz, theta (20 deg around z)
RotateAll 0 0 0 1 0 0 -20 ; x0, y0, z0, ux, uy, uz, theta (20 deg around x)


End

