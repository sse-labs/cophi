; ModuleID = 'buncha_classes.ll'
source_filename = "buncha_classes.cpp"
target datalayout = "e-m:e-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128"
target triple = "aarch64-unknown-linux-gnu"

%class.A = type { i32 (...)** }
%class.B = type { %class.A }
%class.C = type { %class.A }
%class.F = type { i32 (...)** }
%class.D = type { %class.B, %class.C }
%class.E = type { %class.D.base, %class.C }
%class.D.base = type { %class.B }
%class.G = type { %class.F }
%class.H = type { %class.G }

$_ZN1CC1Ev = comdat any

$_ZN1BC1Ev = comdat any

$_ZN1DC1Ev = comdat any

$_ZN1EC1Ev = comdat any

$_ZN1GC1Ev = comdat any

$_ZN1HC1Ev = comdat any

$_ZN1AC2Ev = comdat any

$_ZN1C3fooEv = comdat any

$_ZN1CD1Ev = comdat any

$_ZN1CD0Ev = comdat any

$_ZN1A3fooEv = comdat any

$_ZN1AD2Ev = comdat any

$_ZN1AD0Ev = comdat any

$_ZTv0_n24_N1C3fooEv = comdat any

$_ZN1CD2Ev = comdat any

$_ZTv0_n32_N1CD1Ev = comdat any

$_ZTv0_n32_N1CD0Ev = comdat any

$_ZN1B3fooEv = comdat any

$_ZN1BD1Ev = comdat any

$_ZN1BD0Ev = comdat any

$_ZTv0_n24_N1B3fooEv = comdat any

$_ZN1BD2Ev = comdat any

$_ZTv0_n32_N1BD1Ev = comdat any

$_ZTv0_n32_N1BD0Ev = comdat any

$_ZN1BC2Ev = comdat any

$_ZN1CC2Ev = comdat any

$_ZN1D3fooEv = comdat any

$_ZN1DD1Ev = comdat any

$_ZN1DD0Ev = comdat any

$_ZTv0_n24_N1D3fooEv = comdat any

$_ZTv0_n32_N1DD1Ev = comdat any

$_ZTv0_n32_N1DD0Ev = comdat any

$_ZN1DD2Ev = comdat any

$_ZN1DC2Ev = comdat any

$_ZN1E3fooEv = comdat any

$_ZN1ED1Ev = comdat any

$_ZN1ED0Ev = comdat any

$_ZTv0_n24_N1E3fooEv = comdat any

$_ZTv0_n32_N1ED1Ev = comdat any

$_ZTv0_n32_N1ED0Ev = comdat any

$_ZN1ED2Ev = comdat any

$_ZN1FC2Ev = comdat any

$_ZN1G3fooEv = comdat any

$_ZN1GD1Ev = comdat any

$_ZN1GD0Ev = comdat any

$_ZN1F3fooEv = comdat any

$_ZN1FD2Ev = comdat any

$_ZN1FD0Ev = comdat any

$_ZTv0_n24_N1G3fooEv = comdat any

$_ZN1GD2Ev = comdat any

$_ZTv0_n32_N1GD1Ev = comdat any

$_ZTv0_n32_N1GD0Ev = comdat any

$_ZN1GC2Ev = comdat any

$_ZN1H3fooEv = comdat any

$_ZN1HD1Ev = comdat any

$_ZN1HD0Ev = comdat any

$_ZTv0_n24_N1H3fooEv = comdat any

$_ZN1HD2Ev = comdat any

$_ZTv0_n32_N1HD1Ev = comdat any

$_ZTv0_n32_N1HD0Ev = comdat any

$_ZTV1C = comdat any

$_ZTT1C = comdat any

$_ZTS1C = comdat any

$_ZTS1A = comdat any

$_ZTI1A = comdat any

$_ZTI1C = comdat any

$_ZTV1A = comdat any

$_ZTV1B = comdat any

$_ZTT1B = comdat any

$_ZTS1B = comdat any

$_ZTI1B = comdat any

$_ZTV1D = comdat any

$_ZTT1D = comdat any

$_ZTC1D0_1B = comdat any

$_ZTC1D8_1C = comdat any

$_ZTS1D = comdat any

$_ZTI1D = comdat any

$_ZTV1E = comdat any

$_ZTT1E = comdat any

$_ZTC1E0_1D = comdat any

$_ZTC1E0_1B = comdat any

$_ZTC1E8_1C = comdat any

$_ZTS1E = comdat any

$_ZTI1E = comdat any

$_ZTV1G = comdat any

$_ZTT1G = comdat any

$_ZTS1G = comdat any

$_ZTS1F = comdat any

$_ZTI1F = comdat any

$_ZTI1G = comdat any

$_ZTV1F = comdat any

$_ZTV1H = comdat any

$_ZTT1H = comdat any

$_ZTC1H0_1G = comdat any

$_ZTS1H = comdat any

$_ZTI1H = comdat any

