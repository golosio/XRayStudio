; Quadric array file
;
Device QuadricArray		; Device name

;external ring
CylinderY CY1 0 0 5 5
Plane PE1 0  0.4002  0  0  1  0
Plane PE2 0 -0.4002  0  0 -1  0
CylinderY CY2 0 0 4.001 4.001
Plane PE3 0  0.4001  0  0  1  0
Plane PE4 0 -0.4001  0  0 -1  0
;
CylinderY CY3 0 0 4 4
;
;1st cylinder
CylinderX CX1 0 0 0.4 0.4
Plane PR1 2 0 0  -1 0 0
;2nd cylinder
CylinderX CX2 0 0 0.4 0.4
Rotate 0 0 0 0 1 0 30
Plane PR2 2 0 0 -1 0 0
Rotate 0 0 0 0 1 0 30
;3rd cylinder
CylinderX CX3 0 0 0.4 0.4
Rotate 0 0 0 0 1 0 60
Plane PR3 2 0 0 -1 0 0
Rotate 0 0 0 0 1 0 60
;4th cylinder
CylinderX CX4 0 0 0.4 0.4
Rotate 0 0 0 0 1 0 90
Plane PR4 2 0 0 -1 0 0
Rotate 0 0 0 0 1 0 90
;5th cylinder
CylinderX CX5 0 0 0.4 0.4
Rotate 0 0 0 0 1 0 120
Plane PR5 2 0 0 -1 0 0
Rotate 0 0 0 0 1 0 120
;6th cylinder
CylinderX CX6 0 0 0.4 0.4
Rotate 0 0 0 0 1 0 150
Plane PR6 2 0 0 -1 0 0
Rotate 0 0 0 0 1 0 150
;7th cylinder
CylinderX CX7 0 0 0.4 0.4
Rotate 0 0 0 0 1 0 180
Plane PR7 2 0 0 -1 0 0
Rotate 0 0 0 0 1 0 180
;8th cylinder
CylinderX CX8 0 0 0.4 0.4
Rotate 0 0 0 0 1 0 210
Plane PR8 2 0 0 -1 0 0
Rotate 0 0 0 0 1 0 210
;9th cylinder
CylinderX CX9 0 0 0.4 0.4
Rotate 0 0 0 0 1 0 240
Plane PR9 2 0 0 -1 0 0
Rotate 0 0 0 0 1 0 240
;10th cylinder
CylinderX CX10 0 0 0.4 0.4
Rotate 0 0 0 0 1 0 270
Plane PR10 2 0 0 -1 0 0
Rotate 0 0 0 0 1 0 270
;11th cylinder
CylinderX CX11 0 0 0.4 0.4
Rotate 0 0 0 0 1 0 300
Plane PR11 2 0 0 -1 0 0
Rotate 0 0 0 0 1 0 300
;12th cylinder
CylinderX CX12 0 0 0.4 0.4
Rotate 0 0 0 0 1 0 330
Plane PR12 2 0 0 -1 0 0
Rotate 0 0 0 0 1 0 330

;internal ring
CylinderY CY4 0 0 1.99 1.99
Plane PI1 0  0.4  0  0  1  0
Plane PI2 0 -0.4  0  0 -1  0
CylinderY CY5 0 0 1.3 1.3
Plane PI3 0  0.3999  0  0  1  0
Plane PI4 0 -0.3999  0  0 -1  0

RotateAll 0 0 0 0 0 1  30
RotateAll 0 0 0 1 0 0 20

End
