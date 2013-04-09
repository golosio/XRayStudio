; Quadric array file
;
Device QuadricArray		; Device name

; Star sides
Plane P1			; side 1: point border
0  0 1.528  0  0 -1

Plane P2			; side 1: internal pentagon border
0  0 1.527  0  0  1
;

Plane P3			; side 2: point border
0  0 1.528  0  0 -1
Rotate 0 0 0 0  1  0 72		; rotate 72 degrees around y axis 

Plane P4       			; side 2: internal pentagon border
0  0 1.527  0  0  1
Rotate 0 0 0  0  1  0 72	; rotate 72 degrees around y axis 
;

Plane P5			; side 3: point border
0  0 1.528  0  0 -1
Rotate 0 0 0  0  1  0 144	; rotate 144 degrees around y axis 

Plane P6      			; side 3: internal pentagon border
0  0 1.527  0  0  1
Rotate 0 0 0 0  1  0 144	; rotate 144 degrees around y axis 
;
Plane P7			; side 4: point border
0  0 1.528  0  0 -1
Rotate 0 0 0 0  1  0 216	; rotate 216 degrees around y axis 

Plane P8       			; side 4: internal pentagon border
0  0 1.527  0  0  1
Rotate 0 0 0 0  1  0 216	; rotate 216 degrees around y axis 
;

Plane P9			; side 5: point border
0  0 1.528  0  0 -1
Rotate 0 0 0 0  1  0 288	; rotate 288 degrees around y axis 

Plane P10      		; side 5: internal pentagon border
0  0 1.527  0  0  1
Rotate 0 0 0 0  1  0 288	; rotate 288 degrees around y axis 

; closing planes
Plane P11
0   1   0  0   1   0
Plane P12
0  -1   0  0  -1   0

; Rotation of all previous quadrics:
RotateAll 0 0 0 0 1 0 45 ; x0, y0, z0, ux, uy, uz, theta (45 deg around y)
RotateAll 0 0 0 1 0 0 30 ; x0, y0, z0, ux, uy, uz, theta (30 deg around x)
End
