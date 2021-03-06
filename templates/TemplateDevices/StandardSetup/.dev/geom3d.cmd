; 3D object geometric description file
;
;geom3d				; Device type
Device Geom3D			; Device name
;QArrName QuadricArray		; Quadric array input device name
;CompName Composition            ; Composition input device name

; Object 1: external cilinder
Object Cyl1
PMMA Vacuum			; Phase in, phase out
3				; Number of quadrics
CZ1 P1 P2			; Quadric names

; Object 2: internal (empty) cilinder
Object Cyl2
Vacuum PMMA			; Phase in, phase out
3				; Number of quadrics
CZ2 P3 P4			; Quadric names

End
