; Source position/orientation file
;
;source				; Device type
Device Source			; Device name
;SpectrumName Spectrum		; Spectrum input device name
X 0 -100  0			; source x, y, z
; Source orientation :
uk 0 1 0			; z direction (main source direction)
ui -1 0 0               	; x direction
;Divergence 1e-1	1e-1		; beam divergence (thetax, thetay)
Size 0.05 0.05 0.05 		; source size (sigmax sigmay, sigmaz, cm) in
       	 			; local coordinate system
;Rotate 0 0 0 1 0 0 -20		; rotation around axis x, u, angle theta
;Rotate 0 0 0 0 0 1 -30		; rotation around axis x, u, angle theta

End
