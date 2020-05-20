// (7* (cornerNum)) - 1 = last pixel of cornerNum

//============================================================================================
//horizontal ring segments starting at the base corner of the dodecahedron and moving up to the top corner

segmentSection ringSec0[] = { {0, 1}, {34, 1}, {35, 1} };
Segment ringSegment0 = { SIZE(ringSec0), ringSec0, true }; //numSections, section array pointer, direction

segmentSection ringSec1[] = { {1, 1}, {33, 1}, {36, 1} };
Segment ringSegment1 = { SIZE(ringSec1), ringSec1, true }; //numSections, section array pointer, direction

segmentSection ringSec2[] = { {2, 1}, {32, 1}, {37, 1} };
Segment ringSegment2 = { SIZE(ringSec2), ringSec2, true }; //numSections, section array pointer, direction

segmentSection ringSec3[] = { {3, 1}, {31, 1}, {38, 1} };
Segment ringSegment3 = { SIZE(ringSec3), ringSec3, true }; //numSections, section array pointer, direction

segmentSection ringSec4[] = { {4, 1}, {30, 1}, {39, 1} };
Segment ringSegment4 = { SIZE(ringSec4), ringSec4, true }; //numSections, section array pointer, direction

segmentSection ringSec5[] = { {5, 1}, {29, 1}, {40, 1} };
Segment ringSegment5 = { SIZE(ringSec5), ringSec5, true }; //numSections, section array pointer, direction

segmentSection ringSec6[] = { {6, 1}, {28, 1}, {41, 1} };
Segment ringSegment6 = { SIZE(ringSec6), ringSec6, true }; //numSections, section array pointer, direction
//==
segmentSection ringSec7[] = { {7, 1}, {27, 1}, {125, 1}, {139, 1}, {42, 1}, {62, 1}};
Segment ringSegment7 = { SIZE(ringSec7), ringSec7, true }; //numSections, section array pointer, direction

segmentSection ringSec8[] = { {8, 1}, {26, 1}, {124, 1}, {138, 1}, {43, 1}, {61, 1}};
Segment ringSegment8 = { SIZE(ringSec8), ringSec8, true }; //numSections, section array pointer, direction

segmentSection ringSec9[] = { {9, 1}, {25, 1}, {123, 1}, {137, 1}, {44, 1}, {60, 1}};
Segment ringSegment9 = { SIZE(ringSec9), ringSec9, true }; //numSections, section array pointer, direction

segmentSection ringSec10[] = { {10, 1}, {24, 1}, {122, 1}, {136, 1}, {45, 1}, {59, 1}};
Segment ringSegment10 = { SIZE(ringSec10), ringSec10, true }; //numSections, section array pointer, direction

segmentSection ringSec11[] = { {11, 1}, {23, 1}, {121, 1}, {135, 1}, {46, 1}, {58, 1}};
Segment ringSegment11 = { SIZE(ringSec11), ringSec11, true }; //numSections, section array pointer, direction

segmentSection ringSec12[] = { {12, 1}, {22, 1}, {120, 1}, {134, 1}, {47, 1}, {57, 1}};
Segment ringSegment12 = { SIZE(ringSec12), ringSec12, true }; //numSections, section array pointer, direction

segmentSection ringSec13[] = { {13, 1}, {21, 1}, {119, 1}, {133, 1}, {48, 1}, {56, 1}};
Segment ringSegment13 = { SIZE(ringSec13), ringSec13, true }; //numSections, section array pointer, direction
//==
segmentSection ringSec14[] = { {14, 7}, {126, 7}, {49, 7}};
Segment ringSegment14 = { SIZE(ringSec14), ringSec14, true }; //numSections, section array pointer, direction
//==
segmentSection ringSec15[] = { {83, 1}, {104, 1}, {118, 1}, {202, 1}, {140, 1}, {63, 1}};
Segment ringSegment15 = { SIZE(ringSec15), ringSec15, true }; //numSections, section array pointer, direction

segmentSection ringSec16[] = { {82, 1}, {103, 1}, {117, 1}, {201, 1}, {141, 1}, {64, 1}};
Segment ringSegment16 = { SIZE(ringSec16), ringSec16, true }; //numSections, section array pointer, direction

segmentSection ringSec17[] = { {81, 1}, {102, 1}, {116, 1}, {200, 1}, {142, 1}, {65, 1}};
Segment ringSegment17 = { SIZE(ringSec17), ringSec17, true }; //numSections, section array pointer, direction

