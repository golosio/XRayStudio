; Source position/orientation file
;
Device Source                   ; Device name
;SpectrumName Spectrum		; Spectrum input device name
X 0.94 -0.342 0			; source x, y, z
; Source orientation :
uk -0.94   0.34	0		; z direction (main source direction)
ui 0 0 1   			; x direction
Divergence 4e-1	4e-1		; beam divergence (thetax, thetay)
Size 0.05 0.05 0.05 		; source size (sigmax sigmay, sigmaz, cm) in
       	 			; local coordinate system
;Rotate 0 0 0 1 0 0 -20		; rotation around axis x, u, angle theta
;Rotate 0 0 0 0 0 1 -30		; rotation around axis x, u, angle theta

End