@_ZTV1C = linkonce_odr dso_local unnamed_addr constant { [8 x i8*] } { [8 x i8*] [i8* null, i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1C to i8*), i8* bitcast (void (%class.C*)* @_ZN1C3fooEv to i8*), i8* bitcast (void (%class.C*)* @_ZN1CD1Ev to i8*), i8* bitcast (void (%class.C*)* @_ZN1CD0Ev to i8*)] }, comdat, align 8
@_ZTT1C = linkonce_odr dso_local unnamed_addr constant [2 x i8*] [i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1C, i32 0, inrange i32 0, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1C, i32 0, inrange i32 0, i32 5) to i8*)], comdat, align 8
@_ZTVN10__cxxabiv121__vmi_class_type_infoE = external global i8*
@_ZTS1C = linkonce_odr dso_local constant [3 x i8] c"1C\00", comdat, align 1
@_ZTVN10__cxxabiv117__class_type_infoE = external global i8*
@_ZTS1A = linkonce_odr dso_local constant [3 x i8] c"1A\00", comdat, align 1
@_ZTI1A = linkonce_odr dso_local constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1A, i32 0, i32 0) }, comdat, align 8
@_ZTI1C = linkonce_odr dso_local constant { i8*, i8*, i32, i32, i8*, i64 } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv121__vmi_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1C, i32 0, i32 0), i32 0, i32 1, i8* bitcast ({ i8*, i8* }* @_ZTI1A to i8*), i64 -10237 }, comdat, align 8
@_ZTV1A = linkonce_odr dso_local unnamed_addr constant { [5 x i8*] } { [5 x i8*] [i8* null, i8* bitcast ({ i8*, i8* }* @_ZTI1A to i8*), i8* bitcast (void (%class.A*)* @_ZN1A3fooEv to i8*), i8* bitcast (void (%class.A*)* @_ZN1AD2Ev to i8*), i8* bitcast (void (%class.A*)* @_ZN1AD0Ev to i8*)] }, comdat, align 8
@_ZTV1B = linkonce_odr dso_local unnamed_addr constant { [8 x i8*] } { [8 x i8*] [i8* null, i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1B to i8*), i8* bitcast (void (%class.B*)* @_ZN1B3fooEv to i8*), i8* bitcast (void (%class.B*)* @_ZN1BD1Ev to i8*), i8* bitcast (void (%class.B*)* @_ZN1BD0Ev to i8*)] }, comdat, align 8
@_ZTT1B = linkonce_odr dso_local unnamed_addr constant [2 x i8*] [i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1B, i32 0, inrange i32 0, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1B, i32 0, inrange i32 0, i32 5) to i8*)], comdat, align 8
@_ZTS1B = linkonce_odr dso_local constant [3 x i8] c"1B\00", comdat, align 1
@_ZTI1B = linkonce_odr dso_local constant { i8*, i8*, i32, i32, i8*, i64 } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv121__vmi_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1B, i32 0, i32 0), i32 0, i32 1, i8* bitcast ({ i8*, i8* }* @_ZTI1A to i8*), i64 -10237 }, comdat, align 8
@_ZTV1D = linkonce_odr dso_local unnamed_addr constant { [10 x i8*], [8 x i8*] } { [10 x i8*] [i8* inttoptr (i64 8 to i8*), i8* null, i8* null, i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI1D to i8*), i8* bitcast (void (%class.D*)* @_ZN1D3fooEv to i8*), i8* bitcast (void (%class.D*)* @_ZN1DD1Ev to i8*), i8* bitcast (void (%class.D*)* @_ZN1DD0Ev to i8*)], [8 x i8*] [i8* inttoptr (i64 -8 to i8*), i8* inttoptr (i64 -8 to i8*), i8* inttoptr (i64 -8 to i8*), i8* inttoptr (i64 -8 to i8*), i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI1D to i8*), i8* bitcast (void (%class.D*)* @_ZTv0_n24_N1D3fooEv to i8*), i8* bitcast (void (%class.D*)* @_ZTv0_n32_N1DD1Ev to i8*), i8* bitcast (void (%class.D*)* @_ZTv0_n32_N1DD0Ev to i8*)] }, comdat, align 8
@_ZTT1D = linkonce_odr dso_local unnamed_addr constant [8 x i8*] [i8* bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTV1D, i32 0, inrange i32 0, i32 7) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTV1D, i32 0, inrange i32 0, i32 7) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTV1D, i32 0, inrange i32 0, i32 7) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTV1D, i32 0, inrange i32 1, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTC1D0_1B, i32 0, inrange i32 0, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTC1D0_1B, i32 0, inrange i32 0, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*], [7 x i8*] }, { [8 x i8*], [7 x i8*] }* @_ZTC1D8_1C, i32 0, inrange i32 0, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*], [7 x i8*] }, { [8 x i8*], [7 x i8*] }* @_ZTC1D8_1C, i32 0, inrange i32 1, i32 4) to i8*)], comdat, align 8
@_ZTC1D0_1B = linkonce_odr dso_local unnamed_addr constant { [8 x i8*] } { [8 x i8*] [i8* null, i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1B to i8*), i8* bitcast (void (%class.B*)* @_ZN1B3fooEv to i8*), i8* bitcast (void (%class.B*)* @_ZN1BD1Ev to i8*), i8* bitcast (void (%class.B*)* @_ZN1BD0Ev to i8*)] }, comdat, align 8
@_ZTC1D8_1C = linkonce_odr dso_local unnamed_addr constant { [8 x i8*], [7 x i8*] } { [8 x i8*] [i8* inttoptr (i64 -8 to i8*), i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1C to i8*), i8* bitcast (void (%class.C*)* @_ZN1C3fooEv to i8*), i8* bitcast (void (%class.C*)* @_ZN1CD1Ev to i8*), i8* bitcast (void (%class.C*)* @_ZN1CD0Ev to i8*)], [7 x i8*] [i8* inttoptr (i64 8 to i8*), i8* inttoptr (i64 8 to i8*), i8* inttoptr (i64 8 to i8*), i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1C to i8*), i8* bitcast (void (%class.C*)* @_ZTv0_n24_N1C3fooEv to i8*), i8* bitcast (void (%class.C*)* @_ZTv0_n32_N1CD1Ev to i8*), i8* bitcast (void (%class.C*)* @_ZTv0_n32_N1CD0Ev to i8*)] }, comdat, align 8
@_ZTS1D = linkonce_odr dso_local constant [3 x i8] c"1D\00", comdat, align 1
@_ZTI1D = linkonce_odr dso_local constant { i8*, i8*, i32, i32, i8*, i64, i8*, i64 } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv121__vmi_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1D, i32 0, i32 0), i32 2, i32 2, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1B to i8*), i64 -12285, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1C to i8*), i64 -14333 }, comdat, align 8
@_ZTV1E = linkonce_odr dso_local unnamed_addr constant { [11 x i8*], [8 x i8*] } { [11 x i8*] [i8* null, i8* inttoptr (i64 8 to i8*), i8* null, i8* null, i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1E to i8*), i8* bitcast (void (%class.E*)* @_ZN1E3fooEv to i8*), i8* bitcast (void (%class.E*)* @_ZN1ED1Ev to i8*), i8* bitcast (void (%class.E*)* @_ZN1ED0Ev to i8*)], [8 x i8*] [i8* inttoptr (i64 -8 to i8*), i8* inttoptr (i64 -8 to i8*), i8* inttoptr (i64 -8 to i8*), i8* inttoptr (i64 -8 to i8*), i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1E to i8*), i8* bitcast (void (%class.E*)* @_ZTv0_n24_N1E3fooEv to i8*), i8* bitcast (void (%class.E*)* @_ZTv0_n32_N1ED1Ev to i8*), i8* bitcast (void (%class.E*)* @_ZTv0_n32_N1ED0Ev to i8*)] }, comdat, align 8
@_ZTT1E = linkonce_odr dso_local unnamed_addr constant [13 x i8*] [i8* bitcast (i8** getelementptr inbounds ({ [11 x i8*], [8 x i8*] }, { [11 x i8*], [8 x i8*] }* @_ZTV1E, i32 0, inrange i32 0, i32 8) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [11 x i8*], [8 x i8*] }, { [11 x i8*], [8 x i8*] }* @_ZTV1E, i32 0, inrange i32 0, i32 8) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [11 x i8*], [8 x i8*] }, { [11 x i8*], [8 x i8*] }* @_ZTV1E, i32 0, inrange i32 0, i32 8) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [11 x i8*], [8 x i8*] }, { [11 x i8*], [8 x i8*] }* @_ZTV1E, i32 0, inrange i32 0, i32 8) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [11 x i8*], [8 x i8*] }, { [11 x i8*], [8 x i8*] }* @_ZTV1E, i32 0, inrange i32 1, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTC1E0_1D, i32 0, inrange i32 0, i32 7) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTC1E0_1D, i32 0, inrange i32 0, i32 7) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTC1E0_1D, i32 0, inrange i32 0, i32 7) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTC1E0_1D, i32 0, inrange i32 1, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTC1E0_1B, i32 0, inrange i32 0, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTC1E0_1B, i32 0, inrange i32 0, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*], [7 x i8*] }, { [8 x i8*], [7 x i8*] }* @_ZTC1E8_1C, i32 0, inrange i32 0, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*], [7 x i8*] }, { [8 x i8*], [7 x i8*] }* @_ZTC1E8_1C, i32 0, inrange i32 1, i32 4) to i8*)], comdat, align 8
@_ZTC1E0_1D = linkonce_odr dso_local unnamed_addr constant { [10 x i8*], [8 x i8*] } { [10 x i8*] [i8* inttoptr (i64 8 to i8*), i8* null, i8* null, i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI1D to i8*), i8* bitcast (void (%class.D*)* @_ZN1D3fooEv to i8*), i8* bitcast (void (%class.D*)* @_ZN1DD1Ev to i8*), i8* bitcast (void (%class.D*)* @_ZN1DD0Ev to i8*)], [8 x i8*] [i8* inttoptr (i64 -8 to i8*), i8* inttoptr (i64 -8 to i8*), i8* inttoptr (i64 -8 to i8*), i8* inttoptr (i64 -8 to i8*), i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI1D to i8*), i8* bitcast (void (%class.D*)* @_ZTv0_n24_N1D3fooEv to i8*), i8* bitcast (void (%class.D*)* @_ZTv0_n32_N1DD1Ev to i8*), i8* bitcast (void (%class.D*)* @_ZTv0_n32_N1DD0Ev to i8*)] }, comdat, align 8
@_ZTC1E0_1B = linkonce_odr dso_local unnamed_addr constant { [8 x i8*] } { [8 x i8*] [i8* null, i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1B to i8*), i8* bitcast (void (%class.B*)* @_ZN1B3fooEv to i8*), i8* bitcast (void (%class.B*)* @_ZN1BD1Ev to i8*), i8* bitcast (void (%class.B*)* @_ZN1BD0Ev to i8*)] }, comdat, align 8
@_ZTC1E8_1C = linkonce_odr dso_local unnamed_addr constant { [8 x i8*], [7 x i8*] } { [8 x i8*] [i8* inttoptr (i64 -8 to i8*), i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1C to i8*), i8* bitcast (void (%class.C*)* @_ZN1C3fooEv to i8*), i8* bitcast (void (%class.C*)* @_ZN1CD1Ev to i8*), i8* bitcast (void (%class.C*)* @_ZN1CD0Ev to i8*)], [7 x i8*] [i8* inttoptr (i64 8 to i8*), i8* inttoptr (i64 8 to i8*), i8* inttoptr (i64 8 to i8*), i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1C to i8*), i8* bitcast (void (%class.C*)* @_ZTv0_n24_N1C3fooEv to i8*), i8* bitcast (void (%class.C*)* @_ZTv0_n32_N1CD1Ev to i8*), i8* bitcast (void (%class.C*)* @_ZTv0_n32_N1CD0Ev to i8*)] }, comdat, align 8
@_ZTS1E = linkonce_odr dso_local constant [3 x i8] c"1E\00", comdat, align 1
@_ZTI1E = linkonce_odr dso_local constant { i8*, i8*, i32, i32, i8*, i64 } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv121__vmi_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1E, i32 0, i32 0), i32 2, i32 1, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64, i8*, i64 }* @_ZTI1D to i8*), i64 -16381 }, comdat, align 8
@_ZTV1G = linkonce_odr dso_local unnamed_addr constant { [8 x i8*] } { [8 x i8*] [i8* null, i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1G to i8*), i8* bitcast (void (%class.G*)* @_ZN1G3fooEv to i8*), i8* bitcast (void (%class.G*)* @_ZN1GD1Ev to i8*), i8* bitcast (void (%class.G*)* @_ZN1GD0Ev to i8*)] }, comdat, align 8
@_ZTT1G = linkonce_odr dso_local unnamed_addr constant [2 x i8*] [i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1G, i32 0, inrange i32 0, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1G, i32 0, inrange i32 0, i32 5) to i8*)], comdat, align 8
@_ZTS1G = linkonce_odr dso_local constant [3 x i8] c"1G\00", comdat, align 1
@_ZTS1F = linkonce_odr dso_local constant [3 x i8] c"1F\00", comdat, align 1
@_ZTI1F = linkonce_odr dso_local constant { i8*, i8* } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv117__class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1F, i32 0, i32 0) }, comdat, align 8
@_ZTI1G = linkonce_odr dso_local constant { i8*, i8*, i32, i32, i8*, i64 } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv121__vmi_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1G, i32 0, i32 0), i32 0, i32 1, i8* bitcast ({ i8*, i8* }* @_ZTI1F to i8*), i64 -10237 }, comdat, align 8
@_ZTV1F = linkonce_odr dso_local unnamed_addr constant { [5 x i8*] } { [5 x i8*] [i8* null, i8* bitcast ({ i8*, i8* }* @_ZTI1F to i8*), i8* bitcast (void (%class.F*)* @_ZN1F3fooEv to i8*), i8* bitcast (void (%class.F*)* @_ZN1FD2Ev to i8*), i8* bitcast (void (%class.F*)* @_ZN1FD0Ev to i8*)] }, comdat, align 8
@_ZTV1H = linkonce_odr dso_local unnamed_addr constant { [9 x i8*] } { [9 x i8*] [i8* null, i8* null, i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1H to i8*), i8* bitcast (void (%class.H*)* @_ZN1H3fooEv to i8*), i8* bitcast (void (%class.H*)* @_ZN1HD1Ev to i8*), i8* bitcast (void (%class.H*)* @_ZN1HD0Ev to i8*)] }, comdat, align 8
@_ZTT1H = linkonce_odr dso_local unnamed_addr constant [5 x i8*] [i8* bitcast (i8** getelementptr inbounds ({ [9 x i8*] }, { [9 x i8*] }* @_ZTV1H, i32 0, inrange i32 0, i32 6) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [9 x i8*] }, { [9 x i8*] }* @_ZTV1H, i32 0, inrange i32 0, i32 6) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [9 x i8*] }, { [9 x i8*] }* @_ZTV1H, i32 0, inrange i32 0, i32 6) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTC1H0_1G, i32 0, inrange i32 0, i32 5) to i8*), i8* bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTC1H0_1G, i32 0, inrange i32 0, i32 5) to i8*)], comdat, align 8
@_ZTC1H0_1G = linkonce_odr dso_local unnamed_addr constant { [8 x i8*] } { [8 x i8*] [i8* null, i8* null, i8* null, i8* null, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1G to i8*), i8* bitcast (void (%class.G*)* @_ZN1G3fooEv to i8*), i8* bitcast (void (%class.G*)* @_ZN1GD1Ev to i8*), i8* bitcast (void (%class.G*)* @_ZN1GD0Ev to i8*)] }, comdat, align 8
@_ZTS1H = linkonce_odr dso_local constant [3 x i8] c"1H\00", comdat, align 1
@_ZTI1H = linkonce_odr dso_local constant { i8*, i8*, i32, i32, i8*, i64 } { i8* bitcast (i8** getelementptr inbounds (i8*, i8** @_ZTVN10__cxxabiv121__vmi_class_type_infoE, i64 2) to i8*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_ZTS1H, i32 0, i32 0), i32 0, i32 1, i8* bitcast ({ i8*, i8*, i32, i32, i8*, i64 }* @_ZTI1G to i8*), i64 -12285 }, comdat, align 8

