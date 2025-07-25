#!/usr/bin/env wolframscript
(* ::Package:: *)

lib=LibraryFunctionLoad["/Users/alessandromastrofini/LocalFiles/VirtualElements/Earcut/build/Triangulate.dylib","TriangulateEarClipping",{{Real,2},{Integer,1}},{Integer,2}]


pts=0.015+{{0.9`,0},{0.9`,0.15`},{0.25`,0.15`},{0.25`,0.65`},{0.9`,0.65`},{0.9`,0.8`},{0.1`,0.8`},{0.1`,0.`}};
conn={1,2,3,4,5,6,7,8};
tri=lib[pts,conn]
