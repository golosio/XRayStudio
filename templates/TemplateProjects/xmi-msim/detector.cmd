; Detector array parameter file
;
Device Detector                   ; Device name
;SourceName Sample               ; Source input device name
NPixels 1 1			; Pixel number (NX x NY)
PixelSize 0.79788452 0.79788452 ; Pixel Size (cm) 0.5 cm2 active detector area
Shape 1	       			; Pixel shape (0 rectangular, 1 elliptical)
;dOmegaLim 1e-2			; Cut on dOmega (default = 2*PI)
X  -2  0  0			; detector center coordinates x, y, z
				; Detector orientation :
uk  1  0  0			; z direction (normal to the screen)
ui   0 -1  0			; x direction
ExpTime 1      	   			; Exposure time (sec)
PhotonNum 2000			; Multiplicity of simulated events per pixel
RandomPixelFlag 1		; Enable random point on pixels (0/1)
PoissonFlag 0			; Enable poisson statistic on pix. counts (0/1)
RoundFlag 0 			; Round pixel counts to integer (0/1)
HeaderFlag 1                    ; Use header in output file (0/1)
;RunningFasterFlag 0		; Columns(0) or rows(1) running faster 
PixelType 2	   		; Pixel content type:
	  			; 0: fluence, 1: energy fluence,
				; 2: fluence(E), 3: energy fluence(E)
Emin 0				; Emin
Emax 40				; Emax
NBins 2000			; Nbins
SaturateEmin 0			; Saturate energies lower than Emin (0/1)
SaturateEmax 0			; Saturate energies greater than Emax (0/1)
;Rotate 0 0 0 1 0 0 -20		; rotation around axis x, u, angle theta
;Rotate 0 0 0 0 0 1 -30		; rotation around axis x, u, angle theta

;XMI-MSIM extras
CompositionName Composition
CrystalPhase Crystal
WindowPhase Window
CrystalThickness 0.035
;PulseWidth 2E-09

End