; Function Attrs: mustprogress noinline norecurse optnone uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %class.A*, align 8
  %3 = alloca %class.B*, align 8
  %4 = alloca %class.C*, align 8
  %5 = alloca %class.C*, align 8
  %6 = alloca %class.F*, align 8
  %7 = alloca %class.F*, align 8
  store i32 0, i32* %1, align 4
  %8 = call noalias noundef nonnull i8* @_Znwm(i64 noundef 8) #7
  %9 = bitcast i8* %8 to %class.C*
  %10 = bitcast %class.C* %9 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %10, i8 0, i64 8, i1 false)
  call void @_ZN1CC1Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %9) #8
  %11 = icmp eq %class.C* %9, null
  br i1 %11, label %21, label %12

12:                                               ; preds = %0
  %13 = bitcast %class.C* %9 to i8**
  %14 = load i8*, i8** %13, align 8
  %15 = getelementptr i8, i8* %14, i64 -40
  %16 = bitcast i8* %15 to i64*
  %17 = load i64, i64* %16, align 8
  %18 = bitcast %class.C* %9 to i8*
  %19 = getelementptr inbounds i8, i8* %18, i64 %17
  %20 = bitcast i8* %19 to %class.A*
  br label %21

21:                                               ; preds = %12, %0
  %22 = phi %class.A* [ %20, %12 ], [ null, %0 ]
  store %class.A* %22, %class.A** %2, align 8
  %23 = call noalias noundef nonnull i8* @_Znwm(i64 noundef 8) #7
  %24 = bitcast i8* %23 to %class.B*
  %25 = bitcast %class.B* %24 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %25, i8 0, i64 8, i1 false)
  call void @_ZN1BC1Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %24) #8
  store %class.B* %24, %class.B** %3, align 8
  %26 = call noalias noundef nonnull i8* @_Znwm(i64 noundef 16) #7
  %27 = bitcast i8* %26 to %class.D*
  %28 = bitcast %class.D* %27 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %28, i8 0, i64 16, i1 false)
  call void @_ZN1DC1Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %27) #8
  %29 = icmp eq %class.D* %27, null
  br i1 %29, label %39, label %30

30:                                               ; preds = %21
  %31 = bitcast %class.D* %27 to i8**
  %32 = load i8*, i8** %31, align 8
  %33 = getelementptr i8, i8* %32, i64 -56
  %34 = bitcast i8* %33 to i64*
  %35 = load i64, i64* %34, align 8
  %36 = bitcast %class.D* %27 to i8*
  %37 = getelementptr inbounds i8, i8* %36, i64 %35
  %38 = bitcast i8* %37 to %class.C*
  br label %39

39:                                               ; preds = %30, %21
  %40 = phi %class.C* [ %38, %30 ], [ null, %21 ]
  store %class.C* %40, %class.C** %4, align 8
  %41 = call noalias noundef nonnull i8* @_Znwm(i64 noundef 16) #7
  %42 = bitcast i8* %41 to %class.E*
  %43 = bitcast %class.E* %42 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %43, i8 0, i64 16, i1 false)
  call void @_ZN1EC1Ev(%class.E* noundef nonnull align 8 dereferenceable(8) %42) #8
  %44 = icmp eq %class.E* %42, null
  br i1 %44, label %54, label %45

