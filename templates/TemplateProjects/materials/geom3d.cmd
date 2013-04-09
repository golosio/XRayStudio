; 3D object geometric description file
;
Device Geom3D				; Device name
;QArrName QuadricArray		; Quadric array input device name
;CompName Composition		; Composition input device name

Object TopBeam			; Top beam
PMMA Vacuum			; Phase in, phase out
6				; Number of quadrics for object 0
PZ4 PZp PXm PXp PYm PYp		; Quadric names

Object LowBeam	    		; Lower beam
PMMA Vacuum			; Phase in, phase out
6				; Number of quadrics for object 0
PZm PZ1 PXm PXp PYm PYp		; Quadric names

Object LeftBeam	    		; Left beam
PMMA Vacuum			; Phase in, phase out
6				; Number of quadrics for object 0
PXm PX1 PZ2 PZ3 PYm PYp		; Quadric names

Object RightBeam	    	; Right beam
PMMA Vacuum			; Phase in, phase out
6				; Number of quadrics for object 0
PX2 PXp PZ2 PZ3 PYm PYp		; Quadric names


Object CylPMMA	    		; 1st cylinder: PMMA (Polymethyl methacrylate)
PMMA Vacuum			; Phase in, phase out
3				; Number of quadrics for object 0
C1 PZ2 PZ3			; Quadric names

Object CylWater			; 2nd cylinder: Water
Water Vacuum			; Phase in, phase out
3				; Number of quadrics for object 0
C2 PZ2 PZ3			; Quadric names

Object CylAdipe	    		; 3rd cylinder: Adipose Tissue
Adipe Vacuum			; Phase in, phase out
3				; Number of quadrics for object 0
C3 PZ2 PZ3			; Quadric names

Object CylBone	    		; 4th cylinder: B-100 Bone-Equivalent Plastic
Bone Vacuum			; Phase in, phase out
3				; Number of quadrics for object 0
C4 PZ2 PZ3			; Quadric names

End
