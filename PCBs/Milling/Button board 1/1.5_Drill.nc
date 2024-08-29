(G-CODE GENERATED BY FLATCAM v8.994 - www.flatcam.org - Version Date: 2020/11/7)

(Name: Drill_PTH_Through.DRL_mill_1_cnc)
(Type: G-code from Geometry)
(Units: MM)

(Created on Thursday, 29 August 2024 at 13:04)

(This preprocessor is the default preprocessor used by FlatCAM.)
(It is made to work with MACH3 compatible motion controllers.)

(TOOL DIAMETER: 1.501 mm)
(Feedrate_XY: 120.0 mm/min)
(Feedrate_Z: 60.0 mm/min)
(Feedrate rapids 1500.0 mm/min)

(Z_Cut: -2.4 mm)
(DepthPerCut: 0.8 mm <=>3 passes)
(Z_Move: 2.0 mm)
(Z Start: None mm)
(Z End: 15.0 mm)
(X,Y End: None mm)
(Steps per circle: 64)
(Preprocessor Geometry: default)

(X range:   33.5767 ...   93.6777  mm)
(Y range:    5.4610 ...   10.5410  mm)

(Spindle Speed: 0.0 RPM)
G21
G90
G94

G01 F120.00

M5
G00 Z15.0000
G00 X0.0000 Y0.0000
T1
M6    
(MSG, Change to Tool Dia = 1.5010)
M0
G00 Z15.0000