45:                                               ; preds = %39
  %46 = bitcast %class.E* %42 to i8**
  %47 = load i8*, i8** %46, align 8
  %48 = getelementptr i8, i8* %47, i64 -56
  %49 = bitcast i8* %48 to i64*
  %50 = load i64, i64* %49, align 8
  %51 = bitcast %class.E* %42 to i8*
  %52 = getelementptr inbounds i8, i8* %51, i64 %50
  %53 = bitcast i8* %52 to %class.C*
  br label %54

54:                                               ; preds = %45, %39
  %55 = phi %class.C* [ %53, %45 ], [ null, %39 ]
  store %class.C* %55, %class.C** %5, align 8
  %56 = call noalias noundef nonnull i8* @_Znwm(i64 noundef 8) #7
  %57 = bitcast i8* %56 to %class.G*
  %58 = bitcast %class.G* %57 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %58, i8 0, i64 8, i1 false)
  call void @_ZN1GC1Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %57) #8
  %59 = icmp eq %class.G* %57, null
  br i1 %59, label %69, label %60

60:                                               ; preds = %54
  %61 = bitcast %class.G* %57 to i8**
  %62 = load i8*, i8** %61, align 8
  %63 = getelementptr i8, i8* %62, i64 -40
  %64 = bitcast i8* %63 to i64*
  %65 = load i64, i64* %64, align 8
  %66 = bitcast %class.G* %57 to i8*
  %67 = getelementptr inbounds i8, i8* %66, i64 %65
  %68 = bitcast i8* %67 to %class.F*
  br label %69

69:                                               ; preds = %60, %54
  %70 = phi %class.F* [ %68, %60 ], [ null, %54 ]
  store %class.F* %70, %class.F** %6, align 8
  %71 = call noalias noundef nonnull i8* @_Znwm(i64 noundef 8) #7
  %72 = bitcast i8* %71 to %class.H*
  %73 = bitcast %class.H* %72 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %73, i8 0, i64 8, i1 false)
  call void @_ZN1HC1Ev(%class.H* noundef nonnull align 8 dereferenceable(8) %72) #8
  %74 = icmp eq %class.H* %72, null
  br i1 %74, label %84, label %75

75:                                               ; preds = %69
  %76 = bitcast %class.H* %72 to i8**
  %77 = load i8*, i8** %76, align 8
  %78 = getelementptr i8, i8* %77, i64 -40
  %79 = bitcast i8* %78 to i64*
  %80 = load i64, i64* %79, align 8
  %81 = bitcast %class.H* %72 to i8*
  %82 = getelementptr inbounds i8, i8* %81, i64 %80
  %83 = bitcast i8* %82 to %class.F*
  br label %84

84:                                               ; preds = %75, %69
  %85 = phi %class.F* [ %83, %75 ], [ null, %69 ]
  store %class.F* %85, %class.F** %7, align 8
  %86 = load %class.A*, %class.A** %2, align 8
  %87 = bitcast %class.A* %86 to void (%class.A*)***
  %88 = load void (%class.A*)**, void (%class.A*)*** %87, align 8
  %89 = getelementptr inbounds void (%class.A*)*, void (%class.A*)** %88, i64 0
  %90 = load void (%class.A*)*, void (%class.A*)** %89, align 8
  call void %90(%class.A* noundef nonnull align 8 dereferenceable(8) %86)
  %91 = load %class.B*, %class.B** %3, align 8
  %92 = bitcast %class.B* %91 to void (%class.B*)***
  %93 = load void (%class.B*)**, void (%class.B*)*** %92, align 8
  %94 = getelementptr inbounds void (%class.B*)*, void (%class.B*)** %93, i64 0
  %95 = load void (%class.B*)*, void (%class.B*)** %94, align 8
  call void %95(%class.B* noundef nonnull align 8 dereferenceable(8) %91)
  %96 = load %class.C*, %class.C** %4, align 8
  %97 = bitcast %class.C* %96 to void (%class.C*)***
  %98 = load void (%class.C*)**, void (%class.C*)*** %97, align 8
  %99 = getelementptr inbounds void (%class.C*)*, void (%class.C*)** %98, i64 0
  %100 = load void (%class.C*)*, void (%class.C*)** %99, align 8
  call void %100(%class.C* noundef nonnull align 8 dereferenceable(8) %96)
  %101 = load %class.C*, %class.C** %5, align 8
  %102 = bitcast %class.C* %101 to void (%class.C*)***
  %103 = load void (%class.C*)**, void (%class.C*)*** %102, align 8
  %104 = getelementptr inbounds void (%class.C*)*, void (%class.C*)** %103, i64 0
  %105 = load void (%class.C*)*, void (%class.C*)** %104, align 8
  call void %105(%class.C* noundef nonnull align 8 dereferenceable(8) %101)
  %106 = load %class.F*, %class.F** %6, align 8
  %107 = bitcast %class.F* %106 to void (%class.F*)***
  %108 = load void (%class.F*)**, void (%class.F*)*** %107, align 8
  %109 = getelementptr inbounds void (%class.F*)*, void (%class.F*)** %108, i64 0
  %110 = load void (%class.F*)*, void (%class.F*)** %109, align 8
  call void %110(%class.F* noundef nonnull align 8 dereferenceable(8) %106)
  %111 = load %class.F*, %class.F** %7, align 8
  %112 = bitcast %class.F* %111 to void (%class.F*)***
  %113 = load void (%class.F*)**, void (%class.F*)*** %112, align 8
  %114 = getelementptr inbounds void (%class.F*)*, void (%class.F*)** %113, i64 0
  %115 = load void (%class.F*)*, void (%class.F*)** %114, align 8
  call void %115(%class.F* noundef nonnull align 8 dereferenceable(8) %111)
  %116 = load %class.F*, %class.F** %7, align 8
  %117 = icmp eq %class.F* %116, null
  br i1 %117, label %123, label %118

118:                                              ; preds = %84
  %119 = bitcast %class.F* %116 to void (%class.F*)***
  %120 = load void (%class.F*)**, void (%class.F*)*** %119, align 8
  %121 = getelementptr inbounds void (%class.F*)*, void (%class.F*)** %120, i64 2
  %122 = load void (%class.F*)*, void (%class.F*)** %121, align 8
  call void %122(%class.F* noundef nonnull align 8 dereferenceable(8) %116) #8
  br label %123

123:                                              ; preds = %118, %84
  %124 = load %class.F*, %class.F** %6, align 8
  %125 = icmp eq %class.F* %124, null
  br i1 %125, label %131, label %126

126:                                              ; preds = %123
  %127 = bitcast %class.F* %124 to void (%class.F*)***
  %128 = load void (%class.F*)**, void (%class.F*)*** %127, align 8
  %129 = getelementptr inbounds void (%class.F*)*, void (%class.F*)** %128, i64 2
  %130 = load void (%class.F*)*, void (%class.F*)** %129, align 8
  call void %130(%class.F* noundef nonnull align 8 dereferenceable(8) %124) #8
  br label %131

131:                                              ; preds = %126, %123
  %132 = load %class.C*, %class.C** %5, align 8
  %133 = icmp eq %class.C* %132, null
  br i1 %133, label %139, label %134

134:                                              ; preds = %131
  %135 = bitcast %class.C* %132 to void (%class.C*)***
  %136 = load void (%class.C*)**, void (%class.C*)*** %135, align 8
  %137 = getelementptr inbounds void (%class.C*)*, void (%class.C*)** %136, i64 2
  %138 = load void (%class.C*)*, void (%class.C*)** %137, align 8
  call void %138(%class.C* noundef nonnull align 8 dereferenceable(8) %132) #8
  br label %139

139:                                              ; preds = %134, %131
  %140 = load %class.C*, %class.C** %4, align 8
  %141 = icmp eq %class.C* %140, null
  br i1 %141, label %147, label %142

142:                                              ; preds = %139
  %143 = bitcast %class.C* %140 to void (%class.C*)***
  %144 = load void (%class.C*)**, void (%class.C*)*** %143, align 8
  %145 = getelementptr inbounds void (%class.C*)*, void (%class.C*)** %144, i64 2
  %146 = load void (%class.C*)*, void (%class.C*)** %145, align 8
  call void %146(%class.C* noundef nonnull align 8 dereferenceable(8) %140) #8
  br label %147

