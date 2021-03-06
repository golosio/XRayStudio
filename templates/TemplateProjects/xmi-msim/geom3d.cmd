; 3D object geometric description file
;
Device Geom3D                          ; Device name
;QArrName QuadricArray		; Quadric array input device name
;CompName Composition            ; Composition input device name


; 1st parallelepiped
Object Par1
Sample Air ; Phase in, phase out
6				; Number of quadrics
P1 P2 P3 P4 P5 P6		; Quadric names

; 2nd parallelepiped
Object Par2
Air Vacuum ; Phase in, phase out
6				; Number of quadrics
P7 P8 P9 P10 P11 P12		; Quadric names


End