M03
G01 F120.00
G00 X33.5767 Y5.4610
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X33.5767 Y5.4610
G01 X33.5767 Y5.4610
G01 X33.5767 Y5.4610
G01 X33.5767 Y5.4610
G00 X33.5767 Y5.4610
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X33.5767 Y5.4610
G01 X33.5767 Y5.4610
G01 X33.5767 Y5.4610
G01 X33.5767 Y5.4610
G00 X33.5767 Y5.4610
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X33.5767 Y5.4610
G01 X33.5767 Y5.4610
G01 X33.5767 Y5.4610
G01 X33.5767 Y5.4610
G00 Z2.0000
G00 X33.5767 Y10.5410
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X33.5767 Y10.5410
G01 X33.5767 Y10.5410
G01 X33.5767 Y10.5410
G01 X33.5767 Y10.5410
G00 X33.5767 Y10.5410
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X33.5767 Y10.5410
G01 X33.5767 Y10.5410
G01 X33.5767 Y10.5410
G01 X33.5767 Y10.5410
G00 X33.5767 Y10.5410
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X33.5767 Y10.5410
G01 X33.5767 Y10.5410
G01 X33.5767 Y10.5410
G01 X33.5767 Y10.5410
G00 Z2.0000
G00 X46.0787 Y10.5410
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X46.0787 Y10.5410
G01 X46.0787 Y10.5410
G01 X46.0787 Y10.5410
G01 X46.0787 Y10.5410
G00 X46.0787 Y10.5410
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X46.0787 Y10.5410
G01 X46.0787 Y10.5410
G01 X46.0787 Y10.5410
G01 X46.0787 Y10.5410
G00 X46.0787 Y10.5410
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X46.0787 Y10.5410
G01 X46.0787 Y10.5410
G01 X46.0787 Y10.5410
G01 X46.0787 Y10.5410
G00 Z2.0000
G00 X46.0787 Y5.4610
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X46.0787 Y5.4610
G01 X46.0787 Y5.4610
G01 X46.0787 Y5.4610
G01 X46.0787 Y5.4610
G00 X46.0787 Y5.4610
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X46.0787 Y5.4610
G01 X46.0787 Y5.4610
G01 X46.0787 Y5.4610
G01 X46.0787 Y5.4610
G00 X46.0787 Y5.4610
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X46.0787 Y5.4610
G01 X46.0787 Y5.4610
G01 X46.0787 Y5.4610
G01 X46.0787 Y5.4610
G00 Z2.0000
G00 X57.3767 Y5.4610
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X57.3767 Y5.4610
G01 X57.3767 Y5.4610
G01 X57.3767 Y5.4610
G01 X57.3767 Y5.4610
G00 X57.3767 Y5.4610
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X57.3767 Y5.4610
G01 X57.3767 Y5.4610
G01 X57.3767 Y5.4610
G01 X57.3767 Y5.4610
G00 X57.3767 Y5.4610
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X57.3767 Y5.4610
G01 X57.3767 Y5.4610
G01 X57.3767 Y5.4610
G01 X57.3767 Y5.4610
G00 Z2.0000
G00 X57.3767 Y10.5410
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X57.3767 Y10.5410
G01 X57.3767 Y10.5410
G01 X57.3767 Y10.5410
G01 X57.3767 Y10.5410
G00 X57.3767 Y10.5410
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X57.3767 Y10.5410
G01 X57.3767 Y10.5410
G01 X57.3767 Y10.5410
G01 X57.3767 Y10.5410
G00 X57.3767 Y10.5410
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X57.3767 Y10.5410
G01 X57.3767 Y10.5410
G01 X57.3767 Y10.5410
G01 X57.3767 Y10.5410
G00 Z2.0000
G00 X69.8787 Y10.5410
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X69.8787 Y10.5410
G01 X69.8787 Y10.5410
G01 X69.8787 Y10.5410
G01 X69.8787 Y10.5410
G00 X69.8787 Y10.5410
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X69.8787 Y10.5410
G01 X69.8787 Y10.5410
G01 X69.8787 Y10.5410
G01 X69.8787 Y10.5410
G00 X69.8787 Y10.5410
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X69.8787 Y10.5410
G01 X69.8787 Y10.5410
G01 X69.8787 Y10.5410
G01 X69.8787 Y10.5410
G00 Z2.0000
G00 X69.8787 Y5.4610
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X69.8787 Y5.4610
G01 X69.8787 Y5.4610
G01 X69.8787 Y5.4610
G01 X69.8787 Y5.4610
G00 X69.8787 Y5.4610
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X69.8787 Y5.4610
G01 X69.8787 Y5.4610
G01 X69.8787 Y5.4610
G01 X69.8787 Y5.4610
G00 X69.8787 Y5.4610
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X69.8787 Y5.4610
G01 X69.8787 Y5.4610
G01 X69.8787 Y5.4610
G01 X69.8787 Y5.4610
G00 Z2.0000
G00 X81.1757 Y5.4610
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X81.1757 Y5.4610
G01 X81.1757 Y5.4610
G01 X81.1757 Y5.4610
G01 X81.1757 Y5.4610
G00 X81.1757 Y5.4610
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X81.1757 Y5.4610
G01 X81.1757 Y5.4610
G01 X81.1757 Y5.4610
G01 X81.1757 Y5.4610
G00 X81.1757 Y5.4610
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X81.1757 Y5.4610
G01 X81.1757 Y5.4610
G01 X81.1757 Y5.4610
G01 X81.1757 Y5.4610
G00 Z2.0000
G00 X81.1757 Y10.5410
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X81.1757 Y10.5410
G01 X81.1757 Y10.5410
G01 X81.1757 Y10.5410
G01 X81.1757 Y10.5410
G00 X81.1757 Y10.5410
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X81.1757 Y10.5410
G01 X81.1757 Y10.5410
G01 X81.1757 Y10.5410
G01 X81.1757 Y10.5410
G00 X81.1757 Y10.5410
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X81.1757 Y10.5410
G01 X81.1757 Y10.5410
G01 X81.1757 Y10.5410
G01 X81.1757 Y10.5410
G00 Z2.0000
G00 X93.6777 Y10.5410
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X93.6777 Y10.5410
G01 X93.6777 Y10.5410
G01 X93.6777 Y10.5410
G01 X93.6777 Y10.5410
G00 X93.6777 Y10.5410
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X93.6777 Y10.5410
G01 X93.6777 Y10.5410
G01 X93.6777 Y10.5410
G01 X93.6777 Y10.5410
G00 X93.6777 Y10.5410
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X93.6777 Y10.5410
G01 X93.6777 Y10.5410
G01 X93.6777 Y10.5410
G01 X93.6777 Y10.5410
G00 Z2.0000
G00 X93.6777 Y5.4610
G01 F60.00
G01 Z-0.8000
G01 F120.00
G01 X93.6777 Y5.4610
G01 X93.6777 Y5.4610
G01 X93.6777 Y5.4610
G01 X93.6777 Y5.4610
G00 X93.6777 Y5.4610
G01 F60.00
G01 Z-1.6000
G01 F120.00
G01 X93.6777 Y5.4610
G01 X93.6777 Y5.4610
G01 X93.6777 Y5.4610
G01 X93.6777 Y5.4610
G00 X93.6777 Y5.4610
G01 F60.00
G01 Z-2.4000
G01 F120.00
G01 X93.6777 Y5.4610
G01 X93.6777 Y5.4610
G01 X93.6777 Y5.4610
G01 X93.6777 Y5.4610
G00 Z2.0000
M05
G00 Z2.0000
G00 Z15.00