147:                                              ; preds = %142, %139
  %148 = load %class.B*, %class.B** %3, align 8
  %149 = icmp eq %class.B* %148, null
  br i1 %149, label %155, label %150

150:                                              ; preds = %147
  %151 = bitcast %class.B* %148 to void (%class.B*)***
  %152 = load void (%class.B*)**, void (%class.B*)*** %151, align 8
  %153 = getelementptr inbounds void (%class.B*)*, void (%class.B*)** %152, i64 2
  %154 = load void (%class.B*)*, void (%class.B*)** %153, align 8
  call void %154(%class.B* noundef nonnull align 8 dereferenceable(8) %148) #8
  br label %155

155:                                              ; preds = %150, %147
  %156 = load %class.A*, %class.A** %2, align 8
  %157 = icmp eq %class.A* %156, null
  br i1 %157, label %163, label %158

158:                                              ; preds = %155
  %159 = bitcast %class.A* %156 to void (%class.A*)***
  %160 = load void (%class.A*)**, void (%class.A*)*** %159, align 8
  %161 = getelementptr inbounds void (%class.A*)*, void (%class.A*)** %160, i64 2
  %162 = load void (%class.A*)*, void (%class.A*)** %161, align 8
  call void %162(%class.A* noundef nonnull align 8 dereferenceable(8) %156) #8
  br label %163

163:                                              ; preds = %158, %155
  %164 = load i32, i32* %1, align 4
  ret i32 %164
}

; Function Attrs: nobuiltin allocsize(0)
declare noundef nonnull i8* @_Znwm(i64 noundef) #1

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #2

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1CC1Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  %4 = bitcast %class.C* %3 to %class.A*
  call void @_ZN1AC2Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %4) #8
  %5 = bitcast %class.C* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1C, i32 0, inrange i32 0, i32 5) to i32 (...)**), i32 (...)*** %5, align 8
  %6 = bitcast %class.C* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1C, i32 0, inrange i32 0, i32 5) to i32 (...)**), i32 (...)*** %6, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1BC1Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.B*, align 8
  store %class.B* %0, %class.B** %2, align 8
  %3 = load %class.B*, %class.B** %2, align 8
  %4 = bitcast %class.B* %3 to %class.A*
  call void @_ZN1AC2Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %4) #8
  %5 = bitcast %class.B* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1B, i32 0, inrange i32 0, i32 5) to i32 (...)**), i32 (...)*** %5, align 8
  %6 = bitcast %class.B* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1B, i32 0, inrange i32 0, i32 5) to i32 (...)**), i32 (...)*** %6, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1DC1Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.D*, align 8
  store %class.D* %0, %class.D** %2, align 8
  %3 = load %class.D*, %class.D** %2, align 8
  %4 = bitcast %class.D* %3 to %class.A*
  call void @_ZN1AC2Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %4) #8
  %5 = bitcast %class.D* %3 to %class.B*
  call void @_ZN1BC2Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %5, i8** noundef getelementptr inbounds ([8 x i8*], [8 x i8*]* @_ZTT1D, i64 0, i64 4)) #8
  %6 = bitcast %class.D* %3 to i8*
  %7 = getelementptr inbounds i8, i8* %6, i64 8
  %8 = bitcast i8* %7 to %class.C*
  call void @_ZN1CC2Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %8, i8** noundef getelementptr inbounds ([8 x i8*], [8 x i8*]* @_ZTT1D, i64 0, i64 6)) #8
  %9 = bitcast %class.D* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTV1D, i32 0, inrange i32 0, i32 7) to i32 (...)**), i32 (...)*** %9, align 8
  %10 = bitcast %class.D* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTV1D, i32 0, inrange i32 0, i32 7) to i32 (...)**), i32 (...)*** %10, align 8
  %11 = bitcast %class.D* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTV1D, i32 0, inrange i32 0, i32 7) to i32 (...)**), i32 (...)*** %11, align 8
  %12 = bitcast %class.D* %3 to i8*
  %13 = getelementptr inbounds i8, i8* %12, i64 8
  %14 = bitcast i8* %13 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [10 x i8*], [8 x i8*] }, { [10 x i8*], [8 x i8*] }* @_ZTV1D, i32 0, inrange i32 1, i32 5) to i32 (...)**), i32 (...)*** %14, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1EC1Ev(%class.E* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  %4 = bitcast %class.E* %3 to %class.A*
  call void @_ZN1AC2Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %4) #8
  %5 = bitcast %class.E* %3 to %class.B*
  call void @_ZN1BC2Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %5, i8** noundef getelementptr inbounds ([13 x i8*], [13 x i8*]* @_ZTT1E, i64 0, i64 9)) #8
  %6 = bitcast %class.E* %3 to i8*
  %7 = getelementptr inbounds i8, i8* %6, i64 8
  %8 = bitcast i8* %7 to %class.C*
  call void @_ZN1CC2Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %8, i8** noundef getelementptr inbounds ([13 x i8*], [13 x i8*]* @_ZTT1E, i64 0, i64 11)) #8
  %9 = bitcast %class.E* %3 to %class.D*
  call void @_ZN1DC2Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %9, i8** noundef getelementptr inbounds ([13 x i8*], [13 x i8*]* @_ZTT1E, i64 0, i64 5)) #8
  %10 = bitcast %class.E* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [11 x i8*], [8 x i8*] }, { [11 x i8*], [8 x i8*] }* @_ZTV1E, i32 0, inrange i32 0, i32 8) to i32 (...)**), i32 (...)*** %10, align 8
  %11 = bitcast %class.E* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [11 x i8*], [8 x i8*] }, { [11 x i8*], [8 x i8*] }* @_ZTV1E, i32 0, inrange i32 0, i32 8) to i32 (...)**), i32 (...)*** %11, align 8
  %12 = bitcast %class.E* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [11 x i8*], [8 x i8*] }, { [11 x i8*], [8 x i8*] }* @_ZTV1E, i32 0, inrange i32 0, i32 8) to i32 (...)**), i32 (...)*** %12, align 8
  %13 = bitcast %class.E* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [11 x i8*], [8 x i8*] }, { [11 x i8*], [8 x i8*] }* @_ZTV1E, i32 0, inrange i32 0, i32 8) to i32 (...)**), i32 (...)*** %13, align 8
  %14 = bitcast %class.E* %3 to i8*
  %15 = getelementptr inbounds i8, i8* %14, i64 8
  %16 = bitcast i8* %15 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [11 x i8*], [8 x i8*] }, { [11 x i8*], [8 x i8*] }* @_ZTV1E, i32 0, inrange i32 1, i32 5) to i32 (...)**), i32 (...)*** %16, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1GC1Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.G*, align 8
  store %class.G* %0, %class.G** %2, align 8
  %3 = load %class.G*, %class.G** %2, align 8
  %4 = bitcast %class.G* %3 to %class.F*
  call void @_ZN1FC2Ev(%class.F* noundef nonnull align 8 dereferenceable(8) %4) #8
  %5 = bitcast %class.G* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1G, i32 0, inrange i32 0, i32 5) to i32 (...)**), i32 (...)*** %5, align 8
  %6 = bitcast %class.G* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [8 x i8*] }, { [8 x i8*] }* @_ZTV1G, i32 0, inrange i32 0, i32 5) to i32 (...)**), i32 (...)*** %6, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1HC1Ev(%class.H* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.H*, align 8
  store %class.H* %0, %class.H** %2, align 8
  %3 = load %class.H*, %class.H** %2, align 8
  %4 = bitcast %class.H* %3 to %class.F*
  call void @_ZN1FC2Ev(%class.F* noundef nonnull align 8 dereferenceable(8) %4) #8
  %5 = bitcast %class.H* %3 to %class.G*
  call void @_ZN1GC2Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %5, i8** noundef getelementptr inbounds ([5 x i8*], [5 x i8*]* @_ZTT1H, i64 0, i64 3)) #8
  %6 = bitcast %class.H* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [9 x i8*] }, { [9 x i8*] }* @_ZTV1H, i32 0, inrange i32 0, i32 6) to i32 (...)**), i32 (...)*** %6, align 8
  %7 = bitcast %class.H* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [9 x i8*] }, { [9 x i8*] }* @_ZTV1H, i32 0, inrange i32 0, i32 6) to i32 (...)**), i32 (...)*** %7, align 8
  %8 = bitcast %class.H* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [9 x i8*] }, { [9 x i8*] }* @_ZTV1H, i32 0, inrange i32 0, i32 6) to i32 (...)**), i32 (...)*** %8, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1AC2Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.A*, align 8
  store %class.A* %0, %class.A** %2, align 8
  %3 = load %class.A*, %class.A** %2, align 8
  %4 = bitcast %class.A* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [5 x i8*] }, { [5 x i8*] }* @_ZTV1A, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %4, align 8
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1C3fooEv(%class.C* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1CD1Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  call void @_ZN1CD2Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %3, i8** noundef getelementptr inbounds ([2 x i8*], [2 x i8*]* @_ZTT1C, i64 0, i64 0)) #8
  %4 = bitcast %class.C* %3 to %class.A*
  call void @_ZN1AD2Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %4) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1CD0Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  call void @_ZN1CD1Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %3) #8
  %4 = bitcast %class.C* %3 to i8*
  call void @_ZdlPv(i8* noundef %4) #9
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1A3fooEv(%class.A* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.A*, align 8
  store %class.A* %0, %class.A** %2, align 8
  %3 = load %class.A*, %class.A** %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1AD2Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.A*, align 8
  store %class.A* %0, %class.A** %2, align 8
  %3 = load %class.A*, %class.A** %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1AD0Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.A*, align 8
  store %class.A* %0, %class.A** %2, align 8
  %3 = load %class.A*, %class.A** %2, align 8
  call void @_ZN1AD2Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %3) #8
  %4 = bitcast %class.A* %3 to i8*
  call void @_ZdlPv(i8* noundef %4) #9
  ret void
}

