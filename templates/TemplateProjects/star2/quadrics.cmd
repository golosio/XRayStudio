; Quadric array file
;
Device QuadricArray		; Device name

;external pentagon
Plane P1			; side 1 outer plane
0  0 -4.001  0  0 -1

Plane P2			; side 1 inner plane
0  0 -4      0  0 -1
;

Plane P3			; side 2 outer plane
0  0 -4.001  0  0 -1
Rotate 0 0 0 0  1  0 72	      	; rotate 72 degrees around y axis 

Plane P4     	     		; side 2 inner plane
0  0 -4      0  0 -1
Rotate 0 0 0  0  1  0 72      	; rotate 72 degrees around y axis 
;

Plane P5			; side 3 outer plane
0  0 -4.001  0  0 -1
Rotate 0 0 0 0  1  0 144	; rotate 144 degrees around y axis 

Plane P6     	     		; side 3 inner plane
0  0 -4      0  0 -1
Rotate 0 0 0 0  1  0 144	; rotate 144 degrees around y axis 
;

Plane P7			; side 4 outer plane
0  0 -4.001  0  0 -1
Rotate 0 0 0 0  1  0 216	; rotate 216 degrees around y axis 

Plane P8     	     		; side 4 inner plane
0  0 -4      0  0 -1
Rotate 0 0 0 0  1  0 216	; rotate 216 degrees around y axis 
;

Plane P9			; side 5 outer plane
0  0 -4.001  0  0 -1
Rotate 0 0 0 0  1  0 288	; rotate 288 degrees around y axis 

Plane P10    	     		; side 5 inner plane
0  0 -4      0  0 -1
Rotate 0 0 0 0  1  0 288	; rotate 288 degrees around y axis 

; Star sides
Plane P11			; side 1
0  0 1.528  0  0 -1
;

Plane P12			; side 2
0  0 1.528  0  0 -1
Rotate 0 0 0  0  1  0 72	; rotate 72 degrees around y axis 
;

Plane P13			; side 3
0  0 1.528  0  0 -1
Rotate 0 0 0 0  1  0 144	; rotate 144 degrees around y axis 
;

Plane P14			; side 4
0  0 1.528  0  0 -1
Rotate 0 0 0 0  1  0 216	; rotate 216 degrees around y axis 
;

Plane P15			; side 5
0  0 1.528  0  0 -1
Rotate 0 0 0  0  1  0 288	; rotate 288 degrees around y axis 

; closing external planes
Plane P16
0   1.001   0  0   1   0
Plane P17
0  -1.001   0  0  -1   0

; closing internal planes
Plane P18
0   1   0  0   1   0
Plane P19
0  -1   0  0  -1   0

; Rotation of all previous quadrics:
RotateAll 0 0 0 0 1 0 45 ; x0, y0, z0, ux, uy, uz, theta (45 deg around y)
RotateAll 0 0 0 1 0 0 30 ; x0, y0, z0, ux, uy, uz, theta (30 deg around x)

End
