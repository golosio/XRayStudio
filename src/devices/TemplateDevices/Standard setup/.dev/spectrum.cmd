; Spectrum file
;
;spectrum		; Device type
Device Spectrum		; Device name
PolarizedFlag 0		; unpolarized/polarized beam (0/1)
LoopFlag 1		; 0: extract random energies on the whole spectrum
			; 1: loop on all lines and sampling points
ContinuousPhotonNum 1	; Multiplicity of events for each interval in spectrum 
LinePhotonNum 1		; Multiplicity of events for each line in the spectrum
RandomEneFlag 1		; enable random energy on each interval (0/1)
Lines	      		; discrete energy lines of the spectrum
1			; Number of lines in the spectrum
;			Energy Lines :
50 0.0 1e10		; Energy (keV) , sigma (keV) , intensity (photons/sec)

End
