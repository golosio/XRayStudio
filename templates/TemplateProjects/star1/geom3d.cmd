; 3D object geometric description file
;
Device Geom3D			; Device name
;QArrName QuadricArray		; Quadric array input device name
;CompName Composition		; Composition input device name

Object PentInt			; 3d object: internal pentagon
PMMA Vacuum			; Phase in, phase out
7				; Number of quadrics
P2 P4 P6 P8 P10 P11 P12		; Quadric names

Object Point1	    		; Object 1: point 1
PMMA Vacuum			; Phase in, phase out
5				; Number of quadrics
P1 P4 P10 P11 P12		; Quadric names

Object Point2 			; Object 2: point 2
PMMA Vacuum			; Phase in, phase out
5				; Number of quadrics
P3 P2 P6 P11 P12		; Quadric names

Object Point3			; Object 3: point 3
PMMA Vacuum			; Phase in, phase out
5				; Number of quadrics
P5 P4 P8 P11 P12		; Quadric indexes

Object Point4			; Object 4: point 4
PMMA Vacuum			; Phase in, phase out
5				; Number of quadrics
P7 P6 P10 P11 P12		; Quadric names

Object Point5 			; Object 5: point 5
PMMA Vacuum			; Phase in, phase out
5				; Number of quadrics
P9 P2 P8 P11 P12		; Quadric indexes

End
