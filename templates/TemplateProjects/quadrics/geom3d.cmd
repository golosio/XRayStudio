; 3D object geometric description file
;
Device Geom3D			; Device name
;QArrName QuadricArray		; Quadric array input device name
;CompName Composition		; Composition input device name

; parallelepiped 1 (center in the origin)
Object Par1
PMMA Vacuum			; Phase in, phase out
6				; Number of quadrics for object 0
P1_1 P1_2 P1_3 P1_4 P1_5 P1_6	; Quadric names

; sphere 1 (center on y axis)
Object Sph1
PMMA Vacuum                     ; Phase in, phase out
1                               ; Number of quadrics for object 1
E1	                        ; Quadric names

; parallelepiped 2 (center on y axis)
Object Par2
PMMA Vacuum                     ; Phase in, phase out
6                               ; Number of quadrics for object 2
P2_1 P2_2 P2_3 P2_4 P2_5 P2_6	; Quadric names

; sphere 2 (center on x axis)
Object Sph2
PMMA Vacuum                     ; Phase in, phase out
1                               ; Number of quadrics for object 3
E2             	                ; Quadric names

; parallelepiped 3 (center on z axis)
Object Par3
PMMA Vacuum                     ; Phase in, phase out
6                               ; Number of quadrics for object 4
P3_1 P3_2 P3_3 P3_4 P3_5 P3_6	; Quadric names

; cylinder 1 (along z axis)
Object Cyl1
PMMA Vacuum			; Phase in, phase out
3	                        ; Number of quadrics for object 5
C1 C1P1 C1P2			; Quadric names

; cylinder 2 (along x axis)
Object Cyl2
PMMA Vacuum			; Phase in, phase out
3				; Number of quadrics for object 6
C2 C2P1 C2P2			; Quadric names

; spherical shell: internal (empty) sphere
Object Sph3
Vacuum PMMA			; Phase in, phase out
1				; Number of quadrics for object 7
E3				; Quadrics names

; spherical shell:  external sphere  
Object Sph4
PMMA Vacuum			; Phase in, phase out
1				; Number of quadrics for object 8
E4				; Quadrics names

End
