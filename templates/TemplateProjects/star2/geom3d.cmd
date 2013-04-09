; 3D object geometric description file
;
Device Geom3D			; Device name
;QArrName QuadricArray		; Quadric array input device name
;CompName Composition		; Composition input device name

Object PentExt			; 3d Object: external pentagon
PMMA Vacuum			; Phase in, phase out
7				; Number of quadrics
P1 P3 P5 P7 P9 P16 P17		; Quadric names


Object Triang1 	   		; 3d Object: internal (empty) triangle
Vacuum PMMA			; Phase in, phase out
5				; Number of quadrics
P2 P13 P14 P18 P19		; Quadric names


Object Triang2 	   		; 3d Object: internal (empty) triangle
Vacuum PMMA			; Phase in, phase out
5				; Number of quadrics
P4 P14 P15 P18 P19		; Quadric names


Object Triang3 	   		; 3d Object: internal (empty) triangle
Vacuum PMMA			; Phase in, phase out
5				; Number of quadrics
P6 P15 P11 P18 P19		; Quadric names


Object Triang4 	   		; 3d Object: internal (empty) triangle
Vacuum PMMA			; Phase in, phase out
5				; Number of quadrics
P8 P11 P12 P18 P19		; Quadric names


Object Triang5 	   		; 3d Object: internal (empty) triangle
Vacuum PMMA			; Phase in, phase out
5				; Number of quadrics
P10 P12 P13 P18 P19		; Quadric names

End
