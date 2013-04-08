Device quadrics
		; Device name

;external cylinder
CylinderZ CZ1		; cylinder:
0 0 3 3			; axis x0, y0, ellipt. section semiaxes Rx, Ry
Plane  P1		; upper base plane:
0 0  4.001 0 0  1	; point x0, y0, z0, normal vect. ux, uy, uz
Plane  P2    		; lower base plane:
0 0 -4.001 0 0 -1	; point x0, y0, z0, normal vect. ux, uy, uz

;internal (empty) cylinder
CylinderZ CZ2		; cylinder:
0 0 2 2			; axis x0, y0, ellipt. section semiaxes Rx, Ry
Plane P3		; upper base plane:
0  0  4  0  0  1	; point x0, y0, z0, normal vect. ux, uy, uz
Plane  P4      		; lower base plane:
0  0 -4  0  0 -1	; point x0, y0, z0, normal vect. ux, uy, uz

; Rotation of all previous quadrics:
RotateAll 0 0 0 0 1 0 20 ; rotation axis x0, u, theta (20 deg around y)
RotateAll 0 0 0 1 0 0 30 ; rotation axis x0, u, theta (30 deg around x)
End

 End