segmentSection ringSec18[] = { {80, 1}, {101, 1}, {115, 1}, {199, 1}, {143, 1}, {66, 1}};
Segment ringSegment18 = { SIZE(ringSec18), ringSec18, true }; //numSections, section array pointer, direction

segmentSection ringSec19[] = { {79, 1}, {100, 1}, {114, 1}, {198, 1}, {144, 1}, {67, 1}};
Segment ringSegment19 = { SIZE(ringSec19), ringSec19, true }; //numSections, section array pointer, direction

segmentSection ringSec20[] = { {78, 1}, {99, 1}, {113, 1}, {197, 1}, {145, 1}, {68, 1}};
Segment ringSegment20 = { SIZE(ringSec20), ringSec20, true }; //numSections, section array pointer, direction

segmentSection ringSec21[] = { {77, 1}, {98, 1}, {112, 1}, {196, 1}, {146, 1}, {69, 1}};
Segment ringSegment21 = { SIZE(ringSec21), ringSec21, true }; //numSections, section array pointer, direction
//==
segmentSection ringSec22[] = { {105, 7}, {203, 7}, {70, 7}};
Segment ringSegment22 = { SIZE(ringSec22), ringSec22, true }; //numSections, section array pointer, direction
//==
segmentSection ringSec23[] = { {84, 1}, {97, 1}, {188, 1}, {195, 1}, {147, 1}, {160, 1}};
Segment ringSegment23 = { SIZE(ringSec23), ringSec23, true }; //numSections, section array pointer, direction

segmentSection ringSec24[] = { {85, 1}, {96, 1}, {187, 1}, {194, 1}, {148, 1}, {159, 1}};
Segment ringSegment24 = { SIZE(ringSec24), ringSec24, true }; //numSections, section array pointer, direction

segmentSection ringSec25[] = { {86, 1}, {95, 1}, {186, 1}, {193, 1}, {149, 1}, {158, 1}};
Segment ringSegment25 = { SIZE(ringSec25), ringSec25, true }; //numSections, section array pointer, direction

segmentSection ringSec26[] = { {87, 1}, {94, 1}, {185, 1}, {192, 1}, {150, 1}, {157, 1}};
Segment ringSegment26 = { SIZE(ringSec26), ringSec26, true }; //numSections, section array pointer, direction

segmentSection ringSec27[] = { {88, 1}, {93, 1}, {184, 1}, {191, 1}, {151, 1}, {156, 1}};
Segment ringSegment27 = { SIZE(ringSec27), ringSec27, true }; //numSections, section array pointer, direction

segmentSection ringSec28[] = { {89, 1}, {92, 1}, {183, 1}, {190, 1}, {152, 1}, {155, 1}};
Segment ringSegment28 = { SIZE(ringSec28), ringSec28, true }; //numSections, section array pointer, direction

segmentSection ringSec29[] = { {90, 1}, {91, 1}, {182, 1}, {189, 1}, {153, 1}, {154, 1}};
Segment ringSegment29 = { SIZE(ringSec29), ringSec29, true }; //numSections, section array pointer, direction
//==
segmentSection ringSec30[] = { {174, 1}, {181, 1}, {161, 1} };
Segment ringSegment30 = { SIZE(ringSec30), ringSec30, true }; //numSections, section array pointer, direction

segmentSection ringSec31[] = { {173, 1}, {180, 1}, {162, 1} };
Segment ringSegment31 = { SIZE(ringSec31), ringSec31, true }; //numSections, section array pointer, direction

segmentSection ringSec32[] = { {172, 1}, {179, 1}, {163, 1} };
Segment ringSegment32 = { SIZE(ringSec32), ringSec32, true }; //numSections, section array pointer, direction

segmentSection ringSec33[] = { {171, 1}, {178, 1}, {164, 1} };
Segment ringSegment33 = { SIZE(ringSec33), ringSec33, true }; //numSections, section array pointer, direction

segmentSection ringSec34[] = { {170, 1}, {177, 1}, {165, 1} };
Segment ringSegment34 = { SIZE(ringSec34), ringSec34, true }; //numSections, section array pointer, direction

segmentSection ringSec35[] = { {169, 1}, {176, 1}, {166, 1} };
Segment ringSegment35 = { SIZE(ringSec35), ringSec35, true }; //numSections, section array pointer, direction

segmentSection ringSec36[] = { {168, 1}, {175, 1}, {167, 1} };
Segment ringSegment36 = { SIZE(ringSec36), ringSec36, true }; //numSections, section array pointer, direction

