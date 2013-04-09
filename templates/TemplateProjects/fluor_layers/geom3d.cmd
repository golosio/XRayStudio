; 3D object geometric description file
;
Device Geom3D                          ; Device name
;QArrName QuadricArray		; Quadric array input device name
;CompName Composition            ; Composition input device name


; 1st parallelepiped
Object Par1
Multilayer Vacuum		; Phase in, phase out
6				; Number of quadrics
P1 P2 P7 P8 P9 P10		; Quadric names

; 2nd parallelepiped
Object Par2
Copper Multilayer		; Phase in, phase out
6				; Number of quadrics
P3 P4 P7 P8 P9 P10		; Quadric names

; 3rd parallelepiped
Object Par3
Multilayer Vacuum		; Phase in, phase out
6				; Number of quadrics
P5 P6 P7 P8 P9 P10		; Quadric names

End