; Function Attrs: nobuiltin nounwind
declare void @_ZdlPv(i8* noundef) #5

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n24_N1C3fooEv(%class.C* noundef %0) unnamed_addr #6 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  %4 = bitcast %class.C* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -24
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.C*
  tail call void @_ZN1C3fooEv(%class.C* noundef nonnull align 8 dereferenceable(8) %11)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1CD2Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %0, i8** noundef %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %class.C*, align 8
  %4 = alloca i8**, align 8
  store %class.C* %0, %class.C** %3, align 8
  store i8** %1, i8*** %4, align 8
  %5 = load %class.C*, %class.C** %3, align 8
  %6 = load i8**, i8*** %4, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1CD1Ev(%class.C* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  %4 = bitcast %class.C* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.C*
  tail call void @_ZN1CD1Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1CD0Ev(%class.C* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.C*, align 8
  store %class.C* %0, %class.C** %2, align 8
  %3 = load %class.C*, %class.C** %2, align 8
  %4 = bitcast %class.C* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.C*
  tail call void @_ZN1CD0Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1B3fooEv(%class.B* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.B*, align 8
  store %class.B* %0, %class.B** %2, align 8
  %3 = load %class.B*, %class.B** %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1BD1Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.B*, align 8
  store %class.B* %0, %class.B** %2, align 8
  %3 = load %class.B*, %class.B** %2, align 8
  call void @_ZN1BD2Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %3, i8** noundef getelementptr inbounds ([2 x i8*], [2 x i8*]* @_ZTT1B, i64 0, i64 0)) #8
  %4 = bitcast %class.B* %3 to %class.A*
  call void @_ZN1AD2Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %4) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1BD0Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.B*, align 8
  store %class.B* %0, %class.B** %2, align 8
  %3 = load %class.B*, %class.B** %2, align 8
  call void @_ZN1BD1Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %3) #8
  %4 = bitcast %class.B* %3 to i8*
  call void @_ZdlPv(i8* noundef %4) #9
  ret void
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n24_N1B3fooEv(%class.B* noundef %0) unnamed_addr #6 comdat align 2 {
  %2 = alloca %class.B*, align 8
  store %class.B* %0, %class.B** %2, align 8
  %3 = load %class.B*, %class.B** %2, align 8
  %4 = bitcast %class.B* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -24
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.B*
  tail call void @_ZN1B3fooEv(%class.B* noundef nonnull align 8 dereferenceable(8) %11)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1BD2Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %0, i8** noundef %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %class.B*, align 8
  %4 = alloca i8**, align 8
  store %class.B* %0, %class.B** %3, align 8
  store i8** %1, i8*** %4, align 8
  %5 = load %class.B*, %class.B** %3, align 8
  %6 = load i8**, i8*** %4, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1BD1Ev(%class.B* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.B*, align 8
  store %class.B* %0, %class.B** %2, align 8
  %3 = load %class.B*, %class.B** %2, align 8
  %4 = bitcast %class.B* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.B*
  tail call void @_ZN1BD1Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1BD0Ev(%class.B* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.B*, align 8
  store %class.B* %0, %class.B** %2, align 8
  %3 = load %class.B*, %class.B** %2, align 8
  %4 = bitcast %class.B* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.B*
  tail call void @_ZN1BD0Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1BC2Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %0, i8** noundef %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %class.B*, align 8
  %4 = alloca i8**, align 8
  store %class.B* %0, %class.B** %3, align 8
  store i8** %1, i8*** %4, align 8
  %5 = load %class.B*, %class.B** %3, align 8
  %6 = load i8**, i8*** %4, align 8
  %7 = load i8*, i8** %6, align 8
  %8 = bitcast %class.B* %5 to i32 (...)***
  %9 = bitcast i8* %7 to i32 (...)**
  store i32 (...)** %9, i32 (...)*** %8, align 8
  %10 = getelementptr inbounds i8*, i8** %6, i64 1
  %11 = load i8*, i8** %10, align 8
  %12 = bitcast %class.B* %5 to i8**
  %13 = load i8*, i8** %12, align 8
  %14 = getelementptr i8, i8* %13, i64 -40
  %15 = bitcast i8* %14 to i64*
  %16 = load i64, i64* %15, align 8
  %17 = bitcast %class.B* %5 to i8*
  %18 = getelementptr inbounds i8, i8* %17, i64 %16
  %19 = bitcast i8* %18 to i32 (...)***
  %20 = bitcast i8* %11 to i32 (...)**
  store i32 (...)** %20, i32 (...)*** %19, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1CC2Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %0, i8** noundef %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %class.C*, align 8
  %4 = alloca i8**, align 8
  store %class.C* %0, %class.C** %3, align 8
  store i8** %1, i8*** %4, align 8
  %5 = load %class.C*, %class.C** %3, align 8
  %6 = load i8**, i8*** %4, align 8
  %7 = load i8*, i8** %6, align 8
  %8 = bitcast %class.C* %5 to i32 (...)***
  %9 = bitcast i8* %7 to i32 (...)**
  store i32 (...)** %9, i32 (...)*** %8, align 8
  %10 = getelementptr inbounds i8*, i8** %6, i64 1
  %11 = load i8*, i8** %10, align 8
  %12 = bitcast %class.C* %5 to i8**
  %13 = load i8*, i8** %12, align 8
  %14 = getelementptr i8, i8* %13, i64 -40
  %15 = bitcast i8* %14 to i64*
  %16 = load i64, i64* %15, align 8
  %17 = bitcast %class.C* %5 to i8*
  %18 = getelementptr inbounds i8, i8* %17, i64 %16
  %19 = bitcast i8* %18 to i32 (...)***
  %20 = bitcast i8* %11 to i32 (...)**
  store i32 (...)** %20, i32 (...)*** %19, align 8
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1D3fooEv(%class.D* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.D*, align 8
  store %class.D* %0, %class.D** %2, align 8
  %3 = load %class.D*, %class.D** %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1DD1Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.D*, align 8
  store %class.D* %0, %class.D** %2, align 8
  %3 = load %class.D*, %class.D** %2, align 8
  call void @_ZN1DD2Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %3, i8** noundef getelementptr inbounds ([8 x i8*], [8 x i8*]* @_ZTT1D, i64 0, i64 0)) #8
  %4 = bitcast %class.D* %3 to i8*
  %5 = getelementptr inbounds i8, i8* %4, i64 8
  %6 = bitcast i8* %5 to %class.C*
  call void @_ZN1CD2Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %6, i8** noundef getelementptr inbounds ([8 x i8*], [8 x i8*]* @_ZTT1D, i64 0, i64 6)) #8
  %7 = bitcast %class.D* %3 to %class.B*
  call void @_ZN1BD2Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %7, i8** noundef getelementptr inbounds ([8 x i8*], [8 x i8*]* @_ZTT1D, i64 0, i64 4)) #8
  %8 = bitcast %class.D* %3 to %class.A*
  call void @_ZN1AD2Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %8) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1DD0Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.D*, align 8
  store %class.D* %0, %class.D** %2, align 8
  %3 = load %class.D*, %class.D** %2, align 8
  call void @_ZN1DD1Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %3) #8
  %4 = bitcast %class.D* %3 to i8*
  call void @_ZdlPv(i8* noundef %4) #9
  ret void
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n24_N1D3fooEv(%class.D* noundef %0) unnamed_addr #6 comdat align 2 {
  %2 = alloca %class.D*, align 8
  store %class.D* %0, %class.D** %2, align 8
  %3 = load %class.D*, %class.D** %2, align 8
  %4 = bitcast %class.D* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -24
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.D*
  tail call void @_ZN1D3fooEv(%class.D* noundef nonnull align 8 dereferenceable(8) %11)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1DD1Ev(%class.D* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.D*, align 8
  store %class.D* %0, %class.D** %2, align 8
  %3 = load %class.D*, %class.D** %2, align 8
  %4 = bitcast %class.D* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.D*
  tail call void @_ZN1DD1Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1DD0Ev(%class.D* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.D*, align 8
  store %class.D* %0, %class.D** %2, align 8
  %3 = load %class.D*, %class.D** %2, align 8
  %4 = bitcast %class.D* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.D*
  tail call void @_ZN1DD0Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1DD2Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %0, i8** noundef %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %class.D*, align 8
  %4 = alloca i8**, align 8
  store %class.D* %0, %class.D** %3, align 8
  store i8** %1, i8*** %4, align 8
  %5 = load %class.D*, %class.D** %3, align 8
  %6 = load i8**, i8*** %4, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1DC2Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %0, i8** noundef %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %class.D*, align 8
  %4 = alloca i8**, align 8
  store %class.D* %0, %class.D** %3, align 8
  store i8** %1, i8*** %4, align 8
  %5 = load %class.D*, %class.D** %3, align 8
  %6 = load i8**, i8*** %4, align 8
  %7 = load i8*, i8** %6, align 8
  %8 = bitcast %class.D* %5 to i32 (...)***
  %9 = bitcast i8* %7 to i32 (...)**
  store i32 (...)** %9, i32 (...)*** %8, align 8
  %10 = getelementptr inbounds i8*, i8** %6, i64 1
  %11 = load i8*, i8** %10, align 8
  %12 = bitcast %class.D* %5 to i8**
  %13 = load i8*, i8** %12, align 8
  %14 = getelementptr i8, i8* %13, i64 -48
  %15 = bitcast i8* %14 to i64*
  %16 = load i64, i64* %15, align 8
  %17 = bitcast %class.D* %5 to i8*
  %18 = getelementptr inbounds i8, i8* %17, i64 %16
  %19 = bitcast i8* %18 to i32 (...)***
  %20 = bitcast i8* %11 to i32 (...)**
  store i32 (...)** %20, i32 (...)*** %19, align 8
  %21 = getelementptr inbounds i8*, i8** %6, i64 2
  %22 = load i8*, i8** %21, align 8
  %23 = bitcast %class.D* %5 to i8**
  %24 = load i8*, i8** %23, align 8
  %25 = getelementptr i8, i8* %24, i64 -40
  %26 = bitcast i8* %25 to i64*
  %27 = load i64, i64* %26, align 8
  %28 = bitcast %class.D* %5 to i8*
  %29 = getelementptr inbounds i8, i8* %28, i64 %27
  %30 = bitcast i8* %29 to i32 (...)***
  %31 = bitcast i8* %22 to i32 (...)**
  store i32 (...)** %31, i32 (...)*** %30, align 8
  %32 = getelementptr inbounds i8*, i8** %6, i64 3
  %33 = load i8*, i8** %32, align 8
  %34 = bitcast %class.D* %5 to i8**
  %35 = load i8*, i8** %34, align 8
  %36 = getelementptr i8, i8* %35, i64 -56
  %37 = bitcast i8* %36 to i64*
  %38 = load i64, i64* %37, align 8
  %39 = bitcast %class.D* %5 to i8*
  %40 = getelementptr inbounds i8, i8* %39, i64 %38
  %41 = bitcast i8* %40 to i32 (...)***
  %42 = bitcast i8* %33 to i32 (...)**
  store i32 (...)** %42, i32 (...)*** %41, align 8
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1E3fooEv(%class.E* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1ED1Ev(%class.E* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  call void @_ZN1ED2Ev(%class.E* noundef nonnull align 8 dereferenceable(8) %3, i8** noundef getelementptr inbounds ([13 x i8*], [13 x i8*]* @_ZTT1E, i64 0, i64 0)) #8
  %4 = bitcast %class.E* %3 to %class.D*
  call void @_ZN1DD2Ev(%class.D* noundef nonnull align 8 dereferenceable(8) %4, i8** noundef getelementptr inbounds ([13 x i8*], [13 x i8*]* @_ZTT1E, i64 0, i64 5)) #8
  %5 = bitcast %class.E* %3 to i8*
  %6 = getelementptr inbounds i8, i8* %5, i64 8
  %7 = bitcast i8* %6 to %class.C*
  call void @_ZN1CD2Ev(%class.C* noundef nonnull align 8 dereferenceable(8) %7, i8** noundef getelementptr inbounds ([13 x i8*], [13 x i8*]* @_ZTT1E, i64 0, i64 11)) #8
  %8 = bitcast %class.E* %3 to %class.B*
  call void @_ZN1BD2Ev(%class.B* noundef nonnull align 8 dereferenceable(8) %8, i8** noundef getelementptr inbounds ([13 x i8*], [13 x i8*]* @_ZTT1E, i64 0, i64 9)) #8
  %9 = bitcast %class.E* %3 to %class.A*
  call void @_ZN1AD2Ev(%class.A* noundef nonnull align 8 dereferenceable(8) %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1ED0Ev(%class.E* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  call void @_ZN1ED1Ev(%class.E* noundef nonnull align 8 dereferenceable(8) %3) #8
  %4 = bitcast %class.E* %3 to i8*
  call void @_ZdlPv(i8* noundef %4) #9
  ret void
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n24_N1E3fooEv(%class.E* noundef %0) unnamed_addr #6 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  %4 = bitcast %class.E* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -24
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.E*
  tail call void @_ZN1E3fooEv(%class.E* noundef nonnull align 8 dereferenceable(8) %11)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1ED1Ev(%class.E* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  %4 = bitcast %class.E* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.E*
  tail call void @_ZN1ED1Ev(%class.E* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1ED0Ev(%class.E* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.E*, align 8
  store %class.E* %0, %class.E** %2, align 8
  %3 = load %class.E*, %class.E** %2, align 8
  %4 = bitcast %class.E* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.E*
  tail call void @_ZN1ED0Ev(%class.E* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1ED2Ev(%class.E* noundef nonnull align 8 dereferenceable(8) %0, i8** noundef %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %class.E*, align 8
  %4 = alloca i8**, align 8
  store %class.E* %0, %class.E** %3, align 8
  store i8** %1, i8*** %4, align 8
  %5 = load %class.E*, %class.E** %3, align 8
  %6 = load i8**, i8*** %4, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1FC2Ev(%class.F* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.F*, align 8
  store %class.F* %0, %class.F** %2, align 8
  %3 = load %class.F*, %class.F** %2, align 8
  %4 = bitcast %class.F* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [5 x i8*] }, { [5 x i8*] }* @_ZTV1F, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %4, align 8
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1G3fooEv(%class.G* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.G*, align 8
  store %class.G* %0, %class.G** %2, align 8
  %3 = load %class.G*, %class.G** %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1GD1Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.G*, align 8
  store %class.G* %0, %class.G** %2, align 8
  %3 = load %class.G*, %class.G** %2, align 8
  call void @_ZN1GD2Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %3, i8** noundef getelementptr inbounds ([2 x i8*], [2 x i8*]* @_ZTT1G, i64 0, i64 0)) #8
  %4 = bitcast %class.G* %3 to %class.F*
  call void @_ZN1FD2Ev(%class.F* noundef nonnull align 8 dereferenceable(8) %4) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1GD0Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.G*, align 8
  store %class.G* %0, %class.G** %2, align 8
  %3 = load %class.G*, %class.G** %2, align 8
  call void @_ZN1GD1Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %3) #8
  %4 = bitcast %class.G* %3 to i8*
  call void @_ZdlPv(i8* noundef %4) #9
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1F3fooEv(%class.F* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.F*, align 8
  store %class.F* %0, %class.F** %2, align 8
  %3 = load %class.F*, %class.F** %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1FD2Ev(%class.F* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.F*, align 8
  store %class.F* %0, %class.F** %2, align 8
  %3 = load %class.F*, %class.F** %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1FD0Ev(%class.F* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.F*, align 8
  store %class.F* %0, %class.F** %2, align 8
  %3 = load %class.F*, %class.F** %2, align 8
  call void @_ZN1FD2Ev(%class.F* noundef nonnull align 8 dereferenceable(8) %3) #8
  %4 = bitcast %class.F* %3 to i8*
  call void @_ZdlPv(i8* noundef %4) #9
  ret void
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n24_N1G3fooEv(%class.G* noundef %0) unnamed_addr #6 comdat align 2 {
  %2 = alloca %class.G*, align 8
  store %class.G* %0, %class.G** %2, align 8
  %3 = load %class.G*, %class.G** %2, align 8
  %4 = bitcast %class.G* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -24
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.G*
  tail call void @_ZN1G3fooEv(%class.G* noundef nonnull align 8 dereferenceable(8) %11)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1GD2Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %0, i8** noundef %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %class.G*, align 8
  %4 = alloca i8**, align 8
  store %class.G* %0, %class.G** %3, align 8
  store i8** %1, i8*** %4, align 8
  %5 = load %class.G*, %class.G** %3, align 8
  %6 = load i8**, i8*** %4, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1GD1Ev(%class.G* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.G*, align 8
  store %class.G* %0, %class.G** %2, align 8
  %3 = load %class.G*, %class.G** %2, align 8
  %4 = bitcast %class.G* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.G*
  tail call void @_ZN1GD1Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1GD0Ev(%class.G* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.G*, align 8
  store %class.G* %0, %class.G** %2, align 8
  %3 = load %class.G*, %class.G** %2, align 8
  %4 = bitcast %class.G* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.G*
  tail call void @_ZN1GD0Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1GC2Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %0, i8** noundef %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %class.G*, align 8
  %4 = alloca i8**, align 8
  store %class.G* %0, %class.G** %3, align 8
  store i8** %1, i8*** %4, align 8
  %5 = load %class.G*, %class.G** %3, align 8
  %6 = load i8**, i8*** %4, align 8
  %7 = load i8*, i8** %6, align 8
  %8 = bitcast %class.G* %5 to i32 (...)***
  %9 = bitcast i8* %7 to i32 (...)**
  store i32 (...)** %9, i32 (...)*** %8, align 8
  %10 = getelementptr inbounds i8*, i8** %6, i64 1
  %11 = load i8*, i8** %10, align 8
  %12 = bitcast %class.G* %5 to i8**
  %13 = load i8*, i8** %12, align 8
  %14 = getelementptr i8, i8* %13, i64 -40
  %15 = bitcast i8* %14 to i64*
  %16 = load i64, i64* %15, align 8
  %17 = bitcast %class.G* %5 to i8*
  %18 = getelementptr inbounds i8, i8* %17, i64 %16
  %19 = bitcast i8* %18 to i32 (...)***
  %20 = bitcast i8* %11 to i32 (...)**
  store i32 (...)** %20, i32 (...)*** %19, align 8
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1H3fooEv(%class.H* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #4 comdat align 2 {
  %2 = alloca %class.H*, align 8
  store %class.H* %0, %class.H** %2, align 8
  %3 = load %class.H*, %class.H** %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1HD1Ev(%class.H* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.H*, align 8
  store %class.H* %0, %class.H** %2, align 8
  %3 = load %class.H*, %class.H** %2, align 8
  call void @_ZN1HD2Ev(%class.H* noundef nonnull align 8 dereferenceable(8) %3, i8** noundef getelementptr inbounds ([5 x i8*], [5 x i8*]* @_ZTT1H, i64 0, i64 0)) #8
  %4 = bitcast %class.H* %3 to %class.G*
  call void @_ZN1GD2Ev(%class.G* noundef nonnull align 8 dereferenceable(8) %4, i8** noundef getelementptr inbounds ([5 x i8*], [5 x i8*]* @_ZTT1H, i64 0, i64 3)) #8
  %5 = bitcast %class.H* %3 to %class.F*
  call void @_ZN1FD2Ev(%class.F* noundef nonnull align 8 dereferenceable(8) %5) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1HD0Ev(%class.H* noundef nonnull align 8 dereferenceable(8) %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.H*, align 8
  store %class.H* %0, %class.H** %2, align 8
  %3 = load %class.H*, %class.H** %2, align 8
  call void @_ZN1HD1Ev(%class.H* noundef nonnull align 8 dereferenceable(8) %3) #8
  %4 = bitcast %class.H* %3 to i8*
  call void @_ZdlPv(i8* noundef %4) #9
  ret void
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n24_N1H3fooEv(%class.H* noundef %0) unnamed_addr #6 comdat align 2 {
  %2 = alloca %class.H*, align 8
  store %class.H* %0, %class.H** %2, align 8
  %3 = load %class.H*, %class.H** %2, align 8
  %4 = bitcast %class.H* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -24
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.H*
  tail call void @_ZN1H3fooEv(%class.H* noundef nonnull align 8 dereferenceable(8) %11)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN1HD2Ev(%class.H* noundef nonnull align 8 dereferenceable(8) %0, i8** noundef %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %class.H*, align 8
  %4 = alloca i8**, align 8
  store %class.H* %0, %class.H** %3, align 8
  store i8** %1, i8*** %4, align 8
  %5 = load %class.H*, %class.H** %3, align 8
  %6 = load i8**, i8*** %4, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1HD1Ev(%class.H* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.H*, align 8
  store %class.H* %0, %class.H** %2, align 8
  %3 = load %class.H*, %class.H** %2, align 8
  %4 = bitcast %class.H* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.H*
  tail call void @_ZN1HD1Ev(%class.H* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZTv0_n32_N1HD0Ev(%class.H* noundef %0) unnamed_addr #3 comdat align 2 {
  %2 = alloca %class.H*, align 8
  store %class.H* %0, %class.H** %2, align 8
  %3 = load %class.H*, %class.H** %2, align 8
  %4 = bitcast %class.H* %3 to i8*
  %5 = bitcast i8* %4 to i8**
  %6 = load i8*, i8** %5, align 8
  %7 = getelementptr inbounds i8, i8* %6, i64 -32
  %8 = bitcast i8* %7 to i64*
  %9 = load i64, i64* %8, align 8
  %10 = getelementptr inbounds i8, i8* %4, i64 %9
  %11 = bitcast i8* %10 to %class.H*
  tail call void @_ZN1HD0Ev(%class.H* noundef nonnull align 8 dereferenceable(8) %11) #8
  ret void
}

attributes #0 = { mustprogress noinline norecurse optnone uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon,+outline-atomics,+v8a" }
attributes #1 = { nobuiltin allocsize(0) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon,+outline-atomics,+v8a" }
attributes #2 = { argmemonly nofree nounwind willreturn writeonly }
attributes #3 = { noinline nounwind optnone uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon,+outline-atomics,+v8a" }
attributes #4 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon,+outline-atomics,+v8a" }
attributes #5 = { nobuiltin nounwind "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon,+outline-atomics,+v8a" }
attributes #6 = { noinline optnone uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon,+outline-atomics,+v8a" }
attributes #7 = { builtin allocsize(0) }
attributes #8 = { nounwind }
attributes #9 = { builtin nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 1, !"branch-target-enforcement", i32 0}
!2 = !{i32 1, !"sign-return-address", i32 0}
!3 = !{i32 1, !"sign-return-address-all", i32 0}
!4 = !{i32 1, !"sign-return-address-with-bkey", i32 0}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 1}
!9 = !{!"Ubuntu clang version 14.0.6"}