Segment *rings_arr[] = {
  &ringSegment0 , &ringSegment1, &ringSegment2, &ringSegment3, &ringSegment4, &ringSegment5, &ringSegment6,
  &ringSegment7, &ringSegment8, &ringSegment9, &ringSegment10, &ringSegment11, &ringSegment12, &ringSegment13,
  &ringSegment14,
  &ringSegment15, &ringSegment16, &ringSegment17, &ringSegment18, &ringSegment19, &ringSegment20, &ringSegment21,
  &ringSegment22,
  &ringSegment23, &ringSegment24, &ringSegment25, &ringSegment26, &ringSegment27, &ringSegment28, &ringSegment29,
  &ringSegment30, &ringSegment31, &ringSegment32, &ringSegment33, &ringSegment34, &ringSegment35, &ringSegment36,
};
SegmentSet ringSegments = { SIZE(rings_arr), rings_arr };

//=====================================================

//segments for each edge of the dodecahedron
//numbering matches that of printed diagram
//ie line1 => edge 1 on the diagram
segmentSection line1 = {0, 7};
segmentSection line2 = {7, 7};
segmentSection line3 = {14, 7};
segmentSection line4 = {21, 7};
segmentSection line5 = {28, 7};
segmentSection line6 = {35, 7};
segmentSection line7 = {42, 7};
segmentSection line8 = {49, 7};
segmentSection line9 = {56, 7};
segmentSection line10 = {63, 7};
segmentSection line11 = {70, 7};
segmentSection line12 = {77, 7};
segmentSection line13 = {84, 7};
segmentSection line14 = {91, 7};
segmentSection line15 = {98, 7};
segmentSection line16 = {105, 7};
segmentSection line17 = {112, 7};
segmentSection line18 = {119, 7};
segmentSection line19 = {126, 7};
segmentSection line20 = {133, 7};
segmentSection line21 = {140, 7};
segmentSection line22 = {147, 7};
segmentSection line23 = {154, 7};
segmentSection line24 = {161, 7};
segmentSection line25 = {168, 7};
segmentSection line26 = {175, 7};
segmentSection line27 = {182, 7};
segmentSection line28 = {189, 7};
segmentSection line29 = {196, 7};
segmentSection line30 = {203, 7};

//lines with reversed directions based on printed diagram
segmentSection lineRev1 = {6, -7};
segmentSection lineRev2 = {13, -7};
segmentSection lineRev3 = {20, -7};
segmentSection lineRev4 = {27, -7};
segmentSection lineRev5 = {34, -7};
segmentSection lineRev6 = {41, -7};
segmentSection lineRev7 = {48, -7};
segmentSection lineRev8 = {55, -7};
segmentSection lineRev9 = {62, -7};
segmentSection lineRev10 = {69,-7};
segmentSection lineRev11 = {76, -7};
segmentSection lineRev12 = {83, -7};
segmentSection lineRev13 = {90, -7};
segmentSection lineRev14 = {97, -7};
segmentSection lineRev15 = {104, -7};
segmentSection lineRev16 = {111, -7};
segmentSection lineRev17 = {118, -7};
segmentSection lineRev18 = {125, -7};
segmentSection lineRev19 = {132, -7};
segmentSection lineRev20 = {139, -7};
segmentSection lineRev21 = {146, -7};
segmentSection lineRev22 = {153, -7};
segmentSection lineRev23 = {160, -7};
segmentSection lineRev24 = {167, -7};
segmentSection lineRev25 = {174, -7};
segmentSection lineRev26 = {181, -7};
segmentSection lineRev27 = {188, -7};
segmentSection lineRev28 = {195, -7};
segmentSection lineRev29 = {202, -7};
segmentSection lineRev30 = {209, -7};

//===============================
// vertical lines from base corner to top
//some lines overlap

segmentSection vertLineSec0[] = { lineRev5, lineRev4, lineRev15, lineRev14, lineRev25 }; //line5, line4, line15, line14, line25
Segment vertSegment0 = { SIZE(vertLineSec0), vertLineSec0, true }; //numSections, section array pointer, direction 

segmentSection vertLineSec1[] = { lineRev5, lineRev18, lineRev17, lineRev27, lineRev26 };
Segment vertSegment1 = { SIZE(vertLineSec1), vertLineSec1, true }; //numSections, section array pointer, direction 

segmentSection vertLineSec2[] = { line6, lineRev20, lineRev29, lineRev28, lineRev26 };
Segment vertSegment2 = { SIZE(vertLineSec2), vertLineSec2, true }; //numSections, section array pointer, direction 

segmentSection vertLineSec3[] = { line6, line7, line21, line22, line24 };
Segment vertSegment3 = { SIZE(vertLineSec3), vertLineSec3, true }; //numSections, section array pointer, direction 

segmentSection vertLineSec4[] = { line1, lineRev9, line10, lineRev23, line24 };
Segment vertSegment4 = { SIZE(vertLineSec4), vertLineSec4, true }; //numSections, section array pointer, direction 

segmentSection vertLineSec5[] = { line1, line2, lineRev12, line13, lineRev25 };
Segment vertSegment5 = { SIZE(vertLineSec5), vertLineSec5, true }; //numSections, section array pointer, direction 

Segment *vertLine_arr[] = { &vertSegment0, &vertSegment1, &vertSegment2, &vertSegment3, &vertSegment4, &vertSegment5 };
SegmentSet vertLineSegments = { SIZE(vertLine_arr), vertLine_arr };

//===================================================

//Hexes going clockwise, starting at base

segmentSection hexSec0[] = { line1, line2, line3, line4, line5 }; 
Segment hexSegment0 = { SIZE(hexSec0), hexSec0, true }; //numSections, section array pointer, direction 

segmentSection hexSec1[] = { line6, line7, line8, line9, lineRev1 }; 
Segment hexSegment1 = { SIZE(hexSec1), hexSec1, true }; //numSections, section array pointer, direction 

segmentSection hexSec2[] = { lineRev5, lineRev18, line19, line20, lineRev6 };
Segment hexSegment2 = { SIZE(hexSec2), hexSec2, true }; //numSections, section array pointer, direction 

segmentSection hexSec3[] = { line18, lineRev4, lineRev15, line16, line17 };
Segment hexSegment3 = { SIZE(hexSec3), hexSec3, true }; //numSections, section array pointer, direction 

segmentSection hexSec4[] = { lineRev3, lineRev12, line13, line14, line15 };
Segment hexSegment4 = { SIZE(hexSec4), hexSec4, true }; //numSections, section array pointer, direction 

segmentSection hexSec5[] = { lineRev2, lineRev9, line10, line11, line12 };
Segment hexSegment5 = { SIZE(hexSec5), hexSec5, true }; //numSections, section array pointer, direction 

segmentSection hexSec6[] = { lineRev8, line21, line22, line23, lineRev10 };
Segment hexSegment6 = { SIZE(hexSec6), hexSec6, true }; //numSections, section array pointer, direction 

segmentSection hexSec7[] = { lineRev7, lineRev20, lineRev29, line30, lineRev21 };
Segment hexSegment7 = { SIZE(hexSec7), hexSec7, true }; //numSections, section array pointer, direction 

segmentSection hexSec8[] = { lineRev19, lineRev17, lineRev27, line28, line29 };
Segment hexSegment8 = { SIZE(hexSec8), hexSec8, true }; //numSections, section array pointer, direction 

segmentSection hexSec9[] = { lineRev16, lineRev14, lineRev25, line26, line27 };
Segment hexSegment9 = { SIZE(hexSec9), hexSec9, true }; //numSections, section array pointer, direction 

segmentSection hexSec10[] = { lineRev11, lineRev23, line24, line25, lineRev13 };
Segment hexSegment10 = { SIZE(hexSec10), hexSec10, true }; //numSections, section array pointer, direction 

segmentSection hexSec11[] = { lineRev30, lineRev28, lineRev26, lineRev24, lineRev22 };
Segment hexSegment11 = { SIZE(hexSec11), hexSec11, true }; //numSections, section array pointer, direction 

Segment *hex_arr[] = { &hexSegment0, &hexSegment1, &hexSegment2, &hexSegment3, &hexSegment4, &hexSegment6, &hexSegment8, &hexSegment10, &hexSegment11 };
SegmentSet hexSegments = { SIZE(hex_arr), hex_arr };

//============================================

segmentSection horizSec0[] = { line3, line4, lineRev18, line19, line20, line7, line8, line9, line2 }; 
Segment horizSegment0 = { SIZE(horizSec0), horizSec0, true }; //numSections, section array pointer, direction

segmentSection horizSec1[] = { line13, line14, line16, lineRev27, line28, line30, line22, line23, line11 }; 
Segment horizSegment1 = { SIZE(horizSec1), horizSec1, true }; //numSections, section array pointer, direction

Segment *horiz_arr[] = { &horizSegment0, &horizSegment1 };
SegmentSet horizSegments = { SIZE(horiz_arr), horiz_arr };

//================================================
